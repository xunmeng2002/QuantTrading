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
	DepthMarketDataPrimaryKey::DepthMarketDataPrimaryKey(DepthMarketDataTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	DepthMarketData* DepthMarketDataPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Strcpy(t_CompareDepthMarketData.TradingDay, TradingDay);
		Strcpy(t_CompareDepthMarketData.ExchangeID, ExchangeID);
		Strcpy(t_CompareDepthMarketData.InstrumentID, InstrumentID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareDepthMarketData);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<DepthMarketDataPrimaryKey::iterator, DepthMarketDataPrimaryKey::iterator> DepthMarketDataPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool DepthMarketDataPrimaryKey::Insert(DepthMarketData* const record)
	{
		return m_Index.insert(record).second;
	}
	void DepthMarketDataPrimaryKey::Erase(DepthMarketData* const  record)
	{
		m_Index.erase(record);
	}
	bool DepthMarketDataPrimaryKey::CheckInsert(DepthMarketData* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool DepthMarketDataPrimaryKey::CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord)
	{
		return DepthMarketDataEqualForDepthMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	SEBrokerPrimaryKey::SEBrokerPrimaryKey(SEBrokerTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	SEBroker* SEBrokerPrimaryKey::Select(const BrokerIDType& BrokerID)
	{
		t_CompareSEBroker.BrokerID = BrokerID;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareSEBroker);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<SEBrokerPrimaryKey::iterator, SEBrokerPrimaryKey::iterator> SEBrokerPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool SEBrokerPrimaryKey::Insert(SEBroker* const record)
	{
		return m_Index.insert(record).second;
	}
	void SEBrokerPrimaryKey::Erase(SEBroker* const  record)
	{
		m_Index.erase(record);
	}
	bool SEBrokerPrimaryKey::CheckInsert(SEBroker* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool SEBrokerPrimaryKey::CheckUpdate(const SEBroker* const oldRecord, const SEBroker* const newRecord)
	{
		return SEBrokerEqualForSEBrokerPrimaryKey()(oldRecord, newRecord);
	}
	SEInstrumentPrimaryKey::SEInstrumentPrimaryKey(SEInstrumentTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	SEInstrument* SEInstrumentPrimaryKey::Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Strcpy(t_CompareSEInstrument.ExchangeID, ExchangeID);
		Strcpy(t_CompareSEInstrument.InstrumentID, InstrumentID);
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareSEInstrument);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<SEInstrumentPrimaryKey::iterator, SEInstrumentPrimaryKey::iterator> SEInstrumentPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool SEInstrumentPrimaryKey::Insert(SEInstrument* const record)
	{
		return m_Index.insert(record).second;
	}
	void SEInstrumentPrimaryKey::Erase(SEInstrument* const  record)
	{
		m_Index.erase(record);
	}
	bool SEInstrumentPrimaryKey::CheckInsert(SEInstrument* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool SEInstrumentPrimaryKey::CheckUpdate(const SEInstrument* const oldRecord, const SEInstrument* const newRecord)
	{
		return SEInstrumentEqualForSEInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	SEOrderPrimaryKey::SEOrderPrimaryKey(SEOrderTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	SEOrder* SEOrderPrimaryKey::Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
	{
		Strcpy(t_CompareSEOrder.TradingDay, TradingDay);
		Strcpy(t_CompareSEOrder.AccountID, AccountID);
		Strcpy(t_CompareSEOrder.ExchangeID, ExchangeID);
		Strcpy(t_CompareSEOrder.InstrumentID, InstrumentID);
		t_CompareSEOrder.OrderID = OrderID;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareSEOrder);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<SEOrderPrimaryKey::iterator, SEOrderPrimaryKey::iterator> SEOrderPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool SEOrderPrimaryKey::Insert(SEOrder* const record)
	{
		return m_Index.insert(record).second;
	}
	void SEOrderPrimaryKey::Erase(SEOrder* const  record)
	{
		m_Index.erase(record);
	}
	bool SEOrderPrimaryKey::CheckInsert(SEOrder* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool SEOrderPrimaryKey::CheckUpdate(const SEOrder* const oldRecord, const SEOrder* const newRecord)
	{
		return SEOrderEqualForSEOrderPrimaryKey()(oldRecord, newRecord);
	}
	SETradePrimaryKey::SETradePrimaryKey(SETradeTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	SETrade* SETradePrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
	{
		Strcpy(t_CompareSETrade.TradingDay, TradingDay);
		Strcpy(t_CompareSETrade.ExchangeID, ExchangeID);
		Strcpy(t_CompareSETrade.TradeID, TradeID);
		t_CompareSETrade.Direction = Direction;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareSETrade);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<SETradePrimaryKey::iterator, SETradePrimaryKey::iterator> SETradePrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool SETradePrimaryKey::Insert(SETrade* const record)
	{
		return m_Index.insert(record).second;
	}
	void SETradePrimaryKey::Erase(SETrade* const  record)
	{
		m_Index.erase(record);
	}
	bool SETradePrimaryKey::CheckInsert(SETrade* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool SETradePrimaryKey::CheckUpdate(const SETrade* const oldRecord, const SETrade* const newRecord)
	{
		return SETradeEqualForSETradePrimaryKey()(oldRecord, newRecord);
	}
	SEBrokerLoginSessionPrimaryKey::SEBrokerLoginSessionPrimaryKey(SEBrokerLoginSessionTable* table, size_t buckets)
		:m_Table(table), m_Index(buckets)
	{
	}
	SEBrokerLoginSession* SEBrokerLoginSessionPrimaryKey::Select(const SessionIDType& SessionID)
	{
		t_CompareSEBrokerLoginSession.SessionID = SessionID;
		
		std::shared_lock guard(m_Table->m_SharedMutex);
		auto it = m_Index.find(&t_CompareSEBrokerLoginSession);
		if (it == m_Index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<SEBrokerLoginSessionPrimaryKey::iterator, SEBrokerLoginSessionPrimaryKey::iterator> SEBrokerLoginSessionPrimaryKey::SelectAll()
	{
		std::shared_lock guard(m_Table->m_SharedMutex);
		return std::pair<iterator, iterator>(m_Index.begin(), m_Index.end());
	}
	bool SEBrokerLoginSessionPrimaryKey::Insert(SEBrokerLoginSession* const record)
	{
		return m_Index.insert(record).second;
	}
	void SEBrokerLoginSessionPrimaryKey::Erase(SEBrokerLoginSession* const  record)
	{
		m_Index.erase(record);
	}
	bool SEBrokerLoginSessionPrimaryKey::CheckInsert(SEBrokerLoginSession* const record)
	{
		return m_Index.find(record) == m_Index.end();
	}
	bool SEBrokerLoginSessionPrimaryKey::CheckUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord)
	{
		return SEBrokerLoginSessionEqualForSEBrokerLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
}
