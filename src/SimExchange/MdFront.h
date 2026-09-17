#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>


namespace QuantTrading::SimExchange
{
class MdFront : public Spark::Network::Protocol, public Spark::Network::ProtocolSubscriber
{
public:
	MdFront(const char* address, int milliSecond = 100);

	virtual void OnProtocolConnect(SessionIdType sessionId, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port) override;
	virtual void OnMessage(Spark::Network::Package* package) override;

private:
    Spark::Network::IoThread* ioThread_;
};
}


