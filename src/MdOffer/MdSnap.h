#pragma once
#include "Packages.h"
#include <map>
#include <string>

using QuantTrading::Packages::RtnDepthMarketDataPackage;
namespace QuantTrading::MdOffer
{
    class MdSnap
    {
        MdSnap();
        MdSnap(const MdSnap&) = delete;
        MdSnap& operator=(const MdSnap&) = delete;
    public:
        static MdSnap& GetInstance();

        RtnDepthMarketDataPackage* GetDepthMd(const char* exchangeId, const char* instrumentId);
        RtnDepthMarketDataPackage* AddDepthMd(RtnDepthMarketDataPackage* depthMd);

    private:
        static MdSnap m_Instance;
        std::map<std::string, std::map<std::string, RtnDepthMarketDataPackage*>> m_ExchangeDepthMds;
    };
}
