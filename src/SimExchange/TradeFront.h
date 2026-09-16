#pragma once
#include <Spark/Network/Protocol/Protocol.h>


namespace QuantTrading::simexchange
{
class TradeFront : public Spark::Network::Protocol
{
public:
	TradeFront(const char* address, int milliSecond = 100);

private:
    Spark::Network::IOThread* m_IOThread;
};
}
