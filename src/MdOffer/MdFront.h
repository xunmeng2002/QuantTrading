#pragma once
#include <Spark/Network/IO/IOFactory.h>
#include <Spark/Network/Protocol/Protocol.h>
#include <string>


namespace QuantTrading::MdOffer
{
    class MdFront : public Spark::Network::Protocol
    {
    public:
        MdFront(IoModelType ioModel, const char* address, int milliSecond = 1);



    private:
        std::string m_Address;
        Spark::Network::IoThread* ioThread_;
    };
}


