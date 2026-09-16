// 本文件由 ../Templates/Cpp/BackTestApi/BackTestApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "BackTestApiImpl.h"
#include "SimExchange.h"
#include "Config/Config.h"
#include "QuantTrading/Version.h"


using namespace QuantTrading;

static const char* ConfigName = "BackTest.json";

BackTestApi* BackTestApi::CreateBackTestApi()
{
	return new QuantTrading::BackTest::BackTestApiImpl();
}
const char* BackTestApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

namespace QuantTrading::BackTest
{
BackTestApiImpl::BackTestApiImpl()
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	simExchange = new SimExchange(config);
}
BackTestApiImpl::~BackTestApiImpl()
{
	if (simExchange != nullptr)
	{
		delete simExchange;
		simExchange = nullptr;
	}
}
bool BackTestApiImpl::Init()
{
	return simExchange->Init() && simExchange->Start();
}
void BackTestApiImpl::Join()
{
	if (simExchange != nullptr)
	{
		simExchange->Join();
	}
}
void BackTestApiImpl::Release()
{
	simExchange->Stop();
}
void BackTestApiImpl::RegisterFront(const char* address)
{
}
void BackTestApiImpl::RegisterSpi(BackTestSpi* pSpi)
{
	simExchange->RegisterSpi(pSpi);
}

int BackTestApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	return simExchange->ReqSubMarketData(reqSubMarketData, requestID);
}
int BackTestApiImpl::ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID)
{
	return simExchange->ReqSubMarketDataFinished(reqSubMarketDataFinished, requestID);
}
int BackTestApiImpl::ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestID)
{
	return simExchange->ReqRegisterAccount(reqRegisterAccount, requestID);
}
int BackTestApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return simExchange->ReqInsertOrder(reqInsertOrder, requestID);
}
int BackTestApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return simExchange->ReqCancelOrder(reqCancelOrder, requestID);
}
}
