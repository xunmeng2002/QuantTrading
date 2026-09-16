#include "MdFront.h"
#include "SimExchange.h"
#include "PackageFactory.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Network;

namespace QuantTrading::SimExchange
{
MdFront::MdFront(const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, IoModelType::Select,  milliSecond, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IoThread("MdFront");
	SetIoThread(m_IOThread);
}
void MdFront::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdFront::OnProtocolConnect SessionId:[%lld], IP:[%s], port:[%d]", sessionId, ip, port);
}
void MdFront::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdFront::OnProtocolDisConnect SessionId:[%lld], IP:[%s], port:[%d]", sessionId, ip, port);
}
void MdFront::OnMessage(Package* package)
{

}
}


