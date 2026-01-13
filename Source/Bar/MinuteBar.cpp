#include "MinuteBar.h"
#include "BarUtility.h"
#include "TimeUtility.h"
#include "Logger.h"
#include <limits>

MinuteBar::MinuteBar()
	:m_BarSubscriber(nullptr)
{
}
void MinuteBar::Subscribe(BarSubscriber* barSubscriber)
{
	m_BarSubscriber = barSubscriber;
}
void MinuteBar::ReqSubMarketData(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID)
{
	TradeSession* selectedTradeSession = nullptr;
	auto productID = GetUnderlyingID(instrumentID);
	selectedTradeSession = TradeSessions::GetTradeSession(exchangeID, productID.c_str());
	if (selectedTradeSession == nullptr)
	{
		selectedTradeSession = TradeSessions::GetTradeSession(exchangeID, "*");
	}
	if (selectedTradeSession != nullptr)
	{
		m_InstrumentTradeSessions[instrumentID] = selectedTradeSession;
	}
}
void MinuteBar::OnDepthMarketData(DepthMarketDataField* depthMd)
{
	auto tradeSession = m_InstrumentTradeSessions[depthMd->InstrumentID];
	if (tradeSession == nullptr)
		return;
	auto preBar = m_PreAggregationBars[depthMd->InstrumentID];
	if (preBar != nullptr && depthMd->UpdateTs < preBar->UpdateTs)
	{
		WriteLog(LogLevel::Warning, "MdFrontBar AggregationBar: TickUpdateTs < PreBarUpdateTs. ExchangeID:%s, InstrumentID:%s, TickUpdateTs:%lld, TickLastPrice:%f, BarUpdateTs:%lld, BarClose:%f",
			depthMd->ExchangeID, depthMd->InstrumentID, depthMd->UpdateTs, depthMd->LastPrice, preBar->UpdateTs, preBar->Close);
		return;
	}
	auto bar = m_AggregationBars[depthMd->InstrumentID];

	m_LostBars.clear();
	if (bar == nullptr)
	{
		bar = (BarMarketDataField*)InitMinuteBarFromDepthMarketData((DepthMarketDataField*)depthMd, (BarMarketDataField*)preBar, tradeSession);
		EndLostBars();
		m_AggregationBars[depthMd->InstrumentID] = bar;
		if (bar != nullptr)
		{
			AddBar(bar);
		}
	}
	else if (depthMd->UpdateTs >= bar->BarTime)
	{
		EndBar(preBar, bar);
		preBar = bar;
		bar = (BarMarketDataField*)InitMinuteBarFromDepthMarketData((DepthMarketDataField*)depthMd, (BarMarketDataField*)preBar, tradeSession);
		EndLostBars();
		m_AggregationBars[depthMd->InstrumentID] = bar;
		if (bar != nullptr)
		{
			AddBar(bar);
		}
	}
	else
	{
		UpdateBarFromDepthMarketData((DepthMarketDataField*)depthMd, (BarMarketDataField*)bar);
	}
}

void MinuteBar::CalculateBarTime(TradeSection* tradeSection, int tickDate, long long tickMinuteTime, long long& barMinuteTime, long long& updateTsMinuteTime)
{
	if (tradeSection == nullptr)
		return;
	long long sectionEndTime = tradeSection->To;
	if (sectionEndTime >= 2400LL)
	{
		sectionEndTime -= 2400LL;
	}
	sectionEndTime = (long long)tickDate * 10000LL + sectionEndTime;
	if (tradeSection->SectionClass == SectionClassType::Auction)
	{
		barMinuteTime = MinuteAdd(sectionEndTime, 1);
		updateTsMinuteTime = barMinuteTime;
	}
	else
	{
		if (tickMinuteTime == sectionEndTime)
		{
			barMinuteTime = sectionEndTime;
			updateTsMinuteTime = MinuteAdd(sectionEndTime, 1);
		}
		else
		{
			barMinuteTime = MinuteAdd(tickMinuteTime, 1);
			if (barMinuteTime == sectionEndTime)
			{
				updateTsMinuteTime = MinuteAdd(sectionEndTime, 1);
			}
			else
			{
				updateTsMinuteTime = barMinuteTime;
			}
		}
	}
}

