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
	
	PrimaryAccountIndexOfferID::PrimaryAccountIndexOfferID(PrimaryAccountTable* table)
		:m_Table(table)
	{
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::LowerBound(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePrimaryAccount);
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::UpperBound(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePrimaryAccount);
	}
	std::pair<PrimaryAccountIndexOfferID::iterator, PrimaryAccountIndexOfferID::iterator> PrimaryAccountIndexOfferID::EqualRange(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePrimaryAccount);
	}
	void PrimaryAccountIndexOfferID::Insert(PrimaryAccount* const record)
	{
		m_Index.insert(record);
	}
	void PrimaryAccountIndexOfferID::Erase(PrimaryAccount* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PrimaryAccountIndexOfferID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PrimaryAccountIndexOfferID::NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return !(PrimaryAccountEqualForOfferIDIndex()(oldRecord, newRecord));
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::FindNode(PrimaryAccount* const record)
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
	void PrimaryAccountIndexOfferID::FillCompareRecord(const OfferIDType& OfferID)
	{
		t_ComparePrimaryAccount.OfferID = OfferID;
	}
	
	OrderIndexAccountID::OrderIndexAccountID(OrderTable* table)
		:m_Table(table)
	{
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareOrder);
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareOrder);
	}
	std::pair<OrderIndexAccountID::iterator, OrderIndexAccountID::iterator> OrderIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareOrder);
	}
	void OrderIndexAccountID::Insert(Order* const record)
	{
		m_Index.insert(record);
	}
	void OrderIndexAccountID::Erase(Order* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void OrderIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool OrderIndexAccountID::NeedUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return !(OrderEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::FindNode(Order* const record)
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
	void OrderIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Strcpy(t_CompareOrder.TradingDay, TradingDay);
		Strcpy(t_CompareOrder.AccountID, AccountID);
	}
	
	TradeIndexAccountID::TradeIndexAccountID(TradeTable* table)
		:m_Table(table)
	{
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareTrade);
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareTrade);
	}
	std::pair<TradeIndexAccountID::iterator, TradeIndexAccountID::iterator> TradeIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareTrade);
	}
	void TradeIndexAccountID::Insert(Trade* const record)
	{
		m_Index.insert(record);
	}
	void TradeIndexAccountID::Erase(Trade* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void TradeIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool TradeIndexAccountID::NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return !(TradeEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::FindNode(Trade* const record)
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
	void TradeIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Strcpy(t_CompareTrade.TradingDay, TradingDay);
		Strcpy(t_CompareTrade.AccountID, AccountID);
	}
	
	AccountLoginSessionIndexAccountID::AccountLoginSessionIndexAccountID(AccountLoginSessionTable* table)
		:m_Table(table)
	{
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::LowerBound(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareAccountLoginSession);
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::UpperBound(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionIndexAccountID::iterator, AccountLoginSessionIndexAccountID::iterator> AccountLoginSessionIndexAccountID::EqualRange(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareAccountLoginSession);
	}
	void AccountLoginSessionIndexAccountID::Insert(AccountLoginSession* const record)
	{
		m_Index.insert(record);
	}
	void AccountLoginSessionIndexAccountID::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void AccountLoginSessionIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool AccountLoginSessionIndexAccountID::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::FindNode(AccountLoginSession* const record)
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
	void AccountLoginSessionIndexAccountID::FillCompareRecord(const AccountIDType& AccountID)
	{
		Strcpy(t_CompareAccountLoginSession.AccountID, AccountID);
	}
	
}
