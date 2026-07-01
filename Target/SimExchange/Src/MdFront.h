#pragma once
#include "Protocol.h"
#include "ProtocolSubscriber.h"

class SimExchange;
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
	SimExchange* m_SimExchange;
};



