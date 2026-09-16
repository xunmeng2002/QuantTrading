#pragma once
#include "SettlementPriceSource.h"

namespace QuantTrading
{
	class Mdb;
}

namespace QuantTrading::Settlement
{
	// 行情表结算价来源：取合约当日最新笔 LastPrice，异常值（+inf/nan）逐级回退至行情表 PreSettlementPrice、持仓明细 PreSettlementPrice
	class MdbTickSettlementPriceSource : public SettlementPriceSource
	{
	public:
		explicit MdbTickSettlementPriceSource(QuantTrading::Mdb* mdb);

		PriceType GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail) override;

	private:
		QuantTrading::Mdb* mdb_;
	};
}
