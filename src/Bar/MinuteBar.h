#pragma once
#include "Packages.h"
#include "BarInterface.h"
#include "TradeSession.h"
#include <mutex>
#include <map>
#include <list>

class MinuteBar
{
public:
	MinuteBar();
	void Subscribe(BarSubscriber* barSubscriber);
	void ReqSubMarketData(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID);
	void OnDepthMarketData(DepthMarketDataField* depthMarketData);

private:
	void CalculateBarTime(TradeSection* tradeSection, int tickDate, long long tickMinuteTime, long long& barMinuteTime, long long& updateTsMinuteTime);

	BarMarketDataField* InitLostBarFromPreBar(BarMarketDataField* preBar, long long barMinuteTime);
	BarMarketDataField* InitLostBarFromDepthMd(DepthMarketDataField* depthMd, long long barMinuteTime, long long updateTsMinuteTime);
	void CheckHasLostBar(BarMarketDataField* preBar, DepthMarketDataField* depthMd, TradeSession* tradeSession, long long nextBarMinuteTime);
	BarMarketDataField* InitMinuteBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* preBar, TradeSession* tradeSession);

	void AddBar(BarMarketDataField* bar);
	void EndLostBars();
	void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar);

private:
	BarSubscriber* m_BarSubscriber;
	std::map<std::string, TradeSession*> m_InstrumentTradeSessions;

	std::map<std::string, BarMarketDataField*> m_AggregationBars;
	std::map<std::string, BarMarketDataField*> m_PreAggregationBars;
	std::map<std::string, std::list<BarMarketDataField*>> m_TodayBars;
	std::mutex m_TodayBarsMutex;

	std::list<BarMarketDataField*> m_LostBars;
};

