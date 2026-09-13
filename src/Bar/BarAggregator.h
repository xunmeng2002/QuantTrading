#pragma once
#include "BarInterface.h"
#include "TradeSession.h"
#include <map>
#include <string>

namespace quanttrading::bar
{
    class BarAggregator
    {
    public:
        BarAggregator(const TradeSessions& tradeSessions, BarPrecesType targetPreces, int targetPeriod);
        void Subscribe(BarSubscriber* barSubscriber);
        void OnBarMarketData(const BarMarketDataField* bar);
        void Flush();

        static void ValidatePrecesRelation(BarPrecesType inputPreces, int inputPeriod, BarPrecesType targetPreces, int targetPeriod, const char* instrumentID);

    private:
        struct Bucket
        {
            bool HasBar = false;
            BarMarketDataField Bar{};
            long long LastMinute = 0;    // 最后合并输入 bar 的分钟（迟到/重复乱序丢弃判据，单调不减）
            long long EndMinute = 0;     // 名义桶尾分钟（YYYYMMDDHHMM）
        };

        void ValidateInputBar(const BarMarketDataField& bar);
        void CloseBucket(Bucket& bucket);
        const TradeSession* ResolveTradeSession(const BarMarketDataField& bar);
        long long AlignBucketEndMinute(const BarMarketDataField& bar, long long barMinute);
        long long AlignBucketEndMinuteByTradeSection(const BarMarketDataField& bar, long long barMinute, const TradeSession* tradeSession);
        static long long AlignBucketEndMinuteByWallClock(long long barMinute, int targetPeriod);

        const TradeSessions& m_TradeSessions;
        BarPrecesType m_TargetPreces;
        int m_TargetPeriod;
        bool m_Validated = false;
        BarSubscriber* m_BarSubscriber;
        std::map<std::string, Bucket> m_Buckets;
        std::map<std::string, const TradeSession*> m_InstrumentTradeSessions;
    };
}
