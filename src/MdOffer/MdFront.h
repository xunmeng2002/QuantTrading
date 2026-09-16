#pragma once
#include <Spark/Network/IO/IOFactory.h>
#include <Spark/Network/Protocol/Protocol.h>
#include <string>


namespace QuantTrading::mdoffer
{
    class MdFront : public Spark::Network::Protocol
    {
    public:
        MdFront(IOModelType ioModel, const char* address, int milliSecond = 1);



    private:
        std::string m_Address;
        Spark::Network::IOThread* m_IOThread;
    };
}


