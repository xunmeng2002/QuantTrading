#include "GridStrategyTestHelpers.h"

#include "doctest/doctest.h"

#include <stdexcept>

using namespace QuantTrading::UnitTest;

// 配置键 BarPreces 经 GridParams 传入即声明周期；非法格式在构造期拒启（拒启语义同 DeclareBarPeriod）
TEST_CASE("GridStrategy declares bar period from params and rejects invalid preces at construction")
{
    FakeBackTestApi fake_api;
    auto fine_params = MakeGridParams(10.0, 2);
    fine_params.BarPreces = "5m";
    GridStrategyProbe fine_strategy(&fake_api, "accountA", fine_params);
    REQUIRE(fine_strategy.Start());

    auto bad_params = MakeGridParams(10.0, 2);
    bad_params.BarPreces = "5x";
    REQUIRE_THROWS_AS(GridStrategyProbe(&fake_api, "accountA", bad_params), std::logic_error);
}

// Bar 回放模式无 tick 回调：首根有效 bar Close 为锚价补挂阶梯，后续 bar 不重复锚定
TEST_CASE("GridStrategy anchors ladder from first bar when replay delivers bars instead of ticks")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();

    auto anchor_bar = MakeMdBarField("IF2503", 202410010935LL, 4000.0);
    fake_api.registered_spi->OnRtnBarMarketData(&anchor_bar);
    REQUIRE(fake_api.insert_requests.size() == 4);
    CHECK(fake_api.insert_requests[0].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[0].Price == doctest::Approx(3990.0));
    CHECK(fake_api.insert_requests[1].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[1].Price == doctest::Approx(4010.0));

    auto next_bar = MakeMdBarField("IF2503", 202410010940LL, 4050.0);
    fake_api.registered_spi->OnRtnBarMarketData(&next_bar);
    CHECK(fake_api.insert_requests.size() == 4);
}

// 场景基线：引擎日切结算统一撤单（撤单回报先于 SessionEnd 推送），策略在 OnOrder 中处理格位
TEST_CASE("GridStrategy resets unfilled open slot on day-end cancel and re-places at next anchor")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 买开 3990（ClientOrderId 1）零成交被日终撤销：复位 Empty、不即时重挂
    auto canceled_open_order = MakeCanceledOrderField("IF2503", 42, 1, OrderStatusType::Canceled, 0);
    fake_api.registered_spi->OnRtnOrder(&canceled_open_order);
    CHECK(fake_api.insert_requests.size() == 4);

    // 次日重锚（4050）：仅复位的买格重挂（4050-10=4040），其余三格未回放撤单保持原状
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(fake_api.insert_requests[4].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[4].OffsetFlag == OffsetFlagType::Open);
    CHECK(fake_api.insert_requests[4].Price == doctest::Approx(4040.0));
}

TEST_CASE("GridStrategy places close for filled volume when partially filled open order is canceled")
{
    FakeBackTestApi fake_api;
    auto grid_params = MakeGridParams(10.0, 2);
    grid_params.VolumePerGrid = 2;
    GridStrategyProbe strategy(&fake_api, "accountA", grid_params);
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 买开 3990（2 手）部分成交 1 手：未满格不补平仓
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    CHECK(fake_api.insert_requests.size() == 4);
    CHECK(strategy.GetLongPosition("IF2503") == 1);

    // 日终部成撤单：按已成交 1 手即时补平仓单（3990+10=4000）
    auto canceled_open_order = MakeCanceledOrderField("IF2503", 42, 1, OrderStatusType::PartTradedCanceled, 1);
    fake_api.registered_spi->OnRtnOrder(&canceled_open_order);
    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(fake_api.insert_requests[4].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[4].OffsetFlag == OffsetFlagType::Close);
    CHECK(fake_api.insert_requests[4].Price == doctest::Approx(4000.0));
    CHECK(fake_api.insert_requests[4].Volume == 1);

    // 次日平仓成交：持仓归零
    auto close_order = MakeOrderField("IF2503", 43, 5);
    fake_api.registered_spi->OnRtnOrder(&close_order);
    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
}

