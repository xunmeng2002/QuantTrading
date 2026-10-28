#include "Settlement.h"
#include "LockBased/Mdb.h"
#include "SettlementPriceSource.h"
#include <cstring>
#include <vector>

namespace QuantTrading::Settlement
{
	Settlement::Settlement(QuantTrading::Mdb* mdb, SettlementPriceSource* settlementPriceSource)
		:mdb_(mdb), settlementPriceSource_(settlementPriceSource)
	{
	}

	void Settlement::Settle(const DateType& tradingDay)
	{
		SettlementPositionDetail(tradingDay);
		SettlementPosition(tradingDay);
		SettlementAccount(tradingDay);
	}

	void Settlement::SettlementAccount(const DateType& tradingDay)
	{
		std::vector<QuantTrading::Capital*> capitals;
		auto capitalRange = mdb_->Capitals->TradingDayIndex->EqualRange(tradingDay);
		for (auto capital : capitalRange)
		{
			capitals.push_back(capital);
		}
		for (auto capital : capitals)
		{
			capital->MarketValue = 0;
			capital->CashIn = 0;
			capital->CashOut = 0;
			capital->Margin = 0;
			capital->Commission = 0;
			capital->StampTax = 0;
			capital->TransferFee = 0;
			capital->CloseProfitByDate = 0;
			capital->CloseProfitByTrade = 0;
			capital->PositionProfitByDate = 0;
			capital->PositionProfitByTrade = 0;
			auto positionsInAccount = mdb_->Positions->AccountIndex->EqualRange(capital->TradingDay, capital->AccountId);
			for (auto position : positionsInAccount)
			{
				capital->MarketValue += position->MarketValue;
				capital->CashIn += position->CashIn;
				capital->CashOut += position->CashOut;
				capital->Margin += position->Margin;
				capital->Commission += position->Commission;
				capital->StampTax += position->StampTax;
				capital->TransferFee += position->TransferFee;
				capital->CloseProfitByDate += position->CloseProfitByDate;
				capital->CloseProfitByTrade += position->CloseProfitByTrade;
				capital->PositionProfitByDate += position->PositionProfitByDate;
				capital->PositionProfitByTrade += position->PositionProfitByTrade;
			}
			CalcCapital(capital);
		}
	}

	void Settlement::SettlementPosition(const DateType& tradingDay)
	{
		std::vector<QuantTrading::Position*> positions;
		auto positionRange = mdb_->Positions->TradingDayIndex->EqualRange(tradingDay);
		for (auto position : positionRange)
		{
			positions.push_back(position);
		}
		for (auto position : positions)
		{
			position->PositionFrozen = 0;
			position->MarketValue = 0;
			position->CashIn = 0;
			position->CashOut = 0;
			position->Margin = 0;
			position->Commission = 0;
			position->StampTax = 0;
			position->TransferFee = 0;
			position->CloseProfitByDate = 0;
			position->CloseProfitByTrade = 0;
			position->PositionProfitByDate = 0;
			position->PositionProfitByTrade = 0;

			auto positionDetailsOfPosition = mdb_->PositionDetails->TradeMatchIndex->EqualRange(tradingDay, position->AccountId, position->ExchangeId, position->InstrumentId, position->PosiDirection);
			for (auto positionDetail : positionDetailsOfPosition)
			{
				position->MarketValue += positionDetail->MarketValue;
				position->CashIn += positionDetail->CashIn;
				position->CashOut += positionDetail->CashOut;
				position->Margin += positionDetail->Margin;
				position->Commission += positionDetail->Commission;
				position->StampTax += positionDetail->StampTax;
				position->TransferFee += positionDetail->TransferFee;
				position->CloseProfitByDate += positionDetail->CloseProfitByDate;
				position->CloseProfitByTrade += positionDetail->CloseProfitByTrade;
				position->PositionProfitByDate += positionDetail->PositionProfitByDate;
				position->PositionProfitByTrade += positionDetail->PositionProfitByTrade;
				position->SettlementPrice = positionDetail->SettlementPrice;
			}
		}
	}

	void Settlement::SettlementPositionDetail(const DateType& tradingDay)
	{
		std::vector<QuantTrading::PositionDetail*> positionDetails;
		auto positionDetailRange = mdb_->PositionDetails->TradingDayIndex->EqualRange(tradingDay);
		for (auto positionDetail : positionDetailRange)
		{
			positionDetails.push_back(positionDetail);
		}
		for (auto positionDetail : positionDetails)
		{
			auto flag = positionDetail->PosiDirection == PosiDirectionType::Long ? 1 : -1;
			positionDetail->SettlementPrice = settlementPriceSource_->GetSettlementPrice(positionDetail);
			if (strcmp(positionDetail->OpenDate, tradingDay) == 0)
			{
				positionDetail->PositionProfitByDate = flag * (positionDetail->SettlementPrice - positionDetail->OpenPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
			}
			else
			{
				positionDetail->PositionProfitByDate = flag * (positionDetail->SettlementPrice - positionDetail->PreSettlementPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
			}
			positionDetail->PositionProfitByTrade = flag * (positionDetail->SettlementPrice - positionDetail->OpenPrice) * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
			if (positionDetail->ProductClass == ProductClassType::FutureOption || positionDetail->ProductClass == ProductClassType::StockOption)
			{
				positionDetail->MarketValue = flag * positionDetail->SettlementPrice * (positionDetail->Volume - positionDetail->CloseVolume) * positionDetail->VolumeMultiple;
			}
		}
	}

	void Settlement::CalcCapital(QuantTrading::Capital* capital)
	{
		// 三项费用各自成立、各自扣减：Commission 只装佣金，印花税与过户费不并入它
		capital->Balance = capital->PreBalance + capital->CloseProfitByDate + capital->PositionProfitByDate
			- capital->Commission - capital->StampTax - capital->TransferFee;
		capital->Available = capital->Balance - capital->MarketValue - capital->Margin - capital->FrozenCash - capital->FrozenMargin - capital->FrozenCommission;
	}
}
