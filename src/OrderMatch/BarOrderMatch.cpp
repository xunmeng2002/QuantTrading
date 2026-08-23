#include "BarOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>
#include <string>

using namespace std;
using namespace mdb;
using namespace spark::core;

namespace quanttrading::ordermatch
{
    BarOrderMatch::BarOrderMatch(const DateType& tradingDay, int maxTradeID)
        :OrderMatch(tradingDay, maxTradeID)
    {

    }
    BarOrderMatch::~BarOrderMatch()
    {

    }

    void BarOrderMatch::OnTick(mdb::DepthMarketData* mdTick)
    {

    }
    void BarOrderMatch::OnBar(mdb::BarMarketData* mdBar)
    {
        UpdateDateTime(mdBar->UpdateTs);
        CheckMatch(mdBar);
    }
    void BarOrderMatch::InsertOrder(mdb::Order* order)
    {
        AddOrderToQueue(order);
    }
    void BarOrderMatch::CheckMatch(mdb::BarMarketData* mdBar)
    {
        auto& marketBuyQueueOrders = m_MarketBuyOrders[mdBar->InstrumentID];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            CheckMatchForOrder(mdBar, marketBuyQueueOrder);
        }
        m_MarketBuyOrders.erase(mdBar->InstrumentID);
        auto& marketSellQueueOrders = m_MarketSellOrders[mdBar->InstrumentID];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            CheckMatchForOrder(mdBar, marketSellQueueOrder);
        }
        m_MarketSellOrders.erase(mdBar->InstrumentID);

        auto& buyQueueOrders = m_BuyOrders[mdBar->InstrumentID];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(mdBar, buyQueueOrder))
            {
                break;
            }
        }
        std::erase_if(buyQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });

        auto& sellQueueOrders = m_SellOrders[mdBar->InstrumentID];
        for (auto& sellQueueOrder : sellQueueOrders)
        {
            if (!CheckMatchForOrder(mdBar, sellQueueOrder))
            {
                break;
            }
        }
        std::erase_if(sellQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });
    }
    bool BarOrderMatch::CheckMatchForOrder(mdb::BarMarketData* mdBar, mdb::Order* order)
    {
        PriceType matchPrice;
        if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
        {
            if (order->Direction == DirectionType::Buy)
            {
                if (DoubleUtility::DoubleLess(order->Price, mdBar->Low))
                    return false;
                matchPrice = DoubleUtility::DoubleGreat(order->Price, mdBar->High) ? mdBar->High : order->Price;
            }
            else
            {
                if (DoubleUtility::DoubleGreat(order->Price, mdBar->High))
                    return false;
                matchPrice = DoubleUtility::DoubleLess(order->Price, mdBar->Low) ? mdBar->Low : order->Price;
            }
        }
        else
        {
            matchPrice = (mdBar->High + mdBar->Low) / 2;
        }
        GetNextTradeID(m_TradeID);
        Match(order, matchPrice, order->VolumeTotal, m_TradeID);
        return true;
    }
}

