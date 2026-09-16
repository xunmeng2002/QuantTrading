#include "TradeFront.h"
#include "PackageFactory.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Network;

namespace QuantTrading::simexchange
{
    TradeFront::TradeFront(const char* address, int milliSecond)
        :Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, IOModelType::Select, milliSecond, new QuantTrading::Packages::PackageFactory())
    {
        RegisterFront(address);
        m_IOThread = new IOThread("TradeFront");
        SetIOThread(m_IOThread);
    }
}

