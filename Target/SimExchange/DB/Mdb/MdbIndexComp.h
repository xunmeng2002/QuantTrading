#pragma once
#include "MdbStructs.h"

namespace mdb
{
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
