#pragma once
#include "TableList.h"
#include "MdbStructs.h"


namespace mdb
{
	inline const unsigned int kBackTestTableIDs[] =
	{
		TradingDay::TableID,
		Exchange::TableID,
		Product::TableID,
		HotInstrument::TableID,
		Instrument::TableID,
		PrimaryAccount::TableID,
		Account::TableID,
		Capital::TableID,
		Position::TableID,
		PositionDetail::TableID,
		Order::TableID,
		Trade::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
		MdSubscribe::TableID,
	};
	inline const TableList BackTestTableList = { "BackTest", kBackTestTableIDs, (int)(sizeof(kBackTestTableIDs) / sizeof(kBackTestTableIDs[0])) };
}
