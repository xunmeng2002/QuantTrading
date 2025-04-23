#pragma once
#include "ApiBase.h"
#include "MdApi.h"
#include "ThreadBase.h"
#include "Protocol.h"
#include "TcpBase.h"
#include <string>


class MdApiBase : public ApiBase, public MdApi
{
public:
	MdApiBase();
	virtual ~MdApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;

	//override for MdApi
	virtual void Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(MdSpi* spi) override;


protected:
	MdSpi* m_MdSpi;
	SessionIDType m_SessionID;
};



