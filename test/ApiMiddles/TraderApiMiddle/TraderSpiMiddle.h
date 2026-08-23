#pragma once
#include <QuantTrading/TraderApi.h>


namespace quanttrading
{
class TraderSpiMiddle : public TraderSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(OrderField* order) override;
	virtual void OnRtnTrade(TradeField* trade) override;
	virtual void OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer) override;
	virtual void OnRtnAccountLogout(AccountLogoutField* accountLogout) override;
};
}
