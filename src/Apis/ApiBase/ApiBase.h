#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>
#include <Spark/Network/Io/IoThread.h>
#include <string>


namespace QuantTrading
{
class ApiBase : public Spark::Network::ProtocolSubscriber
{
public:
	ApiBase(const char* name);
	virtual ~ApiBase();

protected:
	Spark::ProtocolTypeType protocolType_;

    Spark::Network::IoThread* ioThread_;
    Spark::Network::Protocol* protocol_;
};
}

