#include "TradeFront.h"


TradeFront::TradeFront(const char* address)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, 1, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("TradeFront");
	SetIOThread(m_IOThread);
}

