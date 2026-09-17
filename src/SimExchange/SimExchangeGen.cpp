// 本文件由 ../Templates/Cpp/Protocol/Kernel/KernelGen.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchange.h"

#include "Error.h"
#include "PackageReply.h"
#include "Packages.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Network/Protocol/Package.h>

namespace QuantTrading::SimExchange
{
bool SimExchange::DispatchPackage(Package* package)
{
	switch (package->Head.PackageId)
	{
	case RspMdUserLoginPackage::PackageId:
	{
		HandleRspMdUserLogin(static_cast<RspMdUserLoginPackage*>(package));
		return true;
	}
	case RspMdUserLogoutPackage::PackageId:
	{
		HandleRspMdUserLogout(static_cast<RspMdUserLogoutPackage*>(package));
		return true;
	}
	case RtnDepthMarketDataPackage::PackageId:
	{
		HandleRtnDepthMarketData(static_cast<RtnDepthMarketDataPackage*>(package));
		return true;
	}
	case RtnBarMarketDataPackage::PackageId:
	{
		HandleRtnBarMarketData(static_cast<RtnBarMarketDataPackage*>(package));
		return true;
	}
	case NotifyDisConnectPackage::PackageId:
	{
		HandleNotifyDisConnect(static_cast<NotifyDisConnectPackage*>(package));
		return true;
	}
	case ReqAccountLoginPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqAccountLoginPackage*>(package);
		if (reqPackage->ReqAccountLogin == nullptr)
		{
			ReplyPackageParseFailed<RspAccountLoginPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqAccountLogin(reqPackage);
		return true;
	}
	case ReqAccountLogoutPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqAccountLogoutPackage*>(package);
		if (reqPackage->ReqAccountLogout == nullptr)
		{
			ReplyPackageParseFailed<RspAccountLogoutPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqAccountLogout(reqPackage);
		return true;
	}
	case ReqInsertOrderPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqInsertOrderPackage*>(package);
		if (reqPackage->ReqInsertOrder == nullptr)
		{
			ReplyPackageParseFailed<RspInsertOrderPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqInsertOrder(reqPackage);
		return true;
	}
	case ReqCancelOrderPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqCancelOrderPackage*>(package);
		if (reqPackage->ReqCancelOrder == nullptr)
		{
			ReplyPackageParseFailed<RspCancelOrderPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqCancelOrder(reqPackage);
		return true;
	}
	case ReqQryOrderPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqQryOrderPackage*>(package);
		if (reqPackage->ReqQryOrder == nullptr)
		{
			ReplyPackageParseFailed<RspQryOrderPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryOrder(reqPackage);
		return true;
	}
	case ReqQryTradePackage::PackageId:
	{
		auto reqPackage = static_cast<ReqQryTradePackage*>(package);
		if (reqPackage->ReqQryTrade == nullptr)
		{
			ReplyPackageParseFailed<RspQryTradePackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryTrade(reqPackage);
		return true;
	}
	case ReqQryInstrumentPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqQryInstrumentPackage*>(package);
		if (reqPackage->ReqQryInstrument == nullptr)
		{
			ReplyPackageParseFailed<RspQryInstrumentPackage>(tradeFront_, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqQryInstrument(reqPackage);
		return true;
	}
	default:
	{
		WriteLog(Spark::Core::LogLevel::Warning, "UnExpected PackageId:%d", package->Head.PackageId);
		break;
	}
	}
	return true;
}
}
