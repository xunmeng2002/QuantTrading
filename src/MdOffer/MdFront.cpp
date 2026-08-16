#include "MdFront.h"


MdFront::MdFront(IOModelType ioModel, const char* address, int milliSecond)
	:Protocol(ProtocolTypeType::Xtp, ServerTypeType::Server, ioModel, milliSecond, new PackageFactory()), m_Address(address)
{
	RegisterFront(address);
	m_IOThread = new IOThread("MdFront");
	SetIOThread(m_IOThread);
}

