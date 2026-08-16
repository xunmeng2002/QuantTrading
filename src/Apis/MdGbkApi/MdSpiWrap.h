#pragma once
#include <QuantTrading/MdCApi.h>
#include <QuantTrading/MdApi.h>


class MdSpiWrap : public MdSpi
{
public:
	void RegisterSpi(MdCSpi* spi);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) override;

private:
	MdCSpi* m_MdCSpi = nullptr;
};
