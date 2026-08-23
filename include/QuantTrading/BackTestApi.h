#pragma once
#include "Fields.h"
#include <QuantTrading/BackTest/BackTestExport.h>

namespace quanttrading
{
class BackTestSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) {}
	virtual void OnRtnSessionBegin(const SessionBeginField* sessionBegin) {}
	virtual void OnRtnSessionEnd(const SessionEndField* sessionEnd) {}
	virtual void OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd) {}
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnOrder(const OrderField* order) {}
	virtual void OnRtnTrade(const TradeField* trade) {}
};

class BACKTEST_EXPORTS BackTestApi
{
public:
	static BackTestApi* CreateBackTestApi();
	static const char* GetApiVersion();
	virtual bool Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(BackTestSpi* pSpi) = 0;
	
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) = 0;
	virtual int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID) = 0;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) = 0;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) = 0;
};
}
