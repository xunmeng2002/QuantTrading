#pragma once
#include "Packages.h"
#include <map>
#include <string>

using QuantTrading::Packages::RtnDepthMarketDataPackage;
namespace QuantTrading::MdOffer
{
    class MdSnap
    {
    public:
        static MdSnap& GetInstance();

        RtnDepthMarketDataPackage* GetDepthMd(const char* exchangeId, const char* instrumentId);
        RtnDepthMarketDataPackage* AddDepthMd(RtnDepthMarketDataPackage* depthMd);

    private:
        MdSnap() = default;
        MdSnap(const MdSnap&) = delete;
        MdSnap& operator=(const MdSnap&) = delete;

        static MdSnap instance_;
        std::map<std::string, std::map<std::string, RtnDepthMarketDataPackage*>> exchangeDepthMds_;
    };
}
