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
#include <DbAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DbAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DbAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DbAdapters/MariadbWrapper/MariadbWrapper.h>
#include <assert.h>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <stdexcept>

using namespace std;
using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;
using namespace DbAdapters;
using namespace QuantTrading;
using namespace QuantTrading::ordermatch;
using namespace QuantTrading::Packages;

static Db* CreateDataDb(const std::string dbType, const std::string dbHost, const std::string dbUser, const std::string dbPassword)
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
    auto oldInstrument = instrumentTable->PrimaryKey->Select(instrument->ExchangeId, instrument->InstrumentId);
    if (oldInstrument == nullptr)
    {
        instrumentTable->Insert(instrument);
        return;
    }
    instrumentTable->Update(oldInstrument, instrument);
}


namespace QuantTrading::BackTest
{
SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), backTestSpi_(nullptr), hasSubMd_(false), isMdEnd_(false),
	registry_(BackTestTableList), currDate_(""), currTime_(""), sessionFile_(config.SessionFile)
{
	auto matchMode = (MatchModeType)config.MatchMode;
	strcpy(tradingDay_, config.StartTradingDay.c_str());
	strcpy(startTradingDay_, config.StartTradingDay.c_str());
	strcpy(endTradingDay_, config.EndTradingDay.c_str());
	marketDataType_ = matchMode == MatchModeType::Bar ? MarketDataTypeType::Bar : MarketDataTypeType::Tick;
	memset(&pushMdTick_, 0, sizeof(DepthMarketDataField));
	memset(&pushMdBar_, 0, sizeof(BarMarketDataField));
	mdReader_ = new MdReader(config);
	runId_ = MakeRunID();
	// Dump 以 fopen(dir//t_Xxx.csv) 落盘，目录缺失时静默失败，按 RunID 隔离前须先建目录
	dumpPath_ = config.DumpPath + "/" + runId_;
	std::error_code dumpDirError;
	std::filesystem::create_directories(dumpPath_, dumpDirError);
	auto runDbHost = DeriveRunDbHost(config.DbHost, runId_);
	db_ = CreateDataDb(config.DbType, runDbHost, config.DbUser, config.DbPassword);
	WriteLog(LogLevel::Info, "RunID:%s, DbHost:%s, DumpPath:%s", runId_.c_str(), runDbHost.c_str(), dumpPath_.c_str());
    dbWriter_ = new AsyncDbWriter(db_, &registry_);
	dbWriter_->Subscribe(this);
	mdb_ = new Mdb(BackTestTableList);
	orderMatch_ = OrderMatch::CreateOrderMatch(matchMode, tradingDay_);
	orderMatch_->Subscribe(this);
	positionMaintenance_ = new QuantTrading::Settlement::PositionMaintenance(mdb_);
	barSettlementPriceSource_.lastMdBars_ = &lastMdBars_;
	if (marketDataType_ == MarketDataTypeType::Tick)
	{
		settlementPriceSource_ = new QuantTrading::Settlement::MdbTickSettlementPriceSource(mdb_);
	}
	else
	{
		settlementPriceSource_ = &barSettlementPriceSource_;
	}
	settlement_ = new QuantTrading::Settlement::Settlement(mdb_, settlementPriceSource_);
}
SimExchange::~SimExchange()
{
	delete mdReader_;
	mdReader_ = nullptr;
	delete mdb_;
	mdb_ = nullptr;
}
bool SimExchange::Init()
{
	if (db_ == nullptr)
	{
		WriteLog(LogLevel::Error, "Create Db Failed.");
		return false;
	}
	// 交易节在首个订阅到达前装载：聚合器按交易节段首锚定桶边界，缺了它会静默回落墙钟对齐而不报错
	if (!tradeSessions_.LoadFromFile(sessionFile_))
	{
		WriteLog(LogLevel::Error, "Load trade sessions failed. SessionFile:%s", sessionFile_.c_str());
		return false;
	}
	mdb_->Subscribe(dbWriter_);

	mdReader_->Init();
	InitMdInstrument();
	InitMainInstrument();
	SendRtnSessionBegin(tradingDay_);
	return true;
}
bool SimExchange::Start()
{
	dbWriter_->Start();
	ThreadBase::Start();
	return true;
}
void SimExchange::Stop()
{
	dbWriter_->Stop();
	ThreadBase::Stop();
}
void SimExchange::Join()
{
	dbWriter_->Join();
	ThreadBase::Join();
}

