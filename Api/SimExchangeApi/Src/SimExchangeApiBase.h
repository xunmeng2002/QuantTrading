#pragma once
#include "ApiBase.h"
#include "SimExchangeApi.h"
#include "ThreadBase.h"
#include "Protocol.h"
#include "TcpBase.h"
#include <string>


class SimExchangeApiBase : public ApiBase, public SimExchangeApi
{
public:
	SimExchangeApiBase();
	virtual ~SimExchangeApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;

	//override for SimExchangeApi
	virtual void Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(SimExchangeSpi* spi) override;


protected:
	SimExchangeSpi* m_SimExchangeSpi;
	SessionIDType m_SessionID;
};



