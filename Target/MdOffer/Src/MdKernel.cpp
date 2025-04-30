#include "MdKernel.h"
#include "Logger.h"
#include "Error.h"
#include "Utility.h"
#include "TimeUtility.h"
#include "MemCacheTemplateSingleton.h"
#include "MdSnap.h"



MdKernel::MdKernel(const char* mdUser, const char* password)
	:ThreadBase("MdKernel"), m_MdFront(nullptr), m_MdSpi(nullptr)
{
	Strcpy(m_MdUser, mdUser);
	Strcpy(m_MdPassword, password);

	m_MinuteBar = new MinuteBar();
	m_MinuteBar->Subscribe(this);
	m_ReqSubMarketData = new ReqSubMarketDataField();
	m_BarMdPackage = new RtnBarMarketDataPackage();
}
void MdKernel::SetMdFront(MdFront* mdFront)
{
	m_MdFront = mdFront;
	m_MdFront->Subscribe(this);
}
void MdKernel::SetMdSpi(CThostFtdcMdSpiImpl* mdSpi)
{
	m_MdSpi = mdSpi;
}
void MdKernel::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdKernel: OnConnect SessionID:%lld, IP:%s, Port:%d", sessionID, ip, port);
}
void MdKernel::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "MdKernel: OnDisConnect SessionID:%lld, IP:%s, Port:%d", sessionID, ip, port);

	NotifyDisConnectPackage* package = NotifyDisConnectPackage::Allocate();
	package->Prepare(0, false, 0);
	package->NotifyDisConnect = ::Allocate<NotifyDisConnectField>();
	package->NotifyDisConnect->SessionID = sessionID;
	Strcpy(package->NotifyDisConnect->IPAddress, ip);
	package->NotifyDisConnect->Port = port;

	std::lock_guard<std::mutex> guard(m_Mutex);
	m_RecvPackages.push_back(package);
}
void MdKernel::OnMessage(Package* package)
{
	std::lock_guard<std::mutex> guard(m_Mutex);
	m_RecvPackages.push_back(package);

	m_ThreadConditionVariable.notify_one();
}
void MdKernel::OnBarMarketData(BarMarketDataField* bar)
{
	m_BarMdPackage->BarMarketData = bar;

	Strcpy(m_ReqSubMarketData->ExchangeID, bar->ExchangeID);
	Strcpy(m_ReqSubMarketData->InstrumentID, bar->InstrumentID);
	PushToAllSubscribed(m_ReqSubMarketData, m_BarMdPackage);
}

void MdKernel::Run()
{
	CheckEvent();
	HandlePackage();
}

