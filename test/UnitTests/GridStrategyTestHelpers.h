#pragma once
#include "TestHelpers.h"
#include "GridStrategy.h"

namespace QuantTrading::UnitTest
{
    using QuantTrading::TestStrategyGrid::GridParams;

    // 单测统一用的网格步长**比例**：0.0025 = 0.25%，在 4000 的锚价上恰好等于 10 个价格单位，
    // 故档位价仍是 3990/4010 这类整数，只有平仓价带比例尾数（3990 × 1.0025 = 3999.975）
    inline constexpr double TestGridStepRatio = 0.0025;

    inline QuantTrading::TestStrategyGrid::GridParams MakeGridParams(double grid_step, int grid_count)
    {
        GridParams grid_params;
        grid_params.GridStep = grid_step;
        grid_params.GridCount = grid_count;
        grid_params.VolumePerGrid = 1;
        grid_params.ExchangeId = "CFFEX";
        grid_params.InstrumentId = "IF2503";
        return grid_params;
    }

    // 暴露 GridStrategy 继承自 StrategyBase 的受保护查询接口给测试断言
    class GridStrategyProbe : public QuantTrading::TestStrategyGrid::GridStrategy
    {
    public:
        using GridStrategy::GridStrategy;
        using QuantTrading::strategy::StrategyBase::GetLongPosition;
        using QuantTrading::strategy::StrategyBase::GetShortPosition;
    };

    // 造引擎日终撤单回报（值类型，OrderStatus/成交量按撤单场景填充）
    inline OrderField MakeCanceledOrderField(const char* instrumentId, int OrderId, int clientOrderId,
        OrderStatusType OrderStatus, long long VolumeTraded)
    {
        OrderField order = MakeOrderField(instrumentId, OrderId, clientOrderId);
        order.OrderStatus = OrderStatus;
        order.VolumeTraded = VolumeTraded;
        order.VolumeTotal = 0;
        return order;
    }
}
