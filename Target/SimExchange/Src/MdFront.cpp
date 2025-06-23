#include "MdFront.h"


MdFront::MdFront(const char* address)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, 1, new PackageFactory())
{
	RegisterFront(address);
	m_IOThread = new IOThread("MdFront");
	SetIOThread(m_IOThread);
}
