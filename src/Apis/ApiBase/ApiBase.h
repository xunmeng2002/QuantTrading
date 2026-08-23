#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>
#include <Spark/Network/IO/IOThread.h>
#include <string>


namespace quanttrading
{
class ApiBase : public spark::network::ProtocolSubscriber
{
public:
	ApiBase(const char* name);
	virtual ~ApiBase();

protected:
	ProtocolTypeType m_ProtocolType;

    spark::network::IOThread* m_IOThread;
    spark::network::Protocol* m_Protocol;
};
}

