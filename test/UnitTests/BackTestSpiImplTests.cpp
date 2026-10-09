#include "TestHelpers.h"
#include "BackTestSpiImpl.h"

#include "doctest/doctest.h"

#include <limits>
#include <stdexcept>
#include <string>

using namespace QuantTrading::UnitTest;
using QuantTrading::TestBackTest::BackTestSpiImpl;
using QuantTrading::TestBackTest::BackTestSpiParams;

namespace
{
    constexpr double TestOrderTriggerRatio = 0.1;

    BackTestSpiParams MakeBackTestSpiParams(double order_trigger_ratio, int order_volume)
    {
        BackTestSpiParams params;
        params.OrderTriggerRatio = order_trigger_ratio;
        params.OrderVolume = order_volume;
        params.AccountId = "18511899894";
        params.ExchangeId = "SZSE";
        params.InstrumentId = "000001";
        return params;
    }
}

// 首帧只建基准并开一手，委托参数取自本帧：修复前它把「刚 new 出来的零值结构」当成委托参数
// （价格 0、交易所代码空），故这里同时钉住价格与交易所代码
TEST_CASE("BackTestSpiImpl anchors on first tick with the frame's own fields")
{
    FakeBackTestApi fake_api;
    BackTestSpiImpl spi(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 1));

    auto first_tick = MakeMdTickField("000001", 10.0);
    CopyString(first_tick.ExchangeId, "SZSE");
    spi.OnRtnDepthMarketData(&first_tick);

    REQUIRE(fake_api.InsertRequests.size() == 1);
    CHECK(fake_api.InsertRequests[0].Price == doctest::Approx(10.0));
    CHECK(fake_api.InsertRequests[0].Direction == DirectionType::Buy);
    CHECK(fake_api.InsertRequests[0].Volume == 1);
    CHECK(std::string(fake_api.InsertRequests[0].ExchangeId) == "SZSE");
    CHECK(std::string(fake_api.InsertRequests[0].AccountId) == "18511899894");
}

// 基准价始终是「上一笔下单时的价格」：阈内波动不动作，越阈反向，且反向后的新价即新基准
TEST_CASE("BackTestSpiImpl reverses direction when price moves past the trigger ratio")
{
    FakeBackTestApi fake_api;
    BackTestSpiImpl spi(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 1));

    auto anchor_tick = MakeMdTickField("000001", 10.0);
    spi.OnRtnDepthMarketData(&anchor_tick);

    auto inside_band_tick = MakeMdTickField("000001", 10.5);
    spi.OnRtnDepthMarketData(&inside_band_tick);
    CHECK(fake_api.InsertRequests.size() == 1);

    // 恰好 +10%（判据是严格大于）：边界本身不动作
    auto at_threshold_tick = MakeMdTickField("000001", 11.0);
    spi.OnRtnDepthMarketData(&at_threshold_tick);
    CHECK(fake_api.InsertRequests.size() == 1);

    auto up_past_tick = MakeMdTickField("000001", 11.1);
    spi.OnRtnDepthMarketData(&up_past_tick);
    REQUIRE(fake_api.InsertRequests.size() == 2);
    CHECK(fake_api.InsertRequests[1].Direction == DirectionType::Sell);
    CHECK(fake_api.InsertRequests[1].Price == doctest::Approx(11.1));

    auto down_inside_band_tick = MakeMdTickField("000001", 10.0);
    spi.OnRtnDepthMarketData(&down_inside_band_tick);
    CHECK(fake_api.InsertRequests.size() == 2);

    auto down_past_tick = MakeMdTickField("000001", 9.9);
    spi.OnRtnDepthMarketData(&down_past_tick);
    REQUIRE(fake_api.InsertRequests.size() == 3);
    CHECK(fake_api.InsertRequests[2].Direction == DirectionType::Buy);
}

