#include "BarOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>
#include <string>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;

namespace QuantTrading::ordermatch
{
    BarOrderMatch::BarOrderMatch(const DateType& tradingDay, int maxTradeID)
        :OrderMatch(tradingDay, maxTradeID)
    {

    }
    BarOrderMatch::~BarOrderMatch()
    {

    }

    void BarOrderMatch::OnTick(QuantTrading::DepthMarketData* mdTick)
    {

    }
    void BarOrderMatch::OnBar(QuantTrading::BarMarketData* mdBar)
    {
        UpdateDateTime(mdBar->UpdateTs);
        CheckMatch(mdBar);
    }
    void BarOrderMatch::CheckMatch(QuantTrading::BarMarketData* mdBar)
    {
        auto& marketBuyQueueOrders = m_MarketBuyOrders[mdBar->InstrumentId];
        for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
        {
            CheckMatchForOrder(mdBar, marketBuyQueueOrder);
        }
        m_MarketBuyOrders.erase(mdBar->InstrumentId);
        auto& marketSellQueueOrders = m_MarketSellOrders[mdBar->InstrumentId];
        for (auto& marketSellQueueOrder : marketSellQueueOrders)
        {
            CheckMatchForOrder(mdBar, marketSellQueueOrder);
        }
        m_MarketSellOrders.erase(mdBar->InstrumentId);

        auto& buyQueueOrders = m_BuyOrders[mdBar->InstrumentId];
        for (auto& buyQueueOrder : buyQueueOrders)
        {
            if (!CheckMatchForOrder(mdBar, buyQueueOrder))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(buyQueueOrders);
        std::erase_if(buyQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });

        auto& sellQueueOrders = m_SellOrders[mdBar->InstrumentId];
        for (auto& sellQueueOrder : sellQueueOrders)
        {
            if (!CheckMatchForOrder(mdBar, sellQueueOrder))
            {
                break;
            }
        }
        CancelUnfilledImmediateOrders(sellQueueOrders);
        std::erase_if(sellQueueOrders, [](QuantTrading::Order* order) {return order->VolumeTotal == 0; });
    }
    bool BarOrderMatch::CheckMatchForOrder(QuantTrading::BarMarketData* mdBar, QuantTrading::Order* order)
    {
        PriceType matchPrice;
        switch (order->OrderPriceType)
        {
        case OrderPriceTypeType::AnyPriceFAK:
        case OrderPriceTypeType::AnyPriceFOK:
            // 市价族按 bar 中价成交
            matchPrice = (mdBar->High + mdBar->Low) / 2;
            break;
        case OrderPriceTypeType::BestOppoPrice:
            // 对方最优按 bar 收盘价成交
            matchPrice = mdBar->Close;
            break;
        default:
            // 限价族(含已解析的本方最优)按 bar 区间受价成交
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
            break;
        }
        GetNextTradeID(m_TradeID);
        Match(order, matchPrice, order->VolumeTotal, m_TradeID);
        return true;
    }
}

