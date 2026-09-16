#include "BarAggregator.h"
#include "TestHelpers.h"
#include "StrategyBase.h"

#include "doctest/doctest.h"
#include <Spark/Core/Utility/TimeUtility.h>

#include <stdexcept>
#include <string>
#include <vector>

using namespace QuantTrading::Bar;
using namespace QuantTrading::UnitTest;

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

// 与 Configs/Sessions.json 同构的最小交易节集：SSE 股票时段（9:25 集合竞价 + 上下午各一段）
const char* kStockSessionJson = R"([{"Name":"SD0930","Exchanges":[{"ExchangeId":"SSE","Products":["*"]}],
"Sections":[{"From":925,"To":930,"SectionClass":0},{"From":930,"To":1130,"SectionClass":1},{"From":1300,"To":1500,"SectionClass":1}]}])";

// SHFE 交易所级日盘("*")与 cu 夜盘并置：FD0900 在前仍不匹配具体品种，据此验证品种级时段优先于交易所级 "*"
const char* kFuturesSessionJson = R"([{"Name":"FD0900","Exchanges":[{"ExchangeId":"SHFE","Products":["*"]}],
"Sections":[{"From":855,"To":900,"SectionClass":0},{"From":900,"To":1015,"SectionClass":1},{"From":1030,"To":1130,"SectionClass":1},{"From":1330,"To":1500,"SectionClass":1}]},
{"Name":"FD0100","Exchanges":[{"ExchangeId":"SHFE","Products":["cu","al"]}],
"Sections":[{"From":2059,"To":2100,"SectionClass":0},{"From":2100,"To":100,"SectionClass":1},{"From":855,"To":900,"SectionClass":0},
{"From":900,"To":1015,"SectionClass":1},{"From":1030,"To":1130,"SectionClass":1},{"From":1330,"To":1500,"SectionClass":1}]}])";

// 每个用例独立装载交易节（"[]" 表示不装载、走墙钟回退）。交易节由本对象持有，生命周期长于用例内构造的
// 聚合器——聚合器只存引用，装载后内容不再变化，故缓存的 TradeSession* 在整个用例内有效
class AggregatorTradeSessionEnvironment
{
public:
    explicit AggregatorTradeSessionEnvironment(const char* session_json)
    {
        REQUIRE(LoadTradeSessionJson(trade_sessions_, session_json));
    }

    const TradeSessions& GetTradeSessions() const
    {
        return trade_sessions_;
    }

private:
    TradeSessions trade_sessions_;
};

// 造 BarMarketDataField 值类型：BarTime=UpdateTs=barMinute×100000（与回放/实时聚合约定一致），
// CurrTurnover/Turnover 取量×10、OpenInterest=量，便于账目断言
BarMarketDataField MakeBarField(const char* instrument_id, const char* trading_day, long long bar_minute,
    BarPrecesType bar_preces, int bar_period, double open_price, double high_price, double low_price, double close_price,
    long long curr_volume, long long volume)
{
    BarMarketDataField bar{};
    CopyString(bar.TradingDay, trading_day);
    CopyString(bar.ExchangeId, "SSE");
    CopyString(bar.InstrumentId, instrument_id);
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

// 造带交易所的 1m 输入 bar（MakeBarField 固定 SSE，交易节匹配需要真实交易所），每根当根量 1
BarMarketDataField MakeSessionBar(const char* exchange_id, const char* instrument_id, const char* trading_day, long long bar_minute)
{
    auto bar = MakeBarField(instrument_id, trading_day, bar_minute, BarPrecesType::Minute, 1, 100.0, 100.0, 100.0, 100.0, 1, 1);
    CopyString(bar.ExchangeId, exchange_id);
    return bar;
}

// 逐分钟喂入 [begin_minute, end_minute]（分钟进位与跨日由 MinuteAdd 承担）
void FeedMinuteBars(BarAggregator& aggregator, const char* exchange_id, const char* instrument_id, const char* trading_day,
    long long begin_minute, long long end_minute)
{
    for (long long bar_minute = begin_minute; bar_minute <= end_minute; bar_minute = Spark::Core::TimeUtility::MinuteAdd(bar_minute, 1))
    {
        auto bar = MakeSessionBar(exchange_id, instrument_id, trading_day, bar_minute);
        aggregator.OnBarMarketData(&bar);
    }
}

// 断言输出桶的 BarTime 序列（BarTime = 桶尾分钟 × 100000）
void CheckBarMinutes(const RecordingBarSubscriber& subscriber, const std::vector<long long>& expected_bar_minutes)
{
    REQUIRE(subscriber.bars.size() == expected_bar_minutes.size());
    for (std::size_t index = 0; index < expected_bar_minutes.size(); ++index)
    {
        CHECK(subscriber.bars[index].BarTime == expected_bar_minutes[index] * 100000LL);
    }
}

class BarProbeStrategy : public QuantTrading::strategy::StrategyBase
{
public:
    using StrategyBase::StrategyBase;
    using StrategyBase::DeclareBarPeriod;
    using StrategyBase::SubscribeBar;

    void OnBar(const BarMarketDataField* bar) override
    {
        bars.push_back(*bar);
    }

    std::vector<BarMarketDataField> bars;
};
}

