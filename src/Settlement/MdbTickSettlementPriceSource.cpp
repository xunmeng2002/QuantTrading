#include "MdbTickSettlementPriceSource.h"
#include "Mdb.h"
#include <cmath>

namespace QuantTrading::Settlement
{
	MdbTickSettlementPriceSource::MdbTickSettlementPriceSource(QuantTrading::Mdb* mdb)
		:m_Mdb(mdb)
	{
	}

	PriceType MdbTickSettlementPriceSource::GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail)
	{
		auto mdTick = m_Mdb->DepthMarketData->PrimaryKey->Select(positionDetail->TradingDay, positionDetail->ExchangeId, positionDetail->InstrumentId);
		if (mdTick == nullptr)
		{
			return positionDetail->PreSettlementPrice;
		}
		else if (!isinf(mdTick->LastPrice) && !isnan(mdTick->LastPrice))
		{
			return mdTick->LastPrice;
		}
		else if (!isinf(mdTick->PreSettlementPrice) && !isnan(mdTick->PreSettlementPrice))
		{
			return mdTick->PreSettlementPrice;
		}
		return positionDetail->PreSettlementPrice;
	}
}
