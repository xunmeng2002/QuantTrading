#include "StrategyBase.h"

#include "BarUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <cstring>
#include <stdexcept>

using namespace spark::core;

namespace quanttrading::strategy
{
StrategyBase::StrategyBase(quanttrading::BackTestApi* backTestApi, const char* accountID)
	:m_BackTestApi(backTestApi), m_AccountID(accountID)
{
}
StrategyBase::~StrategyBase() = default;

bool StrategyBase::Start()
{
	m_BackTestApi->RegisterSpi(this);
	if (!m_BackTestApi->Init())
	{
		WriteLog(LogLevel::Error, "StrategyBase::Start: api init failed");
		return false;
	}
	// 账户注册先于 OnStart 的行情订阅：引擎账户表按需自建，注册与下单同队列 FIFO，撮合检查账户时必已存在
	ReqRegisterAccountField reqRegisterAccount;
	memset(&reqRegisterAccount, 0, sizeof(ReqRegisterAccountField));
	Utility::Strcpy(reqRegisterAccount.AccountID, m_AccountID.c_str());
	m_BackTestApi->ReqRegisterAccount(&reqRegisterAccount, ++m_NextRequestID);
	OnStart();
	return true;
}
void StrategyBase::WaitForEnd()
{
	m_BackTestApi->Join();
}

void StrategyBase::SubscribeMarketData(const char* exchangeID, const char* instrumentID)
{
	ReqSubMarketDataField reqSubMarketData;
	memset(&reqSubMarketData, 0, sizeof(ReqSubMarketDataField));
	Utility::Strcpy(reqSubMarketData.ExchangeID, exchangeID);
	Utility::Strcpy(reqSubMarketData.InstrumentID, instrumentID);
	m_BackTestApi->ReqSubMarketData(&reqSubMarketData, ++m_NextRequestID);

	ReqSubMarketDataFinishedField reqSubMarketDataFinished;
	memset(&reqSubMarketDataFinished, 0, sizeof(ReqSubMarketDataFinishedField));
	m_BackTestApi->ReqSubMarketDataFinished(&reqSubMarketDataFinished, ++m_NextRequestID);
}
void StrategyBase::SubscribeTick(const char* exchangeID, const char* instrumentID)
{
	SubscribeMarketData(exchangeID, instrumentID);
}
void StrategyBase::SubscribeBar(const char* exchangeID, const char* instrumentID)
{
	SubscribeMarketData(exchangeID, instrumentID);
}
void StrategyBase::DeclareBarPeriod(const char* barPreces)
{
	BarPrecesType barPrecesType;
	int barPeriod = 0;
	if (!bar::ParseBarPreces(barPreces != nullptr ? barPreces : "", barPrecesType, barPeriod))
	{
		WriteLog(LogLevel::Error, "DeclareBarPeriod: Invalid barPreces:%s, expect <n><s|m|h|d> e.g. 5m", barPreces != nullptr ? barPreces : "");
		throw std::logic_error("StrategyBase::DeclareBarPeriod: invalid barPreces");
	}
	m_BarAggregator = std::make_unique<bar::BarAggregator>(barPrecesType, barPeriod);
	m_BarAggregator->Subscribe(this);
	m_BarAggregationEnabled = true;
}

ClientOrderIDType StrategyBase::InsertLimitOrder(const char* exchangeID, const char* instrumentID, DirectionType direction, OffsetFlagType offsetFlag, PriceType price, VolumeType volume)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	Utility::Strcpy(reqInsertOrder.AccountID, m_AccountID.c_str());
	Utility::Strcpy(reqInsertOrder.ExchangeID, exchangeID);
	Utility::Strcpy(reqInsertOrder.InstrumentID, instrumentID);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = offsetFlag;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = volume;
	reqInsertOrder.ClientOrderID = ++m_NextClientOrderID;
	m_BackTestApi->ReqInsertOrder(&reqInsertOrder, ++m_NextRequestID);

