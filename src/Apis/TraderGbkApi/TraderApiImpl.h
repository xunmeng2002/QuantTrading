#pragma once
#include "TraderApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace quanttrading
{
class TraderApiImpl : public TraderApiBase
{
public:
	TraderApiImpl();
	virtual void OnMessage(spark::network::Package* package) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID) override;
	virtual int ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID) override;
	virtual int ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) override;
	virtual int ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID) override;
	virtual int ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;
};
}
