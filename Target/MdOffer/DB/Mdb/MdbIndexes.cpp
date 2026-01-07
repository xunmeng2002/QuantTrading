#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
	MdUserLoginSessionIndexMdUserID::MdUserLoginSessionIndexMdUserID(MdUserLoginSessionTable* table)
		:m_Table(table)
	{
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::LowerBound(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareMdUserLoginSession);
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::UpperBound(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionIndexMdUserID::iterator, MdUserLoginSessionIndexMdUserID::iterator> MdUserLoginSessionIndexMdUserID::EqualRange(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareMdUserLoginSession);
	}
	void MdUserLoginSessionIndexMdUserID::Insert(MdUserLoginSession* const record)
	{
		m_Index.insert(record);
	}
	void MdUserLoginSessionIndexMdUserID::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void MdUserLoginSessionIndexMdUserID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool MdUserLoginSessionIndexMdUserID::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForMdUserIDIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::FindNode(MdUserLoginSession* const record)
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
	void MdUserLoginSessionIndexMdUserID::FillCompareRecord(const UserIDType& MdUserID)
	{
		Strcpy(t_CompareMdUserLoginSession.MdUserID, MdUserID);
	}
	
}
