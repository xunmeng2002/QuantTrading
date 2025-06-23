#include "PackageFactory.h"
#include "Packages.h"


Package* PackageFactory::CreatePackage(UShortType packageID)
{
	switch (packageID)
	{
	case ReqQryInstrumentPackage::PackageID:
	{
		return ReqQryInstrumentPackage::Allocate();
	}
	case RspQryInstrumentPackage::PackageID:
	{
		return RspQryInstrumentPackage::Allocate();
	}
	case ReqSEBrokerLoginPackage::PackageID:
	{
		return ReqSEBrokerLoginPackage::Allocate();
	}
	case RspSEBrokerLoginPackage::PackageID:
	{
		return RspSEBrokerLoginPackage::Allocate();
	}
	case ReqSEInsertOrderPackage::PackageID:
	{
		return ReqSEInsertOrderPackage::Allocate();
	}
	case RspSEInsertOrderPackage::PackageID:
	{
		return RspSEInsertOrderPackage::Allocate();
	}
	case ReqSECancelOrderPackage::PackageID:
	{
		return ReqSECancelOrderPackage::Allocate();
	}
	case RspSECancelOrderPackage::PackageID:
	{
		return RspSECancelOrderPackage::Allocate();
	}
	case ReqQrySEOrderPackage::PackageID:
	{
		return ReqQrySEOrderPackage::Allocate();
	}
	case RspQrySEOrderPackage::PackageID:
	{
		return RspQrySEOrderPackage::Allocate();
	}
	case ReqQrySETradePackage::PackageID:
	{
		return ReqQrySETradePackage::Allocate();
	}
	case RspQrySETradePackage::PackageID:
	{
		return RspQrySETradePackage::Allocate();
	}
	case RtnSEOrderPackage::PackageID:
	{
		return RtnSEOrderPackage::Allocate();
	}
	case RtnSETradePackage::PackageID:
	{
		return RtnSETradePackage::Allocate();
	}
	default:
		break;
	}
	return nullptr;
}

