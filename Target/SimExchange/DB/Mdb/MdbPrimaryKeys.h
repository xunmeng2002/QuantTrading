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
	class DepthMarketDataTable;
	class DepthMarketDataPrimaryKey
	{
		using iterator = std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey>::iterator;
		friend class DepthMarketDataTable;
	public:
		DepthMarketDataPrimaryKey(DepthMarketDataTable* table, size_t buckets = 1000);
		DepthMarketData* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(DepthMarketData* const record);
		void Erase(DepthMarketData* const record);
		bool CheckInsert(DepthMarketData* const record);
		bool CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord);

	private:
		DepthMarketDataTable* m_Table;
		std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey> m_Index;
	};
	class SEBrokerTable;
	class SEBrokerPrimaryKey
	{
		using iterator = std::unordered_set<SEBroker*, SEBrokerHashForSEBrokerPrimaryKey, SEBrokerEqualForSEBrokerPrimaryKey>::iterator;
		friend class SEBrokerTable;
	public:
		SEBrokerPrimaryKey(SEBrokerTable* table, size_t buckets = 1000);
		SEBroker* Select(const BrokerIDType& BrokerID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(SEBroker* const record);
		void Erase(SEBroker* const record);
		bool CheckInsert(SEBroker* const record);
		bool CheckUpdate(const SEBroker* const oldRecord, const SEBroker* const newRecord);

	private:
		SEBrokerTable* m_Table;
		std::unordered_set<SEBroker*, SEBrokerHashForSEBrokerPrimaryKey, SEBrokerEqualForSEBrokerPrimaryKey> m_Index;
	};
	class SEInstrumentTable;
	class SEInstrumentPrimaryKey
	{
		using iterator = std::unordered_set<SEInstrument*, SEInstrumentHashForSEInstrumentPrimaryKey, SEInstrumentEqualForSEInstrumentPrimaryKey>::iterator;
		friend class SEInstrumentTable;
	public:
		SEInstrumentPrimaryKey(SEInstrumentTable* table, size_t buckets = 1000);
		SEInstrument* Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(SEInstrument* const record);
		void Erase(SEInstrument* const record);
		bool CheckInsert(SEInstrument* const record);
		bool CheckUpdate(const SEInstrument* const oldRecord, const SEInstrument* const newRecord);

	private:
		SEInstrumentTable* m_Table;
		std::unordered_set<SEInstrument*, SEInstrumentHashForSEInstrumentPrimaryKey, SEInstrumentEqualForSEInstrumentPrimaryKey> m_Index;
	};
	class SEOrderTable;
	class SEOrderPrimaryKey
	{
		using iterator = std::unordered_set<SEOrder*, SEOrderHashForSEOrderPrimaryKey, SEOrderEqualForSEOrderPrimaryKey>::iterator;
		friend class SEOrderTable;
	public:
		SEOrderPrimaryKey(SEOrderTable* table, size_t buckets = 1000);
		SEOrder* Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(SEOrder* const record);
		void Erase(SEOrder* const record);
		bool CheckInsert(SEOrder* const record);
		bool CheckUpdate(const SEOrder* const oldRecord, const SEOrder* const newRecord);

	private:
		SEOrderTable* m_Table;
		std::unordered_set<SEOrder*, SEOrderHashForSEOrderPrimaryKey, SEOrderEqualForSEOrderPrimaryKey> m_Index;
	};
	class SETradeTable;
	class SETradePrimaryKey
	{
		using iterator = std::unordered_set<SETrade*, SETradeHashForSETradePrimaryKey, SETradeEqualForSETradePrimaryKey>::iterator;
		friend class SETradeTable;
	public:
		SETradePrimaryKey(SETradeTable* table, size_t buckets = 1000);
		SETrade* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(SETrade* const record);
		void Erase(SETrade* const record);
		bool CheckInsert(SETrade* const record);
		bool CheckUpdate(const SETrade* const oldRecord, const SETrade* const newRecord);

	private:
		SETradeTable* m_Table;
		std::unordered_set<SETrade*, SETradeHashForSETradePrimaryKey, SETradeEqualForSETradePrimaryKey> m_Index;
	};
	class SEBrokerLoginSessionTable;
	class SEBrokerLoginSessionPrimaryKey
	{
		using iterator = std::unordered_set<SEBrokerLoginSession*, SEBrokerLoginSessionHashForSEBrokerLoginSessionPrimaryKey, SEBrokerLoginSessionEqualForSEBrokerLoginSessionPrimaryKey>::iterator;
		friend class SEBrokerLoginSessionTable;
	public:
		SEBrokerLoginSessionPrimaryKey(SEBrokerLoginSessionTable* table, size_t buckets = 1000);
		SEBrokerLoginSession* Select(const SessionIDType& SessionID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(SEBrokerLoginSession* const record);
		void Erase(SEBrokerLoginSession* const record);
		bool CheckInsert(SEBrokerLoginSession* const record);
		bool CheckUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord);

	private:
		SEBrokerLoginSessionTable* m_Table;
		std::unordered_set<SEBrokerLoginSession*, SEBrokerLoginSessionHashForSEBrokerLoginSessionPrimaryKey, SEBrokerLoginSessionEqualForSEBrokerLoginSessionPrimaryKey> m_Index;
	};
}
