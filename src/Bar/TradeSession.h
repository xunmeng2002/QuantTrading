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
        bool Check(const char* exchangeId, const char* productId) const;
        long long GetFirstBarTime(int tradingDay) const;
        const TradeSection* GetTradeSection(int time) const;
        const TradeSection* GetNextTradeSection(const TradeSection* preTradeSection) const;
        const TradeSection* GetFirstTradeSection() const;
        void GetSectionBarTime(const TradeSection* tradeSection, int tradingDay, long long& beginBarTime, long long& endBarTime) const;
        std::string ToString() const;


        std::string Name;
        std::map<std::string, std::list<std::string>> ExchangeProducts;
        std::vector<std::unique_ptr<TradeSection>> TradeSections;
    };

    class TradeSessions
    {
    public:
        bool LoadFromFile(const std::string& sessionFile);
        bool ParseFromJsonString(const std::string& sessionJsonString);
        const TradeSession* GetTradeSession(const char* exchangeId, const char* productId) const;
        const TradeSession* GetTradeSessionForInstrument(const char* exchangeId, const char* instrumentId) const;

    private:
        bool RejectIfAlreadyLoaded(const char* sessionSource) const;

        bool isLoaded_ = false;
        std::vector<std::unique_ptr<TradeSession>> tradeSessions_;
    };
}
