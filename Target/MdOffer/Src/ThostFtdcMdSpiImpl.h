#pragma once
#include "ThostFtdcMdSpiMiddle.h"
#include "Environment.h"
#include <set>
#include <string>



class CThostFtdcMdSpiImpl : public CThostFtdcMdSpiMiddle
{
public:
	CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi);

	virtual void OnFrontConnected() override;
	virtual void OnFrontDisconnected(int nReason) override;
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;

public:
	void SetAccountInfo(AccountInfo* accountInfo);

private:
	void ReqUserLogin();
	void ReqSubscribeMd();

private:
	CThostFtdcMdApi* m_MdApi;
	int m_RequestID;

	AccountInfo* m_AccountInfo;
};
