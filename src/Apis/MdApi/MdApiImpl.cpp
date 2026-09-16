// 本文件由 ../Templates/Cpp/Api/ApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>

using namespace Spark;
using namespace QuantTrading::Packages;

namespace QuantTrading
{
MdApi* MdApi::CreateMdApi()
{
	return new MdApiImpl();
}
MdApiImpl::MdApiImpl()
{
}

void MdApiImpl::OnMessage(Package* package)
{
	switch (package->Head.PackageId)
	{
	case RspMdUserLoginPackage::PackageId:
	{
		mdSpi_->OnRspMdUserLogin(static_cast<RspMdUserLoginPackage*>(package)->RspMdUserLogin, static_cast<RspMdUserLoginPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageId:
	{
		mdSpi_->OnRspMdUserLogout(static_cast<RspMdUserLogoutPackage*>(package)->RspMdUserLogout, static_cast<RspMdUserLogoutPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageId:
	{
		mdSpi_->OnRspSubMarketData(static_cast<RspSubMarketDataPackage*>(package)->RspSubMarketData, static_cast<RspSubMarketDataPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageId:
	{
		mdSpi_->OnRspUnSubMarketData(static_cast<RspUnSubMarketDataPackage*>(package)->RspUnSubMarketData, static_cast<RspUnSubMarketDataPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageId:
	{
		mdSpi_->OnRtnDepthMarketData(static_cast<RtnDepthMarketDataPackage*>(package)->DepthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageId:
	{
		mdSpi_->OnRtnBarMarketData(static_cast<RtnBarMarketDataPackage*>(package)->BarMarketData);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int MdApiImpl::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestId)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestId)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestId)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
