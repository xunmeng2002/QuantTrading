#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
	class HotInstrumentTable;
	class HotInstrumentIndexTradingDay
	{
		using iterator = std::multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex>::iterator;
		friend class HotInstrumentTable;
	public:
		HotInstrumentIndexTradingDay(HotInstrumentTable* table);
		iterator LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		iterator UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);
		iterator FindNode(HotInstrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);

	private:
		HotInstrumentTable* m_Table;
		multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex> m_Index;
	};
	
}
