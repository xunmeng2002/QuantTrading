#include "MdApiBase.h"
#include "TcpSelectClient.h"

extern const char* Version;

const char* MdApi::GetApiVersion()
{
	return Version;
}

MdApiBase::MdApiBase()
	:ApiBase("MdApi"), m_MdSpi(nullptr), m_SessionID(0)
{
}
MdApiBase::~MdApiBase()
{
}

void MdApiBase::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = sessionID;
	m_MdSpi->OnConnected();
}
void MdApiBase::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = -1;
	m_MdSpi->OnDisConnected();
}

void MdApiBase::Init()
{
	m_Protocol->Init();
	m_Protocol->Start();
}
void MdApiBase::Join()
{
	m_Protocol->Join();
}
void MdApiBase::Release()
{
	m_Protocol->Stop();
	m_Protocol->Join();
	delete this;
}
void MdApiBase::RegisterFront(const char* address)
{
	m_Protocol->RegisterFront(address);
}
void MdApiBase::RegisterSpi(MdSpi* spi)
{
	m_MdSpi = spi;
}
