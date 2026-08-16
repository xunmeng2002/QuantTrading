#pragma once
#include "Fields.h"
#include <QuantTrading/TraderApi/TraderApiExport.h>

#ifdef WIN32
#define TRADERAPI_CALL _stdcall
#else
#define TRADERAPI_CALL
#endif


extern "C"
{
	typedef void (TRADERAPI_CALL *OnConnected)();
	typedef void (TRADERAPI_CALL *OnDisConnected)();
	typedef void (TRADERAPI_CALL *OnRspAccountLogin)(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspAccountLogout)(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryHolderAccount)(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCapital)(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryPosition)(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOrder)(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryTrade)(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryInstrument)(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOptionInstrument)(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCommissionRate)(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryMoneyTransfer)(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspInsertOrder)(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspCancelOrder)(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRtnOrder)(OrderField* order);
	typedef void (TRADERAPI_CALL *OnRtnTrade)(TradeField* trade);
	typedef void (TRADERAPI_CALL *OnRtnMoneyTransfer)(MoneyTransferField* moneyTransfer);
	typedef void (TRADERAPI_CALL *OnRtnAccountLogout)(AccountLogoutField* accountLogout);
	
	struct TraderCSpi
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

	TRADERAPI_EXPORTS void TRADERAPI_CALL CreateTraderCApi();
	TRADERAPI_EXPORTS const char* TRADERAPI_CALL GetApiVersion();
	TRADERAPI_EXPORTS bool TRADERAPI_CALL Init();
	TRADERAPI_EXPORTS void TRADERAPI_CALL Join();
	TRADERAPI_EXPORTS void TRADERAPI_CALL Release();
	TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterFront(const char* address);
	TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterSpi(TraderCSpi* spi);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);
}
