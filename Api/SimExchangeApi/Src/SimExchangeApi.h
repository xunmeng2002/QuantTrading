#pragma once
#include "SimExchangeFields.h"
#include "LoggerInterface.h"

#ifdef WIN32
#ifdef LIB_SIMEXCHANGE_API_EXPORT
#define SIMEXCHANGE_API_EXPORT				__declspec(dllexport)
#else
#define SIMEXCHANGE_API_EXPORT				__declspec(dllimport)
#endif
#else
#define SIMEXCHANGE_API_EXPORT
#endif


class SimExchangeSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(OrderField* order) {}
	virtual void OnRtnTrade(TradeField* trade) {}
};

class SIMEXCHANGE_API_EXPORT SimExchangeApi
{
public:
	static SimExchangeApi* CreateSimExchangeApi();
	static const char* GetApiVersion();
	static void SetExternLogger(WriteLogFunc externLogger);
	virtual void Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(SimExchangeSpi* pSpi) = 0;
	
	virtual int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID) = 0;
	virtual int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID) = 0;
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) = 0;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) = 0;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) = 0;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};

