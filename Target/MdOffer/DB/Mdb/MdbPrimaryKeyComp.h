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
	struct MdSubscribeEqualForMdSubscribePrimaryKey
	{
		bool operator()(const MdSubscribe* const left, const MdSubscribe* const right) const;
	};
	struct MdSubscribeLessForMdSubscribePrimaryKey
	{
		bool operator()(const MdSubscribe* const left, const MdSubscribe* const right) const;
	};
	struct MdSubscribeHashForMdSubscribePrimaryKey
	{
		size_t operator()(const MdSubscribe* const record) const;
	};
	struct MdUserEqualForMdUserPrimaryKey
	{
		bool operator()(const MdUser* const left, const MdUser* const right) const;
	};
	struct MdUserLessForMdUserPrimaryKey
	{
		bool operator()(const MdUser* const left, const MdUser* const right) const;
	};
	struct MdUserHashForMdUserPrimaryKey
	{
		size_t operator()(const MdUser* const record) const;
	};
	struct MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForMdUserLoginSessionPrimaryKey
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey
	{
		size_t operator()(const MdUserLoginSession* const record) const;
	};
}

