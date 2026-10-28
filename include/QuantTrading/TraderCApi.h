// 本文件由 ../Templates/Cpp/Api/CApi.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "Fields.h"
#include <QuantTrading/TraderApi/TraderApiExport.h>

#ifdef _WIN32
#define TRADERAPI_CALL _stdcall
#else
#define TRADERAPI_CALL
#endif


extern "C"
{
	typedef void (TRADERAPI_CALL *OnConnected)();
	typedef void (TRADERAPI_CALL *OnDisConnected)();
	typedef void (TRADERAPI_CALL *OnRspAccountLogin)(const QuantTrading::RspAccountLoginField* rspAccountLogin, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspAccountLogout)(const QuantTrading::RspAccountLogoutField* rspAccountLogout, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryHolderAccount)(const QuantTrading::HolderAccountField* holderAccount, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCapital)(const QuantTrading::CapitalField* capital, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryPosition)(const QuantTrading::PositionField* position, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOrder)(const QuantTrading::OrderField* order, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryTrade)(const QuantTrading::TradeField* trade, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryInstrument)(const QuantTrading::InstrumentField* instrument, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryOptionInstrument)(const QuantTrading::OptionInstrumentField* optionInstrument, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryCommissionRate)(const QuantTrading::CommissionRateField* commissionRate, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspQryMoneyTransfer)(const QuantTrading::MoneyTransferField* moneyTransfer, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspInsertOrder)(const QuantTrading::ReqInsertOrderField* reqInsertOrder, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRspCancelOrder)(const QuantTrading::ReqCancelOrderField* reqCancelOrder, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (TRADERAPI_CALL *OnRtnOrder)(const QuantTrading::OrderField* order);
	typedef void (TRADERAPI_CALL *OnRtnTrade)(const QuantTrading::TradeField* trade);
	typedef void (TRADERAPI_CALL *OnRtnMoneyTransfer)(const QuantTrading::MoneyTransferField* moneyTransfer);
	typedef void (TRADERAPI_CALL *OnRtnAccountLogout)(const QuantTrading::AccountLogoutField* accountLogout);
	
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
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(const QuantTrading::ReqAccountLoginField* reqAccountLogin, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(const QuantTrading::ReqAccountLogoutField* reqAccountLogout, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(const QuantTrading::ReqQryHolderAccountField* reqQryHolderAccount, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(const QuantTrading::ReqQryCapitalField* reqQryCapital, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(const QuantTrading::ReqQryPositionField* reqQryPosition, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(const QuantTrading::ReqQryOrderField* reqQryOrder, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(const QuantTrading::ReqQryTradeField* reqQryTrade, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(const QuantTrading::ReqQryInstrumentField* reqQryInstrument, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(const QuantTrading::ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(const QuantTrading::ReqQryCommissionRateField* reqQryCommissionRate, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(const QuantTrading::ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(const QuantTrading::ReqInsertOrderField* reqInsertOrder, int requestId);
	TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(const QuantTrading::ReqCancelOrderField* reqCancelOrder, int requestId);
}
