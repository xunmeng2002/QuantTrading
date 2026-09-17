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
	:backTestApi_(backTestApi), accountId_(accountId)
{
}
StrategyBase::~StrategyBase() = default;

bool StrategyBase::Start()
{
	backTestApi_->RegisterSpi(this);
	if (!backTestApi_->Init())
	{
		WriteLog(LogLevel::Error, "StrategyBase::Start: api init failed");
		return false;
	}
	// 账户注册先于 OnStart 的行情订阅：引擎账户表按需自建，注册与下单同队列 FIFO，撮合检查账户时必已存在
	ReqRegisterAccountField reqRegisterAccount;
	memset(&reqRegisterAccount, 0, sizeof(ReqRegisterAccountField));
	Utility::Strcpy(reqRegisterAccount.AccountId, accountId_.c_str());
	backTestApi_->ReqRegisterAccount(&reqRegisterAccount, ++nextRequestId_);
	OnStart();
	return true;
}
void StrategyBase::WaitForEnd()
{
	backTestApi_->Join();
}

void StrategyBase::SubscribeMarketData(const char* exchangeId, const char* instrumentId)
{
	ReqSubMarketDataField reqSubMarketData;
	memset(&reqSubMarketData, 0, sizeof(ReqSubMarketDataField));
	Utility::Strcpy(reqSubMarketData.ExchangeId, exchangeId);
	Utility::Strcpy(reqSubMarketData.InstrumentId, instrumentId);
	reqSubMarketData.BarPreces = declaredBarPreces_;
	reqSubMarketData.BarPeriod = declaredBarPeriod_;
	backTestApi_->ReqSubMarketData(&reqSubMarketData, ++nextRequestId_);

	ReqSubMarketDataFinishedField reqSubMarketDataFinished;
	memset(&reqSubMarketDataFinished, 0, sizeof(ReqSubMarketDataFinishedField));
	backTestApi_->ReqSubMarketDataFinished(&reqSubMarketDataFinished, ++nextRequestId_);
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
	declaredBarPreces_ = barPrecesType;
	declaredBarPeriod_ = barPeriod;
}

ClientOrderIdType StrategyBase::InsertLimitOrder(const char* exchangeId, const char* instrumentId, DirectionType direction, OffsetFlagType offsetFlag, PriceType price, VolumeType volume)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	Utility::Strcpy(reqInsertOrder.AccountId, accountId_.c_str());
	Utility::Strcpy(reqInsertOrder.ExchangeId, exchangeId);
	Utility::Strcpy(reqInsertOrder.InstrumentId, instrumentId);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = offsetFlag;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = volume;
	reqInsertOrder.ClientOrderId = ++nextClientOrderId_;
	backTestApi_->ReqInsertOrder(&reqInsertOrder, ++nextRequestId_);

	OrderContext orderContext;
	orderContext.ExchangeId = exchangeId;
	orderContext.InstrumentId = instrumentId;
	orderContexts_[reqInsertOrder.ClientOrderId] = orderContext;
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
	auto orderContextIt = orderContexts_.find(clientOrderID);
	if (orderContextIt == orderContexts_.end())
	{
		WriteLog(LogLevel::Error, "CancelOrder: ClientOrderId:%d was not inserted by this strategy", clientOrderID);
		return false;
	}
	ReqCancelOrderField reqCancelOrder;
	memset(&reqCancelOrder, 0, sizeof(ReqCancelOrderField));
	Utility::Strcpy(reqCancelOrder.AccountId, accountId_.c_str());
	Utility::Strcpy(reqCancelOrder.ExchangeId, orderContextIt->second.ExchangeId.c_str());
	Utility::Strcpy(reqCancelOrder.InstrumentId, orderContextIt->second.InstrumentId.c_str());
	reqCancelOrder.ClientOrderId = clientOrderID;
	reqCancelOrder.ClientCancelOrderId = ++nextClientCancelOrderId_;
	auto orderIt = orders_.find(clientOrderID);
	if (orderIt != orders_.end())
	{
		reqCancelOrder.OrderId = orderIt->second.OrderId;
	}
	backTestApi_->ReqCancelOrder(&reqCancelOrder, ++nextRequestId_);
	return true;
}

VolumeType StrategyBase::GetLongPosition(const char* instrumentId) const
{
	auto instrumentStateIt = instrumentStates_.find(instrumentId);
	return instrumentStateIt != instrumentStates_.end() ? instrumentStateIt->second.LongVolume : 0;
}
VolumeType StrategyBase::GetShortPosition(const char* instrumentId) const
{
	auto instrumentStateIt = instrumentStates_.find(instrumentId);
	return instrumentStateIt != instrumentStates_.end() ? instrumentStateIt->second.ShortVolume : 0;
}
PriceType StrategyBase::GetLastPrice(const char* instrumentId) const
{
	auto instrumentStateIt = instrumentStates_.find(instrumentId);
	return instrumentStateIt != instrumentStates_.end() ? instrumentStateIt->second.LastPrice : 0;
}

void StrategyBase::OnConnected()
{
	WriteLog(LogLevel::Info, "StrategyBase: connected");
}
void StrategyBase::OnDisConnected()
{
	WriteLog(LogLevel::Info, "StrategyBase: disconnected");
}
void StrategyBase::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "SubscribeMarketData failed: ErrorId:%d ErrorMsg:%s", rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRspRegisterAccount(const RspRegisterAccountField* rspRegisterAccount, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "RegisterAccount failed: AccountId:%s ErrorId:%d ErrorMsg:%s",
			rspRegisterAccount != nullptr ? rspRegisterAccount->AccountId : "", rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
}
void StrategyBase::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	instrumentStates_[depthMarketData->InstrumentId].LastPrice = depthMarketData->LastPrice;
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
	if (!isMdEnded_)
	{
		isMdEnded_ = true;
		OnEnd();
		backTestApi_->Release();
	}
}
void StrategyBase::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (rspInfo != nullptr && rspInfo->ErrorId != 0)
	{
		WriteLog(LogLevel::Error, "InsertOrder rejected, ClientOrderId:%d ErrorId:%d ErrorMsg:%s",
			reqInsertOrder != nullptr ? reqInsertOrder->ClientOrderId : 0, rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	OnInsertOrderRsp(reqInsertOrder, rspInfo);
}
void StrategyBase::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
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
	orders_[order->ClientOrderId] = *order;
	if (order->OrderId != 0)
	{
		engineOrderIds_[order->OrderId] = order->ClientOrderId;
	}
	WriteLog(LogLevel::Info, "OnRtnOrder ClientOrderId:%d OrderId:%d Status:%d Price:%f Traded:%lld Total:%lld",
		order->ClientOrderId, order->OrderId, (int)order->OrderStatus, order->Price, order->VolumeTraded, order->VolumeTotal);
	OnOrder(order);
}
void StrategyBase::OnRtnTrade(const TradeField* trade)
{
	auto& instrumentState = instrumentStates_[trade->InstrumentId];
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
	auto engineOrderIDIt = engineOrderIds_.find(trade->OrderId);
	if (engineOrderIDIt != engineOrderIds_.end())
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
