#pragma once
#include "Protocol.h"

class TradeFront : public Protocol
{
public:
	TradeFront(const char* address);

private:
	IOThread* m_IOThread;
};

