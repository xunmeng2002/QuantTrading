#pragma once
#include "Packages.h"
#include <map>
#include <list>
#include <string>

std::string GetUnderlyingID(const std::string& instrumentID);

void UpdateBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* bar);
void UpdateBarFromBar(BarMarketDataField* srcBar, BarMarketDataField* destBar);
void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar);
