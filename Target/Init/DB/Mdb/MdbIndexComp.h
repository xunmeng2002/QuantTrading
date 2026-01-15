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
	
	struct InstrumentEqualForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	struct InstrumentLessForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	
}
