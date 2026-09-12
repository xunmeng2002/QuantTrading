#include "BarAggregator.h"
#include "BarUtility.h"
#include "QuantUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <charconv>
#include <cstring>
#include <stdexcept>
#include <system_error>

using namespace spark::core;

namespace quanttrading::bar
{
    namespace
    {
        // 交易日（YYYYMMDD）解析：失败返回 0，由调用方回落墙钟对齐（不静默当作有效日期使用）
        int ParseTradingDay(const char* tradingDay)
        {
            if (tradingDay == nullptr || tradingDay[0] == '\0')
                return 0;
            int tradingDayValue = 0;
            const char* tradingDayEnd = tradingDay + strlen(tradingDay);
            const std::from_chars_result parseResult = std::from_chars(tradingDay, tradingDayEnd, tradingDayValue);
            if (parseResult.ec != std::errc() || parseResult.ptr != tradingDayEnd || tradingDayValue <= 0)
                return 0;
            return tradingDayValue;
        }

        long long PrecesToSeconds(BarPrecesType barPreces, int barPeriod)
        {
            switch (barPreces)
            {
                case BarPrecesType::Second:
                    return barPeriod;
                case BarPrecesType::Minute:
                    return static_cast<long long>(barPeriod) * 60;
                case BarPrecesType::Day:
                    return static_cast<long long>(barPeriod) * 86400;
                default:
                    return 0;
            }
        }
    }

    BarAggregator::BarAggregator(const TradeSessions& tradeSessions, BarPrecesType targetPreces, int targetPeriod)
        :m_TradeSessions(tradeSessions)
        ,m_TargetPreces(targetPreces)
        ,m_TargetPeriod(targetPeriod)
        ,m_BarSubscriber(nullptr)
    {
        if (!quanttrading::IsValidBarPrecesTarget(targetPreces, targetPeriod))
        {
            WriteLog(LogLevel::Error, "BarAggregator: Invalid target. BarPreces:%d, BarPeriod:%d", static_cast<int>(targetPreces), targetPeriod);
            throw std::logic_error("BarAggregator: target preces must be Minute or Day with positive period");
        }
    }

    void BarAggregator::Subscribe(BarSubscriber* barSubscriber)
    {
        m_BarSubscriber = barSubscriber;
    }

    void BarAggregator::OnBarMarketData(const BarMarketDataField* bar)
    {
        if (bar->BarPreces == m_TargetPreces && bar->BarPeriod == m_TargetPeriod)
        {
            if (m_BarSubscriber != nullptr)
                m_BarSubscriber->OnBarMarketData(const_cast<BarMarketDataField*>(bar));
            return;
        }
        if (!m_Validated)
        {
            ValidateInputBar(*bar);
            m_Validated = true;
        }
        const long long barMinute = bar->BarTime / 100000LL;
        Bucket& bucket = m_Buckets[bar->InstrumentID];
        if (bucket.HasBar && strcmp(bucket.Bar.TradingDay, bar->TradingDay) != 0)
            CloseBucket(bucket);
        if (bucket.HasBar && barMinute > bucket.EndMinute)
            CloseBucket(bucket);
        if (bucket.HasBar && barMinute <= bucket.LastMinute)
        {
            WriteLog(LogLevel::Warning, "BarAggregator: Late bar dropped. InstrumentID:%s, BarTime:%lld, BucketLastMinute:%lld",
                bar->InstrumentID, bar->BarTime, bucket.LastMinute);
            return;
        }
        if (!bucket.HasBar)
        {
            bucket.Bar = *bar;   // 整字段拷贝：Open/High/Low/HighestPrice/LowestPrice/Pre* 以首根为基线（清零后合并会丢 Low 极值）
            bucket.EndMinute = AlignBucketEndMinute(*bar, barMinute);
            bucket.HasBar = true;
        }
        else
        {
            // UpdateBarFromBar 只读 srcBar，入参 const 经 const_cast 传入
            UpdateBarFromBar(const_cast<BarMarketDataField*>(bar), &bucket.Bar);
        }
        bucket.LastMinute = barMinute;
        if (barMinute == bucket.EndMinute)
        {
            CloseBucket(bucket);
        }
    }

    void BarAggregator::Flush()
    {
        for (auto& bucketEntry : m_Buckets)
        {
            if (bucketEntry.second.HasBar)
                CloseBucket(bucketEntry.second);
        }
    }

