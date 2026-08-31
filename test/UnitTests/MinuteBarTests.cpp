#include "MinuteBar.h"
#include "TestHelpers.h"

#include "doctest/doctest.h"

#include <vector>

using namespace quanttrading::bar;
using namespace quanttrading::unittest;

TEST_SUITE("MinuteBar")
{

namespace
{
const char* kBarSessionJson = R"([
    {"Name":"DaySession","Exchanges":[{"ExchangeID":"SHFE","Products":["cu"]}],
     "Sections":[{"From":900,"To":1015,"SectionClass":1},
                 {"From":1030,"To":1130,"SectionClass":1},
                 {"From":1330,"To":1500,"SectionClass":1}]},
    {"Name":"AuctionOnly","Exchanges":[{"ExchangeID":"DCE","Products":["a"]}],
     "Sections":[{"From":850,"To":900,"SectionClass":0}]}
])";

class RecordingBarSubscriber : public BarSubscriber
{
public:
    void OnBarMarketData(BarMarketDataField* bar) override
    {
        bars.push_back(*bar);
    }

    std::vector<BarMarketDataField> bars;
};

DepthMarketDataField MakeTick(const char* instrument_id, long long update_ts, double last_price,
    double high_price, double low_price, long long volume, long long curr_volume, long long turnover)
{
    DepthMarketDataField tick{};
    CopyString(tick.TradingDay, "20240301");
    CopyString(tick.ExchangeID, "SHFE");
    CopyString(tick.InstrumentID, instrument_id);
    tick.UpdateTs = update_ts;
    tick.LastPrice = last_price;
    tick.PreClosePrice = 100.0;
    tick.PreSettlementPrice = 100.0;
    tick.HighestPrice = high_price;
    tick.LowestPrice = low_price;
    tick.Volume = volume;
    tick.CurrVolume = curr_volume;
    tick.Turnover = static_cast<double>(turnover);
    return tick;
}

// 每个用例独立装载时段与 MinuteBar，结束时清理静态时段状态
class MinuteBarEnvironment
{
public:
    MinuteBarEnvironment(const char* exchange_id, const char* instrument_id)
    {
        ResetTradeSessions();
        REQUIRE(LoadTradeSessionJson(kBarSessionJson));
        ExchangeIDType exchange_id_buffer{};
        InstrumentIDType instrument_id_buffer{};
        CopyString(exchange_id_buffer, exchange_id);
        CopyString(instrument_id_buffer, instrument_id);
        minute_bar_.Subscribe(&subscriber_);
        minute_bar_.ReqSubMarketData(exchange_id_buffer, instrument_id_buffer);
    }

    ~MinuteBarEnvironment()
    {
        ResetTradeSessions();
    }

    MinuteBar& GetMinuteBar()
    {
        return minute_bar_;
    }

    RecordingBarSubscriber& GetSubscriber()
    {
        return subscriber_;
    }

private:
    MinuteBar minute_bar_;
    RecordingBarSubscriber subscriber_;
};
}

TEST_CASE("分钟内聚合并在跨分钟时闭合")
{
    MinuteBarEnvironment environment("SHFE", "cu2503");
    auto& minute_bar = environment.GetMinuteBar();
    auto tick1 = MakeTick("cu2503", MakeUpdateTs(20240301, 90000, 500), 100.0, 100.0, 100.0, 10, 0, 1000);
    auto tick2 = MakeTick("cu2503", MakeUpdateTs(20240301, 90030, 0), 101.0, 101.0, 100.0, 15, 5, 1500);
    auto tick3 = MakeTick("cu2503", MakeUpdateTs(20240301, 90100, 200), 102.0, 102.0, 100.0, 20, 5, 2000);
    minute_bar.OnDepthMarketData(&tick1);
    minute_bar.OnDepthMarketData(&tick2);
    minute_bar.OnDepthMarketData(&tick3);

    REQUIRE(environment.GetSubscriber().bars.size() == 1);
    auto& closed_bar = environment.GetSubscriber().bars[0];
    CHECK(closed_bar.BarTime == 202403010901LL * 100000);
    CHECK(closed_bar.BarPreces == BarPrecesType::Minute);
    CHECK(closed_bar.BarPeriod == 1);
    CHECK(closed_bar.Open == 100.0);
    CHECK(closed_bar.High == 101.0);
    CHECK(closed_bar.Low == 100.0);
    CHECK(closed_bar.Close == 101.0);
    CHECK(closed_bar.CurrVolume == 15);
    CHECK(closed_bar.Volume == 15);
    CHECK(closed_bar.CurrTurnover == 1500.0);
}

TEST_CASE("仅集合竞价时段时丢失bar合成不崩溃(H19回归)")
{
    MinuteBarEnvironment environment("DCE", "a2503");
    auto& minute_bar = environment.GetMinuteBar();
    auto tick = MakeTick("a2503", MakeUpdateTs(20240301, 85000, 0), 100.0, 100.0, 100.0, 10, 0, 1000);
    minute_bar.OnDepthMarketData(&tick);

    CHECK(environment.GetSubscriber().bars.empty());
}

TEST_CASE("开盘跳档时按交易时段合成丢失bar")
{
    MinuteBarEnvironment environment("SHFE", "cu2503");
    auto& minute_bar = environment.GetMinuteBar();
    auto tick = MakeTick("cu2503", MakeUpdateTs(20240301, 143500, 500), 100.0, 100.0, 100.0, 10, 0, 1000);
    minute_bar.OnDepthMarketData(&tick);

    // 0901-1015 共 75 根 + 1031-1130 共 60 根 + 1331-1435 共 65 根 = 200 根
    REQUIRE(environment.GetSubscriber().bars.size() == 200);
    CHECK(environment.GetSubscriber().bars.front().BarTime == 202403010901LL * 100000);
    CHECK(environment.GetSubscriber().bars.back().BarTime == 202403011435LL * 100000);
}

TEST_CASE("UpdateTs早于上一根bar的tick被忽略")
{
    MinuteBarEnvironment environment("SHFE", "cu2503");
    auto& minute_bar = environment.GetMinuteBar();
    auto tick1 = MakeTick("cu2503", MakeUpdateTs(20240301, 90000, 500), 100.0, 100.0, 100.0, 10, 0, 1000);
    auto tick2 = MakeTick("cu2503", MakeUpdateTs(20240301, 90100, 200), 101.0, 101.0, 100.0, 15, 5, 1500);
    minute_bar.OnDepthMarketData(&tick1);
    minute_bar.OnDepthMarketData(&tick2);
    auto late_tick = MakeTick("cu2503", MakeUpdateTs(20240301, 90059, 900), 99.0, 101.0, 99.0, 20, 5, 2000);
    minute_bar.OnDepthMarketData(&late_tick);

    CHECK(environment.GetSubscriber().bars.size() == 1);
}
}