TEST_CASE("GridStrategy re-places close order for remaining volume when close order is canceled")
{
    FakeBackTestApi fake_api;
    auto grid_params = MakeGridParams(10.0, 2);
    grid_params.VolumePerGrid = 2;
    GridStrategyProbe strategy(&fake_api, "accountA", grid_params);
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 买开 3990 全量成交 2 手 → 补平仓单 2 手
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 2, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(fake_api.insert_requests[4].Volume == 2);

    // 平仓单部分成交 1 手后日终被撤：按剩余 1 手以原价位重下
    auto close_order = MakeOrderField("IF2503", 43, 5);
    fake_api.registered_spi->OnRtnOrder(&close_order);
    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 1);

    auto canceled_close_order = MakeCanceledOrderField("IF2503", 43, 5, OrderStatusType::PartTradedCanceled, 1);
    fake_api.registered_spi->OnRtnOrder(&canceled_close_order);
    REQUIRE(fake_api.insert_requests.size() == 6);
    CHECK(fake_api.insert_requests[5].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[5].OffsetFlag == OffsetFlagType::Close);
    CHECK(fake_api.insert_requests[5].Price == doctest::Approx(4000.0));
    CHECK(fake_api.insert_requests[5].Volume == 1);

    // 重下平仓单成交：配对结清、持仓归零
    auto replaced_close_order = MakeOrderField("IF2503", 44, 6);
    fake_api.registered_spi->OnRtnOrder(&replaced_close_order);
    auto replaced_close_trade = MakeTradeField("IF2503", 44, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&replaced_close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
}

TEST_CASE("GridStrategy re-places close after day-end cancel when slot cycles through completed pair")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 首周期：买开 3990 成交 → 补平仓 4000 → 平仓成交，格位完成配对（CloseFilledVolume 累计为 1）
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    auto close_order = MakeOrderField("IF2503", 43, 5);
    fake_api.registered_spi->OnRtnOrder(&close_order);
    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);
    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(strategy.GetLongPosition("IF2503") == 0);

    // 次日 SessionBegin：Closed 格复位 Empty（须清净上周期成交量），重锚仅重挂该格（4050-10=4040）
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    REQUIRE(fake_api.insert_requests.size() == 6);
    CHECK(fake_api.insert_requests[5].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[5].OffsetFlag == OffsetFlagType::Open);
    CHECK(fake_api.insert_requests[5].Price == doctest::Approx(4040.0));

    // 新周期：买开 4040 成交 → 补平仓 4050
    auto open_order2 = MakeOrderField("IF2503", 52, 6);
    fake_api.registered_spi->OnRtnOrder(&open_order2);
    auto open_trade2 = MakeTradeField("IF2503", 52, DirectionType::Buy, OffsetFlagType::Open, 4040.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade2);
    REQUIRE(fake_api.insert_requests.size() == 7);
    CHECK(fake_api.insert_requests[6].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[6].OffsetFlag == OffsetFlagType::Close);
    CHECK(fake_api.insert_requests[6].Price == doctest::Approx(4050.0));

    // 关键回归：上周期残留的 CloseFilledVolume 不得污染剩余量——平仓单日终零成交被撤后须重下 1 手
    auto canceled_close_order = MakeCanceledOrderField("IF2503", 53, 7, OrderStatusType::Canceled, 0);
    fake_api.registered_spi->OnRtnOrder(&canceled_close_order);
    REQUIRE(fake_api.insert_requests.size() == 8);
    CHECK(fake_api.insert_requests[7].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[7].OffsetFlag == OffsetFlagType::Close);
    CHECK(fake_api.insert_requests[7].Price == doctest::Approx(4050.0));
    CHECK(fake_api.insert_requests[7].Volume == 1);

    // 重下平仓单成交：新周期配对结清、持仓归零
    auto replaced_close_order = MakeOrderField("IF2503", 54, 8);
    fake_api.registered_spi->OnRtnOrder(&replaced_close_order);
    auto replaced_close_trade = MakeTradeField("IF2503", 54, DirectionType::Sell, OffsetFlagType::Close, 4050.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&replaced_close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
}

TEST_CASE("GridStrategy full day-end cancel sweep resets all open slots and re-places ladder next day")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 引擎日终清算：四格挂单全部撤单（零成交撤单回报先于 SessionEnd）
    for (int client_order_id = 1; client_order_id <= 4; ++client_order_id)
    {
        auto canceled_order = MakeCanceledOrderField("IF2503", 100 + client_order_id, client_order_id, OrderStatusType::Canceled, 0);
        fake_api.registered_spi->OnRtnOrder(&canceled_order);
    }
    CHECK(fake_api.insert_requests.size() == 4);

    SessionEndField session_end;
    fake_api.registered_spi->OnRtnSessionEnd(&session_end);
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);

    // 次日重锚（4050）：四格全部按新锚重挂
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    REQUIRE(fake_api.insert_requests.size() == 8);
    CHECK(fake_api.insert_requests[4].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[4].Price == doctest::Approx(4040.0));
    CHECK(fake_api.insert_requests[5].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[5].Price == doctest::Approx(4060.0));
    CHECK(fake_api.insert_requests[6].Price == doctest::Approx(4030.0));
    CHECK(fake_api.insert_requests[7].Price == doctest::Approx(4070.0));
}
