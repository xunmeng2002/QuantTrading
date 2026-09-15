#include "SimExchange.h"
#include "MdbTickSettlementPriceSource.h"
#include "MdbTableRegistry.h"
#include "BackTestTableList.h"
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>
#include "Error.h"
#include "QuantUtility.h"
#include "OrderUtility.h"
#include "InitMdbFromCsv.h"
#include "MdbFieldConverter.h"
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <stdexcept>

using namespace std;
using namespace mdb;
using namespace spark;
using namespace spark::core;
using namespace dbadapters;
using namespace quanttrading;
using namespace quanttrading::ordermatch;
using namespace quanttrading::packages;

static DB* CreateDataDb(const std::string dbType, const std::string dbHost, const std::string dbUser, const std::string dbPassword)
{
    if (dbType == "0")
    {
        return new DuckdbWrapper(dbHost);
    }
    if (dbType == "2")
    {
        return new MysqlWrapper(dbHost);
    }
    if (dbType == "3")
    {
        return new MariadbWrapper(dbHost, dbUser, dbPassword);
    }
    return new SqliteWrapper(dbHost);
}

// RunID：本地时间到毫秒，作为本次回测输出库/快照目录的隔离后缀，多次回测互不覆盖
static std::string MakeRunID()
{
    std::tm* localTm = TimeUtility::GetLocalTm();
    auto milliSecond = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000;
    char runID[32] = { 0 };
    snprintf(runID, sizeof(runID), "%04d%02d%02d_%02d%02d%02d_%03lld",
        localTm->tm_year + 1900, localTm->tm_mon + 1, localTm->tm_mday,
        localTm->tm_hour, localTm->tm_min, localTm->tm_sec, static_cast<long long>(milliSecond));
    return runID;
}

// 输出库文件名派生：在扩展名前插入 _<RunID>（./BackTest.db → ./BackTest_<RunID>.db）
static std::string DeriveRunDbHost(const std::string& dbHost, const std::string& runID)
{
    auto extensionPos = dbHost.rfind('.');
    if (extensionPos == std::string::npos)
    {
        return dbHost + "_" + runID;
    }
    return dbHost.substr(0, extensionPos) + "_" + runID + dbHost.substr(extensionPos);
}

// 合约落库：主键已存在则就地更新，否则插入。
// 不能写成「先 Insert，失败再 Update」——Insert 失败路径已把记录回池，再拿它去 Select/Update 会读已释放对象并二次回池
static void InsertInstrumentOrUpdate(InstrumentTable* instrumentTable, Instrument* instrument)
{
    auto oldInstrument = instrumentTable->primaryKey->Select(instrument->ExchangeID, instrument->InstrumentID);
    if (oldInstrument == nullptr)
    {
        instrumentTable->Insert(instrument);
        return;
    }
    instrumentTable->Update(oldInstrument, instrument);
}


namespace quanttrading::backtest
{
SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_BackTestSpi(nullptr), m_HasSubMd(false), m_IsMdEnd(false),
	m_Registry(backtestTableList), m_CurrDate(""), m_CurrTime(""), m_SessionFile(config.SessionFile)
{
	auto matchMode = (MatchModeType)config.MatchMode;
	strcpy(m_TradingDay, config.StartTradingDay.c_str());
	strcpy(m_StartTradingDay, config.StartTradingDay.c_str());
	strcpy(m_EndTradingDay, config.EndTradingDay.c_str());
	m_MarketDataType = matchMode == MatchModeType::Bar ? MarketDataTypeType::Bar : MarketDataTypeType::Tick;
	memset(&m_PushMdTick, 0, sizeof(DepthMarketDataField));
	memset(&m_PushMdBar, 0, sizeof(BarMarketDataField));
	m_MdReader = new MdReader(config);
	m_RunID = MakeRunID();
	// Dump 以 fopen(dir//t_Xxx.csv) 落盘，目录缺失时静默失败，按 RunID 隔离前须先建目录
	m_DumpPath = config.DumpPath + "/" + m_RunID;
	std::error_code dumpDirError;
	std::filesystem::create_directories(m_DumpPath, dumpDirError);
	auto runDbHost = DeriveRunDbHost(config.DbHost, m_RunID);
	m_DB = CreateDataDb(config.DbType, runDbHost, config.DbUser, config.DbPassword);
	WriteLog(LogLevel::Info, "RunID:%s, DbHost:%s, DumpPath:%s", m_RunID.c_str(), runDbHost.c_str(), m_DumpPath.c_str());
    m_DBWriter = new AsyncDBWriter(m_DB, &m_Registry);
	m_DBWriter->Subscribe(this);
	m_Mdb = new Mdb(backtestTableList);
	m_OrderMatch = OrderMatch::CreateOrderMatch(matchMode, m_TradingDay);
	m_OrderMatch->Subscribe(this);
	m_PositionMaintenance = new quanttrading::settlement::PositionMaintenance(m_Mdb);
	m_BarSettlementPriceSource.m_LastMdBars = &m_LastMdBars;
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		m_SettlementPriceSource = new quanttrading::settlement::MdbTickSettlementPriceSource(m_Mdb);
	}
	else
	{
		m_SettlementPriceSource = &m_BarSettlementPriceSource;
	}
	m_Settlement = new quanttrading::settlement::Settlement(m_Mdb, m_SettlementPriceSource);
}
SimExchange::~SimExchange()
{
	delete m_MdReader;
	m_MdReader = nullptr;
	delete m_Mdb;
	m_Mdb = nullptr;
}
bool SimExchange::Init()
{
	if (m_DB == nullptr)
	{
		WriteLog(LogLevel::Error, "Create DB Failed.");
		return false;
	}
	// 交易节在首个订阅到达前装载：聚合器按交易节段首锚定桶边界，缺了它会静默回落墙钟对齐而不报错
	if (!m_TradeSessions.LoadFromFile(m_SessionFile))
	{
		WriteLog(LogLevel::Error, "Load trade sessions failed. SessionFile:%s", m_SessionFile.c_str());
		return false;
	}
	m_Mdb->Subscribe(m_DBWriter);

	m_MdReader->Init();
	InitMdInstrument();
	InitMainInstrument();
	SendRtnSessionBegin(m_TradingDay);
	return true;
}
bool SimExchange::Start()
{
	m_DBWriter->Start();
	ThreadBase::Start();
	return true;
}
void SimExchange::Stop()
{
	m_DBWriter->Stop();
	ThreadBase::Stop();
}
void SimExchange::Join()
{
	m_DBWriter->Join();
	ThreadBase::Join();
}

