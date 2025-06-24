#include "MdFront.h"


MdFront::MdFront(const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, milliSecond, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("MdFront");
	SetIOThread(m_IOThread);
}
