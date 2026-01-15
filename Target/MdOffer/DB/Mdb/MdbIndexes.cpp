#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
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