	OrderContext orderContext;
	orderContext.ExchangeID = exchangeID;
	orderContext.InstrumentID = instrumentID;
	m_OrderContexts[reqInsertOrder.ClientOrderID] = orderContext;
	return reqInsertOrder.ClientOrderID;
}
ClientOrderIDType StrategyBase::BuyOpen(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeID, instrumentID, DirectionType::Buy, OffsetFlagType::Open, price, volume);
}
ClientOrderIDType StrategyBase::SellOpen(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeID, instrumentID, DirectionType::Sell, OffsetFlagType::Open, price, volume);
}
ClientOrderIDType StrategyBase::BuyClose(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeID, instrumentID, DirectionType::Buy, OffsetFlagType::Close, price, volume);
}
ClientOrderIDType StrategyBase::SellClose(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeID, instrumentID, DirectionType::Sell, OffsetFlagType::Close, price, volume);
}

bool StrategyBase::CancelOrder(ClientOrderIDType clientOrderID)
{
	auto orderContextIt = m_OrderContexts.find(clientOrderID);
	if (orderContextIt == m_OrderContexts.end())
	{
		WriteLog(LogLevel::Error, "CancelOrder: ClientOrderID:%d was not inserted by this strategy", clientOrderID);
		return false;
	}
	ReqCancelOrderField reqCancelOrder;
	memset(&reqCancelOrder, 0, sizeof(ReqCancelOrderField));
	Utility::Strcpy(reqCancelOrder.AccountID, m_AccountID.c_str());
	Utility::Strcpy(reqCancelOrder.ExchangeID, orderContextIt->second.ExchangeID.c_str());
	Utility::Strcpy(reqCancelOrder.InstrumentID, orderContextIt->second.InstrumentID.c_str());
	reqCancelOrder.ClientOrderID = clientOrderID;
	reqCancelOrder.ClientCancelOrderID = ++m_NextClientCancelOrderID;
	auto orderIt = m_Orders.find(clientOrderID);
	if (orderIt != m_Orders.end())
	{
		reqCancelOrder.OrderID = orderIt->second.OrderID;
	}
	m_BackTestApi->ReqCancelOrder(&reqCancelOrder, ++m_NextRequestID);
	return true;
}

VolumeType StrategyBase::GetLongPosition(const char* instrumentID) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentID);
	return instrumentStateIt != m_InstrumentStates.end() ? instrumentStateIt->second.LongVolume : 0;
}
VolumeType StrategyBase::GetShortPosition(const char* instrumentID) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentID);
	return instrumentStateIt != m_InstrumentStates.end() ? instrumentStateIt->second.ShortVolume : 0;
}
PriceType StrategyBase::GetLastPrice(const char* instrumentID) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentID);
	return instrumentStateIt != m_InstrumentStates.end() ? instrumentStateIt->second.LastPrice : 0;
}

