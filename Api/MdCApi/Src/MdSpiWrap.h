#pragma once
#include "MdApi.h"
#include "MdCApi.h"


class MdSpiWrap : public MdSpi
{
public:
	void RegisterSpi(MdCSpi* spi);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) override;

private:
	MdCSpi* m_MdCSpi = nullptr;
};
