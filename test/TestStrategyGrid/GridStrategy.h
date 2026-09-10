#pragma once
#include "StrategyBase.h"
#include <string>
#include <vector>

namespace quanttrading::teststrategygrid
{
struct GridParams
{
	double GridStep = 0.0;
	int GridCount = 0;
	int VolumePerGrid = 0;
	std::string ExchangeID;
	std::string InstrumentID;
	std::string BarPreces;   // 策略期望 bar 周期（"5m" 格式，同 BackTest.json BarPreces）；空=OnBar 纯透传
};

// 成对网格：每格一开一平，利润 = 步长 × 乘数 × 手数，仓位天然有界（≤ GridCount 手/向）。
// 格位状态机：Empty → OpenPending → OpenFilled → ClosePending → Closed。
// 日级重锚：SessionBegin 复位 Closed 格为 Empty，首笔 tick LastPrice 或首根 bar Close（Bar 回放模式无 tick）
// 为新中枢补挂阶梯，两者先到先锚；
// 引擎日切结算统一撤销全部未成交挂单（撤单回报先于 SessionEnd 推送）：零成交开仓格经撤单
// 回报复位 Empty 等次日重锚重挂；部分成交开仓格与被撤平仓格按已成交/剩余量即时补平仓单，
// 新平仓单经引擎队列在次一交易日撮合。平仓单价格取自开仓成交价 ∓ 步长，与锚点无关。
class GridStrategy : public quanttrading::strategy::StrategyBase
{
public:
	GridStrategy(quanttrading::BackTestApi* backTestApi, const char* accountID, const GridParams& gridParams);

protected:
	void OnStart() override;
	void OnTick(const DepthMarketDataField* depthMarketData) override;
	void OnBar(const BarMarketDataField* barMarketData) override;
	void OnTrade(const TradeField* trade, ClientOrderIDType clientOrderID) override;
	void OnOrder(const OrderField* order) override;
	void OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo) override;
	// 日切后等待首笔有效 tick 重锚
	void OnSessionBegin(const SessionBeginField* sessionBegin) override;
	void OnSessionEnd(const SessionEndField* sessionEnd) override;
	void OnEnd() override;

private:
	enum class GridSlotState
	{
		Empty = 0,
		OpenPending,
		OpenFilled,
		ClosePending,
		Closed,
	};
	struct GridSlot
	{
		GridSlotState State = GridSlotState::Empty;
		DirectionType Direction = DirectionType::Buy;   // 开仓方向：Buy=中枢下方买开格，Sell=中枢上方卖开格
		PriceType OpenPrice = 0.0;
		PriceType OpenFillPrice = 0.0;
		PriceType ClosePrice = 0.0;
		ClientOrderIDType OpenClientOrderID = 0;
		ClientOrderIDType CloseClientOrderID = 0;
		VolumeType OpenFilledVolume = 0;
		VolumeType CloseFilledVolume = 0;
	};

	void PlaceLadder(PriceType anchorPrice);
	void PlaceOpenOrder(GridSlot& gridSlot);
	void PlaceCloseOrder(GridSlot& gridSlot, VolumeType volume);
	void HandleOpenTrade(const TradeField* trade, GridSlot* gridSlot);
	void HandleCloseTrade(const TradeField* trade, GridSlot* gridSlot);
	void UpdateClosePrice(GridSlot& gridSlot);
	void ResetSlotToEmpty(GridSlot& gridSlot);
	void HandleOpenOrderCanceled(GridSlot* gridSlot);
	void HandleCloseOrderCanceled(GridSlot* gridSlot);
	GridSlot* FindSlotByOpenOrder(ClientOrderIDType clientOrderID);
	GridSlot* FindSlotByCloseOrder(ClientOrderIDType clientOrderID);

	GridParams m_Params;
	std::vector<GridSlot> m_Slots;   // [0, GridCount) 买开格；[GridCount, 2×GridCount) 卖开格
	bool m_AwaitingAnchor = true;
	int m_ClosedPairCount = 0;
	double m_RealizedProfit = 0.0;
	double m_TotalCommission = 0.0;
};
}
