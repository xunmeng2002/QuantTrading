#pragma once
#include <QuantTrading/TraderApi.h>


namespace quanttrading
{
class TraderSpiMiddle : public TraderSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(const OrderField* order) override;
	virtual void OnRtnTrade(const TradeField* trade) override;
	virtual void OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer) override;
	virtual void OnRtnAccountLogout(const AccountLogoutField* accountLogout) override;
};
}