TEST_CASE("未声明周期时OnBar原样透传引擎推送的bar")
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

    MarketDataEndField market_data_end{};
    fake_api.registered_spi->OnRtnMarketDataEnd(&market_data_end);
    CHECK(fake_api.release_count == 1);
}

TEST_CASE("等周期输入直发透传不建桶")
{
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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
    CHECK(std::string(subscriber.bars[0].InstrumentId) == "600000");
    CHECK(subscriber.bars[0].CurrVolume == 5);
    auto barB5 = MakeBarField("000001", "20240301", 202403010935LL, BarPrecesType::Minute, 1, 20.2, 20.8, 20.0, 20.5, 2, 2);
    aggregator.OnBarMarketData(&barB5);

    REQUIRE(subscriber.bars.size() == 2);
    CHECK(std::string(subscriber.bars[1].InstrumentId) == "000001");
    CHECK(subscriber.bars[1].CurrVolume == 10);
    CHECK(subscriber.bars[1].Open == 20.0);
}

TEST_CASE("首根输入周期不合法拒启")
{
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator fineAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
    auto sevenMinuteBar = MakeBarField("600000", "20240301", 202403010907LL, BarPrecesType::Minute, 7, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(fineAggregator.OnBarMarketData(&sevenMinuteBar), std::logic_error);

    BarAggregator hourAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    auto dayBar = MakeBarField("600000", "20240301", 202403011500LL, BarPrecesType::Day, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(hourAggregator.OnBarMarketData(&dayBar), std::logic_error);

    BarAggregator minuteAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 1);
    auto fiveMinuteBar = MakeBarField("600000", "20240301", 202403010935LL, BarPrecesType::Minute, 5, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(minuteAggregator.OnBarMarketData(&fiveMinuteBar), std::logic_error);
}

TEST_CASE("构造期目标非法与声明非法拒启")
{
    AggregatorTradeSessionEnvironment environment("[]");
    REQUIRE_THROWS_AS(BarAggregator(environment.GetTradeSessions(), BarPrecesType::Second, 10), std::logic_error);
    REQUIRE_THROWS_AS(BarAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 0), std::logic_error);

    FakeBackTestApi fake_api;
    BarProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());
    REQUIRE_THROWS_AS(strategy.DeclareBarPeriod("5x"), std::logic_error);
    REQUIRE_THROWS_AS(strategy.DeclareBarPeriod("5s"), std::logic_error);
}

TEST_CASE("桶内迟到bar丢弃")
{
    AggregatorTradeSessionEnvironment environment("[]");
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 5);
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

