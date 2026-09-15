#include "Settlement.h"
#include "Mdb.h"
#include <cstring>
#include <vector>

namespace quanttrading::settlement
{
	// 结转次序对齐原回测实现：资金层先触发，逐层向下复制（资金→持仓→明细），源行均取 tradingDay 当日数据
	void Settlement::RollToNextDay(const DateType& tradingDay, const DateType& nextTradingDay)
	{
		InitAccount(tradingDay, nextTradingDay);
	}

	void Settlement::InitAccount(const DateType& tradingDay, const DateType& nextTradingDay)
	{
		InitPosition(tradingDay, nextTradingDay);
		std::vector<mdb::Capital*> capitals;
		auto capitalItPair = m_Mdb->capital->tradingDayIndex->EqualRange(tradingDay);
		for (auto& capitalIt = capitalItPair.first; capitalIt != capitalItPair.second; ++capitalIt)
		{
			capitals.push_back(*capitalIt);
		}
		for (auto capital : capitals)
		{
			auto newCapital = mdb::Capital::Allocate();
			memcpy(newCapital, capital, sizeof(mdb::Capital));
			strcpy(newCapital->TradingDay, nextTradingDay);
			newCapital->PreBalance = capital->Balance;
			newCapital->MarketValue = 0.0;
			newCapital->CashIn = 0.0;
			newCapital->CashOut = 0.0;
			newCapital->Commission = 0.0;
			newCapital->FrozenCash = 0.0;
			newCapital->FrozenMargin = 0.0;
			newCapital->FrozenCommission = 0.0;
			newCapital->CloseProfitByDate = 0.0;
			newCapital->PositionProfitByDate = 0.0;

			m_Mdb->capital->Insert(newCapital);
		}
	}

	void Settlement::InitPosition(const DateType& tradingDay, const DateType& nextTradingDay)
	{
		InitPositionDetail(tradingDay, nextTradingDay);
		std::vector<mdb::Position*> positions;
		auto positionItPair = m_Mdb->position->tradingDayIndex->EqualRange(tradingDay);
		for (auto& positionIt = positionItPair.first; positionIt != positionItPair.second; ++positionIt)
		{
			positions.push_back(*positionIt);
		}
		for (auto position : positions)
		{
			if (position->TotalPosition == 0)
				continue;
			auto newPosition = mdb::Position::Allocate();
			memcpy(newPosition, position, sizeof(mdb::Position));
			strcpy(newPosition->TradingDay, nextTradingDay);
			newPosition->PositionFrozen = 0;
			newPosition->TodayPosition = 0;
			newPosition->CashIn = 0;
			newPosition->CashOut = 0;
			newPosition->Commission = 0.0;
			newPosition->FrozenCash = 0;
			newPosition->FrozenMargin = 0;
			newPosition->FrozenCommission = 0;
			newPosition->CloseProfitByDate = 0.0;
			newPosition->CloseProfitByTrade = 0.0;
			newPosition->PositionProfitByDate = 0.0;
			newPosition->PreSettlementPrice = position->SettlementPrice;
			m_Mdb->position->Insert(newPosition);
		}
	}

	void Settlement::InitPositionDetail(const DateType& tradingDay, const DateType& nextTradingDay)
	{
		std::vector<mdb::PositionDetail*> positionDetails;
		auto positionDetailItPair = m_Mdb->positionDetail->tradingDayIndex->EqualRange(tradingDay);
		for (auto& positionDetailIt = positionDetailItPair.first; positionDetailIt != positionDetailItPair.second; ++positionDetailIt)
		{
			positionDetails.push_back(*positionDetailIt);
		}
		for (auto positionDetail : positionDetails)
		{
			if (positionDetail->Volume - positionDetail->CloseVolume == 0)
				continue;
			auto newPositionDetail = mdb::PositionDetail::Allocate();
			memcpy(newPositionDetail, positionDetail, sizeof(mdb::PositionDetail));
			strcpy(newPositionDetail->TradingDay, nextTradingDay);
			newPositionDetail->CashIn = 0;
			newPositionDetail->CashOut = 0;
			newPositionDetail->Commission = 0;
			newPositionDetail->CloseProfitByDate = 0.0;
			newPositionDetail->CloseProfitByTrade = 0.0;
			newPositionDetail->PositionProfitByDate = 0.0;
			newPositionDetail->PreSettlementPrice = positionDetail->SettlementPrice;
			m_Mdb->positionDetail->Insert(newPositionDetail);
		}
	}
}
