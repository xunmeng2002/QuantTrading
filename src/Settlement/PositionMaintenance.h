#pragma once
#include "MdbStructs.h"
#include <set>

namespace mdb
{
	class Mdb;
}

namespace quanttrading::settlement
{
	// 平仓配对顺序：先开仓日期早者优先，同日按开仓成交 TradeID 先开先平
	struct PositionDetailLessForOpenDate
	{
		bool operator()(const mdb::PositionDetail* const left, const mdb::PositionDetail* const right) const;
	};

	// 成交驱动持仓维护：开仓建持仓/明细并累计，平仓按先开先平配对扣减并逐笔记平仓盈亏（回测与模拟盘共用）
	class PositionMaintenance
	{
	public:
		explicit PositionMaintenance(mdb::Mdb* mdb);

		void UpdateOnTrade(mdb::Trade* trade);

	private:
		mdb::Mdb* m_Mdb;
	};
}
