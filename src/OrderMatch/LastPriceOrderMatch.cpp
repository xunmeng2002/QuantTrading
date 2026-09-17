#include "LastPriceOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;

namespace QuantTrading::OrderMatch
{
    LastPriceOrderMatch::LastPriceOrderMatch(const DateType& tradingDay, int tradeId)
        :OrderMatch(tradingDay, tradeId)
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
        auto& marketBuyQueueOrders = marketBuyOrders_[mdTick->InstrumentId];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            MatchMarketOrderAtPrice(marketBuyQueueOrder, mdTick->LastPrice, mdTick->AskPrice1);
        }
        marketBuyOrders_.erase(mdTick->InstrumentId);
        auto& marketSellQueueOrders = marketSellOrders_[mdTick->InstrumentId];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            MatchMarketOrderAtPrice(marketSellQueueOrder, mdTick->LastPrice, mdTick->BidPrice1);
        }
        marketSellOrders_.erase(mdTick->InstrumentId);

        auto& buyQueueOrders = buyOrders_[mdTick->InstrumentId];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(mdTick, buyQueueOrder))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(buyQueueOrders);
        std::erase_if(buyQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });

        auto& sellQueueOrders = sellOrders_[mdTick->InstrumentId];
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

        GetNextTradeID(tradeId_);
        Match(order, mdTick->LastPrice, order->VolumeTotal, tradeId_);
        return true;
    }
}
