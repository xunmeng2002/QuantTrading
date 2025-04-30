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
		iterator LowerBound();
		iterator UpperBound();
		std::pair<iterator, iterator> EqualRange();
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);
		iterator FindNode(PrimaryAccount* const record);
		void FillCompareRecord();

	private:
		PrimaryAccountTable* m_Table;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex> m_Index;
	};



	class PositionTable;
	class PositionIndexAccount
	{
		using iterator = std::multiset<Position*, PositionLessForAccountIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexAccount(PositionTable* table);
		iterator LowerBound();
		iterator UpperBound();
		std::pair<iterator, iterator> EqualRange();
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord();

	private:
		PositionTable* m_Table;
		multiset<Position*, PositionLessForAccountIndex> m_Index;
	};




}
