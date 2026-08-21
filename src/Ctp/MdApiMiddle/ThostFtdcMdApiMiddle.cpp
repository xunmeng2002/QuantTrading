#include "ThostFtdcMdApiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;


CThostFtdcMdApi *CThostFtdcMdApiMiddle::CreateFtdcMdApi(const char *pszFlowPath)
{
	WriteLog(LogLevel::Info, "CreateFtdcMdApi: pszFlowPath[%s]", pszFlowPath);
	
	auto api = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath);
	auto apiMiddle = new CThostFtdcMdApiMiddle();
	apiMiddle->m_MdApi = api;
	
	return apiMiddle;
}

const char *CThostFtdcMdApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion:");
	
	return CThostFtdcMdApi::GetApiVersion();
}

void CThostFtdcMdApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release:");

	return m_MdApi->Release();
}
void CThostFtdcMdApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init:");

	return m_MdApi->Init();
}
int CThostFtdcMdApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join:");

	return m_MdApi->Join();
}
const char * CThostFtdcMdApiMiddle::GetTradingDay()
{
	WriteLog(LogLevel::Info, "GetTradingDay:");

	return m_MdApi->GetTradingDay();
}
void CThostFtdcMdApiMiddle::RegisterFront(char * pszFrontAddress)
{
	WriteLog(LogLevel::Info, "RegisterFront: pszFrontAddress[%s]", pszFrontAddress);

	return m_MdApi->RegisterFront(pszFrontAddress);
}
void CThostFtdcMdApiMiddle::RegisterNameServer(char * pszNsAddress)
{
	WriteLog(LogLevel::Info, "RegisterNameServer: pszNsAddress[%s]", pszNsAddress);

	return m_MdApi->RegisterNameServer(pszNsAddress);
}
void CThostFtdcMdApiMiddle::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo)
{
	WriteLog(LogLevel::Info, "RegisterFensUserInfo:");
	WriteFensUserInfo(pFensUserInfo);

	return m_MdApi->RegisterFensUserInfo(pFensUserInfo);
}
void CThostFtdcMdApiMiddle::RegisterSpi(CThostFtdcMdSpi *pMdSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi:");

	return m_MdApi->RegisterSpi(pMdSpi);
}
int CThostFtdcMdApiMiddle::SubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "SubscribeMarketData: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return m_MdApi->SubscribeMarketData(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::UnSubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "UnSubscribeMarketData: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return m_MdApi->UnSubscribeMarketData(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::SubscribeForQuoteRsp(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "SubscribeForQuoteRsp: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return m_MdApi->SubscribeForQuoteRsp(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::UnSubscribeForQuoteRsp(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "UnSubscribeForQuoteRsp: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return m_MdApi->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogin: nRequestID[%d]", nRequestID);
	WriteReqUserLogin(pReqUserLogin);

	return m_MdApi->ReqUserLogin(pReqUserLogin, nRequestID);
}
int CThostFtdcMdApiMiddle::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogout: nRequestID[%d]", nRequestID);
	WriteUserLogout(pUserLogout);

	return m_MdApi->ReqUserLogout(pUserLogout, nRequestID);
}
int CThostFtdcMdApiMiddle::ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMulticastInstrument: nRequestID[%d]", nRequestID);
	WriteQryMulticastInstrument(pQryMulticastInstrument);

	return m_MdApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
}
