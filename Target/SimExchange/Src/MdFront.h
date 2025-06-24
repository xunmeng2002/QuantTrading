#pragma once
#include "Protocol.h"


class MdFront : public Protocol
{
public:
	MdFront(const char* address, int milliSecond = 100);

private:
	IOThread* m_IOThread;
};



