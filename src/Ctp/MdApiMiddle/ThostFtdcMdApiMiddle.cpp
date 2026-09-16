// 本文件由 ../Templates/Cpp/LibTest/CtpWrapper/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "ThostFtdcMdApiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


CThostFtdcMdApi *CThostFtdcMdApiMiddle::CreateFtdcMdApi(const char *pszFlowPath)
{
	WriteLog(LogLevel::Info, "CreateFtdcMdApi: pszFlowPath[%s]", pszFlowPath);
	
	auto api = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath);
	auto apiMiddle = new CThostFtdcMdApiMiddle();
	apiMiddle->mdApi = api;
	
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

	return mdApi->Release();
}
void CThostFtdcMdApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init:");

	return mdApi->Init();
}
int CThostFtdcMdApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join:");

	return mdApi->Join();
}
const char * CThostFtdcMdApiMiddle::GetTradingDay()
{
	WriteLog(LogLevel::Info, "GetTradingDay:");

	return mdApi->GetTradingDay();
}
void CThostFtdcMdApiMiddle::RegisterFront(char * pszFrontAddress)
{
	WriteLog(LogLevel::Info, "RegisterFront: pszFrontAddress[%s]", pszFrontAddress);

	return mdApi->RegisterFront(pszFrontAddress);
}
void CThostFtdcMdApiMiddle::RegisterNameServer(char * pszNsAddress)
{
	WriteLog(LogLevel::Info, "RegisterNameServer: pszNsAddress[%s]", pszNsAddress);

	return mdApi->RegisterNameServer(pszNsAddress);
}
void CThostFtdcMdApiMiddle::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo)
{
	WriteLog(LogLevel::Info, "RegisterFensUserInfo:");
	WriteFensUserInfo(pFensUserInfo);

	return mdApi->RegisterFensUserInfo(pFensUserInfo);
}
void CThostFtdcMdApiMiddle::RegisterSpi(CThostFtdcMdSpi *pMdSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi:");

	return mdApi->RegisterSpi(pMdSpi);
}
int CThostFtdcMdApiMiddle::SubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "SubscribeMarketData: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return mdApi->SubscribeMarketData(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::UnSubscribeMarketData(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "UnSubscribeMarketData: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return mdApi->UnSubscribeMarketData(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::SubscribeForQuoteRsp(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "SubscribeForQuoteRsp: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return mdApi->SubscribeForQuoteRsp(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::UnSubscribeForQuoteRsp(char * ppInstrumentID[], int nCount)
{
	WriteLog(LogLevel::Info, "UnSubscribeForQuoteRsp: nCount[%d]", nCount);
	for (auto i = 0; i < nCount; ++i)
	{
		WriteLog(LogLevel::Info, "ppInstrumentID:%s", ppInstrumentID[i]);
	}

	return mdApi->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}
int CThostFtdcMdApiMiddle::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogin: nRequestID[%d]", nRequestID);
	WriteReqUserLogin(pReqUserLogin);

	return mdApi->ReqUserLogin(pReqUserLogin, nRequestID);
}
int CThostFtdcMdApiMiddle::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogout: nRequestID[%d]", nRequestID);
	WriteUserLogout(pUserLogout);

	return mdApi->ReqUserLogout(pUserLogout, nRequestID);
}
int CThostFtdcMdApiMiddle::ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMulticastInstrument: nRequestID[%d]", nRequestID);
	WriteQryMulticastInstrument(pQryMulticastInstrument);

	return mdApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
}
