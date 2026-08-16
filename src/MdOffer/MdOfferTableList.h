#pragma once
#include "TableList.h"
#include "MdbStructs.h"


namespace mdb
{
	inline const unsigned int kMdOfferTableIDs[] =
	{
		Exchange::TableID,
		Instrument::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
		MdSubscribe::TableID,
		MdUser::TableID,
		MdUserLoginSession::TableID,
	};
	inline const TableList MdOfferTableList = { "MdOffer", kMdOfferTableIDs, (int)(sizeof(kMdOfferTableIDs) / sizeof(kMdOfferTableIDs[0])) };
}
