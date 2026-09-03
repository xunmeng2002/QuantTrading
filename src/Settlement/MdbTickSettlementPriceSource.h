#pragma once
#include "SettlementPriceSource.h"

namespace mdb
{
	class Mdb;
}

namespace quanttrading::settlement
{
	// 行情表结算价来源：取合约当日最新笔 LastPrice，异常值（+inf/nan）逐级回退至行情表 PreSettlementPrice、持仓明细 PreSettlementPrice
	class MdbTickSettlementPriceSource : public SettlementPriceSource
	{
	public:
		explicit MdbTickSettlementPriceSource(mdb::Mdb* mdb);

		PriceType GetSettlementPrice(const mdb::PositionDetail* positionDetail) override;

	private:
		mdb::Mdb* m_Mdb;
	};
}
