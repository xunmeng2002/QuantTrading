#include "GridStrategyTestHelpers.h"

#include "doctest/doctest.h"

using namespace quanttrading::unittest;

TEST_CASE("GridStrategy places ladder around first tick anchor")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();

    auto md_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&md_tick);

    REQUIRE(fake_api.insert_requests.size() == 4);
    CHECK(fake_api.insert_requests[0].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[0].OffsetFlag == OffsetFlagType::Open);
    CHECK(fake_api.insert_requests[0].Price == doctest::Approx(3990.0));
    CHECK(fake_api.insert_requests[0].ClientOrderID == 1);
    CHECK(fake_api.insert_requests[1].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[1].Price == doctest::Approx(4010.0));
    CHECK(fake_api.insert_requests[2].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[2].Price == doctest::Approx(3980.0));
    CHECK(fake_api.insert_requests[3].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[3].Price == doctest::Approx(4020.0));
    for (auto& insert_request : fake_api.insert_requests)
    {
        CHECK(insert_request.OrderPriceType == OrderPriceTypeType::LimitPrice);
        CHECK(insert_request.Volume == 1);
    }
}

TEST_CASE("GridStrategy places close order once after open fill and ignores duplicate fill")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 买开 3990 成交：OnRtnOrder 先于 OnRtnTrade（引擎成交推送顺序）
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);

    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(fake_api.insert_requests[4].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[4].OffsetFlag == OffsetFlagType::Close);
    CHECK(fake_api.insert_requests[4].Price == doctest::Approx(4000.0));
    CHECK(strategy.GetLongPosition("IF2503") == 1);

    // 格位已转入 ClosePending：同一开仓单的重复成交不得再次补平仓单
    // （StrategyBase 持仓累计不做去重，真实引擎每笔成交只推送一次，此处仅验证状态机防重）
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    CHECK(fake_api.insert_requests.size() == 5);
}

TEST_CASE("GridStrategy pair closes flat after close fill")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 开仓成交 → 补平仓单 → 平仓成交：持仓归零
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    REQUIRE(fake_api.insert_requests.size() == 5);

    auto close_order = MakeOrderField("IF2503", 43, 5);
    fake_api.registered_spi->OnRtnOrder(&close_order);
    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
    CHECK(strategy.GetShortPosition("IF2503") == 0);
}

TEST_CASE("GridStrategy re-places rejected level at next session anchor")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 拒单（level0 卖格）复位 Empty
    ReqInsertOrderField rejected_request;
    std::memset(&rejected_request, 0, sizeof(rejected_request));
    rejected_request.ClientOrderID = 2;
    RspInfoField reject_info;
    reject_info.ErrorID = 27;
    fake_api.registered_spi->OnRspInsertOrder(&rejected_request, &reject_info, 0, true);

    // 策略自身不发起撤单（日终挂单由引擎统一清算并推送撤单回报，本用例未回放撤单事件）
    SessionEndField session_end;
    fake_api.registered_spi->OnRtnSessionEnd(&session_end);
    CHECK(fake_api.cancel_requests.empty());

    // 次日重锚：本用例未回放撤单回报，OpenPending 三格保持原状，仅被拒格位按新锚重挂
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    REQUIRE(fake_api.insert_requests.size() == 5);
    CHECK(fake_api.insert_requests[4].Direction == DirectionType::Sell);
    CHECK(fake_api.insert_requests[4].Price == doctest::Approx(4060.0));
}

TEST_CASE("GridStrategy keeps pending close orders working across session end")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 一格开仓成交进入 ClosePending（日终撤单回报未回放时格位原状保留），其余三格 OpenPending
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    REQUIRE(fake_api.insert_requests.size() == 5);

    // 次日重锚不重复挂单（ClosePending 与 OpenPending 格位均原状保留）
    SessionEndField session_end;
    fake_api.registered_spi->OnRtnSessionEnd(&session_end);
    CHECK(fake_api.cancel_requests.empty());
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    CHECK(fake_api.insert_requests.size() == 5);
}

TEST_CASE("GridStrategy re-arms closed level at next session anchor")
{
    FakeBackTestApi fake_api;
    GridStrategyProbe strategy(&fake_api, "accountA", MakeGridParams(10.0, 2));
    strategy.Start();
    auto anchor_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.insert_requests.size() == 4);

    // 开平各一笔完成配对 → 格位 Closed
    auto open_order = MakeOrderField("IF2503", 42, 1);
    fake_api.registered_spi->OnRtnOrder(&open_order);
    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    auto close_order = MakeOrderField("IF2503", 43, 5);
    fake_api.registered_spi->OnRtnOrder(&close_order);
    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);

    // 次日重锚：仅 Closed 的 level0 买格重挂（本用例未回放撤单回报，OpenPending 三格保持原状）
    SessionEndField session_end;
    fake_api.registered_spi->OnRtnSessionEnd(&session_end);
    SessionBeginField session_begin;
    fake_api.registered_spi->OnRtnSessionBegin(&session_begin);
    auto next_day_tick = MakeMdTickField("IF2503", 4050.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&next_day_tick);
    REQUIRE(fake_api.insert_requests.size() == 6);
    CHECK(fake_api.insert_requests[5].Direction == DirectionType::Buy);
    CHECK(fake_api.insert_requests[5].Price == doctest::Approx(4040.0));
}
