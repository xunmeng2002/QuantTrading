#pragma once
#include "MdbStructs.h"
#include <stddef.h>

namespace mdb
{
	struct DepthMarketDataEqualForDepthMarketDataPrimaryKey
	{
		bool operator()(const DepthMarketData* const left, const DepthMarketData* const right) const;
	};
	struct DepthMarketDataLessForDepthMarketDataPrimaryKey
	{
		bool operator()(const DepthMarketData* const left, const DepthMarketData* const right) const;
	};
	struct DepthMarketDataHashForDepthMarketDataPrimaryKey
	{
		size_t operator()(const DepthMarketData* const record) const;
	};
	struct BarMarketDataEqualForBarMarketDataPrimaryKey
	{
		bool operator()(const BarMarketData* const left, const BarMarketData* const right) const;
	};
	struct BarMarketDataLessForBarMarketDataPrimaryKey
	{
		bool operator()(const BarMarketData* const left, const BarMarketData* const right) const;
	};
	struct BarMarketDataHashForBarMarketDataPrimaryKey
	{
		size_t operator()(const BarMarketData* const record) const;
	};
}

