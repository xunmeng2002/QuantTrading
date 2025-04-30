#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{




	PrimaryAccountIndexOfferID::PrimaryAccountIndexOfferID(PrimaryAccountTable* table)
		:m_Table(table)
	{
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::LowerBound()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePrimaryAccount);
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::UpperBound()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePrimaryAccount);
	}
	std::pair<PrimaryAccountIndexOfferID::iterator, PrimaryAccountIndexOfferID::iterator> PrimaryAccountIndexOfferID::EqualRange()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePrimaryAccount);
	}
	void PrimaryAccountIndexOfferID::Insert(PrimaryAccount* const record)
	{
		m_Index.insert(record);
	}
	void PrimaryAccountIndexOfferID::Erase(PrimaryAccount* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PrimaryAccountIndexOfferID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PrimaryAccountIndexOfferID::NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return !(PrimaryAccountEqualForOfferIDIndex()(oldRecord, newRecord));
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::FindNode(PrimaryAccount* const record)
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
	void PrimaryAccountIndexOfferID::FillCompareRecord()
	{
	}



	PositionIndexAccount::PositionIndexAccount(PositionTable* table)
		:m_Table(table)
	{
	}
	PositionIndexAccount::iterator PositionIndexAccount::LowerBound()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePosition);
	}
	PositionIndexAccount::iterator PositionIndexAccount::UpperBound()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePosition);
	}
	std::pair<PositionIndexAccount::iterator, PositionIndexAccount::iterator> PositionIndexAccount::EqualRange()
	{
		FillCompareRecord();
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePosition);
	}
	void PositionIndexAccount::Insert(Position* const record)
	{
		m_Index.insert(record);
	}
	void PositionIndexAccount::Erase(Position* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PositionIndexAccount::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PositionIndexAccount::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForAccountIndex()(oldRecord, newRecord));
	}
	PositionIndexAccount::iterator PositionIndexAccount::FindNode(Position* const record)
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
	void PositionIndexAccount::FillCompareRecord()
	{
	}




}
