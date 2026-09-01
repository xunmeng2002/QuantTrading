#pragma once
#include <QuantTrading/BackTestApi.h>
#include <map>
#include <string>

namespace quanttrading::strategy
{
// 策略层基类：吸收订阅两步走、报单字段填充、ID 分配、订单/持仓视图与回测结束收口等脚手架，
// 策略子类只需实现 OnXxx 钩子与业务逻辑。回测路径注入 BackTestApi；实盘路径（MdApi+TraderApi）
// 由未来的适配器注入同一组钩子，钩子签名保持源码兼容。
//
// 线程契约：所有钩子在引擎线程内触发（与 CTP 回调同线程模型），策略逻辑只在回调线程执行，
// StrategyBase 内部状态因此不加锁；若未来策略从其他线程调用 Req 接口，须先在此层加锁。
// 钩子收到的指针仅在本次回调内有效，如需保留请自行拷贝。
class StrategyBase : protected quanttrading::BackTestSpi
{
public:
	StrategyBase(quanttrading::BackTestApi* backTestApi, const char* accountID);
	virtual ~StrategyBase();

	// RegisterSpi → api->Init → OnStart（策略在 OnStart 内订阅行情）
	bool Start();
	// 等待引擎线程退出（回测结束由 OnRtnMarketDataEnd 桥接收口 api->Release）
	void WaitForEnd();

protected:
	virtual void OnStart() {}
	virtual void OnTick(const DepthMarketDataField* depthMarketData) {}
	virtual void OnBar(const BarMarketDataField* barMarketData) {}
	// clientOrderID：本策略下单时分配的编号；成交回报不含该字段，由订单缓存经引擎 OrderID 反查补齐，查不到为 0
	virtual void OnTrade(const TradeField* trade, ClientOrderIDType clientOrderID) {}
	virtual void OnOrder(const OrderField* order) {}
	virtual void OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo) {}
	virtual void OnCancelOrderRsp(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo) {}
	virtual void OnSessionBegin(const SessionBeginField* sessionBegin) {}
	virtual void OnSessionEnd(const SessionEndField* sessionEnd) {}
	// 行情结束（回测收尾），返回后基类调用 api->Release 停止引擎
	virtual void OnEnd() {}

	void SubscribeTick(const char* exchangeID, const char* instrumentID);
	void SubscribeBar(const char* exchangeID, const char* instrumentID);

	ClientOrderIDType BuyOpen(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume);
	ClientOrderIDType SellOpen(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume);
	ClientOrderIDType BuyClose(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume);
	ClientOrderIDType SellClose(const char* exchangeID, const char* instrumentID, PriceType price, VolumeType volume);

	// 缓存有引擎 OrderID（已收到过该单回报）时按 OrderID 主路径撤单；未收到过回报（如 OppositePrice
	// 模式下未成交挂单）时走引擎的 ClientOrderID 唯一键回退路径
	bool CancelOrder(ClientOrderIDType clientOrderID);

	VolumeType GetLongPosition(const char* instrumentID) const;
	VolumeType GetShortPosition(const char* instrumentID) const;
	PriceType GetLastPrice(const char* instrumentID) const;

private:
	void OnConnected() override;
	void OnDisConnected() override;
	void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override;
	void OnRtnBarMarketData(const BarMarketDataField* barMarketData) override;
	void OnRtnSessionBegin(const SessionBeginField* sessionBegin) override;
	void OnRtnSessionEnd(const SessionEndField* sessionEnd) override;
	void OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd) override;
	void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	void OnRtnOrder(const OrderField* order) override;
	void OnRtnTrade(const TradeField* trade) override;

	void SubscribeMarketData(const char* exchangeID, const char* instrumentID);
	ClientOrderIDType InsertLimitOrder(const char* exchangeID, const char* instrumentID, DirectionType direction, OffsetFlagType offsetFlag, PriceType price, VolumeType volume);

	struct InstrumentState
	{
		VolumeType LongVolume = 0;
		VolumeType ShortVolume = 0;
		PriceType LastPrice = 0;
	};
	struct OrderContext
	{
		std::string ExchangeID;
		std::string InstrumentID;
	};

	std::map<std::string, InstrumentState> m_InstrumentStates;
	std::map<ClientOrderIDType, OrderContext> m_OrderContexts;   // 下单时记录，撤单时取 ExchangeID/InstrumentID
	std::map<ClientOrderIDType, OrderField> m_Orders;            // 回报快照，兼作撤单主路径的 OrderID 来源
	std::map<OrderIDType, ClientOrderIDType> m_EngineOrderIDs;   // 引擎 OrderID → ClientOrderID，供 OnTrade 路由

	quanttrading::BackTestApi* m_BackTestApi;
	std::string m_AccountID;
	int m_NextRequestID = 0;
	ClientOrderIDType m_NextClientOrderID = 0;
	bool m_IsMdEnded = false;
};
}
