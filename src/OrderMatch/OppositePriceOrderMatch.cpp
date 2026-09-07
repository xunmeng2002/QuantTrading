#include "OppositePriceOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace mdb;
using namespace spark::core;


namespace quanttrading::ordermatch
{
    OppositePriceOrderMatch::OppositePriceOrderMatch(const DateType& tradingDay, int maxTradeID)
        :OrderMatch(tradingDay, maxTradeID)
    {

    }
    OppositePriceOrderMatch::~OppositePriceOrderMatch()
    {

    }

    void OppositePriceOrderMatch::OnTick(mdb::DepthMarketData* mdTick)
    {
        UpdateDateTime(mdTick->UpdateTs);
        if (mdTick->AskVolume1 > 0 && mdTick->AskPrice1 != std::numeric_limits<double>::infinity())
        {
            CheckBuyMatch(mdTick);
        }
        if (mdTick->BidVolume1 > 0 && mdTick->BidPrice1 != std::numeric_limits<double>::infinity())
        {
            CheckSellMatch(mdTick);
        }
    }
    void OppositePriceOrderMatch::OnBar(mdb::BarMarketData* mdBar)
    {

    }

    void OppositePriceOrderMatch::CheckBuyMatch(mdb::DepthMarketData* mdTick)
    {
        auto& marketBuyQueueOrders = m_MarketBuyOrders[mdTick->InstrumentID];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            GetNextTradeID(m_TradeID);
            Match(marketBuyQueueOrder, mdTick->AskPrice1, marketBuyQueueOrder->VolumeTotal, m_TradeID);
        }
        m_MarketBuyOrders.erase(mdTick->InstrumentID);

        auto& buyQueueOrders = m_BuyOrders[mdTick->InstrumentID];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(buyQueueOrder, mdTick->AskPrice1))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(buyQueueOrders);
        std::erase_if(buyQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });
    }
    void OppositePriceOrderMatch::CheckSellMatch(mdb::DepthMarketData* mdTick)
    {
        auto& marketSellQueueOrders = m_MarketSellOrders[mdTick->InstrumentID];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            GetNextTradeID(m_TradeID);
            Match(marketSellQueueOrder, mdTick->BidPrice1, marketSellQueueOrder->VolumeTotal, m_TradeID);
        }
        m_MarketSellOrders.erase(mdTick->InstrumentID);

        auto& sellQueueOrders = m_SellOrders[mdTick->InstrumentID];
        for (auto& sellQueueOrder : sellQueueOrders)
        {
            if (!CheckMatchForOrder(sellQueueOrder, mdTick->BidPrice1))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(sellQueueOrders);
        std::erase_if(sellQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });
    }
    bool OppositePriceOrderMatch::CheckMatchForOrder(mdb::Order* order, const double& price)
    {
        if (order->Direction == DirectionType::Buy && DoubleUtility::DoubleLess(order->Price, price))
            return false;
        else if (order->Direction == DirectionType::Sell && DoubleUtility::DoubleGreat(order->Price, price))
            return false;

        GetNextTradeID(m_TradeID);
        Match(order, price, order->VolumeTotal, m_TradeID);
        return true;
    }
}

