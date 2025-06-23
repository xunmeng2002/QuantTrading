#pragma once
#include "Protocol.h"


class MdFront : public Protocol
{
public:
	MdFront(const char* address);

private:
	IOThread* m_IOThread;
};