void SimExchange::OnDBConnected()
{
	
}
void SimExchange::OnDBDisConnected()
{

}

void SimExchange::OnOrder(mdb::Order* order)
{
	SendRtnOrder(order);
}
void SimExchange::OnOrderUpdate(mdb::Order* order, mdb::Order* newOrder)
{
    m_Mdb->order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(mdb::Trade* trade)
{
    m_Mdb->trade->Insert(trade);
	SendRtnTrade(trade);
	m_PositionMaintenance->UpdateOnTrade(trade);
}


void SimExchange::RegisterSpi(BackTestSpi* pSpi)
{
	m_BackTestSpi = pSpi;
}
int SimExchange::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataField* reqSubMd = ::Allocate<ReqSubMarketDataField>();
	memcpy(reqSubMd, reqSubMarketData, sizeof(ReqSubMarketDataField));
	{
		lock_guard<mutex> guard(m_QueueMutex);
		m_ReqSubMds.push_back(reqSubMd);
	}
	return 0;
}
int SimExchange::ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID)
{
	ReqSubMarketDataFinishedPackage* reqPackage = ReqSubMarketDataFinishedPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqSubMarketDataFinished = ::Allocate<ReqSubMarketDataFinishedField>();
	memcpy(reqPackage->ReqSubMarketDataFinished, reqSubMarketDataFinished, sizeof(ReqSubMarketDataFinishedField));

	{
		lock_guard<mutex> guard(m_QueueMutex);
		m_Packages.push_back(reqPackage);
	}
	return 0;
}
int SimExchange::ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestID)
{
	ReqRegisterAccountPackage* reqPackage = ReqRegisterAccountPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqRegisterAccount = ::Allocate<ReqRegisterAccountField>();
	memcpy(reqPackage->ReqRegisterAccount, reqRegisterAccount, sizeof(ReqRegisterAccountField));

	{
		lock_guard<mutex> guard(m_QueueMutex);
		m_Packages.push_back(reqPackage);
	}
	return 0;
}
int SimExchange::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));

	{
		lock_guard<mutex> guard(m_QueueMutex);
		m_Packages.push_back(reqPackage);
	}
	return 0;
}
int SimExchange::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));

	{
		lock_guard<mutex> guard(m_QueueMutex);
		m_Packages.push_back(reqPackage);
	}
	return 0;
}
void SimExchange::Run()
{
	HandlePackages();
	if (m_HasSubMd)
	{
		PushNextMd();
	}
	else
	{
		WriteLog(LogLevel::Info, "Waiting For SubMarketData.");
		this_thread::sleep_for(chrono::milliseconds(m_TimeOut));
	}
}
void SimExchange::HandlePackages()
{
	std::list<Package*> packages;
	{
		lock_guard<mutex> guard(m_QueueMutex);
		packages.swap(m_Packages);
	}
	for (auto package : packages)
	{
		switch (package->Head.PackageID)
		{
		case ReqRegisterAccountPackage::PackageID:
			HandleRegisterAccount((ReqRegisterAccountPackage*)package);
			break;
		case ReqSubMarketDataFinishedPackage::PackageID:
			HandleSubMarketDataFinished((ReqSubMarketDataFinishedPackage*)package);
			break;
		case ReqInsertOrderPackage::PackageID:
			HandleInsertOrder((ReqInsertOrderPackage*)package);
			break;
		case ReqCancelOrderPackage::PackageID:
			HandleCancelOrder((ReqCancelOrderPackage*)package);
			break;
		default:
			break;
		}
		package->Deallocate();
	}
}
void SimExchange::PushNextMd()
{
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		if (m_MdTicks.empty())
		{
			OnMdEnd();
		}
		else
		{
			auto mdTick = m_MdTicks.front();
			m_MdTicks.pop_front();
			PushNextTick(mdTick);
		}
	}
	else if (m_MarketDataType == MarketDataTypeType::Bar)
	{
		if (m_MdBars.empty())
		{
			OnMdEnd();
		}
		else
		{
			auto mdBar = m_MdBars.front();
			m_MdBars.pop_front();
			PushNextBar(mdBar);
		}
	}
}
void SimExchange::OnMdEnd()
{
	if (m_IsMdEnd)
	{
		return;
	}
	m_IsMdEnd = true;
	WriteLog(LogLevel::Info, "OnMdEnd");
	FlushBarAggregators();
    m_OrderMatch->OnTradingDayChange(m_TradingDay);
	Settlement();
	m_Mdb->Dump(m_DumpPath.c_str());
	WriteLog(LogLevel::Info, "Dump Completed\n");
	
	m_Mdb->InitDB();
    SendRtnMarketDataEnd();
}

