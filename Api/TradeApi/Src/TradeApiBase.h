#pragma once
#include "ApiBase.h"
#include "TradeApi.h"
#include "ThreadBase.h"
#include "Protocol.h"
#include "TcpBase.h"
#include <string>


class TradeApiBase : public ApiBase, public TradeApi
{
public:
	TradeApiBase();
	virtual ~TradeApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;

	//override for TradeApi
	virtual void Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(TradeSpi* spi) override;


protected:
	TradeSpi* m_TradeSpi;
	SessionIDType m_SessionID;
};



