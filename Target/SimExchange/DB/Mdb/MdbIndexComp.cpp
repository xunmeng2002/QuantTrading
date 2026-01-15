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