TEST_CASE("声明的周期随订阅请求上报引擎")
{
    FakeBackTestApi fake_api;
    BarProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    // 未声明 → BarPeriod 0，引擎按数据集精度推送
    strategy.SubscribeBar("SSE", "600000");
    REQUIRE(fake_api.subscribe_requests.size() == 1);
    CHECK(std::string(fake_api.subscribe_requests[0].ExchangeId) == "SSE");
    CHECK(std::string(fake_api.subscribe_requests[0].InstrumentId) == "600000");
    CHECK(fake_api.subscribe_requests[0].BarPeriod == 0);

    // 声明后每次订阅都带上目标周期，引擎据此为合约挂聚合器
    strategy.DeclareBarPeriod("5m");
    strategy.SubscribeBar("SSE", "000001");
    REQUIRE(fake_api.subscribe_requests.size() == 2);
    CHECK(fake_api.subscribe_requests[1].BarPreces == BarPrecesType::Minute);
    CHECK(fake_api.subscribe_requests[1].BarPeriod == 5);
    CHECK(std::string(fake_api.subscribe_requests[1].InstrumentId) == "000001");

    // 小时以上按分钟折算：60m → Minute×60
    strategy.DeclareBarPeriod("60m");
    strategy.SubscribeBar("SSE", "000002");
    REQUIRE(fake_api.subscribe_requests.size() == 3);
    CHECK(fake_api.subscribe_requests[2].BarPreces == BarPrecesType::Minute);
    CHECK(fake_api.subscribe_requests[2].BarPeriod == 60);
}

TEST_CASE("无交易节时墙钟回退的桶尾按60进制折算")
{
    AggregatorTradeSessionEnvironment environment("[]");

    // 15m：1301 起（旧实现取 1301%15=11 分钟，仅补 4 分钟，把 1305 误当桶尾）
    BarAggregator quarterAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 15);
    RecordingBarSubscriber quarterSubscriber;
    quarterAggregator.Subscribe(&quarterSubscriber);
    FeedMinuteBars(quarterAggregator, "SSE", "600000", "20240301", 202403011301LL, 202403011315LL);
    CheckBarMinutes(quarterSubscriber, { 202403011315LL });

    // 30m：1016 起（1016 折算 616 分钟，616%30=16，补 14 分钟到 1030）
    BarAggregator halfAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 30);
    RecordingBarSubscriber halfSubscriber;
    halfAggregator.Subscribe(&halfSubscriber);
    FeedMinuteBars(halfAggregator, "SSE", "600000", "20240301", 202403011016LL, 202403011030LL);
    CheckBarMinutes(halfSubscriber, { 202403011030LL });

    // 60m：0931 起（931 折算 571 分钟，571%60=31，补 29 分钟到 1000）
    BarAggregator hourAggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber hourSubscriber;
    hourAggregator.Subscribe(&hourSubscriber);
    FeedMinuteBars(hourAggregator, "SSE", "600000", "20240301", 202403010931LL, 202403011000LL);
    CheckBarMinutes(hourSubscriber, { 202403011000LL });
}

