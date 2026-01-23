#include "SimExchangeApiMiddle.h"
#include "Logger.h"



SimExchangeApiMiddle* SimExchangeApiMiddle::CreateSimExchangeApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateSimExchangeApi");
	
	auto api = SimExchangeApi::CreateSimExchangeApi();
	auto apiMiddle = new SimExchangeApiMiddle();
	apiMiddle->m_SimExchangeApi = api;
	
	return apiMiddle;
}
const char* SimExchangeApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return SimExchangeApi::GetApiVersion();
}
bool SimExchangeApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return m_SimExchangeApi->Init();
}
void SimExchangeApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	m_SimExchangeApi->Join();
}
void SimExchangeApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	m_SimExchangeApi->Release();
}
void SimExchangeApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	m_SimExchangeApi->RegisterFront(address);
}
void SimExchangeApiMiddle::RegisterSpi(SimExchangeSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	m_SimExchangeApi->RegisterSpi(pSpi);
}

int SimExchangeApiMiddle::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestID);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountID:[%s], Password:[%s]",
			reqAccountLogin->AccountID, reqAccountLogin->Password);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return m_SimExchangeApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int SimExchangeApiMiddle::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
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
	return m_SimExchangeApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int SimExchangeApiMiddle::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
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
	return m_SimExchangeApi->ReqQryOrder(reqQryOrder, requestID);
}
int SimExchangeApiMiddle::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
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
	return m_SimExchangeApi->ReqQryTrade(reqQryTrade, requestID);
}
int SimExchangeApiMiddle::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
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
	return m_SimExchangeApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int SimExchangeApiMiddle::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
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
	return m_SimExchangeApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int SimExchangeApiMiddle::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
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
	return m_SimExchangeApi->ReqCancelOrder(reqCancelOrder, requestID);
}
