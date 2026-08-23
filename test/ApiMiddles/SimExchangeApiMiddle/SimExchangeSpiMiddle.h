#pragma once
#include <QuantTrading/SimExchangeApi.h>


namespace quanttrading
{
class SimExchangeSpiMiddle : public SimExchangeSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(const OrderField* order) override;
	virtual void OnRtnTrade(const TradeField* trade) override;
};
}
