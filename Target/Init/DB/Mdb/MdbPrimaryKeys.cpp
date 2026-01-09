#include "MdbPrimaryKeys.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>

using std::unordered_set;


namespace mdb
{
	TradingDayPrimaryKey::TradingDayPrimaryKey(TradingDayTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	TradingDay* TradingDayPrimaryKey::Select(const IntType& PK)
	{
		t_CompareTradingDay.PK = PK;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareTradingDay);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<TradingDayPrimaryKey::iterator, TradingDayPrimaryKey::iterator> TradingDayPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool TradingDayPrimaryKey::Insert(TradingDay* const record)
	{
		return m_Index.insert(record).second;
	}
	void TradingDayPrimaryKey::Erase(TradingDay* const  record)
	{
		m_Index.erase(record);
	}
	bool TradingDayPrimaryKey::CheckInsert(TradingDay* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool TradingDayPrimaryKey::CheckUpdate(const TradingDay* const oldRecord, const TradingDay* const newRecord)
	{
		return TradingDayEqualForTradingDayPrimaryKey()(oldRecord, newRecord);
	}
	ExchangePrimaryKey::ExchangePrimaryKey(ExchangeTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	Exchange* ExchangePrimaryKey::Select(const ExchangeIDType& ExchangeID)
	{
		Strcpy(t_CompareExchange.ExchangeID, ExchangeID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareExchange);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ExchangePrimaryKey::iterator, ExchangePrimaryKey::iterator> ExchangePrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool ExchangePrimaryKey::Insert(Exchange* const record)
	{
		return m_Index.insert(record).second;
	}
	void ExchangePrimaryKey::Erase(Exchange* const  record)
	{
		m_Index.erase(record);
	}
	bool ExchangePrimaryKey::CheckInsert(Exchange* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool ExchangePrimaryKey::CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord)
	{
		return ExchangeEqualForExchangePrimaryKey()(oldRecord, newRecord);
	}
	ProductPrimaryKey::ProductPrimaryKey(ProductTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	Product* ProductPrimaryKey::Select(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID)
	{
		Strcpy(t_CompareProduct.ExchangeID, ExchangeID);
		Strcpy(t_CompareProduct.ProductID, ProductID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareProduct);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ProductPrimaryKey::iterator, ProductPrimaryKey::iterator> ProductPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool ProductPrimaryKey::Insert(Product* const record)
	{
		return m_Index.insert(record).second;
	}
	void ProductPrimaryKey::Erase(Product* const  record)
	{
		m_Index.erase(record);
	}
	bool ProductPrimaryKey::CheckInsert(Product* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool ProductPrimaryKey::CheckUpdate(const Product* const oldRecord, const Product* const newRecord)
	{
		return ProductEqualForProductPrimaryKey()(oldRecord, newRecord);
	}
	HotInstrumentPrimaryKey::HotInstrumentPrimaryKey(HotInstrumentTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	HotInstrument* HotInstrumentPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank)
	{
		Strcpy(t_CompareHotInstrument.TradingDay, TradingDay);
		Strcpy(t_CompareHotInstrument.ExchangeID, ExchangeID);
		Strcpy(t_CompareHotInstrument.ProductID, ProductID);
		t_CompareHotInstrument.Rank = Rank;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareHotInstrument);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<HotInstrumentPrimaryKey::iterator, HotInstrumentPrimaryKey::iterator> HotInstrumentPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool HotInstrumentPrimaryKey::Insert(HotInstrument* const record)
	{
		return m_Index.insert(record).second;
	}
	void HotInstrumentPrimaryKey::Erase(HotInstrument* const  record)
	{
		m_Index.erase(record);
	}
	bool HotInstrumentPrimaryKey::CheckInsert(HotInstrument* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool HotInstrumentPrimaryKey::CheckUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return HotInstrumentEqualForHotInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	InstrumentPrimaryKey::InstrumentPrimaryKey(InstrumentTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	Instrument* InstrumentPrimaryKey::Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Strcpy(t_CompareInstrument.ExchangeID, ExchangeID);
		Strcpy(t_CompareInstrument.InstrumentID, InstrumentID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareInstrument);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<InstrumentPrimaryKey::iterator, InstrumentPrimaryKey::iterator> InstrumentPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool InstrumentPrimaryKey::Insert(Instrument* const record)
	{
		return m_Index.insert(record).second;
	}
	void InstrumentPrimaryKey::Erase(Instrument* const  record)
	{
		m_Index.erase(record);
	}
	bool InstrumentPrimaryKey::CheckInsert(Instrument* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool InstrumentPrimaryKey::CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return InstrumentEqualForInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	AccountPrimaryKey::AccountPrimaryKey(AccountTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	Account* AccountPrimaryKey::Select(const AccountIDType& AccountID)
	{
		Strcpy(t_CompareAccount.AccountID, AccountID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareAccount);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<AccountPrimaryKey::iterator, AccountPrimaryKey::iterator> AccountPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool AccountPrimaryKey::Insert(Account* const record)
	{
		return m_Index.insert(record).second;
	}
	void AccountPrimaryKey::Erase(Account* const  record)
	{
		m_Index.erase(record);
	}
	bool AccountPrimaryKey::CheckInsert(Account* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool AccountPrimaryKey::CheckUpdate(const Account* const oldRecord, const Account* const newRecord)
	{
		return AccountEqualForAccountPrimaryKey()(oldRecord, newRecord);
	}
}
