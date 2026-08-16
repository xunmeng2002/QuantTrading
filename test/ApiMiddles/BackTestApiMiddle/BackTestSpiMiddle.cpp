#include "BackTestSpiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

double GetDoubleValue(const double& value)
{
    if (value == std::numeric_limits<double>::max())
    {
        return 0.0;
    }
    return value;
}


void BackTestSpiMiddle::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
}
void BackTestSpiMiddle::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void BackTestSpiMiddle::OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSubMarketData: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "RspSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			rspSubMarketData->ExchangeID, rspSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspSubMarketData is nullptr");
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
void BackTestSpiMiddle::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnDepthMarketData");
	if (depthMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "DepthMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			depthMarketData->TradingDay, depthMarketData->ExchangeID, depthMarketData->InstrumentID, depthMarketData->UpdateTs, GetDoubleValue(depthMarketData->LastPrice), GetDoubleValue(depthMarketData->PreSettlementPrice), GetDoubleValue(depthMarketData->PreClosePrice), GetDoubleValue(depthMarketData->PreOpenInterest), GetDoubleValue(depthMarketData->OpenPrice), GetDoubleValue(depthMarketData->HighestPrice), GetDoubleValue(depthMarketData->LowestPrice), GetDoubleValue(depthMarketData->ClosePrice), depthMarketData->CurrVolume, depthMarketData->Volume, GetDoubleValue(depthMarketData->CurrTurnover), GetDoubleValue(depthMarketData->Turnover), GetDoubleValue(depthMarketData->OpenInterest), GetDoubleValue(depthMarketData->SettlementPrice), GetDoubleValue(depthMarketData->UpperLimitPrice), GetDoubleValue(depthMarketData->LowerLimitPrice), GetDoubleValue(depthMarketData->AveragePrice), GetDoubleValue(depthMarketData->AskPrice1), GetDoubleValue(depthMarketData->AskPrice2), GetDoubleValue(depthMarketData->AskPrice3), GetDoubleValue(depthMarketData->AskPrice4), GetDoubleValue(depthMarketData->AskPrice5), GetDoubleValue(depthMarketData->AskPrice6), GetDoubleValue(depthMarketData->AskPrice7), GetDoubleValue(depthMarketData->AskPrice8), GetDoubleValue(depthMarketData->AskPrice9), GetDoubleValue(depthMarketData->AskPrice10), depthMarketData->AskVolume1, depthMarketData->AskVolume2, depthMarketData->AskVolume3, depthMarketData->AskVolume4, depthMarketData->AskVolume5, depthMarketData->AskVolume6, depthMarketData->AskVolume7, depthMarketData->AskVolume8, depthMarketData->AskVolume9, depthMarketData->AskVolume10, GetDoubleValue(depthMarketData->BidPrice1), GetDoubleValue(depthMarketData->BidPrice2), GetDoubleValue(depthMarketData->BidPrice3), GetDoubleValue(depthMarketData->BidPrice4), GetDoubleValue(depthMarketData->BidPrice5), GetDoubleValue(depthMarketData->BidPrice6), GetDoubleValue(depthMarketData->BidPrice7), GetDoubleValue(depthMarketData->BidPrice8), GetDoubleValue(depthMarketData->BidPrice9), GetDoubleValue(depthMarketData->BidPrice10), depthMarketData->BidVolume1, depthMarketData->BidVolume2, depthMarketData->BidVolume3, depthMarketData->BidVolume4, depthMarketData->BidVolume5, depthMarketData->BidVolume6, depthMarketData->BidVolume7, depthMarketData->BidVolume8, depthMarketData->BidVolume9, depthMarketData->BidVolume10);
	}
	else
	{
		WriteLog(LogLevel::Info, "depthMarketData is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnBarMarketData(BarMarketDataField* barMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnBarMarketData");
	if (barMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "BarMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			barMarketData->TradingDay, barMarketData->ExchangeID, barMarketData->InstrumentID, (int)barMarketData->BarPreces, barMarketData->BarPeriod, barMarketData->BarTime, barMarketData->UpdateTs, GetDoubleValue(barMarketData->PreSettlementPrice), GetDoubleValue(barMarketData->PreClosePrice), GetDoubleValue(barMarketData->HighestPrice), GetDoubleValue(barMarketData->LowestPrice), GetDoubleValue(barMarketData->Open), GetDoubleValue(barMarketData->High), GetDoubleValue(barMarketData->Low), GetDoubleValue(barMarketData->Close), barMarketData->CurrVolume, barMarketData->Volume, GetDoubleValue(barMarketData->CurrTurnover), GetDoubleValue(barMarketData->Turnover), GetDoubleValue(barMarketData->OpenInterest));
	}
	else
	{
		WriteLog(LogLevel::Info, "barMarketData is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnSessionBegin(SessionBeginField* sessionBegin)
{
	WriteLog(LogLevel::Info, "OnRtnSessionBegin");
	if (sessionBegin != nullptr)
	{
		WriteLog(LogLevel::Info, "SessionBeginField:TradingDay:[%s]",
			sessionBegin->TradingDay);
	}
	else
	{
		WriteLog(LogLevel::Info, "sessionBegin is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnSessionEnd(SessionEndField* sessionEnd)
{
	WriteLog(LogLevel::Info, "OnRtnSessionEnd");
	if (sessionEnd != nullptr)
	{
		WriteLog(LogLevel::Info, "SessionEndField:TradingDay:[%s]",
			sessionEnd->TradingDay);
	}
	else
	{
		WriteLog(LogLevel::Info, "sessionEnd is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnMarketDataEnd(MarketDataEndField* marketDataEnd)
{
	WriteLog(LogLevel::Info, "OnRtnMarketDataEnd");
	if (marketDataEnd != nullptr)
	{
		WriteLog(LogLevel::Info, "MarketDataEndField:TradingDay:[%s]",
			marketDataEnd->TradingDay);
	}
	else
	{
		WriteLog(LogLevel::Info, "marketDataEnd is nullptr");
	}
}
void BackTestSpiMiddle::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
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
void BackTestSpiMiddle::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
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
void BackTestSpiMiddle::OnRtnOrder(OrderField* order)
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
void BackTestSpiMiddle::OnRtnTrade(TradeField* trade)
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
