#pragma once
#include "BackTestSpiMiddle.h"
#include "Config/Config.h"

namespace QuantTrading::TestBackTest
{
class BackTestSpiImpl : public BackTestSpiMiddle
{
public:
	BackTestSpiImpl(BackTestApi* backTestApi, const Config& config);

	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;
	virtual void OnRtnSessionBegin(const SessionBeginField* sessionBegin) override;
	virtual void OnRtnSessionEnd(const SessionEndField* sessionEnd) override;
	virtual void OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRtnOrder(const OrderField* order) override;
	virtual void OnRtnTrade(const TradeField* trade) override;

	void ReqRegisterAccount();
	void ReqSubMarketData();

private:
	void ReqInsertOrder(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId, const double& price, DirectionType direction);

	BackTestApi* backTestApi_;
	DepthMarketDataField* lastOrderTickMd_;
	BarMarketDataField* lastOrderBarMd_;
	AccountIdType accountId_;
	ExchangeIdType exchangeId_;
	InstrumentIdType instrumentId_;
	int maxRequestId_;
	int maxClientOrderId_;
};
}
