// 本文件由 ../Templates/Cpp/Api/ApiBase.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiBase.h"
#include "QuantTrading/Version.h"

namespace QuantTrading
{
const char* MdApi::GetApiVersion()
{
	return QUANTTRADING_VERSION;
}

MdApiBase::MdApiBase()
	:ApiBase("MdApi"), mdSpi(nullptr), sessionId_(0)
{
}
MdApiBase::~MdApiBase()
{
}

void MdApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (mdSpi != nullptr)
	{
		mdSpi->OnConnected();
	}
}
void MdApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (mdSpi != nullptr)
	{
		mdSpi->OnDisConnected();
	}
}

bool MdApiBase::Init()
{
	return m_Protocol->Init() && m_Protocol->Start();
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
	mdSpi = spi;
}
}