BarMarketDataField* MinuteBar::InitLostBarFromPreBar(BarMarketDataField* preBar, long long barMinuteTime)
{
	auto bar = new BarMarketDataField();
	memset(bar, 0, sizeof(BarMarketDataField));

	strcpy(bar->TradingDay, preBar->TradingDay);
	strcpy(bar->ExchangeID, preBar->ExchangeID);
	strcpy(bar->InstrumentID, preBar->InstrumentID);
	bar->BarPreces = BarPrecesType::Minute;
	bar->BarPeriod = 1;
	bar->BarTime = barMinuteTime * 100000LL;
	bar->UpdateTs = bar->BarTime;
	bar->HighestPrice = preBar->HighestPrice;
	bar->LowestPrice = preBar->LowestPrice;
	bar->Open = preBar->Close;
	bar->High = preBar->Close;
	bar->Low = preBar->Close;
	bar->Close = preBar->Close;

	bar->Volume = preBar->Volume;
	bar->Turnover = preBar->Turnover;
	bar->OpenInterest = preBar->OpenInterest;
	return bar;
}
BarMarketDataField* MinuteBar::InitLostBarFromDepthMd(DepthMarketDataField* depthMd, long long barMinuteTime, long long updateTsMinuteTime)
{
	auto price = 0.0;
	if (depthMd->PreClosePrice != std::numeric_limits<double>::max())
	{
		price = depthMd->PreClosePrice;
	}
	else if (depthMd->PreSettlementPrice != std::numeric_limits<double>::max())
	{
		price = depthMd->PreSettlementPrice;
	}
	auto bar = new BarMarketDataField();
	memset(bar, 0, sizeof(BarMarketDataField));

	strcpy(bar->TradingDay, depthMd->TradingDay);
	strcpy(bar->ExchangeID, depthMd->ExchangeID);
	strcpy(bar->InstrumentID, depthMd->InstrumentID);
	bar->BarPreces = BarPrecesType::Minute;
	bar->BarPeriod = 1;
	bar->BarTime = barMinuteTime * 100000LL;
	bar->UpdateTs = updateTsMinuteTime * 100000LL;
	bar->HighestPrice = price;
	bar->LowestPrice = price;
	bar->Open = price;
	bar->High = price;
	bar->Low = price;
	bar->Close = price;

	bar->Volume = depthMd->Volume;
	bar->Turnover = depthMd->Turnover;
	bar->OpenInterest = depthMd->OpenInterest;
	return bar;
}
void MinuteBar::CheckHasLostBar(BarMarketDataField* preBar, DepthMarketDataField* depthMd, TradeSession* tradeSession, long long nextBarMinuteTime)
{
	auto tradingDay = atoi(depthMd->TradingDay);
	if (preBar == nullptr)
	{
		auto lostBarMinuteTime = tradeSession->GetFirstBarTime(tradingDay);
		if (lostBarMinuteTime >= nextBarMinuteTime)
			return;
		preBar = InitLostBarFromDepthMd(depthMd, lostBarMinuteTime, lostBarMinuteTime);
		m_LostBars.push_back(preBar);
	}
	auto preBarMinuteTime = preBar->BarTime / 100000LL;
	auto lostBarMinuteTime = MinuteAdd(preBarMinuteTime, 1);
	if (lostBarMinuteTime >= nextBarMinuteTime)
	{
		return;
	}
	auto tradeSection = tradeSession->GetTradeSection(preBarMinuteTime % 10000LL);
	if (tradeSection == nullptr) return;
	long long sectionBeginBarTime = 0LL, sectionEndBarTime = 0LL;
	tradeSession->GetSectionBarTime(tradeSection, tradingDay, sectionBeginBarTime, sectionEndBarTime);
	auto endBarTime = sectionEndBarTime > nextBarMinuteTime ? nextBarMinuteTime : sectionEndBarTime;
	while (lostBarMinuteTime < nextBarMinuteTime)
	{
		for (; lostBarMinuteTime < endBarTime; lostBarMinuteTime = MinuteAdd(lostBarMinuteTime, 1))
		{
			preBar = InitLostBarFromPreBar(preBar, lostBarMinuteTime);
			m_LostBars.push_back(preBar);
		}
		tradeSection = tradeSession->GetNextTradeSection(tradeSection);
		if (tradeSection == nullptr)
		{
			printf("NextTradeSection Not Exist\n");
			break;
		}
		tradeSession->GetSectionBarTime(tradeSection, tradingDay, sectionBeginBarTime, sectionEndBarTime);
		endBarTime = sectionEndBarTime > nextBarMinuteTime ? nextBarMinuteTime : sectionEndBarTime;
		lostBarMinuteTime = sectionBeginBarTime;
	}
}
BarMarketDataField* MinuteBar::InitMinuteBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* preBar, TradeSession* tradeSession)
{
	long long tickDate = depthMd->UpdateTs / 1000000000LL;
	long long tickMinuteTime = depthMd->UpdateTs / 100000LL;
	auto tradeSection = tradeSession->GetTradeSection(tickMinuteTime % 10000LL);
	if (tradeSection == nullptr)
		return nullptr;
	long long barMinuteTime = 0LL, updateTsMinuteTime = 0LL;
	CalculateBarTime(tradeSection, (int)tickDate, tickMinuteTime, barMinuteTime, updateTsMinuteTime);
	CheckHasLostBar(preBar, depthMd, tradeSession, barMinuteTime);

	auto bar = new BarMarketDataField();
	memset(bar, 0, sizeof(BarMarketDataField));

	strcpy(bar->TradingDay, depthMd->TradingDay);
	strcpy(bar->ExchangeID, depthMd->ExchangeID);
	strcpy(bar->InstrumentID, depthMd->InstrumentID);
	bar->BarPreces = BarPrecesType::Minute;
	bar->BarPeriod = 1;
	bar->BarTime = barMinuteTime * 100000LL;
	bar->UpdateTs = updateTsMinuteTime * 100000LL;
	bar->HighestPrice = depthMd->HighestPrice;
	bar->LowestPrice = depthMd->LowestPrice;
	bar->Open = depthMd->LastPrice;
	bar->High = depthMd->LastPrice;
	bar->Low = depthMd->LastPrice;
	bar->Close = depthMd->LastPrice;

	if (preBar == nullptr)
	{
		bar->CurrVolume = depthMd->Volume;
		bar->CurrTurnover = depthMd->Turnover;
	}
	else
	{
		bar->CurrVolume = depthMd->Volume - preBar->Volume;
		bar->CurrTurnover = depthMd->Turnover - preBar->Turnover;
	}
	bar->Volume = depthMd->Volume;
	bar->Turnover = depthMd->Turnover;

	bar->OpenInterest = depthMd->OpenInterest;
	return bar;
}

void MinuteBar::AddBar(BarMarketDataField* bar)
{
	std::lock_guard<std::mutex> guard(m_TodayBarsMutex);
	m_TodayBars[bar->InstrumentID].push_back(bar);
}
void MinuteBar::EndLostBars()
{
	std::lock_guard<std::mutex> guard(m_TodayBarsMutex);
	for (auto lostBar : m_LostBars)
	{
		m_TodayBars[lostBar->InstrumentID].push_back(lostBar);
		m_PreAggregationBars[lostBar->InstrumentID] = lostBar;
		if (m_BarSubscriber != nullptr)
			m_BarSubscriber->OnBarMarketData(lostBar);
	}
}
void MinuteBar::EndBar(BarMarketDataField* preBar, BarMarketDataField* bar)
{
	::EndBar((BarMarketDataField*)preBar, (BarMarketDataField*)bar);
	m_PreAggregationBars[bar->InstrumentID] = bar;
	m_AggregationBars[bar->InstrumentID] = nullptr;

	if (m_BarSubscriber != nullptr)
		m_BarSubscriber->OnBarMarketData(bar);
}


