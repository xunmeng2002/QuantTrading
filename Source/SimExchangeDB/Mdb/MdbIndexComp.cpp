#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{




	bool PrimaryAccountEqualForOfferIDIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		return ;
	}
	bool PrimaryAccountLessForOfferIDIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		return false;
	}



	bool PositionEqualForAccountIndex::operator()(const Position* const left, const Position* const right) const
	{
		return ;
	}
	bool PositionLessForAccountIndex::operator()(const Position* const left, const Position* const right) const
	{
		return false;
	}




}
