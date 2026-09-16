// 本文件由 ../Templates/Cpp/Protocol/Packages/PackageFactory.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "PackageFactory.h"
#include "Packages.h"


using namespace Spark::Network;

namespace QuantTrading::Packages
{
Package* PackageFactory::CreatePackage(UInt16Type packageId)
{
	switch (packageId)
	{
	case NotifyConnectPackage::PackageId:
	{
		return NotifyConnectPackage::Allocate();
	}
	case NotifyDisConnectPackage::PackageId:
	{
		return NotifyDisConnectPackage::Allocate();
	}
	case NotifyDbConnectPackage::PackageId:
	{
		return NotifyDbConnectPackage::Allocate();
	}
	case NotifyDbDisConnectPackage::PackageId:
	{
		return NotifyDbDisConnectPackage::Allocate();
	}
	case ReqMdUserLoginPackage::PackageId:
	{
		return ReqMdUserLoginPackage::Allocate();
	}
	case RspMdUserLoginPackage::PackageId:
	{
		return RspMdUserLoginPackage::Allocate();
	}
	case ReqMdUserLogoutPackage::PackageId:
	{
		return ReqMdUserLogoutPackage::Allocate();
	}
	case RspMdUserLogoutPackage::PackageId:
	{
		return RspMdUserLogoutPackage::Allocate();
	}
	case ReqSubMarketDataPackage::PackageId:
	{
		return ReqSubMarketDataPackage::Allocate();
	}
	case RspSubMarketDataPackage::PackageId:
	{
		return RspSubMarketDataPackage::Allocate();
	}
	case ReqUnSubMarketDataPackage::PackageId:
	{
		return ReqUnSubMarketDataPackage::Allocate();
	}
	case RspUnSubMarketDataPackage::PackageId:
	{
		return RspUnSubMarketDataPackage::Allocate();
	}
	case ReqSubMarketDataFinishedPackage::PackageId:
	{
		return ReqSubMarketDataFinishedPackage::Allocate();
	}
	case RtnDepthMarketDataPackage::PackageId:
	{
		return RtnDepthMarketDataPackage::Allocate();
	}
	case RtnBarMarketDataPackage::PackageId:
	{
		return RtnBarMarketDataPackage::Allocate();
	}
	case RtnSessionBeginPackage::PackageId:
	{
		return RtnSessionBeginPackage::Allocate();
	}
	case RtnSessionEndPackage::PackageId:
	{
		return RtnSessionEndPackage::Allocate();
	}
	case RtnMarketDataEndPackage::PackageId:
	{
		return RtnMarketDataEndPackage::Allocate();
	}
	case ReqRegisterAccountPackage::PackageId:
	{
		return ReqRegisterAccountPackage::Allocate();
	}
	case RspRegisterAccountPackage::PackageId:
	{
		return RspRegisterAccountPackage::Allocate();
	}
	case ReqAccountLoginPackage::PackageId:
	{
		return ReqAccountLoginPackage::Allocate();
	}
	case RspAccountLoginPackage::PackageId:
	{
		return RspAccountLoginPackage::Allocate();
	}
	case ReqAccountLogoutPackage::PackageId:
	{
		return ReqAccountLogoutPackage::Allocate();
	}
	case RspAccountLogoutPackage::PackageId:
	{
		return RspAccountLogoutPackage::Allocate();
	}
	case ReqQryAccountPackage::PackageId:
	{
		return ReqQryAccountPackage::Allocate();
	}
	case RspQryAccountPackage::PackageId:
	{
		return RspQryAccountPackage::Allocate();
	}
	case ReqQryHolderAccountPackage::PackageId:
	{
		return ReqQryHolderAccountPackage::Allocate();
	}
	case RspQryHolderAccountPackage::PackageId:
	{
		return RspQryHolderAccountPackage::Allocate();
	}
	case ReqQryCapitalPackage::PackageId:
	{
		return ReqQryCapitalPackage::Allocate();
	}
	case RspQryCapitalPackage::PackageId:
	{
		return RspQryCapitalPackage::Allocate();
	}
	case ReqQryPositionPackage::PackageId:
	{
		return ReqQryPositionPackage::Allocate();
	}
	case RspQryPositionPackage::PackageId:
	{
		return RspQryPositionPackage::Allocate();
	}
	case ReqQryOrderPackage::PackageId:
	{
		return ReqQryOrderPackage::Allocate();
	}
	case RspQryOrderPackage::PackageId:
	{
		return RspQryOrderPackage::Allocate();
	}
	case ReqQryTradePackage::PackageId:
	{
		return ReqQryTradePackage::Allocate();
	}
	case RspQryTradePackage::PackageId:
	{
		return RspQryTradePackage::Allocate();
	}
	case ReqQryInstrumentPackage::PackageId:
	{
		return ReqQryInstrumentPackage::Allocate();
	}
	case RspQryInstrumentPackage::PackageId:
	{
		return RspQryInstrumentPackage::Allocate();
	}
	case ReqQryOptionInstrumentPackage::PackageId:
	{
		return ReqQryOptionInstrumentPackage::Allocate();
	}
	case RspQryOptionInstrumentPackage::PackageId:
	{
		return RspQryOptionInstrumentPackage::Allocate();
	}
	case ReqQryCommissionRatePackage::PackageId:
	{
		return ReqQryCommissionRatePackage::Allocate();
	}
	case RspQryCommissionRatePackage::PackageId:
	{
		return RspQryCommissionRatePackage::Allocate();
	}
	case ReqQryMoneyTransferPackage::PackageId:
	{
		return ReqQryMoneyTransferPackage::Allocate();
	}
	case RspQryMoneyTransferPackage::PackageId:
	{
		return RspQryMoneyTransferPackage::Allocate();
	}
	case ReqInsertOrderPackage::PackageId:
	{
		return ReqInsertOrderPackage::Allocate();
	}
	case RspInsertOrderPackage::PackageId:
	{
		return RspInsertOrderPackage::Allocate();
	}
	case ReqCancelOrderPackage::PackageId:
	{
		return ReqCancelOrderPackage::Allocate();
	}
	case RspCancelOrderPackage::PackageId:
	{
		return RspCancelOrderPackage::Allocate();
	}
	case RtnOrderPackage::PackageId:
	{
		return RtnOrderPackage::Allocate();
	}
	case RtnTradePackage::PackageId:
	{
		return RtnTradePackage::Allocate();
	}
	case RtnMoneyTransferPackage::PackageId:
	{
		return RtnMoneyTransferPackage::Allocate();
	}
	case RtnAccountLogoutPackage::PackageId:
	{
		return RtnAccountLogoutPackage::Allocate();
	}
	default:
		break;
	}
	return nullptr;
}
}
