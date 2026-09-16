#pragma once
#include <Spark/Types.h>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace QuantTrading::Bar
{
    struct TradeSection
    {
    public:
        int From;
        int To;
        SectionClassType SectionClass;
    };

    class TradeSession
    {
    public:
        std::string Name;
        std::map<std::string, std::list<std::string>> ExchangeProducts;
        std::vector<std::unique_ptr<TradeSection>> TradeSections;

    public:
        bool Check(const char* exchangeId, const char* productId) const;
        long long GetFirstBarTime(int tradingDay) const;
        const TradeSection* GetTradeSection(int time) const;
        const TradeSection* GetNextTradeSection(const TradeSection* preTradeSection) const;
        const TradeSection* GetFirstTradeSection() const;
        void GetSectionBarTime(const TradeSection* tradeSection, int tradingDay, long long& beginBarTime, long long& endBarTime) const;
        std::string ToString() const;
    };

    // 交易节集合：由各运行环境各自持有实例（行情服务持 MdOffer.json 的 SessionFile，回测引擎持 BackTest.json 的 SessionFile）。
    // 刻意不做进程级静态成员——静态库被 exe 与 dll 分别链接时，进程内会出现两份互不可见的副本，
    // 装载落在其中一份、消费读另一份，症状是静默按墙钟回退而非报错。
    // 装载完成后内容不再变化，他方缓存的裸指针（TradeSession*/TradeSection*）在整个持有期内有效。
    class TradeSessions
    {
    public:
        // 装载失败（打开失败/解析失败）返回 false 并 WriteLog；已装载时拒绝重复装载并返回 false
        bool LoadFromFile(const std::string& sessionFile);
        // 从 JSON 串装载（供不经文件的调用方与单测使用），语义与 LoadFromFile 一致
        bool ParseFromJsonString(const std::string& sessionJsonString);
        const TradeSession* GetTradeSession(const char* exchangeId, const char* productId) const;
        // 按合约查交易节：先取合约品种精确匹配，再按该交易所的 "*" 兜底；未匹配返回 nullptr
        const TradeSession* GetTradeSessionForInstrument(const char* exchangeId, const char* instrumentId) const;

    private:
        // 已装载则 WriteLog 并返回 true（调用方据此拒绝重复装载，避免他方缓存的裸指针失效）
        bool RejectIfAlreadyLoaded(const char* sessionSource) const;

        bool isLoaded_ = false;
        std::vector<std::unique_ptr<TradeSession>> tradeSessions_;
    };
}
