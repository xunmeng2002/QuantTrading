#pragma once
#include <Spark/Network/IO/IOFactory.h>
#include <Spark/Network/Protocol/Protocol.h>

using namespace spark::network;

class MdFront : public Protocol
{
public:
	MdFront(IOModelType ioModel, const char* address, int milliSecond = 1);



private:
	std::string m_Address;
	IOThread* m_IOThread;
};



