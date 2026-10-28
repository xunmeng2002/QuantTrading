#pragma once
#include <QuantTrading/Fields.h>
#include <string>

template <>
struct std::less<QuantTrading::ReqSubMarketDataField>
{
	bool operator()(const QuantTrading::ReqSubMarketDataField* left, const QuantTrading::ReqSubMarketDataField* right) const;
    bool operator()(const QuantTrading::ReqSubMarketDataField left, const QuantTrading::ReqSubMarketDataField right) const;
};
