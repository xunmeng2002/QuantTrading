#include "MdFront.h"
#include "SimExchange.h"


MdFront::MdFront(const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, milliSecond, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("MdFront");
	SetIOThread(m_IOThread);
}
void MdFront::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdFront::OnProtocolConnect SessionID:[%lld], IP:[%s], port:[%d]", sessionID, ip, port);
}
void MdFront::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdFront::OnProtocolDisConnect SessionID:[%lld], IP:[%s], port:[%d]", sessionID, ip, port);
}
void MdFront::OnMessage(Package* package)
{

}



