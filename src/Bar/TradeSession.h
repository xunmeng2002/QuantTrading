#pragma once
#include <Spark/Types.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>

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
        static bool ParseTradeSessions();
        static TradeSession* GetTradeSession(const char* exchangeID, const char* productID);

        static bool m_Inited;
        static std::string m_SessionJsonString;
        static std::vector<TradeSession*> m_TradeSessions;
    };
}
