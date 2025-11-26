#pragma once
#include "SimExchangeApiBase.h"
#include "ThreadBase.h"
#include "Protocol.h"


class SimExchangeApiImpl : public SimExchangeApiBase
{
public:
	SimExchangeApiImpl();
	virtual void OnMessage(Package* package) override;
	
	virtual int ReqSEBrokerLogin(ReqSEBrokerLoginField* reqSEBrokerLogin, int requestID) override;
	virtual int ReqSEBrokerLogout(ReqSEBrokerLogoutField* reqSEBrokerLogout, int requestID) override;
	virtual int ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID) override;
	virtual int ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID) override;
	virtual int ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID) override;
	virtual int ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID) override;
	virtual int ReqQrySEInstrument(ReqQrySEInstrumentField* reqQrySEInstrument, int requestID) override;
};

