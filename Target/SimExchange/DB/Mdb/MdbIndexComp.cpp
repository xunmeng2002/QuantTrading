#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{
	bool SEInstrumentEqualForExchangeIDIndex::operator()(const SEInstrument* const left, const SEInstrument* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0;
	}
	bool SEInstrumentLessForExchangeIDIndex::operator()(const SEInstrument* const left, const SEInstrument* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		return false;
	}
	
	bool SEOrderEqualForAccountIDIndex::operator()(const SEOrder* const left, const SEOrder* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool SEOrderLessForAccountIDIndex::operator()(const SEOrder* const left, const SEOrder* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountID, right->AccountID) < 0)
			return true;
		else if (strcmp(left->AccountID, right->AccountID) > 0)
			return false;
		return false;
	}
	
	bool SETradeEqualForAccountIDIndex::operator()(const SETrade* const left, const SETrade* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool SETradeLessForAccountIDIndex::operator()(const SETrade* const left, const SETrade* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountID, right->AccountID) < 0)
			return true;
		else if (strcmp(left->AccountID, right->AccountID) > 0)
			return false;
		return false;
	}
	
	bool SEBrokerLoginSessionEqualForBrokerIDIndex::operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const
	{
		return left->BrokerID == right->BrokerID ;
	}
	bool SEBrokerLoginSessionLessForBrokerIDIndex::operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const
	{
		if (left->BrokerID < right->BrokerID)
			return true;
		else if (left->BrokerID > right->BrokerID)
			return false;
		return false;
	}
	
}
