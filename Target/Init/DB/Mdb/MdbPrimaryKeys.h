#pragma once
#include <unordered_set>
#include "MdbStructs.h"
#include "MdbPrimaryKeyComp.h"

namespace mdb
{
	class TradingDayTable;
	class TradingDayPrimaryKey
	{
		using iterator = std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey>::iterator;
		friend class TradingDayTable;
	public:
		TradingDayPrimaryKey(TradingDayTable* table, size_t buckets = 1000);
		TradingDay* Select(const IntType& PK);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(TradingDay* const record);
		void Erase(TradingDay* const record);
		bool CheckInsert(TradingDay* const record);
		bool CheckUpdate(const TradingDay* const oldRecord, const TradingDay* const newRecord);

	private:
		TradingDayTable* m_Table;
		std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey> m_Index;
	};
	class ExchangeTable;
	class ExchangePrimaryKey
	{
		using iterator = std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey>::iterator;
		friend class ExchangeTable;
	public:
		ExchangePrimaryKey(ExchangeTable* table, size_t buckets = 1000);
		Exchange* Select(const ExchangeIDType& ExchangeID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Exchange* const record);
		void Erase(Exchange* const record);
		bool CheckInsert(Exchange* const record);
		bool CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord);

	private:
		ExchangeTable* m_Table;
		std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey> m_Index;
	};
	class ProductTable;
	class ProductPrimaryKey
	{
		using iterator = std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey>::iterator;
		friend class ProductTable;
	public:
		ProductPrimaryKey(ProductTable* table, size_t buckets = 1000);
		Product* Select(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Product* const record);
		void Erase(Product* const record);
		bool CheckInsert(Product* const record);
		bool CheckUpdate(const Product* const oldRecord, const Product* const newRecord);

	private:
		ProductTable* m_Table;
		std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey> m_Index;
	};
	class HotInstrumentTable;
	class HotInstrumentPrimaryKey
	{
		using iterator = std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey>::iterator;
		friend class HotInstrumentTable;
	public:
		HotInstrumentPrimaryKey(HotInstrumentTable* table, size_t buckets = 1000);
		HotInstrument* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		bool CheckInsert(HotInstrument* const record);
		bool CheckUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);

	private:
		HotInstrumentTable* m_Table;
		std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey> m_Index;
	};
	class InstrumentTable;
	class InstrumentPrimaryKey
	{
		using iterator = std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey>::iterator;
		friend class InstrumentTable;
	public:
		InstrumentPrimaryKey(InstrumentTable* table, size_t buckets = 1000);
		Instrument* Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Instrument* const record);
		void Erase(Instrument* const record);
		bool CheckInsert(Instrument* const record);
		bool CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);

	private:
		InstrumentTable* m_Table;
		std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey> m_Index;
	};
	class AccountTable;
	class AccountPrimaryKey
	{
		using iterator = std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey>::iterator;
		friend class AccountTable;
	public:
		AccountPrimaryKey(AccountTable* table, size_t buckets = 1000);
		Account* Select(const AccountIDType& AccountID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Account* const record);
		void Erase(Account* const record);
		bool CheckInsert(Account* const record);
		bool CheckUpdate(const Account* const oldRecord, const Account* const newRecord);

	private:
		AccountTable* m_Table;
		std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey> m_Index;
	};
}
