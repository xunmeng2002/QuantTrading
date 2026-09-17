#pragma once
#include <QuantTrading/BackTestApi.h>

#include <map>
#include <string>

namespace QuantTrading::strategy
{
// 策略层基类：吸收订阅两步走、报单字段填充、ID 分配、订单/持仓视图与回测结束收口等脚手架，
// 策略子类只需实现 OnXxx 钩子与业务逻辑。回测路径注入 BackTestApi；实盘路径（MdApi+TraderApi）
// 由未来的适配器注入同一组钩子，钩子签名保持源码兼容。
//
// 线程契约：所有钩子在引擎线程内触发（与 CTP 回调同线程模型），策略逻辑只在回调线程执行，
// StrategyBase 内部状态因此不加锁；若未来策略从其他线程调用 Req 接口，须先在此层加锁。
// 钩子收到的指针仅在本次回调内有效，如需保留请自行拷贝。
class StrategyBase : protected QuantTrading::BackTestSpi
{
public:
	StrategyBase(QuantTrading::BackTestApi* backTestApi, const char* accountId);
	virtual ~StrategyBase();

	// RegisterSpi → api->Init → ReqRegisterAccount（账户按需自建，先于 OnStart 的行情订阅）→ OnStart
	bool Start();
	// 等待引擎线程退出（回测结束由 OnRtnMarketDataEnd 桥接收口 api->Release）
	void WaitForEnd();

protected:
	virtual void OnStart() {}
	virtual void OnTick(const DepthMarketDataField* depthMarketData) {}
	virtual void OnBar(const BarMarketDataField* barMarketData) {}
	// clientOrderID：本策略下单时分配的编号；成交回报不含该字段，由订单缓存经引擎 OrderId 反查补齐，查不到为 0
	virtual void OnTrade(const TradeField* trade, ClientOrderIdType clientOrderID) {}
	virtual void OnOrder(const OrderField* order) {}
	virtual void OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo) {}
	virtual void OnCancelOrderRsp(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo) {}
	virtual void OnSessionBegin(const SessionBeginField* sessionBegin) {}
	virtual void OnSessionEnd(const SessionEndField* sessionEnd) {}
	// 行情结束（回测收尾），返回后基类调用 api->Release 停止引擎
	virtual void OnEnd() {}

	void SubscribeTick(const char* exchangeId, const char* instrumentId);
	void SubscribeBar(const char* exchangeId, const char* instrumentId);

	// 声明策略期望的 bar 周期（格式同 BackTest.json BarPreces：<n><s|m|h|d>，如 "5m"）。
	// 声明后随每次行情订阅上报给引擎，OnBar 收到聚合到该周期的 bar；未声明 → OnBar 收到数据集精度 bar。
	// 周期非法（格式错误/秒级）抛 std::logic_error；无法由数据集精度聚合时由引擎在装载期拒启。
	// 应在构造或 OnStart 内、订阅之前调用一次。
	void DeclareBarPeriod(const char* barPreces);

	ClientOrderIdType BuyOpen(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume);
	ClientOrderIdType SellOpen(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume);
	ClientOrderIdType BuyClose(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume);
	ClientOrderIdType SellClose(const char* exchangeId, const char* instrumentId, PriceType price, VolumeType volume);

	// 缓存有引擎 OrderId（已收到过该单回报）时按 OrderId 主路径撤单；未收到过回报（如 OppositePrice
	// 模式下未成交挂单）时走引擎的 ClientOrderId 唯一键回退路径
	bool CancelOrder(ClientOrderIdType clientOrderID);

	VolumeType GetLongPosition(const char* instrumentId) const;
	VolumeType GetShortPosition(const char* instrumentId) const;
	PriceType GetLastPrice(const char* instrumentId) const;

private:
	void OnConnected() override;
	void OnDisConnected() override;
	void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;
	void OnRtnSessionBegin(const SessionBeginField* sessionBegin) override;
	void OnRtnSessionEnd(const SessionEndField* sessionEnd) override;
	void OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd) override;
	void OnRspRegisterAccount(const RspRegisterAccountField* rspRegisterAccount, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	void OnRtnOrder(const OrderField* order) override;
	void OnRtnTrade(const TradeField* trade) override;

	void SubscribeMarketData(const char* exchangeId, const char* instrumentId);
	ClientOrderIdType InsertLimitOrder(const char* exchangeId, const char* instrumentId, DirectionType direction, OffsetFlagType offsetFlag, PriceType price, VolumeType volume);

	struct InstrumentState
	{
		VolumeType LongVolume = 0;
		VolumeType ShortVolume = 0;
		PriceType LastPrice = 0;
	};
	struct OrderContext
	{
		std::string ExchangeId;
		std::string InstrumentId;
	};

	std::map<std::string, InstrumentState> instrumentStates_;
	std::map<ClientOrderIdType, OrderContext> orderContexts_;   // 下单时记录，撤单时取 ExchangeId/InstrumentId
	std::map<ClientOrderIdType, OrderField> orders_;            // 回报快照，兼作撤单主路径的 OrderId 来源
	std::map<OrderIdType, ClientOrderIdType> engineOrderIds_;   // 引擎 OrderId → ClientOrderId，供 OnTrade 路由

	QuantTrading::BackTestApi* backTestApi_;
	std::string accountId_;
	// 声明后的目标 bar 周期，随每次行情订阅上报给引擎；BarPeriod<=0 表示未声明，引擎按数据集精度推送
	BarPrecesType declaredBarPreces_ = BarPrecesType::Minute;
	int declaredBarPeriod_ = 0;
	int nextRequestId_ = 0;
	ClientOrderIdType nextClientOrderId_ = 0;
    ClientOrderIdType nextClientCancelOrderId_ = 0;
	bool isMdEnded_ = false;
};
}