void MdKernel::CheckEvent()
{
	std::unique_lock<std::mutex> guard(m_Mutex);
	m_ThreadConditionVariable.wait_for(guard, m_TimeOut, [&] {return (!m_RecvPackages.empty()); });
}
int MdKernel::HandlePackage()
{
	Package* package = nullptr;
	while ((package = GetPackage()) != nullptr)
	{
		switch (package->Head.PackageID)
		{
		case NotifyDisConnectPackage::PackageID:
		{
			return HandleNotifyDisConnect((NotifyDisConnectPackage*)package);
		}
		case ReqMdUserLoginPackage::PackageID:
		{
			return HandleReqMdUserLogin((ReqMdUserLoginPackage*)package);
		}
		case ReqSubMarketDataPackage::PackageID:
		{
			return HandleReqSubMarketData((ReqSubMarketDataPackage*)package);
		}
		case RtnDepthMarketDataPackage::PackageID:
		{
			return HandleRtnDepthMarketData((RtnDepthMarketDataPackage*)package);
		}
		default:
			package->Free();
			break;
		}
	}
	return 0;
}
int MdKernel::HandleNotifyDisConnect(NotifyDisConnectPackage* package)
{
	m_LoggedSessions.erase(package->NotifyDisConnect->SessionID);
	m_SessionSubscribeInstruments.erase(package->NotifyDisConnect->SessionID);
	package->Free();
	return 0;
}
int MdKernel::HandleReqMdUserLogin(ReqMdUserLoginPackage* package)
{
	auto errorID = ErrorNone;
	if (strcmp(package->ReqMdUserLogin->UserID, m_MdUser) != 0 || strcmp(package->ReqMdUserLogin->Password, m_MdPassword) != 0)
	{
		errorID = ErrorIncorrectPassword;
	}
	else
	{
		m_LoggedSessions.insert(package->SessionID);
	}

	RspMdUserLoginPackage* rspPackage = RspMdUserLoginPackage::Allocate();
	rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);

	rspPackage->RspInfo = ::Allocate<RspInfoField>();
	rspPackage->RspInfo->ErrorID = errorID;
	Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));

	rspPackage->RspMdUserLogin = ::Allocate<RspMdUserLoginField>();
	Strcpy(rspPackage->RspMdUserLogin->UserID, package->ReqMdUserLogin->UserID);
	rspPackage->RspMdUserLogin->SessionID = package->SessionID;
	if (errorID == ErrorNone)
	{
		GetLocalDateTime(rspPackage->RspMdUserLogin->LoginDate, rspPackage->RspMdUserLogin->LoginTime);
	}

	WriteLog(LogLevel::Info, "HandleReqMdUserLogin: ReqMdUserLoginPackage:%s, RspMdUserLoginPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

	m_MdFront->Send(rspPackage);
	rspPackage->Free();

	package->Free();
	return 0;
}
int MdKernel::HandleReqMdUserLogout(ReqMdUserLogoutPackage* package)
{
	m_LoggedSessions.erase(package->SessionID);
	m_SessionSubscribeInstruments[package->SessionID].clear();

	RspMdUserLogoutPackage* rspPackage = RspMdUserLogoutPackage::Allocate();
	rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);
	
	rspPackage->RspInfo = ::Allocate<RspInfoField>();
	rspPackage->RspInfo->ErrorID = ErrorNone;
	Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));

	rspPackage->RspMdUserLogout = ::Allocate<RspMdUserLogoutField>();
	Strcpy(rspPackage->RspMdUserLogout->UserID, package->ReqMdUserLogout->UserID);



	WriteLog(LogLevel::Info, "HandleReqMdUserLogout: ReqMdUserLogoutPackage:%s, RspMdUserLogoutPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

	m_MdFront->Send(rspPackage);
	rspPackage->Free();

	package->Free();
	return 0;
}
int MdKernel::HandleReqSubMarketData(ReqSubMarketDataPackage* package)
{
	WriteLog(LogLevel::Info, "HandleReqSubMarketData: %s", package->GetDebugString());
	auto reqSubMarketData = package->ReqSubMarketData;
	auto errorID = ErrorNone;
	auto loggedSessionIt = m_LoggedSessions.find(package->SessionID);
	if (loggedSessionIt == m_LoggedSessions.end())
	{
		errorID = ErrorUserNotLogin;
	}
	else
	{
		auto it = m_SubscribeInstruments.find(reqSubMarketData);
		if (it == m_SubscribeInstruments.end())
		{
			m_SubscribeInstruments.insert(reqSubMarketData);
			m_MinuteBar->ReqSubMarketData(reqSubMarketData);
			m_MdSpi->SubscribeMd(reqSubMarketData);
		}
		auto& sessionSubscribeInstruments = m_SessionSubscribeInstruments[package->SessionID];
		if (sessionSubscribeInstruments.find(reqSubMarketData) == sessionSubscribeInstruments.end())
		{
			sessionSubscribeInstruments.insert(reqSubMarketData);
			package->ReqSubMarketData = nullptr;
		}
	}

	RspSubMarketDataPackage* rspPackage = RspSubMarketDataPackage::Allocate();
	rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);
	rspPackage->RspInfo = ::Allocate<RspInfoField>();
	rspPackage->RspInfo->ErrorID = errorID;
	Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	rspPackage->RspSubMarketData = ::Allocate<RspSubMarketDataField>();
	Strcpy(rspPackage->RspSubMarketData->ExchangeID, reqSubMarketData->ExchangeID);
	Strcpy(rspPackage->RspSubMarketData->InstrumentID, reqSubMarketData->InstrumentID);
	m_MdFront->Send(rspPackage);
	rspPackage->Free();
	package->Free();

	auto rtnDepthMdPackage = MdSnap::GetInstance().GetDepthMd(reqSubMarketData->ExchangeID, reqSubMarketData->InstrumentID);
	if (rtnDepthMdPackage != nullptr)
	{
		rtnDepthMdPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);
		m_MdFront->Send(rtnDepthMdPackage);
	}
	return 0;
}
int MdKernel::HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package)
{
	m_MinuteBar->OnDepthMarketData(package->DepthMarketData);
	package = MdSnap::GetInstance().AddDepthMd(package);
	Strcpy(m_ReqSubMarketData->ExchangeID, package->DepthMarketData->ExchangeID);
	Strcpy(m_ReqSubMarketData->InstrumentID, package->DepthMarketData->InstrumentID);
	PushToAllSubscribed(m_ReqSubMarketData, package);
	return 0;
}

Package* MdKernel::GetPackage()
{
	std::lock_guard<std::mutex> guard(m_Mutex);
	if (m_RecvPackages.empty())
	{
		return nullptr;
	}
	auto package = m_RecvPackages.front();
	m_RecvPackages.pop_front();
	return package;
}
void MdKernel::PushToAll(Package* package)
{
	for (auto& item : m_SessionSubscribeInstruments)
	{
		package->Prepare(item.first, false, 0);
		if (!m_MdFront->Send(package))
		{
			WriteLog(LogLevel::Error, "PushToAll MdFront->Send Failed. SessionID:%lld, Package:%s", item.first, package->GetDebugString());
		}
	}
}
void MdKernel::PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package)
{
	for (auto& item : m_SessionSubscribeInstruments)
	{
		auto& instruments = item.second;
		if (instruments.find(reqSubMarketData) != instruments.end())
		{
			package->Prepare(item.first, false, 0);
			if (!m_MdFront->Send(package))
			{
				WriteLog(LogLevel::Error, "PushToAllSubscribed MdFront->Send Failed. SessionID:%lld, Package:%s", item.first, package->GetDebugString());
			}
		}
	}
}