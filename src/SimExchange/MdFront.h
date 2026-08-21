#pragma once
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>

using namespace spark::network;

class MdFront : public Protocol, public ProtocolSubscriber
{
public:
	MdFront(const char* address, int milliSecond = 100);

public:
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;

private:
	IOThread* m_IOThread;
};



