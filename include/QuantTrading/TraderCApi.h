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
	typedef void (TRADERAPI_CALL *OnRspAccountLogin)(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspAccountLogout)(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryHolderAccount)(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCapital)(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryPosition)(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOrder)(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryTrade)(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryInstrument)(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOptionInstrument)(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCommissionRate)(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryMoneyTransfer)(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspInsertOrder)(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspCancelOrder)(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (TRADERAPI_CALL *OnRtnOrder)(const OrderField* order);
	typedef void (TRADERAPI_CALL *OnRtnTrade)(const TradeField* trade);
	typedef void (TRADERAPI_CALL *OnRtnMoneyTransfer)(const MoneyTransferField* moneyTransfer);
	typedef void (TRADERAPI_CALL *OnRtnAccountLogout)(const AccountLogoutField* accountLogout);
	
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
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID);
}
