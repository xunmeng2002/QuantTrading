#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{
	bool HotInstrumentEqualForTradingDayIndex::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0&& strcmp(left->ProductID, right->ProductID) == 0&& left->Rank == right->Rank && strcmp(left->TradingDay, right->TradingDay) == 0;
	}
	bool HotInstrumentLessForTradingDayIndex::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->ProductID, right->ProductID) < 0)
			return true;
		else if (strcmp(left->ProductID, right->ProductID) > 0)
			return false;
		if (left->Rank < right->Rank)
			return true;
		else if (left->Rank > right->Rank)
			return false;
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		return false;
	}
	
}
