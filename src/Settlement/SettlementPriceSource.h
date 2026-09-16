#pragma once
#include "MdbStructs.h"

namespace QuantTrading::Settlement
{
	// 结算价来源：结算模块不感知行情出处（回测 Tick 查行情表 / Bar 用引擎末根 bar / 模拟盘行情表或官方结算价覆盖），由宿主提供
	class SettlementPriceSource
	{
	public:
		virtual ~SettlementPriceSource() = default;

		virtual PriceType GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail) = 0;
	};
}
