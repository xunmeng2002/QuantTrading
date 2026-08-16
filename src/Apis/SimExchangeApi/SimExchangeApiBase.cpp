#include "SimExchangeApiBase.h"
#include "QuantTrading/Version.h"

const char* SimExchangeApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

SimExchangeApiBase::SimExchangeApiBase()
	:ApiBase("SimExchangeApi"), m_SimExchangeSpi(nullptr), m_SessionID(0)
{
}
SimExchangeApiBase::~SimExchangeApiBase()
{
}

void SimExchangeApiBase::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = sessionID;
	m_SimExchangeSpi->OnConnected();
}
void SimExchangeApiBase::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = -1;
	m_SimExchangeSpi->OnDisConnected();
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
	m_SimExchangeSpi = spi;
}
