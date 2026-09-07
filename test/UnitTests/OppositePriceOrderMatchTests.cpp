#include "OppositePriceOrderMatch.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <limits>

using namespace quanttrading::ordermatch;
using namespace quanttrading::unittest;

TEST_SUITE("OppositePriceOrderMatch")
{

TEST_CASE("市价买单按卖一价市价卖单按买一价成交")
{
    DateType trading_day{"20240301"};
    OppositePriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<mdb::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 102.0, 10));

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 102.0);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 99.0);

    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 100.0, 10, 99.0, 10, 102.0, 10));
    CHECK(subscriber.trades.size() == 2);
}

TEST_CASE("限价买单不高于卖一价时按卖一价成交")
{
    DateType trading_day{"20240301"};
    OppositePriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<mdb::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 105.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 98.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 101.0, 5));

    REQUIRE(subscriber.trades.size() == 1);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 101.0);

    // 卖一价回落到 97 后,挂着的 98 买单被成交
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 99.0, 10, 96.0, 10, 97.0, 5));
    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 97.0);
}

TEST_CASE("限价卖单不低于买一价时按买一价成交")
{
    DateType trading_day{"20240301"};
    OppositePriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<mdb::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 95.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 105.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 102.0, 5));

    REQUIRE(subscriber.trades.size() == 1);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 99.0);

    // 买一价上行到 106 后,挂着的 105 卖单被成交
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 105.0, 10, 106.0, 10, 107.0, 5));
    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 106.0);
}

TEST_CASE("无对手流动性或无限价的tick不触发买方撮合")
{
    DateType trading_day{"20240301"};
    OppositePriceOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<mdb::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 105.0, 10));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 102.0, 0));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90100, 0), 100.0, 10, 99.0, 10, std::numeric_limits<double>::infinity(), 10));
    CHECK(subscriber.trades.empty());

    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90200, 0), 100.0, 10, 99.0, 10, 101.0, 10));
    REQUIRE(subscriber.trades.size() == 1);
    CHECK(subscriber.trades[0].price == 101.0);
}

}
