#pragma once
#include "Protocol.h"
#include "ProtocolSubscriber.h"
#include "TcpBase.h"
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

