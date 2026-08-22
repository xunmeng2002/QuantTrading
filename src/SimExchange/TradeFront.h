#pragma once
#include <Spark/Network/Protocol/Protocol.h>

using namespace spark::network;

namespace quanttrading::simexchange
{
class TradeFront : public Protocol
{
public:
	TradeFront(const char* address, int milliSecond = 100);

private:
	IOThread* m_IOThread;
};
}
