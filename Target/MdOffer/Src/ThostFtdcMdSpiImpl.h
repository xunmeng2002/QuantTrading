#pragma once
#include "ThostFtdcMdSpiMiddle.h"
#include "Environment.h"
#include "Fields.h"
#include <set>
#include <map>
#include <string>


class MdKernel;
class CThostFtdcMdSpiImpl : public CThostFtdcMdSpiMiddle
{
public:
	CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi, MdKernel* mdKernel);

	virtual void OnFrontConnected() override;
	virtual void OnFrontDisconnected(int nReason) override;
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) override;

	void SetAccountInfo(AccountInfo* accountInfo);
	void SubscribeMd(ReqSubMarketDataField* reqSubMd);
private:
	void ReqUserLogin();

private:
	CThostFtdcMdApi* m_MdApi;
	MdKernel* m_MdKernel;
	int m_RequestID;
	AccountInfo* m_AccountInfo;
	std::map<std::string, ReqSubMarketDataField*> m_ReqSubMds;;
};
