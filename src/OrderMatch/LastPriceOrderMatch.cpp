#include "LastPriceOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;

namespace QuantTrading::ordermatch
{
    LastPriceOrderMatch::LastPriceOrderMatch(const DateType& tradingDay, int maxTradeID)
        :OrderMatch(tradingDay, maxTradeID)
    {

    }
    LastPriceOrderMatch::~LastPriceOrderMatch()
    {

    }

    void LastPriceOrderMatch::OnTick(QuantTrading::DepthMarketData* mdTick)
    {
        UpdateDateTime(mdTick->UpdateTs);
        if (mdTick->Volume > 0 && mdTick->LastPrice != std::numeric_limits<double>::infinity())
        {
            CheckMatch(mdTick);
        }
    }
    void LastPriceOrderMatch::OnBar(QuantTrading::BarMarketData* mdBar)
    {

    }

    void LastPriceOrderMatch::CheckMatch(QuantTrading::DepthMarketData* mdTick)
    {
        auto& marketBuyQueueOrders = m_MarketBuyOrders[mdTick->InstrumentId];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            MatchMarketOrderAtPrice(marketBuyQueueOrder, mdTick->LastPrice, mdTick->AskPrice1);
        }
        m_MarketBuyOrders.erase(mdTick->InstrumentId);
        auto& marketSellQueueOrders = m_MarketSellOrders[mdTick->InstrumentId];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            MatchMarketOrderAtPrice(marketSellQueueOrder, mdTick->LastPrice, mdTick->BidPrice1);
        }
        m_MarketSellOrders.erase(mdTick->InstrumentId);

        auto& buyQueueOrders = m_BuyOrders[mdTick->InstrumentId];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(mdTick, buyQueueOrder))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(buyQueueOrders);
        std::erase_if(buyQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });

        auto& sellQueueOrders = m_SellOrders[mdTick->InstrumentId];
        for (auto& sellQueueOrder : sellQueueOrders)
        {
            if (!CheckMatchForOrder(mdTick, sellQueueOrder))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(sellQueueOrders);
        std::erase_if(sellQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });
    }
    bool LastPriceOrderMatch::CheckMatchForOrder(QuantTrading::DepthMarketData* mdTick, QuantTrading::Order* order)
    {
        if (order->Direction == DirectionType::Buy && DoubleUtility::DoubleLess(order->Price, mdTick->LastPrice))
            return false;
        else if (order->Direction == DirectionType::Sell && DoubleUtility::DoubleGreat(order->Price, mdTick->LastPrice))
            return false;

        GetNextTradeID(m_TradeID);
        Match(order, mdTick->LastPrice, order->VolumeTotal, m_TradeID);
        return true;
    }
}
