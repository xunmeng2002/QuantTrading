#include "PackageFactory.h"
#include "Packages.h"


Package* PackageFactory::CreatePackage(UShortType packageID)
{
	switch (packageID)
	{
	case ReqAccountLoginPackage::PackageID:
	{
		return ReqAccountLoginPackage::Allocate();
	}
	case RspAccountLoginPackage::PackageID:
	{
		return RspAccountLoginPackage::Allocate();
	}
	case ReqAccountLogoutPackage::PackageID:
	{
		return ReqAccountLogoutPackage::Allocate();
	}
	case RspAccountLogoutPackage::PackageID:
	{
		return RspAccountLogoutPackage::Allocate();
	}
	case ReqQryOrderPackage::PackageID:
	{
		return ReqQryOrderPackage::Allocate();
	}
	case RspQryOrderPackage::PackageID:
	{
		return RspQryOrderPackage::Allocate();
	}
	case ReqQryTradePackage::PackageID:
	{
		return ReqQryTradePackage::Allocate();
	}
	case RspQryTradePackage::PackageID:
	{
		return RspQryTradePackage::Allocate();
	}
	case ReqQryInstrumentPackage::PackageID:
	{
		return ReqQryInstrumentPackage::Allocate();
	}
	case RspQryInstrumentPackage::PackageID:
	{
		return RspQryInstrumentPackage::Allocate();
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

