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

	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;

	void ReqUserLogout();


    std::atomic<int> RtnMdCount{ 0 };
    std::atomic<int> RspMdUserLoginCount{ 0 };
    std::atomic<int> RspMdUserLogoutCount{ 0 };
private:
	void ReqUserLogin();
	void ReqSubscribeMd();


	MdApi* mdApi_;
	std::atomic<int> requestId_{0};
	ReqSubMarketDataField* reqSubMarketData_;
};
}
