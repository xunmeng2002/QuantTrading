#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace mdb;
namespace quanttrading::mdoffer
{
	inline const unsigned int kmdofferTableIDs[] =
	{
		Exchange::TableID,
		Instrument::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
		MdSubscribe::TableID,
		MdUser::TableID,
		MdUserLoginSession::TableID,
	};
	inline const TableList mdofferTableList = { "mdoffer", kmdofferTableIDs, (int)(sizeof(kmdofferTableIDs) / sizeof(kmdofferTableIDs[0])) };
}
