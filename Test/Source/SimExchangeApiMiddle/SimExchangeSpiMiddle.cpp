#include "SimExchangeSpiMiddle.h"
#include "Logger.h"
#include "TestUtility.h"


void SimExchangeSpiMiddle::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
}
void SimExchangeSpiMiddle::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void SimExchangeSpiMiddle::OnRspSEBrokerLogin(RspSEBrokerLoginField* rspSEBrokerLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSEBrokerLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspSEBrokerLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspSEBrokerLoginField:BrokerID:[%d], BrokerName:[%s], SessionID:[%lld], IPAddress:[%s]",
			rspSEBrokerLogin->BrokerID, rspSEBrokerLogin->BrokerName, rspSEBrokerLogin->SessionID, rspSEBrokerLogin->IPAddress);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspSEBrokerLogin is nullptr");
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
void SimExchangeSpiMiddle::OnRspSEBrokerLogout(RspSEBrokerLogoutField* rspSEBrokerLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSEBrokerLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspSEBrokerLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspSEBrokerLogoutField:BrokerID:[%d], SessionID:[%lld], IPAddress:[%s]",
			rspSEBrokerLogout->BrokerID, rspSEBrokerLogout->SessionID, rspSEBrokerLogout->IPAddress);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspSEBrokerLogout is nullptr");
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
void SimExchangeSpiMiddle::OnRspSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSEInsertOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqSEInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSEInsertOrderField:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]",
			reqSEInsertOrder->BrokerID, reqSEInsertOrder->AccountID, reqSEInsertOrder->ExchangeID, reqSEInsertOrder->InstrumentID, (int)reqSEInsertOrder->Direction, (int)reqSEInsertOrder->OffsetFlag, (int)reqSEInsertOrder->OrderPriceType, GetDoubleValue(reqSEInsertOrder->Price), reqSEInsertOrder->Volume, reqSEInsertOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSEInsertOrder is nullptr");
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
void SimExchangeSpiMiddle::OnRspSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSECancelOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqSECancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSECancelOrderField:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], ClientOrderID:[%d], SessionID:[%lld]",
			reqSECancelOrder->BrokerID, reqSECancelOrder->AccountID, reqSECancelOrder->ExchangeID, reqSECancelOrder->InstrumentID, reqSECancelOrder->CancelOrderID, reqSECancelOrder->OrderID, reqSECancelOrder->ClientOrderID, reqSECancelOrder->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSECancelOrder is nullptr");
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
void SimExchangeSpiMiddle::OnRspQrySEOrder(SEOrderField* sEOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySEOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (sEOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "SEOrderField:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			sEOrder->TradingDay, sEOrder->BrokerID, sEOrder->AccountID, sEOrder->ExchangeID, sEOrder->InstrumentID, (int)sEOrder->ProductClass, sEOrder->OrderID, (int)sEOrder->Direction, (int)sEOrder->OffsetFlag, (int)sEOrder->OrderPriceType, GetDoubleValue(sEOrder->Price), sEOrder->Volume, sEOrder->VolumeTotal, sEOrder->VolumeTraded, sEOrder->VolumeMultiple, (int)sEOrder->OrderStatus, sEOrder->OrderDate, sEOrder->OrderTime, sEOrder->CancelDate, sEOrder->CancelTime, sEOrder->SessionID, sEOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "sEOrder is nullptr");
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
void SimExchangeSpiMiddle::OnRspQrySETrade(SETradeField* sETrade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySETrade: RequestID:%d, IsLast:%d", requestID, isLast);
	if (sETrade != nullptr)
	{
		WriteLog(LogLevel::Info, "SETradeField:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			sETrade->TradingDay, sETrade->BrokerID, sETrade->AccountID, sETrade->ExchangeID, sETrade->InstrumentID, (int)sETrade->ProductClass, sETrade->OrderID, sETrade->TradeID, (int)sETrade->Direction, (int)sETrade->OffsetFlag, GetDoubleValue(sETrade->Price), sETrade->Volume, sETrade->VolumeMultiple, GetDoubleValue(sETrade->TradeAmount), GetDoubleValue(sETrade->Commission), sETrade->TradeDate, sETrade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "sETrade is nullptr");
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
void SimExchangeSpiMiddle::OnRspQrySEInstrument(SEInstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySEInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (sEInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "SEInstrumentField:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], VolumeMultiple:[%d], PriceTick:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f]",
			sEInstrument->ExchangeID, sEInstrument->InstrumentID, sEInstrument->ExchangeInstID, sEInstrument->InstrumentName, sEInstrument->ProductID, (int)sEInstrument->ProductClass, sEInstrument->MaxMarketOrderVolume, sEInstrument->MinMarketOrderVolume, sEInstrument->MaxLimitOrderVolume, sEInstrument->MinLimitOrderVolume, sEInstrument->VolumeMultiple, GetDoubleValue(sEInstrument->PriceTick), GetDoubleValue(sEInstrument->UpperLimitPrice), GetDoubleValue(sEInstrument->LowerLimitPrice));
	}
	else
	{
		WriteLog(LogLevel::Info, "sEInstrument is nullptr");
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
void SimExchangeSpiMiddle::OnRtnSEOrder(SEOrderField* sEOrder)
{
	WriteLog(LogLevel::Info, "OnRtnSEOrder");
	if (sEOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "SEOrderField:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			sEOrder->TradingDay, sEOrder->BrokerID, sEOrder->AccountID, sEOrder->ExchangeID, sEOrder->InstrumentID, (int)sEOrder->ProductClass, sEOrder->OrderID, (int)sEOrder->Direction, (int)sEOrder->OffsetFlag, (int)sEOrder->OrderPriceType, GetDoubleValue(sEOrder->Price), sEOrder->Volume, sEOrder->VolumeTotal, sEOrder->VolumeTraded, sEOrder->VolumeMultiple, (int)sEOrder->OrderStatus, sEOrder->OrderDate, sEOrder->OrderTime, sEOrder->CancelDate, sEOrder->CancelTime, sEOrder->SessionID, sEOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "sEOrder is nullptr");
	}
}
void SimExchangeSpiMiddle::OnRtnSETrade(SETradeField* sETrade)
{
	WriteLog(LogLevel::Info, "OnRtnSETrade");
	if (sETrade != nullptr)
	{
		WriteLog(LogLevel::Info, "SETradeField:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			sETrade->TradingDay, sETrade->BrokerID, sETrade->AccountID, sETrade->ExchangeID, sETrade->InstrumentID, (int)sETrade->ProductClass, sETrade->OrderID, sETrade->TradeID, (int)sETrade->Direction, (int)sETrade->OffsetFlag, GetDoubleValue(sETrade->Price), sETrade->Volume, sETrade->VolumeMultiple, GetDoubleValue(sETrade->TradeAmount), GetDoubleValue(sETrade->Commission), sETrade->TradeDate, sETrade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "sETrade is nullptr");
	}
}
