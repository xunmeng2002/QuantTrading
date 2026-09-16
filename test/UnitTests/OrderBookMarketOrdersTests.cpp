#include "OrderBookOrderMatch.h"
#include "OrderUtility.h"
#include "Error.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <cstring>
#include <vector>

using namespace QuantTrading::ordermatch;
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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].order_id == 1);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].price == 100.0);
    CHECK(subscriber.order_updates.back().order_id == 2);
    CHECK(subscriber.order_updates.back().order_status == OrderStatusType::AllTraded);
    CHECK(subscriber.resting_order_ids == std::vector<int>{1});
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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].volume == 4);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].volume == 4);
    REQUIRE(subscriber.order_updates.size() == 3);
    CHECK(subscriber.order_updates[1].order_id == 2);
    CHECK(subscriber.order_updates[1].order_status == OrderStatusType::PartTraded);
    CHECK(subscriber.order_updates[2].order_id == 2);
    CHECK(subscriber.order_updates[2].volume_total == 0);
    CHECK(subscriber.order_updates[2].order_status == OrderStatusType::PartTradedCanceled);

    // 剩余量已撤销:后续对手盘不再为其成交
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    CHECK(subscriber.trades.size() == 2);
}

TEST_CASE("市价FAK零成交接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::AnyPriceFAK));

    CHECK(subscriber.trades.empty());
    CHECK(subscriber.resting_order_ids == std::vector<int>{1});
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].volume_traded == 0);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
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

    REQUIRE(subscriber.trades.size() == 4);
    CHECK(subscriber.trades[1].order_id == 3);
    CHECK(subscriber.trades[1].price == 100.0);
    CHECK(subscriber.trades[1].volume == 4);
    CHECK(subscriber.trades[3].order_id == 3);
    CHECK(subscriber.trades[3].price == 101.0);
    CHECK(subscriber.trades[3].volume == 6);
    CHECK(subscriber.order_updates.back().order_id == 3);
    CHECK(subscriber.order_updates.back().order_status == OrderStatusType::AllTraded);
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
    CHECK(subscriber.trades.empty());
    CHECK(subscriber.resting_order_ids == std::vector<int>{1, 2});
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].order_id == 2);
    CHECK(subscriber.order_updates[0].volume_traded == 0);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
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
    CHECK(subscriber.trades.empty());
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].order_id == 3);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[1].order_id == 2);
    CHECK(subscriber.trades[1].volume == 4);
    REQUIRE(subscriber.order_updates.size() == 3);
    CHECK(subscriber.order_updates[1].order_id == 2);
    CHECK(subscriber.order_updates[1].order_status == OrderStatusType::PartTraded);
    CHECK(subscriber.order_updates[2].order_id == 2);
    CHECK(subscriber.order_updates[2].order_status == OrderStatusType::PartTradedCanceled);

    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    CHECK(subscriber.trades.size() == 2);
}

TEST_CASE("限价FAK无对手盘接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 99.0, 10, OrderPriceTypeType::LimitPriceFAK));

    CHECK(subscriber.resting_order_ids == std::vector<int>{1});
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
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

    CHECK(subscriber.resting_order_ids == std::vector<int>{1, 2, 3});
    CHECK(subscriber.trades.empty());

    order_match.InsertOrder(order_pool.MakeOrder(4, DirectionType::Sell, 100.0, 20));
    REQUIRE(subscriber.trades.size() == 4);
    CHECK(subscriber.trades[0].order_id == 2);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[2].order_id == 3);
    CHECK(subscriber.trades[2].price == 100.0);
}

TEST_CASE("本方最优空簿接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::BestOwnPrice));

    CHECK(subscriber.resting_order_ids == std::vector<int>{1});
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
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

    REQUIRE(subscriber.trades.size() == 2);
    CHECK(subscriber.trades[0].price == 100.0);
    CHECK(subscriber.trades[0].volume == 4);
    CHECK(subscriber.trades[1].order_id == 2);
    REQUIRE(subscriber.order_updates.size() == 2);
    CHECK(subscriber.order_updates[1].order_id == 2);
    CHECK(subscriber.order_updates[1].volume_traded == 4);
    CHECK(subscriber.order_updates[1].order_status == OrderStatusType::PartTraded);

    // 剩余 6 手挂在对手最优价 100:后续对手单按该价与其成交
    order_match.InsertOrder(order_pool.MakeOrder(3, DirectionType::Sell, 100.0, 6));
    REQUIRE(subscriber.trades.size() == 4);
    CHECK(subscriber.trades[2].order_id == 2);
    CHECK(subscriber.trades[2].price == 100.0);
    CHECK(subscriber.trades[2].volume == 6);
    REQUIRE(subscriber.order_updates.size() == 4);
    CHECK(subscriber.order_updates[2].order_id == 2);
    CHECK(subscriber.order_updates[2].order_status == OrderStatusType::AllTraded);
}

TEST_CASE("对方最优空对手簿接受后撤销")
{
    DateType trading_day{"20240301"};
    OrderBookOrderMatch order_match(trading_day);
    RecordingOrderMatchSubscriber subscriber;
    order_match.Subscribe(&subscriber);
    OrderPoolGuard order_pool;

    order_match.InsertOrder(order_pool.MakeOrder(1, DirectionType::Buy, 0.0, 10, OrderPriceTypeType::BestOppoPrice));

    CHECK(subscriber.resting_order_ids == std::vector<int>{1});
    REQUIRE(subscriber.order_updates.size() == 1);
    CHECK(subscriber.order_updates[0].order_status == OrderStatusType::Canceled);
}

TEST_CASE("入口校验按市价限价类分流合约量限")
{
    ReqInsertOrderField req_insert_order;
    std::memset(&req_insert_order, 0, sizeof(req_insert_order));
    CopyString(req_insert_order.AccountId, "test");
    req_insert_order.Direction = DirectionType::Buy;
    req_insert_order.OffsetFlag = OffsetFlagType::Open;
    req_insert_order.Volume = 10;

    QuantTrading::Instrument instrument;
    std::memset(&instrument, 0, sizeof(instrument));
    instrument.MaxMarketOrderVolume = 5;
    instrument.MaxLimitOrderVolume = 100;

    req_insert_order.OrderPriceType = OrderPriceTypeType::AnyPriceFAK;
    CHECK(CheckForInsertOrder(&req_insert_order, &instrument) == QuantTrading::ErrorInvalidOrderVolume);
    req_insert_order.OrderPriceType = OrderPriceTypeType::LimitPrice;
    CHECK(CheckForInsertOrder(&req_insert_order, &instrument) == QuantTrading::ErrorNone);
    req_insert_order.OrderPriceType = static_cast<OrderPriceTypeType>(99);
    CHECK(CheckForInsertOrder(&req_insert_order, &instrument) == QuantTrading::ErrorInvalidOrderPriceType);
}

}
