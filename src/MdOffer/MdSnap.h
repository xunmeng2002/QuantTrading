#pragma once
#include "Packages.h"
#include <map>
#include <string>

using quanttrading::packages::RtnDepthMarketDataPackage;
namespace quanttrading::mdoffer
{
    class MdSnap
    {
        MdSnap();
        MdSnap(const MdSnap&) = delete;
        MdSnap& operator=(const MdSnap&) = delete;
    public:
        static MdSnap& GetInstance();

        RtnDepthMarketDataPackage* GetDepthMd(const char* exchangeID, const char* instrumentID);
        RtnDepthMarketDataPackage* AddDepthMd(RtnDepthMarketDataPackage* depthMd);

    private:
        static MdSnap m_Instance;
        std::map<std::string, std::map<std::string, RtnDepthMarketDataPackage*>> m_ExchangeDepthMds;
    };
}
