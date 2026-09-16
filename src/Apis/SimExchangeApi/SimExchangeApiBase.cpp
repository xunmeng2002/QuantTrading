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
	:ApiBase("SimExchangeApi"), simExchangeSpi_(nullptr), sessionId_(0)
{
}
SimExchangeApiBase::~SimExchangeApiBase()
{
}

void SimExchangeApiBase::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = sessionId;
	if (simExchangeSpi_ != nullptr)
	{
		simExchangeSpi_->OnConnected();
	}
}
void SimExchangeApiBase::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	sessionId_ = -1;
	if (simExchangeSpi_ != nullptr)
	{
		simExchangeSpi_->OnDisConnected();
	}
}

bool SimExchangeApiBase::Init()
{
	return protocol_->Init() && protocol_->Start();
}
void SimExchangeApiBase::Join()
{
	protocol_->Join();
}
void SimExchangeApiBase::Release()
{
	protocol_->Stop();
	protocol_->Join();
	delete this;
}
void SimExchangeApiBase::RegisterFront(const char* address)
{
	protocol_->RegisterFront(address);
}
void SimExchangeApiBase::RegisterSpi(SimExchangeSpi* spi)
{
	simExchangeSpi_ = spi;
}
}
