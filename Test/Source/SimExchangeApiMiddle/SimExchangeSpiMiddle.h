#pragma once
#include "SimExchangeApi.h"


class SimExchangeSpiMiddle : public SimExchangeSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspSEBrokerLogin(RspSEBrokerLoginField* rspSEBrokerLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSEBrokerLogout(RspSEBrokerLogoutField* rspSEBrokerLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQrySEOrder(SEOrderField* sEOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQrySETrade(SETradeField* sETrade, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQrySEInstrument(SEInstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnSEOrder(SEOrderField* sEOrder) override;
	virtual void OnRtnSETrade(SETradeField* sETrade) override;
};
