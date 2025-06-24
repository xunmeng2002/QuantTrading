#pragma once
#include "SimExchangeFields.h"

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
	virtual void OnRspSEBrokerLogin(RspSEBrokerLoginField* rspSEBrokerLogin, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQrySEOrder(SEOrderField* sEOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQrySETrade(SETradeField* sETrade, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQrySEInstrument(SEInstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnSEOrder(SEOrderField* sEOrder) {}
	virtual void OnRtnSETrade(SETradeField* sETrade) {}
};

class SIMEXCHANGE_API_EXPORT SimExchangeApi
{
public:
	static SimExchangeApi* CreateSimExchangeApi();
	static const char* GetApiVersion();
	virtual void Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(SimExchangeSpi* pSpi) = 0;
	
	virtual int ReqSEBrokerLogin(ReqSEBrokerLoginField* reqSEBrokerLogin, int requestID) = 0;
	virtual int ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID) = 0;
	virtual int ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID) = 0;
	virtual int ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID) = 0;
	virtual int ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID) = 0;
	virtual int ReqQrySEInstrument(ReqQrySEInstrumentField* reqQrySEInstrument, int requestID) = 0;
};

