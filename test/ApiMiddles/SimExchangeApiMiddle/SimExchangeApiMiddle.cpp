// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


namespace QuantTrading
{
SimExchangeApiMiddle* SimExchangeApiMiddle::CreateSimExchangeApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateSimExchangeApi");
	
	auto api = SimExchangeApi::CreateSimExchangeApi();
	auto apiMiddle = new SimExchangeApiMiddle();
	apiMiddle->simExchangeApi_ = api;
	
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
	return simExchangeApi_->Init();
}
void SimExchangeApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	simExchangeApi_->Join();
}
void SimExchangeApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	simExchangeApi_->Release();
}
void SimExchangeApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	simExchangeApi_->RegisterFront(address);
}
void SimExchangeApiMiddle::RegisterSpi(SimExchangeSpi* spi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	simExchangeApi_->RegisterSpi(spi);
}

int SimExchangeApiMiddle::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestId);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountId:[%s]",
			reqAccountLogin->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return simExchangeApi_->ReqAccountLogin(reqAccountLogin, requestId);
}
int SimExchangeApiMiddle::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	WriteLog(LogLevel::Info, "ReqAccountLogout: RequestID:%d", requestId);
	if (reqAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLogoutField:AccountId:[%s]",
			reqAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogout is nullptr");
	}
	return simExchangeApi_->ReqAccountLogout(reqAccountLogout, requestId);
}
int SimExchangeApiMiddle::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: RequestID:%d", requestId);
	if (reqQryOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOrderField:AccountId:[%s]",
			reqQryOrder->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOrder is nullptr");
	}
	return simExchangeApi_->ReqQryOrder(reqQryOrder, requestId);
}
int SimExchangeApiMiddle::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: RequestID:%d", requestId);
	if (reqQryTrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryTradeField:AccountId:[%s]",
			reqQryTrade->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryTrade is nullptr");
	}
	return simExchangeApi_->ReqQryTrade(reqQryTrade, requestId);
}
int SimExchangeApiMiddle::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: RequestID:%d", requestId);
	if (reqQryInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryInstrument->ExchangeId, reqQryInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryInstrument is nullptr");
	}
	return simExchangeApi_->ReqQryInstrument(reqQryInstrument, requestId);
}
int SimExchangeApiMiddle::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqInsertOrder: RequestID:%d", requestId);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), reqInsertOrder->Price, reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	return simExchangeApi_->ReqInsertOrder(reqInsertOrder, requestId);
}
int SimExchangeApiMiddle::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqCancelOrder: RequestID:%d", requestId);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	return simExchangeApi_->ReqCancelOrder(reqCancelOrder, requestId);
}
}
