// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::core;


namespace QuantTrading
{
SimExchangeApiMiddle* SimExchangeApiMiddle::CreateSimExchangeApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateSimExchangeApi");
	
	auto api = SimExchangeApi::CreateSimExchangeApi();
	auto apiMiddle = new SimExchangeApiMiddle();
	apiMiddle->simExchangeApi = api;
	
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
	return simExchangeApi->Init();
}
void SimExchangeApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	simExchangeApi->Join();
}
void SimExchangeApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	simExchangeApi->Release();
}
void SimExchangeApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	simExchangeApi->RegisterFront(address);
}
void SimExchangeApiMiddle::RegisterSpi(SimExchangeSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	simExchangeApi->RegisterSpi(pSpi);
}

int SimExchangeApiMiddle::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestID);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountId:[%s]",
			reqAccountLogin->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return simExchangeApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int SimExchangeApiMiddle::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogout: RequestID:%d", requestID);
	if (reqAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLogoutField:AccountId:[%s]",
			reqAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogout is nullptr");
	}
	return simExchangeApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int SimExchangeApiMiddle::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: RequestID:%d", requestID);
	if (reqQryOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOrderField:AccountId:[%s]",
			reqQryOrder->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOrder is nullptr");
	}
	return simExchangeApi->ReqQryOrder(reqQryOrder, requestID);
}
int SimExchangeApiMiddle::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: RequestID:%d", requestID);
	if (reqQryTrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryTradeField:AccountId:[%s]",
			reqQryTrade->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryTrade is nullptr");
	}
	return simExchangeApi->ReqQryTrade(reqQryTrade, requestID);
}
int SimExchangeApiMiddle::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: RequestID:%d", requestID);
	if (reqQryInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryInstrument->ExchangeId, reqQryInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryInstrument is nullptr");
	}
	return simExchangeApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int SimExchangeApiMiddle::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqInsertOrder: RequestID:%d", requestID);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), reqInsertOrder->Price, reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	return simExchangeApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int SimExchangeApiMiddle::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqCancelOrder: RequestID:%d", requestID);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	return simExchangeApi->ReqCancelOrder(reqCancelOrder, requestID);
}
}
