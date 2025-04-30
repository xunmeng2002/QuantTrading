#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{




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



	bool PositionEqualForAccountIndex::operator()(const Position* const left, const Position* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool PositionLessForAccountIndex::operator()(const Position* const left, const Position* const right) const
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




}
