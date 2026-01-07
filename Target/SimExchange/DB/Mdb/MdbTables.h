#pragma once
#include "MdbStructs.h"
#include "MdbPrimaryKeys.h"
#include "MdbIndexes.h"
#include "MemCacheTemplate.h"
#include "MdbSubscriber.h"
#include <shared_mutex>
#include <atomic>
#include <list>


namespace mdb
{
	class Mdb;
	class TradingDayTable
	{
	public:
		TradingDayTable(Mdb* mdb);
		~TradingDayTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(TradingDay* record);
		void BatchInsert(std::list<mdb::TradingDay*>* records);
		void Erase(TradingDay* record);
		bool Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(TradingDay* record);
		void EraseIndex(TradingDay* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		TradingDayPrimaryKey* m_PrimaryKey;
	};

	class ExchangeTable
	{
	public:
		ExchangeTable(Mdb* mdb);
		~ExchangeTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Exchange* record);
		void BatchInsert(std::list<mdb::Exchange*>* records);
		void Erase(Exchange* record);
		bool Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Exchange* record);
		void EraseIndex(Exchange* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		ExchangePrimaryKey* m_PrimaryKey;
	};

	class ProductTable
	{
	public:
		ProductTable(Mdb* mdb);
		~ProductTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Product* record);
		void BatchInsert(std::list<mdb::Product*>* records);
		void Erase(Product* record);
		bool Update(Product* const oldRecord, Product* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Product* record);
		void EraseIndex(Product* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		ProductPrimaryKey* m_PrimaryKey;
	};

	class SEBrokerTable
	{
	public:
		SEBrokerTable(Mdb* mdb);
		~SEBrokerTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(SEBroker* record);
		void BatchInsert(std::list<mdb::SEBroker*>* records);
		void Erase(SEBroker* record);
		bool Update(SEBroker* const oldRecord, SEBroker* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(SEBroker* record);
		void EraseIndex(SEBroker* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		SEBrokerPrimaryKey* m_PrimaryKey;
	};

	class SEInstrumentTable
	{
	public:
		SEInstrumentTable(Mdb* mdb);
		~SEInstrumentTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(SEInstrument* record);
		void BatchInsert(std::list<mdb::SEInstrument*>* records);
		void Erase(SEInstrument* record);
		int EraseByExchangeIDIndex(const ExchangeIDType& ExchangeID);
		bool Update(SEInstrument* const oldRecord, SEInstrument* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(SEInstrument* record);
		void EraseIndex(SEInstrument* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		SEInstrumentPrimaryKey* m_PrimaryKey;
		SEInstrumentIndexExchangeID* m_ExchangeIDIndex;
	};

	class SEOrderTable
	{
	public:
		SEOrderTable(Mdb* mdb);
		~SEOrderTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(SEOrder* record);
		void BatchInsert(std::list<mdb::SEOrder*>* records);
		void Erase(SEOrder* record);
		int EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID);
		bool Update(SEOrder* const oldRecord, SEOrder* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(SEOrder* record);
		void EraseIndex(SEOrder* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		SEOrderPrimaryKey* m_PrimaryKey;
		SEOrderIndexAccountID* m_AccountIDIndex;
	};

	class SETradeTable
	{
	public:
		SETradeTable(Mdb* mdb);
		~SETradeTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(SETrade* record);
		void BatchInsert(std::list<mdb::SETrade*>* records);
		void Erase(SETrade* record);
		int EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID);
		bool Update(SETrade* const oldRecord, SETrade* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(SETrade* record);
		void EraseIndex(SETrade* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		SETradePrimaryKey* m_PrimaryKey;
		SETradeIndexAccountID* m_AccountIDIndex;
	};

	class SEBrokerLoginSessionTable
	{
	public:
		SEBrokerLoginSessionTable(Mdb* mdb);
		~SEBrokerLoginSessionTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(SEBrokerLoginSession* record);
		void BatchInsert(std::list<mdb::SEBrokerLoginSession*>* records);
		void Erase(SEBrokerLoginSession* record);
		int EraseByBrokerIDIndex(const BrokerIDType& BrokerID);
		bool Update(SEBrokerLoginSession* const oldRecord, SEBrokerLoginSession* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(SEBrokerLoginSession* record);
		void EraseIndex(SEBrokerLoginSession* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		SEBrokerLoginSessionPrimaryKey* m_PrimaryKey;
		SEBrokerLoginSessionIndexBrokerID* m_BrokerIDIndex;
	};

	class DepthMarketDataTable
	{
	public:
		DepthMarketDataTable(Mdb* mdb);
		~DepthMarketDataTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(DepthMarketData* record);
		void BatchInsert(std::list<mdb::DepthMarketData*>* records);
		void Erase(DepthMarketData* record);
		bool Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(DepthMarketData* record);
		void EraseIndex(DepthMarketData* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		DepthMarketDataPrimaryKey* m_PrimaryKey;
	};

}
