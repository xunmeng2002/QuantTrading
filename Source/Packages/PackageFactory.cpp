#include "PackageFactory.h"
#include "Packages.h"


Package* PackageFactory::CreatePackage(UShortType packageID)
{
	switch (packageID)
	{
	case NotifyConnectPackage::PackageID:
	{
		return NotifyConnectPackage::Allocate();
	}
	case NotifyDisConnectPackage::PackageID:
	{
		return NotifyDisConnectPackage::Allocate();
	}
	case ReqMdUserLoginPackage::PackageID:
	{
		return ReqMdUserLoginPackage::Allocate();
	}
	case RspMdUserLoginPackage::PackageID:
	{
		return RspMdUserLoginPackage::Allocate();
	}
	case ReqSubMarketDataPackage::PackageID:
	{
		return ReqSubMarketDataPackage::Allocate();
	}
	case RspSubMarketDataPackage::PackageID:
	{
		return RspSubMarketDataPackage::Allocate();
	}
	case ReqUnSubMarketDataPackage::PackageID:
	{
		return ReqUnSubMarketDataPackage::Allocate();
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		return RspUnSubMarketDataPackage::Allocate();
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		return RtnDepthMarketDataPackage::Allocate();
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		return RtnBarMarketDataPackage::Allocate();
	}
	default:
		break;
	}
	return nullptr;
}

