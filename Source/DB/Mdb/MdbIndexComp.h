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



	struct PositionEqualForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	struct PositionLessForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};




}
