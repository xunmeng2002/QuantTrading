#pragma once
#include <Spark/Network/Protocol/Protocol.h>


class TradeFront : public Protocol
{
public:
	TradeFront(const char* address, int milliSecond = 100);

private:
	IOThread* m_IOThread;
};

