#pragma once
#include "MdSpiMiddle.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>

namespace quanttrading::testmdapi
{
class MdSpiImpl : public MdSpiMiddle
{
public:
	MdSpiImpl(MdApi* mdApi);
	~MdSpiImpl();

	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	virtual void OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;

private:
	void ReqUserLogin();
	void ReqSubscribeMd();

private:
	MdApi* m_MdApi;
	int m_RequestID;
	ReqSubMarketDataField* m_ReqSubMarketData;
};
}
