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
	
}