void SimExchange::PushNextTick(mdb::DepthMarketData* mdTick)
{
	if (strcmp(mdTick->TradingDay, m_TradingDay) < 0)
	{
		WriteLog(LogLevel::Warning, "UnExpected Md, While MdTick TradingDay:%s less than CurrTradingDay:%s, DepthMarketData:%s", mdTick->TradingDay, m_TradingDay, mdTick->GetDebugString());
		return;
	}
	else if (strcmp(mdTick->TradingDay, m_TradingDay) > 0)
	{
		ChangeTradingDay(mdTick->TradingDay);
	}
	TimeUtility::GetDateTimeFromTimeStamp(mdTick->UpdateTs, m_CurrDate, m_CurrTime);
	m_OrderMatch->OnTick(mdTick);
	SendRtnDepthMarketData(mdTick);
	auto oldMdTick = m_Mdb->depthMarketData->primaryKey->Select(mdTick->TradingDay, mdTick->ExchangeID, mdTick->InstrumentID);
	if (oldMdTick == nullptr)
	{
		m_Mdb->depthMarketData->Insert(mdTick);
	}
	else
	{
		m_Mdb->depthMarketData->Update(oldMdTick, mdTick);
	}
}
void SimExchange::PushNextBar(mdb::BarMarketData* mdBar)
{
	if (strcmp(mdBar->TradingDay, m_TradingDay) < 0)
	{
		WriteLog(LogLevel::Warning, "UnExpected Md, While MdBar TradingDay:%s less than CurrTradingDay:%s, BarMarketData:%s", mdBar->TradingDay, m_TradingDay, mdBar->GetDebugString());
		return;
	}
	else if (strcmp(mdBar->TradingDay, m_TradingDay) > 0)
	{
		ChangeTradingDay(mdBar->TradingDay);
	}
    TimeUtility::GetDateTimeFromTimeStamp(mdBar->UpdateTs, m_CurrDate, m_CurrTime);
	// 撮合始终用数据集精度的原始 bar（聚合只改变推送给策略的粒度，不降低撮合精度）
	m_OrderMatch->OnBar(mdBar);
	PushBarMarketData(mdBar);
	// Insert 失败即回池（记录已被表释放，失败原因由表内日志给出）：末根 bar 只在入库成功时登记，
	// 否则结算价来源会取到悬空指针，且失败后读取 mdBar->InstrumentID 已是释放后访问
	if (m_Mdb->barMarketData->Insert(mdBar))
	{
		m_LastMdBars[mdBar->InstrumentID] = mdBar;
	}
}
void SimExchange::PushBarMarketData(mdb::BarMarketData* mdBar)
{
	// 输入字段就地读进 m_PushMdBar：未声明周期的合约直接把这份字段推给策略，不额外占缓冲
	MdbToField(mdBar, &m_PushMdBar);
	auto barAggregatorIt = m_InstrumentBarAggregators.find(mdBar->InstrumentID);
	if (barAggregatorIt == m_InstrumentBarAggregators.end())
	{
		OnBarMarketData(&m_PushMdBar);
		return;
	}
	// 声明了周期的合约交聚合器：闭桶时经 OnBarMarketData 推送桶内 bar，未闭桶则不推送
	barAggregatorIt->second->OnBarMarketData(&m_PushMdBar);
}
void SimExchange::OnBarMarketData(BarMarketDataField* bar)
{
	// 桶内 bar 与透传 bar 都是本次回调内有效的字段，订阅方复制后即弃
	m_BackTestSpi->OnRtnBarMarketData(bar);
}
bool SimExchange::BindBarAggregator(const char* exchangeID, const char* instrumentID, BarPrecesType barPreces, int barPeriod)
{
	if (barPeriod <= 0)
	{
		return true;
	}
	try
	{
		// 装载期预校验：数据集精度本就在手，不必等首根 bar 才发现不可聚合（那时已是引擎线程内抛异常）
		bar::BarAggregator::ValidatePrecesRelation(m_MdReader->GetBarPrecesType(), m_MdReader->GetBarPeriod(), barPreces, barPeriod, instrumentID);
	}
	catch (const std::logic_error& e)
	{
		WriteLog(LogLevel::Error, "SubMarketData rejected, bar period can not be served. ExchangeID:%s, InstrumentID:%s, Error:%s",
			exchangeID, instrumentID, e.what());
		return false;
	}
	const std::pair<BarPrecesType, int> targetPeriod(barPreces, barPeriod);
	auto barAggregatorIt = m_BarAggregators.find(targetPeriod);
	if (barAggregatorIt == m_BarAggregators.end())
	{
		auto barAggregator = std::make_unique<bar::BarAggregator>(m_TradeSessions, barPreces, barPeriod);
		barAggregator->Subscribe(this);
		barAggregatorIt = m_BarAggregators.emplace(targetPeriod, std::move(barAggregator)).first;
	}
	m_InstrumentBarAggregators[instrumentID] = barAggregatorIt->second.get();
	return true;
}
void SimExchange::FlushBarAggregators()
{
	for (auto& barAggregatorEntry : m_BarAggregators)
	{
		barAggregatorEntry.second->Flush();
	}
}

