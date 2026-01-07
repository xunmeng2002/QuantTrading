#include "MdbPrimaryKeys.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>

using std::unordered_set;


namespace mdb
{
	DepthMarketDataPrimaryKey::DepthMarketDataPrimaryKey(DepthMarketDataTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	DepthMarketData* DepthMarketDataPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Strcpy(t_CompareDepthMarketData.TradingDay, TradingDay);
		Strcpy(t_CompareDepthMarketData.ExchangeID, ExchangeID);
		Strcpy(t_CompareDepthMarketData.InstrumentID, InstrumentID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareDepthMarketData);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<DepthMarketDataPrimaryKey::iterator, DepthMarketDataPrimaryKey::iterator> DepthMarketDataPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool DepthMarketDataPrimaryKey::Insert(DepthMarketData* const record)
	{
		return m_Index.insert(record).second;
	}
	void DepthMarketDataPrimaryKey::Erase(DepthMarketData* const  record)
	{
		m_Index.erase(record);
	}
	bool DepthMarketDataPrimaryKey::CheckInsert(DepthMarketData* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool DepthMarketDataPrimaryKey::CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord)
	{
		return DepthMarketDataEqualForDepthMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	BarMarketDataPrimaryKey::BarMarketDataPrimaryKey(BarMarketDataTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	BarMarketData* BarMarketDataPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime)
	{
		Strcpy(t_CompareBarMarketData.TradingDay, TradingDay);
		Strcpy(t_CompareBarMarketData.ExchangeID, ExchangeID);
		Strcpy(t_CompareBarMarketData.InstrumentID, InstrumentID);
		t_CompareBarMarketData.BarPreces = BarPreces;
		t_CompareBarMarketData.BarPeriod = BarPeriod;
		t_CompareBarMarketData.BarTime = BarTime;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareBarMarketData);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<BarMarketDataPrimaryKey::iterator, BarMarketDataPrimaryKey::iterator> BarMarketDataPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool BarMarketDataPrimaryKey::Insert(BarMarketData* const record)
	{
		return m_Index.insert(record).second;
	}
	void BarMarketDataPrimaryKey::Erase(BarMarketData* const  record)
	{
		m_Index.erase(record);
	}
	bool BarMarketDataPrimaryKey::CheckInsert(BarMarketData* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool BarMarketDataPrimaryKey::CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord)
	{
		return BarMarketDataEqualForBarMarketDataPrimaryKey()(oldRecord, newRecord);
	}
}
