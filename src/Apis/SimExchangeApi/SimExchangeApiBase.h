// 本文件由 ../Templates/Cpp/Api/ApiBase.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "ApiBase.h"
#include <QuantTrading/SimExchangeApi.h>
#include <Spark/Network/Protocol/Protocol.h>


namespace QuantTrading
{
class SimExchangeApiBase : public ApiBase, public SimExchangeApi
{
public:
	SimExchangeApiBase();
	virtual ~SimExchangeApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIdType newSessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIdType newSessionID, const char* ip, int port) override;

	//override for SimExchangeApi
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(SimExchangeSpi* spi) override;


protected:
	SimExchangeSpi* simExchangeSpi;
	SessionIdType sessionID;
};
}


