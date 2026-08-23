#pragma once
#include "OrderMatch.h"

namespace quanttrading::ordermatch
{
    class OppositePriceOrderMatch : public OrderMatch
    {
    public:
        OppositePriceOrderMatch(const DateType& tradingDay, int maxTradeID = 0);
        virtual ~OppositePriceOrderMatch();

        virtual void OnTick(mdb::DepthMarketData* mdTick) override;
        virtual void OnBar(mdb::BarMarketData* mdBar) override;
        virtual void InsertOrder(mdb::Order* order) override;
    protected:
        void CheckBidMatch(mdb::DepthMarketData* mdTick);
        void CheckAskMatch(mdb::DepthMarketData* mdTick);
        bool CheckMatchForOrder(mdb::Order* order, const double& price);

    };
}

