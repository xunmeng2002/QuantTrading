#include "PackageFactory.h"
#include "Packages.h"


using namespace spark::network;

namespace quanttrading::packages
{
PackageFactory::PackageFactory(ServerTypeType serverType)
	:m_ServerType(serverType)
{
}
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
	case NotifyDBConnectPackage::PackageID:
	{
		return NotifyDBConnectPackage::Allocate();
	}
	case NotifyDBDisConnectPackage::PackageID:
	{
		return NotifyDBDisConnectPackage::Allocate();
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
	case ReqRegisterAccountPackage::PackageID:
	{
		return ReqRegisterAccountPackage::Allocate();
	}
	case RspRegisterAccountPackage::PackageID:
	{
		return RspRegisterAccountPackage::Allocate();
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
bool PackageFactory::IsInboundPackageAccepted(UShortType packageID)
{
	// 方向族按包名前缀生成：Req 只可能由客户端发往服务端，Rsp/Rtn 反过来，Notify 是进程内自造、网线上永不合法
	switch (packageID)
	{
	case NotifyConnectPackage::PackageID:
	{
		return false;
	}
	case NotifyDisConnectPackage::PackageID:
	{
		return false;
	}
	case NotifyDBConnectPackage::PackageID:
	{
		return false;
	}
	case NotifyDBDisConnectPackage::PackageID:
	{
		return false;
	}
	case ReqMdUserLoginPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspMdUserLoginPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqMdUserLogoutPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqSubMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqUnSubMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqSubMarketDataFinishedPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnSessionBeginPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnSessionEndPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnMarketDataEndPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqRegisterAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspRegisterAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqAccountLoginPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspAccountLoginPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqAccountLogoutPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspAccountLogoutPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryHolderAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryHolderAccountPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryCapitalPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryCapitalPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryPositionPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryPositionPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryTradePackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryTradePackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryInstrumentPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryInstrumentPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryOptionInstrumentPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryOptionInstrumentPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryCommissionRatePackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryCommissionRatePackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqQryMoneyTransferPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspQryMoneyTransferPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqInsertOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspInsertOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case ReqCancelOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Server;
	}
	case RspCancelOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnOrderPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnTradePackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnMoneyTransferPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	case RtnAccountLogoutPackage::PackageID:
	{
		return m_ServerType == ServerTypeType::Client;
	}
	default:
		break;
	}
	return false;
}
}
