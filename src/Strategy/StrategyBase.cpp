#include "StrategyBase.h"

#include "QuantUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <cstring>
#include <stdexcept>

using namespace Spark::Core;

namespace QuantTrading::strategy
{
StrategyBase::StrategyBase(QuantTrading::BackTestApi* backTestApi, const char* accountId)
	:m_BackTestApi(backTestApi), m_AccountID(accountId)
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
	Utility::Strcpy(reqRegisterAccount.AccountId, m_AccountID.c_str());
	m_BackTestApi->ReqRegisterAccount(&reqRegisterAccount, ++m_NextRequestID);
	OnStart();
	return true;
}
void StrategyBase::WaitForEnd()
{
	m_BackTestApi->Join();
}

void StrategyBase::SubscribeMarketData(const char* exchangeId, const char* instrumentId)
{
	ReqSubMarketDataField reqSubMarketData;
	memset(&reqSubMarketData, 0, sizeof(ReqSubMarketDataField));
	Utility::Strcpy(reqSubMarketData.ExchangeId, exchangeId);
	Utility::Strcpy(reqSubMarketData.InstrumentId, instrumentId);
	reqSubMarketData.BarPreces = m_DeclaredBarPreces;
	reqSubMarketData.BarPeriod = m_DeclaredBarPeriod;
	m_BackTestApi->ReqSubMarketData(&reqSubMarketData, ++m_NextRequestID);

	ReqSubMarketDataFinishedField reqSubMarketDataFinished;
	memset(&reqSubMarketDataFinished, 0, sizeof(ReqSubMarketDataFinishedField));
	m_BackTestApi->ReqSubMarketDataFinished(&reqSubMarketDataFinished, ++m_NextRequestID);
}
void StrategyBase::SubscribeTick(const char* exchangeId, const char* instrumentId)
{
	SubscribeMarketData(exchangeId, instrumentId);
}
void StrategyBase::SubscribeBar(const char* exchangeId, const char* instrumentId)
{
	SubscribeMarketData(exchangeId, instrumentId);
}
void StrategyBase::DeclareBarPeriod(const char* barPreces)
{
	BarPrecesType barPrecesType = BarPrecesType::Minute;
	int barPeriod = 0;
	if (!ParseBarPreces(barPreces != nullptr ? barPreces : "", barPrecesType, barPeriod))
	{
		WriteLog(LogLevel::Error, "DeclareBarPeriod: Invalid barPreces:%s, expect <n><s|m|h|d> e.g. 5m", barPreces != nullptr ? barPreces : "");
		throw std::logic_error("StrategyBase::DeclareBarPeriod: invalid barPreces");
	}
	if (!IsValidBarPrecesTarget(barPrecesType, barPeriod))
	{
		WriteLog(LogLevel::Error, "DeclareBarPeriod: BarPreces:%s can not be a target, expect <n><m|h|d> e.g. 5m", barPreces != nullptr ? barPreces : "");
		throw std::logic_error("StrategyBase::DeclareBarPeriod: barPreces can not be a target");
	}
	m_DeclaredBarPreces = barPrecesType;
	m_DeclaredBarPeriod = barPeriod;
}

ClientOrderIdType StrategyBase::InsertLimitOrder(const char* exchangeId, const char* instrumentId, DirectionType direction, OffsetFlagType offsetFlag, PriceType price, VolumeType volume)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	Utility::Strcpy(reqInsertOrder.AccountId, m_AccountID.c_str());
	Utility::Strcpy(reqInsertOrder.ExchangeId, exchangeId);
	Utility::Strcpy(reqInsertOrder.InstrumentId, instrumentId);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = offsetFlag;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = volume;
	reqInsertOrder.ClientOrderId = ++m_NextClientOrderID;
	m_BackTestApi->ReqInsertOrder(&reqInsertOrder, ++m_NextRequestID);

	OrderContext orderContext;
	orderContext.ExchangeId = exchangeId;
	orderContext.InstrumentId = instrumentId;
	m_OrderContexts[reqInsertOrder.ClientOrderId] = orderContext;
	return reqInsertOrder.ClientOrderId;
}
ClientOrderIdType StrategyBase::BuyOpen(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeId, instrumentId, DirectionType::Buy, OffsetFlagType::Open, price, volume);
}
ClientOrderIdType StrategyBase::SellOpen(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeId, instrumentId, DirectionType::Sell, OffsetFlagType::Open, price, volume);
}
ClientOrderIdType StrategyBase::BuyClose(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeId, instrumentId, DirectionType::Buy, OffsetFlagType::Close, price, volume);
}
ClientOrderIdType StrategyBase::SellClose(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume)
{
	return InsertLimitOrder(exchangeId, instrumentId, DirectionType::Sell, OffsetFlagType::Close, price, volume);
}

