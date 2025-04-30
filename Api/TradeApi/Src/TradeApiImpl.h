#pragma once
#include "TradeApiBase.h"
#include "ThreadBase.h"
#include "Protocol.h"


class TradeApiImpl : public TradeApiBase
{
public:
	TradeApiImpl();
	virtual void OnMessage(Package* package) override;
	
	virtual int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID) override;
	virtual int ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID) override;
	virtual int ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID) override;
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) override;
	virtual int ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID) override;
	virtual int ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) override;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) override;
};

