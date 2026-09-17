#include "OppositePriceOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;


namespace QuantTrading::ordermatch
{
    OppositePriceOrderMatch::OppositePriceOrderMatch(const DateType& tradingDay, int tradeId)
        :OrderMatch(tradingDay, tradeId)
    {

    }
    OppositePriceOrderMatch::~OppositePriceOrderMatch()
    {

    }

    void OppositePriceOrderMatch::OnTick(QuantTrading::DepthMarketData* mdTick)
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
    void OppositePriceOrderMatch::OnBar(QuantTrading::BarMarketData* mdBar)
    {

    }

    void OppositePriceOrderMatch::CheckBuyMatch(QuantTrading::DepthMarketData* mdTick)
    {
        auto& marketBuyQueueOrders = marketBuyOrders_[mdTick->InstrumentId];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            GetNextTradeID(tradeId_);
            Match(marketBuyQueueOrder, mdTick->AskPrice1, marketBuyQueueOrder->VolumeTotal, tradeId_);
        }
        marketBuyOrders_.erase(mdTick->InstrumentId);

        auto& buyQueueOrders = buyOrders_[mdTick->InstrumentId];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(buyQueueOrder, mdTick->AskPrice1))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(buyQueueOrders);
        std::erase_if(buyQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });
    }
    void OppositePriceOrderMatch::CheckSellMatch(QuantTrading::DepthMarketData* mdTick)
    {
        auto& marketSellQueueOrders = marketSellOrders_[mdTick->InstrumentId];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            GetNextTradeID(tradeId_);
            Match(marketSellQueueOrder, mdTick->BidPrice1, marketSellQueueOrder->VolumeTotal, tradeId_);
        }
        marketSellOrders_.erase(mdTick->InstrumentId);

        auto& sellQueueOrders = sellOrders_[mdTick->InstrumentId];
        for (auto& sellQueueOrder : sellQueueOrders)
        {
            if (!CheckMatchForOrder(sellQueueOrder, mdTick->BidPrice1))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(sellQueueOrders);
        std::erase_if(sellQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });
    }
    bool OppositePriceOrderMatch::CheckMatchForOrder(QuantTrading::Order* order, const double& price)
    {
        if (order->Direction == DirectionType::Buy && DoubleUtility::DoubleLess(order->Price, price))
            return false;
        else if (order->Direction == DirectionType::Sell && DoubleUtility::DoubleGreat(order->Price, price))
            return false;

        GetNextTradeID(tradeId_);
        Match(order, price, order->VolumeTotal, tradeId_);
        return true;
    }
}

