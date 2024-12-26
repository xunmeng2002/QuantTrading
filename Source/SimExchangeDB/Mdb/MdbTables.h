#pragma once
#include "MdbStructs.h"
#include "MdbPrimaryKeys.h"
#include "MdbIndexes.h"
#include "MemCacheTemplate.h"
#include "MdbSubscriber.h"
#include <shared_mutex>
#include <atomic>


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
		void Erase(TradingDay* record);
		bool Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB = true);
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
		void Erase(Exchange* record);
		bool Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB = true);
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
		void Erase(Product* record);
		bool Update(Product* const oldRecord, Product* const newRecord, bool updateDB = true);
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
		void Erase(Instrument* record);
		bool Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB = true);
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
		void Erase(Account* record);
		bool Update(Account* const oldRecord, Account* const newRecord, bool updateDB = true);
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

	class PositionTable
	{
	public:
		PositionTable(Mdb* mdb);
		~PositionTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(Position* record);
		void Erase(Position* record);
		bool Update(Position* const oldRecord, Position* const newRecord, bool updateDB = true);
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(Position* record);
		void EraseIndex(Position* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		PositionPrimaryKey* m_PrimaryKey;
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
		void Erase(Order* record);
		bool Update(Order* const oldRecord, Order* const newRecord, bool updateDB = true);
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
		void Erase(Trade* record);
		bool Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB = true);
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

	class MdTickTable
	{
	public:
		MdTickTable(Mdb* mdb);
		~MdTickTable();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void LockShared();
		void UnlockShared();
		void InitDB();
		bool Insert(MdTick* record);
		void Erase(MdTick* record);
		bool Update(MdTick* const oldRecord, MdTick* const newRecord, bool updateDB = true);
		void TruncateTable();
		void Dump(const char* dir);

	private:
		void EraseUniqueKey(MdTick* record);
		void EraseIndex(MdTick* record);

	public:
		std::atomic<bool> m_DBInited;
		Mdb* m_Mdb;
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdTickPrimaryKey* m_PrimaryKey;
	};

}
