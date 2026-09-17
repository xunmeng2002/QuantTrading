#pragma once
#include "OrderMatch.h"

namespace QuantTrading::ordermatch
{
    class BarOrderMatch : public OrderMatch
    {
    public:
        BarOrderMatch(const DateType& tradingDay, int tradeId = 0);
        virtual ~BarOrderMatch();

        virtual void OnTick(QuantTrading::DepthMarketData* mdTick) override;
        virtual void OnBar(QuantTrading::BarMarketData* mdBar) override;

    protected:
        void CheckMatch(QuantTrading::BarMarketData* mdBar);
        bool CheckMatchForOrder(QuantTrading::BarMarketData* mdBar, QuantTrading::Order* order);
    };
}



