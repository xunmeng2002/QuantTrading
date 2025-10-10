#pragma once
#include "ThostFtdcMdApi.h"


class CThostFtdcMdApiMiddle : public CThostFtdcMdApi
{
public:
	static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "");
	static const char *GetApiVersion();
	virtual void Release() override;
	virtual void Init() override;
	virtual int Join() override;
	virtual const char * GetTradingDay() override;
	virtual void RegisterFront(char * pszFrontAddress) override;
	virtual void RegisterNameServer(char * pszNsAddress) override;
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo) override;
	virtual void RegisterSpi(CThostFtdcMdSpi *pMdSpi) override;
	virtual int SubscribeMarketData(char * ppInstrumentID[], int nCount) override;
	virtual int UnSubscribeMarketData(char * ppInstrumentID[], int nCount) override;
	virtual int SubscribeForQuoteRsp(char * ppInstrumentID[], int nCount) override;
	virtual int UnSubscribeForQuoteRsp(char * ppInstrumentID[], int nCount) override;
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID) override;
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) override;
	virtual int ReqQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID) override;

private:
	CThostFtdcMdApi* m_MdApi;
};
