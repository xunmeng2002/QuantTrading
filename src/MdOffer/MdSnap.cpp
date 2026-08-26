#include "MdSnap.h"
#include <string.h>

namespace quanttrading::mdoffer
{
    MdSnap MdSnap::m_Instance;
    MdSnap::MdSnap()
    {}
    MdSnap& MdSnap::GetInstance()
    {
        return m_Instance;
    }
    RtnDepthMarketDataPackage* MdSnap::GetDepthMd(const char* exchangeID, const char* instrumentID)
    {
        auto& depthMds = m_ExchangeDepthMds[exchangeID];
        auto depthMdIt = depthMds.find(instrumentID);
        if (depthMdIt == depthMds.end())
        {
            return nullptr;
        }
        return depthMdIt->second;
    }
    RtnDepthMarketDataPackage* MdSnap::AddDepthMd(RtnDepthMarketDataPackage* depthMd)
    {
        auto& depthMds = m_ExchangeDepthMds[depthMd->DepthMarketData->ExchangeID];
        auto it = depthMds.find(depthMd->DepthMarketData->InstrumentID);
        if (it == depthMds.end())
        {
            depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume;
            depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover;
            depthMds[depthMd->DepthMarketData->InstrumentID] = depthMd;
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
