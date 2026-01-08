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

	class MdSubscribeTable
	{
	public:
		MdSubscribeTable(Mdb* mdb);
		~MdSubscribeTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(MdSubscribe* record);
		void BatchInsert(std::list<mdb::MdSubscribe*>* records);
		void Erase(MdSubscribe* record);
		bool Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(MdSubscribe* record);
		void EraseIndex(MdSubscribe* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdSubscribePrimaryKey* m_PrimaryKey;
	};

	class MdUserTable
	{
	public:
		MdUserTable(Mdb* mdb);
		~MdUserTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(MdUser* record);
		void BatchInsert(std::list<mdb::MdUser*>* records);
		void Erase(MdUser* record);
		bool Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(MdUser* record);
		void EraseIndex(MdUser* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdUserPrimaryKey* m_PrimaryKey;
	};

	class MdUserLoginSessionTable
	{
	public:
		MdUserLoginSessionTable(Mdb* mdb);
		~MdUserLoginSessionTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(MdUserLoginSession* record);
		void BatchInsert(std::list<mdb::MdUserLoginSession*>* records);
		void Erase(MdUserLoginSession* record);
		int EraseByMdUserIDIndex(const UserIDType& MdUserID);
		bool Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB = true);
		void TruncateTables();
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(MdUserLoginSession* record);
		void EraseIndex(MdUserLoginSession* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdUserLoginSessionPrimaryKey* m_PrimaryKey;
		MdUserLoginSessionIndexMdUserID* m_MdUserIDIndex;
	};

}
