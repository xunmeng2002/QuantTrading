#include "OrderMatch.h"
#include "OrderBookOrderMatch.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <vector>

using namespace QuantTrading::OrderMatch;
using namespace QuantTrading::UnitTest;

TEST_SUITE("OrderMatch")
{

TEST_CASE("同价买单按先到先成交(H14回归)")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    auto* first_buy = order_pool.MakeOrder(1, DirectionType::Buy, 100.0, 10);
    auto* second_buy = order_pool.MakeOrder(2, DirectionType::Buy, 100.0, 10);
    auto* sell = order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 10);
    order_match.InsertOrder(first_buy);
    order_match.InsertOrder(second_buy);
    order_match.InsertOrder(sell);

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[1].OrderId == 3);
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1, 2});
    REQUIRE(subscriber.OrderUpdates.size() == 2);
    CHECK(subscriber.OrderUpdates[0].OrderId == 1);
    CHECK(subscriber.OrderUpdates[0].VolumeTraded == 10);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::AllTraded);
    CHECK(subscriber.OrderUpdates[1].OrderStatus == OrderStatusType::AllTraded);
}

TEST_CASE("同价卖单按先到先成交")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    auto* first_sell = order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 10);
    auto* second_sell = order_pool.MakeOrder(2, DirectionType::Sell, 100.0, 10);
    auto* buy = order_pool.MakeOrder(3, DirectionType::Buy, 100.0, 10);
    order_match.InsertOrder(first_sell);
    order_match.InsertOrder(second_sell);
    order_match.InsertOrder(buy);

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1, 2});
    CHECK(subscriber.OrderUpdates.size() == 2);
    CHECK(subscriber.OrderUpdates[0].OrderId == 1);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::AllTraded);
}

TEST_CASE("价格优先并吃穿多档深度")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    auto* buy_101 = order_pool.MakeOrder(1, DirectionType::Buy, 101.0, 10);
    auto* buy_100 = order_pool.MakeOrder(2, DirectionType::Buy, 100.0, 5);
    auto* sell = order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 12);
    order_match.InsertOrder(buy_101);
    order_match.InsertOrder(buy_100);
    order_match.InsertOrder(sell);

    REQUIRE(subscriber.Trades.size() == 4);
    CHECK(subscriber.Trades[0].Price == 101.0);
    CHECK(subscriber.Trades[0].Volume == 10);
    CHECK(subscriber.Trades[2].Price == 100.0);
    CHECK(subscriber.Trades[2].Volume == 2);
    CHECK(subscriber.OrderUpdates.size() == 4);
    CHECK(subscriber.OrderUpdates[2].OrderId == 2);
    CHECK(subscriber.OrderUpdates[2].VolumeTraded == 2);
    CHECK(subscriber.OrderUpdates[2].VolumeTotal == 3);
    CHECK(subscriber.OrderUpdates[2].OrderStatus == OrderStatusType::PartTraded);
}

TEST_CASE("部分成交后与后续对手单继续成交")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    auto* buy = order_pool.MakeOrder(1, DirectionType::Buy, 100.0, 10);
    order_match.InsertOrder(buy);
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));

    CHECK(subscriber.OrderUpdates.size() == 4);
    CHECK(subscriber.OrderUpdates[0].OrderId == 1);
    CHECK(subscriber.OrderUpdates[0].VolumeTraded == 4);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::PartTraded);
    CHECK(subscriber.OrderUpdates[2].OrderId == 1);
    CHECK(subscriber.OrderUpdates[2].VolumeTraded == 10);
    CHECK(subscriber.OrderUpdates[2].OrderStatus == OrderStatusType::AllTraded);
    CHECK(subscriber.Trades.size() == 4);
}

TEST_CASE("限价单不越过限价成交")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    auto* sell = order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 10);
    auto* low_buy = order_pool.MakeOrder(2, DirectionType::Buy, 99.0, 10);
    order_match.InsertOrder(sell);
    order_match.InsertOrder(low_buy);
    CHECK(subscriber.Trades.empty());

    auto* equal_buy = order_pool.MakeOrder(3, DirectionType::Buy, 100.0, 1);
    order_match.InsertOrder(equal_buy);
    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[0].Volume == 1);
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1, 2});
}

}
