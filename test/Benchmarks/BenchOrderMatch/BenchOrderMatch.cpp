#include "OrderBookOrderMatch.h"

#include <Spark/TemplateLib/Benchmark/BenchmarkRunner.h>

#include <cstdio>

using namespace QuantTrading;
using namespace QuantTrading::OrderMatch;
namespace Benchmark = Spark::Benchmark;

namespace
{
    // 基准专用：同一撮合器连测多轮，每轮摘掉簿内指针。
    // 生产路径由交易日切换清理，不在此测——不清理会让下一轮用到已归还对象池的订单
    class ReusableOrderBookOrderMatch : public OrderBookOrderMatch
    {
    public:
        using OrderBookOrderMatch::OrderBookOrderMatch;

        void ClearOrderBooks()
        {
            for (auto& orderBook : buyOrders_)
                orderBook.second.clear();
            for (auto& orderBook : sellOrders_)
                orderBook.second.clear();
            for (auto& orderBook : marketBuyOrders_)
                orderBook.second.clear();
            for (auto& orderBook : marketSellOrders_)
                orderBook.second.clear();
        }
    };

    class CountingOrderMatchSubscriber : public OrderMatchSubscriber
    {
    public:
        void OnOrder(Order* /*order*/) override
        {
            ++acceptedOrderCount;
        }

        void OnOrderUpdate(Order* /*order*/, Order* newOrder) override
        {
            newOrder->Deallocate();
            ++orderUpdateCount;
        }

        void OnTrade(Trade* trade) override
        {
            trade->Deallocate();
            ++tradeCount;
        }

        void Reset()
        {
            acceptedOrderCount = 0;
            orderUpdateCount = 0;
            tradeCount = 0;
        }

        std::size_t acceptedOrderCount = 0;
        std::size_t orderUpdateCount = 0;
        std::size_t tradeCount = 0;
    };

    Order* MakeOrder(int orderId, DirectionType direction, double price, VolumeType volume)
    {
        Order* order = Order::Allocate();
        std::snprintf(order->TradingDay, sizeof(order->TradingDay), "%s", "20240301");
        std::snprintf(order->AccountId, sizeof(order->AccountId), "%s", "bench");
        std::snprintf(order->ExchangeId, sizeof(order->ExchangeId), "%s", "SHFE");
        std::snprintf(order->InstrumentId, sizeof(order->InstrumentId), "%s", "cu2503");
        order->OrderId = orderId;
        order->Direction = direction;
        order->OffsetFlag = OffsetFlagType::Open;
        order->OrderPriceType = OrderPriceTypeType::LimitPrice;
        order->Price = price;
        order->Volume = volume;
        order->VolumeTotal = volume;
        order->OrderStatus = OrderStatusType::Inserted;
        order->VolumeMultiple = 1;
        return order;
    }
}

int main()
{
    Benchmark::PrintHeader();

    const DateType tradingDay{"20240301"};
    ReusableOrderBookOrderMatch orderMatch(tradingDay);
    CountingOrderMatchSubscriber subscriber;
    orderMatch.Subscribe(&subscriber);

    // 一张卖方挂单被一张同价买方单完全吃掉的整条路径：
    // 两次下单入口（含 UpdateDateTime）、两次成交回报、两次订单更新回报，外加对象池的取用与归还
    auto matchOneOrderPair = [&]() -> std::size_t
    {
        Order* sellOrder = MakeOrder(1, DirectionType::Sell, 100.0, 10);
        Order* buyOrder = MakeOrder(2, DirectionType::Buy, 100.0, 10);
        orderMatch.InsertOrder(sellOrder);
        orderMatch.InsertOrder(buyOrder);
        const std::size_t tradeCount = subscriber.tradeCount;

        orderMatch.ClearOrderBooks();
        sellOrder->Deallocate();
        buyOrder->Deallocate();
        subscriber.Reset();
        return tradeCount;
    };

    // 一张挂单必须被吃掉并产生两笔成交回报，读不到就当场失败，不给错误读数留出口
    if (matchOneOrderPair() != 2)
    {
        std::fprintf(stderr, "expected 2 trades for one fully matched order pair\n");
        return 1;
    }

    Benchmark::Measure("OrderBookOrderMatch.InsertOrder_matched_pair", matchOneOrderPair);
    return 0;
}
