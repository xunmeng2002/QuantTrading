#pragma once
#include "TradeFields.h"
#include "LoggerInterface.h"

#ifdef WIN32
#ifdef LIB_TRADE_API_EXPORT
#define TRADE_API_EXPORT				__declspec(dllexport)
#else
#define TRADE_API_EXPORT				__declspec(dllimport)
#endif
#else
#define TRADE_API_EXPORT
#endif


class TradeSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(OrderField* order) {}
	virtual void OnRtnTrade(TradeField* trade) {}
	virtual void OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer) {}
	virtual void OnRtnAccountLogout(AccountLogoutField* accountLogout) {}
};

class TRADE_API_EXPORT TradeApi
{
public:
	static TradeApi* CreateTradeApi();
	static const char* GetApiVersion();
	static void SetExternLogger(WriteLogFunc externLogger);
	virtual bool Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(TradeSpi* pSpi) = 0;
	
	virtual int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID) = 0;
	virtual int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID) = 0;
	virtual int ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID) = 0;
	virtual int ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID) = 0;
	virtual int ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID) = 0;
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) = 0;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) = 0;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) = 0;
	virtual int ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) = 0;
	virtual int ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID) = 0;
	virtual int ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) = 0;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};

