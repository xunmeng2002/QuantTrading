#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
	class SEBrokerLoginSessionTable;
	class SEBrokerLoginSessionIndexBrokerID
	{
		using iterator = std::multiset<SEBrokerLoginSession*, SEBrokerLoginSessionLessForBrokerIDIndex>::iterator;
		friend class SEBrokerLoginSessionTable;
	public:
		SEBrokerLoginSessionIndexBrokerID(SEBrokerLoginSessionTable* table);
		iterator LowerBound(const BrokerIDType& BrokerID);
		iterator UpperBound(const BrokerIDType& BrokerID);
		std::pair<iterator, iterator> EqualRange(const BrokerIDType& BrokerID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(SEBrokerLoginSession* const record);
		void Erase(SEBrokerLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord);
		iterator FindNode(SEBrokerLoginSession* const record);
		void FillCompareRecord(const BrokerIDType& BrokerID);

	private:
		SEBrokerLoginSessionTable* m_Table;
		multiset<SEBrokerLoginSession*, SEBrokerLoginSessionLessForBrokerIDIndex> m_Index;
	};
	
}