// 不可用价既不得起基准也不得覆盖基准：DB 把 NULL 价写成 +inf 哨兵，max() 是另一处占位值；
// 0 价还会让变动比例除零。三类值都必须被跳过，且随后的真实价照常起基准
TEST_CASE("BackTestSpiImpl ignores unusable prices on tick path")
{
    FakeBackTestApi fake_api;
    BackTestSpiImpl spi(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 1));

    auto null_sentinel_tick = MakeMdTickField("000001", std::numeric_limits<double>::infinity());
    spi.OnRtnDepthMarketData(&null_sentinel_tick);
    auto max_placeholder_tick = MakeMdTickField("000001", std::numeric_limits<double>::max());
    spi.OnRtnDepthMarketData(&max_placeholder_tick);
    auto zero_tick = MakeMdTickField("000001", 0.0);
    spi.OnRtnDepthMarketData(&zero_tick);
    CHECK(fake_api.InsertRequests.empty());

    auto anchor_tick = MakeMdTickField("000001", 10.0);
    spi.OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.InsertRequests.size() == 1);
    CHECK(fake_api.InsertRequests[0].Price == doctest::Approx(10.0));

    // 基准价为 10.0 时来一帧不可用价：不得被写入基准，故下一帧 11.1 仍按 +11% 触发
    auto unusable_tick = MakeMdTickField("000001", std::numeric_limits<double>::infinity());
    spi.OnRtnDepthMarketData(&unusable_tick);
    CHECK(fake_api.InsertRequests.size() == 1);

    auto up_past_tick = MakeMdTickField("000001", 11.1);
    spi.OnRtnDepthMarketData(&up_past_tick);
    REQUIRE(fake_api.InsertRequests.size() == 2);
    CHECK(fake_api.InsertRequests[1].Direction == DirectionType::Sell);
}

// Bar 回放模式无 tick（宿主也不订阅周期聚合），以 Close 为价走同一口径
TEST_CASE("BackTestSpiImpl reverses on bar path by close price")
{
    FakeBackTestApi fake_api;
    BackTestSpiImpl spi(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 2));

    auto null_sentinel_bar = MakeMdBarField("000001", 202410010935LL, std::numeric_limits<double>::infinity());
    spi.OnRtnBarMarketData(&null_sentinel_bar);
    CHECK(fake_api.InsertRequests.empty());

    auto anchor_bar = MakeMdBarField("000001", 202410010940LL, 4000.0);
    spi.OnRtnBarMarketData(&anchor_bar);
    REQUIRE(fake_api.InsertRequests.size() == 1);
    CHECK(fake_api.InsertRequests[0].Direction == DirectionType::Buy);
    CHECK(fake_api.InsertRequests[0].Price == doctest::Approx(4000.0));
    CHECK(fake_api.InsertRequests[0].Volume == 2);

    auto up_past_bar = MakeMdBarField("000001", 202410010945LL, 4500.0);
    spi.OnRtnBarMarketData(&up_past_bar);
    REQUIRE(fake_api.InsertRequests.size() == 2);
    CHECK(fake_api.InsertRequests[1].Direction == DirectionType::Sell);
    CHECK(fake_api.InsertRequests[1].Price == doctest::Approx(4500.0));
}

// OrderTriggerRatio 是比例，越界即拒启；OrderVolume 小于 1 无意义
TEST_CASE("BackTestSpiImpl rejects out-of-range parameters at construction")
{
    FakeBackTestApi fake_api;
    REQUIRE_THROWS_AS(BackTestSpiImpl(&fake_api, MakeBackTestSpiParams(0.0, 1)), std::logic_error);
    REQUIRE_THROWS_AS(BackTestSpiImpl(&fake_api, MakeBackTestSpiParams(-0.1, 1)), std::logic_error);
    REQUIRE_THROWS_AS(BackTestSpiImpl(&fake_api, MakeBackTestSpiParams(1.0, 1)), std::logic_error);
    REQUIRE_THROWS_AS(BackTestSpiImpl(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 0)), std::logic_error);

    // 界内参数照常起跑
    BackTestSpiImpl inside_range_spi(&fake_api, MakeBackTestSpiParams(TestOrderTriggerRatio, 3));
    auto anchor_tick = MakeMdTickField("000001", 10.0);
    inside_range_spi.OnRtnDepthMarketData(&anchor_tick);
    REQUIRE(fake_api.InsertRequests.size() == 1);
    CHECK(fake_api.InsertRequests[0].Volume == 3);
}
