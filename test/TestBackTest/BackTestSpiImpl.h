#pragma once
#include "BackTestSpiMiddle.h"
#include <string>

namespace QuantTrading::TestBackTest
{
struct BackTestSpiParams
{
	double OrderTriggerRatio = 0.0;   // 反向触发阈（比例，0.1 = 10%）：与上一笔下单时的价格比，涨/跌幅越过它才反向开一手
	int OrderVolume = 0;              // 每笔委托的手数
	std::string AccountId;
	std::string ExchangeId;
	std::string InstrumentId;
};

// 裸 SPI 宿主：不接策略，行情到即按「与上一笔下单价的价格变动」逆向开单，
// 用于验证引擎的撮合/结算链路。参数由 BackTestSpiParams 注入（不经 Config 生成代码）。
class BackTestSpiImpl : public BackTestSpiMiddle
{
public:
	BackTestSpiImpl(BackTestApi* backTestApi, const BackTestSpiParams& params);

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
	bool TryDecideReversalDirection(PriceType lastOrderPrice, PriceType currentPrice, DirectionType& direction) const;
	// Tick 与 Bar 回放的骨架相同，仅结构体类型、取价字段、基准成员不同，故以模板收口；
	// 定义放在 .cpp（本 TU 是唯一使用方），readPrice 由调用方给出各自的取价字段
	template <typename MdField, typename PriceReader>
	void ApplyPriceTrigger(const MdField* currentFrame, MdField*& lastOrderFrame, PriceReader readPrice);

	BackTestSpiParams params_;
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
