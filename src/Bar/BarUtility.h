#pragma once
#include "Packages.h"
#include <map>
#include <list>
#include <string>

namespace QuantTrading::bar
{
    std::string GetUnderlyingID(const std::string& instrumentId);

    void UpdateBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* bar);
    void UpdateBarFromBar(BarMarketDataField* srcBar, BarMarketDataField* destBar);
    void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar);
}
