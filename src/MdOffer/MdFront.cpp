#include "MdFront.h"
#include "PackageFactory.h"

using namespace Spark::Network;

namespace QuantTrading::MdOffer
{
    MdFront::MdFront(Spark::IoModelType ioModel, const char* address, int milliSecond)
        :Protocol(Spark::ProtocolTypeType::Xtp, Spark::ServerTypeType::Server, ioModel, milliSecond, new QuantTrading::Packages::PackageFactory())
    {
        RegisterFront(address);
        ioThread_ = new IoThread("MdFront");
        SetIoThread(ioThread_);
    }
}
