#include "BarAggregator.h"
#include "TestHelpers.h"
#include "StrategyBase.h"

#include "doctest/doctest.h"

#include <stdexcept>
#include <vector>

using namespace quanttrading::bar;
using namespace quanttrading::unittest;

TEST_SUITE("BarAggregator")
{

namespace
{
class RecordingBarSubscriber : public BarSubscriber
{
public:
    void OnBarMarketData(BarMarketDataField* bar) override
    {
        bars.push_back(*bar);
    }

    std::vector<BarMarketDataField> bars;
};

// 造 BarMarketDataField 值类型：BarTime=UpdateTs=barMinute×100000（与回放/实时聚合约定一致），
// CurrTurnover/Turnover 取量×10、OpenInterest=量，便于账目断言
BarMarketDataField MakeBarField(const char* instrument_id, const char* trading_day, long long bar_minute,
    BarPrecesType bar_preces, int bar_period, double open_price, double high_price, double low_price, double close_price,
    long long curr_volume, long long volume)
{
    BarMarketDataField bar{};
    CopyString(bar.TradingDay, trading_day);
    CopyString(bar.ExchangeID, "SSE");
    CopyString(bar.InstrumentID, instrument_id);
    bar.BarPreces = bar_preces;
    bar.BarPeriod = bar_period;
    bar.BarTime = bar_minute * 100000;
    bar.UpdateTs = bar_minute * 100000;
    bar.Open = open_price;
    bar.High = high_price;
    bar.Low = low_price;
    bar.Close = close_price;
    bar.HighestPrice = high_price;
    bar.LowestPrice = low_price;
    bar.CurrVolume = curr_volume;
    bar.Volume = volume;
    bar.CurrTurnover = static_cast<double>(curr_volume) * 10.0;
    bar.Turnover = static_cast<double>(volume) * 10.0;
    bar.OpenInterest = static_cast<double>(volume);
    return bar;
}

class BarProbeStrategy : public quanttrading::strategy::StrategyBase
{
public:
    using StrategyBase::StrategyBase;
    using StrategyBase::DeclareBarPeriod;

    void OnBar(const BarMarketDataField* bar) override
    {
        bars.push_back(*bar);
    }

    std::vector<BarMarketDataField> bars;
};
}

TEST_CASE("未声明周期时OnBar纯透传")
{
    FakeBackTestApi fake_api;
    BarProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto bar = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 5, 100.0, 101.0, 99.0, 100.5, 3, 3);
    fake_api.registered_spi->OnRtnBarMarketData(&bar);

    REQUIRE(strategy.bars.size() == 1);
    CHECK(strategy.bars[0].BarTime == 202403010935LL * 100000);
    CHECK(strategy.bars[0].BarPreces == BarPrecesType::Minute);
    CHECK(strategy.bars[0].BarPeriod == 5);
    CHECK(strategy.bars[0].Close == 100.5);
}

TEST_CASE("等周期输入直发透传不建桶")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    auto bar = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 5, 100.0, 101.0, 99.0, 100.5, 3, 3);
    aggregator.OnBarMarketData(&bar);
    aggregator.Flush();

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403010935LL * 100000);
    CHECK(subscriber.bars[0].CurrVolume == 3);
}

TEST_CASE("1m聚合为5m完整桶")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto bar1 = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    auto bar2 = MakeBarField("600000", "20240301", 202403010932LL, BarPrecesType::Minute, 1, 100.5, 102.0, 100.0, 101.5, 1, 2);
    auto bar3 = MakeBarField("600000", "20240301", 202403010933LL, BarPrecesType::Minute, 1, 101.5, 103.0, 101.0, 102.5, 1, 3);
    auto bar4 = MakeBarField("600000", "20240301", 202403010934LL, BarPrecesType::Minute, 1, 102.5, 104.0, 101.5, 103.5, 1, 4);
    auto bar5 = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 1, 103.5, 105.0, 102.0, 104.0, 1, 5);

    aggregator.OnBarMarketData(&bar1);
    aggregator.OnBarMarketData(&bar2);
    aggregator.OnBarMarketData(&bar3);
    aggregator.OnBarMarketData(&bar4);
    CHECK(subscriber.bars.empty());
    aggregator.OnBarMarketData(&bar5);

    REQUIRE(subscriber.bars.size() == 1);
    auto& aggregated = subscriber.bars[0];
    CHECK(aggregated.BarTime == 202403010935LL * 100000);
    CHECK(aggregated.UpdateTs == aggregated.BarTime);
    CHECK(aggregated.BarPreces == BarPrecesType::Minute);
    CHECK(aggregated.BarPeriod == 5);
    CHECK(aggregated.Open == 100.0);
    CHECK(aggregated.High == 105.0);
    CHECK(aggregated.Low == 99.0);
    CHECK(aggregated.HighestPrice == 105.0);
    CHECK(aggregated.LowestPrice == 99.0);
    CHECK(aggregated.Close == 104.0);
    CHECK(aggregated.CurrVolume == 5);
    CHECK(aggregated.CurrTurnover == doctest::Approx(50.0));
    CHECK(aggregated.Volume == 5);
    CHECK(aggregated.Turnover == doctest::Approx(50.0));
    CHECK(aggregated.OpenInterest == 5.0);
}

