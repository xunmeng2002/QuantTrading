#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct SEBrokerLoginSessionEqualForBrokerIDIndex
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	struct SEBrokerLoginSessionLessForBrokerIDIndex
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	
}
