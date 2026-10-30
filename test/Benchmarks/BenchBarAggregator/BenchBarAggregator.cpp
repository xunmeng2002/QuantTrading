#include "BarAggregator.h"
#include "TradeSession.h"

#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/TemplateLib/Benchmark/BenchmarkRunner.h>

#include <cstdio>

using namespace QuantTrading;
using namespace QuantTrading::Bar;
using Spark::Core::TimeUtility;
namespace Benchmark = Spark::Benchmark;

namespace
{
    class CountingBarSubscriber : public BarSubscriber
    {
    public:
        void OnBarMarketData(BarMarketDataField* /*bar*/) override
        {
            ++closedBucketCount;
        }

        std::size_t closedBucketCount = 0;
    };

    // 与单元测试同一份 SSE 交易节：集合竞价段 + 上午/下午连续竞价段
    const char* const SessionJson = R"([{"Name":"SD0930","Exchanges":[{"ExchangeId":"SSE","Products":["*"]}],
"Sections":[{"From":925,"To":930,"SectionClass":0},{"From":930,"To":1130,"SectionClass":1},{"From":1300,"To":1500,"SectionClass":1}]}])";

    constexpr int MorningBeginMinute = 931;
    constexpr int MorningEndMinute = 1130;
    constexpr int AfternoonBeginMinute = 1301;
    constexpr int AfternoonEndMinute = 1500;

    int IncrementMinuteOfDay(int hourMinute)
    {
        int hour = hourMinute / 100;
        int minute = hourMinute % 100 + 1;
        if (minute == 60)
        {
            minute = 0;
            ++hour;
        }
        return hour * 100 + minute;
    }

    // 按真实行情流推进：段内逐分钟，段间与隔日直接跳到下一段起点（休市分钟不产生输入 bar）
    class SessionMinuteCursor
    {
    public:
        int Next()
        {
            if (minuteOfDay_ > segmentEndMinute_)
            {
                if (segmentEndMinute_ == MorningEndMinute)
                {
                    minuteOfDay_ = AfternoonBeginMinute;
                    segmentEndMinute_ = AfternoonEndMinute;
                }
                else
                {
                    tradingDay_ = TimeUtility::GetNextDate(tradingDay_);
                    minuteOfDay_ = MorningBeginMinute;
                    segmentEndMinute_ = MorningEndMinute;
                }
            }
            const int minute = minuteOfDay_;
            minuteOfDay_ = IncrementMinuteOfDay(minuteOfDay_);
            return minute;
        }

        int GetTradingDay() const
        {
            return tradingDay_;
        }

    private:
        int tradingDay_ = 20240301;
        int minuteOfDay_ = MorningBeginMinute;
        int segmentEndMinute_ = MorningEndMinute;
    };

    BarMarketDataField MakeOneMinuteBar()
    {
        BarMarketDataField bar{};
        std::snprintf(bar.TradingDay, sizeof(bar.TradingDay), "%d", 20240301);
        std::snprintf(bar.ExchangeId, sizeof(bar.ExchangeId), "%s", "SSE");
        std::snprintf(bar.InstrumentId, sizeof(bar.InstrumentId), "%s", "600000");
        bar.BarPreces = BarPrecesType::Minute;
        bar.BarPeriod = 1;
        bar.Open = 100.0;
        bar.High = 100.5;
        bar.Low = 99.5;
        bar.Close = 100.2;
        bar.HighestPrice = 100.5;
        bar.LowestPrice = 99.5;
        bar.CurrVolume = 1;
        bar.Volume = 1;
        bar.CurrTurnover = 100.2;
        bar.Turnover = 100.2;
        return bar;
    }
}

int main()
{
    Benchmark::PrintHeader();

    TradeSessions tradeSessions;
    if (!tradeSessions.ParseFromJsonString(SessionJson))
    {
        std::fprintf(stderr, "cannot parse trade session fixture\n");
        return 1;
    }

    BarAggregator aggregator(tradeSessions, BarPrecesType::Minute, 5);
    CountingBarSubscriber subscriber;
    aggregator.Subscribe(&subscriber);

    BarMarketDataField inputBar = MakeOneMinuteBar();
    SessionMinuteCursor minuteCursor;
    int formattedTradingDay = 0;

    // 每根输入 bar 推进一分钟：测的是「1m 输入合并进 5m 桶」的逐根成本，
    // 桶尾闭合并交给订阅方的那一根也走同一入口，不单独拆行
    auto aggregateOneMinuteBar = [&]() -> std::size_t
    {
        const int minuteOfDay = minuteCursor.Next();
        const int tradingDay = minuteCursor.GetTradingDay();
        if (tradingDay != formattedTradingDay)
        {
            std::snprintf(inputBar.TradingDay, sizeof(inputBar.TradingDay), "%d", tradingDay);
            formattedTradingDay = tradingDay;
        }
        // 与数据口径一致：BarTime = 日期 × 10000 + HHMM，再乘 100000
        inputBar.BarTime = (static_cast<long long>(tradingDay) * 10000LL + minuteOfDay) * 100000LL;
        inputBar.UpdateTs = inputBar.BarTime;

        const std::size_t closedBucketsBefore = subscriber.closedBucketCount;
        aggregator.OnBarMarketData(&inputBar);
        return subscriber.closedBucketCount - closedBucketsBefore;
    };

    // 空转也能跑出漂亮的数字：先喂满一个 5m 桶，读不回闭合 bar 就当场失败
    for (int barIndex = 0; barIndex < 5; ++barIndex)
    {
        aggregateOneMinuteBar();
    }
    if (subscriber.closedBucketCount != 1)
    {
        std::fprintf(stderr, "expected 1 closed 5m bucket after 5 input bars, got %zu\n", subscriber.closedBucketCount);
        return 1;
    }
    subscriber.closedBucketCount = 0;

    Benchmark::Measure("BarAggregator.OnBarMarketData_1m_to_5m", aggregateOneMinuteBar);
    return 0;
}
