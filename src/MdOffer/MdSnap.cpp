#include "MdSnap.h"
#include <string.h>

namespace QuantTrading::MdOffer
{
    MdSnap MdSnap::instance_;
    MdSnap& MdSnap::GetInstance()
    {
        return instance_;
    }
    RtnDepthMarketDataPackage* MdSnap::GetDepthMd(const char* exchangeId, const char* instrumentId)
    {
        auto& depthMds = exchangeDepthMds_[exchangeId];
        auto depthMdIt = depthMds.find(instrumentId);
        if (depthMdIt == depthMds.end())
        {
            return nullptr;
        }
        return depthMdIt->second;
    }
    RtnDepthMarketDataPackage* MdSnap::AddDepthMd(RtnDepthMarketDataPackage* depthMd)
    {
        auto& depthMds = exchangeDepthMds_[depthMd->DepthMarketData->ExchangeId];
        auto it = depthMds.find(depthMd->DepthMarketData->InstrumentId);
        if (it == depthMds.end())
        {
            depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume;
            depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover;
            depthMds[depthMd->DepthMarketData->InstrumentId] = depthMd;
            return depthMd;
        }
        else
        {
            auto lastDepthMd = it->second->DepthMarketData;
            // 新交易日累计量回退（或重连重放）：按新会话直接取累计值，避免产生负的增量。
            if (depthMd->DepthMarketData->Volume < lastDepthMd->Volume)
            {
                depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume;
                depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover;
            }
            else
            {
                depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume - lastDepthMd->Volume;
                depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover - lastDepthMd->Turnover;
            }
            memcpy(it->second->DepthMarketData, depthMd->DepthMarketData, sizeof(DepthMarketDataField));
            depthMd->Deallocate();
            return it->second;
        }
    }
}
