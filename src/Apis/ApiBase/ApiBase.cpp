#include "ApiBase.h"
#include "PackageFactory.h"
#include <Spark/Network/IO/IOFactory.h>

using namespace Spark::Network;

namespace QuantTrading
{
ApiBase::ApiBase(const char* name)
	:protocol_(nullptr), protocolType_(ProtocolTypeType::Xtp)
{
	ioThread_ = new IoThread(name);
	protocol_ = new Protocol(protocolType_, ServerTypeType::Client, IoModelType::Select, 100, new QuantTrading::Packages::PackageFactory());
	protocol_->Subscribe(this);
	protocol_->SetIoThread(ioThread_);
}
ApiBase::~ApiBase()
{
	if (protocol_ != nullptr)
	{
		delete protocol_;
		protocol_ = nullptr;
	}
}
}
