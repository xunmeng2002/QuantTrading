#pragma once
#include "SimExchangeApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace quanttrading
{
class SimExchangeApiImpl : public SimExchangeApiBase
{
public:
	SimExchangeApiImpl();
	virtual void OnMessage(spark::network::Package* package) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;
};
}
