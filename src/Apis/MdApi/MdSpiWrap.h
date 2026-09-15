// 本文件由 ../Templates/Cpp/Api/SpiWrap.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/MdCApi.h>
#include <QuantTrading/MdApi.h>


namespace quanttrading
{
class MdSpiWrap : public MdSpi
{
public:
	void RegisterSpi(MdCSpi* spi);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;

private:
	MdCSpi* mdCSpi = nullptr;
};
}
