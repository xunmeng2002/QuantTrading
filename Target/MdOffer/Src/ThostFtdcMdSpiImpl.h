#pragma once
#include "ThostFtdcMdSpiMiddle.h"
#include "CtpAccountInfo.h"
#include <set>
#include <string>



class CThostFtdcMdSpiImpl : public CThostFtdcMdSpiMiddle
{
public:
	CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi);

	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

public:
	void SetCtpAccountInfo(CtpAccountInfo* accountInfo);

private:
	void ReqUserLogin();
	void ReqSubscribeMd();

private:
	CThostFtdcMdApi* m_MdApi;
	int m_RequestID;

	CtpAccountInfo* m_CtpAccountInfo;
};
