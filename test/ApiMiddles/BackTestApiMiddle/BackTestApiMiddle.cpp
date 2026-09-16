// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "BackTestApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


namespace QuantTrading
{
BackTestApiMiddle* BackTestApiMiddle::CreateBackTestApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateBackTestApi");
	
	auto api = BackTestApi::CreateBackTestApi();
	auto apiMiddle = new BackTestApiMiddle();
	apiMiddle->backTestApi_ = api;
	
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
	return backTestApi_->Init();
}
void BackTestApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	backTestApi_->Join();
}
void BackTestApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	backTestApi_->Release();
}
void BackTestApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	backTestApi_->RegisterFront(address);
}
void BackTestApiMiddle::RegisterSpi(BackTestSpi* spi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	backTestApi_->RegisterSpi(spi);
}

int BackTestApiMiddle::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId)
{
	WriteLog(LogLevel::Info, "ReqSubMarketData: RequestID:%d", requestId);
	if (reqSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataField:ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d]",
			reqSubMarketData->ExchangeId, reqSubMarketData->InstrumentId, static_cast<int>(reqSubMarketData->BarPreces), reqSubMarketData->BarPeriod);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketData is nullptr");
	}
	return backTestApi_->ReqSubMarketData(reqSubMarketData, requestId);
}
int BackTestApiMiddle::ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestId)
{
	WriteLog(LogLevel::Info, "ReqSubMarketDataFinished: RequestID:%d", requestId);
	if (reqSubMarketDataFinished != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataFinishedField:SessionId:[%lld]",
			reqSubMarketDataFinished->SessionId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketDataFinished is nullptr");
	}
	return backTestApi_->ReqSubMarketDataFinished(reqSubMarketDataFinished, requestId);
}
int BackTestApiMiddle::ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestId)
{
	WriteLog(LogLevel::Info, "ReqRegisterAccount: RequestID:%d", requestId);
	if (reqRegisterAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqRegisterAccountField:AccountId:[%s]",
			reqRegisterAccount->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqRegisterAccount is nullptr");
	}
	return backTestApi_->ReqRegisterAccount(reqRegisterAccount, requestId);
}
int BackTestApiMiddle::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
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
	return backTestApi_->ReqInsertOrder(reqInsertOrder, requestId);
}
int BackTestApiMiddle::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
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
	return backTestApi_->ReqCancelOrder(reqCancelOrder, requestId);
}
}
