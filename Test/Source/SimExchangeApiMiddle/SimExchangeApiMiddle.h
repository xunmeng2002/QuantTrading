#pragma once
#include "SimExchangeApi.h"


class SimExchangeApiMiddle : public SimExchangeApi
{
public:
	static SimExchangeApiMiddle* CreateSimExchangeApiMiddle();
	static const char* GetApiVersion();
	virtual void Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(SimExchangeSpi* pSpi) override;
	
	virtual int ReqSEBrokerLogin(ReqSEBrokerLoginField* reqSEBrokerLogin, int requestID) override;
	virtual int ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID) override;
	virtual int ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID) override;
	virtual int ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID) override;
	virtual int ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID) override;
	virtual int ReqQrySEInstrument(ReqQrySEInstrumentField* reqQrySEInstrument, int requestID) override;

private:
	SimExchangeApi* m_SimExchangeApi;
};
