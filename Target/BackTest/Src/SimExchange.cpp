#include "SimExchange.h"
#include "MemCacheTemplateSingleton.h"
#include "Error.h"
#include "QuantUtility.h"
#include "Logger.h"
#include "InitMdbFromCsv.h"
#include <assert.h>

using namespace std;
using namespace mdb;

SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_BackTestSpi(nullptr), m_HasSubMd(false), m_MaxOrderID(0), m_MaxTradeID(0), m_DumpPath(config.DumpPath)
{
	strcpy(m_TradingDay, config.StartTradingDay.c_str());
	strcpy(m_StartTradingDay, config.StartTradingDay.c_str());
	strcpy(m_EndTradingDay, config.EndTradingDay.c_str());
	m_MarketDataType = MarketDataTypeType(config.MarketDataType[0]);
	memset(&m_PushMdTick, 0, sizeof(DepthMarketDataField));
	memset(&m_PushMdBar, 0, sizeof(BarMarketDataField));
	m_MdReader = new MdReader(config);
	m_Mdb = new Mdb();
	InitMdbFromCsv::LoadTables(m_Mdb, config.CsvPath.c_str());
}
SimExchange::~SimExchange()
{
	delete m_MdReader;
	m_MdReader = nullptr;
	delete m_Mdb;
	m_Mdb = nullptr;
}
void SimExchange::Init()
{
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
}
void SimExchange::RegisterSpi(BackTestSpi* pSpi)
{
	m_BackTestSpi = pSpi;
}
int SimExchange::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataField* reqSubMd = new ReqSubMarketDataField();
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
	UpdateOrderQueue();
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
		package->Free();
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
void SimExchange::UpdateOrderQueue()
{
	for (auto& it : m_InstrumentsHasMatched)
	{
		if (it.second)
		{
			UpdateAllQueueOrder(it.first);
			it.second = false;
		}
	}
}
void SimExchange::OnMdEnd()
{
	WriteLog(LogLevel::Info, "OnMdEnd");
	Settlement();
	m_Mdb->Dump(m_DumpPath.c_str());
	WriteLog(LogLevel::Info, "Dump Completed\n");
	m_ShouldRun = false;
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
	UpdateLastMdTick(mdTick);

	auto& marketBuyQueueOrders = m_MarketBuyOrders[mdTick->InstrumentID];
	for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
	{
		CheckMatchForMdTick(marketBuyQueueOrder, mdTick);
	}
	auto& marketSellQueueOrders = m_MarketSellOrders[mdTick->InstrumentID];
	for (auto& marketSellQueueOrder : marketSellQueueOrders)
	{
		CheckMatchForMdTick(marketSellQueueOrder, mdTick);
	}
	UpdateMarketOrderAfterMd(mdTick->InstrumentID);

	auto& buyQueueOrders = m_BuyOrders[mdTick->InstrumentID];
	for (auto& buyQueueOrder : buyQueueOrders)
	{
		CheckMatchForMdTick(buyQueueOrder, mdTick);
	}
	auto& sellQueueOrders = m_SellOrders[mdTick->InstrumentID];
	for (auto& sellQueueOrder : sellQueueOrders)
	{
		CheckMatchForMdTick(sellQueueOrder, mdTick);
	}

	SendRtnDepthMarketData(mdTick);
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
	UpdateLastMdBar(mdBar);

	auto& marketBuyQueueOrders = m_MarketBuyOrders[mdBar->InstrumentID];
	for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
	{
		CheckMatchForMdBar(marketBuyQueueOrder, mdBar);
	}
	auto& marketSellQueueOrders = m_MarketSellOrders[mdBar->InstrumentID];
	for (auto& marketSellQueueOrder : marketSellQueueOrders)
	{
		CheckMatchForMdBar(marketSellQueueOrder, mdBar);
	}
	UpdateMarketOrderAfterMd(mdBar->InstrumentID);

	auto& buyQueueOrders = m_BuyOrders[mdBar->InstrumentID];
	for (auto& buyQueueOrder : buyQueueOrders)
	{
		CheckMatchForMdBar(buyQueueOrder, mdBar);
	}
	auto& sellQueueOrders = m_SellOrders[mdBar->InstrumentID];
	for (auto& sellQueueOrder : sellQueueOrders)
	{
		CheckMatchForMdBar(sellQueueOrder, mdBar);
	}

	SendRtnBarMarketData(mdBar);
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
		::Free(reqSubMd);
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
	auto reqInsertOrder = reqPackage->ReqInsertOrder;
	int errorID = ErrorNone;
	auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		errorID = ErrorInstrumentNotExist;
	}
	DepthMarketData* mdTick = nullptr;
	BarMarketData* mdBar = nullptr;
	Int64Type updatTs = 0LL;
	PriceType preSettlementPrice = 0.0;
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		mdTick = m_LastMdTicks[reqInsertOrder->InstrumentID];
		if (mdTick != nullptr)
		{
			updatTs = mdTick->UpdateTs;
			preSettlementPrice = mdTick->PreSettlementPrice != std::numeric_limits<double>::infinity() ? mdTick->PreSettlementPrice : mdTick->PreClosePrice;
		}
	}
	else
	{
		mdBar = m_LastMdBars[reqInsertOrder->InstrumentID];
		if (mdBar != nullptr)
		{
			updatTs = mdBar->UpdateTs;
			preSettlementPrice = mdBar->PreSettlementPrice != std::numeric_limits<double>::infinity() ? mdBar->PreSettlementPrice : mdBar->PreClosePrice;
		}
	}
	auto account = m_Mdb->t_Account->m_PrimaryKey->Select(reqInsertOrder->AccountID);
	if (account == nullptr)
	{
		errorID = ErrorAccountNotExist;
	}
	mdb::Position* position = nullptr;
	if (errorID == ErrorNone)
	{
		position = GetPosition(reqInsertOrder, account, instrument, preSettlementPrice);
		errorID = CheckForInputOrder(reqInsertOrder, position);
	}
	SendRspOrderInsert(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	Order* order = InitOrder(reqPackage, account, position, (updatTs / 1000) % 1000000LL);
	CheckMatchForOrderQueue(order);
	if (order->VolumeTotal > 0)
	{
		AddOrderToQueue(order);
	}
	if (order->VolumeTraded == 0)
	{
		SendRtnOrder(order);
	}
}
void SimExchange::HandleCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	int errorID = ErrorNone;
	auto order = m_Mdb->t_Order->m_PrimaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID, reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->OrderID);
	if (order == nullptr)
	{
		order = m_Mdb->t_Order->m_ClientOrderIDUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID, reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->SessionID, reqPackage->ReqCancelOrder->ClientCancelOrderID);
		if (order == nullptr)
		{
			errorID = ErrorOrderNotExist;
		}
	}
	if (errorID == ErrorNone)
	{
		errorID = CheckForCancelOrder(order);
	}
	SendRspCancelOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	if (order->Direction == DirectionType::Buy)
	{
		m_BuyOrders[order->InstrumentID].erase(order);
	}
	else
	{
		m_SellOrders[order->InstrumentID].erase(order);
	}
	if (order->OffsetFlag != OffsetFlagType::Open)
	{
		auto position = GetPosition(order);
		position->PositionFrozen -= order->VolumeTotal;
	}
	order->VolumeTotal = 0;
	order->OrderStatus = order->VolumeTraded > 0 ? OrderStatusType::PartTradedCanceled : OrderStatusType::Canceled;
	SendRtnOrder(order);
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
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		for (auto& it : m_LastMdTicks)
		{
			if (it.second != nullptr)
			{
				m_Mdb->t_DepthMarketData->Insert(it.second);
			}
		}
	}
	else
	{
		for (auto& it : m_LastMdBars)
		{
			if (it.second != nullptr)
			{
				m_Mdb->t_BarMarketData->Insert(it.second);
			}
		}
	}
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
	m_InstrumentsHasMatched.clear();
	for (auto& buyOrders : m_BuyOrders)
	{
		buyOrders.second.clear();
	}
	m_BuyOrders.clear();
	for (auto& sellOrders : m_SellOrders)
	{
		sellOrders.second.clear();
	}
	m_SellOrders.clear();
	m_MaxOrderID = 0;
	m_MaxTradeID = 0;
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

