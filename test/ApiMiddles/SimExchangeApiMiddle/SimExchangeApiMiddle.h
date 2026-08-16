#pragma once
#include <QuantTrading/SimExchangeApi.h>


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
	
	virtual int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	SimExchangeApi* m_SimExchangeApi;
};
