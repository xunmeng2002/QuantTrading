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


namespace quanttrading::backtest
{
SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_BackTestSpi(nullptr), m_HasSubMd(false), m_IsMdEnd(false),
	m_Registry(backtestTableList),
	m_CurrDate(""), m_CurrTime("")
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
    m_Mdb->t_Order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(mdb::Trade* trade)
{
    m_Mdb->t_Trade->Insert(trade);
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
	auto oldMdTick = m_Mdb->t_DepthMarketData->m_PrimaryKey->Select(mdTick->TradingDay, mdTick->ExchangeID, mdTick->InstrumentID);
	if (oldMdTick == nullptr)
	{
		m_Mdb->t_DepthMarketData->Insert(mdTick);
	}
	else
	{
		m_Mdb->t_DepthMarketData->Update(oldMdTick, mdTick);
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
	m_OrderMatch->OnBar(mdBar);
	SendRtnBarMarketData(mdBar);
	m_Mdb->t_BarMarketData->Insert(mdBar);
	m_LastMdBars[mdBar->InstrumentID] = mdBar;
}

void SimExchange::HandleSubMarketDataFinished(ReqSubMarketDataFinishedPackage* reqPackage)
{
	std::list<ReqSubMarketDataField*> reqSubMds;
	{
		lock_guard<mutex> guard(m_QueueMutex);
		reqSubMds.swap(m_ReqSubMds);
	}
	map<std::string, list<MdSubscribe*>> instrumentMdSubscribes;
	for (auto reqSubMd : reqSubMds)
	{
		if (instrumentMdSubscribes.find(reqSubMd->InstrumentID) != instrumentMdSubscribes.end())
		{
			WriteLog(LogLevel::Warning, "Repeat Subscribe for ExchangeID:%s InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
			::Deallocate(reqSubMd);
			continue;
		}
		auto& mdSubscribes = instrumentMdSubscribes[reqSubMd->InstrumentID];
		auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqSubMd->ExchangeID, reqSubMd->InstrumentID);
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
			auto startIt = m_Mdb->t_HotInstrument->m_TradingDayIndex->LowerBound(instrument->ExchangeID, instrument->ProductID, instrument->Rank, m_StartTradingDay);
			auto endIt = m_Mdb->t_HotInstrument->m_TradingDayIndex->UpperBound(instrument->ExchangeID, instrument->ProductID, instrument->Rank, m_EndTradingDay);
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
	map<int, list<MdSubscribe*>> yearMdSubscribes;
	for (auto& it : instrumentMdSubscribes)
	{
		for (auto mdSubscribe : it.second)
		{
			int year = int(atoi(mdSubscribe->StartTradingDay) / 10000);
			auto& mdSubscribes = yearMdSubscribes[year];
			mdSubscribes.push_back(mdSubscribe);
			m_Mdb->t_MdSubscribe->Insert(mdSubscribe);
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
	auto account = m_Mdb->t_Account->m_PrimaryKey->Select(reqRegisterAccount->AccountID);
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
		m_Mdb->t_Account->Insert(account);

		auto capital = mdb::Capital::Allocate();
		memset(capital, 0, sizeof(mdb::Capital));
		strcpy(capital->TradingDay, m_TradingDay);
		strcpy(capital->AccountID, account->AccountID);
		capital->AccountType = AccountTypeType::Primary;
		m_Mdb->t_Capital->Insert(capital);
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
	auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		SendRspOrderInsert(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = m_Mdb->t_Account->m_PrimaryKey->Select(reqInsertOrder->AccountID);
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
	m_Mdb->t_Order->Insert(order);
	m_OrderMatch->InsertOrder(order);
}
void SimExchange::HandleCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleCancelOrder %s", reqPackage->GetDebugString());
	int errorID = ErrorNone;
	auto order = m_Mdb->t_Order->m_PrimaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID, 
		reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->OrderID);
	if (order == nullptr)
	{
		order = m_Mdb->t_Order->m_ClientOrderIDUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
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
		auto product = m_Mdb->t_Product->m_PrimaryKey->Select(exchangeID, productID);
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
				if (!m_Mdb->t_Instrument->Insert(instrument))
				{
					auto oldInstrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(instrument->ExchangeID, instrument->InstrumentID);
					m_Mdb->t_Instrument->Update(oldInstrument, instrument);
				}
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

				if (!m_Mdb->t_Instrument->Insert(instrument))
				{
					auto oldInstrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(instrument->ExchangeID, instrument->InstrumentID);
					m_Mdb->t_Instrument->Update(oldInstrument, instrument);
				}
			}
		}
	}
}
void SimExchange::InitMainInstrument()
{
	auto productPair = m_Mdb->t_Product->m_PrimaryKey->SelectAll();
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

		m_Mdb->t_Instrument->Insert(instrument1);
		m_Mdb->t_Instrument->Insert(instrument2);
		m_Mdb->t_Instrument->Insert(instrument3);
	}
}
void SimExchange::ChangeTradingDay(const DateType& nextTradingDay)
{
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
void SimExchange::SendRtnBarMarketData(mdb::BarMarketData* mdBar)
{
    MdbToField(mdBar, &m_PushMdBar);
	m_BackTestSpi->OnRtnBarMarketData(&m_PushMdBar);
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
