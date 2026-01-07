#pragma once
#include <unordered_set>
#include "MdbStructs.h"
#include "MdbPrimaryKeyComp.h"

namespace mdb
{
	class DepthMarketDataTable;
	class DepthMarketDataPrimaryKey
	{
		using iterator = std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey>::iterator;
		friend class DepthMarketDataTable;
	public:
		DepthMarketDataPrimaryKey(DepthMarketDataTable* table, size_t buckets = 1000);
		DepthMarketData* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(DepthMarketData* const record);
		void Erase(DepthMarketData* const record);
		bool CheckInsert(DepthMarketData* const record);
		bool CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord);

	private:
		DepthMarketDataTable* m_Table;
		std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey> m_Index;
	};
	class BarMarketDataTable;
	class BarMarketDataPrimaryKey
	{
		using iterator = std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey>::iterator;
		friend class BarMarketDataTable;
	public:
		BarMarketDataPrimaryKey(BarMarketDataTable* table, size_t buckets = 1000);
		BarMarketData* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(BarMarketData* const record);
		void Erase(BarMarketData* const record);
		bool CheckInsert(BarMarketData* const record);
		bool CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord);

	private:
		BarMarketDataTable* m_Table;
		std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey> m_Index;
	};
}
