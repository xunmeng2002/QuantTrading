#pragma once
#include "BarInterface.h"
#include "TradeSession.h"
#include <map>
#include <string>

namespace quanttrading::bar
{
    // 策略层 bar 周期聚合器：把输入周期 bar（精度由数据集决定，如 1m/5m）聚合成策略声明的目标周期 bar。
    // 桶边界锚定在「交易节」段首（TradeSessions，来源 Configs/Sessions.json，跟交易所与品种走）：
    // 以 GetSectionBarTime 给出的段首 bar 分钟为首桶起点、按目标周期逐桶推进（与首根输入 bar 无关，
    // 故输入 bar 迟到/缺失时桶仍落在同一网格上），段末不满一桶的尾桶按段末收口；换段即闭合（午休不跨桶）；
    // 夜盘跨零点由段起止时间的日期进位承担（GetSectionBarTime 给出上一交易日/次日的日期化时间）。
    // 查不到交易节（未装载 Sessions.json / 该合约无匹配会话 / bar 落在全部交易节之外）时回落到「午夜墙钟对齐」，
    // 并在首次无法匹配会话时告警一次，保证不静默丢 bar。
    // 输出 BarTime/UpdateTs = 桶尾分钟 × 100000。
    // 目标为日线（Day）时不做跨精度聚合：日线是交易日历概念（午休/夜盘/法定假日）而非定长分钟周期，名义桶尾无定义，
    // 且日线量额/结算字段无法由分钟 bar 等价重建。日线目标只透传数据集自身的日线精度，跨精度输入在首根校验期拒启
    // （要日线请把 BackTest.json 的 BarPreces 设为数据集日线精度，如 1d）。
    // 线程契约：仅在引擎线程调用（同 StrategyBase），内部无锁；输入流要求单一精度（回放侧由 BarPreces 过滤保证）。
    class BarAggregator
    {
    public:
        // 目标非法（Second 精度——BarTime 为分钟粒度不可表达 / 周期数 ≤0）时 WriteLog 并抛 std::logic_error
        BarAggregator(BarPrecesType targetPreces, int targetPeriod);
        void Subscribe(BarSubscriber* barSubscriber);
        // 首根输入校验输入/目标周期关系（输入>目标、不整除、秒级、日线跨精度均拒启抛 std::logic_error），
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
        // 按合约缓存交易节（首个 bar 解析一次，未匹配到则缓存 nullptr 以免逐 bar 重复查询与告警）
        TradeSession* ResolveTradeSession(const BarMarketDataField& bar);
        // 会话锚定的桶尾；无法会话锚定（无交易节 / bar 不在任何连续竞价段内）时返回 0，由调用方回落墙钟对齐
        long long AlignBucketEndMinute(const BarMarketDataField& bar, long long barMinute);
        long long AlignBucketEndMinuteByTradeSection(const BarMarketDataField& bar, long long barMinute, TradeSession* tradeSession);
        static long long AlignBucketEndMinuteByWallClock(long long barMinute, int targetPeriod);

        BarPrecesType m_TargetPreces;
        int m_TargetPeriod;
        bool m_Validated = false;
        BarSubscriber* m_BarSubscriber;
        std::map<std::string, Bucket> m_Buckets;
        // 值 nullptr = 该合约无交易节，回落墙钟对齐。缓存的裸指针指向 TradeSessions 静态区，
        // 该静态区进程内只装载一次且不卸载（TradeSessions::LoadFromFile 幂等），故缓存不设失效钩子；
        // 键仅含 InstrumentID（与 m_Buckets 一致）：同代码跨交易所属异常数据，不额外区分
        std::map<std::string, TradeSession*> m_InstrumentTradeSessions;
    };
}
