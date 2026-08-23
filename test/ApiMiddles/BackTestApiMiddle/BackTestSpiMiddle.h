#pragma once
#include <QuantTrading/BackTestApi.h>


namespace quanttrading
{
class BackTestSpiMiddle : public BackTestSpi
{
public:
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;
	virtual void OnRtnSessionBegin(const SessionBeginField* sessionBegin) override;
	virtual void OnRtnSessionEnd(const SessionEndField* sessionEnd) override;
	virtual void OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(const OrderField* order) override;
	virtual void OnRtnTrade(const TradeField* trade) override;
};
}
