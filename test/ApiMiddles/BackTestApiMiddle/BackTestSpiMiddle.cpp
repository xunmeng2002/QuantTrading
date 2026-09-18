// 本文件由 ../Templates/Cpp/ApiTest/SpiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "BackTestSpiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;

namespace QuantTrading
{
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

void BackTestSpiMiddle::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSubMarketData: RequestId:%d, IsLast:%d", requestId, isLast);
	if (rspSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "RspSubMarketDataField:ExchangeId:[%s], InstrumentId:[%s]",
			rspSubMarketData->ExchangeId, rspSubMarketData->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspSubMarketData is nullptr");
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
void BackTestSpiMiddle::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnDepthMarketData");
	if (depthMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "DepthMarketDataField:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			depthMarketData->TradingDay, depthMarketData->ExchangeId, depthMarketData->InstrumentId, depthMarketData->UpdateTs, GetDoubleValue(depthMarketData->LastPrice), GetDoubleValue(depthMarketData->PreSettlementPrice), GetDoubleValue(depthMarketData->PreClosePrice), GetDoubleValue(depthMarketData->PreOpenInterest), GetDoubleValue(depthMarketData->OpenPrice), GetDoubleValue(depthMarketData->HighestPrice), GetDoubleValue(depthMarketData->LowestPrice), GetDoubleValue(depthMarketData->ClosePrice), depthMarketData->CurrVolume, depthMarketData->Volume, GetDoubleValue(depthMarketData->CurrTurnover), GetDoubleValue(depthMarketData->Turnover), GetDoubleValue(depthMarketData->OpenInterest), GetDoubleValue(depthMarketData->SettlementPrice), GetDoubleValue(depthMarketData->UpperLimitPrice), GetDoubleValue(depthMarketData->LowerLimitPrice), GetDoubleValue(depthMarketData->AveragePrice), GetDoubleValue(depthMarketData->AskPrice1), GetDoubleValue(depthMarketData->AskPrice2), GetDoubleValue(depthMarketData->AskPrice3), GetDoubleValue(depthMarketData->AskPrice4), GetDoubleValue(depthMarketData->AskPrice5), GetDoubleValue(depthMarketData->AskPrice6), GetDoubleValue(depthMarketData->AskPrice7), GetDoubleValue(depthMarketData->AskPrice8), GetDoubleValue(depthMarketData->AskPrice9), GetDoubleValue(depthMarketData->AskPrice10), depthMarketData->AskVolume1, depthMarketData->AskVolume2, depthMarketData->AskVolume3, depthMarketData->AskVolume4, depthMarketData->AskVolume5, depthMarketData->AskVolume6, depthMarketData->AskVolume7, depthMarketData->AskVolume8, depthMarketData->AskVolume9, depthMarketData->AskVolume10, GetDoubleValue(depthMarketData->BidPrice1), GetDoubleValue(depthMarketData->BidPrice2), GetDoubleValue(depthMarketData->BidPrice3), GetDoubleValue(depthMarketData->BidPrice4), GetDoubleValue(depthMarketData->BidPrice5), GetDoubleValue(depthMarketData->BidPrice6), GetDoubleValue(depthMarketData->BidPrice7), GetDoubleValue(depthMarketData->BidPrice8), GetDoubleValue(depthMarketData->BidPrice9), GetDoubleValue(depthMarketData->BidPrice10), depthMarketData->BidVolume1, depthMarketData->BidVolume2, depthMarketData->BidVolume3, depthMarketData->BidVolume4, depthMarketData->BidVolume5, depthMarketData->BidVolume6, depthMarketData->BidVolume7, depthMarketData->BidVolume8, depthMarketData->BidVolume9, depthMarketData->BidVolume10);
	}
	else
	{
		WriteLog(LogLevel::Info, "depthMarketData is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnBarMarketData");
	if (barMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "BarMarketDataField:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			barMarketData->TradingDay, barMarketData->ExchangeId, barMarketData->InstrumentId, static_cast<int>(barMarketData->BarPreces), barMarketData->BarPeriod, barMarketData->BarTime, barMarketData->UpdateTs, GetDoubleValue(barMarketData->PreSettlementPrice), GetDoubleValue(barMarketData->PreClosePrice), GetDoubleValue(barMarketData->HighestPrice), GetDoubleValue(barMarketData->LowestPrice), GetDoubleValue(barMarketData->Open), GetDoubleValue(barMarketData->High), GetDoubleValue(barMarketData->Low), GetDoubleValue(barMarketData->Close), barMarketData->CurrVolume, barMarketData->Volume, GetDoubleValue(barMarketData->CurrTurnover), GetDoubleValue(barMarketData->Turnover), GetDoubleValue(barMarketData->OpenInterest));
	}
	else
	{
		WriteLog(LogLevel::Info, "barMarketData is nullptr");
	}
}
void BackTestSpiMiddle::OnRtnSessionBegin(const SessionBeginField* sessionBegin)
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
void BackTestSpiMiddle::OnRtnSessionEnd(const SessionEndField* sessionEnd)
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
void BackTestSpiMiddle::OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd)
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
void BackTestSpiMiddle::OnRspRegisterAccount(const RspRegisterAccountField* rspRegisterAccount, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspRegisterAccount: RequestId:%d, IsLast:%d", requestId, isLast);
	if (rspRegisterAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "RspRegisterAccountField:AccountId:[%s]",
			rspRegisterAccount->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspRegisterAccount is nullptr");
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
void BackTestSpiMiddle::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspInsertOrder: RequestId:%d, IsLast:%d", requestId, isLast);
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
void BackTestSpiMiddle::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOrder: RequestId:%d, IsLast:%d", requestId, isLast);
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
void BackTestSpiMiddle::OnRtnOrder(const OrderField* order)
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
void BackTestSpiMiddle::OnRtnTrade(const TradeField* trade)
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
