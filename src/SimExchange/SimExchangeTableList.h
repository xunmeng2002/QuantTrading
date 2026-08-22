#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace mdb;
namespace quanttrading::simexchange
{
	inline const unsigned int ksimexchangeTableIDs[] =
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
	inline const TableList simexchangeTableList = { "simexchange", ksimexchangeTableIDs, (int)(sizeof(ksimexchangeTableIDs) / sizeof(ksimexchangeTableIDs[0])) };
}
