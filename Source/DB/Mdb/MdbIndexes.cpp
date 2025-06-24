#include "MdbIndexes.h"
#include "MdbTables.h"
#include "Utility.h"
#include <string.h>


namespace mdb
{
	HotInstrumentIndexTradingDay::HotInstrumentIndexTradingDay(HotInstrumentTable* table)
		:m_Table(table)
	{
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareHotInstrument);
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareHotInstrument);
	}
	std::pair<HotInstrumentIndexTradingDay::iterator, HotInstrumentIndexTradingDay::iterator> HotInstrumentIndexTradingDay::EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareHotInstrument);
	}
	void HotInstrumentIndexTradingDay::Insert(HotInstrument* const record)
	{
		m_Index.insert(record);
	}
	void HotInstrumentIndexTradingDay::Erase(HotInstrument* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void HotInstrumentIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool HotInstrumentIndexTradingDay::NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return !(HotInstrumentEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::FindNode(HotInstrument* const record)
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
	void HotInstrumentIndexTradingDay::FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		Strcpy(t_CompareHotInstrument.ExchangeID, ExchangeID);
		Strcpy(t_CompareHotInstrument.ProductID, ProductID);
		t_CompareHotInstrument.Rank = Rank;
		Strcpy(t_CompareHotInstrument.TradingDay, TradingDay);
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
	
	CapitalIndexTradingDay::CapitalIndexTradingDay(CapitalTable* table)
		:m_Table(table)
	{
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_CompareCapital);
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_CompareCapital);
	}
	std::pair<CapitalIndexTradingDay::iterator, CapitalIndexTradingDay::iterator> CapitalIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_CompareCapital);
	}
	void CapitalIndexTradingDay::Insert(Capital* const record)
	{
		m_Index.insert(record);
	}
	void CapitalIndexTradingDay::Erase(Capital* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void CapitalIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool CapitalIndexTradingDay::NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return !(CapitalEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::FindNode(Capital* const record)
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
	void CapitalIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Strcpy(t_CompareCapital.TradingDay, TradingDay);
	}
	
	PositionIndexAccount::PositionIndexAccount(PositionTable* table)
		:m_Table(table)
	{
	}
	PositionIndexAccount::iterator PositionIndexAccount::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePosition);
	}
	PositionIndexAccount::iterator PositionIndexAccount::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePosition);
	}
	std::pair<PositionIndexAccount::iterator, PositionIndexAccount::iterator> PositionIndexAccount::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePosition);
	}
	void PositionIndexAccount::Insert(Position* const record)
	{
		m_Index.insert(record);
	}
	void PositionIndexAccount::Erase(Position* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PositionIndexAccount::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PositionIndexAccount::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForAccountIndex()(oldRecord, newRecord));
	}
	PositionIndexAccount::iterator PositionIndexAccount::FindNode(Position* const record)
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
	void PositionIndexAccount::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Strcpy(t_ComparePosition.TradingDay, TradingDay);
		Strcpy(t_ComparePosition.AccountID, AccountID);
	}
	
	PositionIndexTradingDay::PositionIndexTradingDay(PositionTable* table)
		:m_Table(table)
	{
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePosition);
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePosition);
	}
	std::pair<PositionIndexTradingDay::iterator, PositionIndexTradingDay::iterator> PositionIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePosition);
	}
	void PositionIndexTradingDay::Insert(Position* const record)
	{
		m_Index.insert(record);
	}
	void PositionIndexTradingDay::Erase(Position* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PositionIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PositionIndexTradingDay::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::FindNode(Position* const record)
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
	void PositionIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Strcpy(t_ComparePosition.TradingDay, TradingDay);
	}
	
	PositionDetailIndexTradeMatch::PositionDetailIndexTradeMatch(PositionDetailTable* table)
		:m_Table(table)
	{
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePositionDetail);
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradeMatch::iterator, PositionDetailIndexTradeMatch::iterator> PositionDetailIndexTradeMatch::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePositionDetail);
	}
	void PositionDetailIndexTradeMatch::Insert(PositionDetail* const record)
	{
		m_Index.insert(record);
	}
	void PositionDetailIndexTradeMatch::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PositionDetailIndexTradeMatch::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PositionDetailIndexTradeMatch::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradeMatchIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::FindNode(PositionDetail* const record)
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
	void PositionDetailIndexTradeMatch::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		Strcpy(t_ComparePositionDetail.TradingDay, TradingDay);
		Strcpy(t_ComparePositionDetail.AccountID, AccountID);
		Strcpy(t_ComparePositionDetail.ExchangeID, ExchangeID);
		Strcpy(t_ComparePositionDetail.InstrumentID, InstrumentID);
		t_ComparePositionDetail.PosiDirection = PosiDirection;
	}
	
	PositionDetailIndexTradingDay::PositionDetailIndexTradingDay(PositionDetailTable* table)
		:m_Table(table)
	{
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.lower_bound(&t_ComparePositionDetail);
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.upper_bound(&t_ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradingDay::iterator, PositionDetailIndexTradingDay::iterator> PositionDetailIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(m_Table->m_SharedMutex);
		return m_Index.equal_range(&t_ComparePositionDetail);
	}
	void PositionDetailIndexTradingDay::Insert(PositionDetail* const record)
	{
		m_Index.insert(record);
	}
	void PositionDetailIndexTradingDay::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		m_Index.erase(it);
	}
	void PositionDetailIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		m_Index.erase(it);
		m_Index.insert(record);
	}
	bool PositionDetailIndexTradingDay::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::FindNode(PositionDetail* const record)
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
	void PositionDetailIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Strcpy(t_ComparePositionDetail.TradingDay, TradingDay);
	}
	
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
