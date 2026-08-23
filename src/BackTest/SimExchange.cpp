#include "SimExchange.h"
#include "MdbTableRegistry.h"
#include "BackTestTableList.h"
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>
#include "Error.h"
#include "QuantUtility.h"
#include "OrderUtility.h"
#include "InitMdbFromCsv.h"
#include "InitMdbFromDB.h"
#include "MdbFieldConverter.h"
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
#include <assert.h>
#include <cmath>

using namespace std;
using namespace mdb;
using namespace spark;
using namespace spark::core;
using namespace quanttrading;
using namespace quanttrading::ordermatch;

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


namespace quanttrading::backtest
{
SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_BackTestSpi(nullptr), m_HasSubMd(false), m_IsMdEnd(false), m_DumpPath(config.DumpPath),
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
	m_InitDB = CreateDataDb(config.DbType, config.DbInitHost, config.DbUser, config.DbPassword);
	m_DB = CreateDataDb(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
    m_DBWriter = new AsyncDBWriter(m_DB, &m_Registry);
	m_DBWriter->Subscribe(this);
	m_Mdb = new Mdb(backtestTableList);
	m_OrderMatch = OrderMatch::CreateOrderMatch(matchMode, m_TradingDay);
	m_OrderMatch->Subscribe(this);
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
	if (m_InitDB == nullptr || m_DB == nullptr)
	{
		WriteLog(LogLevel::Error, "Create DB Failed.");
		return false;
	}
	if (!m_InitDB->Connect())
	{
		WriteLog(LogLevel::Error, "InitDB Connect Failed.");
		return false;
	}
	InitMdbFromDB::LoadTables(m_Mdb, m_InitDB, backtestTableList);
	m_Mdb->Subscribe(m_DBWriter);

	m_MdReader->Init();
	InitMdInstrument();
	InitMainInstrument();
	auto capitalPair = m_Mdb->t_Capital->m_PrimaryKey->SelectAll();
	for (auto& it = capitalPair.first; it != capitalPair.second; ++it)
	{
		auto capital = *it;
		strcpy(capital->TradingDay, m_TradingDay);
	}
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

	auto posiDirection = GetPosiDirection(trade->OffsetFlag, trade->Direction);
	auto position = m_Mdb->t_Position->m_PrimaryKey->Select(trade->TradingDay, trade->AccountID, trade->ExchangeID, trade->InstrumentID, posiDirection);
	if (position == nullptr)
	{
		position = ::CreatePosition(trade, posiDirection);
		m_Mdb->t_Position->Insert(position);
	}
	else
	{
		if (trade->OffsetFlag == OffsetFlagType::Open)
		{
			position->TotalPosition += trade->Volume;
		}
		else
		{
			if (position->TotalPosition < trade->Volume)
			{
				WriteLog(LogLevel::Warning, "Position not Enough For Close Trade. Position:%s, Trade:%s", position->GetDebugString(), trade->GetDebugString());
			}
			position->TotalPosition -= trade->Volume;
		}
	}

	auto tradeAmount = trade->Price * trade->Volume * trade->VolumeMultiple;
	if (trade->OffsetFlag == OffsetFlagType::Open)
	{
		auto positionDetail = ::CreatePositionDetail(trade, posiDirection);
		m_Mdb->t_PositionDetail->Insert(positionDetail);
	}
	else
	{
		std::set<mdb::PositionDetail*, PositionDetialLessForOpenDate> positionDetails;
		auto itPair = m_Mdb->t_PositionDetail->m_TradeMatchIndex->EqualRange(position->TradingDay, position->AccountID, position->ExchangeID, 
			position->InstrumentID, position->PosiDirection);
		for (auto& it = itPair.first; it != itPair.second; ++it)
		{
			positionDetails.insert(*it);
		}
		auto flag = position->PosiDirection == PosiDirectionType::Long ? 1 : -1;
		auto remainVolume = trade->Volume;
		for (auto positionDetail : positionDetails)
		{
			auto currVolume = std::min(remainVolume, positionDetail->Volume - positionDetail->CloseVolume);
			if (currVolume <= 0)
			{
				continue;
			}
			auto closeAmount = trade->Price * currVolume * position->VolumeMultiple;
			positionDetail->CloseVolume += currVolume;
			positionDetail->CloseAmount += closeAmount;
			positionDetail->CloseProfitByTrade += flag * (trade->Price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
			if (strcmp(positionDetail->OpenDate, positionDetail->TradingDay) == 0)
			{
				positionDetail->CloseProfitByDate += flag * (trade->Price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
			}
			else
			{
				positionDetail->CloseProfitByDate += flag * (trade->Price - positionDetail->PreSettlementPrice) * currVolume * positionDetail->VolumeMultiple;
			}
			if (position->ProductClass == ProductClassType::FutureOption || position->ProductClass == ProductClassType::StockOption 
				|| position->ProductClass == ProductClassType::Stock || position->ProductClass == ProductClassType::ETF)
			{
				positionDetail->CashIn += trade->Direction == DirectionType::Sell ? closeAmount : 0.0;
				positionDetail->CashOut += trade->Direction == DirectionType::Buy ? closeAmount : 0.0;
			}
			remainVolume -= currVolume;
			if (remainVolume <= 0)
				break;
		}
	}
}


void SimExchange::RegisterSpi(BackTestSpi* pSpi)
{
	m_BackTestSpi = pSpi;
}
int SimExchange::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataField* reqSubMd = ::Allocate<ReqSubMarketDataField>();
	memcpy(reqSubMd, reqSubMarketData, sizeof(ReqSubMarketDataField));
	m_ReqSubMds.push_back(reqSubMd);
	return 0;
}
int SimExchange::ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID)
{
	ReqSubMarketDataFinishedPackage* reqPackage = ReqSubMarketDataFinishedPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqSubMarketDataFinished = ::Allocate<ReqSubMarketDataFinishedField>();
	memcpy(reqPackage->ReqSubMarketDataFinished, reqSubMarketDataFinished, sizeof(ReqSubMarketDataFinishedField));

	m_Packages.push_back(reqPackage);
	return 0;
}
int SimExchange::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));

	m_Packages.push_back(reqPackage);
	return 0;
}
int SimExchange::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(0LL, false, requestID);
	reqPackage->ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));

	m_Packages.push_back(reqPackage);
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
	while (!m_Packages.empty())
	{
		auto package = m_Packages.front();
		m_Packages.pop_front();
		switch (package->Head.PackageID)
		{
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
	map<std::string, list<MdSubscribe*>> instrumentMdSubscribes;
	for (auto reqSubMd : m_ReqSubMds)
	{
		if (instrumentMdSubscribes.find(reqSubMd->InstrumentID) != instrumentMdSubscribes.end())
		{
			WriteLog(LogLevel::Warning, "Repeat Subscribe for ExchangeID:%s InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
			continue;
		}
		auto& mdSubscribes = instrumentMdSubscribes[reqSubMd->InstrumentID];
		auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqSubMd->ExchangeID, reqSubMd->InstrumentID);
		if (instrument == nullptr)
		{
			WriteLog(LogLevel::Error, "Cannot Find Instrument While SubMarketData. ExchangeID:%s, InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
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
	m_ReqSubMds.clear();
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
				auto newMdSubscribe = new MdSubscribe();
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
	map<int, list<MdSubscribe*>*> yearMdSubscribes;
	for (auto& it : instrumentMdSubscribes)
	{
		for (auto mdSubscribe : it.second)
		{
			int year = int(atoi(mdSubscribe->StartTradingDay) / 10000);
			auto& mdSubscribes = yearMdSubscribes[year];
			if (mdSubscribes == nullptr)
			{
				mdSubscribes = new list<MdSubscribe*>();
			}
			mdSubscribes->push_back(mdSubscribe);
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
			auto mdSubscribes = it.second;
			m_MdReader->ReadMdTick(*mdSubscribes, mdTicks);
			m_MdTicks.splice(m_MdTicks.end(), mdTicks);
		}
	}
	else
	{
		std::list<BarMarketData*> mdBars;
		for (auto& it : yearMdSubscribes)
		{
			auto mdSubscribes = it.second;
			m_MdReader->ReadMdBar(*mdSubscribes, mdBars);
			m_MdBars.splice(m_MdBars.end(), mdBars);
		}
	}
	m_HasSubMd = true;
}
void SimExchange::HandleInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleInsertOrder %s", reqPackage->GetDebugString());
	auto reqInsertOrder = reqPackage->ReqInsertOrder;
	int errorID = ErrorNone;
	auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		errorID = ErrorInstrumentNotExist;
	}
	else
	{
		errorID = CheckForInsertOrder(reqInsertOrder, instrument);
	}
	auto account = m_Mdb->t_Account->m_PrimaryKey->Select(reqInsertOrder->AccountID);
	if (account == nullptr)
	{
		errorID = ErrorAccountNotExist;
	}
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
			reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->SessionID, reqPackage->ReqCancelOrder->ClientCancelOrderID);
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
	Settlement();
	Init(nextTradingDay);
}
void SimExchange::Settlement()
{
	SettlementAccount();
	SendRtnSessionEnd(m_TradingDay);
}
void SimExchange::SettlementAccount()
{
	SettlementPosition();
	std::vector<mdb::Capital*> capitals;
	auto capitalItPair = m_Mdb->t_Capital->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& capitalIt = capitalItPair.first; capitalIt != capitalItPair.second; ++capitalIt)
	{
		capitals.push_back(*capitalIt);
	}
	for (auto capital : capitals)
	{
		capital->MarketValue = 0;
		capital->CashIn = 0;
		capital->CashOut = 0;
		capital->Margin = 0;
		capital->Commission = 0;
		capital->CloseProfitByDate = 0;
		capital->CloseProfitByTrade = 0;
		capital->PositionProfitByDate = 0;
		capital->PositionProfitByTrade = 0;
		auto positionItPair = m_Mdb->t_Position->m_AccountIndex->EqualRange(capital->TradingDay, capital->AccountID);
		for (auto& positionIt = positionItPair.first; positionIt != positionItPair.second; ++positionIt)
		{
			auto position = *positionIt;
			capital->MarketValue += position->MarketValue;
			capital->CashIn += position->CashIn;
			capital->CashOut += position->CashOut;
			capital->Margin += position->Margin;
			capital->Commission += position->Commission;
			capital->CloseProfitByDate += position->CloseProfitByDate;
			capital->CloseProfitByTrade += position->CloseProfitByTrade;
			capital->PositionProfitByDate += position->PositionProfitByDate;
			capital->PositionProfitByTrade += position->PositionProfitByTrade;
		}
		CalcCapital(capital);
	}
}
void SimExchange::SettlementPosition()
{
	SettlementPositionDetail();
	std::vector<mdb::Position*> positions;
	auto positionItPair = m_Mdb->t_Position->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& positionIt = positionItPair.first; positionIt != positionItPair.second; ++positionIt)
	{
		positions.push_back(*positionIt);
	}
	for (auto position : positions)
	{
		position->PositionFrozen = 0;
		position->MarketValue = 0;
		position->CashIn = 0;
		position->CashOut = 0;
		position->Margin = 0;
		position->Commission = 0;
		position->CloseProfitByDate = 0;
		position->CloseProfitByTrade = 0;
		position->PositionProfitByDate = 0;
		position->PositionProfitByTrade = 0;

		auto positionDetailItPair = m_Mdb->t_PositionDetail->m_TradeMatchIndex->EqualRange(m_TradingDay, position->AccountID, position->ExchangeID, position->InstrumentID, position->PosiDirection);
		for (auto& positionDetailIt = positionDetailItPair.first; positionDetailIt != positionDetailItPair.second; ++positionDetailIt)
		{
			auto positionDetail = *positionDetailIt;
			position->MarketValue += positionDetail->MarketValue;
			position->CashIn += positionDetail->CashIn;
			position->CashOut += positionDetail->CashOut;
			position->Margin += positionDetail->Margin;
			position->Commission += positionDetail->Commission;
			position->CloseProfitByDate += positionDetail->CloseProfitByDate;
			position->CloseProfitByTrade += positionDetail->CloseProfitByTrade;
			position->PositionProfitByDate += positionDetail->PositionProfitByDate;
			position->PositionProfitByTrade += positionDetail->PositionProfitByTrade;
			position->SettlementPrice = positionDetail->SettlementPrice;
		}
	}
}
void SimExchange::SettlementPositionDetail()
{
	std::vector<mdb::PositionDetail*> positionDetails;
	auto positionDetailItPair = m_Mdb->t_PositionDetail->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& positionDetailIt = positionDetailItPair.first; positionDetailIt != positionDetailItPair.second; ++positionDetailIt)
	{
		positionDetails.push_back(*positionDetailIt);
	}
	for (auto positionDetail : positionDetails)
	{
		auto flag = positionDetail->PosiDirection == PosiDirectionType::Long ? 1 : -1;
		positionDetail->SettlementPrice = GetSettlementPrice(positionDetail);
		if (strcmp(positionDetail->OpenDate, m_TradingDay) == 0)
		{
			positionDetail->PositionProfitByDate = flag * (positionDetail->SettlementPrice - positionDetail->OpenPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
		}
		else
		{
			positionDetail->PositionProfitByDate = flag * (positionDetail->SettlementPrice - positionDetail->PreSettlementPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
		}
		positionDetail->PositionProfitByTrade = flag * (positionDetail->SettlementPrice - positionDetail->OpenPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
		if (positionDetail->ProductClass == ProductClassType::FutureOption || positionDetail->ProductClass == ProductClassType::StockOption)
		{
			positionDetail->MarketValue = flag * positionDetail->SettlementPrice * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
		}
	}
}
void SimExchange::Init(const DateType& nextTradingDay)
{
	InitAccount(nextTradingDay);
	strcpy(m_TradingDay, nextTradingDay);
	SendRtnSessionBegin(nextTradingDay);
}
void SimExchange::InitAccount(const DateType& nextTradingDay)
{
	InitPosition(nextTradingDay);
	std::vector<mdb::Capital*> capitals;
	auto capitalItPair = m_Mdb->t_Capital->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& capitalIt = capitalItPair.first; capitalIt != capitalItPair.second; ++capitalIt)
	{
		capitals.push_back(*capitalIt);
	}
	for (auto capital : capitals)
	{
		auto newCapital = new mdb::Capital();
		memcpy(newCapital, capital, sizeof(mdb::Capital));
		strcpy(newCapital->TradingDay, nextTradingDay);
		newCapital->PreBalance = capital->Balance;
		newCapital->MarketValue = 0.0;
		newCapital->CashIn = 0.0;
		newCapital->CashOut = 0.0;
		newCapital->Commission = 0.0;
		newCapital->FrozenCash = 0.0;
		newCapital->FrozenMargin = 0.0;
		newCapital->FrozenCommission = 0.0;
		newCapital->CloseProfitByDate = 0.0;
		newCapital->CloseProfitByDate = 0.0;
		newCapital->PositionProfitByDate = 0.0;
		
		m_Mdb->t_Capital->Insert(newCapital);
	}
}
void SimExchange::InitPosition(const DateType& nextTradingDay)
{
	InitPositionDetail(nextTradingDay);
	std::vector<mdb::Position*> positions;
	auto positionItPair = m_Mdb->t_Position->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& positionIt = positionItPair.first; positionIt != positionItPair.second; ++positionIt)
	{
		positions.push_back(*positionIt);
	}
	for (auto position : positions)
	{
		if (position->TotalPosition == 0)
			continue;
		auto newPosition = new mdb::Position();
		memcpy(newPosition, position, sizeof(mdb::Position));
		strcpy(newPosition->TradingDay, nextTradingDay);
		newPosition->PositionFrozen = 0;
		newPosition->TodayPosition = 0;
		newPosition->CashIn = 0;
		newPosition->CashOut = 0;
		newPosition->Commission = 0.0;
		newPosition->FrozenCash = 0;
		newPosition->FrozenMargin = 0;
		newPosition->FrozenCommission = 0;
		newPosition->CloseProfitByDate = 0.0;
		newPosition->CloseProfitByTrade = 0.0;
		newPosition->PositionProfitByDate = 0.0;
		newPosition->PreSettlementPrice = position->SettlementPrice;
		m_Mdb->t_Position->Insert(newPosition);
	}
}
void SimExchange::InitPositionDetail(const DateType& nextTradingDay)
{
	std::vector<mdb::PositionDetail*> positionDetails;
	auto positionDetailItPair = m_Mdb->t_PositionDetail->m_TradingDayIndex->EqualRange(m_TradingDay);
	for (auto& positionDetailIt = positionDetailItPair.first; positionDetailIt != positionDetailItPair.second; ++positionDetailIt)
	{
		positionDetails.push_back(*positionDetailIt);
	}
	for (auto positionDetail : positionDetails)
	{
		if (positionDetail->Volume - positionDetail->CloseVolume == 0)
			continue;
		auto newPositionDetail = new mdb::PositionDetail();
		memcpy(newPositionDetail, positionDetail, sizeof(mdb::PositionDetail));
		strcpy(newPositionDetail->TradingDay, nextTradingDay);
		newPositionDetail->CashIn = 0;
		newPositionDetail->CashOut = 0;
		newPositionDetail->Commission = 0;
		newPositionDetail->CloseProfitByDate = 0.0;
		newPositionDetail->CloseProfitByTrade = 0.0;
		newPositionDetail->PositionProfitByDate = 0.0;
		newPositionDetail->PreSettlementPrice = positionDetail->SettlementPrice;
		m_Mdb->t_PositionDetail->Insert(newPositionDetail);
	}
}



