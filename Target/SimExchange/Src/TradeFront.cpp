#include "TradeFront.h"
#include "Logger.h"

TradeFront::TradeFront(const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, milliSecond, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("TradeFront");
	SetIOThread(m_IOThread);
}


