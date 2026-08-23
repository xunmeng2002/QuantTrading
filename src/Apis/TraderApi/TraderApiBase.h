#pragma once
#include "ApiBase.h"
#include <QuantTrading/TraderApi.h>
#include <Spark/Network/Protocol/Protocol.h>


namespace quanttrading
{
class TraderApiBase : public ApiBase, public TraderApi
{
public:
	TraderApiBase();
	virtual ~TraderApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;

	//override for TraderApi
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(TraderSpi* spi) override;


protected:
	TraderSpi* m_TraderSpi;
	SessionIDType m_SessionID;
};
}


