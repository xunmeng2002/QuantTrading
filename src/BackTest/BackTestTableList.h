// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace QuantTrading;
namespace QuantTrading::BackTest
{
	inline const unsigned int BackTestTableIds[] =
	{
		TradingDay::TableId,
		Exchange::TableId,
		Product::TableId,
		HotInstrument::TableId,
		Instrument::TableId,
		PrimaryAccount::TableId,
		Account::TableId,
		Capital::TableId,
		Position::TableId,
		PositionDetail::TableId,
		Order::TableId,
		Trade::TableId,
		DepthMarketData::TableId,
		BarMarketData::TableId,
		MdSubscribe::TableId,
		CommissionGroup::TableId,
		BaseCommission::TableId,
	};
	inline const TableList BackTestTableList = { "BackTest", BackTestTableIds, static_cast<int>(sizeof(BackTestTableIds) / sizeof(BackTestTableIds[0])) };
}
