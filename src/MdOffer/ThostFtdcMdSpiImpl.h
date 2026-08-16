#pragma once
#include "ThostFtdcMdSpiMiddle.h"
#include "Environment.h"
#include <QuantTrading/Fields.h>
#include <atomic>
#include <mutex>
#include <list>
#include <set>
#include <map>
#include <vector>
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
	void SubscribeMd(const ReqSubMarketDataField* reqSubMd);
	void SubscribeMds(const std::list<const ReqSubMarketDataField*>& reqSubMds);
private:
	void ReqUserLogin();

private:
	CThostFtdcMdApi* m_MdApi;
	MdKernel* m_MdKernel;
	std::atomic<bool> m_IsLogged;
	int m_RequestID;
	AccountInfo* m_AccountInfo;
	std::map<std::string, const ReqSubMarketDataField*> m_ReqSubMds;
	std::vector<const char*> m_ReqSubInstruments;
	std::mutex m_Mutex;
};
