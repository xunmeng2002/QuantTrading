#pragma once
#include "BarInterface.h"
#include <map>
#include <string>

namespace quanttrading::bar
{
    // 策略层 bar 周期聚合器：把输入周期 bar（精度由数据集决定，如 1m/5m）聚合成策略声明的目标周期 bar。
    // 桶闭合：输入结束分钟到达名义桶尾 / 下一根输入跨过桶尾（断档部分桶闭合）/ TradingDay 变化（跨日重置）/ Flush。
    // 输出 BarTime/UpdateTs = 名义桶尾分钟 × 100000（Day 目标除外，保留末根输入 bar 时间）。
    // 线程契约：仅在引擎线程调用（同 StrategyBase），内部无锁；输入流要求单一精度（回放侧由 BarPreces 过滤保证）。
    class BarAggregator
    {
    public:
        // 目标非法（Second 精度——BarTime 为分钟粒度不可表达 / 周期数 ≤0）时 WriteLog 并抛 std::logic_error
        BarAggregator(BarPrecesType targetPreces, int targetPeriod);
        void Subscribe(BarSubscriber* barSubscriber);
        // 首根输入校验输入/目标周期关系（输入>目标、不整除、秒级、跨精度降级均拒启抛 std::logic_error），
        // 之后按合约分桶聚合，桶闭合时经 BarSubscriber 回调输出目标周期 bar
        void OnBarMarketData(const BarMarketDataField* bar);
        // 闭合全部未闭合桶（行情收尾时保证最后一根不满桶不丢）
        void Flush();

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
        static long long AlignBucketEndMinute(long long barMinute, int period);

        BarPrecesType m_TargetPreces;
        int m_TargetPeriod;
        bool m_Validated = false;
        BarSubscriber* m_BarSubscriber;
        std::map<std::string, Bucket> m_Buckets;
    };
}
