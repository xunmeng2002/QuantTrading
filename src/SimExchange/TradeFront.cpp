#include "TradeFront.h"
#include <Spark/Core/Logger/Logger.h>

TradeFront::TradeFront(const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, IOModelType::Select, milliSecond, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("TradeFront");
	SetIOThread(m_IOThread);
}


