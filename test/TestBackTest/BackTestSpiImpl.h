#pragma once
#include "BackTestSpiMiddle.h"
#include "Config/Config.h"

namespace quanttrading::testbacktest
{
class BackTestSpiImpl : public BackTestSpiMiddle
{
public:
	BackTestSpiImpl(BackTestApi* backTestApi, const Config& config);

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
}
