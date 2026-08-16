#pragma once
#include <QuantTrading/Fields.h>
#include <string>

template <>
struct std::less<ReqSubMarketDataField>
{
	bool operator()(const ReqSubMarketDataField* left, const ReqSubMarketDataField* right) const;
    bool operator()(const ReqSubMarketDataField left, const ReqSubMarketDataField right) const;
};
