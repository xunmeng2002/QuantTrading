#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct PrimaryAccountEqualForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	struct PrimaryAccountLessForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	
	struct AccountLoginSessionEqualForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
}
