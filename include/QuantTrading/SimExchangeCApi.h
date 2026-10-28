// 本文件由 ../Templates/Cpp/Api/CApi.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "Fields.h"
#include <QuantTrading/SimExchangeApi/SimExchangeApiExport.h>

#ifdef _WIN32
#define SIMEXCHANGEAPI_CALL _stdcall
#else
#define SIMEXCHANGEAPI_CALL
#endif


extern "C"
{
	typedef void (SIMEXCHANGEAPI_CALL *OnConnected)();
	typedef void (SIMEXCHANGEAPI_CALL *OnDisConnected)();
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogin)(const QuantTrading::RspAccountLoginField* rspAccountLogin, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspAccountLogout)(const QuantTrading::RspAccountLogoutField* rspAccountLogout, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryOrder)(const QuantTrading::OrderField* order, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryTrade)(const QuantTrading::TradeField* trade, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspQryInstrument)(const QuantTrading::InstrumentField* instrument, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspInsertOrder)(const QuantTrading::ReqInsertOrderField* reqInsertOrder, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRspCancelOrder)(const QuantTrading::ReqCancelOrderField* reqCancelOrder, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnOrder)(const QuantTrading::OrderField* order);
	typedef void (SIMEXCHANGEAPI_CALL *OnRtnTrade)(const QuantTrading::TradeField* trade);
	
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
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogin(const QuantTrading::ReqAccountLoginField* reqAccountLogin, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogout(const QuantTrading::ReqAccountLogoutField* reqAccountLogout, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryOrder(const QuantTrading::ReqQryOrderField* reqQryOrder, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryTrade(const QuantTrading::ReqQryTradeField* reqQryTrade, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryInstrument(const QuantTrading::ReqQryInstrumentField* reqQryInstrument, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqInsertOrder(const QuantTrading::ReqInsertOrderField* reqInsertOrder, int requestId);
	SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqCancelOrder(const QuantTrading::ReqCancelOrderField* reqCancelOrder, int requestId);
}