TEST_CASE("交易节锚定：SSE 60m 自9:30分段且午休不跨桶")
{
    AggregatorTradeSessionEnvironment environment(kStockSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    FeedMinuteBars(aggregator, "SSE", "600000", "20240301", 202403010931LL, 202403011130LL);
    CheckBarMinutes(subscriber, { 202403011030LL, 202403011130LL });
    CHECK(subscriber.bars[0].CurrVolume == 60);
    CHECK(subscriber.bars[1].CurrVolume == 60);

    FeedMinuteBars(aggregator, "SSE", "600000", "20240301", 202403011301LL, 202403011500LL);
    CheckBarMinutes(subscriber, { 202403011030LL, 202403011130LL, 202403011400LL, 202403011500LL });
    CHECK(subscriber.bars[2].CurrVolume == 60);
    CHECK(subscriber.bars[3].CurrVolume == 60);

    aggregator.Flush();
    CHECK(subscriber.bars.size() == 4);   // 段末满桶已闭合，无残留部分桶
}

TEST_CASE("交易节锚定：非整除周期在段末收口")
{
    AggregatorTradeSessionEnvironment environment(kStockSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 45);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    // 09:31 起：首桶 45 分钟到 10:15，次桶 10:16-11:00，段末尾桶 11:01-11:30（不足 45 分钟按段末收口）
    FeedMinuteBars(aggregator, "SSE", "600000", "20240301", 202403010931LL, 202403011130LL);
    CheckBarMinutes(subscriber, { 202403011015LL, 202403011100LL, 202403011130LL });
    CHECK(subscriber.bars[1].CurrVolume == 45);
    CHECK(subscriber.bars[2].CurrVolume == 30);
}

TEST_CASE("交易节锚定：SHFE日盘段末尾桶按段末收口")
{
    AggregatorTradeSessionEnvironment environment(kFuturesSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    // ni 未列入品种级时段，回落交易所级 "*"（FD0900，9:00 开盘）：日盘三段各自重新锚定
    FeedMinuteBars(aggregator, "SHFE", "ni2506", "20240301", 202403010901LL, 202403011015LL);
    CheckBarMinutes(subscriber, { 202403011000LL, 202403011015LL });   // 尾桶仅 10:01-10:15

    FeedMinuteBars(aggregator, "SHFE", "ni2506", "20240301", 202403011031LL, 202403011130LL);
    FeedMinuteBars(aggregator, "SHFE", "ni2506", "20240301", 202403011331LL, 202403011500LL);
    CheckBarMinutes(subscriber,
        { 202403011000LL, 202403011015LL, 202403011130LL, 202403011430LL, 202403011500LL });
    CHECK(subscriber.bars[2].CurrVolume == 60);
    CHECK(subscriber.bars[4].CurrVolume == 30);   // 14:31-15:00 为段末尾桶（时分不连续：14:59 后即 15:00）
}

TEST_CASE("交易节锚定：夜盘跨零点按会话继续分桶")
{
    AggregatorTradeSessionEnvironment environment(kFuturesSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    // cu 命中品种级时段 FD0100（夜盘 21:00-次日 01:00）：20240301 的前一交易日为 20240229，夜盘日期化时间落在 02-29
    FeedMinuteBars(aggregator, "SHFE", "cu2503", "20240301", 202402292101LL, 202402292359LL);
    CheckBarMinutes(subscriber, { 202402292200LL, 202402292300LL });

    FeedMinuteBars(aggregator, "SHFE", "cu2503", "20240301", 202403010000LL, 202403010100LL);
    CheckBarMinutes(subscriber, { 202402292200LL, 202402292300LL, 202403010000LL, 202403010100LL });
    CHECK(subscriber.bars[2].CurrVolume == 60);
    CHECK(subscriber.bars[3].CurrVolume == 60);
    CHECK(std::string(subscriber.bars[3].TradingDay) == "20240301");
}

TEST_CASE("交易节锚定：首根bar迟到仍落在段首网格上")
{
    AggregatorTradeSessionEnvironment environment(kStockSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    // 桶网格锚定段首而非首根输入 bar：10:40 迟到（10:30 桶已无输入）应落到 11:30 桶而非 11:40
    auto morningBar = MakeSessionBar("SSE", "600000", "20240301", 202403011040LL);
    aggregator.OnBarMarketData(&morningBar);
    aggregator.Flush();
    CheckBarMinutes(subscriber, { 202403011130LL });
    CHECK(subscriber.bars[0].CurrVolume == 1);

    // 14:05 迟到（14:00 桶已无输入）应落到段末桶 15:00
    auto afternoonBar = MakeSessionBar("SSE", "600000", "20240301", 202403011405LL);
    aggregator.OnBarMarketData(&afternoonBar);
    aggregator.Flush();
    CheckBarMinutes(subscriber, { 202403011130LL, 202403011500LL });
}

TEST_CASE("交易节锚定：TradingDay非法时回落墙钟对齐")
{
    AggregatorTradeSessionEnvironment environment(kStockSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Minute, 60);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    // TradingDay 为空串无法推出日期化段起止（10:01 折算 601 分钟，补 59 分钟到 11:00），按墙钟对齐而非静默用"0 日"推算
    FeedMinuteBars(aggregator, "SSE", "600000", "", 202403011001LL, 202403011100LL);
    CheckBarMinutes(subscriber, { 202403011100LL });
    CHECK(subscriber.bars[0].CurrVolume == 60);
}

TEST_CASE("装载期精度预校验：数据集精度到目标周期的可聚合矩阵")
{
    // 引擎在订阅装载期以此判据预校验（不必等首根 bar 才发现不可聚合，那时已在引擎线程内抛异常）
    BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 15, "600000");
    BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 60, "600000");
    BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 1, BarPrecesType::Minute, 5, "600000");
    BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 5, "600000");   // 同精度同周期透传
    BarAggregator::ValidatePrecesRelation(BarPrecesType::Day, 1, BarPrecesType::Day, 1, "600000");   // 同精度透传

    // 目标周期小于数据集精度：目标大周期由小周期聚合而来，反向不可行
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 1, "600000"), std::logic_error);
    // 非整除：5m 数据集无法切出 7m 桶
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 7, "600000"), std::logic_error);
    // 数据集周期数非法：不得触发除零
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 0, BarPrecesType::Minute, 5, "600000"), std::logic_error);
    // 日线目标不做跨精度聚合
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 1, BarPrecesType::Day, 1, "600000"), std::logic_error);
    // 日线/秒级数据集不可再聚合
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Day, 1, BarPrecesType::Minute, 5, "600000"), std::logic_error);
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Second, 60, BarPrecesType::Minute, 5, "600000"), std::logic_error);
    // 秒级目标本身非法（分钟粒度 BarTime 装不下）：即便数据集同为 Second，也不得借同精度分支直通构造期
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Second, 10, BarPrecesType::Second, 10, "600000"), std::logic_error);
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Second, 30, "600000"), std::logic_error);
    // 目标周期数非正一律拒（"未声明周期"由调用方在更外层过滤，不得进本判据）
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Minute, 5, BarPrecesType::Minute, 0, "600000"), std::logic_error);
    REQUIRE_THROWS_AS(BarAggregator::ValidatePrecesRelation(BarPrecesType::Day, 1, BarPrecesType::Day, 0, "600000"), std::logic_error);
}

TEST_CASE("日线目标仅同精度透传，跨精度拒启")
{
    AggregatorTradeSessionEnvironment environment(kStockSessionJson);
    BarAggregator aggregator(environment.GetTradeSessions(), BarPrecesType::Day, 1);
    RecordingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    auto fiveMinuteBar = MakeBarField("600000", "20240301", 202403011500LL, BarPrecesType::Minute, 5, 100.0, 101.0, 99.0, 100.5, 1, 1);
    REQUIRE_THROWS_AS(aggregator.OnBarMarketData(&fiveMinuteBar), std::logic_error);
    CHECK(subscriber.bars.empty());

    auto dayBar = MakeBarField("600000", "20240301", 202403011500LL, BarPrecesType::Day, 1, 100.0, 101.0, 99.0, 100.5, 1, 1);
    aggregator.OnBarMarketData(&dayBar);
    REQUIRE(subscriber.bars.size() == 1);
    CHECK(subscriber.bars[0].BarTime == 202403011500LL * 100000);   // 同精度直发，不经桶、不改时间
    CHECK(subscriber.bars[0].BarPreces == BarPrecesType::Day);
    CHECK(subscriber.bars[0].BarPeriod == 1);
}
}
