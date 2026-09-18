// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/SimExchangeApi.h>


namespace QuantTrading
{
class SimExchangeApiMiddle : public SimExchangeApi
{
public:
	static SimExchangeApiMiddle* CreateSimExchangeApiMiddle();
	static const char* GetApiVersion();
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(SimExchangeSpi* spi) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId) override;

private:
	SimExchangeApi* simExchangeApi_;
};
}