bool StrategyBase::CancelOrder(ClientOrderIdType clientOrderID)
{
	auto orderContextIt = m_OrderContexts.find(clientOrderID);
	if (orderContextIt == m_OrderContexts.end())
	{
		WriteLog(LogLevel::Error, "CancelOrder: ClientOrderId:%d was not inserted by this strategy", clientOrderID);
		return false;
	}
	ReqCancelOrderField reqCancelOrder;
	memset(&reqCancelOrder, 0, sizeof(ReqCancelOrderField));
	Utility::Strcpy(reqCancelOrder.AccountId, m_AccountID.c_str());
	Utility::Strcpy(reqCancelOrder.ExchangeId, orderContextIt->second.ExchangeId.c_str());
	Utility::Strcpy(reqCancelOrder.InstrumentId, orderContextIt->second.InstrumentId.c_str());
	reqCancelOrder.ClientOrderId = clientOrderID;
	reqCancelOrder.ClientCancelOrderId = ++m_NextClientCancelOrderID;
	auto orderIt = m_Orders.find(clientOrderID);
	if (orderIt != m_Orders.end())
	{
		reqCancelOrder.OrderId = orderIt->second.OrderId;
	}
	m_BackTestApi->ReqCancelOrder(&reqCancelOrder, ++m_NextRequestID);
	return true;
}

VolumeType StrategyBase::GetLongPosition(const char* instrumentId) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentId);
	return instrumentStateIt != m_InstrumentStates.end() ? instrumentStateIt->second.LongVolume : 0;
}
VolumeType StrategyBase::GetShortPosition(const char* instrumentId) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentId);
	return instrumentStateIt != m_InstrumentStates.end() ? instrumentStateIt->second.ShortVolume : 0;
}
PriceType StrategyBase::GetLastPrice(const char* instrumentId) const
{
	auto instrumentStateIt = m_InstrumentStates.find(instrumentId);
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
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "SubscribeMarketData failed: ErrorId:%d ErrorMsg:%s", rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRspRegisterAccount(const RspRegisterAccountField* rspRegisterAccount, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "RegisterAccount failed: AccountId:%s ErrorId:%d ErrorMsg:%s",
			rspRegisterAccount != nullptr ? rspRegisterAccount->AccountId : "", rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	m_InstrumentStates[depthMarketData->InstrumentId].LastPrice = depthMarketData->LastPrice;
	OnTick(depthMarketData);
}
void StrategyBase::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	OnBar(barMarketData);
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
		OnEnd();
		m_BackTestApi->Release();
	}
}
void StrategyBase::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "InsertOrder rejected, ClientOrderId:%d ErrorId:%d ErrorMsg:%s",
			reqInsertOrder != nullptr ? reqInsertOrder->ClientOrderId : 0, rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	OnInsertOrderRsp(reqInsertOrder, rspInfo);
}
void StrategyBase::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Warning, "CancelOrder failed, ClientOrderId:%d ErrorId:%d ErrorMsg:%s",
			reqCancelOrder != nullptr ? reqCancelOrder->ClientOrderId : 0, rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	OnCancelOrderRsp(reqCancelOrder, rspInfo);
}
void StrategyBase::OnRtnOrder(const OrderField* order)
{
	m_Orders[order->ClientOrderId] = *order;
	if (order->OrderId != 0)
	{
		m_EngineOrderIDs[order->OrderId] = order->ClientOrderId;
	}
	WriteLog(LogLevel::Info, "OnRtnOrder ClientOrderId:%d OrderId:%d Status:%d Price:%f Traded:%lld Total:%lld",
		order->ClientOrderId, order->OrderId, (int)order->OrderStatus, order->Price, order->VolumeTraded, order->VolumeTotal);
	OnOrder(order);
}
void StrategyBase::OnRtnTrade(const TradeField* trade)
{
	auto& instrumentState = m_InstrumentStates[trade->InstrumentId];
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
	ClientOrderIdType clientOrderID = 0;
	auto engineOrderIDIt = m_EngineOrderIDs.find(trade->OrderId);
	if (engineOrderIDIt != m_EngineOrderIDs.end())
	{
		clientOrderID = engineOrderIDIt->second;
	}
	else
	{
		WriteLog(LogLevel::Warning, "OnRtnTrade: trade OrderId:%d has no matched client order", trade->OrderId);
	}
	WriteLog(LogLevel::Info, "OnRtnTrade ClientOrderId:%d Direction:%d Offset:%d Price:%f Volume:%lld Commission:%f",
		clientOrderID, (int)trade->Direction, (int)trade->OffsetFlag, trade->Price, trade->Volume, trade->Commission);
	OnTrade(trade, clientOrderID);
}
}
