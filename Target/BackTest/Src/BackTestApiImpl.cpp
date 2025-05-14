#include "BackTestApiImpl.h"
#include "SimExchange.h"
#include "Config.h"
#include "Logger.h"

using namespace std;

extern const char* Version;
const char* ConfigName = "BackTest.json";

BackTestApi* BackTestApi::CreateBackTestApi()
{
	return new BackTestApiImpl();
}
const char* BackTestApi::GetApiVersion()
{
	return Version;
}

BackTestApiImpl::BackTestApiImpl()
{
	Logger::GetInstance().Init("BackTest");
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();
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
void BackTestApiImpl::Init()
{
	m_SimExchange->Init();
	m_SimExchange->Start();
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
	Logger::GetInstance().Stop();
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

