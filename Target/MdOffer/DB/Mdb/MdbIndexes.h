#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
	class InstrumentTable;
	class InstrumentIndexExchangeID
	{
		using iterator = std::multiset<Instrument*, InstrumentLessForExchangeIDIndex>::iterator;
		friend class InstrumentTable;
	public:
		InstrumentIndexExchangeID(InstrumentTable* table);
		iterator LowerBound(const ExchangeIDType& ExchangeID);
		iterator UpperBound(const ExchangeIDType& ExchangeID);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Instrument* const record);
		void Erase(Instrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);
		iterator FindNode(Instrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID);

	private:
		InstrumentTable* m_Table;
		multiset<Instrument*, InstrumentLessForExchangeIDIndex> m_Index;
	};
	
	class MdUserLoginSessionTable;
	class MdUserLoginSessionIndexMdUserID
	{
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIDIndex>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionIndexMdUserID(MdUserLoginSessionTable* table);
		iterator LowerBound(const UserIDType& MdUserID);
		iterator UpperBound(const UserIDType& MdUserID);
		std::pair<iterator, iterator> EqualRange(const UserIDType& MdUserID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const UserIDType& MdUserID);

	private:
		MdUserLoginSessionTable* m_Table;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIDIndex> m_Index;
	};
	
}
