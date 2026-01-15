#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
	class PrimaryAccountTable;
	class PrimaryAccountIndexOfferID
	{
		using iterator = std::multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex>::iterator;
		friend class PrimaryAccountTable;
	public:
		PrimaryAccountIndexOfferID(PrimaryAccountTable* table);
		iterator LowerBound(const OfferIDType& OfferID);
		iterator UpperBound(const OfferIDType& OfferID);
		std::pair<iterator, iterator> EqualRange(const OfferIDType& OfferID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);
		iterator FindNode(PrimaryAccount* const record);
		void FillCompareRecord(const OfferIDType& OfferID);

	private:
		PrimaryAccountTable* m_Table;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex> m_Index;
	};
	
	class AccountLoginSessionTable;
	class AccountLoginSessionIndexAccountID
	{
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIDIndex>::iterator;
		friend class AccountLoginSessionTable;
	public:
		AccountLoginSessionIndexAccountID(AccountLoginSessionTable* table);
		iterator LowerBound(const AccountIDType& AccountID);
		iterator UpperBound(const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const AccountIDType& AccountID);

	private:
		AccountLoginSessionTable* m_Table;
		multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIDIndex> m_Index;
	};
	
}
