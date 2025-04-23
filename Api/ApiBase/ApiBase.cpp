#include "ApiBase.h"
#include "Config.h"
#include "PackageFactory.h"
#include "IOFactory.h"


auto ConfigName = "Api.json";

ApiBase::ApiBase(const char* name)
	:m_Protocol(nullptr)
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	if (config.ProtocolType == "step")
	{
		m_ProtocolType = ProtocolTypeType::Step;	
	}
	else
	{
		m_ProtocolType = ProtocolTypeType::Xtp;
	}
	m_IOThread = new IOThread(name);
	m_Protocol = new Protocol(m_ProtocolType, ServerTypeType::Client, 100, new PackageFactory());
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
