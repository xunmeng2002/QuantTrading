#include "MdbTickSettlementPriceSource.h"
#include "Mdb.h"
#include <cmath>

namespace quanttrading::settlement
{
	MdbTickSettlementPriceSource::MdbTickSettlementPriceSource(mdb::Mdb* mdb)
		:m_Mdb(mdb)
	{
	}

	PriceType MdbTickSettlementPriceSource::GetSettlementPrice(const mdb::PositionDetail* positionDetail)
	{
		auto mdTick = m_Mdb->t_DepthMarketData->m_PrimaryKey->Select(positionDetail->TradingDay, positionDetail->ExchangeID, positionDetail->InstrumentID);
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
