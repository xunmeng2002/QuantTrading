#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace mdb;
namespace quanttrading::backtest
{
	inline const unsigned int kbacktestTableIDs[] =
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
	inline const TableList backtestTableList = { "backtest", kbacktestTableIDs, (int)(sizeof(kbacktestTableIDs) / sizeof(kbacktestTableIDs[0])) };
}
