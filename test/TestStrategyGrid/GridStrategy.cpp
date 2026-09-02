#include "GridStrategy.h"
#include <Spark/Core/Logger/Logger.h>
#include <limits>

using namespace spark::core;

namespace quanttrading::teststrategygrid
{
GridStrategy::GridStrategy(quanttrading::BackTestApi* backTestApi, const char* accountID, const GridParams& gridParams)
	:StrategyBase(backTestApi, accountID), m_Params(gridParams)
{
	m_Slots.resize(gridParams.GridCount * 2);
	for (int level = 0; level < gridParams.GridCount; ++level)
	{
		m_Slots[level].Direction = DirectionType::Buy;
		m_Slots[gridParams.GridCount + level].Direction = DirectionType::Sell;
	}
}

void GridStrategy::OnStart()
{
	SubscribeTick(m_Params.ExchangeID.c_str(), m_Params.InstrumentID.c_str());
}

void GridStrategy::OnTick(const DepthMarketDataField* depthMarketData)
{
	if (!m_AwaitingAnchor)
	{
		return;
	}
	constexpr PriceType InvalidPrice = std::numeric_limits<PriceType>::max();
	PriceType anchorPrice = depthMarketData->LastPrice;
	if (anchorPrice <= 0 || anchorPrice == InvalidPrice)
	{
		return;
	}
	m_AwaitingAnchor = false;
	WriteLog(LogLevel::Info, "Anchor price: %f", anchorPrice);
	PlaceLadder(anchorPrice);
}

void GridStrategy::PlaceLadder(PriceType anchorPrice)
{
	for (int level = 0; level < m_Params.GridCount; ++level)
	{
		GridSlot& buySlot = m_Slots[level];
		if (buySlot.State == GridSlotState::Empty)
		{
			buySlot.OpenPrice = anchorPrice - m_Params.GridStep * (level + 1);
			PlaceOpenOrder(buySlot);
		}
		GridSlot& sellSlot = m_Slots[m_Params.GridCount + level];
		if (sellSlot.State == GridSlotState::Empty)
		{
			sellSlot.OpenPrice = anchorPrice + m_Params.GridStep * (level + 1);
			PlaceOpenOrder(sellSlot);
		}
	}
}

void GridStrategy::PlaceOpenOrder(GridSlot& gridSlot)
{
	gridSlot.OpenFilledVolume = 0;
	if (gridSlot.Direction == DirectionType::Buy)
	{
		gridSlot.OpenClientOrderID = BuyOpen(m_Params.ExchangeID.c_str(), m_Params.InstrumentID.c_str(), gridSlot.OpenPrice, m_Params.VolumePerGrid);
	}
	else
	{
		gridSlot.OpenClientOrderID = SellOpen(m_Params.ExchangeID.c_str(), m_Params.InstrumentID.c_str(), gridSlot.OpenPrice, m_Params.VolumePerGrid);
	}
	gridSlot.State = GridSlotState::OpenPending;
	WriteLog(LogLevel::Info, "Place open order, ClientOrderID:%d Direction:%d Price:%f", gridSlot.OpenClientOrderID, (int)gridSlot.Direction, gridSlot.OpenPrice);
}

void GridStrategy::PlaceCloseOrder(GridSlot& gridSlot, VolumeType volume)
{
	if (gridSlot.Direction == DirectionType::Buy)
	{
		gridSlot.CloseClientOrderID = SellClose(m_Params.ExchangeID.c_str(), m_Params.InstrumentID.c_str(), gridSlot.ClosePrice, volume);
	}
	else
	{
		gridSlot.CloseClientOrderID = BuyClose(m_Params.ExchangeID.c_str(), m_Params.InstrumentID.c_str(), gridSlot.ClosePrice, volume);
	}
	gridSlot.State = GridSlotState::ClosePending;
	WriteLog(LogLevel::Info, "Place close order, ClientOrderID:%d Price:%f Volume:%lld", gridSlot.CloseClientOrderID, gridSlot.ClosePrice, volume);
}

void GridStrategy::OnTrade(const TradeField* trade, ClientOrderIDType clientOrderID)
{
	if (clientOrderID == 0)
	{
		return;
	}
	if (GridSlot* gridSlot = FindSlotByOpenOrder(clientOrderID))
	{
		HandleOpenTrade(trade, gridSlot);
	}
	else if (GridSlot* gridSlot = FindSlotByCloseOrder(clientOrderID))
	{
		HandleCloseTrade(trade, gridSlot);
	}
}

void GridStrategy::OnOrder(const OrderField* order)
{
	if (order->OrderStatus != OrderStatusType::Canceled && order->OrderStatus != OrderStatusType::PartTradedCanceled)
	{
		return;
	}
	if (GridSlot* gridSlot = FindSlotByOpenOrder(order->ClientOrderID))
	{
		HandleOpenOrderCanceled(gridSlot);
	}
	else if (GridSlot* gridSlot = FindSlotByCloseOrder(order->ClientOrderID))
	{
		HandleCloseOrderCanceled(gridSlot);
	}
}

void GridStrategy::HandleOpenTrade(const TradeField* trade, GridSlot* gridSlot)
{
	if (gridSlot->State != GridSlotState::OpenPending)
	{
		return;
	}
	gridSlot->OpenFillPrice = trade->Price;
	gridSlot->OpenFilledVolume += trade->Volume;
	if (gridSlot->OpenFilledVolume < m_Params.VolumePerGrid)
	{
		return;
	}
	UpdateClosePrice(*gridSlot);
	PlaceCloseOrder(*gridSlot, gridSlot->OpenFilledVolume);
}

void GridStrategy::HandleCloseTrade(const TradeField* trade, GridSlot* gridSlot)
{
	if (gridSlot->State != GridSlotState::ClosePending)
	{
		return;
	}
	gridSlot->CloseFilledVolume += trade->Volume;
	if (gridSlot->CloseFilledVolume < gridSlot->OpenFilledVolume)
	{
		return;
	}
	double profitPerUnit = 0.0;
	if (gridSlot->Direction == DirectionType::Buy)
	{
		profitPerUnit = trade->Price - gridSlot->OpenFillPrice;
	}
	else
	{
		profitPerUnit = gridSlot->OpenFillPrice - trade->Price;
	}
	double pairProfit = profitPerUnit * trade->Volume * trade->VolumeMultiple - trade->Commission;
	m_RealizedProfit += pairProfit;
	m_TotalCommission += trade->Commission;
	++m_ClosedPairCount;
	gridSlot->State = GridSlotState::Closed;
	WriteLog(LogLevel::Info, "Pair closed, open:%f close:%f profit:%f", gridSlot->OpenFillPrice, trade->Price, pairProfit);
}

void GridStrategy::UpdateClosePrice(GridSlot& gridSlot)
{
	if (gridSlot.Direction == DirectionType::Buy)
	{
		gridSlot.ClosePrice = gridSlot.OpenFillPrice + m_Params.GridStep;
	}
	else
	{
		gridSlot.ClosePrice = gridSlot.OpenFillPrice - m_Params.GridStep;
	}
}

void GridStrategy::ResetSlotToEmpty(GridSlot& gridSlot)
{
	// 清净周期态字段：格位跨周期复用，残留的 CloseFilledVolume 会使新周期的平仓剩余量
	// 计算为 0，撤单后不再补平仓单，格位带持仓困死在 ClosePending
	gridSlot.State = GridSlotState::Empty;
	gridSlot.OpenClientOrderID = 0;
	gridSlot.CloseClientOrderID = 0;
	gridSlot.OpenFilledVolume = 0;
	gridSlot.CloseFilledVolume = 0;
}

void GridStrategy::HandleOpenOrderCanceled(GridSlot* gridSlot)
{
	if (gridSlot->State != GridSlotState::OpenPending)
	{
		return;
	}
	if (gridSlot->OpenFilledVolume == 0)
	{
		ResetSlotToEmpty(*gridSlot);
		WriteLog(LogLevel::Info, "Open order canceled without fill, slot reset to Empty, Price:%f", gridSlot->OpenPrice);
		return;
	}
	// 部分成交后被日终撤销：按已成交量即时补平仓单，新单经引擎队列在次一交易日撮合
	UpdateClosePrice(*gridSlot);
	PlaceCloseOrder(*gridSlot, gridSlot->OpenFilledVolume);
	WriteLog(LogLevel::Warning, "Partially filled open order canceled by day-end settlement, close volume:%lld", gridSlot->OpenFilledVolume);
}

void GridStrategy::HandleCloseOrderCanceled(GridSlot* gridSlot)
{
	if (gridSlot->State != GridSlotState::ClosePending)
	{
		return;
	}
	VolumeType remainingVolume = gridSlot->OpenFilledVolume - gridSlot->CloseFilledVolume;
	if (remainingVolume <= 0)
	{
		WriteLog(LogLevel::Warning, "Close order canceled with zero remaining volume, ClosePrice:%f", gridSlot->ClosePrice);
		return;
	}
	// 平仓单被日终撤销：按剩余未平量以原价位重下平仓单，CloseFilledVolume 累计保留
	PlaceCloseOrder(*gridSlot, remainingVolume);
	WriteLog(LogLevel::Warning, "Close order canceled by day-end settlement, re-place close volume:%lld", remainingVolume);
}

void GridStrategy::OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo)
{
	if (reqInsertOrder == nullptr || rspInfo == nullptr || rspInfo->ErrorID == 0)
	{
		return;
	}
	ClientOrderIDType clientOrderID = reqInsertOrder->ClientOrderID;
	if (GridSlot* gridSlot = FindSlotByOpenOrder(clientOrderID))
	{
		if (gridSlot->State == GridSlotState::OpenPending)
		{
			ResetSlotToEmpty(*gridSlot);
			WriteLog(LogLevel::Warning, "Open order rejected, slot reset to Empty, Price:%f", gridSlot->OpenPrice);
		}
	}
	else if (GridSlot* gridSlot = FindSlotByCloseOrder(clientOrderID))
	{
		// 平仓单被拒：保持 OpenFilled（持仓留存），由 OnEnd 总结提示剩余持仓
		WriteLog(LogLevel::Error, "Close order rejected, position remains, ClosePrice:%f", gridSlot->ClosePrice);
	}
}

