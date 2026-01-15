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

	class InstrumentTable
	{
	public:
		InstrumentTable(Mdb* mdb);
		~InstrumentTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Instrument* record);
		void BatchInsert(std::list<mdb::Instrument*>* records);
		void Erase(Instrument* record);
		bool Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Instrument* record);
		void EraseIndex(Instrument* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		InstrumentPrimaryKey* m_PrimaryKey;
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

	class BarMarketDataTable
	{
	public:
		BarMarketDataTable(Mdb* mdb);
		~BarMarketDataTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(BarMarketData* record);
		void BatchInsert(std::list<mdb::BarMarketData*>* records);
		void Erase(BarMarketData* record);
		bool Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(BarMarketData* record);
		void EraseIndex(BarMarketData* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		BarMarketDataPrimaryKey* m_PrimaryKey;
	};

	class PrimaryAccountTable
	{
	public:
		PrimaryAccountTable(Mdb* mdb);
		~PrimaryAccountTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(PrimaryAccount* record);
		void BatchInsert(std::list<mdb::PrimaryAccount*>* records);
		void Erase(PrimaryAccount* record);
		int EraseByOfferIDIndex(const OfferIDType& OfferID);
		bool Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(PrimaryAccount* record);
		void EraseIndex(PrimaryAccount* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		PrimaryAccountPrimaryKey* m_PrimaryKey;
		PrimaryAccountIndexOfferID* m_OfferIDIndex;
	};

	class AccountTable
	{
	public:
		AccountTable(Mdb* mdb);
		~AccountTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Account* record);
		void BatchInsert(std::list<mdb::Account*>* records);
		void Erase(Account* record);
		bool Update(Account* const oldRecord, Account* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Account* record);
		void EraseIndex(Account* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		AccountPrimaryKey* m_PrimaryKey;
	};

	class OrderTable
	{
	public:
		OrderTable(Mdb* mdb);
		~OrderTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Order* record);
		void BatchInsert(std::list<mdb::Order*>* records);
		void Erase(Order* record);
		bool Update(Order* const oldRecord, Order* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Order* record);
		void EraseIndex(Order* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		OrderPrimaryKey* m_PrimaryKey;
		OrderUniqueKeyClientOrderID* m_ClientOrderIDUniqueKey;
	};

	class TradeTable
	{
	public:
		TradeTable(Mdb* mdb);
		~TradeTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Trade* record);
		void BatchInsert(std::list<mdb::Trade*>* records);
		void Erase(Trade* record);
		bool Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Trade* record);
		void EraseIndex(Trade* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		TradePrimaryKey* m_PrimaryKey;
	};

	class AccountLoginSessionTable
	{
	public:
		AccountLoginSessionTable(Mdb* mdb);
		~AccountLoginSessionTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(AccountLoginSession* record);
		void BatchInsert(std::list<mdb::AccountLoginSession*>* records);
		void Erase(AccountLoginSession* record);
		int EraseByAccountIDIndex(const AccountIDType& AccountID);
		bool Update(AccountLoginSession* const oldRecord, AccountLoginSession* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(AccountLoginSession* record);
		void EraseIndex(AccountLoginSession* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		AccountLoginSessionPrimaryKey* m_PrimaryKey;
		AccountLoginSessionIndexAccountID* m_AccountIDIndex;
	};

}
