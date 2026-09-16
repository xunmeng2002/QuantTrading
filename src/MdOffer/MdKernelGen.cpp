// 本文件由 ../Templates/Cpp/Protocol/Kernel/KernelGen.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdKernel.h"

#include "Error.h"
#include "PackageReply.h"
#include "Packages.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Network/Protocol/Package.h>

namespace QuantTrading::MdOffer
{
bool MdKernel::DispatchPackage(Package* package)
{
	switch (package->Head.PackageId)
	{
	case NotifyDisConnectPackage::PackageId:
	{
		HandleNotifyDisConnect(static_cast<NotifyDisConnectPackage*>(package));
		return true;
	}
	case NotifyDbConnectPackage::PackageId:
	{
		HandleNotifyDbConnect(static_cast<NotifyDbConnectPackage*>(package));
		return true;
	}
	case NotifyDbDisConnectPackage::PackageId:
	{
		HandleNotifyDbDisConnect(static_cast<NotifyDbDisConnectPackage*>(package));
		return true;
	}
	case ReqMdUserLoginPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqMdUserLoginPackage*>(package);
		if (reqPackage->ReqMdUserLogin == nullptr)
		{
			ReplyPackageParseFailed<RspMdUserLoginPackage>(m_MdFront, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqMdUserLogin(reqPackage);
		return true;
	}
	case ReqMdUserLogoutPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqMdUserLogoutPackage*>(package);
		if (reqPackage->ReqMdUserLogout == nullptr)
		{
			ReplyPackageParseFailed<RspMdUserLogoutPackage>(m_MdFront, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqMdUserLogout(reqPackage);
		return true;
	}
	case ReqSubMarketDataPackage::PackageId:
	{
		auto reqPackage = static_cast<ReqSubMarketDataPackage*>(package);
		if (reqPackage->ReqSubMarketData == nullptr)
		{
			ReplyPackageParseFailed<RspSubMarketDataPackage>(m_MdFront, reqPackage->SessionId, reqPackage->Head.MsgSeqNum);
			return true;
		}
		HandleReqSubMarketData(reqPackage);
		return true;
	}
	case RtnDepthMarketDataPackage::PackageId:
	{
		HandleRtnDepthMarketData(static_cast<RtnDepthMarketDataPackage*>(package));
		return false;
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
