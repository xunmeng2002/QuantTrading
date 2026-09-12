#include "SimExchange.h"

#include "Error.h"
#include "PackageReply.h"
#include "Packages.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Network/Protocol/Package.h>

namespace quanttrading::simexchange
{
bool SimExchange::DispatchPackage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case RspMdUserLoginPackage::PackageID:
	{
		HandleRspMdUserLogin((RspMdUserLoginPackage*)package);
		return true;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		HandleRspMdUserLogout((RspMdUserLogoutPackage*)package);
		return true;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		HandleRtnDepthMarketData((RtnDepthMarketDataPackage*)package);
		return true;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		HandleRtnBarMarketData((RtnBarMarketDataPackage*)package);
		return true;
	}
	case NotifyDisConnectPackage::PackageID:
	{
		HandleNotifyDisConnect((NotifyDisConnectPackage*)package);
		return true;
	}
	case ReqAccountLoginPackage::PackageID:
	{
		auto reqPackage = (ReqAccountLoginPackage*)package;
		if (reqPackage->ReqAccountLogin == nullptr)
		{
			ReplyPackageParseFailed<RspAccountLoginPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqAccountLogin(reqPackage);
		return true;
	}
	case ReqAccountLogoutPackage::PackageID:
	{
		auto reqPackage = (ReqAccountLogoutPackage*)package;
		if (reqPackage->ReqAccountLogout == nullptr)
		{
			ReplyPackageParseFailed<RspAccountLogoutPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqAccountLogout(reqPackage);
		return true;
	}
	case ReqInsertOrderPackage::PackageID:
	{
		auto reqPackage = (ReqInsertOrderPackage*)package;
		if (reqPackage->ReqInsertOrder == nullptr)
		{
			ReplyPackageParseFailed<RspInsertOrderPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqInsertOrder(reqPackage);
		return true;
	}
	case ReqCancelOrderPackage::PackageID:
	{
		auto reqPackage = (ReqCancelOrderPackage*)package;
		if (reqPackage->ReqCancelOrder == nullptr)
		{
			ReplyPackageParseFailed<RspCancelOrderPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqCancelOrder(reqPackage);
		return true;
	}
	case ReqQryOrderPackage::PackageID:
	{
		auto reqPackage = (ReqQryOrderPackage*)package;
		if (reqPackage->ReqQryOrder == nullptr)
		{
			ReplyPackageParseFailed<RspQryOrderPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryOrder(reqPackage);
		return true;
	}
	case ReqQryTradePackage::PackageID:
	{
		auto reqPackage = (ReqQryTradePackage*)package;
		if (reqPackage->ReqQryTrade == nullptr)
		{
			ReplyPackageParseFailed<RspQryTradePackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryTrade(reqPackage);
		return true;
	}
	case ReqQryInstrumentPackage::PackageID:
	{
		auto reqPackage = (ReqQryInstrumentPackage*)package;
		if (reqPackage->ReqQryInstrument == nullptr)
		{
			ReplyPackageParseFailed<RspQryInstrumentPackage>(m_TradeFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryInstrument(reqPackage);
		return true;
	}
	default:
	{
		WriteLog(spark::core::LogLevel::Warning, "UnExpected PackageID:%d", package->Head.PackageID);
		break;
	}
	}
	return true;
}
}
