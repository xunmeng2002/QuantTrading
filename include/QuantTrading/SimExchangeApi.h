#pragma once
#include "Fields.h"
#include <QuantTrading/SimExchangeApi/SimExchangeApiExport.h>

namespace quanttrading
{
class SimExchangeSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(const OrderField* order) {}
	virtual void OnRtnTrade(const TradeField* trade) {}
};

class SIMEXCHANGEAPI_EXPORTS SimExchangeApi
{
public:
	static SimExchangeApi* CreateSimExchangeApi();
	static const char* GetApiVersion();
	virtual bool Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(SimExchangeSpi* pSpi) = 0;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) = 0;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) = 0;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) = 0;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) = 0;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) = 0;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};
}
