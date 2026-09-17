#pragma once
#include "OrderMatch.h"


namespace QuantTrading::OrderMatch
{
    class OrderBookOrderMatch : public OrderMatch
    {
    public:
        OrderBookOrderMatch(const DateType& tradingDay, int tradeId = 0);
        virtual ~OrderBookOrderMatch();

        virtual void OnTick(QuantTrading::DepthMarketData* mdTick) override;
        virtual void OnBar(QuantTrading::BarMarketData* mdBar) override;
        virtual void InsertOrder(QuantTrading::Order* order) override;

    protected:
        void CheckMatch(QuantTrading::Order* order);
        bool  CheckMatchForTwoOrder(QuantTrading::Order* order, QuantTrading::Order* queueOrder);
    };
}
