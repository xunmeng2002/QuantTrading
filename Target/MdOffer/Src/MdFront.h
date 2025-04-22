#pragma once
#include "IOFactory.h"
#include "Protocol.h"

class MdFront : public Protocol
{
public:
	MdFront(const char* address, int milliSecond = 1);



private:
	std::string m_Address;
	IOThread* m_IOThread;
};



