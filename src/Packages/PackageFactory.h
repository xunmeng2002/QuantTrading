#pragma once
#include <Spark/Network/Protocol/PackageFactoryBase.h>

namespace quanttrading::packages
{
class PackageFactory : public spark::network::PackageFactoryBase
{
public:
	PackageFactory(ServerTypeType serverType);
	virtual spark::network::Package* CreatePackage(UShortType packageID) override;
	virtual bool IsInboundPackageAccepted(UShortType packageID) override;

private:
	ServerTypeType m_ServerType;
};
}

