#include "SimExchangeSpiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

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

void SimExchangeSpiMiddle::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLoginField:AccountID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]",
			rspAccountLogin->AccountID, rspAccountLogin->LoginDate, rspAccountLogin->LoginTime, rspAccountLogin->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogin is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLogoutField:AccountID:[%s]",
			rspAccountLogout->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogout is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, (int)order->ProductClass, order->OrderID, order->OrderSysID, (int)order->Direction, (int)order->OffsetFlag, (int)order->OrderPriceType, GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, (int)order->OrderStatus, order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionID, order->ClientOrderID, order->RequestID, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTrade: RequestID:%d, IsLast:%d", requestID, isLast);
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountID, trade->ExchangeID, trade->InstrumentID, (int)trade->ProductClass, trade->OrderID, trade->OrderSysID, trade->TradeID, (int)trade->Direction, (int)trade->OffsetFlag, GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (instrument != nullptr)
	{
		WriteLog(LogLevel::Info, "InstrumentField:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			instrument->ExchangeID, instrument->InstrumentID, instrument->ExchangeInstID, instrument->InstrumentName, instrument->ProductID, (int)instrument->ProductClass, instrument->VolumeMultiple, GetDoubleValue(instrument->PriceTick), instrument->MaxMarketOrderVolume, instrument->MinMarketOrderVolume, instrument->MaxLimitOrderVolume, instrument->MinLimitOrderVolume, instrument->SessionName);
	}
	else
	{
		WriteLog(LogLevel::Info, "instrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspInsertOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]",
			reqInsertOrder->AccountID, reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID, (int)reqInsertOrder->Direction, (int)reqInsertOrder->OffsetFlag, (int)reqInsertOrder->OrderPriceType, GetDoubleValue(reqInsertOrder->Price), reqInsertOrder->Volume, reqInsertOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			reqCancelOrder->AccountID, reqCancelOrder->ExchangeID, reqCancelOrder->InstrumentID, reqCancelOrder->ClientCancelOrderID, reqCancelOrder->OrderID, reqCancelOrder->OrderSysID, reqCancelOrder->SessionID, reqCancelOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRtnOrder(OrderField* order)
{
	WriteLog(LogLevel::Info, "OnRtnOrder");
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, (int)order->ProductClass, order->OrderID, order->OrderSysID, (int)order->Direction, (int)order->OffsetFlag, (int)order->OrderPriceType, GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, (int)order->OrderStatus, order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionID, order->ClientOrderID, order->RequestID, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRtnTrade(TradeField* trade)
{
	WriteLog(LogLevel::Info, "OnRtnTrade");
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountID, trade->ExchangeID, trade->InstrumentID, (int)trade->ProductClass, trade->OrderID, trade->OrderSysID, trade->TradeID, (int)trade->Direction, (int)trade->OffsetFlag, GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
}
