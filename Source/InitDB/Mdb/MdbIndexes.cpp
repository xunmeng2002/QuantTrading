#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
	HotInstrumentIndexTradingDay::HotInstrumentIndexTradingDay(HotInstrumentTable* table)
		:m_Table(table)
	{
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareHotInstrument);
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareHotInstrument);
	}
	std::pair<HotInstrumentIndexTradingDay::iterator, HotInstrumentIndexTradingDay::iterator> HotInstrumentIndexTradingDay::EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareHotInstrument);
	}
	void HotInstrumentIndexTradingDay::Insert(HotInstrument* const record)
	{
		m_Index.insert(record);
	}
	void HotInstrumentIndexTradingDay::Erase(HotInstrument* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void HotInstrumentIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool HotInstrumentIndexTradingDay::NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return !(HotInstrumentEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::FindNode(HotInstrument* const record)
	{
		auto p = m_Index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return m_Index.end();
	}
	void HotInstrumentIndexTradingDay::FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		Strcpy(t_CompareHotInstrument.ExchangeID, ExchangeID);
		Strcpy(t_CompareHotInstrument.ProductID, ProductID);
		t_CompareHotInstrument.Rank = Rank;
		Strcpy(t_CompareHotInstrument.TradingDay, TradingDay);
	}
	
	InstrumentIndexExchangeID::InstrumentIndexExchangeID(InstrumentTable* table)
		:m_Table(table)
	{
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::LowerBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareInstrument);
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::UpperBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareInstrument);
	}
	std::pair<InstrumentIndexExchangeID::iterator, InstrumentIndexExchangeID::iterator> InstrumentIndexExchangeID::EqualRange(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareInstrument);
	}
	void InstrumentIndexExchangeID::Insert(Instrument* const record)
	{
		m_Index.insert(record);
	}
	void InstrumentIndexExchangeID::Erase(Instrument* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void InstrumentIndexExchangeID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool InstrumentIndexExchangeID::NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return !(InstrumentEqualForExchangeIDIndex()(oldRecord, newRecord));
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::FindNode(Instrument* const record)
	{
		auto p = m_Index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return m_Index.end();
	}
	void InstrumentIndexExchangeID::FillCompareRecord(const ExchangeIDType& ExchangeID)
	{
		Strcpy(t_CompareInstrument.ExchangeID, ExchangeID);
	}
	
}
