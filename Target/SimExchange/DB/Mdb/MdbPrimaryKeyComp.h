#pragma once
#include "MdbStructs.h"
#include <stddef.h>

namespace mdb
{
	struct TradingDayEqualForTradingDayPrimaryKey
	{
		bool operator()(const TradingDay* const left, const TradingDay* const right) const;
	};
	struct TradingDayLessForTradingDayPrimaryKey
	{
		bool operator()(const TradingDay* const left, const TradingDay* const right) const;
	};
	struct TradingDayHashForTradingDayPrimaryKey
	{
		size_t operator()(const TradingDay* const record) const;
	};
	struct ExchangeEqualForExchangePrimaryKey
	{
		bool operator()(const Exchange* const left, const Exchange* const right) const;
	};
	struct ExchangeLessForExchangePrimaryKey
	{
		bool operator()(const Exchange* const left, const Exchange* const right) const;
	};
	struct ExchangeHashForExchangePrimaryKey
	{
		size_t operator()(const Exchange* const record) const;
	};
	struct ProductEqualForProductPrimaryKey
	{
		bool operator()(const Product* const left, const Product* const right) const;
	};
	struct ProductLessForProductPrimaryKey
	{
		bool operator()(const Product* const left, const Product* const right) const;
	};
	struct ProductHashForProductPrimaryKey
	{
		size_t operator()(const Product* const record) const;
	};
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
	struct SEBrokerEqualForSEBrokerPrimaryKey
	{
		bool operator()(const SEBroker* const left, const SEBroker* const right) const;
	};
	struct SEBrokerLessForSEBrokerPrimaryKey
	{
		bool operator()(const SEBroker* const left, const SEBroker* const right) const;
	};
	struct SEBrokerHashForSEBrokerPrimaryKey
	{
		size_t operator()(const SEBroker* const record) const;
	};
	struct SEInstrumentEqualForSEInstrumentPrimaryKey
	{
		bool operator()(const SEInstrument* const left, const SEInstrument* const right) const;
	};
	struct SEInstrumentLessForSEInstrumentPrimaryKey
	{
		bool operator()(const SEInstrument* const left, const SEInstrument* const right) const;
	};
	struct SEInstrumentHashForSEInstrumentPrimaryKey
	{
		size_t operator()(const SEInstrument* const record) const;
	};
	struct SEOrderEqualForSEOrderPrimaryKey
	{
		bool operator()(const SEOrder* const left, const SEOrder* const right) const;
	};
	struct SEOrderLessForSEOrderPrimaryKey
	{
		bool operator()(const SEOrder* const left, const SEOrder* const right) const;
	};
	struct SEOrderHashForSEOrderPrimaryKey
	{
		size_t operator()(const SEOrder* const record) const;
	};
	struct SETradeEqualForSETradePrimaryKey
	{
		bool operator()(const SETrade* const left, const SETrade* const right) const;
	};
	struct SETradeLessForSETradePrimaryKey
	{
		bool operator()(const SETrade* const left, const SETrade* const right) const;
	};
	struct SETradeHashForSETradePrimaryKey
	{
		size_t operator()(const SETrade* const record) const;
	};
	struct SEBrokerLoginSessionEqualForSEBrokerLoginSessionPrimaryKey
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	struct SEBrokerLoginSessionLessForSEBrokerLoginSessionPrimaryKey
	{
		bool operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const;
	};
	struct SEBrokerLoginSessionHashForSEBrokerLoginSessionPrimaryKey
	{
		size_t operator()(const SEBrokerLoginSession* const record) const;
	};
}

