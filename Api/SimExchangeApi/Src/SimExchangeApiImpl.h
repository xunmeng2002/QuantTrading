#pragma once
#include "SimExchangeApiBase.h"
#include "ThreadBase.h"
#include "Protocol.h"


class SimExchangeApiImpl : public SimExchangeApiBase
{
public:
	SimExchangeApiImpl();
	virtual void OnMessage(Package* package) override;
	
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) override;
};

