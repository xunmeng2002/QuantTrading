// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
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
	inline const TableList backtestTableList = { "backtest", kbacktestTableIDs, static_cast<int>(sizeof(kbacktestTableIDs) / sizeof(kbacktestTableIDs[0])) };
}
