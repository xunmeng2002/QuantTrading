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
	virtual void RegisterSpi(SimExchangeSpi* pSpi) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	SimExchangeApi* simExchangeApi;
};
}
