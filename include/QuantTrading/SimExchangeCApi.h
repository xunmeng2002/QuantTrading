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
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogin)(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogout)(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryOrder)(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryTrade)(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryInstrument)(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspInsertOrder)(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspCancelOrder)(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnOrder)(OrderField* order);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnTrade)(TradeField* trade);
	
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
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);
}
