#pragma once
#include "SimExchangeApiBase.h"
#include "ThreadBase.h"
#include "Protocol.h"


class SimExchangeApiImpl : public SimExchangeApiBase
{
public:
	SimExchangeApiImpl();
	virtual void OnMessage(Package* package) override;
	
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID) override;
	virtual int ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID) override;
	virtual int ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID) override;
	virtual int ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID) override;
};

