#pragma once
#include "Packages.h"
#include <map>
#include <list>
#include <string>

namespace quanttrading::bar
{
    std::string GetUnderlyingID(const std::string& instrumentID);

    // BarPreces 与 Parquet Preces 列同格式（<n><s|m|h|d>，如 1m/5m/1h/1d），
    // 拆解为行情主键的精度枚举与周期数：s→Second、m→Minute、h→Minute×60、d→Day。
    bool ParseBarPreces(const std::string& barPreces, BarPrecesType& barPrecesType, int& barPeriod);

    void UpdateBarFromDepthMarketData(DepthMarketDataField* depthMd, BarMarketDataField* bar);
    void UpdateBarFromBar(BarMarketDataField* srcBar, BarMarketDataField* destBar);
    void EndBar(BarMarketDataField* preBar, BarMarketDataField* bar);
}
