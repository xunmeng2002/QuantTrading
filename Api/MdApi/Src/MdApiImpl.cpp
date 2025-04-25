#include "MdApiImpl.h"
#include "Items.h"
#include "Packages.h"
#include "MemCacheTemplateSingleton.h"
#include "Error.h"
#include <cstring>


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
		m_MdSpi->OnRspMdUserLogin(((RspMdUserLoginPackage*)package)->RspInfo, ((RspMdUserLoginPackage*)package)->RspMdUserLogin, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		m_MdSpi->OnRspMdUserLogout(((RspMdUserLogoutPackage*)package)->RspInfo, ((RspMdUserLogoutPackage*)package)->RspMdUserLogout, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRspSubMarketData(((RspSubMarketDataPackage*)package)->RspInfo, ((RspSubMarketDataPackage*)package)->RspSubMarketData, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRspUnSubMarketData(((RspUnSubMarketDataPackage*)package)->RspInfo, ((RspUnSubMarketDataPackage*)package)->RspUnSubMarketData, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRtnDepthMarketData(((RtnDepthMarketDataPackage*)package)->DepthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRtnBarMarketData(((RtnBarMarketDataPackage*)package)->BarMarketData);
		break;
	}
	default:
		break;
	}
	package->Free();
}


int MdApiImpl::ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int MdApiImpl::ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int MdApiImpl::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}