void SimExchange::HandleSubMarketDataFinished(ReqSubMarketDataFinishedPackage* reqPackage)
{
	std::list<ReqSubMarketDataField*> reqSubMds;
	{
		lock_guard<mutex> guard(m_QueueMutex);
		reqSubMds.swap(m_ReqSubMds);
	}
	map<std::string, list<MdSubscribe*>> instrumentMdSubscribes;
	// 订阅声明的目标周期按合约代码暂存：实际登记要等 MdSubscribe 展开出 RealInstrumentID（热门合约滚动时二者不同）
	map<std::string, ReqSubMarketDataField> instrumentBarPeriods;
	for (auto reqSubMd : reqSubMds)
	{
		if (instrumentMdSubscribes.find(reqSubMd->InstrumentID) != instrumentMdSubscribes.end())
		{
			WriteLog(LogLevel::Warning, "Repeat Subscribe for ExchangeID:%s InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
			::Deallocate(reqSubMd);
			continue;
		}
		instrumentBarPeriods[reqSubMd->InstrumentID] = *reqSubMd;
		auto& mdSubscribes = instrumentMdSubscribes[reqSubMd->InstrumentID];
		auto instrument = m_Mdb->instrument->primaryKey->Select(reqSubMd->ExchangeID, reqSubMd->InstrumentID);
		if (instrument == nullptr)
		{
			WriteLog(LogLevel::Error, "Cannot Find Instrument While SubMarketData. ExchangeID:%s, InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
			::Deallocate(reqSubMd);
			continue;
		}
		if (instrument->InstrumentClass == InstrumentClassType::Normal)
		{
			MdSubscribe* mdSubscribe = MdSubscribe::Allocate();
			memset(mdSubscribe, 0, sizeof(MdSubscribe));
			strcpy(mdSubscribe->ExchangeID, instrument->ExchangeID);
			strcpy(mdSubscribe->InstrumentID, instrument->InstrumentID);
			strcpy(mdSubscribe->RealInstrumentID, instrument->InstrumentID);
			strcpy(mdSubscribe->ProductID, instrument->ProductID);
			mdSubscribe->ProductClass = instrument->ProductClass;
			strcpy(mdSubscribe->StartTradingDay, m_StartTradingDay);
			strcpy(mdSubscribe->EndTradingDay, m_EndTradingDay);
			
			mdSubscribes.push_back(mdSubscribe);
		}
		else
		{
			auto startIt = m_Mdb->hotInstrument->tradingDayIndex->LowerBound(instrument->ExchangeID, instrument->ProductID, instrument->Rank, m_StartTradingDay);
			auto endIt = m_Mdb->hotInstrument->tradingDayIndex->UpperBound(instrument->ExchangeID, instrument->ProductID, instrument->Rank, m_EndTradingDay);
			if (startIt == endIt)
			{
				WriteLog(LogLevel::Warning, "Cannot Find HotInstrument While SubMarketData. ExchangeID:%s, ProductID:%s, Rank:%d, StartTradingDay:%s, EndTradingDay:%s",
					instrument->ExchangeID, instrument->ProductID, instrument->Rank, m_StartTradingDay, m_EndTradingDay);
				continue;
			}
			MdSubscribe* mdSubscribe = MdSubscribe::Allocate();
			memset(mdSubscribe, 0, sizeof(MdSubscribe));
			strcpy(mdSubscribe->ExchangeID, instrument->ExchangeID);
			strcpy(mdSubscribe->InstrumentID, instrument->InstrumentID);
			strcpy(mdSubscribe->RealInstrumentID, (*startIt)->InstrumentID);
			strcpy(mdSubscribe->ProductID, instrument->ProductID);
			mdSubscribe->ProductClass = instrument->ProductClass;
			strcpy(mdSubscribe->StartTradingDay, (*startIt)->TradingDay);
			strcpy(mdSubscribe->EndTradingDay, (*startIt)->TradingDay);
			for (auto& it = startIt; it != endIt; ++it)
			{
				auto hotInstrument = *it;
				if (strcmp(mdSubscribe->RealInstrumentID, hotInstrument->InstrumentID) == 0)
				{
					strcpy(mdSubscribe->EndTradingDay, hotInstrument->TradingDay);
				}
				else
				{
					mdSubscribes.push_back(mdSubscribe);

					mdSubscribe = MdSubscribe::Allocate();
					memset(mdSubscribe, 0, sizeof(MdSubscribe));
					strcpy(mdSubscribe->ExchangeID, instrument->ExchangeID);
					strcpy(mdSubscribe->InstrumentID, instrument->InstrumentID);
					strcpy(mdSubscribe->RealInstrumentID, hotInstrument->InstrumentID);
					strcpy(mdSubscribe->ProductID, instrument->ProductID);
					mdSubscribe->ProductClass = instrument->ProductClass;
					strcpy(mdSubscribe->StartTradingDay, hotInstrument->TradingDay);
					strcpy(mdSubscribe->EndTradingDay, hotInstrument->TradingDay);
				}
			}
			mdSubscribes.push_back(mdSubscribe);
		}
        ::Deallocate(reqSubMd);
	}
	for (auto& it : instrumentMdSubscribes)
	{
		auto& mdSubscribes = it.second;
		list<MdSubscribe*> addMdSubscribes;
		for (auto it = mdSubscribes.begin(); it != mdSubscribes.end(); ++it)
		{
			auto mdSubscribe = *it;
			int startYear = int(atoi(mdSubscribe->StartTradingDay) / 10000);
			int endYear = int(atoi(mdSubscribe->EndTradingDay) / 10000);
			while (endYear > startYear)
			{
				auto newMdSubscribe = MdSubscribe::Allocate();
				memcpy(newMdSubscribe, mdSubscribe, sizeof(MdSubscribe));
				strcpy(newMdSubscribe->EndTradingDay, to_string(startYear * 10000 + 1231).c_str());
				addMdSubscribes.push_back(newMdSubscribe);
				strcpy(mdSubscribe->StartTradingDay, to_string((++startYear) * 10000 + 101).c_str());
			}
		}
		for (auto mdSubscribe : addMdSubscribes)
		{
			mdSubscribes.push_back(mdSubscribe);
		}
	}
	// 聚合器登记键取订阅的 InstrumentID（MdReader 按 mdSubscribe->InstrumentID 给 bar 打戳，PushBarMarketData 也按同一字段查表），
	// 不能用 SQL 读取用的 RealInstrumentID（热门合约滚动时二者不同，用它登记会让 find 落空、声明的周期静默失效）；
	// 声明的周期无法由数据集精度聚合时属配置错误，与「订阅为空」同样直接收尾，不静默降级为数据集精度
	bool hasRejectedBarPeriod = false;
	for (auto& it : instrumentMdSubscribes)
	{
		auto reqSubMdIt = instrumentBarPeriods.find(it.first);
		if (reqSubMdIt == instrumentBarPeriods.end() || reqSubMdIt->second.BarPeriod <= 0)
		{
			continue;
		}
		for (auto mdSubscribe : it.second)
		{
			if (!BindBarAggregator(mdSubscribe->ExchangeID, mdSubscribe->InstrumentID, reqSubMdIt->second.BarPreces, reqSubMdIt->second.BarPeriod))
			{
				hasRejectedBarPeriod = true;
			}
		}
	}
	if (hasRejectedBarPeriod)
	{
		OnMdEnd();
		return;
	}
	map<int, list<MdSubscribe*>> yearMdSubscribes;
	for (auto& it : instrumentMdSubscribes)
	{
		for (auto mdSubscribe : it.second)
		{
			int year = int(atoi(mdSubscribe->StartTradingDay) / 10000);
			// 先入库再入年份队列：Insert 失败即回池，此指针不可再读取（明细由表内日志给出），
			// 也不得进年份队列——否则行情读取线程会拿着已释放的订阅去取数
			if (!m_Mdb->mdSubscribe->Insert(mdSubscribe))
			{
				WriteLog(LogLevel::Warning, "MdSubscribe dropped, its market data will not be read. InstrumentID:%s, Year:%d", it.first.c_str(), year);
				continue;
			}
			yearMdSubscribes[year].push_back(mdSubscribe);
		}
	}
	if (yearMdSubscribes.empty())
	{
		WriteLog(LogLevel::Warning, "MdSubscribes is Empty.");
		OnMdEnd();
		return;
	}
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		std::list<DepthMarketData*> mdTicks;
		for (auto& it : yearMdSubscribes)
		{
			auto& mdSubscribes = it.second;
			m_MdReader->ReadMdTick(mdSubscribes, mdTicks);
			m_MdTicks.splice(m_MdTicks.end(), mdTicks);
		}
	}
	else
	{
		std::list<BarMarketData*> mdBars;
		for (auto& it : yearMdSubscribes)
		{
			auto& mdSubscribes = it.second;
			m_MdReader->ReadMdBar(mdSubscribes, mdBars);
			m_MdBars.splice(m_MdBars.end(), mdBars);
		}
	}
	m_HasSubMd = true;
}
void SimExchange::HandleRegisterAccount(ReqRegisterAccountPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleRegisterAccount %s", reqPackage->GetDebugString());
	auto reqRegisterAccount = reqPackage->ReqRegisterAccount;
	auto account = m_Mdb->account->primaryKey->Select(reqRegisterAccount->AccountID);
	if (account == nullptr)
	{
		// 回测账户按需自建（同 BackTestInit 种子语义）：Balance=0，资金账目由日终结算按日滚动
		account = mdb::Account::Allocate();
		memset(account, 0, sizeof(mdb::Account));
		strcpy(account->AccountID, reqRegisterAccount->AccountID);
		strcpy(account->AccountName, reqRegisterAccount->AccountID);
		account->AccountType = AccountTypeType::Primary;
		account->AccountStatus = AccountStatusType::Normal;
		account->TradeGroupID = 1;
		account->RiskGroupID = 1;
		account->CommissionGroupID = 1;
		m_Mdb->account->Insert(account);

		auto capital = mdb::Capital::Allocate();
		memset(capital, 0, sizeof(mdb::Capital));
		strcpy(capital->TradingDay, m_TradingDay);
		strcpy(capital->AccountID, account->AccountID);
		capital->AccountType = AccountTypeType::Primary;
		m_Mdb->capital->Insert(capital);
		WriteLog(LogLevel::Info, "Account registered, AccountID:%s, TradingDay:%s", account->AccountID, m_TradingDay);
	}
	else
	{
		WriteLog(LogLevel::Info, "Account already registered, AccountID:%s", account->AccountID);
	}
	SendRspRegisterAccount(reqPackage, ErrorNone);
}
void SimExchange::HandleInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleInsertOrder %s", reqPackage->GetDebugString());
	auto reqInsertOrder = reqPackage->ReqInsertOrder;
	int errorID = ErrorNone;
	auto instrument = m_Mdb->instrument->primaryKey->Select(reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		SendRspOrderInsert(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = m_Mdb->account->primaryKey->Select(reqInsertOrder->AccountID);
	if (account == nullptr)
	{
		SendRspOrderInsert(reqPackage, ErrorAccountNotExist);
		return;
	}
	errorID = CheckForInsertOrder(reqInsertOrder, instrument);
	SendRspOrderInsert(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	
	auto order = CreateOrder(reqPackage, account, instrument, m_TradingDay, m_CurrDate, m_CurrTime);
	m_Mdb->order->Insert(order);
	m_OrderMatch->InsertOrder(order);
}
void SimExchange::HandleCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleCancelOrder %s", reqPackage->GetDebugString());
	int errorID = ErrorNone;
	auto order = m_Mdb->order->primaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID, 
		reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->OrderID);
	if (order == nullptr)
	{
		order = m_Mdb->order->clientOrderIDUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
			reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->SessionID, reqPackage->ReqCancelOrder->ClientOrderID);
		if (order == nullptr)
		{
			errorID = ErrorOrderNotExist;
		}
	}
	if (order != nullptr)
	{
		errorID = CheckForCancelOrder(order);
	}
	SendRspCancelOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	m_OrderMatch->CancelOrder(order);
}

