#pragma once
#include "TestHelpers.h"
#include "GridStrategy.h"

namespace quanttrading::unittest
{
    using quanttrading::teststrategygrid::GridParams;

    inline quanttrading::teststrategygrid::GridParams MakeGridParams(double grid_step, int grid_count)
    {
        GridParams grid_params;
        grid_params.GridStep = grid_step;
        grid_params.GridCount = grid_count;
        grid_params.VolumePerGrid = 1;
        grid_params.ExchangeID = "CFFEX";
        grid_params.InstrumentID = "IF2503";
        return grid_params;
    }

    // 暴露 GridStrategy 继承自 StrategyBase 的受保护查询接口给测试断言
    class GridStrategyProbe : public quanttrading::teststrategygrid::GridStrategy
    {
    public:
        using GridStrategy::GridStrategy;
        using quanttrading::strategy::StrategyBase::GetLongPosition;
        using quanttrading::strategy::StrategyBase::GetShortPosition;
    };

    // 造引擎日终撤单回报（值类型，OrderStatus/成交量按撤单场景填充）
    inline OrderField MakeCanceledOrderField(const char* instrument_id, int order_id, int client_order_id,
        OrderStatusType order_status, long long volume_traded)
    {
        OrderField order = MakeOrderField(instrument_id, order_id, client_order_id);
        order.OrderStatus = order_status;
        order.VolumeTraded = volume_traded;
        order.VolumeTotal = 0;
        return order;
    }
}
