#include "BarAggregator.h"
#include "BarUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <cstring>
#include <stdexcept>

using namespace spark::core;

namespace quanttrading::bar
{
    namespace
    {
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

    BarAggregator::BarAggregator(BarPrecesType targetPreces, int targetPeriod)
        :m_TargetPreces(targetPreces)
        ,m_TargetPeriod(targetPeriod)
        ,m_BarSubscriber(nullptr)
    {
        if (targetPreces == BarPrecesType::Second || targetPeriod <= 0)
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
            bucket.EndMinute = AlignBucketEndMinute(barMinute, m_TargetPeriod);
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

    void BarAggregator::ValidateInputBar(const BarMarketDataField& bar)
    {
        if (bar.BarPreces == BarPrecesType::Second)
        {
            WriteLog(LogLevel::Error, "BarAggregator: Second preces input can not aggregate (BarTime is minute-grained). InstrumentID:%s", bar.InstrumentID);
            throw std::logic_error("BarAggregator: second preces input can not aggregate");
        }
        if (bar.BarPreces == BarPrecesType::Day)
        {
            // 同精度 Day→Day 已由透传分支直发；跨日再聚合需交易日历，不支持
            WriteLog(LogLevel::Error, "BarAggregator: Day preces input can not aggregate. InstrumentID:%s", bar.InstrumentID);
            throw std::logic_error("BarAggregator: day preces input can not aggregate");
        }
        const long long inputSeconds = PrecesToSeconds(bar.BarPreces, bar.BarPeriod);
        const long long targetSeconds = PrecesToSeconds(m_TargetPreces, m_TargetPeriod);
        if (inputSeconds > targetSeconds || (m_TargetPreces != BarPrecesType::Day && targetSeconds % inputSeconds != 0))
        {
            WriteLog(LogLevel::Error, "BarAggregator: Input preces can not aggregate to target. Input BarPreces:%d BarPeriod:%d, Target BarPreces:%d BarPeriod:%d, InstrumentID:%s",
                static_cast<int>(bar.BarPreces), bar.BarPeriod, static_cast<int>(m_TargetPreces), m_TargetPeriod, bar.InstrumentID);
            throw std::logic_error("BarAggregator: input preces can not aggregate to target preces");
        }
    }

    void BarAggregator::CloseBucket(Bucket& bucket)
    {
        bucket.Bar.BarPreces = m_TargetPreces;
        bucket.Bar.BarPeriod = m_TargetPeriod;
        if (m_TargetPreces != BarPrecesType::Day)
        {
            // 名义桶尾：断档/Flush 的部分桶同样取名义桶尾，保证多合约跨品种时间对齐
            bucket.Bar.BarTime = bucket.EndMinute * 100000LL;
            bucket.Bar.UpdateTs = bucket.Bar.BarTime;
        }
        // Day 目标保留末根输入 bar 的 BarTime/UpdateTs（日桶随 TradingDay 变化闭合，与 BaoStock 1d UpdateTs 格式待对账）
        if (m_BarSubscriber != nullptr)
            m_BarSubscriber->OnBarMarketData(&bucket.Bar);
        bucket.HasBar = false;
    }

    long long BarAggregator::AlignBucketEndMinute(long long barMinute, int period)
    {
        const long long minuteOfDay = barMinute % 10000;
        const long long delta = (period - minuteOfDay % period) % period;
        return delta == 0 ? barMinute : TimeUtility::MinuteAdd(barMinute, static_cast<int>(delta));
    }
}
