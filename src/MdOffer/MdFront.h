#pragma once
#include <Spark/Network/IO/IOFactory.h>
#include <Spark/Network/Protocol/Protocol.h>


class MdFront : public spark::network::Protocol
{
public:
	MdFront(IOModelType ioModel, const char* address, int milliSecond = 1);



private:
	std::string m_Address;
    spark::network::IOThread* m_IOThread;
};



