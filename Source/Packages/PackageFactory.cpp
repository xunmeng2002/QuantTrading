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
	case ReqMdUserLogoutPackage::PackageID:
	{
		return ReqMdUserLogoutPackage::Allocate();
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		return RspMdUserLogoutPackage::Allocate();
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
	case RtnMarketDataEndPackage::PackageID:
	{
		return RtnMarketDataEndPackage::Allocate();
	}
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
	case ReqQryAccountPackage::PackageID:
	{
		return ReqQryAccountPackage::Allocate();
	}
	case RspQryAccountPackage::PackageID:
	{
		return RspQryAccountPackage::Allocate();
	}
	case ReqQryHolderAccountPackage::PackageID:
	{
		return ReqQryHolderAccountPackage::Allocate();
	}
	case RspQryHolderAccountPackage::PackageID:
	{
		return RspQryHolderAccountPackage::Allocate();
	}
	case ReqQryCapitalPackage::PackageID:
	{
		return ReqQryCapitalPackage::Allocate();
	}
	case RspQryCapitalPackage::PackageID:
	{
		return RspQryCapitalPackage::Allocate();
	}
	case ReqQryPositionPackage::PackageID:
	{
		return ReqQryPositionPackage::Allocate();
	}
	case RspQryPositionPackage::PackageID:
	{
		return RspQryPositionPackage::Allocate();
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
	case ReqQryOptionInstrumentPackage::PackageID:
	{
		return ReqQryOptionInstrumentPackage::Allocate();
	}
	case RspQryOptionInstrumentPackage::PackageID:
	{
		return RspQryOptionInstrumentPackage::Allocate();
	}
	case ReqQryCommissionRatePackage::PackageID:
	{
		return ReqQryCommissionRatePackage::Allocate();
	}
	case RspQryCommissionRatePackage::PackageID:
	{
		return RspQryCommissionRatePackage::Allocate();
	}
	case ReqQryMoneyTransferPackage::PackageID:
	{
		return ReqQryMoneyTransferPackage::Allocate();
	}
	case RspQryMoneyTransferPackage::PackageID:
	{
		return RspQryMoneyTransferPackage::Allocate();
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
	case RtnMoneyTransferPackage::PackageID:
	{
		return RtnMoneyTransferPackage::Allocate();
	}
	case RtnAccountLogoutPackage::PackageID:
	{
		return RtnAccountLogoutPackage::Allocate();
	}
	default:
		break;
	}
	return nullptr;
}

