#pragma once
#include "ThostFtdcMdApi.h"


class CThostFtdcMdApiMiddle : public CThostFtdcMdApi
{
public:
	static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "");
	static const char *GetApiVersion();
	virtual void Release();
	virtual void Init();
	virtual int Join();
	virtual const char * GetTradingDay();
	virtual void RegisterFront(char * pszFrontAddress);
	virtual void RegisterNameServer(char * pszNsAddress);
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo);
	virtual void RegisterSpi(CThostFtdcMdSpi *pMdSpi);
	virtual int SubscribeMarketData(char * ppInstrumentID[], int nCount);
	virtual int UnSubscribeMarketData(char * ppInstrumentID[], int nCount);
	virtual int SubscribeForQuoteRsp(char * ppInstrumentID[], int nCount);
	virtual int UnSubscribeForQuoteRsp(char * ppInstrumentID[], int nCount);
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID);
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID);

private:
	CThostFtdcMdApi* m_MdApi;
};
