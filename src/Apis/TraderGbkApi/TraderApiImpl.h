// 本文件由 ../Templates/Cpp/Api/ApiImpl.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "TraderApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace QuantTrading
{
class TraderApiImpl : public TraderApiBase
{
public:
	TraderApiImpl();
	virtual void OnMessage(Spark::Network::Package* package) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId) override;
	virtual int ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId) override;
	virtual int ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId) override;
	virtual int ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId) override;
	virtual int ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId) override;
	virtual int ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId) override;
	virtual int ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId) override;
};
}
