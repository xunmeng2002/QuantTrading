#include "TradeFront.h"
#include "PackageFactory.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Network;

namespace QuantTrading::SimExchange
{
    TradeFront::TradeFront(const char* address, int milliSecond)
        :Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, IoModelType::Select, milliSecond, new QuantTrading::Packages::PackageFactory())
    {
        RegisterFront(address);
        ioThread_ = new IoThread("TradeFront");
        SetIoThread(ioThread_);
    }
}

