#include "MdbTickSettlementPriceSource.h"

#include "LockBased/Mdb.h"

#include <cmath>

namespace QuantTrading::Settlement
{
	namespace
	{
		bool IsFinitePrice(const PriceType price)
		{
			return std::isfinite(price);
		}
	}

	MdbTickSettlementPriceSource::MdbTickSettlementPriceSource(QuantTrading::Mdb* mdb)
		:mdb_(mdb)
	{
	}

	PriceType MdbTickSettlementPriceSource::GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail)
	{
		auto mdTick = mdb_->DepthMarketDatas->PrimaryKey->Select(positionDetail->TradingDay, positionDetail->ExchangeId, positionDetail->InstrumentId);
		if (!mdTick.has_value())
		{
			return positionDetail->PreSettlementPrice;
		}
		else if (IsFinitePrice(mdTick->LastPrice))
		{
			return mdTick->LastPrice;
		}
		else if (IsFinitePrice(mdTick->PreSettlementPrice))
		{
			return mdTick->PreSettlementPrice;
		}
		return positionDetail->PreSettlementPrice;
	}
}
