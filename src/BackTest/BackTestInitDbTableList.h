#pragma once
#include "TableList.h"
#include "MdbStructs.h"

// 手写、非生成文件：回测 InitDb 的装载清单。BackTestTableList.h 是 pump 产物会被覆盖，故清单另立一份。
// 只含「基本数据」三张表，刻意不含 Account/Capital/Position/Order/Trade——那些由引擎按需自建
// （HandleRegisterAccount）与日终结算滚动，灌进来会与之正面冲突：Account 行被抢注后不再建 Capital，
// 而灌进来的 Capital 行 TradingDay 是种子库里的历史交易日，SettlementAccount 按当日索引查不到、
// RollToNextDay 也不接它，种子资金会被静默忽略。也不含 Instrument——它会被行情侧整行 Update 覆盖。
namespace QuantTrading::BackTest
{
	inline const unsigned int BackTestInitDbTableIds[] =
	{
		Product::TableId,
		CommissionGroup::TableId,
		BaseCommission::TableId,
	};
	inline const TableList BackTestInitDbTableList =
		{ "BackTestInitDb", BackTestInitDbTableIds, static_cast<int>(sizeof(BackTestInitDbTableIds) / sizeof(BackTestInitDbTableIds[0])) };
}
