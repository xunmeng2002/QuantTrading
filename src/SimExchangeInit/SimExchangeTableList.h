#pragma once
#include "TableList.h"
#include "MdbStructs.h"


namespace mdb
{
	inline const unsigned int kSimExchangeTableIDs[] =
	{
		TradingDay::TableID,
		Exchange::TableID,
		Product::TableID,
		Instrument::TableID,
		PrimaryAccount::TableID,
		Account::TableID,
		Capital::TableID,
		Position::TableID,
		PositionDetail::TableID,
		Order::TableID,
		Trade::TableID,
		AccountLoginSession::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
	};
	inline const TableList SimExchangeTableList = { "SimExchange", kSimExchangeTableIDs, (int)(sizeof(kSimExchangeTableIDs) / sizeof(kSimExchangeTableIDs[0])) };
}
