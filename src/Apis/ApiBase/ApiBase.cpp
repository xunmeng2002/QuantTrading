#include "ApiBase.h"
#include "PackageFactory.h"
#include <Spark/Network/IO/IOFactory.h>

using namespace Spark::Network;

namespace QuantTrading
{
ApiBase::ApiBase(const char* name)
	:m_Protocol(nullptr), m_ProtocolType(ProtocolTypeType::Xtp)
{
	m_IOThread = new IoThread(name);
	m_Protocol = new Protocol(m_ProtocolType, ServerTypeType::Client, IoModelType::Select, 100, new QuantTrading::Packages::PackageFactory());
	m_Protocol->Subscribe(this);
	m_Protocol->SetIoThread(m_IOThread);
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
