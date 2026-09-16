// 本文件由 ../Templates/Cpp/ApiTest/SpiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeSpiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;

namespace quanttrading
{
double GetDoubleValue(const double& value)
{
    if (value == std::numeric_limits<double>::max())
    {
        return 0.0;
    }
    return value;
}


void SimExchangeSpiMiddle::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
}
void SimExchangeSpiMiddle::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void SimExchangeSpiMiddle::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLoginField:AccountId:[%s], LoginDate:[%s], LoginTime:[%s], SessionId:[%lld]",
			rspAccountLogin->AccountId, rspAccountLogin->LoginDate, rspAccountLogin->LoginTime, rspAccountLogin->SessionId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogin is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLogoutField:AccountId:[%s]",
			rspAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogout is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountId, order->ExchangeId, order->InstrumentId, static_cast<int>(order->ProductClass), order->OrderId, order->OrderSysId, static_cast<int>(order->Direction), static_cast<int>(order->OffsetFlag), static_cast<int>(order->OrderPriceType), GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, static_cast<int>(order->OrderStatus), order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionId, order->ClientOrderId, order->RequestId, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTrade: RequestID:%d, IsLast:%d", requestID, isLast);
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, static_cast<int>(trade->ProductClass), trade->OrderId, trade->OrderSysId, trade->TradeId, static_cast<int>(trade->Direction), static_cast<int>(trade->OffsetFlag), GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (instrument != nullptr)
	{
		WriteLog(LogLevel::Info, "InstrumentField:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], ProductId:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			instrument->ExchangeId, instrument->InstrumentId, instrument->ExchangeInstId, instrument->InstrumentName, instrument->ProductId, static_cast<int>(instrument->ProductClass), instrument->VolumeMultiple, GetDoubleValue(instrument->PriceTick), instrument->MaxMarketOrderVolume, instrument->MinMarketOrderVolume, instrument->MaxLimitOrderVolume, instrument->MinLimitOrderVolume, instrument->SessionName);
	}
	else
	{
		WriteLog(LogLevel::Info, "instrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspInsertOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), GetDoubleValue(reqInsertOrder->Price), reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRtnOrder(const OrderField* order)
{
	WriteLog(LogLevel::Info, "OnRtnOrder");
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountId, order->ExchangeId, order->InstrumentId, static_cast<int>(order->ProductClass), order->OrderId, order->OrderSysId, static_cast<int>(order->Direction), static_cast<int>(order->OffsetFlag), static_cast<int>(order->OrderPriceType), GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, static_cast<int>(order->OrderStatus), order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionId, order->ClientOrderId, order->RequestId, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRtnTrade(const TradeField* trade)
{
	WriteLog(LogLevel::Info, "OnRtnTrade");
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, static_cast<int>(trade->ProductClass), trade->OrderId, trade->OrderSysId, trade->TradeId, static_cast<int>(trade->Direction), static_cast<int>(trade->OffsetFlag), GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
}
}
