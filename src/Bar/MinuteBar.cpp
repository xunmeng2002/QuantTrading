#include "MinuteBar.h"
#include "BarUtility.h"
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <limits>
#include <cstring>

using namespace Spark::Core;

namespace QuantTrading::Bar
{
    MinuteBar::MinuteBar(const TradeSessions& tradeSessions)
        :tradeSessions_(tradeSessions)
        ,barSubscriber_(nullptr)
    {}
    void MinuteBar::Subscribe(BarSubscriber* barSubscriber)
    {
        barSubscriber_ = barSubscriber;
    }
    void MinuteBar::ReqSubMarketData(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId)
    {
        const TradeSession* selectedTradeSession = tradeSessions_.GetTradeSessionForInstrument(exchangeId, instrumentId);
        if (selectedTradeSession != nullptr)
        {
            instrumentTradeSessions_[instrumentId] = selectedTradeSession;
        }
    }
    void MinuteBar::OnDepthMarketData(DepthMarketDataField* depthMd)
    {
        auto tradeSession = instrumentTradeSessions_[depthMd->InstrumentId];
        if (tradeSession == nullptr)
            return;
        auto preBar = preAggregationBars_[depthMd->InstrumentId];
        if (preBar != nullptr && depthMd->UpdateTs < preBar->UpdateTs)
        {
            WriteLog(LogLevel::Warning, "MdFrontBar AggregationBar: TickUpdateTs < PreBarUpdateTs. ExchangeId:%s, InstrumentId:%s, TickUpdateTs:%lld, TickLastPrice:%f, BarUpdateTs:%lld, BarClose:%f",
                depthMd->ExchangeId, depthMd->InstrumentId, depthMd->UpdateTs, depthMd->LastPrice, preBar->UpdateTs, preBar->Close);
            return;
        }
        auto bar = aggregationBars_[depthMd->InstrumentId];

        lostBars_.clear();
        if (bar == nullptr)
        {
            bar = (BarMarketDataField*)InitMinuteBarFromDepthMarketData((DepthMarketDataField*)depthMd, (BarMarketDataField*)preBar, tradeSession);
            EndLostBars();
            aggregationBars_[depthMd->InstrumentId] = bar;
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
            aggregationBars_[depthMd->InstrumentId] = bar;
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

    void MinuteBar::CalculateBarTime(const TradeSection* tradeSection, int tickDate, long long tickMinuteTime, long long& barMinuteTime, long long& updateTsMinuteTime)
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
            barMinuteTime = TimeUtility::MinuteAdd(sectionEndTime, 1);
            updateTsMinuteTime = barMinuteTime;
        }
        else
        {
            if (tickMinuteTime == sectionEndTime)
            {
                barMinuteTime = sectionEndTime;
                updateTsMinuteTime = TimeUtility::MinuteAdd(sectionEndTime, 1);
            }
            else
            {
                barMinuteTime = TimeUtility::MinuteAdd(tickMinuteTime, 1);
                if (barMinuteTime == sectionEndTime)
                {
                    updateTsMinuteTime = TimeUtility::MinuteAdd(sectionEndTime, 1);
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
        strcpy(bar->ExchangeId, preBar->ExchangeId);
        strcpy(bar->InstrumentId, preBar->InstrumentId);
        bar->BarPreces = BarPrecesType::Minute;
        bar->BarPeriod = 1;
        bar->BarTime = barMinuteTime * 100000LL;
        bar->UpdateTs = bar->BarTime;
        bar->PreSettlementPrice = preBar->PreSettlementPrice;
        bar->PreClosePrice = preBar->PreClosePrice;
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
        strcpy(bar->ExchangeId, depthMd->ExchangeId);
        strcpy(bar->InstrumentId, depthMd->InstrumentId);
        bar->BarPreces = BarPrecesType::Minute;
        bar->BarPeriod = 1;
        bar->BarTime = barMinuteTime * 100000LL;
        bar->UpdateTs = updateTsMinuteTime * 100000LL;
        bar->PreSettlementPrice = depthMd->PreSettlementPrice;
        bar->PreClosePrice = depthMd->PreClosePrice;
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
    void MinuteBar::CheckHasLostBar(BarMarketDataField* preBar, DepthMarketDataField* depthMd, const TradeSession* tradeSession, long long nextBarMinuteTime)
    {
        auto tradingDay = atoi(depthMd->TradingDay);
        if (preBar == nullptr)
        {
            auto lostBarMinuteTime = tradeSession->GetFirstBarTime(tradingDay);
            if (lostBarMinuteTime <= 0 || lostBarMinuteTime >= nextBarMinuteTime)
                return;
            preBar = InitLostBarFromDepthMd(depthMd, lostBarMinuteTime, lostBarMinuteTime);
            lostBars_.push_back(preBar);
        }
        auto preBarMinuteTime = preBar->BarTime / 100000LL;
        auto lostBarMinuteTime = TimeUtility::MinuteAdd(preBarMinuteTime, 1);
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
            for (; lostBarMinuteTime < endBarTime; lostBarMinuteTime = TimeUtility::MinuteAdd(lostBarMinuteTime, 1))
            {
                preBar = InitLostBarFromPreBar(preBar, lostBarMinuteTime);
                lostBars_.push_back(preBar);
            }
            tradeSection = tradeSession->GetNextTradeSection(tradeSection);
            if (tradeSection == nullptr)
            {
                WriteLog(LogLevel::Warning, "MinuteBar: NextTradeSection not exist. InstrumentId:%s, TradingDay:%s", depthMd->InstrumentId, depthMd->TradingDay);
                break;
            }
            tradeSession->GetSectionBarTime(tradeSection, tradingDay, sectionBeginBarTime, sectionEndBarTime);
            endBarTime = sectionEndBarTime > nextBarMinuteTime ? nextBarMinuteTime : sectionEndBarTime;
            lostBarMinuteTime = sectionBeginBarTime;
        }
    }
    BarMarketDataField* MinuteBar::InitMinuteBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* preBar, const TradeSession* tradeSession)
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
        strcpy(bar->ExchangeId, depthMd->ExchangeId);
        strcpy(bar->InstrumentId, depthMd->InstrumentId);
        bar->BarPreces = BarPrecesType::Minute;
        bar->BarPeriod = 1;
        bar->BarTime = barMinuteTime * 100000LL;
        bar->UpdateTs = updateTsMinuteTime * 100000LL;
        bar->PreSettlementPrice = depthMd->PreSettlementPrice;
        bar->PreClosePrice = depthMd->PreClosePrice;
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
        std::lock_guard<std::mutex> guard(todayBarsMutex_);
        todayBars_[bar->InstrumentId].push_back(bar);
    }
    void MinuteBar::EndLostBars()
    {
        std::lock_guard<std::mutex> guard(todayBarsMutex_);
        for (auto lostBar : lostBars_)
        {
            todayBars_[lostBar->InstrumentId].push_back(lostBar);
            preAggregationBars_[lostBar->InstrumentId] = lostBar;
            if (barSubscriber_ != nullptr)
                barSubscriber_->OnBarMarketData(lostBar);
        }
    }
    void MinuteBar::EndBar(BarMarketDataField* preBar, BarMarketDataField* bar)
    {
        QuantTrading::Bar::EndBar((BarMarketDataField*)preBar, (BarMarketDataField*)bar);
        preAggregationBars_[bar->InstrumentId] = bar;
        aggregationBars_[bar->InstrumentId] = nullptr;

        if (barSubscriber_ != nullptr)
            barSubscriber_->OnBarMarketData(bar);
    }
}

