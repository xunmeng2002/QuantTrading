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
	
	bool MdUserLoginSessionEqualForMdUserIDIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return strcmp(left->MdUserID, right->MdUserID) == 0;
	}
	bool MdUserLoginSessionLessForMdUserIDIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (strcmp(left->MdUserID, right->MdUserID) < 0)
			return true;
		else if (strcmp(left->MdUserID, right->MdUserID) > 0)
			return false;
		return false;
	}
	
}
