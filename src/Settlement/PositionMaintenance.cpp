#include "PositionMaintenance.h"
#include "Mdb.h"
#include "CommissionCalculator.h"
#include "OrderUtility.h"
#include "QuantUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <algorithm>
#include <cstring>

using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;
using namespace QuantTrading;
using namespace QuantTrading::OrderMatch;

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
		:mdb_(mdb)
	{
	}

	void PositionMaintenance::UpdateOnTrade(QuantTrading::Trade* trade)
	{
		auto posiDirection = QuantTrading::GetPosiDirection(trade->OffsetFlag, trade->Direction);
		auto position = mdb_->Position->PrimaryKey->Select(trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, posiDirection);
		if (position == nullptr)
		{
			position = QuantTrading::OrderMatch::CreatePosition(trade, posiDirection);
			mdb_->Position->Insert(position);
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
			auto positionDetail = QuantTrading::OrderMatch::CreatePositionDetail(trade, posiDirection);
			mdb_->PositionDetail->Insert(positionDetail);
		}
		else
		{
			std::set<QuantTrading::PositionDetail*, PositionDetailLessForOpenDate> positionDetails;
			auto itPair = mdb_->PositionDetail->TradeMatchIndex->EqualRange(position->TradingDay, position->AccountId, position->ExchangeId,
				position->InstrumentId, position->PosiDirection);
			for (auto& it = itPair.first; it != itPair.second; ++it)
			{
				positionDetails.insert(*it);
			}
			auto flag = position->PosiDirection == PosiDirectionType::Long ? 1 : -1;
			auto remainVolume = trade->Volume;
			// 平仓腿在这里才把成交的三项费用落到明细上（开仓腿由 CreatePositionDetail 抄写）。
			// 末笔直接取余额而非按比例算，保证 sum(各明细分摊) ≡ trade 的三项在 IEEE double 下逐位闭合
			const TradeFee tradeFee{ trade->Commission, trade->StampTax, trade->TransferFee };
			auto remainFee = tradeFee;
			QuantTrading::PositionDetail* lastMatchedDetail = nullptr;
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
				// currVolume == remainVolume 即本条明细吃下全部剩余成交量，它就是末笔。
				// 该分支隐含 remainVolume > 0，故 trade->Volume 必为正，下面的除法不会除零
				const auto detailFee = currVolume == remainVolume
					? remainFee
					: ScaleTradeFee(tradeFee, static_cast<double>(currVolume) / static_cast<double>(trade->Volume));
				positionDetail->Commission += detailFee.Commission;
				positionDetail->StampTax += detailFee.StampTax;
				positionDetail->TransferFee += detailFee.TransferFee;
				remainFee = SubtractTradeFee(remainFee, detailFee);
				lastMatchedDetail = positionDetail;
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
			// 持仓不足：余额没有对应成交量可分摊，退回最后一条已配对明细，不让费用凭空消失
			// （成交量不足本身已由上方 "Position not Enough For Close Trade" 告警）
			if (lastMatchedDetail != nullptr && remainVolume > 0)
			{
				lastMatchedDetail->Commission += remainFee.Commission;
				lastMatchedDetail->StampTax += remainFee.StampTax;
				lastMatchedDetail->TransferFee += remainFee.TransferFee;
			}
		}
	}
}
