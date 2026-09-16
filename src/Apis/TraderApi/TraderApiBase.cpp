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
	:ApiBase("TraderApi"), traderSpi_(nullptr), sessionId_(0)
{
}
TraderApiBase::~TraderApiBase()
{
}

void TraderApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (traderSpi_ != nullptr)
	{
		traderSpi_->OnConnected();
	}
}
void TraderApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (traderSpi_ != nullptr)
	{
		traderSpi_->OnDisConnected();
	}
}

bool TraderApiBase::Init()
{
	return protocol_->Init() && protocol_->Start();
}
void TraderApiBase::Join()
{
	protocol_->Join();
}
void TraderApiBase::Release()
{
	protocol_->Stop();
	protocol_->Join();
	delete this;
}
void TraderApiBase::RegisterFront(const char* address)
{
	protocol_->RegisterFront(address);
}
void TraderApiBase::RegisterSpi(TraderSpi* spi)
{
	traderSpi_ = spi;
}
}
