#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{
	bool InstrumentEqualForExchangeIDIndex::operator()(const Instrument* const left, const Instrument* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0;
	}
	bool InstrumentLessForExchangeIDIndex::operator()(const Instrument* const left, const Instrument* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		return false;
	}
	
	bool PrimaryAccountEqualForOfferIDIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		return left->OfferID == right->OfferID ;
	}
	bool PrimaryAccountLessForOfferIDIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		if (left->OfferID < right->OfferID)
			return true;
		else if (left->OfferID > right->OfferID)
			return false;
		return false;
	}
	
	bool OrderEqualForAccountIDIndex::operator()(const Order* const left, const Order* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool OrderLessForAccountIDIndex::operator()(const Order* const left, const Order* const right) const
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
	
	bool TradeEqualForAccountIDIndex::operator()(const Trade* const left, const Trade* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool TradeLessForAccountIDIndex::operator()(const Trade* const left, const Trade* const right) const
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
	
	bool AccountLoginSessionEqualForAccountIDIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		return strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool AccountLoginSessionLessForAccountIDIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		if (strcmp(left->AccountID, right->AccountID) < 0)
			return true;
		else if (strcmp(left->AccountID, right->AccountID) > 0)
			return false;
		return false;
	}
	
}
