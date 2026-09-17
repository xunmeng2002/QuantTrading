// 本文件由 ../Templates/Cpp/ApiTest/SpiMiddle.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/MdApi.h>


namespace QuantTrading
{
class MdSpiMiddle : public MdSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;
};
}
