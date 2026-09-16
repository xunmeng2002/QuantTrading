#include "PositionMaintenance.h"
#include "Mdb.h"
#include "OrderUtility.h"
#include "QuantUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <algorithm>
#include <cstring>

using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;
using namespace QuantTrading;
using namespace QuantTrading::ordermatch;

namespace QuantTrading::Settlement
{
	bool PositionDetailLessForOpenDate::operator()(const QuantTrading::PositionDetail* const left, const QuantTrading::PositionDetail* const right) const
	{
		auto openDateResult = strcmp(left->OpenDate, right->OpenDate);
		if (openDateResult != 0)
		{
			return openDateResult < 0;
		}
		return strcmp(left->TradeId, right->TradeId) < 0;
	}

	PositionMaintenance::PositionMaintenance(QuantTrading::Mdb* mdb)
		:m_Mdb(mdb)
	{
	}

	void PositionMaintenance::UpdateOnTrade(QuantTrading::Trade* trade)
	{
		auto posiDirection = QuantTrading::GetPosiDirection(trade->OffsetFlag, trade->Direction);
		auto position = m_Mdb->Position->PrimaryKey->Select(trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, posiDirection);
		if (position == nullptr)
		{
			position = QuantTrading::ordermatch::CreatePosition(trade, posiDirection);
			m_Mdb->Position->Insert(position);
		}
		else
		{
			if (trade->OffsetFlag == OffsetFlagType::Open)
			{
				position->TotalPosition += trade->Volume;
			}
			else
			{
				if (position->TotalPosition < trade->Volume)
				{
					WriteLog(LogLevel::Warning, "Position not Enough For Close Trade. Position:%s, Trade:%s", position->GetDebugString(), trade->GetDebugString());
				}
				position->TotalPosition -= trade->Volume;
			}
		}

		if (trade->OffsetFlag == OffsetFlagType::Open)
		{
			auto positionDetail = QuantTrading::ordermatch::CreatePositionDetail(trade, posiDirection);
			m_Mdb->PositionDetail->Insert(positionDetail);
		}
		else
		{
			std::set<QuantTrading::PositionDetail*, PositionDetailLessForOpenDate> positionDetails;
			auto itPair = m_Mdb->PositionDetail->TradeMatchIndex->EqualRange(position->TradingDay, position->AccountId, position->ExchangeId,
				position->InstrumentId, position->PosiDirection);
			for (auto& it = itPair.first; it != itPair.second; ++it)
			{
				positionDetails.insert(*it);
			}
			auto flag = position->PosiDirection == PosiDirectionType::Long ? 1 : -1;
			auto remainVolume = trade->Volume;
			for (auto positionDetail : positionDetails)
			{
				auto currVolume = std::min(remainVolume, positionDetail->Volume - positionDetail->CloseVolume);
				if (currVolume <= 0)
				{
					continue;
				}
				auto closeAmount = trade->Price * currVolume * position->VolumeMultiple;
				positionDetail->CloseVolume += currVolume;
				positionDetail->CloseAmount += closeAmount;
				positionDetail->CloseProfitByTrade += flag * (trade->Price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
				if (strcmp(positionDetail->OpenDate, positionDetail->TradingDay) == 0)
				{
					positionDetail->CloseProfitByDate += flag * (trade->Price - positionDetail->OpenPrice) * currVolume * positionDetail->VolumeMultiple;
				}
				else
				{
					positionDetail->CloseProfitByDate += flag * (trade->Price - positionDetail->PreSettlementPrice) * currVolume * positionDetail->VolumeMultiple;
				}
				if (position->ProductClass == ProductClassType::FutureOption || position->ProductClass == ProductClassType::StockOption
					|| position->ProductClass == ProductClassType::Stock || position->ProductClass == ProductClassType::ETF)
				{
					positionDetail->CashIn += trade->Direction == DirectionType::Sell ? closeAmount : 0.0;
					positionDetail->CashOut += trade->Direction == DirectionType::Buy ? closeAmount : 0.0;
				}
				remainVolume -= currVolume;
				if (remainVolume <= 0)
					break;
			}
		}
	}
}
