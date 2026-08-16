#include "TraderApiBase.h"
#include "QuantTrading/Version.h"

const char* TraderApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

TraderApiBase::TraderApiBase()
	:ApiBase("TraderApi"), m_TraderSpi(nullptr), m_SessionID(0)
{
}
TraderApiBase::~TraderApiBase()
{
}

void TraderApiBase::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = sessionID;
	m_TraderSpi->OnConnected();
}
void TraderApiBase::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = -1;
	m_TraderSpi->OnDisConnected();
}

bool TraderApiBase::Init()
{
	return m_Protocol->Init() && m_Protocol->Start();
}
void TraderApiBase::Join()
{
	m_Protocol->Join();
}
void TraderApiBase::Release()
{
	m_Protocol->Stop();
	m_Protocol->Join();
	delete this;
}
void TraderApiBase::RegisterFront(const char* address)
{
	m_Protocol->RegisterFront(address);
}
void TraderApiBase::RegisterSpi(TraderSpi* spi)
{
	m_TraderSpi = spi;
}
