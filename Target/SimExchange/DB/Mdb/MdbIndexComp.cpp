#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{
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
