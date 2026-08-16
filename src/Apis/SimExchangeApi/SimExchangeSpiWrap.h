#pragma once
#include <QuantTrading/SimExchangeCApi.h>
#include <QuantTrading/SimExchangeApi.h>


class SimExchangeSpiWrap : public SimExchangeSpi
{
public:
	void RegisterSpi(SimExchangeCSpi* spi);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(OrderField* order) override;
	virtual void OnRtnTrade(TradeField* trade) override;

private:
	SimExchangeCSpi* m_SimExchangeCSpi = nullptr;
};