void SimExchange::UpdateLastMdTick(mdb::DepthMarketData* mdTick)
{
	auto lastTick = m_LastMdTicks[mdTick->InstrumentID];
	if (lastTick != nullptr)
	{
		::Free(lastTick);
	}
	m_LastMdTicks[mdTick->InstrumentID] = mdTick;
}
void SimExchange::UpdateLastMdBar(mdb::BarMarketData* mdBar)
{
	auto lastBar = m_LastMdBars[mdBar->InstrumentID];
	if (lastBar != nullptr)
	{
		::Free(lastBar);
	}
	m_LastMdBars[mdBar->InstrumentID] = mdBar;
}

mdb::Position* SimExchange::InitPosition(ReqInsertOrderField* reqInsertOrder, mdb::Account* account, mdb::Instrument* instrument, const PosiDirectionType& posiDirection, const PriceType& preSettlementPrice)
{
	auto position = mdb::Position::Allocate();
	memset(position, 0, sizeof(Position));
	strcpy(position->TradingDay, m_TradingDay);
	strcpy(position->AccountID, reqInsertOrder->AccountID);
	position->AccountType = account->AccountType;
	strcpy(position->ExchangeID, reqInsertOrder->ExchangeID);
	strcpy(position->InstrumentID, reqInsertOrder->InstrumentID);
	position->ProductClass = instrument->ProductClass;
	position->PosiDirection = posiDirection;
	position->VolumeMultiple = instrument->VolumeMultiple;
	position->PreSettlementPrice = preSettlementPrice;
	m_Mdb->t_Position->Insert(position);
	return position;
}
mdb::Position* SimExchange::GetPosition(ReqInsertOrderField* reqInsertOrder, mdb::Account* account, mdb::Instrument* instrument, const PriceType& preSettlementPrice)
{
	auto posiDirection = GetPosiDirection(reqInsertOrder->OffsetFlag, reqInsertOrder->Direction);
	auto position = m_Mdb->t_Position->m_PrimaryKey->Select(m_TradingDay, reqInsertOrder->AccountID, reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID, posiDirection);
	if (position == nullptr)
	{
		position = InitPosition(reqInsertOrder, account, instrument, posiDirection, preSettlementPrice);
	}
	return position;
}
mdb::Position* SimExchange::GetPosition(mdb::Order* order)
{
	auto posiDirection = GetPosiDirection(order->OffsetFlag, order->Direction);
	return m_Mdb->t_Position->m_PrimaryKey->Select(order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, posiDirection);
}
int SimExchange::CheckForInputOrder(ReqInsertOrderField* reqInsertOrder, mdb::Position* position)
{
	if (reqInsertOrder->OffsetFlag == OffsetFlagType::Open)
		return ErrorNone;
	if (position->TotalPosition - position->PositionFrozen < reqInsertOrder->Volume)
		return ErrorPositionInsufficient;
	return ErrorNone;
}
mdb::Order* SimExchange::InitOrder(ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::Position* postion, const Int64Type& insertTime)
{
	auto reqInsertOrder = reqPackage->ReqInsertOrder;
	Order* order = Order::Allocate();
	memset(order, 0, sizeof(Order));
	strcpy(order->TradingDay, m_TradingDay);
	strcpy(order->AccountID, account->AccountID);
	order->AccountType = account->AccountType;
	strcpy(order->ExchangeID, postion->ExchangeID);
	strcpy(order->InstrumentID, postion->InstrumentID);
	order->ProductClass = postion->ProductClass;
	order->OrderID = GetNextOrderID();
	strcpy(order->OrderSysID, to_string(order->OrderID).c_str());
	order->Direction = reqInsertOrder->Direction;
	order->OffsetFlag = reqInsertOrder->OffsetFlag;
	order->OrderPriceType = reqInsertOrder->OrderPriceType;
	order->Price = reqInsertOrder->Price;
	order->Volume = reqInsertOrder->Volume;
	order->VolumeTotal = reqInsertOrder->Volume;
	order->VolumeTraded = 0;
	order->VolumeMultiple = postion->VolumeMultiple;
	order->OrderStatus = OrderStatusType::Inserted;
	strcpy(order->OrderDate, m_TradingDay);
	strncpy(order->OrderTime, to_string(insertTime).c_str(), sizeof(TimeType));
	order->SessionID = reqPackage->SessionID;
	order->ClientOrderID = reqInsertOrder->ClientOrderID;
	order->RequestID = reqPackage->Head.MsgSeqNum;
	order->TradeGroupID = account->TradeGroupID;
	order->RiskGroupID = account->RiskGroupID;
	order->CommissionGroupID = account->CommissionGroupID;
	order->RebuildMark = false;
	order->IsForceClose = false;
	m_Mdb->t_Order->Insert(order);
	return order;
}
void SimExchange::AddOrderToQueue(mdb::Order* order)
{
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_BuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_SellOrders[order->InstrumentID].insert(order);
		}
	}
	else
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_MarketBuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_MarketSellOrders[order->InstrumentID].insert(order);
		}
	}
}
void SimExchange::UpdateMarketOrderAfterMd(const InstrumentIDType& instrumentID)
{
	auto& buyOrderQueue = m_MarketBuyOrders[instrumentID];
	for (auto order : buyOrderQueue)
	{
		if (order->VolumeTotal > 0)
		{
			order->VolumeTotal = 0;
			if (order->VolumeTraded > 0)
			{
				order->OrderStatus = OrderStatusType::PartTradedCanceled;
			}
			else
			{
				order->OrderStatus = OrderStatusType::Canceled;
			}
			SendRtnOrder(order);
		}
	}
	buyOrderQueue.clear();

	auto& sellOrderQueue = m_MarketSellOrders[instrumentID];
	for (auto order : sellOrderQueue)
	{
		if (order->VolumeTotal > 0)
		{
			order->VolumeTotal = 0;
			if (order->VolumeTraded > 0)
			{
				order->OrderStatus = OrderStatusType::PartTradedCanceled;
			}
			else
			{
				order->OrderStatus = OrderStatusType::Canceled;
			}
			SendRtnOrder(order);
		}
	}
	sellOrderQueue.clear();
}
int SimExchange::CheckForCancelOrder(mdb::Order* order)
{
	if (order->OrderStatus == OrderStatusType::Inserting || order->OrderStatus == OrderStatusType::Inserted || order->OrderStatus == OrderStatusType::PartTraded)
	{
		return ErrorNone;
	}
	return ErrorFinalOrderStatus;
}

