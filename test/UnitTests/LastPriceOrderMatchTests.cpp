#include "LastPriceOrderMatch.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <limits>

using namespace QuantTrading::ordermatch;
using namespace QuantTrading::UnitTest;

TEST_SUITE("LastPriceOrderMatch")
{

TEST_CASE("市价买卖单被首个有效tick全额成交于最新价")
{
    DateType trading_day{"20240301"};
    LastPriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 101.0, 10));

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 100.0);
    REQUIRE(subscriber.order_updates.size() == 2);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::AllTraded);

    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 101.0, 10, 100.0, 10, 102.0, 10));
    CHECK(subscriber.trades.size() == 2);
}

TEST_CASE("限价买单按最新价成交且低于最新价不追价")
{
    DateType trading_day{"20240301"};
    LastPriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 105.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 99.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 101.0, 10, 100.0, 10, 102.0, 10));

    REQUIRE(subscriber.trades.size() == 1);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 101.0);

    // 最新价回落到 98 后,挂着的 99 买单被成交
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 98.0, 10, 97.0, 10, 99.0, 10));
    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 98.0);
}

TEST_CASE("限价卖单不高于最新价时按最新价成交")
{
    DateType trading_day{"20240301"};
    LastPriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 95.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 105.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 101.0, 10, 100.0, 10, 102.0, 10));

    REQUIRE(subscriber.trades.size() == 1);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 101.0);

    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 106.0, 10, 105.0, 10, 107.0, 10));
    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 106.0);
}

TEST_CASE("无效tick与OnBar不触发撮合")
{
    DateType trading_day{"20240301"};
    LastPriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::DepthMarketData> tick_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> bar_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), std::numeric_limits<double>::infinity(), 10, 99.0, 10, 101.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 100.0, 0, 99.0, 10, 101.0, 10));
    order_match.OnBar(MakeBarRecord(bar_pool, MakeUpdateTs(20240301, 90200, 0), 99.0, 101.0, 98.0, 100.0));
    CHECK(subscriber.trades.empty());

    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90300, 0), 100.0, 10, 99.0, 10, 101.0, 10));
    REQUIRE(subscriber.trades.size() == 1);
}

}
