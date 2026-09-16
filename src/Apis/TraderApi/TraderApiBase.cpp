// 本文件由 ../Templates/Cpp/Api/ApiBase.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderApiBase.h"
#include "QuantTrading/Version.h"

namespace QuantTrading
{
const char* TraderApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

TraderApiBase::TraderApiBase()
	:ApiBase("TraderApi"), traderSpi(nullptr), sessionId_(0)
{
}
TraderApiBase::~TraderApiBase()
{
}

void TraderApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (traderSpi != nullptr)
	{
		traderSpi->OnConnected();
	}
}
void TraderApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (traderSpi != nullptr)
	{
		traderSpi->OnDisConnected();
	}
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
	traderSpi = spi;
}
}
