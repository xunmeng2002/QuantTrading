#include "BarUtility.h"
#include <cstring>

namespace quanttrading::bar
{
    std::string GetUnderlyingID(const std::string& instrumentID)
    {
        for (auto it = instrumentID.begin(); it < instrumentID.end(); ++it)
        {
            if (*it >= '0' && *it <= '9')
            {
                return std::string(instrumentID.begin(), it);
            }
        }
        return instrumentID;
    }

    void UpdateBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* bar)
    {
        strcpy(bar->TradingDay, depthMd->TradingDay);
        bar->UpdateTs = depthMd->UpdateTs;
        bar->PreSettlementPrice = depthMd->PreSettlementPrice;
        bar->PreClosePrice = depthMd->PreClosePrice;
        bar->HighestPrice = depthMd->HighestPrice;
        bar->LowestPrice = depthMd->LowestPrice;
        if (depthMd->CurrVolume == 0)
        {
            bar->Open = depthMd->LastPrice;
        }
        if (depthMd->LastPrice > bar->High)
            bar->High = depthMd->LastPrice;
        if (depthMd->LastPrice < bar->Low)
            bar->Low = depthMd->LastPrice;
        bar->Close = depthMd->LastPrice;

        bar->CurrVolume += depthMd->Volume - bar->Volume;
        bar->CurrTurnover += depthMd->Turnover - bar->Turnover;
        bar->Volume = depthMd->Volume;
        bar->Turnover = depthMd->Turnover;

        bar->OpenInterest = depthMd->OpenInterest;
    }
    void UpdateBarFromBar(BarMarketDataField* srcBar, BarMarketDataField* destBar)
    {
        strcpy(destBar->TradingDay, srcBar->TradingDay);
        if (srcBar->BarTime > destBar->BarTime)
        {
            destBar->BarTime = srcBar->BarTime;
            destBar->UpdateTs = srcBar->UpdateTs;
        }
        if (srcBar->HighestPrice > destBar->HighestPrice)
            destBar->HighestPrice = srcBar->HighestPrice;
        if (srcBar->LowestPrice < destBar->LowestPrice)
            destBar->LowestPrice = srcBar->LowestPrice;
        if (srcBar->High > destBar->High)
            destBar->High = srcBar->High;
        if (srcBar->Low < destBar->Low)
            destBar->Low = srcBar->Low;
        destBar->Close = srcBar->Close;

        destBar->CurrVolume += srcBar->CurrVolume;
        destBar->Volume = srcBar->Volume;
        destBar->CurrTurnover += srcBar->CurrTurnover;
        destBar->Turnover = srcBar->Turnover;

        destBar->OpenInterest = srcBar->OpenInterest;
    }
    void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar)
    {
        if (preBar == nullptr)
        {
            bar->High = bar->HighestPrice;
            bar->Low = bar->LowestPrice;
        }
        else
        {
            if (bar->HighestPrice > preBar->HighestPrice)
                bar->High = bar->HighestPrice;
            if (bar->LowestPrice < preBar->LowestPrice)
                bar->Low = bar->LowestPrice;
        }
    }
}

