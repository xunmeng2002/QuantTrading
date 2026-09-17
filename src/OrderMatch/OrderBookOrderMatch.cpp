#include "OrderBookOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace Spark::Core;

namespace QuantTrading::ordermatch
{
    OrderBookOrderMatch::OrderBookOrderMatch(const DateType& tradingDay, int tradeId)
        :OrderMatch(tradingDay, tradeId)
    {

    }
    OrderBookOrderMatch::~OrderBookOrderMatch()
    {

    }

    void OrderBookOrderMatch::OnTick(QuantTrading::DepthMarketData* mdTick)
    {

    }
    void OrderBookOrderMatch::OnBar(QuantTrading::BarMarketData* mdBar)
    {

    }
    void OrderBookOrderMatch::InsertOrder(QuantTrading::Order* order)
    {
        UpdateDateTime();
        if (order->OrderPriceType == OrderPriceTypeType::BestOwnPrice)
        {
            // 本方最优:按本方簿最优价入限价队列排队,由基类标准路径处理
            OrderMatch::InsertOrder(order);
            return;
        }
        if (order->OrderPriceType == OrderPriceTypeType::BestOppoPrice)
        {
            PriceType bestPrice;
            if (!TryGetOpponentBookBestPrice(order, bestPrice))
            {
                // 对手簿为空,无价格参照:接受后撤销
                CancelOrderOnInsert(order);
                return;
            }
            order->Price = bestPrice;
        }
        if ((order->OrderPriceType == OrderPriceTypeType::AnyPriceFOK || order->OrderPriceType == OrderPriceTypeType::LimitPriceFOK)
            && CountOpponentFillableVolume(order) < order->VolumeTotal)
        {
            // FOK 预扫可成量不足:接受后整单撤销
            CancelOrderOnInsert(order);
            return;
        }
        CheckMatch(order);
        if (order->VolumeTraded == 0)
        {
            orderMatchSubscriber_->OnOrder(order);
        }
        if (order->VolumeTotal > 0)
        {
            if (order->OrderPriceType == OrderPriceTypeType::AnyPriceFAK || order->OrderPriceType == OrderPriceTypeType::LimitPriceFAK)
            {
                // FAK 剩余量立即撤销
                CancelOrder(order);
            }
            else
            {
                AddOrderToLimitQueue(order);
            }
        }
    }
    void OrderBookOrderMatch::CheckMatch(QuantTrading::Order* order)
    {
        if (order->Direction == DirectionType::Buy)
        {
            auto& queueOrders = sellOrders_[order->InstrumentId];
            for (auto queueOrder : queueOrders)
            {
                if (!CheckMatchForTwoOrder(order, queueOrder))
                {
                    break;
                }
            }
        }
        else
        {
            auto& queueOrders = buyOrders_[order->InstrumentId];
            for (auto queueOrder : queueOrders)
            {
                if (!CheckMatchForTwoOrder(order, queueOrder))
                {
                    break;
                }
            }
        }
    }
    bool OrderBookOrderMatch::CheckMatchForTwoOrder(QuantTrading::Order* order, QuantTrading::Order* queueOrder)
    {
        if (order->VolumeTotal <= 0)
            return false;
        if (queueOrder->VolumeTotal <= 0)
            return true;
        if (HasOrderPriceBound(order->OrderPriceType))
        {
            if (order->Direction == DirectionType::Buy && DoubleUtility::DoubleLess(order->Price, queueOrder->Price))
                return false;
            if (order->Direction == DirectionType::Sell && DoubleUtility::DoubleGreat(order->Price, queueOrder->Price))
                return false;
        }

        VolumeType matchVolume = 0;
        PriceType matchPrice = 0.0;
        matchVolume = min(order->VolumeTotal, queueOrder->VolumeTotal);
        matchPrice = queueOrder->Price;

        GetNextTradeID(tradeId_);
        Match(queueOrder, matchPrice, matchVolume, tradeId_);
        Match(order, matchPrice, matchVolume, tradeId_);
        return true;
    }
}
