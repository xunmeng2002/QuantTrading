#include "BackTestApiImpl.h"
#include "SimExchange.h"
#include "Config/Config.h"
#include "QuantTrading/Version.h"


using namespace std;

static const char* ConfigName = "BackTest.json";

BackTestApi* BackTestApi::CreateBackTestApi()
{
	return new BackTestApiImpl();
}
const char* BackTestApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

BackTestApiImpl::BackTestApiImpl()
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	m_SimExchange = new SimExchange(config);
}
BackTestApiImpl::~BackTestApiImpl()
{
	if (m_SimExchange != nullptr)
	{
		delete m_SimExchange;
		m_SimExchange = nullptr;
	}
}
bool BackTestApiImpl::Init()
{
	return m_SimExchange->Init() && m_SimExchange->Start();
}
void BackTestApiImpl::Join()
{
	if (m_SimExchange != nullptr)
	{
		m_SimExchange->Join();
	}
}
void BackTestApiImpl::Release()
{
	m_SimExchange->Stop();
}
void BackTestApiImpl::RegisterFront(const char* address)
{
}
void BackTestApiImpl::RegisterSpi(BackTestSpi* pSpi)
{
	m_SimExchange->RegisterSpi(pSpi);
}

int BackTestApiImpl::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	return m_SimExchange->ReqSubMarketData(reqSubMarketData, requestID);
}
int BackTestApiImpl::ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID)
{
	return m_SimExchange->ReqSubMarketDataFinished(reqSubMarketDataFinished, requestID);
}
int BackTestApiImpl::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return m_SimExchange->ReqInsertOrder(reqInsertOrder, requestID);
}
int BackTestApiImpl::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return m_SimExchange->ReqCancelOrder(reqCancelOrder, requestID);
}

