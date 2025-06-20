#include "TradeApiBase.h"
#include "TcpSelectClient.h"

extern const char* Version;

const char* TradeApi::GetApiVersion()
{
	return Version;
}

TradeApiBase::TradeApiBase()
	:ApiBase("TradeApi"), m_TradeSpi(nullptr), m_SessionID(0)
{
}
TradeApiBase::~TradeApiBase()
{
}

void TradeApiBase::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = sessionID;
	m_TradeSpi->OnConnected();
}
void TradeApiBase::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = -1;
	m_TradeSpi->OnDisConnected();
}

void TradeApiBase::Init()
{
	m_Protocol->Init();
	m_Protocol->Start();
}
void TradeApiBase::Join()
{
	m_Protocol->Join();
}
void TradeApiBase::Release()
{
	m_Protocol->Stop();
	m_Protocol->Join();
	delete this;
}
void TradeApiBase::RegisterFront(const char* address)
{
	m_Protocol->RegisterFront(address);
}
void TradeApiBase::RegisterSpi(TradeSpi* spi)
{
	m_TradeSpi = spi;
}
