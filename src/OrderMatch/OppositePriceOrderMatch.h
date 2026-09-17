#pragma once
#include "OrderMatch.h"

namespace QuantTrading::OrderMatch
{
    class OppositePriceOrderMatch : public OrderMatch
    {
    public:
        OppositePriceOrderMatch(const DateType& tradingDay, int tradeId = 0);
        virtual ~OppositePriceOrderMatch();

        virtual void OnTick(QuantTrading::DepthMarketData* mdTick) override;
        virtual void OnBar(QuantTrading::BarMarketData* mdBar) override;
    protected:
        void CheckBuyMatch(QuantTrading::DepthMarketData* mdTick);
        void CheckSellMatch(QuantTrading::DepthMarketData* mdTick);
        bool CheckMatchForOrder(QuantTrading::Order* order, const double& price);

    };
}

