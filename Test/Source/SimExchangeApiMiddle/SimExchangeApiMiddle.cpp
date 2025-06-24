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
void SimExchangeApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	m_SimExchangeApi->Init();
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

int SimExchangeApiMiddle::ReqSEBrokerLogin(ReqSEBrokerLoginField* reqSEBrokerLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSEBrokerLogin: RequestID:%d", requestID);
	if (reqSEBrokerLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSEBrokerLoginField:BrokerID:[%d], Password:[%s]",
			reqSEBrokerLogin->BrokerID, reqSEBrokerLogin->Password);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSEBrokerLogin is nullptr");
	}
	return m_SimExchangeApi->ReqSEBrokerLogin(reqSEBrokerLogin, requestID);
}
int SimExchangeApiMiddle::ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSEInsertOrder: RequestID:%d", requestID);
	if (reqSEInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSEInsertOrderField:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]",
			reqSEInsertOrder->BrokerID, reqSEInsertOrder->AccountID, reqSEInsertOrder->ExchangeID, reqSEInsertOrder->InstrumentID, (int)reqSEInsertOrder->Direction, (int)reqSEInsertOrder->OffsetFlag, (int)reqSEInsertOrder->OrderPriceType, reqSEInsertOrder->Price, reqSEInsertOrder->Volume, reqSEInsertOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSEInsertOrder is nullptr");
	}
	return m_SimExchangeApi->ReqSEInsertOrder(reqSEInsertOrder, requestID);
}
int SimExchangeApiMiddle::ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSECancelOrder: RequestID:%d", requestID);
	if (reqSECancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSECancelOrderField:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], ClientOrderID:[%d], SessionID:[%lld]",
			reqSECancelOrder->BrokerID, reqSECancelOrder->AccountID, reqSECancelOrder->ExchangeID, reqSECancelOrder->InstrumentID, reqSECancelOrder->CancelOrderID, reqSECancelOrder->OrderID, reqSECancelOrder->ClientOrderID, reqSECancelOrder->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSECancelOrder is nullptr");
	}
	return m_SimExchangeApi->ReqSECancelOrder(reqSECancelOrder, requestID);
}
int SimExchangeApiMiddle::ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQrySEOrder: RequestID:%d", requestID);
	if (reqQrySEOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQrySEOrderField:AccountID:[%s]",
			reqQrySEOrder->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQrySEOrder is nullptr");
	}
	return m_SimExchangeApi->ReqQrySEOrder(reqQrySEOrder, requestID);
}
int SimExchangeApiMiddle::ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQrySETrade: RequestID:%d", requestID);
	if (reqQrySETrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQrySETradeField:AccountID:[%s]",
			reqQrySETrade->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQrySETrade is nullptr");
	}
	return m_SimExchangeApi->ReqQrySETrade(reqQrySETrade, requestID);
}
int SimExchangeApiMiddle::ReqQrySEInstrument(ReqQrySEInstrumentField* reqQrySEInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQrySEInstrument: RequestID:%d", requestID);
	if (reqQrySEInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQrySEInstrumentField:ExchangeID:[%s], InstrumentID:[%s]",
			reqQrySEInstrument->ExchangeID, reqQrySEInstrument->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQrySEInstrument is nullptr");
	}
	return m_SimExchangeApi->ReqQrySEInstrument(reqQrySEInstrument, requestID);
}