void GridStrategy::OnSessionBegin(const SessionBeginField* sessionBegin)
{
	// 引擎已在结算时统一撤单（撤单回报先于 SessionEnd）：OpenPending 格位已经撤单回报复位 Empty
	// 或转换为 ClosePending，此处仅需复位 Closed 格等待重锚
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.State == GridSlotState::Closed)
		{
			ResetSlotToEmpty(gridSlot);
		}
	}
	m_AwaitingAnchor = true;
}

void GridStrategy::OnSessionEnd(const SessionEndField* sessionEnd)
{
	// 引擎日切结算已撤销全部未成交挂单（撤单回报先于本回调）：OpenPending 格位已在 OnOrder 中
	// 复位/转换，此处统计的是转换后仍带平仓单、次一交易日继续工作的格位
	int closePendingCount = 0;
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.State == GridSlotState::ClosePending)
		{
			++closePendingCount;
		}
	}
	WriteLog(LogLevel::Info, "Session end: %d slots closing next day after day-end cancel sweeps", closePendingCount);
}

void GridStrategy::OnEnd()
{
	WriteLog(LogLevel::Info, "Grid strategy end: closedPairs:%d realizedProfit:%f totalCommission:%f longPosition:%lld shortPosition:%lld",
		m_ClosedPairCount, m_RealizedProfit, m_TotalCommission,
		GetLongPosition(m_Params.InstrumentID.c_str()), GetShortPosition(m_Params.InstrumentID.c_str()));
}

GridStrategy::GridSlot* GridStrategy::FindSlotByOpenOrder(ClientOrderIDType clientOrderID)
{
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.OpenClientOrderID == clientOrderID)
		{
			return &gridSlot;
		}
	}
	return nullptr;
}
GridStrategy::GridSlot* GridStrategy::FindSlotByCloseOrder(ClientOrderIDType clientOrderID)
{
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.CloseClientOrderID == clientOrderID)
		{
			return &gridSlot;
		}
	}
	return nullptr;
}
}
