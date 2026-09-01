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
	if (gridSlot->Direction == DirectionType::Buy)
	{
		gridSlot->ClosePrice = gridSlot->OpenFillPrice + m_Params.GridStep;
	}
	else
	{
		gridSlot->ClosePrice = gridSlot->OpenFillPrice - m_Params.GridStep;
	}
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
			gridSlot->State = GridSlotState::Empty;
			gridSlot->OpenClientOrderID = 0;
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
	// Closed 格复位重挂；OpenPending/ClosePending 挂单跨日仍有效，保留原价位继续工作
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.State == GridSlotState::Closed)
		{
			gridSlot.State = GridSlotState::Empty;
		}
	}
	m_AwaitingAnchor = true;
}

void GridStrategy::OnSessionEnd(const SessionEndField* sessionEnd)
{
	// 引擎挂单跨日不清且会继续成交（撤单跨日必失败，见类注释），日终不做任何撤单
	int workingCount = 0;
	for (auto& gridSlot : m_Slots)
	{
		if (gridSlot.State == GridSlotState::OpenPending || gridSlot.State == GridSlotState::ClosePending)
		{
			++workingCount;
		}
	}
	WriteLog(LogLevel::Info, "Session end: %d grid orders keep working next day", workingCount);
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
