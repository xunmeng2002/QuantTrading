#include "ApiBase.h"
#include "PackageFactory.h"
#include <Spark/Network/IO/IOFactory.h>


namespace quanttrading
{
ApiBase::ApiBase(const char* name)
	:m_Protocol(nullptr), m_ProtocolType(ProtocolTypeType::Xtp)
{
	m_IOThread = new IOThread(name);
	m_Protocol = new Protocol(m_ProtocolType, ServerTypeType::Client, IOModelType::Select, 100, new PackageFactory());
	m_Protocol->Subscribe(this);
	m_Protocol->SetIOThread(m_IOThread);
}
ApiBase::~ApiBase()
{
	if (m_Protocol != nullptr)
	{
		delete m_Protocol;
		m_Protocol = nullptr;
	}
}
}
