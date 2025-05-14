#pragma once
#include "BackTestFields.h"

#ifdef WIN32
#ifdef LIB_BACKTEST_API_EXPORT
#define BACKTEST_API_EXPORT				__declspec(dllexport)
#else
#define BACKTEST_API_EXPORT				__declspec(dllimport)
#endif
#else
#define BACKTEST_API_EXPORT
#endif


class BackTestSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) {}
	virtual void OnRtnSessionBegin(SessionBeginField* sessionBegin) {}
	virtual void OnRtnSessionEnd(SessionEndField* sessionEnd) {}
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(OrderField* order) {}
	virtual void OnRtnTrade(TradeField* trade) {}
};

class BACKTEST_API_EXPORT BackTestApi
{
public:
	static BackTestApi* CreateBackTestApi();
	static const char* GetApiVersion();
	virtual void Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(BackTestSpi* pSpi) = 0;
	
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) = 0;
	virtual int ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID) = 0;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};

