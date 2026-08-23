#pragma once
#include "Fields.h"
#include <QuantTrading/SimExchangeApi/SimExchangeApiExport.h>

#ifdef WIN32
#define SIMEXCHANGEAPI_CALL _stdcall
#else
#define SIMEXCHANGEAPI_CALL
#endif


extern "C"
{
	typedef void (SIMEXCHANGEAPI_CALL *OnConnected)();
	typedef void (SIMEXCHANGEAPI_CALL *OnDisConnected)();
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogin)(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogout)(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryOrder)(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryTrade)(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryInstrument)(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspInsertOrder)(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspCancelOrder)(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnOrder)(const OrderField* order);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnTrade)(const TradeField* trade);
	
	struct SimExchangeCSpi
	{
	public:
		OnConnected OnConnected;
		OnDisConnected OnDisConnected;
		OnRspAccountLogin OnRspAccountLogin;
		OnRspAccountLogout OnRspAccountLogout;
		OnRspQryOrder OnRspQryOrder;
		OnRspQryTrade OnRspQryTrade;
		OnRspQryInstrument OnRspQryInstrument;
		OnRspInsertOrder OnRspInsertOrder;
		OnRspCancelOrder OnRspCancelOrder;
		OnRtnOrder OnRtnOrder;
		OnRtnTrade OnRtnTrade;
	};

	SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL CreateSimExchangeCApi();
	SIMEXCHANGEAPI_EXPORTS const char* SIMEXCHANGEAPI_CALL GetApiVersion();
	SIMEXCHANGEAPI_EXPORTS bool SIMEXCHANGEAPI_CALL Init();
	SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Join();
	SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Release();
	SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterFront(const char* address);
	SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterSpi(SimExchangeCSpi* spi);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID);
}