void SimExchange::CheckMatchForMdTick(mdb::Order* order, mdb::DepthMarketData* mdTick)
{
	if (order->Direction == DirectionType::Buy)
	{
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->AskPrice1, mdTick->AskVolume1);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->AskPrice2, mdTick->AskVolume2);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->AskPrice3, mdTick->AskVolume3);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->AskPrice4, mdTick->AskVolume4);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->AskPrice5, mdTick->AskVolume5);
	}
	else
	{
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->BidPrice1, mdTick->BidVolume1);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->BidPrice2, mdTick->BidVolume2);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->BidPrice3, mdTick->BidVolume3);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->BidPrice4, mdTick->BidVolume4);
		CheckMatchForOnePrice(order, mdTick->UpdateTs, mdTick->LastPrice, mdTick->BidPrice5, mdTick->BidVolume5);
	}
}
void SimExchange::CheckMatchForMdBar(mdb::Order* order, mdb::BarMarketData* mdBar)
{
	PriceType matchPrice;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy)
		{
			if (order->Price < mdBar->Low)
				return;
			matchPrice = order->Price > mdBar->High ? mdBar->High : order->Price;
		}
		else
		{
			if (order->Price > mdBar->High)
				return;
			matchPrice = order->Price < mdBar->Low ? mdBar->Low : order->Price;
		}
	}
	else
	{
		matchPrice = (mdBar->High + mdBar->Low) / 2;
	}
	TradeIDType tradeID;
	GetNextTradeID(tradeID);
	TimeType tradeTime;
	strcpy(tradeTime, to_string((mdBar->UpdateTs /1000) % 1000000).c_str());
	Match(order, matchPrice, order->VolumeTotal, tradeID, tradeTime);
}
void SimExchange::CheckMatchForOnePrice(mdb::Order* order, const Int64Type& updateTs, PriceType lastPrice, PriceType oppoPrice, VolumeType& oppoVolume)
{
	if (order->VolumeTotal <= 0 || oppoVolume <= 0 || oppoVolume == std::numeric_limits<double>::infinity())
		return;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy && order->Price < oppoPrice)
			return;
		if (order->Direction == DirectionType::Sell && order->Price > oppoPrice)
			return;
	}

	VolumeType matchVolume = 0;
	PriceType matchPrice = 0.0;
	matchVolume = std::min(order->VolumeTotal, oppoVolume);
	matchPrice = GetMatchPrice(order->OrderPriceType, order->Price, oppoPrice, lastPrice);

	oppoVolume -= matchVolume;
	TradeIDType tradeID;
	GetNextTradeID(tradeID);
	TimeType tradeTime;
	strcpy(tradeTime, to_string((updateTs / 1000) % 1000000).c_str());
	Match(order, matchPrice, matchVolume, tradeID, tradeTime);
}
void SimExchange::CheckMatchForOrderQueue(mdb::Order* order)
{
	if (order->Direction == DirectionType::Buy)
	{
		auto& queueOrders = m_SellOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			CheckMatchForTwoOrder(order, queueOrder);
		}
	}
	else
	{
		auto& queueOrders = m_BuyOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			CheckMatchForTwoOrder(order, queueOrder);
		}
	}
}
bool SimExchange::CheckMatchForTwoOrder(mdb::Order* order, mdb::Order* queueOrder)
{
	if (order->VolumeTotal <= 0)
		return false;
	if (queueOrder->VolumeTotal <= 0)
		return true;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy && order->Price < queueOrder->Price)
			return false;
		if (order->Direction == DirectionType::Sell && order->Price > queueOrder->Price)
			return false;
	}

	VolumeType matchVolume = 0;
	PriceType matchPrice = 0.0;
	matchVolume = min(order->VolumeTotal, queueOrder->VolumeTotal);
	matchPrice = queueOrder->Price;

	TradeIDType tradeID;
	GetNextTradeID(tradeID);
	Match(queueOrder, matchPrice, matchVolume, tradeID, order->OrderTime);
	Match(order, matchPrice, matchVolume, tradeID, order->OrderTime);
	return true;
}
void SimExchange::Match(mdb::Order* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime)
{
	m_InstrumentsHasMatched[order->InstrumentID] = true;
	auto posiDirection = GetPosiDirection(order->OffsetFlag, order->Direction);
	auto position = m_Mdb->t_Position->m_PrimaryKey->Select(order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, posiDirection);
	auto tradeAmount = price * volume * position->VolumeMultiple;
	if (order->OffsetFlag == OffsetFlagType::Open)
	{
		auto positionDetail = PositionDetail::Allocate();
		strcpy(positionDetail->TradingDay, position->TradingDay);
		strcpy(positionDetail->AccountID, position->AccountID);
		positionDetail->AccountType = position->AccountType;
		strcpy(positionDetail->ExchangeID, position->ExchangeID);
		strcpy(positionDetail->InstrumentID, position->InstrumentID);
		positionDetail->ProductClass = position->ProductClass;
		positionDetail->PosiDirection = position->PosiDirection;
		strcpy(positionDetail->OpenDate, position->TradingDay);
		strcpy(positionDetail->TradeID, tradeID);
		positionDetail->Volume = volume;
		positionDetail->OpenPrice = price;
		if (position->ProductClass == ProductClassType::FutureOption || position->ProductClass == ProductClassType::StockOption)
		{
			positionDetail->MarketValue = order->Direction == DirectionType::Buy ? tradeAmount : -tradeAmount;
			positionDetail->CashIn = order->Direction == DirectionType::Sell ? tradeAmount : 0.0;
			positionDetail->CashOut = order->Direction == DirectionType::Buy ? tradeAmount : 0.0;
		}
		positionDetail->Margin = 0.0;
		positionDetail->Commission = 0.0;
		positionDetail->VolumeMultiple = position->VolumeMultiple;
		positionDetail->CloseProfitByDate = 0.0;
		positionDetail->CloseProfitByTrade = 0.0;
		positionDetail->PositionProfitByDate = 0.0;
		positionDetail->PositionProfitByTrade = 0.0;
		positionDetail->SettlementPrice = 0.0;
		positionDetail->PreSettlementPrice = position->PreSettlementPrice;
		positionDetail->CloseVolume = 0;
		positionDetail->CloseAmount = 0.0;
		m_Mdb->t_PositionDetail->Insert(positionDetail);

		position->TotalPosition += volume;
		position->TodayPosition += volume;
	}
	else
	{
		std::set<mdb::PositionDetail*, PositionDetialLessForOpenDate> positionDetails;
		auto itPair = m_Mdb->t_PositionDetail->m_TradeMatchIndex->EqualRange(position->TradingDay, position->AccountID, position->ExchangeID, position->InstrumentID, position->PosiDirection);
		for (auto& it = itPair.first; it != itPair.second; ++it)
		{
			positionDetails.insert(*it);
		}
		auto flag = position->PosiDirection == PosiDirectionType::Long ? 1 : -1;
		auto remainVolume = volume;
		for (auto positionDetail : positionDetails)
		{
			auto currVolume = std::min(remainVolume, positionDetail->Volume - positionDetail->CloseVolume);
			if (currVolume <= 0)
			{
				continue;
			}
			auto closeAmount = price * currVolume * position->VolumeMultiple;
			positionDetail->CloseVolume += currVolume;
			positionDetail->CloseAmount += closeAmount;
			positionDetail->CloseProfitByTrade += flag * (price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
			if (strcmp(positionDetail->OpenDate, positionDetail->TradingDay) == 0)
			{
				positionDetail->CloseProfitByDate += flag * (price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
			}
			else
			{
				positionDetail->CloseProfitByDate += flag * (price - positionDetail->PreSettlementPrice) * currVolume * positionDetail->VolumeMultiple;
			}
			if (position->ProductClass == ProductClassType::FutureOption || position->ProductClass == ProductClassType::StockOption || position->ProductClass == ProductClassType::Stock || position->ProductClass == ProductClassType::ETF)
			{
				positionDetail->CashIn += order->Direction == DirectionType::Sell ? closeAmount : 0.0;
				positionDetail->CashOut += order->Direction == DirectionType::Buy ? closeAmount : 0.0;
			}
			remainVolume -= currVolume;
			if (remainVolume <= 0)
				break;
		}

		position->TotalPosition -= volume;
		position->PositionFrozen -= volume;
	}
	order->VolumeTraded += volume;
	order->VolumeTotal -= volume;
	order->OrderStatus = order->VolumeTotal > 0 ? OrderStatusType::PartTraded : OrderStatusType::AllTraded;
	SendRtnOrder(order);
	auto trade = Trade::Allocate();
	memset(trade, 0, sizeof(Trade));
	strcpy(trade->TradingDay, m_TradingDay);
	strcpy(trade->AccountID, order->AccountID);
	trade->AccountType = order->AccountType;
	strcpy(trade->ExchangeID, order->ExchangeID);
	strcpy(trade->InstrumentID, order->InstrumentID);
	trade->ProductClass = order->ProductClass;
	trade->OrderID = order->OrderID;
	strcpy(trade->OrderSysID, order->OrderSysID);
	strcpy(trade->TradeID, tradeID);
	trade->Direction = order->Direction;
	trade->OffsetFlag = order->OffsetFlag;
	trade->Price = price;
	trade->Volume = volume;
	trade->VolumeMultiple = order->VolumeMultiple;
	trade->TradeAmount = tradeAmount;
	trade->Commission = 1;
	strcpy(trade->TradeDate, order->OrderDate);
	strcpy(trade->TradeTime, tradeTime);
	m_Mdb->t_Trade->Insert(trade);
	SendRtnTrade(trade);
}

void SimExchange::UpdateAllQueueOrder(const std::string& instrumentID)
{
	auto& buyOrderQueue = m_BuyOrders[instrumentID];
	std::erase_if(buyOrderQueue, [](mdb::Order* order) {return order->VolumeTotal == 0; });
	auto& sellOrderQueue = m_SellOrders[instrumentID];
	std::erase_if(sellOrderQueue, [](mdb::Order* order) {return order->VolumeTotal == 0; });
}

OrderIDType SimExchange::GetNextOrderID()
{
	return ++m_MaxOrderID;
}
void SimExchange::GetNextTradeID(TradeIDType& tradeID)
{
	sprintf(tradeID, "%s%08d", m_TradingDay, ++m_MaxTradeID);
}
PriceType SimExchange::GetSettlementPrice(mdb::PositionDetail* positionDetail)
{
	if (m_MarketDataType == MarketDataTypeType::Tick)
	{
		auto mdTick = m_LastMdTicks[positionDetail->InstrumentID];
		if (mdTick == nullptr)
		{
			return positionDetail->PreSettlementPrice;
		}
		else if (mdTick->LastPrice != std::numeric_limits<double>::infinity())
		{
			return mdTick->LastPrice;
		}
		else if (mdTick->PreSettlementPrice != std::numeric_limits<double>::infinity())
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
	::Free(orderField);
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
	::Free(tradeField);
}
void SimExchange::SendRtnDepthMarketData(mdb::DepthMarketData* mdTick)
{
	assert((sizeof(DepthMarketDataField) == sizeof(mdb::DepthMarketData)));
	memcpy(&m_PushMdTick, mdTick, sizeof(DepthMarketDataField));
	m_BackTestSpi->OnRtnDepthMarketData(&m_PushMdTick);
}
void SimExchange::SendRtnBarMarketData(mdb::BarMarketData* mdBar)
{
	assert((sizeof(BarMarketDataField) == sizeof(mdb::BarMarketData)));
	memcpy(&m_PushMdBar, mdBar, sizeof(BarMarketDataField));
	m_BackTestSpi->OnRtnBarMarketData(&m_PushMdBar);
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


