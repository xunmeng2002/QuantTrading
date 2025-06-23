#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
	SEBrokerLoginSessionIndexBrokerID::SEBrokerLoginSessionIndexBrokerID(SEBrokerLoginSessionTable* table)
		:m_Table(table)
	{
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::LowerBound(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareSEBrokerLoginSession);
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::UpperBound(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareSEBrokerLoginSession);
	}
	std::pair<SEBrokerLoginSessionIndexBrokerID::iterator, SEBrokerLoginSessionIndexBrokerID::iterator> SEBrokerLoginSessionIndexBrokerID::EqualRange(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareSEBrokerLoginSession);
	}
	void SEBrokerLoginSessionIndexBrokerID::Insert(SEBrokerLoginSession* const record)
	{
		m_Index.insert(record);
	}
	void SEBrokerLoginSessionIndexBrokerID::Erase(SEBrokerLoginSession* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void SEBrokerLoginSessionIndexBrokerID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool SEBrokerLoginSessionIndexBrokerID::NeedUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord)
	{
		return !(SEBrokerLoginSessionEqualForBrokerIDIndex()(oldRecord, newRecord));
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::FindNode(SEBrokerLoginSession* const record)
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
	void SEBrokerLoginSessionIndexBrokerID::FillCompareRecord(const BrokerIDType& BrokerID)
	{
		t_CompareSEBrokerLoginSession.BrokerID = BrokerID;
	}
	
}