TEST_CASE("断档部分桶按名义桶尾闭合")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto bar1 = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 100.0, 100.5, 99.5, 100.2, 1, 1);
    auto bar2 = MakeBarField("600000", "20240301", 202403010932LL, BarPrecesType::Minute, 1, 100.2, 100.8, 100.0, 100.6, 1, 2);
    auto bar3 = MakeBarField("600000", "20240301", 202403010933LL, BarPrecesType::Minute, 1, 100.6, 101.0, 100.4, 100.9, 1, 3);
    auto gapBar = MakeBarField("600000", "20240301", 202403010938LL, BarPrecesType::Minute, 1, 101.0, 101.5, 100.8, 101.2, 1, 4);

    aggregator.OnBarMarketData(&bar1);
    aggregator.OnBarMarketData(&bar2);
    aggregator.OnBarMarketData(&bar3);
    aggregator.OnBarMarketData(&gapBar);

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403010935LL * 100000);
    CHECK(subscriber.bars[0].Close == 100.9);
    CHECK(subscriber.bars[0].CurrVolume == 3);
    aggregator.Flush();
    REQUIRE(subscriber.bars.size() == 2);
    CHECK(subscriber.bars[1].BarTime == 202403010940LL * 100000);
    CHECK(subscriber.bars[1].CurrVolume == 1);   // 尾桶仅 gapBar 一根：CurrVolume 是当根量 1，累计量 Volume 才是 4
}

TEST_CASE("跨日TradingDay变化重置桶")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto day1Bar1 = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 100.0, 100.5, 99.5, 100.2, 1, 1);
    auto day1Bar2 = MakeBarField("600000", "20240301", 202403010932LL, BarPrecesType::Minute, 1, 100.2, 100.8, 100.0, 100.6, 1, 2);
    auto day2Bar1 = MakeBarField("600000", "20240304", 202403040931LL, BarPrecesType::Minute, 1, 200.0, 200.5, 199.5, 200.2, 5, 10);

    aggregator.OnBarMarketData(&day1Bar1);
    aggregator.OnBarMarketData(&day1Bar2);
    aggregator.OnBarMarketData(&day2Bar1);

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403010935LL * 100000);
    CHECK(subscriber.bars[0].CurrVolume == 2);
    aggregator.Flush();
    REQUIRE(subscriber.bars.size() == 2);
    CHECK(subscriber.bars[1].BarTime == 202403040935LL * 100000);
    CHECK(std::string(subscriber.bars[1].TradingDay) == "20240304");
    CHECK(subscriber.bars[1].Open == 200.0);
    CHECK(subscriber.bars[1].CurrVolume == 5);
}

TEST_CASE("夜盘跨日同TradingDay继续同桶(MinuteAdd跨日锁定)")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto bar2356 = MakeBarField("au2506", "20240301", 202403012356LL, BarPrecesType::Minute, 1, 500.0, 501.0, 499.0, 500.5, 1, 1);
    auto bar2357 = MakeBarField("au2506", "20240301", 202403012357LL, BarPrecesType::Minute, 1, 500.5, 502.0, 500.0, 501.5, 1, 2);
    auto bar0000 = MakeBarField("au2506", "20240301", 202403020000LL, BarPrecesType::Minute, 1, 501.5, 503.0, 501.0, 502.5, 1, 3);

    aggregator.OnBarMarketData(&bar2356);
    aggregator.OnBarMarketData(&bar2357);
    aggregator.OnBarMarketData(&bar0000);

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403020000LL * 100000);
    CHECK(subscriber.bars[0].CurrVolume == 3);
}

TEST_CASE("Flush闭合未满桶")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto bar1 = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    auto bar2 = MakeBarField("600000", "20240301", 202403010932LL, BarPrecesType::Minute, 1, 100.5, 102.0, 100.0, 101.5, 1, 2);
    auto bar3 = MakeBarField("600000", "20240301", 202403010933LL, BarPrecesType::Minute, 1, 101.5, 103.0, 101.0, 102.5, 1, 3);

    aggregator.OnBarMarketData(&bar1);
    aggregator.OnBarMarketData(&bar2);
    aggregator.OnBarMarketData(&bar3);
    aggregator.Flush();

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403010935LL * 100000);
    CHECK(subscriber.bars[0].CurrVolume == 3);
}

