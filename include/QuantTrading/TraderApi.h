#pragma once
#include "Fields.h"
#include <QuantTrading/TraderApi/TraderApiExport.h>

namespace quanttrading
{
class TraderSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(const OrderField* order) {}
	virtual void OnRtnTrade(const TradeField* trade) {}
	virtual void OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer) {}
	virtual void OnRtnAccountLogout(const AccountLogoutField* accountLogout) {}
};

class TRADERAPI_EXPORTS TraderApi
{
public:
	static TraderApi* CreateTraderApi();
	static const char* GetApiVersion();
	virtual bool Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(TraderSpi* pSpi) = 0;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) = 0;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) = 0;
	virtual int ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID) = 0;
	virtual int ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID) = 0;
	virtual int ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID) = 0;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) = 0;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) = 0;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) = 0;
	virtual int ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) = 0;
	virtual int ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID) = 0;
	virtual int ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) = 0;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};
}
