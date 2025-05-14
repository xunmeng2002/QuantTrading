#include "PackageFactory.h"
#include "Packages.h"


Package* PackageFactory::CreatePackage(UShortType packageID)
{
	switch (packageID)
	{
	case ReqSubMarketDataPackage::PackageID:
	{
		return ReqSubMarketDataPackage::Allocate();
	}
	case RspSubMarketDataPackage::PackageID:
	{
		return RspSubMarketDataPackage::Allocate();
	}
	case ReqSubMarketDataFinishedPackage::PackageID:
	{
		return ReqSubMarketDataFinishedPackage::Allocate();
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		return RtnDepthMarketDataPackage::Allocate();
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		return RtnBarMarketDataPackage::Allocate();
	}
	case RtnSessionBeginPackage::PackageID:
	{
		return RtnSessionBeginPackage::Allocate();
	}
	case RtnSessionEndPackage::PackageID:
	{
		return RtnSessionEndPackage::Allocate();
	}
	case ReqInsertOrderPackage::PackageID:
	{
		return ReqInsertOrderPackage::Allocate();
	}
	case RspInsertOrderPackage::PackageID:
	{
		return RspInsertOrderPackage::Allocate();
	}
	case ReqCancelOrderPackage::PackageID:
	{
		return ReqCancelOrderPackage::Allocate();
	}
	case RspCancelOrderPackage::PackageID:
	{
		return RspCancelOrderPackage::Allocate();
	}
	case RtnOrderPackage::PackageID:
	{
		return RtnOrderPackage::Allocate();
	}
	case RtnTradePackage::PackageID:
	{
		return RtnTradePackage::Allocate();
	}
	default:
		break;
	}
	return nullptr;
}

