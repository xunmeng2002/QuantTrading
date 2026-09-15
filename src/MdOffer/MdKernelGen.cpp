// 本文件由 ../Templates/Cpp/Protocol/Kernel/KernelGen.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdKernel.h"

#include "Error.h"
#include "PackageReply.h"
#include "Packages.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Network/Protocol/Package.h>

namespace quanttrading::mdoffer
{
bool MdKernel::DispatchPackage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case NotifyDisConnectPackage::PackageID:
	{
		HandleNotifyDisConnect(static_cast<NotifyDisConnectPackage*>(package));
		return true;
	}
	case NotifyDBConnectPackage::PackageID:
	{
		HandleNotifyDBConnect(static_cast<NotifyDBConnectPackage*>(package));
		return true;
	}
	case NotifyDBDisConnectPackage::PackageID:
	{
		HandleNotifyDBDisConnect(static_cast<NotifyDBDisConnectPackage*>(package));
		return true;
	}
	case ReqMdUserLoginPackage::PackageID:
	{
		auto reqPackage = static_cast<ReqMdUserLoginPackage*>(package);
		if (reqPackage->ReqMdUserLogin == nullptr)
		{
			ReplyPackageParseFailed<RspMdUserLoginPackage>(m_MdFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqMdUserLogin(reqPackage);
		return true;
	}
	case ReqMdUserLogoutPackage::PackageID:
	{
		auto reqPackage = static_cast<ReqMdUserLogoutPackage*>(package);
		if (reqPackage->ReqMdUserLogout == nullptr)
		{
			ReplyPackageParseFailed<RspMdUserLogoutPackage>(m_MdFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqMdUserLogout(reqPackage);
		return true;
	}
	case ReqSubMarketDataPackage::PackageID:
	{
		auto reqPackage = static_cast<ReqSubMarketDataPackage*>(package);
		if (reqPackage->ReqSubMarketData == nullptr)
		{
			ReplyPackageParseFailed<RspSubMarketDataPackage>(m_MdFront, reqPackage->SessionID, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqSubMarketData(reqPackage);
		return true;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		HandleRtnDepthMarketData(static_cast<RtnDepthMarketDataPackage*>(package));
		return false;
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
