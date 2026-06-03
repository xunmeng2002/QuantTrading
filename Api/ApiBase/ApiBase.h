#pragma once
#include "Protocol/Protocol.h"
#include "Protocol/ProtocolSubscriber.h"
#include "Tcp/TcpBase/TcpBase.h"
#include <string>


class ApiBase : public ProtocolSubscriber
{
public:
	ApiBase(const char* name);
	virtual ~ApiBase();

protected:
	ProtocolTypeType m_ProtocolType;

	IOThread* m_IOThread;
	Protocol* m_Protocol;
};

