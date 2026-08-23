#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>


namespace quanttrading::simexchange
{
class MdFront : public spark::network::Protocol, public spark::network::ProtocolSubscriber
{
public:
	MdFront(const char* address, int milliSecond = 100);

public:
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(spark::network::Package* package) override;

private:
    spark::network::IOThread* m_IOThread;
};
}


