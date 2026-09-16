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
	:ApiBase("MdApi"), mdSpi_(nullptr), sessionId_(0)
{
}
MdApiBase::~MdApiBase()
{
}

void MdApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (mdSpi_ != nullptr)
	{
		mdSpi_->OnConnected();
	}
}
void MdApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (mdSpi_ != nullptr)
	{
		mdSpi_->OnDisConnected();
	}
}

bool MdApiBase::Init()
{
	return protocol_->Init() && protocol_->Start();
}
void MdApiBase::Join()
{
	protocol_->Join();
}
void MdApiBase::Release()
{
	protocol_->Stop();
	protocol_->Join();
	delete this;
}
void MdApiBase::RegisterFront(const char* address)
{
	protocol_->RegisterFront(address);
}
void MdApiBase::RegisterSpi(MdSpi* spi)
{
	mdSpi_ = spi;
}
}
