#pragma once
#include "InnerMdApi.h"
#include <set>
#include <atomic>
#include <mutex>

class SimExchange;
class InnerMdSpiImpl : public MdSpi
{
public:
	InnerMdSpiImpl(InnerMdApi* mdApi, const std::string& mdUser, const std::string& mdPassword);
	void SetSimExchange(SimExchange* simExchange);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;

	virtual void OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) override;


	void ReqMdUserLogin();
	void ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData);

private:
	InnerMdApi* m_MdApi;
	SimExchange* m_SimExchange;
	int m_RequestID;
	std::string m_MdUser;
	std::string m_MdPassword;
};
