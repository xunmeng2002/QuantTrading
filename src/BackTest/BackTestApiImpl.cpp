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
	simExchange_ = new SimExchange(config);
}
BackTestApiImpl::~BackTestApiImpl()
{
	if (simExchange_ != nullptr)
	{
		delete simExchange_;
		simExchange_ = nullptr;
	}
}
bool BackTestApiImpl::Init()
{
	return simExchange_->Init() && simExchange_->Start();
}
void BackTestApiImpl::Join()
{
	if (simExchange_ != nullptr)
	{
		simExchange_->Join();
	}
}
void BackTestApiImpl::Release()
{
	simExchange_->Stop();
}
void BackTestApiImpl::RegisterFront(const char* address)
{
}
void BackTestApiImpl::RegisterSpi(BackTestSpi* pSpi)
{
	simExchange_->RegisterSpi(pSpi);
}

int BackTestApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId)
{
	return simExchange_->ReqSubMarketData(reqSubMarketData, requestId);
}
int BackTestApiImpl::ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestId)
{
	return simExchange_->ReqSubMarketDataFinished(reqSubMarketDataFinished, requestId);
}
int BackTestApiImpl::ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestId)
{
	return simExchange_->ReqRegisterAccount(reqRegisterAccount, requestId);
}
int BackTestApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	return simExchange_->ReqInsertOrder(reqInsertOrder, requestId);
}
int BackTestApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	return simExchange_->ReqCancelOrder(reqCancelOrder, requestId);
}
}