void SimExchange::OnDbConnected()
{
	
}
void SimExchange::OnDbDisConnected()
{

}

void SimExchange::OnOrder(QuantTrading::Order* order)
{
	SendRtnOrder(order);
}
void SimExchange::OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder)
{
    mdb_->Order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(QuantTrading::Trade* trade)
{
    mdb_->Trade->Insert(trade);
	SendRtnTrade(trade);
	positionMaintenance_->UpdateOnTrade(trade);
}


void SimExchange::RegisterSpi(BackTestSpi* pSpi)
{
	backTestSpi_ = pSpi;
}
int SimExchange::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataField* reqSubMd = ::Allocate<ReqSubMarketDataField>();
	memcpy(reqSubMd, reqSubMarketData, sizeof(ReqSubMarketDataField));
	{
		lock_guard<mutex> guard(queueMutex_);
		reqSubMds_.push_back(reqSubMd);
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
		lock_guard<mutex> guard(queueMutex_);
		packages_.push_back(reqPackage);
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
		lock_guard<mutex> guard(queueMutex_);
		packages_.push_back(reqPackage);
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
		lock_guard<mutex> guard(queueMutex_);
		packages_.push_back(reqPackage);
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
		lock_guard<mutex> guard(queueMutex_);
		packages_.push_back(reqPackage);
	}
	return 0;
}
void SimExchange::Run()
{
	HandlePackages();
	if (hasSubMd_)
	{
		PushNextMd();
	}
	else
	{
		WriteLog(LogLevel::Info, "Waiting For SubMarketData.");
		this_thread::sleep_for(chrono::milliseconds(timeOut_));
	}
}
void SimExchange::HandlePackages()
{
	std::list<Package*> packages;
	{
		lock_guard<mutex> guard(queueMutex_);
		packages.swap(packages_);
	}
	for (auto package : packages)
	{
		switch (package->Head.PackageId)
		{
		case ReqRegisterAccountPackage::PackageId:
			HandleRegisterAccount((ReqRegisterAccountPackage*)package);
			break;
		case ReqSubMarketDataFinishedPackage::PackageId:
			HandleSubMarketDataFinished((ReqSubMarketDataFinishedPackage*)package);
			break;
		case ReqInsertOrderPackage::PackageId:
			HandleInsertOrder((ReqInsertOrderPackage*)package);
			break;
		case ReqCancelOrderPackage::PackageId:
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
	if (marketDataType_ == MarketDataTypeType::Tick)
	{
		if (mdTicks_.empty())
		{
			OnMdEnd();
		}
		else
		{
			auto mdTick = mdTicks_.front();
			mdTicks_.pop_front();
			PushNextTick(mdTick);
		}
	}
	else if (marketDataType_ == MarketDataTypeType::Bar)
	{
		if (mdBars_.empty())
		{
			OnMdEnd();
		}
		else
		{
			auto mdBar = mdBars_.front();
			mdBars_.pop_front();
			PushNextBar(mdBar);
		}
	}
}
void SimExchange::OnMdEnd()
{
	if (isMdEnd_)
	{
		return;
	}
	isMdEnd_ = true;
	WriteLog(LogLevel::Info, "OnMdEnd");
	FlushBarAggregators();
    orderMatch_->OnTradingDayChange(tradingDay_);
	Settlement();
	mdb_->Dump(dumpPath_.c_str());
	WriteLog(LogLevel::Info, "Dump Completed\n");
	
	mdb_->InitDb();
    SendRtnMarketDataEnd();
}

void SimExchange::PushNextTick(QuantTrading::DepthMarketData* mdTick)
{
	if (strcmp(mdTick->TradingDay, tradingDay_) < 0)
	{
		WriteLog(LogLevel::Warning, "UnExpected Md, While MdTick TradingDay:%s less than CurrTradingDay:%s, DepthMarketData:%s", mdTick->TradingDay, tradingDay_, mdTick->GetDebugString());
		return;
	}
	else if (strcmp(mdTick->TradingDay, tradingDay_) > 0)
	{
		ChangeTradingDay(mdTick->TradingDay);
	}
	TimeUtility::GetDateTimeFromTimeStamp(mdTick->UpdateTs, currDate_, currTime_);
	orderMatch_->OnTick(mdTick);
	SendRtnDepthMarketData(mdTick);
	auto oldMdTick = mdb_->DepthMarketData->PrimaryKey->Select(mdTick->TradingDay, mdTick->ExchangeId, mdTick->InstrumentId);
	if (oldMdTick == nullptr)
	{
		mdb_->DepthMarketData->Insert(mdTick);
	}
	else
	{
		mdb_->DepthMarketData->Update(oldMdTick, mdTick);
	}
}
void SimExchange::PushNextBar(QuantTrading::BarMarketData* mdBar)
{
	if (strcmp(mdBar->TradingDay, tradingDay_) < 0)
	{
		WriteLog(LogLevel::Warning, "UnExpected Md, While MdBar TradingDay:%s less than CurrTradingDay:%s, BarMarketData:%s", mdBar->TradingDay, tradingDay_, mdBar->GetDebugString());
		return;
	}
	else if (strcmp(mdBar->TradingDay, tradingDay_) > 0)
	{
		ChangeTradingDay(mdBar->TradingDay);
	}
    TimeUtility::GetDateTimeFromTimeStamp(mdBar->UpdateTs, currDate_, currTime_);
	// 撮合始终用数据集精度的原始 bar（聚合只改变推送给策略的粒度，不降低撮合精度）
	orderMatch_->OnBar(mdBar);
	PushBarMarketData(mdBar);
	// Insert 失败即回池（记录已被表释放，失败原因由表内日志给出）：末根 bar 只在入库成功时登记，
	// 否则结算价来源会取到悬空指针，且失败后读取 mdBar->InstrumentId 已是释放后访问
	if (mdb_->BarMarketData->Insert(mdBar))
	{
		lastMdBars_[mdBar->InstrumentId] = mdBar;
	}
}
void SimExchange::PushBarMarketData(QuantTrading::BarMarketData* mdBar)
{
	// 输入字段就地读进 pushMdBar_：未声明周期的合约直接把这份字段推给策略，不额外占缓冲
	MdbToField(mdBar, &pushMdBar_);
	auto barAggregatorIt = instrumentBarAggregators_.find(mdBar->InstrumentId);
	if (barAggregatorIt == instrumentBarAggregators_.end())
	{
		OnBarMarketData(&pushMdBar_);
		return;
	}
	// 声明了周期的合约交聚合器：闭桶时经 OnBarMarketData 推送桶内 bar，未闭桶则不推送
	barAggregatorIt->second->OnBarMarketData(&pushMdBar_);
}
void SimExchange::OnBarMarketData(BarMarketDataField* bar)
{
	// 桶内 bar 与透传 bar 都是本次回调内有效的字段，订阅方复制后即弃
	backTestSpi_->OnRtnBarMarketData(bar);
}
bool SimExchange::BindBarAggregator(const char* exchangeId, const char* instrumentId, BarPrecesType barPreces, int barPeriod)
{
	if (barPeriod <= 0)
	{
		return true;
	}
	try
	{
		// 装载期预校验：数据集精度本就在手，不必等首根 bar 才发现不可聚合（那时已是引擎线程内抛异常）
		Bar::BarAggregator::ValidatePrecesRelation(mdReader_->GetBarPrecesType(), mdReader_->GetBarPeriod(), barPreces, barPeriod, instrumentId);
	}
	catch (const std::logic_error& e)
	{
		WriteLog(LogLevel::Error, "SubMarketData rejected, bar period can not be served. ExchangeId:%s, InstrumentId:%s, Error:%s",
			exchangeId, instrumentId, e.what());
		return false;
	}
	const std::pair<BarPrecesType, int> targetPeriod(barPreces, barPeriod);
	auto barAggregatorIt = barAggregators_.find(targetPeriod);
	if (barAggregatorIt == barAggregators_.end())
	{
		auto barAggregator = std::make_unique<Bar::BarAggregator>(tradeSessions_, barPreces, barPeriod);
		barAggregator->Subscribe(this);
		barAggregatorIt = barAggregators_.emplace(targetPeriod, std::move(barAggregator)).first;
	}
	instrumentBarAggregators_[instrumentId] = barAggregatorIt->second.get();
	return true;
}
void SimExchange::FlushBarAggregators()
{
	for (auto& barAggregatorEntry : barAggregators_)
	{
		barAggregatorEntry.second->Flush();
	}
}

void SimExchange::HandleSubMarketDataFinished(ReqSubMarketDataFinishedPackage* reqPackage)
{
	std::list<ReqSubMarketDataField*> reqSubMds;
	{
		lock_guard<mutex> guard(queueMutex_);
		reqSubMds.swap(reqSubMds_);
	}
	map<std::string, list<MdSubscribe*>> instrumentMdSubscribes;
	// 订阅声明的目标周期按合约代码暂存：实际登记要等 MdSubscribe 展开出 RealInstrumentId（热门合约滚动时二者不同）
	map<std::string, ReqSubMarketDataField> instrumentBarPeriods;
	for (auto reqSubMd : reqSubMds)
	{
		if (instrumentMdSubscribes.find(reqSubMd->InstrumentId) != instrumentMdSubscribes.end())
		{
			WriteLog(LogLevel::Warning, "Repeat Subscribe for ExchangeId:%s InstrumentId:%s", reqSubMd->ExchangeId, reqSubMd->InstrumentId);
			::Deallocate(reqSubMd);
			continue;
		}
		instrumentBarPeriods[reqSubMd->InstrumentId] = *reqSubMd;
		auto& mdSubscribes = instrumentMdSubscribes[reqSubMd->InstrumentId];
		auto instrument = mdb_->Instrument->PrimaryKey->Select(reqSubMd->ExchangeId, reqSubMd->InstrumentId);
		if (instrument == nullptr)
		{
			WriteLog(LogLevel::Error, "Cannot Find Instrument While SubMarketData. ExchangeId:%s, InstrumentId:%s", reqSubMd->ExchangeId, reqSubMd->InstrumentId);
			::Deallocate(reqSubMd);
			continue;
		}
		if (instrument->InstrumentClass == InstrumentClassType::Normal)
		{
			MdSubscribe* mdSubscribe = MdSubscribe::Allocate();
			memset(mdSubscribe, 0, sizeof(MdSubscribe));
			strcpy(mdSubscribe->ExchangeId, instrument->ExchangeId);
			strcpy(mdSubscribe->InstrumentId, instrument->InstrumentId);
			strcpy(mdSubscribe->RealInstrumentId, instrument->InstrumentId);
			strcpy(mdSubscribe->ProductId, instrument->ProductId);
			mdSubscribe->ProductClass = instrument->ProductClass;
			strcpy(mdSubscribe->StartTradingDay, startTradingDay_);
			strcpy(mdSubscribe->EndTradingDay, endTradingDay_);
			
			mdSubscribes.push_back(mdSubscribe);
		}
		else
		{
			auto startIt = mdb_->HotInstrument->TradingDayIndex->LowerBound(instrument->ExchangeId, instrument->ProductId, instrument->Rank, startTradingDay_);
			auto endIt = mdb_->HotInstrument->TradingDayIndex->UpperBound(instrument->ExchangeId, instrument->ProductId, instrument->Rank, endTradingDay_);
			if (startIt == endIt)
			{
				WriteLog(LogLevel::Warning, "Cannot Find HotInstrument While SubMarketData. ExchangeId:%s, ProductId:%s, Rank:%d, StartTradingDay:%s, EndTradingDay:%s",
					instrument->ExchangeId, instrument->ProductId, instrument->Rank, startTradingDay_, endTradingDay_);
				continue;
			}
			MdSubscribe* mdSubscribe = MdSubscribe::Allocate();
			memset(mdSubscribe, 0, sizeof(MdSubscribe));
			strcpy(mdSubscribe->ExchangeId, instrument->ExchangeId);
			strcpy(mdSubscribe->InstrumentId, instrument->InstrumentId);
			strcpy(mdSubscribe->RealInstrumentId, (*startIt)->InstrumentId);
			strcpy(mdSubscribe->ProductId, instrument->ProductId);
			mdSubscribe->ProductClass = instrument->ProductClass;
			strcpy(mdSubscribe->StartTradingDay, (*startIt)->TradingDay);
			strcpy(mdSubscribe->EndTradingDay, (*startIt)->TradingDay);
			for (auto& it = startIt; it != endIt; ++it)
			{
				auto hotInstrument = *it;
				if (strcmp(mdSubscribe->RealInstrumentId, hotInstrument->InstrumentId) == 0)
				{
					strcpy(mdSubscribe->EndTradingDay, hotInstrument->TradingDay);
				}
				else
				{
					mdSubscribes.push_back(mdSubscribe);

					mdSubscribe = MdSubscribe::Allocate();
					memset(mdSubscribe, 0, sizeof(MdSubscribe));
					strcpy(mdSubscribe->ExchangeId, instrument->ExchangeId);
					strcpy(mdSubscribe->InstrumentId, instrument->InstrumentId);
					strcpy(mdSubscribe->RealInstrumentId, hotInstrument->InstrumentId);
					strcpy(mdSubscribe->ProductId, instrument->ProductId);
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
	// 聚合器登记键取订阅的 InstrumentId（MdReader 按 mdSubscribe->InstrumentId 给 bar 打戳，PushBarMarketData 也按同一字段查表），
	// 不能用 SQL 读取用的 RealInstrumentId（热门合约滚动时二者不同，用它登记会让 find 落空、声明的周期静默失效）；
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
			if (!BindBarAggregator(mdSubscribe->ExchangeId, mdSubscribe->InstrumentId, reqSubMdIt->second.BarPreces, reqSubMdIt->second.BarPeriod))
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
			if (!mdb_->MdSubscribe->Insert(mdSubscribe))
			{
				WriteLog(LogLevel::Warning, "MdSubscribe dropped, its market data will not be read. InstrumentId:%s, Year:%d", it.first.c_str(), year);
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
	if (marketDataType_ == MarketDataTypeType::Tick)
	{
		std::list<DepthMarketData*> mdTicks;
		for (auto& it : yearMdSubscribes)
		{
			auto& mdSubscribes = it.second;
			mdReader_->ReadMdTick(mdSubscribes, mdTicks);
			mdTicks_.splice(mdTicks_.end(), mdTicks);
		}
	}
	else
	{
		std::list<BarMarketData*> mdBars;
		for (auto& it : yearMdSubscribes)
		{
			auto& mdSubscribes = it.second;
			mdReader_->ReadMdBar(mdSubscribes, mdBars);
			mdBars_.splice(mdBars_.end(), mdBars);
		}
	}
	hasSubMd_ = true;
}
void SimExchange::HandleRegisterAccount(ReqRegisterAccountPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleRegisterAccount %s", reqPackage->GetDebugString());
	auto reqRegisterAccount = reqPackage->ReqRegisterAccount;
	auto account = mdb_->Account->PrimaryKey->Select(reqRegisterAccount->AccountId);
	if (account == nullptr)
	{
		// 回测账户按需自建（同 BackTestInit 种子语义）：Balance=0，资金账目由日终结算按日滚动
		account = QuantTrading::Account::Allocate();
		memset(account, 0, sizeof(QuantTrading::Account));
		strcpy(account->AccountId, reqRegisterAccount->AccountId);
		strcpy(account->AccountName, reqRegisterAccount->AccountId);
		account->AccountType = AccountTypeType::Primary;
		account->AccountStatus = AccountStatusType::Normal;
		account->TradeGroupId = 1;
		account->RiskGroupId = 1;
		account->CommissionGroupId = 1;
		mdb_->Account->Insert(account);

		auto capital = QuantTrading::Capital::Allocate();
		memset(capital, 0, sizeof(QuantTrading::Capital));
		strcpy(capital->TradingDay, tradingDay_);
		strcpy(capital->AccountId, account->AccountId);
		capital->AccountType = AccountTypeType::Primary;
		mdb_->Capital->Insert(capital);
		WriteLog(LogLevel::Info, "Account registered, AccountId:%s, TradingDay:%s", account->AccountId, tradingDay_);
	}
	else
	{
		WriteLog(LogLevel::Info, "Account already registered, AccountId:%s", account->AccountId);
	}
	SendRspRegisterAccount(reqPackage, ErrorNone);
}
void SimExchange::HandleInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleInsertOrder %s", reqPackage->GetDebugString());
	auto reqInsertOrder = reqPackage->ReqInsertOrder;
	int errorId = ErrorNone;
	auto instrument = mdb_->Instrument->PrimaryKey->Select(reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId);
	if (instrument == nullptr)
	{
		SendRspOrderInsert(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = mdb_->Account->PrimaryKey->Select(reqInsertOrder->AccountId);
	if (account == nullptr)
	{
		SendRspOrderInsert(reqPackage, ErrorAccountNotExist);
		return;
	}
	errorId = CheckForInsertOrder(reqInsertOrder, instrument);
	SendRspOrderInsert(reqPackage, errorId);
	if (errorId != ErrorNone)
	{
		return;
	}
	
	auto order = CreateOrder(reqPackage, account, instrument, tradingDay_, currDate_, currTime_);
	mdb_->Order->Insert(order);
	orderMatch_->InsertOrder(order);
}
void SimExchange::HandleCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleCancelOrder %s", reqPackage->GetDebugString());
	int errorId = ErrorNone;
	auto order = mdb_->Order->PrimaryKey->Select(tradingDay_, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId, 
		reqPackage->ReqCancelOrder->InstrumentId, reqPackage->ReqCancelOrder->OrderId);
	if (order == nullptr)
	{
		order = mdb_->Order->ClientOrderIdUniqueKey->Select(tradingDay_, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId,
			reqPackage->ReqCancelOrder->InstrumentId, reqPackage->ReqCancelOrder->SessionId, reqPackage->ReqCancelOrder->ClientOrderId);
		if (order == nullptr)
		{
			errorId = ErrorOrderNotExist;
		}
	}
	if (order != nullptr)
	{
		errorId = CheckForCancelOrder(order);
	}
	SendRspCancelOrder(reqPackage, errorId);
	if (errorId != ErrorNone)
	{
		return;
	}
	orderMatch_->CancelOrder(order);
}

void SimExchange::InitMdInstrument()
{
	std::list<QuantTrading::Instrument*> instruments;
	mdReader_->ReadMdInstrument(instruments);
	std::map<std::string, std::list<QuantTrading::Instrument*>> productInstruments;
	for (auto instrument : instruments)
	{
		auto& productInstrument = productInstruments[instrument->ProductId];
		productInstrument.push_back(instrument);
	}
	for (auto& it : productInstruments)
	{
		if (it.second.empty())
			continue;
		auto& exchangeId = it.second.front()->ExchangeId;
		ProductIdType productId;
		strcpy(productId, it.first.c_str());
		auto product = mdb_->Product->PrimaryKey->Select(exchangeId, productId);
		if (product != nullptr)
		{
			for (auto instrument : it.second)
			{
				strcpy(instrument->ExchangeInstId, instrument->InstrumentId);
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
				InsertInstrumentOrUpdate(mdb_->Instrument, instrument);
			}
		}
		else
		{
			for (auto instrument : it.second)
			{
				strcpy(instrument->ExchangeInstId, instrument->InstrumentId);
				instrument->InstrumentClass = InstrumentClassType::Normal;
				instrument->Rank = 0;
				instrument->VolumeMultiple = 1;
				instrument->PriceTick = 0;
				instrument->MaxMarketOrderVolume = 0;
				instrument->MinMarketOrderVolume = 0;
				instrument->MaxLimitOrderVolume = 0;
				instrument->MinLimitOrderVolume = 0;
				strcpy(instrument->SessionName, "FD0900");

				InsertInstrumentOrUpdate(mdb_->Instrument, instrument);
			}
		}
	}
}
void SimExchange::InitMainInstrument()
{
	auto productPair = mdb_->Product->PrimaryKey->SelectAll();
	for (auto& it = productPair.first; it != productPair.second; ++it)
	{
		auto product = *it;
		if (product->ProductClass != ProductClassType::Future)
			continue;
		auto instrument1 = ::Allocate<QuantTrading::Instrument>();
		auto instrument2 = ::Allocate<QuantTrading::Instrument>();
		auto instrument3 = ::Allocate<QuantTrading::Instrument>();
		memset(instrument1, 0, sizeof(QuantTrading::Instrument));
		memset(instrument2, 0, sizeof(QuantTrading::Instrument));
		memset(instrument3, 0, sizeof(QuantTrading::Instrument));
		strcpy(instrument1->ExchangeId, product->ExchangeId);
		strcpy(instrument1->InstrumentId, (product->ProductId + std::string(".Hot")).c_str());
		strcpy(instrument1->ProductId, product->ProductId);
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

		strcpy(instrument2->ExchangeId, product->ExchangeId);
		strcpy(instrument2->InstrumentId, (product->ProductId + std::string(".Second")).c_str());
		strcpy(instrument2->ProductId, product->ProductId);
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

		strcpy(instrument3->ExchangeId, product->ExchangeId);
		strcpy(instrument3->InstrumentId, (product->ProductId + std::string(".Third")).c_str());
		strcpy(instrument3->ProductId, product->ProductId);
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

		mdb_->Instrument->Insert(instrument1);
		mdb_->Instrument->Insert(instrument2);
		mdb_->Instrument->Insert(instrument3);
	}
}
void SimExchange::ChangeTradingDay(const DateType& nextTradingDay)
{
	// 先闭合本日残桶：尾桶的 BarTime 属上一交易日，晚一交易日的首根 bar 才收口会把它推到次日推送
	FlushBarAggregators();
    orderMatch_->OnTradingDayChange(nextTradingDay);
	Settlement();
	Init(nextTradingDay);
}
void SimExchange::Settlement()
{
	settlement_->Settle(tradingDay_);
	SendRtnSessionEnd(tradingDay_);
}
void SimExchange::Init(const DateType& nextTradingDay)
{
	settlement_->RollToNextDay(tradingDay_, nextTradingDay);
	strcpy(tradingDay_, nextTradingDay);
	SendRtnSessionBegin(nextTradingDay);
}

PriceType SimExchange::BarSettlementPriceSource::GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail)
{
	auto it = lastMdBars_->find(positionDetail->InstrumentId);
	if (it != lastMdBars_->end() && it->second != nullptr)
	{
		return it->second->Close;
	}
	return positionDetail->PreSettlementPrice;
}

void SimExchange::SendRspRegisterAccount(ReqRegisterAccountPackage* reqPackage, int errorId)
{
	RspInfoField rspInfo;
	rspInfo.ErrorId = errorId;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorId));
	RspRegisterAccountField rspRegisterAccount;
	memset(&rspRegisterAccount, 0, sizeof(RspRegisterAccountField));
	strcpy(rspRegisterAccount.AccountId, reqPackage->ReqRegisterAccount->AccountId);
	backTestSpi_->OnRspRegisterAccount(&rspRegisterAccount, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspRegisterAccount: AccountId:%s, ErrorId:%d, ErrorMsg:%s", rspRegisterAccount.AccountId, rspInfo.ErrorId, rspInfo.ErrorMsg);
}
void SimExchange::SendRspOrderInsert(ReqInsertOrderPackage* reqPackage, int errorId)
{
	RspInfoField rspInfo;
	rspInfo.ErrorId = errorId;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorId));

	backTestSpi_->OnRspInsertOrder(reqPackage->ReqInsertOrder, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspOrderInsert: ErrorId:%d, ErrorMsg:%s", rspInfo.ErrorId, rspInfo.ErrorMsg);
}
void SimExchange::SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorId)
{
	RspInfoField rspInfo;
	rspInfo.ErrorId = errorId;
	strcpy(rspInfo.ErrorMsg, GetErrorMessage(errorId));

	backTestSpi_->OnRspCancelOrder(reqPackage->ReqCancelOrder, &rspInfo, reqPackage->Head.MsgSeqNum, true);
	WriteLog(LogLevel::Info, "SendRspCancelOrder: ErrorId:%d, ErrorMsg:%s", rspInfo.ErrorId, rspInfo.ErrorMsg);
}
void SimExchange::SendRtnOrder(QuantTrading::Order* order)
{
	auto orderField = ::Allocate<OrderField>();
	MdbToField(order, orderField);
	backTestSpi_->OnRtnOrder(orderField);
	::Deallocate(orderField);
}
void SimExchange::SendRtnTrade(QuantTrading::Trade* trade)
{
	auto tradeField = ::Allocate<TradeField>();
	MdbToField(trade, tradeField);
	backTestSpi_->OnRtnTrade(tradeField);
	::Deallocate(tradeField);
}
void SimExchange::SendRtnDepthMarketData(QuantTrading::DepthMarketData* mdTick)
{
    MdbToField(mdTick, &pushMdTick_);
	backTestSpi_->OnRtnDepthMarketData(&pushMdTick_);
}
void SimExchange::SendRtnMarketDataEnd()
{
    MarketDataEndField marketDataEnd;
    memcpy(marketDataEnd.TradingDay, tradingDay_, sizeof(DateType));
    backTestSpi_->OnRtnMarketDataEnd(&marketDataEnd);
}
void SimExchange::SendRtnSessionBegin(const DateType& tradingDay)
{
	SessionBeginField sessionBegin;
	strcpy(sessionBegin.TradingDay, tradingDay);
	backTestSpi_->OnRtnSessionBegin(&sessionBegin);
}
void SimExchange::SendRtnSessionEnd(const DateType& tradingDay)
{
	SessionEndField sessionEnd;
	strcpy(sessionEnd.TradingDay, tradingDay);
	backTestSpi_->OnRtnSessionEnd(&sessionEnd);
}
}
