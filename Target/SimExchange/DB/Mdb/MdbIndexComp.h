#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct InstrumentEqualForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	struct InstrumentLessForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	
	struct PrimaryAccountEqualForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	struct PrimaryAccountLessForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	
	struct OrderEqualForAccountIDIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	struct OrderLessForAccountIDIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	
	struct TradeEqualForAccountIDIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	struct TradeLessForAccountIDIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	
	struct AccountLoginSessionEqualForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
}
