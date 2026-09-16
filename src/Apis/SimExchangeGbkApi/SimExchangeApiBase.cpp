// 本文件由 ../Templates/Cpp/Api/ApiBase.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeApiBase.h"
#include "QuantTrading/Version.h"

namespace QuantTrading
{
const char* SimExchangeApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

SimExchangeApiBase::SimExchangeApiBase()
	:ApiBase("SimExchangeApi"), simExchangeSpi(nullptr), sessionId_(0)
{
}
SimExchangeApiBase::~SimExchangeApiBase()
{
}

void SimExchangeApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (simExchangeSpi != nullptr)
	{
		simExchangeSpi->OnConnected();
	}
}
void SimExchangeApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (simExchangeSpi != nullptr)
	{
		simExchangeSpi->OnDisConnected();
	}
}

bool SimExchangeApiBase::Init()
{
	return m_Protocol->Init() && m_Protocol->Start();
}
void SimExchangeApiBase::Join()
{
	m_Protocol->Join();
}
void SimExchangeApiBase::Release()
{
	m_Protocol->Stop();
	m_Protocol->Join();
	delete this;
}
void SimExchangeApiBase::RegisterFront(const char* address)
{
	m_Protocol->RegisterFront(address);
}
void SimExchangeApiBase::RegisterSpi(SimExchangeSpi* spi)
{
	simExchangeSpi = spi;
}
}