void SimExchange::InitMdInstrument()
{
	std::list<mdb::Instrument*> instruments;
	m_MdReader->ReadMdInstrument(instruments);
	std::map<std::string, std::list<mdb::Instrument*>> productInstruments;
	for (auto instrument : instruments)
	{
		auto& productInstrument = productInstruments[instrument->ProductID];
		productInstrument.push_back(instrument);
	}
	for (auto& it : productInstruments)
	{
		if (it.second.empty())
			continue;
		auto& exchangeID = it.second.front()->ExchangeID;
		ProductIDType productID;
		strcpy(productID, it.first.c_str());
		auto product = m_Mdb->product->primaryKey->Select(exchangeID, productID);
		if (product != nullptr)
		{
			for (auto instrument : it.second)
			{
				strcpy(instrument->ExchangeInstID, instrument->InstrumentID);
				strcpy(instrument->InstrumentName, product->ProductName);
				instrument->ProductClass = product->ProductClass;
				instrument->InstrumentClass = InstrumentClassType::Normal;
				instrument->Rank = 0;
				instrument->VolumeMultiple = product->VolumeMultiple;
				instrument->PriceTick = product->PriceTick;
				instrument->MaxMarketOrderVolume = product->MaxMarketOrderVolume;
				instrument->MinMarketOrderVolume = product->MinMarketOrderVolume;
				instrument->MaxLimitOrderVolume = product->MaxLimitOrderVolume;
				instrument->MinLimitOrderVolume = product->MinLimitOrderVolume;
				strcpy(instrument->SessionName, product->SessionName);
				InsertInstrumentOrUpdate(m_Mdb->instrument, instrument);
			}
		}
		else
		{
			for (auto instrument : it.second)
			{
				strcpy(instrument->ExchangeInstID, instrument->InstrumentID);
				instrument->InstrumentClass = InstrumentClassType::Normal;
				instrument->Rank = 0;
				instrument->VolumeMultiple = 1;
				instrument->PriceTick = 0;
				instrument->MaxMarketOrderVolume = 0;
				instrument->MinMarketOrderVolume = 0;
				instrument->MaxLimitOrderVolume = 0;
				instrument->MinLimitOrderVolume = 0;
				strcpy(instrument->SessionName, "FD0900");

				InsertInstrumentOrUpdate(m_Mdb->instrument, instrument);
			}
		}
	}
}
void SimExchange::InitMainInstrument()
{
	auto productPair = m_Mdb->product->primaryKey->SelectAll();
	for (auto& it = productPair.first; it != productPair.second; ++it)
	{
		auto product = *it;
		if (product->ProductClass != ProductClassType::Future)
			continue;
		auto instrument1 = ::Allocate<mdb::Instrument>();
		auto instrument2 = ::Allocate<mdb::Instrument>();
		auto instrument3 = ::Allocate<mdb::Instrument>();
		memset(instrument1, 0, sizeof(mdb::Instrument));
		memset(instrument2, 0, sizeof(mdb::Instrument));
		memset(instrument3, 0, sizeof(mdb::Instrument));
		strcpy(instrument1->ExchangeID, product->ExchangeID);
		strcpy(instrument1->InstrumentID, (product->ProductID + std::string(".Hot")).c_str());
		strcpy(instrument1->ProductID, product->ProductID);
		strcpy(instrument1->InstrumentName, product->ProductName);
		instrument1->ProductClass = product->ProductClass;
		instrument1->InstrumentClass = InstrumentClassType::Main;
		instrument1->Rank = 1;
		instrument1->VolumeMultiple = product->VolumeMultiple;
		instrument1->PriceTick = product->PriceTick;
		instrument1->MaxMarketOrderVolume = product->MaxMarketOrderVolume;
		instrument1->MinMarketOrderVolume = product->MinMarketOrderVolume;
		instrument1->MaxLimitOrderVolume = product->MaxLimitOrderVolume;
		instrument1->MinLimitOrderVolume = product->MinLimitOrderVolume;
		strcpy(instrument1->SessionName, product->SessionName);

		strcpy(instrument2->ExchangeID, product->ExchangeID);
		strcpy(instrument2->InstrumentID, (product->ProductID + std::string(".Second")).c_str());
		strcpy(instrument2->ProductID, product->ProductID);
		strcpy(instrument2->InstrumentName, product->ProductName);
		instrument2->ProductClass = product->ProductClass;
		instrument2->InstrumentClass = InstrumentClassType::Main;
		instrument2->Rank = 1;
		instrument2->VolumeMultiple = product->VolumeMultiple;
		instrument2->PriceTick = product->PriceTick;
		instrument2->MaxMarketOrderVolume = product->MaxMarketOrderVolume;
		instrument2->MinMarketOrderVolume = product->MinMarketOrderVolume;
		instrument2->MaxLimitOrderVolume = product->MaxLimitOrderVolume;
		instrument2->MinLimitOrderVolume = product->MinLimitOrderVolume;
		strcpy(instrument2->SessionName, product->SessionName);

		strcpy(instrument3->ExchangeID, product->ExchangeID);
		strcpy(instrument3->InstrumentID, (product->ProductID + std::string(".Third")).c_str());
		strcpy(instrument3->ProductID, product->ProductID);
		strcpy(instrument3->InstrumentName, product->ProductName);
		instrument3->ProductClass = product->ProductClass;
		instrument3->InstrumentClass = InstrumentClassType::Main;
		instrument3->Rank = 1;
		instrument3->VolumeMultiple = product->VolumeMultiple;
		instrument3->PriceTick = product->PriceTick;
		instrument3->MaxMarketOrderVolume = product->MaxMarketOrderVolume;
		instrument3->MinMarketOrderVolume = product->MinMarketOrderVolume;
		instrument3->MaxLimitOrderVolume = product->MaxLimitOrderVolume;
		instrument3->MinLimitOrderVolume = product->MinLimitOrderVolume;
		strcpy(instrument3->SessionName, product->SessionName);

		m_Mdb->instrument->Insert(instrument1);
		m_Mdb->instrument->Insert(instrument2);
		m_Mdb->instrument->Insert(instrument3);
	}
}
void SimExchange::ChangeTradingDay(const DateType& nextTradingDay)
{
	// 先闭合本日残桶：尾桶的 BarTime 属上一交易日，晚一交易日的首根 bar 才收口会把它推到次日推送
	FlushBarAggregators();
    m_OrderMatch->OnTradingDayChange(nextTradingDay);
	Settlement();
	Init(nextTradingDay);
}
void SimExchange::Settlement()
{
	m_Settlement->Settle(m_TradingDay);
	SendRtnSessionEnd(m_TradingDay);
}
void SimExchange::Init(const DateType& nextTradingDay)
{
	m_Settlement->RollToNextDay(m_TradingDay, nextTradingDay);
	strcpy(m_TradingDay, nextTradingDay);
	SendRtnSessionBegin(nextTradingDay);
}