    void BarAggregator::ValidatePrecesRelation(BarPrecesType inputPreces, int inputPeriod, BarPrecesType targetPreces, int targetPeriod, const char* instrumentID)
    {
        // 同精度同周期无需聚合（OnBarMarketData 的透传分支直发，不建桶）：
        // 装载期预校验据此放行"数据集精度与目标一致"的声明，否则日线数据集声明 1d 会被误判为跨精度聚合而拒启
        if (inputPreces == targetPreces && inputPeriod == targetPeriod)
        {
            return;
        }
        if (targetPreces == BarPrecesType::Day)
        {
            // 同精度 Day→Day 已由透传分支直发；跨精度聚合日线需要交易日历（午休/夜盘/法定假日）与日线量额结算字段，不支持
            WriteLog(LogLevel::Error, "BarAggregator: Day target only passes through same-preces bars, cross-preces aggregation is not supported. Input BarPreces:%d BarPeriod:%d, Target BarPeriod:%d, InstrumentID:%s",
                static_cast<int>(inputPreces), inputPeriod, targetPeriod, instrumentID);
            throw std::logic_error("BarAggregator: day target can not aggregate cross preces input");
        }
        if (inputPreces == BarPrecesType::Second)
        {
            WriteLog(LogLevel::Error, "BarAggregator: Second preces input can not aggregate (BarTime is minute-grained). InstrumentID:%s", instrumentID);
            throw std::logic_error("BarAggregator: second preces input can not aggregate");
        }
        if (inputPreces == BarPrecesType::Day)
        {
            // 同精度 Day→Day 已由透传分支直发；跨日再聚合需交易日历，不支持
            WriteLog(LogLevel::Error, "BarAggregator: Day preces input can not aggregate. InstrumentID:%s", instrumentID);
            throw std::logic_error("BarAggregator: day preces input can not aggregate");
        }
        const long long inputSeconds = PrecesToSeconds(inputPreces, inputPeriod);
        const long long targetSeconds = PrecesToSeconds(targetPreces, targetPeriod);
        // inputSeconds 兼作取模除数，非正即拒（周期数 <=0 的输入 bar 视为非法数据，不得触发除零）
        if (inputSeconds <= 0LL || inputSeconds > targetSeconds || targetSeconds % inputSeconds != 0)
        {
            WriteLog(LogLevel::Error, "BarAggregator: Input preces can not aggregate to target. Input BarPreces:%d BarPeriod:%d, Target BarPreces:%d BarPeriod:%d, InstrumentID:%s",
                static_cast<int>(inputPreces), inputPeriod, static_cast<int>(targetPreces), targetPeriod, instrumentID);
            throw std::logic_error("BarAggregator: input preces can not aggregate to target preces");
        }
    }

    void BarAggregator::ValidateInputBar(const BarMarketDataField& bar)
    {
        ValidatePrecesRelation(bar.BarPreces, bar.BarPeriod, m_TargetPreces, m_TargetPeriod, bar.InstrumentID);
    }

    void BarAggregator::CloseBucket(Bucket& bucket)
    {
        bucket.Bar.BarPreces = m_TargetPreces;
        bucket.Bar.BarPeriod = m_TargetPeriod;
        // 名义桶尾：断档/段末尾桶同样取名义桶尾，保证多合约跨品种时间对齐
        bucket.Bar.BarTime = bucket.EndMinute * 100000LL;
        bucket.Bar.UpdateTs = bucket.Bar.BarTime;
        if (m_BarSubscriber != nullptr)
            m_BarSubscriber->OnBarMarketData(&bucket.Bar);
        bucket.HasBar = false;
    }

    const TradeSession* BarAggregator::ResolveTradeSession(const BarMarketDataField& bar)
    {
        auto cachedIt = m_InstrumentTradeSessions.find(bar.InstrumentID);
        if (cachedIt != m_InstrumentTradeSessions.end())
            return cachedIt->second;

        const TradeSession* tradeSession = m_TradeSessions.GetTradeSessionForInstrument(bar.ExchangeID, bar.InstrumentID);
        if (tradeSession == nullptr)
        {
            WriteLog(LogLevel::Warning, "BarAggregator: Trade session not found, fall back to wall-clock alignment. ExchangeID:%s, InstrumentID:%s",
                bar.ExchangeID, bar.InstrumentID);
        }
        m_InstrumentTradeSessions[bar.InstrumentID] = tradeSession;
        return tradeSession;
    }

