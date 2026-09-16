#pragma once
#include "MdSpiMiddle.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <atomic>

namespace QuantTrading::TestMdApi
{
class MdSpiImpl : public MdSpiMiddle
{
public:
	MdSpiImpl(MdApi* mdApi);
	~MdSpiImpl();

	std::atomic<int> m_RtnMdCount{0};
	std::atomic<int> m_RspMdUserLoginCount{0};
	std::atomic<int> m_RspMdUserLogoutCount{0};

	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;

	void ReqUserLogout();

private:
	void ReqUserLogin();
	void ReqSubscribeMd();

private:
	MdApi* m_MdApi;
	std::atomic<int> m_RequestID{0};
	ReqSubMarketDataField* m_ReqSubMarketData;
};
}
