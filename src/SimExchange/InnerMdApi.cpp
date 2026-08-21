#include "InnerMdApi.h"
#include "Error.h"
#include "Packages.h"
#include "PackageFactory.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Network/Protocol/Items.h>
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>
#include <cstring>

using namespace spark;
using namespace spark::core;

InnerMdApi::InnerMdApi(const char* name)
	:m_ProtocolType(ProtocolTypeType::Xtp), m_MdSpi(nullptr), m_SessionID(0)
{
	m_IOThread = new IOThread(name);
	m_Protocol = new Protocol(m_ProtocolType, ServerTypeType::Client, IOModelType::Select, 100, new PackageFactory());
	m_Protocol->Subscribe(this);
	m_Protocol->SetIOThread(m_IOThread);
}

void InnerMdApi::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = sessionID;
	m_MdSpi->OnConnected();
}
void InnerMdApi::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	m_SessionID = -1;
	m_MdSpi->OnDisConnected();
}
void InnerMdApi::OnMessage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case RspMdUserLoginPackage::PackageID:
	{
		m_MdSpi->OnRspMdUserLogin(((RspMdUserLoginPackage*)package)->RspMdUserLogin, ((RspMdUserLoginPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		m_MdSpi->OnRspMdUserLogout(((RspMdUserLogoutPackage*)package)->RspMdUserLogout, ((RspMdUserLogoutPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRspSubMarketData(((RspSubMarketDataPackage*)package)->RspSubMarketData, ((RspSubMarketDataPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		m_MdSpi->OnRspUnSubMarketData(((RspUnSubMarketDataPackage*)package)->RspUnSubMarketData, ((RspUnSubMarketDataPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
	package->Deallocate();
}


bool InnerMdApi::Init()
{
	return m_Protocol->Init() && m_Protocol->Start();
}
void InnerMdApi::Join()
{
	m_Protocol->Join();
}
void InnerMdApi::Release()
{
	m_Protocol->Stop();
	m_Protocol->Join();
	delete this;
}
void InnerMdApi::RegisterFront(const char* address)
{
	m_Protocol->RegisterFront(address);
}
void InnerMdApi::RegisterSpi(MdSpi* spi)
{
	m_MdSpi = spi;
}


int InnerMdApi::ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));

	int result = (m_Protocol->Send(reqPackage)) ? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int InnerMdApi::ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));

	int result = (m_Protocol->Send(reqPackage)) ? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int InnerMdApi::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));

	int result = (m_Protocol->Send(reqPackage)) ? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int InnerMdApi::ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));

	int result = (m_Protocol->Send(reqPackage)) ? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}



