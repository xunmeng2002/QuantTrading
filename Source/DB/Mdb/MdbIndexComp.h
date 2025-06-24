#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct HotInstrumentEqualForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	struct HotInstrumentLessForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	
	struct PrimaryAccountEqualForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	struct PrimaryAccountLessForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	
	struct CapitalEqualForTradingDayIndex
	{
		bool operator()(const Capital* const left, const Capital* const right) const;
	};
	struct CapitalLessForTradingDayIndex
	{
		bool operator()(const Capital* const left, const Capital* const right) const;
	};
	
	struct PositionEqualForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	struct PositionLessForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	
	struct PositionEqualForTradingDayIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	struct PositionLessForTradingDayIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	
	struct PositionDetailEqualForTradeMatchIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	struct PositionDetailLessForTradeMatchIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	
	struct PositionDetailEqualForTradingDayIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	struct PositionDetailLessForTradingDayIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	
	struct SEInstrumentEqualForExchangeIDIndex
	{
		bool operator()(const SEInstrument* const left, const SEInstrument* const right) const;
	};
	struct SEInstrumentLessForExchangeIDIndex
	{
		bool operator()(const SEInstrument* const left, const SEInstrument* const right) const;
	};
	
	struct SEOrderEqualForAccountIDIndex
	{
		bool operator()(const SEOrder* const left, const SEOrder* const right) const;
	};
	struct SEOrderLessForAccountIDIndex
	{
		bool operator()(const SEOrder* const left, const SEOrder* const right) const;
	};
	
	struct SETradeEqualForAccountIDIndex
	{
		bool operator()(const SETrade* const left, const SETrade* const right) const;
	};
	struct SETradeLessForAccountIDIndex
	{
		bool operator()(const SETrade* const left, const SETrade* const right) const;
	};
	
	struct SEBrokerLoginSessionEqualForBrokerIDIndex
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	struct SEBrokerLoginSessionLessForBrokerIDIndex
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	
}
