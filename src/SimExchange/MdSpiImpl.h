#pragma once
#include <QuantTrading/MdApi.h>
#include <set>
#include <atomic>
#include <mutex>

namespace quanttrading::simexchange
{
class SimExchange;
class MdSpiImpl : public MdSpi
{
public:
	MdSpiImpl(MdApi* mdApi, const std::string& mdUser, const std::string& mdPassword);
	void SetSimExchange(SimExchange* simExchange);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;

	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;


	void ReqMdUserLogin();
	void ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData);

private:
	MdApi* m_MdApi;
	SimExchange* m_SimExchange;
	int m_RequestID;
	std::string m_MdUser;
	std::string m_MdPassword;
};
}
