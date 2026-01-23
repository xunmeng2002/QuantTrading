#pragma once
#include "BackTestSpiMiddle.h"
#include "Config.h"

class BackTestSpiImpl : public BackTestSpiMiddle
{
public:
	BackTestSpiImpl(BackTestApi* backTestApi, const Config& config);

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

	void ReqSubMarketData();

private:
	void ReqInsertOrder(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID, const double& price, DirectionType direction);

private:
	BackTestApi* m_BackTestApi;
	DepthMarketDataField* m_LastOrderTickMd;
	BarMarketDataField* m_LastOrderBarMd;
	AccountIDType m_AccountID;
	ExchangeIDType m_ExchangeID;
	InstrumentIDType m_InstrumentID;
	int m_MaxRequestID;
	int m_MaxClientOrderID;
};