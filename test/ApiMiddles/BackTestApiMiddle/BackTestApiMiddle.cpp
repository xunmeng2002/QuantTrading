#include "BackTestApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>



BackTestApiMiddle* BackTestApiMiddle::CreateBackTestApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateBackTestApi");
	
	auto api = BackTestApi::CreateBackTestApi();
	auto apiMiddle = new BackTestApiMiddle();
	apiMiddle->m_BackTestApi = api;
	
	return apiMiddle;
}
const char* BackTestApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return BackTestApi::GetApiVersion();
}
bool BackTestApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return m_BackTestApi->Init();
}
void BackTestApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	m_BackTestApi->Join();
}
void BackTestApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	m_BackTestApi->Release();
}
void BackTestApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	m_BackTestApi->RegisterFront(address);
}
void BackTestApiMiddle::RegisterSpi(BackTestSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	m_BackTestApi->RegisterSpi(pSpi);
}

int BackTestApiMiddle::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSubMarketData: RequestID:%d", requestID);
	if (reqSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			reqSubMarketData->ExchangeID, reqSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketData is nullptr");
	}
	return m_BackTestApi->ReqSubMarketData(reqSubMarketData, requestID);
}
int BackTestApiMiddle::ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSubMarketDataFinished: RequestID:%d", requestID);
	if (reqSubMarketDataFinished != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataFinishedField:SessionID:[%lld]",
			reqSubMarketDataFinished->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketDataFinished is nullptr");
	}
	return m_BackTestApi->ReqSubMarketDataFinished(reqSubMarketDataFinished, requestID);
}
int BackTestApiMiddle::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
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
	return m_BackTestApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int BackTestApiMiddle::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
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
	return m_BackTestApi->ReqCancelOrder(reqCancelOrder, requestID);
}
