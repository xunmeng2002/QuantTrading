#include "OrderMatch.h"
#include "OrderBookOrderMatch.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <limits>
#include <vector>

using namespace quanttrading::ordermatch;
using namespace quanttrading::unittest;

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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[1].order_id == 3);
    CHECK(subscriber.resting_order_ids == std::vector<int>{1, 2});
    REQUIRE(subscriber.order_updates.size() == 2);
    CHECK(subscriber.order_updates[0].order_id == 1);
    CHECK(subscriber.order_updates[0].volume_traded == 10);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::AllTraded);
    CHECK(subscriber.order_updates[1].order_status == OrderStatusType::AllTraded);
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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.resting_order_ids == std::vector<int>{1, 2});
    CHECK(subscriber.order_updates.size() == 2);
    CHECK(subscriber.order_updates[0].order_id == 1);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::AllTraded);
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

    REQUIRE(subscriber.trades.size() == 4);
    CHECK(subscriber.trades[0].price == 101.0);
    CHECK(subscriber.trades[0].volume == 10);
    CHECK(subscriber.trades[2].price == 100.0);
    CHECK(subscriber.trades[2].volume == 2);
    CHECK(subscriber.order_updates.size() == 4);
    CHECK(subscriber.order_updates[2].order_id == 2);
    CHECK(subscriber.order_updates[2].volume_traded == 2);
    CHECK(subscriber.order_updates[2].volume_total == 3);
    CHECK(subscriber.order_updates[2].order_status == OrderStatusType::PartTraded);
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

    CHECK(subscriber.order_updates.size() == 4);
    CHECK(subscriber.order_updates[0].order_id == 1);
    CHECK(subscriber.order_updates[0].volume_traded == 4);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::PartTraded);
    CHECK(subscriber.order_updates[2].order_id == 1);
    CHECK(subscriber.order_updates[2].volume_traded == 10);
    CHECK(subscriber.order_updates[2].order_status == OrderStatusType::AllTraded);
    CHECK(subscriber.trades.size() == 4);
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
    CHECK(subscriber.trades.empty());

    auto* equal_buy = order_pool.MakeOrder(3, DirectionType::Buy, 100.0, 1);
    order_match.InsertOrder(equal_buy);
    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[0].volume == 1);
    CHECK(subscriber.resting_order_ids == std::vector<int>{1, 2});
}

TEST_CASE("GetMatchPrice按委托价对手价最新价取有效价")
{
    CHECK(GetMatchPrice(OrderPriceTypeType::AnyPriceFAK, 90.0, 95.0, 100.0) == 95.0);
    CHECK(GetMatchPrice(OrderPriceTypeType::LimitPrice, 90.0, 95.0, std::numeric_limits<double>::infinity()) == 95.0);
    CHECK(GetMatchPrice(OrderPriceTypeType::LimitPrice, 95.0, 90.0, 100.0) == 95.0);
    CHECK(GetMatchPrice(OrderPriceTypeType::LimitPrice, 95.0, 100.0, 90.0) == 95.0);
    CHECK(GetMatchPrice(OrderPriceTypeType::LimitPrice, 95.0, 97.0, 100.0) == 97.0);
    CHECK(GetMatchPrice(OrderPriceTypeType::LimitPrice, 95.0, 90.0, 93.0) == 93.0);
}

}
