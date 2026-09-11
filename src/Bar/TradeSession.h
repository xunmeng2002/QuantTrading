#pragma once
#include <Spark/Types.h>
#include <map>
#include <list>
#include <vector>
#include <string>

namespace quanttrading::bar
{
    class TradeSection
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
        std::vector<TradeSection*> TradeSections;

    public:
        bool Check(const char* exchangeID, const char* productID);
        long long GetFirstBarTime(int tradingDay);
        TradeSection* GetTradeSection(int time);
        TradeSection* GetNextTradeSection(TradeSection* preTradeSection);
        TradeSection* GetFirstTradeSection();
        void GetSectionBarTime(TradeSection* tradeSection, int tradingDay, long long& beginBarTime, long long& endBarTime);
        const char* ToString() const;
    };

    class TradeSessions
    {
    public:
        // 从 JSON 文件装载交易节（消费方入口）；已装载则直接返回 true（幂等，重复调用不重复解析）
        static bool LoadFromFile(const std::string& sessionFile);
        static bool ParseTradeSessions();
        static TradeSession* GetTradeSession(const char* exchangeID, const char* productID);
        // 按合约查交易节：先取合约品种精确匹配，再按该交易所的 "*" 兜底；未匹配返回 nullptr
        static TradeSession* GetTradeSessionForInstrument(const char* exchangeID, const char* instrumentID);

        static bool m_Inited;
        static std::string m_SessionJsonString;
        static std::vector<TradeSession*> m_TradeSessions;
    };
}
