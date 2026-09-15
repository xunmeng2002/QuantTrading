// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
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
		PrimaryAccountLoginSession::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
	};
	inline const TableList simexchangeTableList = { "simexchange", ksimexchangeTableIDs, static_cast<int>(sizeof(ksimexchangeTableIDs) / sizeof(ksimexchangeTableIDs[0])) };
}
