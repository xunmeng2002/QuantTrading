#pragma once
#include "TradeFields.h"
#include "LoggerInterface.h"

#ifdef WIN32
#define TRADE_CAPI_CALL _stdcall
#ifdef LIB_TRADE_CAPI_EXPORT
#define TRADE_CAPI_EXPORT __declspec(dllexport)
#else
#define TRADE_CAPI_EXPORT __declspec(dllimport)
#endif
#else
#define TRADE_CAPI_CALL
#define TRADE_CAPI_EXPORT
#endif


extern "C"
{
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnConnected)();
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnDisConnected)();
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspAccountLogin)(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspAccountLogout)(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryHolderAccount)(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryCapital)(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryPosition)(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryOrder)(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryTrade)(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryInstrument)(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryOptionInstrument)(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryCommissionRate)(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspQryMoneyTransfer)(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspInsertOrder)(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRspCancelOrder)(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRtnOrder)(OrderField* order);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRtnTrade)(TradeField* trade);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRtnMoneyTransfer)(MoneyTransferField* moneyTransfer);
	typedef TRADE_CAPI_EXPORT void (TRADE_CAPI_CALL *OnRtnAccountLogout)(AccountLogoutField* accountLogout);
	
	struct TRADE_CAPI_EXPORT TradeCSpi
	{
	public:
		OnConnected OnConnected;
		OnDisConnected OnDisConnected;
		OnRspAccountLogin OnRspAccountLogin;
		OnRspAccountLogout OnRspAccountLogout;
		OnRspQryHolderAccount OnRspQryHolderAccount;
		OnRspQryCapital OnRspQryCapital;
		OnRspQryPosition OnRspQryPosition;
		OnRspQryOrder OnRspQryOrder;
		OnRspQryTrade OnRspQryTrade;
		OnRspQryInstrument OnRspQryInstrument;
		OnRspQryOptionInstrument OnRspQryOptionInstrument;
		OnRspQryCommissionRate OnRspQryCommissionRate;
		OnRspQryMoneyTransfer OnRspQryMoneyTransfer;
		OnRspInsertOrder OnRspInsertOrder;
		OnRspCancelOrder OnRspCancelOrder;
		OnRtnOrder OnRtnOrder;
		OnRtnTrade OnRtnTrade;
		OnRtnMoneyTransfer OnRtnMoneyTransfer;
		OnRtnAccountLogout OnRtnAccountLogout;
	};

	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL CreateTradeApi();
	TRADE_CAPI_EXPORT const char* TRADE_CAPI_CALL GetApiVersion();
	TRADE_CAPI_EXPORT void SetExternLogger(WriteLogFunc externLogger);
	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL Init();
	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL Join();
	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL Release();
	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL RegisterFront(const char* address);
	TRADE_CAPI_EXPORT void TRADE_CAPI_CALL RegisterSpi(TradeCSpi* spi);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	TRADE_CAPI_EXPORT int TRADE_CAPI_CALL ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);
}
