#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
	SEInstrumentIndexExchangeID::SEInstrumentIndexExchangeID(SEInstrumentTable* table)
		:m_Table(table)
	{
	}
	SEInstrumentIndexExchangeID::iterator SEInstrumentIndexExchangeID::LowerBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareSEInstrument);
	}
	SEInstrumentIndexExchangeID::iterator SEInstrumentIndexExchangeID::UpperBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareSEInstrument);
	}
	std::pair<SEInstrumentIndexExchangeID::iterator, SEInstrumentIndexExchangeID::iterator> SEInstrumentIndexExchangeID::EqualRange(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareSEInstrument);
	}
	void SEInstrumentIndexExchangeID::Insert(SEInstrument* const record)
	{
		m_Index.insert(record);
	}
	void SEInstrumentIndexExchangeID::Erase(SEInstrument* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void SEInstrumentIndexExchangeID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool SEInstrumentIndexExchangeID::NeedUpdate(const SEInstrument* const oldRecord, const SEInstrument* const newRecord)
	{
		return !(SEInstrumentEqualForExchangeIDIndex()(oldRecord, newRecord));
	}
	SEInstrumentIndexExchangeID::iterator SEInstrumentIndexExchangeID::FindNode(SEInstrument* const record)
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
	void SEInstrumentIndexExchangeID::FillCompareRecord(const ExchangeIDType& ExchangeID)
	{
		Strcpy(t_CompareSEInstrument.ExchangeID, ExchangeID);
	}
	
	SEOrderIndexAccountID::SEOrderIndexAccountID(SEOrderTable* table)
		:m_Table(table)
	{
	}
	SEOrderIndexAccountID::iterator SEOrderIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareSEOrder);
	}
	SEOrderIndexAccountID::iterator SEOrderIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareSEOrder);
	}
	std::pair<SEOrderIndexAccountID::iterator, SEOrderIndexAccountID::iterator> SEOrderIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareSEOrder);
	}
	void SEOrderIndexAccountID::Insert(SEOrder* const record)
	{
		m_Index.insert(record);
	}
	void SEOrderIndexAccountID::Erase(SEOrder* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void SEOrderIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool SEOrderIndexAccountID::NeedUpdate(const SEOrder* const oldRecord, const SEOrder* const newRecord)
	{
		return !(SEOrderEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	SEOrderIndexAccountID::iterator SEOrderIndexAccountID::FindNode(SEOrder* const record)
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
	void SEOrderIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Strcpy(t_CompareSEOrder.TradingDay, TradingDay);
		Strcpy(t_CompareSEOrder.AccountID, AccountID);
	}
	
	SETradeIndexAccountID::SETradeIndexAccountID(SETradeTable* table)
		:m_Table(table)
	{
	}
	SETradeIndexAccountID::iterator SETradeIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareSETrade);
	}
	SETradeIndexAccountID::iterator SETradeIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareSETrade);
	}
	std::pair<SETradeIndexAccountID::iterator, SETradeIndexAccountID::iterator> SETradeIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareSETrade);
	}
	void SETradeIndexAccountID::Insert(SETrade* const record)
	{
		m_Index.insert(record);
	}
	void SETradeIndexAccountID::Erase(SETrade* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void SETradeIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool SETradeIndexAccountID::NeedUpdate(const SETrade* const oldRecord, const SETrade* const newRecord)
	{
		return !(SETradeEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	SETradeIndexAccountID::iterator SETradeIndexAccountID::FindNode(SETrade* const record)
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
	void SETradeIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Strcpy(t_CompareSETrade.TradingDay, TradingDay);
		Strcpy(t_CompareSETrade.AccountID, AccountID);
	}
	
	SEBrokerLoginSessionIndexBrokerID::SEBrokerLoginSessionIndexBrokerID(SEBrokerLoginSessionTable* table)
		:m_Table(table)
	{
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::LowerBound(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareSEBrokerLoginSession);
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::UpperBound(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareSEBrokerLoginSession);
	}
	std::pair<SEBrokerLoginSessionIndexBrokerID::iterator, SEBrokerLoginSessionIndexBrokerID::iterator> SEBrokerLoginSessionIndexBrokerID::EqualRange(const BrokerIDType& BrokerID)
	{
		FillCompareRecord(BrokerID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareSEBrokerLoginSession);
	}
	void SEBrokerLoginSessionIndexBrokerID::Insert(SEBrokerLoginSession* const record)
	{
		m_Index.insert(record);
	}
	void SEBrokerLoginSessionIndexBrokerID::Erase(SEBrokerLoginSession* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void SEBrokerLoginSessionIndexBrokerID::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool SEBrokerLoginSessionIndexBrokerID::NeedUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord)
	{
		return !(SEBrokerLoginSessionEqualForBrokerIDIndex()(oldRecord, newRecord));
	}
	SEBrokerLoginSessionIndexBrokerID::iterator SEBrokerLoginSessionIndexBrokerID::FindNode(SEBrokerLoginSession* const record)
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
	void SEBrokerLoginSessionIndexBrokerID::FillCompareRecord(const BrokerIDType& BrokerID)
	{
		t_CompareSEBrokerLoginSession.BrokerID = BrokerID;
	}
	
}
