#include "OrderBookOrderMatch.h"
#include "OrderUtility.h"
#include "Error.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <cstring>
#include <vector>

using namespace QuantTrading::OrderMatch;
using namespace QuantTrading::UnitTest;

TEST_SUITE("OrderBookMarketOrders")
{

TEST_CASE("市价FAK吃满对手簿全成")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].OrderId == 1);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[1].OrderId == 2);
    CHECK(subscriber.Trades[1].Price == 100.0);
    CHECK(subscriber.OrderUpdates.back().OrderId == 2);
    CHECK(subscriber.OrderUpdates.back().OrderStatus == OrderStatusType::AllTraded);
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1});
}

TEST_CASE("市价FAK部成剩余撤销且不滞留队列(H15回归)")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].Volume == 4);
    CHECK(subscriber.Trades[1].OrderId == 2);
    CHECK(subscriber.Trades[1].Volume == 4);
    REQUIRE(subscriber.OrderUpdates.size() == 3);
    CHECK(subscriber.OrderUpdates[1].OrderId == 2);
    CHECK(subscriber.OrderUpdates[1].OrderStatus == OrderStatusType::PartTraded);
    CHECK(subscriber.OrderUpdates[2].OrderId == 2);
    CHECK(subscriber.OrderUpdates[2].VolumeTotal == 0);
    CHECK(subscriber.OrderUpdates[2].OrderStatus == OrderStatusType::PartTradedCanceled);

    // 剩余量已撤销:后续对手盘不再为其成交
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    CHECK(subscriber.Trades.size() == 2);
}

TEST_CASE("市价FAK零成交接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));

    CHECK(subscriber.Trades.empty());
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1});
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].VolumeTraded == 0);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("市价FOK足量逐档全成")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 101.0, 6));
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFOK));

    REQUIRE(subscriber.Trades.size() == 4);
    CHECK(subscriber.Trades[1].OrderId == 3);
    CHECK(subscriber.Trades[1].Price == 100.0);
    CHECK(subscriber.Trades[1].Volume == 4);
    CHECK(subscriber.Trades[3].OrderId == 3);
    CHECK(subscriber.Trades[3].Price == 101.0);
    CHECK(subscriber.Trades[3].Volume == 6);
    CHECK(subscriber.OrderUpdates.back().OrderId == 3);
    CHECK(subscriber.OrderUpdates.back().OrderStatus == OrderStatusType::AllTraded);
}

TEST_CASE("市价FOK可成量不足整单撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFOK));

    // 预扫不足:不做任何成交,接受确认后整单撤销
    CHECK(subscriber.Trades.empty());
    CHECK(subscriber.RestingOrderIds == std::vector<int>{1, 2});
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].OrderId == 2);
    CHECK(subscriber.OrderUpdates[0].VolumeTraded == 0);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("限价FOK受价预扫不足整单撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Sell, 105.0, 6));
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Buy, 100.0, 10, OrderPriceTypeType::LimitPriceFOK));

    // 委托价 100 之外还有 6 手:受价预扫只累计 4 手,不足整撤
    CHECK(subscriber.Trades.empty());
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].OrderId == 3);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("限价FAK部成剩余撤销且后续对手单不再成交")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 100.0, 10, OrderPriceTypeType::LimitPriceFAK));

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[1].OrderId == 2);
    CHECK(subscriber.Trades[1].Volume == 4);
    REQUIRE(subscriber.OrderUpdates.size() == 3);
    CHECK(subscriber.OrderUpdates[1].OrderId == 2);
    CHECK(subscriber.OrderUpdates[1].OrderStatus == OrderStatusType::PartTraded);
    CHECK(subscriber.OrderUpdates[2].OrderId == 2);
    CHECK(subscriber.OrderUpdates[2].OrderStatus == OrderStatusType::PartTradedCanceled);

    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    CHECK(subscriber.Trades.size() == 2);
}

