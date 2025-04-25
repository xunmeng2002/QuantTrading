#pragma once
#include "MdApi.h"


class MdSpiMiddle : public MdSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(RspInfoField* rspInfo, RspMdUserLogoutField* rspMdUserLogout, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) override;
};
