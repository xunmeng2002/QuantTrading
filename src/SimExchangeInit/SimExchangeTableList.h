// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace QuantTrading;
namespace QuantTrading::SimExchange
{
	inline const unsigned int SimExchangeTableIds[] =
	{
		TradingDay::TableId,
		Exchange::TableId,
		Product::TableId,
		Instrument::TableId,
		PrimaryAccount::TableId,
		Account::TableId,
		Capital::TableId,
		Position::TableId,
		PositionDetail::TableId,
		Order::TableId,
		Trade::TableId,
		PrimaryAccountLoginSession::TableId,
		DepthMarketData::TableId,
		BarMarketData::TableId,
	};
	inline const TableList SimExchangeTableList = { "SimExchange", SimExchangeTableIds, static_cast<int>(sizeof(SimExchangeTableIds) / sizeof(SimExchangeTableIds[0])) };
}