TEST_CASE("限价FAK无对手盘接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 99.0, 10, OrderPriceTypeType::LimitPriceFAK));

    CHECK(subscriber.RestingOrderIds == std::vector<int>{1});
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("本方最优按本方簿最优价入簿排队")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 99.0, 10));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 100.0, 10));
    // 买3 携带价 98 无效:解析为本方簿最优价 100 后入限价队列
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Buy, 98.0, 10, OrderPriceTypeType::BestOwnPrice));

    CHECK(subscriber.RestingOrderIds == std::vector<int>{1, 2, 3});
    CHECK(subscriber.Trades.empty());

    order_match.InsertOrder(order_pool.MakeOrder(4, DirectionType::Sell, 100.0, 20));
    REQUIRE(subscriber.Trades.size() == 4);
    CHECK(subscriber.Trades[0].OrderId == 2);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[2].OrderId == 3);
    CHECK(subscriber.Trades[2].Price == 100.0);
}

TEST_CASE("本方最优空簿接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::BestOwnPrice));

    CHECK(subscriber.RestingOrderIds == std::vector<int>{1});
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("对方最优按对手最优价成交且剩余挂该价")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Sell, 100.0, 4));
    order_match.InsertOrder(order_pool.MakeOrder(2, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::BestOppoPrice));

    REQUIRE(subscriber.Trades.size() == 2);
    CHECK(subscriber.Trades[0].Price == 100.0);
    CHECK(subscriber.Trades[0].Volume == 4);
    CHECK(subscriber.Trades[1].OrderId == 2);
    REQUIRE(subscriber.OrderUpdates.size() == 2);
    CHECK(subscriber.OrderUpdates[1].OrderId == 2);
    CHECK(subscriber.OrderUpdates[1].VolumeTraded == 4);
    CHECK(subscriber.OrderUpdates[1].OrderStatus == OrderStatusType::PartTraded);

    // 剩余 6 手挂在对手最优价 100:后续对手单按该价与其成交
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    REQUIRE(subscriber.Trades.size() == 4);
    CHECK(subscriber.Trades[2].OrderId == 2);
    CHECK(subscriber.Trades[2].Price == 100.0);
    CHECK(subscriber.Trades[2].Volume == 6);
    REQUIRE(subscriber.OrderUpdates.size() == 4);
    CHECK(subscriber.OrderUpdates[2].OrderId == 2);
    CHECK(subscriber.OrderUpdates[2].OrderStatus == OrderStatusType::AllTraded);
}

TEST_CASE("对方最优空对手簿接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::BestOppoPrice));

    CHECK(subscriber.RestingOrderIds == std::vector<int>{1});
    REQUIRE(subscriber.OrderUpdates.size() == 1);
    CHECK(subscriber.OrderUpdates[0].OrderStatus == OrderStatusType::Canceled);
}

TEST_CASE("入口校验按市价限价类分流合约量限")
{
    ReqInsertOrderField reqInsertOrder;
    std::memset(&reqInsertOrder, 0, sizeof(reqInsertOrder));
    CopyString(reqInsertOrder.AccountId, "test");
    reqInsertOrder.Direction = DirectionType::Buy;
    reqInsertOrder.OffsetFlag = OffsetFlagType::Open;
    reqInsertOrder.Volume = 10;

    QuantTrading::Instrument instrument;
    std::memset(&instrument, 0, sizeof(instrument));
    instrument.MaxMarketOrderVolume = 5;
    instrument.MaxLimitOrderVolume = 100;

    reqInsertOrder.OrderPriceType = OrderPriceTypeType::AnyPriceFAK;
    CHECK(CheckForInsertOrder(&reqInsertOrder, &instrument) == QuantTrading::ErrorInvalidOrderVolume);
    reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
    CHECK(CheckForInsertOrder(&reqInsertOrder, &instrument) == QuantTrading::ErrorNone);
    reqInsertOrder.OrderPriceType = static_cast<OrderPriceTypeType>(99);
    CHECK(CheckForInsertOrder(&reqInsertOrder, &instrument) == QuantTrading::ErrorInvalidOrderPriceType);
}

}
