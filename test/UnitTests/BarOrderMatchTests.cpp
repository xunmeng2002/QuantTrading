#include "BarOrderMatch.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

using namespace QuantTrading::OrderMatch;
using namespace QuantTrading::UnitTest;

TEST_SUITE("BarOrderMatch")
{

TEST_CASE("限价买在bar价格区间内按委托价成交")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> barPool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 100.0, 10));
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90100, 0), 99.5, 101.0, 99.0, 100.5));

    REQUIRE(subscriber.Trades.size() == 1);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.Trades[0].Price == 100.0);
}

TEST_CASE("限价买高于bar最高价按最高价成交")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> barPool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 105.0, 10));
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90100, 0), 99.0, 101.0, 99.0, 100.0));

    REQUIRE(subscriber.Trades.size() == 1);
    CHECK(subscriber.Trades[0].Price == 101.0);
}

TEST_CASE("限价买低于bar最低价不成交直到bar触及")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> barPool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 98.0, 10));
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90100, 0), 99.0, 101.0, 99.0, 100.0));
    CHECK(subscriber.Trades.empty());

    // bar [96,97] 整体低于委托价 98:按悲观假设以该 bar 最高价 97 成交
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90200, 0), 96.5, 97.0, 96.0, 96.5));
    REQUIRE(subscriber.Trades.size() == 1);
    CHECK(subscriber.Trades[0].Price == 97.0);
}

TEST_CASE("限价卖低于bar最低价按最低价成交且高于最高价不成交")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> barPool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 95.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 105.0, 10));
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90100, 0), 99.0, 101.0, 99.0, 100.0));

    REQUIRE(subscriber.Trades.size() == 1);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.Trades[0].Price == 99.0);

    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90200, 0), 102.0, 106.0, 102.0, 105.5));
    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[1].OrderId == 2);
    CHECK(subscriber.Trades[1].Price == 105.0);
}

TEST_CASE("市价单按bar中价成交")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::BarMarketData> barPool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.OnBar(MakeBarRecord(barPool, MakeUpdateTs(20240301, 90100, 0), 99.0, 101.0, 99.0, 100.0));

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[1].Price == 100.0);
}

TEST_CASE("OnTick不触发撮合")
{
    DateType trading_day{"20240301"};
    BarOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;
    PoolRecordGuard<QuantTrading::DepthMarketData> tick_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));
    order_match.OnTick(MakeMdTick(tick_pool, MakeUpdateTs(20240301, 90000, 0), 100.0, 10, 99.0, 10, 101.0, 10));
    CHECK(subscriber.Trades.empty());
}

}