PriceType SimExchange::GetSettlementPrice(mdb::PositionDetail* positionDetail)
{
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		auto mdTick = m_Mdb->t_DepthMarketData->m_PrimaryKey->Select(positionDetail->TradingDay, positionDetail->ExchangeID, positionDetail->InstrumentID);
		if (mdTick == nullptr)
		{
			return positionDetail->PreSettlementPrice;
		}
		else if (!isinf(mdTick->LastPrice) && !isnan(mdTick->LastPrice))
		{
			return mdTick->LastPrice;
		}
		else if (!isinf(mdTick->PreSettlementPrice) && !isnan(mdTick->PreSettlementPrice))
		{
			return mdTick->PreSettlementPrice;
		}
	}
	else
	{
		auto mdBar = m_LastMdBars[positionDetail->InstrumentID];
		if (mdBar != nullptr)
		{
			return mdBar->Close;
		}
	}
	return positionDetail->PreSettlementPrice;
}
void SimExchange::CalcCapital(mdb::Capital* capital)
{
	capital->Balance = capital->PreBalance + capital->CloseProfitByDate + capital->PositionProfitByDate  - capital->Commission;
	capital->Available = capital->Balance - capital->MarketValue - capital->Margin - capital->FrozenCash - capital->FrozenMargin - capital->FrozenCommission;
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
	memset(orderField, 0, sizeof(OrderField));
	strcpy(orderField->TradingDay, order->TradingDay);
	strcpy(orderField->AccountID, order->AccountID);
	strcpy(orderField->ExchangeID, order->ExchangeID);
	strcpy(orderField->InstrumentID, order->InstrumentID);
	orderField->ProductClass = order->ProductClass;
	orderField->OrderID = order->OrderID;
	strcpy(orderField->OrderSysID, order->OrderSysID);
	orderField->Direction = order->Direction;
	orderField->OffsetFlag = order->OffsetFlag;
	orderField->OrderPriceType = order->OrderPriceType;
	orderField->Price = order->Price;
	orderField->Volume = order->Volume;
	orderField->VolumeTotal = order->VolumeTotal;
	orderField->VolumeTraded = order->VolumeTraded;
	orderField->VolumeMultiple = order->VolumeMultiple;
	orderField->OrderStatus = order->OrderStatus;
	strcpy(orderField->OrderDate, order->OrderDate);
	strcpy(orderField->OrderTime, order->OrderTime);
	strcpy(orderField->CancelDate, order->CancelDate);
	strcpy(orderField->CancelTime, order->CancelTime);
	orderField->SessionID = order->SessionID;
	orderField->ClientOrderID = order->ClientOrderID;
	orderField->RequestID = order->RequestID;
	orderField->FrozenCash = order->FrozenCash;
	orderField->FrozenMargin = order->FrozenMargin;
	orderField->FrozenCommission = order->FrozenCommission;
	m_BackTestSpi->OnRtnOrder(orderField);
	::Deallocate(orderField);
}
void SimExchange::SendRtnTrade(mdb::Trade* trade)
{
	auto tradeField = ::Allocate<TradeField>();
	memset(tradeField, 0, sizeof(TradeField));
	strcpy(tradeField->TradingDay, trade->TradingDay);
	strcpy(tradeField->AccountID, trade->AccountID);
	strcpy(tradeField->ExchangeID, trade->ExchangeID);
	strcpy(tradeField->InstrumentID, trade->InstrumentID);
	tradeField->ProductClass = trade->ProductClass;
	tradeField->OrderID = trade->OrderID;
	strcpy(tradeField->OrderSysID, trade->OrderSysID);
	strcpy(tradeField->TradeID, trade->TradeID);
	tradeField->Direction = trade->Direction;
	tradeField->OffsetFlag = trade->OffsetFlag;
	tradeField->Price = trade->Price;
	tradeField->Volume = trade->Volume;
	tradeField->VolumeMultiple = trade->VolumeMultiple;
	tradeField->TradeAmount = trade->TradeAmount;
	tradeField->Commission = trade->Commission;
	strcpy(tradeField->TradeDate, trade->TradeDate);
	strcpy(tradeField->TradeTime, trade->TradeTime);
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
