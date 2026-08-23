#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>
#include <Spark/Network/IO/IOThread.h>
#include <string>

using namespace spark::network;

namespace quanttrading
{
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
}

