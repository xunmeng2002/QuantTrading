#pragma once
#include <Spark/Network/Protocol/Protocol.h>


namespace quanttrading::simexchange
{
class TradeFront : public spark::network::Protocol
{
public:
	TradeFront(const char* address, int milliSecond = 100);

private:
    spark::network::IOThread* m_IOThread;
};
}
