#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
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
