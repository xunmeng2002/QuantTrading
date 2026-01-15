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
	
	class OrderTable;
	class OrderIndexAccountID
	{
		using iterator = std::multiset<Order*, OrderLessForAccountIDIndex>::iterator;
		friend class OrderTable;
	public:
		OrderIndexAccountID(OrderTable* table);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Order* const record);
		void Erase(Order* const record);
		void Update(iterator it);
		bool NeedUpdate(const Order* const oldRecord, const Order* const newRecord);
		iterator FindNode(Order* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		OrderTable* m_Table;
		multiset<Order*, OrderLessForAccountIDIndex> m_Index;
	};
	
	class TradeTable;
	class TradeIndexAccountID
	{
		using iterator = std::multiset<Trade*, TradeLessForAccountIDIndex>::iterator;
		friend class TradeTable;
	public:
		TradeIndexAccountID(TradeTable* table);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Trade* const record);
		void Erase(Trade* const record);
		void Update(iterator it);
		bool NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord);
		iterator FindNode(Trade* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		TradeTable* m_Table;
		multiset<Trade*, TradeLessForAccountIDIndex> m_Index;
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
