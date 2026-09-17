#pragma once
#include "OrderMatch.h"

namespace QuantTrading::ordermatch
{
    class LastPriceOrderMatch : public OrderMatch
    {
    public:
        LastPriceOrderMatch(const DateType& tradingDay, int tradeId = 0);
        virtual ~LastPriceOrderMatch();

        virtual void OnTick(QuantTrading::DepthMarketData* mdTick) override;
        virtual void OnBar(QuantTrading::BarMarketData* mdBar) override;
    protected:
        void CheckMatch(QuantTrading::DepthMarketData* mdTick);
        bool CheckMatchForOrder(QuantTrading::DepthMarketData* mdTick, QuantTrading::Order* order);
    };
}

