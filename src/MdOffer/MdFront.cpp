#include "MdFront.h"
#include "PackageFactory.h"

using namespace Spark::Network;

namespace QuantTrading::MdOffer
{
    MdFront::MdFront(IoModelType ioModel, const char* address, int milliSecond)
        :Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, ioModel, milliSecond, new QuantTrading::Packages::PackageFactory()), m_Address(address)
    {
        RegisterFront(address);
        m_IOThread = new IoThread("MdFront");
        SetIoThread(m_IOThread);
    }
}
