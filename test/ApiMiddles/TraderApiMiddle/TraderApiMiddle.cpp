#include "TraderApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;


namespace quanttrading
{
TraderApiMiddle* TraderApiMiddle::CreateTraderApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateTraderApi");
	
	auto api = TraderApi::CreateTraderApi();
	auto apiMiddle = new TraderApiMiddle();
	apiMiddle->m_TraderApi = api;
	
	return apiMiddle;
}
const char* TraderApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return TraderApi::GetApiVersion();
}
bool TraderApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return m_TraderApi->Init();
}
void TraderApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	m_TraderApi->Join();
}
void TraderApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	m_TraderApi->Release();
}
void TraderApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	m_TraderApi->RegisterFront(address);
}
void TraderApiMiddle::RegisterSpi(TraderSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	m_TraderApi->RegisterSpi(pSpi);
}

int TraderApiMiddle::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestID);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountID:[%s]",
			reqAccountLogin->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return m_TraderApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int TraderApiMiddle::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogout: RequestID:%d", requestID);
	if (reqAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLogoutField:AccountID:[%s]",
			reqAccountLogout->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogout is nullptr");
	}
	return m_TraderApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int TraderApiMiddle::ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryHolderAccount: RequestID:%d", requestID);
	if (reqQryHolderAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryHolderAccountField:AccountID:[%s]",
			reqQryHolderAccount->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryHolderAccount is nullptr");
	}
	return m_TraderApi->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
int TraderApiMiddle::ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryCapital: RequestID:%d", requestID);
	if (reqQryCapital != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCapitalField:AccountID:[%s]",
			reqQryCapital->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCapital is nullptr");
	}
	return m_TraderApi->ReqQryCapital(reqQryCapital, requestID);
}
int TraderApiMiddle::ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryPosition: RequestID:%d", requestID);
	if (reqQryPosition != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryPositionField:AccountID:[%s]",
			reqQryPosition->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryPosition is nullptr");
	}
	return m_TraderApi->ReqQryPosition(reqQryPosition, requestID);
}
int TraderApiMiddle::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: RequestID:%d", requestID);
	if (reqQryOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOrderField:AccountID:[%s]",
			reqQryOrder->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOrder is nullptr");
	}
	return m_TraderApi->ReqQryOrder(reqQryOrder, requestID);
}
int TraderApiMiddle::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: RequestID:%d", requestID);
	if (reqQryTrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryTradeField:AccountID:[%s]",
			reqQryTrade->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryTrade is nullptr");
	}
	return m_TraderApi->ReqQryTrade(reqQryTrade, requestID);
}
int TraderApiMiddle::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: RequestID:%d", requestID);
	if (reqQryInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryInstrumentField:ExchangeID:[%s], InstrumentID:[%s]",
			reqQryInstrument->ExchangeID, reqQryInstrument->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryInstrument is nullptr");
	}
	return m_TraderApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int TraderApiMiddle::ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrument: RequestID:%d", requestID);
	if (reqQryOptionInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOptionInstrumentField:ExchangeID:[%s], InstrumentID:[%s]",
			reqQryOptionInstrument->ExchangeID, reqQryOptionInstrument->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOptionInstrument is nullptr");
	}
	return m_TraderApi->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
int TraderApiMiddle::ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryCommissionRate: RequestID:%d", requestID);
	if (reqQryCommissionRate != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCommissionRateField:AccountID:[%s], ExchangeID:[%s], ProductClass:[%d]",
			reqQryCommissionRate->AccountID, reqQryCommissionRate->ExchangeID, (int)reqQryCommissionRate->ProductClass);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCommissionRate is nullptr");
	}
	return m_TraderApi->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
int TraderApiMiddle::ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryMoneyTransfer: RequestID:%d", requestID);
	if (reqQryMoneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryMoneyTransferField:AccountID:[%s]",
			reqQryMoneyTransfer->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryMoneyTransfer is nullptr");
	}
	return m_TraderApi->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
int TraderApiMiddle::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqInsertOrder: RequestID:%d", requestID);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]",
			reqInsertOrder->AccountID, reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID, (int)reqInsertOrder->Direction, (int)reqInsertOrder->OffsetFlag, (int)reqInsertOrder->OrderPriceType, reqInsertOrder->Price, reqInsertOrder->Volume, reqInsertOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	return m_TraderApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int TraderApiMiddle::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqCancelOrder: RequestID:%d", requestID);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			reqCancelOrder->AccountID, reqCancelOrder->ExchangeID, reqCancelOrder->InstrumentID, reqCancelOrder->ClientCancelOrderID, reqCancelOrder->OrderID, reqCancelOrder->OrderSysID, reqCancelOrder->SessionID, reqCancelOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	return m_TraderApi->ReqCancelOrder(reqCancelOrder, requestID);
}
}
