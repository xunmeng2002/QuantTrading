#pragma once
#include "MdbStructs.h"

namespace mdb
{
	class Mdb;
}

namespace quanttrading::settlement
{
	class SettlementPriceSource;

	// 日结与跨日结转：Settle 按"明细→持仓→资金"三级聚合当日盈亏/保证金/结算价；RollToNextDay 把未平明细、持仓、资金复制到下一交易日并滚动结算价
	class Settlement
	{
	public:
		Settlement(mdb::Mdb* mdb, SettlementPriceSource* settlementPriceSource);

		void Settle(const DateType& tradingDay);
		void RollToNextDay(const DateType& tradingDay, const DateType& nextTradingDay);

	private:
		void SettlementAccount(const DateType& tradingDay);
		void SettlementPosition(const DateType& tradingDay);
		void SettlementPositionDetail(const DateType& tradingDay);
		void InitAccount(const DateType& tradingDay, const DateType& nextTradingDay);
		void InitPosition(const DateType& tradingDay, const DateType& nextTradingDay);
		void InitPositionDetail(const DateType& tradingDay, const DateType& nextTradingDay);
		void CalcCapital(mdb::Capital* capital);

		mdb::Mdb* m_Mdb;
		SettlementPriceSource* m_SettlementPriceSource;
	};
}