void StrategyBase::OnConnected()
{
	WriteLog(LogLevel::Info, "StrategyBase: connected");
}
void StrategyBase::OnDisConnected()
{
	WriteLog(LogLevel::Info, "StrategyBase: disconnected");
}
void StrategyBase::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorID != 0)
	{
		WriteLog(LogLevel::Error, "SubscribeMarketData failed: ErrorID:%d ErrorMsg:%s", rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRspRegisterAccount(const RspRegisterAccountField* rspRegisterAccount, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorID != 0)
	{
		WriteLog(LogLevel::Error, "RegisterAccount failed: AccountID:%s ErrorID:%d ErrorMsg:%s",
			rspRegisterAccount != nullptr ? rspRegisterAccount->AccountID : "", rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	m_InstrumentStates[depthMarketData->InstrumentID].LastPrice = depthMarketData->LastPrice;
	OnTick(depthMarketData);
}
void StrategyBase::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	if (m_BarAggregationEnabled)
	{
		m_BarAggregator->OnBarMarketData(barMarketData);
		return;
	}
	OnBar(barMarketData);
}
void StrategyBase::OnBarMarketData(BarMarketDataField* bar)
{
	OnBar(bar);
}
void StrategyBase::OnRtnSessionBegin(const SessionBeginField* sessionBegin)
{
	WriteLog(LogLevel::Info, "Session begin, TradingDay:%s", sessionBegin != nullptr ? sessionBegin->TradingDay : "");
	OnSessionBegin(sessionBegin);
}
void StrategyBase::OnRtnSessionEnd(const SessionEndField* sessionEnd)
{
	WriteLog(LogLevel::Info, "Session end, TradingDay:%s", sessionEnd != nullptr ? sessionEnd->TradingDay : "");
	OnSessionEnd(sessionEnd);
}
void StrategyBase::OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd)
{
	if (!m_IsMdEnded)
	{
		m_IsMdEnded = true;
		if (m_BarAggregationEnabled)
		{
			m_BarAggregator->Flush();
		}
		OnEnd();
		m_BackTestApi->Release();
	}
}
void StrategyBase::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorID != 0)
	{
		WriteLog(LogLevel::Error, "InsertOrder rejected, ClientOrderID:%d ErrorID:%d ErrorMsg:%s",
			reqInsertOrder != nullptr ? reqInsertOrder->ClientOrderID : 0, rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	OnInsertOrderRsp(reqInsertOrder, rspInfo);
}
void StrategyBase::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorID != 0)
	{
		WriteLog(LogLevel::Warning, "CancelOrder failed, ClientOrderID:%d ErrorID:%d ErrorMsg:%s",
			reqCancelOrder != nullptr ? reqCancelOrder->ClientOrderID : 0, rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	OnCancelOrderRsp(reqCancelOrder, rspInfo);
}
void StrategyBase::OnRtnOrder(const OrderField* order)
{
	m_Orders[order->ClientOrderID] = *order;
	if (order->OrderID != 0)
	{
		m_EngineOrderIDs[order->OrderID] = order->ClientOrderID;
	}
	WriteLog(LogLevel::Info, "OnRtnOrder ClientOrderID:%d OrderID:%d Status:%d Price:%f Traded:%lld Total:%lld",
		order->ClientOrderID, order->OrderID, (int)order->OrderStatus, order->Price, order->VolumeTraded, order->VolumeTotal);
	OnOrder(order);
}
void StrategyBase::OnRtnTrade(const TradeField* trade)
{
	auto& instrumentState = m_InstrumentStates[trade->InstrumentID];
	bool isOpenTrade = trade->OffsetFlag == OffsetFlagType::Open;
	if (trade->Direction == DirectionType::Buy && isOpenTrade)
	{
		instrumentState.LongVolume += trade->Volume;
	}
	else if (trade->Direction == DirectionType::Buy)
	{
		instrumentState.ShortVolume -= trade->Volume;
	}
	else if (isOpenTrade)
	{
		instrumentState.ShortVolume += trade->Volume;
	}
	else
	{
		instrumentState.LongVolume -= trade->Volume;
	}
	ClientOrderIDType clientOrderID = 0;
	auto engineOrderIDIt = m_EngineOrderIDs.find(trade->OrderID);
	if (engineOrderIDIt != m_EngineOrderIDs.end())
	{
		clientOrderID = engineOrderIDIt->second;
	}
	else
	{
		WriteLog(LogLevel::Warning, "OnRtnTrade: trade OrderID:%d has no matched client order", trade->OrderID);
	}
	WriteLog(LogLevel::Info, "OnRtnTrade ClientOrderID:%d Direction:%d Offset:%d Price:%f Volume:%lld Commission:%f",
		clientOrderID, (int)trade->Direction, (int)trade->OffsetFlag, trade->Price, trade->Volume, trade->Commission);
	OnTrade(trade, clientOrderID);
}
}
