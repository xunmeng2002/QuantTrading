#include "MdApiMiddle.h"
#include "Logger.h"



MdApiMiddle* MdApiMiddle::CreateMdApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateMdApi");
	
	auto api = MdApi::CreateMdApi();
	auto apiMiddle = new MdApiMiddle();
	apiMiddle->m_MdApi = api;
	
	return apiMiddle;
}
const char* MdApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return MdApi::GetApiVersion();
}
bool MdApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return m_MdApi->Init();
}
void MdApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	m_MdApi->Join();
}
void MdApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	m_MdApi->Release();
}
void MdApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	m_MdApi->RegisterFront(address);
}
void MdApiMiddle::RegisterSpi(MdSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	m_MdApi->RegisterSpi(pSpi);
}

int MdApiMiddle::ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogin: RequestID:%d", requestID);
	if (reqMdUserLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLoginField:UserID:[%s], Password:[%s]",
			reqMdUserLogin->UserID, reqMdUserLogin->Password);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogin is nullptr");
	}
	return m_MdApi->ReqMdUserLogin(reqMdUserLogin, requestID);
}
int MdApiMiddle::ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogout: RequestID:%d", requestID);
	if (reqMdUserLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLogoutField:UserID:[%s]",
			reqMdUserLogout->UserID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogout is nullptr");
	}
	return m_MdApi->ReqMdUserLogout(reqMdUserLogout, requestID);
}
int MdApiMiddle::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSubMarketData: RequestID:%d", requestID);
	if (reqSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			reqSubMarketData->ExchangeID, reqSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketData is nullptr");
	}
	return m_MdApi->ReqSubMarketData(reqSubMarketData, requestID);
}
int MdApiMiddle::ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	WriteLog(LogLevel::Info, "ReqUnSubMarketData: RequestID:%d", requestID);
	if (reqUnSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqUnSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			reqUnSubMarketData->ExchangeID, reqUnSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqUnSubMarketData is nullptr");
	}
	return m_MdApi->ReqUnSubMarketData(reqUnSubMarketData, requestID);
}
