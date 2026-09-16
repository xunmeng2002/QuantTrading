#pragma once
#include "Packages.h"
#include "BarInterface.h"
#include "TradeSession.h"
#include <mutex>
#include <map>
#include <list>
#include <string>

namespace QuantTrading::bar
{
    class MinuteBar
    {
    public:
        // tradeSessions 须长于本对象，且装载后不得再装载（见 TradeSessions）
        explicit MinuteBar(const TradeSessions& tradeSessions);
        void Subscribe(BarSubscriber* barSubscriber);
        void ReqSubMarketData(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId);
        void OnDepthMarketData(DepthMarketDataField* depthMarketData);

    private:
        void CalculateBarTime(const TradeSection* tradeSection, int tickDate, long long tickMinuteTime, long long& barMinuteTime, long long& updateTsMinuteTime);

        BarMarketDataField* InitLostBarFromPreBar(BarMarketDataField* preBar, long long barMinuteTime);
        BarMarketDataField* InitLostBarFromDepthMd(DepthMarketDataField* depthMd, long long barMinuteTime, long long updateTsMinuteTime);
        void CheckHasLostBar(BarMarketDataField* preBar, DepthMarketDataField* depthMd, const TradeSession* tradeSession, long long nextBarMinuteTime);
        BarMarketDataField* InitMinuteBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* preBar, const TradeSession* tradeSession);

        void AddBar(BarMarketDataField* bar);
        void EndLostBars();
        void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar);

    private:
        const TradeSessions& m_TradeSessions;
        BarSubscriber* m_BarSubscriber;
        std::map<std::string, const TradeSession*> m_InstrumentTradeSessions;

        std::map<std::string, BarMarketDataField*> m_AggregationBars;
        std::map<std::string, BarMarketDataField*> m_PreAggregationBars;
        std::map<std::string, std::list<BarMarketDataField*>> m_TodayBars;
        std::mutex m_TodayBarsMutex;

        std::list<BarMarketDataField*> m_LostBars;
    };
}
