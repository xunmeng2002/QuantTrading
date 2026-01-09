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

	class HotInstrumentTable
	{
	public:
		HotInstrumentTable(Mdb* mdb);
		~HotInstrumentTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(HotInstrument* record);
		void BatchInsert(std::list<mdb::HotInstrument*>* records);
		void Erase(HotInstrument* record);
		int EraseByTradingDayIndex(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		bool Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(HotInstrument* record);
		void EraseIndex(HotInstrument* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		HotInstrumentPrimaryKey* m_PrimaryKey;
		HotInstrumentIndexTradingDay* m_TradingDayIndex;
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

}