TEST_CASE("多合约独立分桶互不串桶")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    for (long long minute = 202403010931LL; minute <= 202403010934LL; ++minute)
    {
        auto barA = MakeBarField("600000", "20240301", minute, BarPrecesType::Minute, 1, 10.0, 10.5, 9.5, 10.2, 1, 1);
        auto barB = MakeBarField("000001", "20240301", minute, BarPrecesType::Minute, 1, 20.0, 20.5, 19.5, 20.2, 2, 2);
        aggregator.OnBarMarketData(&barA);
        aggregator.OnBarMarketData(&barB);
    }
    auto barA5 = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 1, 10.2, 10.8, 10.0, 10.5, 1, 1);
    aggregator.OnBarMarketData(&barA5);

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(std::string(subscriber.bars[0].InstrumentID) == "600000");
    CHECK(subscriber.bars[0].CurrVolume == 5);
    auto barB5 = MakeBarField("000001", "20240301", 202403010935LL, BarPrecesType::Minute, 1, 20.2, 20.8, 20.0, 20.5, 2, 2);
    aggregator.OnBarMarketData(&barB5);

    REQUIRE(subscriber.bars.size() == 2);
    CHECK(std::string(subscriber.bars[1].InstrumentID) == "000001");
    CHECK(subscriber.bars[1].CurrVolume == 10);
    CHECK(subscriber.bars[1].Open == 20.0);
}

TEST_CASE("首根输入周期不合法拒启")
{
    BarAggregator fineAggregator(BarPrecesType::Minute, 5);
    auto sevenMinuteBar = MakeBarField("600000", "20240301", 202403010907LL, BarPrecesType::Minute, 7, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(fineAggregator.OnBarMarketData(&sevenMinuteBar), std::logic_error);

    BarAggregator hourAggregator(BarPrecesType::Minute, 60);
    auto dayBar = MakeBarField("600000", "20240301", 202403011500LL, BarPrecesType::Day, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(hourAggregator.OnBarMarketData(&dayBar), std::logic_error);

    BarAggregator minuteAggregator(BarPrecesType::Minute, 1);
    auto fiveMinuteBar = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 5, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(minuteAggregator.OnBarMarketData(&fiveMinuteBar), std::logic_error);
}

TEST_CASE("构造期目标非法与声明非法拒启")
{
    REQUIRE_THROWS_AS(BarAggregator(BarPrecesType::Second, 10), std::logic_error);
    REQUIRE_THROWS_AS(BarAggregator(BarPrecesType::Minute, 0), std::logic_error);

    FakeBackTestApi fake_api;
    BarProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());
    REQUIRE_THROWS_AS(strategy.DeclareBarPeriod("5x"), std::logic_error);
}

TEST_CASE("桶内迟到bar丢弃")
{
    BarAggregator aggregator(BarPrecesType::Minute, 5);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);
    auto bar1 = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    auto bar2 = MakeBarField("600000", "20240301", 202403010932LL, BarPrecesType::Minute, 1, 100.5, 102.0, 100.0, 101.5, 1, 2);
    auto lateBar = MakeBarField("600000", "20240301", 202403010931LL, BarPrecesType::Minute, 1, 999.0, 999.0, 999.0, 999.0, 9, 9);
    auto bar3 = MakeBarField("600000", "20240301", 202403010933LL, BarPrecesType::Minute, 1, 101.5, 103.0, 101.0, 102.5, 1, 3);
    auto bar4 = MakeBarField("600000", "20240301", 202403010934LL, BarPrecesType::Minute, 1, 102.5, 104.0, 101.5, 103.5, 1, 4);
    auto bar5 = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 1, 103.5, 105.0, 102.0, 104.0, 1, 5);

    aggregator.OnBarMarketData(&bar1);
    aggregator.OnBarMarketData(&bar2);
    aggregator.OnBarMarketData(&lateBar);
    CHECK(subscriber.bars.empty());
    aggregator.OnBarMarketData(&bar3);
    aggregator.OnBarMarketData(&bar4);
    aggregator.OnBarMarketData(&bar5);

    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].CurrVolume == 5);
    CHECK(subscriber.bars[0].Close == 104.0);
}

TEST_CASE("StrategyBase声明周期后OnBar收到聚合bar")
{
    FakeBackTestApi fake_api;
    BarProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());
    strategy.DeclareBarPeriod("5m");

    for (long long minute = 202403010931LL; minute <= 202403010935LL; ++minute)
    {
        auto bar = MakeBarField("600000", "20240301", minute, BarPrecesType::Minute, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
        fake_api.registered_spi->OnRtnBarMarketData(&bar);
    }
    REQUIRE(strategy.bars.size() == 1);
    CHECK(strategy.bars[0].BarPreces == BarPrecesType::Minute);
    CHECK(strategy.bars[0].BarPeriod == 5);
    CHECK(strategy.bars[0].BarTime == 202403010935LL * 100000);

    for (long long minute = 202403010936LL; minute <= 202403010937LL; ++minute)
    {
        auto bar = MakeBarField("600000", "20240301", minute, BarPrecesType::Minute, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
        fake_api.registered_spi->OnRtnBarMarketData(&bar);
    }
    MarketDataEndField market_data_end;
    fake_api.registered_spi->OnRtnMarketDataEnd(&market_data_end);

    REQUIRE(strategy.bars.size() == 2);
    CHECK(strategy.bars[1].BarTime == 202403010940LL * 100000);
    CHECK(strategy.bars[1].CurrVolume == 2);
    CHECK(fake_api.release_count == 1);
}
}
