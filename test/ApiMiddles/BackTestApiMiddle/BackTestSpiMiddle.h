#pragma once
#include <QuantTrading/BackTestApi.h>


namespace quanttrading
{
class BackTestSpiMiddle : public BackTestSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) override;
	virtual void OnRtnSessionBegin(SessionBeginField* sessionBegin) override;
	virtual void OnRtnSessionEnd(SessionEndField* sessionEnd) override;
	virtual void OnRtnMarketDataEnd(MarketDataEndField* marketDataEnd) override;
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(OrderField* order) override;
	virtual void OnRtnTrade(TradeField* trade) override;
};
}
