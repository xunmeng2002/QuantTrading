#include "MdFront.h"
#include "PackageFactory.h"

using namespace Spark::Network;

namespace QuantTrading::MdOffer
{
    MdFront::MdFront(IoModelType ioModel, const char* address, int milliSecond)
        :Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, ioModel, milliSecond, new QuantTrading::Packages::PackageFactory())
    {
        RegisterFront(address);
        ioThread_ = new IoThread("MdFront");
        SetIoThread(ioThread_);
    }
}