PriceType SimExchange::BarSettlementPriceSource::GetSettlementPrice(const mdb::PositionDetail* positionDetail)
{
	auto it = m_LastMdBars->find(positionDetail->InstrumentID);
	if (it != m_LastMdBars->end() && it->second != nullptr)
	{
		return it->second->Close;
	}
	return positionDetail->PreSettlementPrice;
}

void SimExchange::SendRspRegisterAccount(ReqRegisterAccountPackage* reqPackage, int errorID)
{
	RspInfoField rspInfo;
	rspInfo.ErrorID = errorID;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorID));
	RspRegisterAccountField rspRegisterAccount;
	memset(&rspRegisterAccount, 0, sizeof(RspRegisterAccountField));
	strcpy(rspRegisterAccount.AccountID, reqPackage->ReqRegisterAccount->AccountID);
	m_BackTestSpi->OnRspRegisterAccount(&rspRegisterAccount, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspRegisterAccount: AccountID:%s, ErrorID:%d, ErrorMsg:%s", rspRegisterAccount.AccountID, rspInfo.ErrorID, rspInfo.ErrorMsg);
}
void SimExchange::SendRspOrderInsert(ReqInsertOrderPackage* reqPackage, int errorID)
{
	RspInfoField rspInfo;
	rspInfo.ErrorID = errorID;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorID));

	m_BackTestSpi->OnRspInsertOrder(reqPackage->ReqInsertOrder, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspOrderInsert: ErrorID:%d, ErrorMsg:%s", rspInfo.ErrorID, rspInfo.ErrorMsg);
}
void SimExchange::SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorID)
{
	RspInfoField rspInfo;
	rspInfo.ErrorID = errorID;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorID));

	m_BackTestSpi->OnRspCancelOrder(reqPackage->ReqCancelOrder, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspCancelOrder: ErrorID:%d, ErrorMsg:%s", rspInfo.ErrorID, rspInfo.ErrorMsg);
}
void SimExchange::SendRtnOrder(mdb::Order* order)
{
	auto orderField = ::Allocate<OrderField>();
	MdbToField(order, orderField);
	m_BackTestSpi->OnRtnOrder(orderField);
	::Deallocate(orderField);
}
void SimExchange::SendRtnTrade(mdb::Trade* trade)
{
	auto tradeField = ::Allocate<TradeField>();
	MdbToField(trade, tradeField);
	m_BackTestSpi->OnRtnTrade(tradeField);
	::Deallocate(tradeField);
}
void SimExchange::SendRtnDepthMarketData(mdb::DepthMarketData* mdTick)
{
    MdbToField(mdTick, &m_PushMdTick);
	m_BackTestSpi->OnRtnDepthMarketData(&m_PushMdTick);
}
void SimExchange::SendRtnMarketDataEnd()
{
    MarketDataEndField marketDataEnd;
    memcpy(marketDataEnd.TradingDay, m_TradingDay, sizeof(DateType));
    m_BackTestSpi->OnRtnMarketDataEnd(&marketDataEnd);
}
void SimExchange::SendRtnSessionBegin(const DateType& tradingDay)
{
	SessionBeginField sessionBegin;
	strcpy(sessionBegin.TradingDay, tradingDay);
	m_BackTestSpi->OnRtnSessionBegin(&sessionBegin);
}
void SimExchange::SendRtnSessionEnd(const DateType& tradingDay)
{
	SessionEndField sessionEnd;
	strcpy(sessionEnd.TradingDay, tradingDay);
	m_BackTestSpi->OnRtnSessionEnd(&sessionEnd);
}
}
