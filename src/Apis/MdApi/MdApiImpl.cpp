// 本文件由 ../Templates/Cpp/Api/ApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>

using namespace spark;
using namespace quanttrading::packages;

namespace quanttrading
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
	switch (package->Head.PackageID)
	{
	case RspMdUserLoginPackage::PackageID:
	{
		mdSpi->OnRspMdUserLogin(static_cast<RspMdUserLoginPackage*>(package)->RspMdUserLogin, static_cast<RspMdUserLoginPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		mdSpi->OnRspMdUserLogout(static_cast<RspMdUserLogoutPackage*>(package)->RspMdUserLogout, static_cast<RspMdUserLogoutPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		mdSpi->OnRspSubMarketData(static_cast<RspSubMarketDataPackage*>(package)->RspSubMarketData, static_cast<RspSubMarketDataPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		mdSpi->OnRspUnSubMarketData(static_cast<RspUnSubMarketDataPackage*>(package)->RspUnSubMarketData, static_cast<RspUnSubMarketDataPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		mdSpi->OnRtnDepthMarketData(static_cast<RtnDepthMarketDataPackage*>(package)->DepthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		mdSpi->OnRtnBarMarketData(static_cast<RtnBarMarketDataPackage*>(package)->BarMarketData);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int MdApiImpl::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