    long long BarAggregator::AlignBucketEndMinute(const BarMarketDataField& bar, long long barMinute)
    {
        const TradeSession* tradeSession = ResolveTradeSession(bar);
        if (tradeSession != nullptr)
        {
            const long long sectionEndMinute = AlignBucketEndMinuteByTradeSection(bar, barMinute, tradeSession);
            if (sectionEndMinute > 0LL)
                return sectionEndMinute;
        }
        return AlignBucketEndMinuteByWallClock(barMinute, m_TargetPeriod);
    }

    long long BarAggregator::AlignBucketEndMinuteByTradeSection(const BarMarketDataField& bar, long long barMinute, const TradeSession* tradeSession)
    {
        const TradeSection* tradeSection = tradeSession->GetTradeSection(static_cast<int>(barMinute % 10000LL));
        if (tradeSection != nullptr && tradeSection->SectionClass == SectionClassType::Auction)
        {
            // 集合竞价的成交由行情侧并入随后的连续竞价首根 bar（MinuteBar::CalculateBarTime 用撮合时刻改写 BarTime），
            // 故竞价段的输入 bar 一律归其后的连续竞价段；竞价段自身的分钟（如股票 09:25-09:29）会被下面的包含性校验挡下回落墙钟
            tradeSection = tradeSession->GetNextTradeSection(tradeSection);
        }
        if (tradeSection == nullptr || tradeSection->SectionClass != SectionClassType::Section)
            return 0LL;

        const int tradingDay = ParseTradingDay(bar.TradingDay);
        if (tradingDay == 0)
        {
            WriteLog(LogLevel::Warning, "BarAggregator: Invalid TradingDay, fall back to wall-clock alignment. TradingDay:%s, InstrumentID:%s",
                bar.TradingDay, bar.InstrumentID);
            return 0LL;
        }
        long long sectionBeginBarTime = 0LL;
        long long sectionEndBarTime = 0LL;
        tradeSession->GetSectionBarTime(tradeSection, tradingDay, sectionBeginBarTime, sectionEndBarTime);
        if (sectionBeginBarTime <= 0LL || sectionEndBarTime <= sectionBeginBarTime)
            return 0LL;
        const long long sectionFromMinute = TimeUtility::MinuteAdd(sectionBeginBarTime, -1);
        const long long sectionLastBarMinute = TimeUtility::MinuteAdd(sectionEndBarTime, -1);
        // 段起止由 bar.TradingDay 推出，日期化后仍不含 bar 说明数据集的 TradingDay 约定与交易节不一致（如夜盘用日历日），回落墙钟
        if (barMinute < sectionFromMinute || barMinute > sectionLastBarMinute)
            return 0LL;
        // 段内按目标周期自段首逐桶推进：断档（bar 迟到/缺失）时也能定位到正确的名义桶，段末不满一桶的尾桶按段末收口
        long long bucketEndMinute = TimeUtility::MinuteAdd(sectionBeginBarTime, m_TargetPeriod - 1);
        if (bucketEndMinute > sectionLastBarMinute)
            bucketEndMinute = sectionLastBarMinute;
        while (bucketEndMinute < barMinute)
        {
            bucketEndMinute = TimeUtility::MinuteAdd(bucketEndMinute, m_TargetPeriod);
            if (bucketEndMinute >= sectionLastBarMinute)
            {
                bucketEndMinute = sectionLastBarMinute;
                break;   // 已到段末：匹配到的段必然包含 barMinute，仅防越界时死循环
            }
        }
        return bucketEndMinute;
    }

    long long BarAggregator::AlignBucketEndMinuteByWallClock(long long barMinute, int targetPeriod)
    {
        const int hour = static_cast<int>((barMinute % 10000LL) / 100LL);
        const int minute = static_cast<int>(barMinute % 100LL);
        const long long minuteOfDay = TimeUtility::CalculateMinutes(hour, minute);
        const long long deltaMinutes = (targetPeriod - minuteOfDay % targetPeriod) % targetPeriod;
        return deltaMinutes == 0LL ? barMinute : TimeUtility::MinuteAdd(barMinute, static_cast<int>(deltaMinutes));
    }
}
