// 本文件由 ../Templates/Cpp/Mdb/MdbTables.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbTables.h"
#include <Spark/Core/Logger/Logger.h>
#include <string>
#include <cstring>
#include <set>
#include <vector>

using std::string;
using std::set;
using namespace spark::core;

namespace mdb
{
	TradingDayTable::TradingDayTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new TradingDayPrimaryKey(this);
	}
	TradingDayTable::~TradingDayTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void TradingDayTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void TradingDayTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void TradingDayTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void TradingDayTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void TradingDayTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(TradingDay::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = TradingDay::Allocate();
				memcpy(record, *it, sizeof(TradingDay));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(TradingDay::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool TradingDayTable::Insert(TradingDay* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for TradingDay:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(TradingDay::TableID, record);
		}
		return true;
	}
	void TradingDayTable::BatchInsert(std::vector<mdb::TradingDay*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = TradingDay::Allocate();
				memcpy(newRecord, record, sizeof(TradingDay));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(TradingDay::TableID, dbRecords);
		}
		delete records;
	}
	void TradingDayTable::Erase(TradingDay* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(TradingDay::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool TradingDayTable::Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for TradingDay:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New TradingDay:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(TradingDay));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(TradingDay::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void TradingDayTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void TradingDayTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(TradingDay::TableID);
		}
	}
	void TradingDayTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_TradingDay.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "PK,CurrTradingDay,PreTradingDay\n");
		char buff[4096] = { 0 };
		set<TradingDay*, TradingDayLessForTradingDayPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void TradingDayTable::EraseUniqueKey(TradingDay* record)
	{
		primaryKey->Erase(record);
	}
	void TradingDayTable::EraseIndex(TradingDay* record)
	{
	}

	ExchangeTable::ExchangeTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new ExchangePrimaryKey(this);
	}
	ExchangeTable::~ExchangeTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void ExchangeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void ExchangeTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void ExchangeTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void ExchangeTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void ExchangeTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Exchange::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Exchange::Allocate();
				memcpy(record, *it, sizeof(Exchange));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Exchange::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool ExchangeTable::Insert(Exchange* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Exchange:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Exchange::TableID, record);
		}
		return true;
	}
	void ExchangeTable::BatchInsert(std::vector<mdb::Exchange*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Exchange::Allocate();
				memcpy(newRecord, record, sizeof(Exchange));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Exchange::TableID, dbRecords);
		}
		delete records;
	}
	void ExchangeTable::Erase(Exchange* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Exchange::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool ExchangeTable::Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Exchange:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Exchange:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Exchange));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Exchange::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void ExchangeTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void ExchangeTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Exchange::TableID);
		}
	}
	void ExchangeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Exchange.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "ExchangeID,ExchangeName\n");
		char buff[4096] = { 0 };
		set<Exchange*, ExchangeLessForExchangePrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void ExchangeTable::EraseUniqueKey(Exchange* record)
	{
		primaryKey->Erase(record);
	}
	void ExchangeTable::EraseIndex(Exchange* record)
	{
	}

	ProductTable::ProductTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new ProductPrimaryKey(this);
	}
	ProductTable::~ProductTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void ProductTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void ProductTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void ProductTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void ProductTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void ProductTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Product::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Product::Allocate();
				memcpy(record, *it, sizeof(Product));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Product::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool ProductTable::Insert(Product* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Product:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Product::TableID, record);
		}
		return true;
	}
	void ProductTable::BatchInsert(std::vector<mdb::Product*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Product::Allocate();
				memcpy(newRecord, record, sizeof(Product));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Product::TableID, dbRecords);
		}
		delete records;
	}
	void ProductTable::Erase(Product* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Product::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool ProductTable::Update(Product* const oldRecord, Product* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Product:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Product:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Product));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Product::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void ProductTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void ProductTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Product::TableID);
		}
	}
	void ProductTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Product.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "ExchangeID,ProductID,ProductName,ProductClass,VolumeMultiple,PriceTick,MaxMarketOrderVolume,MinMarketOrderVolume,MaxLimitOrderVolume,MinLimitOrderVolume,SessionName\n");
		char buff[4096] = { 0 };
		set<Product*, ProductLessForProductPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void ProductTable::EraseUniqueKey(Product* record)
	{
		primaryKey->Erase(record);
	}
	void ProductTable::EraseIndex(Product* record)
	{
	}

	HotInstrumentTable::HotInstrumentTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new HotInstrumentPrimaryKey(this);
		tradingDayIndex = new HotInstrumentIndexTradingDay(this);
	}
	HotInstrumentTable::~HotInstrumentTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete tradingDayIndex;
		tradingDayIndex = nullptr;
	}
	void HotInstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void HotInstrumentTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void HotInstrumentTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void HotInstrumentTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void HotInstrumentTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(HotInstrument::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = HotInstrument::Allocate();
				memcpy(record, *it, sizeof(HotInstrument));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(HotInstrument::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool HotInstrumentTable::Insert(HotInstrument* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for HotInstrument:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		tradingDayIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(HotInstrument::TableID, record);
		}
		return true;
	}
	void HotInstrumentTable::BatchInsert(std::vector<mdb::HotInstrument*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = HotInstrument::Allocate();
				memcpy(newRecord, record, sizeof(HotInstrument));
				primaryKey->Insert(newRecord);

				tradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(HotInstrument::TableID, dbRecords);
		}
		delete records;
	}
	void HotInstrumentTable::Erase(HotInstrument* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(HotInstrument::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int HotInstrumentTable::EraseByTradingDayIndex(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay)
	{
		tradingDayIndex->FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::vector<HotInstrument*> records;
		std::lock_guard guard(sharedMutex);
		auto range = tradingDayIndex->index.equal_range(&CompareHotInstrument);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = HotInstrument::Allocate();
			memcpy(record, &CompareHotInstrument, sizeof(HotInstrument));
			mdbSubscriber->OnRecordEraseByIndex(HotInstrument::TableID, HotInstrumentIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool HotInstrumentTable::Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for HotInstrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New HotInstrument:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradingDayIndexUpdate = tradingDayIndex->NeedUpdate(oldRecord, newRecord);
		HotInstrumentIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = tradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(HotInstrument));
		if (TradingDayIndexUpdate)
		{
			tradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(HotInstrument::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void HotInstrumentTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradingDayIndex->index.clear();
	}
	void HotInstrumentTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradingDayIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(HotInstrument::TableID);
		}
	}
	void HotInstrumentTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_HotInstrument.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,ExchangeID,ProductID,InstrumentID,ProductClass,Volume,MaxVolume,Turnover,MaxTurnover,OpenInterest,MaxOpenInterest,Rank\n");
		char buff[4096] = { 0 };
		set<HotInstrument*, HotInstrumentLessForHotInstrumentPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void HotInstrumentTable::EraseUniqueKey(HotInstrument* record)
	{
		primaryKey->Erase(record);
	}
	void HotInstrumentTable::EraseIndex(HotInstrument* record)
	{
		tradingDayIndex->Erase(record);
	}

	InstrumentTable::InstrumentTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new InstrumentPrimaryKey(this);
		exchangeIDIndex = new InstrumentIndexExchangeID(this);
	}
	InstrumentTable::~InstrumentTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete exchangeIDIndex;
		exchangeIDIndex = nullptr;
	}
	void InstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void InstrumentTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void InstrumentTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void InstrumentTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void InstrumentTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Instrument::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Instrument::Allocate();
				memcpy(record, *it, sizeof(Instrument));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Instrument::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool InstrumentTable::Insert(Instrument* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Instrument:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		exchangeIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Instrument::TableID, record);
		}
		return true;
	}
	void InstrumentTable::BatchInsert(std::vector<mdb::Instrument*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Instrument::Allocate();
				memcpy(newRecord, record, sizeof(Instrument));
				primaryKey->Insert(newRecord);

				exchangeIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Instrument::TableID, dbRecords);
		}
		delete records;
	}
	void InstrumentTable::Erase(Instrument* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Instrument::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int InstrumentTable::EraseByExchangeIDIndex(const ExchangeIDType& ExchangeID)
	{
		exchangeIDIndex->FillCompareRecord(ExchangeID);
		std::vector<Instrument*> records;
		std::lock_guard guard(sharedMutex);
		auto range = exchangeIDIndex->index.equal_range(&CompareInstrument);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Instrument::Allocate();
			memcpy(record, &CompareInstrument, sizeof(Instrument));
			mdbSubscriber->OnRecordEraseByIndex(Instrument::TableID, InstrumentIndexExchangeID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool InstrumentTable::Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Instrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Instrument:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool ExchangeIDIndexUpdate = exchangeIDIndex->NeedUpdate(oldRecord, newRecord);
		InstrumentIndexExchangeID::iterator itExchangeID;
		if (ExchangeIDIndexUpdate)
		{
			itExchangeID = exchangeIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Instrument));
		if (ExchangeIDIndexUpdate)
		{
			exchangeIDIndex->Update(itExchangeID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Instrument::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void InstrumentTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		exchangeIDIndex->index.clear();
	}
	void InstrumentTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		exchangeIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Instrument::TableID);
		}
	}
	void InstrumentTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Instrument.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "ExchangeID,InstrumentID,ExchangeInstID,InstrumentName,ProductID,ProductClass,InstrumentClass,Rank,VolumeMultiple,PriceTick,MaxMarketOrderVolume,MinMarketOrderVolume,MaxLimitOrderVolume,MinLimitOrderVolume,SessionName\n");
		char buff[4096] = { 0 };
		set<Instrument*, InstrumentLessForInstrumentPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void InstrumentTable::EraseUniqueKey(Instrument* record)
	{
		primaryKey->Erase(record);
	}
	void InstrumentTable::EraseIndex(Instrument* record)
	{
		exchangeIDIndex->Erase(record);
	}

	DepthMarketDataTable::DepthMarketDataTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new DepthMarketDataPrimaryKey(this);
	}
	DepthMarketDataTable::~DepthMarketDataTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void DepthMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void DepthMarketDataTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void DepthMarketDataTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void DepthMarketDataTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void DepthMarketDataTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(DepthMarketData::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = DepthMarketData::Allocate();
				memcpy(record, *it, sizeof(DepthMarketData));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(DepthMarketData::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool DepthMarketDataTable::Insert(DepthMarketData* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for DepthMarketData:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(DepthMarketData::TableID, record);
		}
		return true;
	}
	void DepthMarketDataTable::BatchInsert(std::vector<mdb::DepthMarketData*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = DepthMarketData::Allocate();
				memcpy(newRecord, record, sizeof(DepthMarketData));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(DepthMarketData::TableID, dbRecords);
		}
		delete records;
	}
	void DepthMarketDataTable::Erase(DepthMarketData* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(DepthMarketData::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool DepthMarketDataTable::Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for DepthMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New DepthMarketData:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(DepthMarketData));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(DepthMarketData::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void DepthMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void DepthMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(DepthMarketData::TableID);
		}
	}
	void DepthMarketDataTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_DepthMarketData.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,ExchangeID,InstrumentID,UpdateTs,LastPrice,PreSettlementPrice,PreClosePrice,PreOpenInterest,OpenPrice,HighestPrice,LowestPrice,ClosePrice,CurrVolume,Volume,CurrTurnover,Turnover,OpenInterest,SettlementPrice,UpperLimitPrice,LowerLimitPrice,AveragePrice,AskPrice1,AskPrice2,AskPrice3,AskPrice4,AskPrice5,AskPrice6,AskPrice7,AskPrice8,AskPrice9,AskPrice10,AskVolume1,AskVolume2,AskVolume3,AskVolume4,AskVolume5,AskVolume6,AskVolume7,AskVolume8,AskVolume9,AskVolume10,BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,BidPrice6,BidPrice7,BidPrice8,BidPrice9,BidPrice10,BidVolume1,BidVolume2,BidVolume3,BidVolume4,BidVolume5,BidVolume6,BidVolume7,BidVolume8,BidVolume9,BidVolume10\n");
		char buff[4096] = { 0 };
		set<DepthMarketData*, DepthMarketDataLessForDepthMarketDataPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void DepthMarketDataTable::EraseUniqueKey(DepthMarketData* record)
	{
		primaryKey->Erase(record);
	}
	void DepthMarketDataTable::EraseIndex(DepthMarketData* record)
	{
	}

	BarMarketDataTable::BarMarketDataTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new BarMarketDataPrimaryKey(this);
	}
	BarMarketDataTable::~BarMarketDataTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void BarMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void BarMarketDataTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void BarMarketDataTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void BarMarketDataTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void BarMarketDataTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(BarMarketData::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = BarMarketData::Allocate();
				memcpy(record, *it, sizeof(BarMarketData));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(BarMarketData::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool BarMarketDataTable::Insert(BarMarketData* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for BarMarketData:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(BarMarketData::TableID, record);
		}
		return true;
	}
	void BarMarketDataTable::BatchInsert(std::vector<mdb::BarMarketData*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = BarMarketData::Allocate();
				memcpy(newRecord, record, sizeof(BarMarketData));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(BarMarketData::TableID, dbRecords);
		}
		delete records;
	}
	void BarMarketDataTable::Erase(BarMarketData* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(BarMarketData::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool BarMarketDataTable::Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for BarMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New BarMarketData:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(BarMarketData));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(BarMarketData::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void BarMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void BarMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(BarMarketData::TableID);
		}
	}
	void BarMarketDataTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_BarMarketData.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,ExchangeID,InstrumentID,BarPreces,BarPeriod,BarTime,UpdateTs,PreSettlementPrice,PreClosePrice,HighestPrice,LowestPrice,Open,High,Low,Close,CurrVolume,Volume,CurrTurnover,Turnover,OpenInterest\n");
		char buff[4096] = { 0 };
		set<BarMarketData*, BarMarketDataLessForBarMarketDataPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void BarMarketDataTable::EraseUniqueKey(BarMarketData* record)
	{
		primaryKey->Erase(record);
	}
	void BarMarketDataTable::EraseIndex(BarMarketData* record)
	{
	}

	MdSubscribeTable::MdSubscribeTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new MdSubscribePrimaryKey(this);
	}
	MdSubscribeTable::~MdSubscribeTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void MdSubscribeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void MdSubscribeTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void MdSubscribeTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void MdSubscribeTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void MdSubscribeTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(MdSubscribe::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = MdSubscribe::Allocate();
				memcpy(record, *it, sizeof(MdSubscribe));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(MdSubscribe::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool MdSubscribeTable::Insert(MdSubscribe* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdSubscribe:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(MdSubscribe::TableID, record);
		}
		return true;
	}
	void MdSubscribeTable::BatchInsert(std::vector<mdb::MdSubscribe*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdSubscribe::Allocate();
				memcpy(newRecord, record, sizeof(MdSubscribe));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(MdSubscribe::TableID, dbRecords);
		}
		delete records;
	}
	void MdSubscribeTable::Erase(MdSubscribe* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(MdSubscribe::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool MdSubscribeTable::Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdSubscribe:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdSubscribe:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(MdSubscribe));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(MdSubscribe::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdSubscribeTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void MdSubscribeTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(MdSubscribe::TableID);
		}
	}
	void MdSubscribeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_MdSubscribe.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "ExchangeID,InstrumentID,RealInstrumentID,ProductID,ProductClass,StartTradingDay,EndTradingDay\n");
		char buff[4096] = { 0 };
		set<MdSubscribe*, MdSubscribeLessForMdSubscribePrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void MdSubscribeTable::EraseUniqueKey(MdSubscribe* record)
	{
		primaryKey->Erase(record);
	}
	void MdSubscribeTable::EraseIndex(MdSubscribe* record)
	{
	}

	MdUserTable::MdUserTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new MdUserPrimaryKey(this);
	}
	MdUserTable::~MdUserTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void MdUserTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void MdUserTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void MdUserTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void MdUserTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void MdUserTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(MdUser::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = MdUser::Allocate();
				memcpy(record, *it, sizeof(MdUser));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(MdUser::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool MdUserTable::Insert(MdUser* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUser:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(MdUser::TableID, record);
		}
		return true;
	}
	void MdUserTable::BatchInsert(std::vector<mdb::MdUser*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUser::Allocate();
				memcpy(newRecord, record, sizeof(MdUser));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(MdUser::TableID, dbRecords);
		}
		delete records;
	}
	void MdUserTable::Erase(MdUser* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(MdUser::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool MdUserTable::Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUser:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUser:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(MdUser));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(MdUser::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdUserTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void MdUserTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(MdUser::TableID);
		}
	}
	void MdUserTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_MdUser.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "MdUserID,MdUserName,Password\n");
		char buff[4096] = { 0 };
		set<MdUser*, MdUserLessForMdUserPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void MdUserTable::EraseUniqueKey(MdUser* record)
	{
		primaryKey->Erase(record);
	}
	void MdUserTable::EraseIndex(MdUser* record)
	{
	}

	MdUserLoginSessionTable::MdUserLoginSessionTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new MdUserLoginSessionPrimaryKey(this);
		sessionIDIndex = new MdUserLoginSessionIndexSessionID(this);
		mdUserIDIndex = new MdUserLoginSessionIndexMdUserID(this);
	}
	MdUserLoginSessionTable::~MdUserLoginSessionTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete sessionIDIndex;
		sessionIDIndex = nullptr;
		delete mdUserIDIndex;
		mdUserIDIndex = nullptr;
	}
	void MdUserLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void MdUserLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void MdUserLoginSessionTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void MdUserLoginSessionTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void MdUserLoginSessionTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(MdUserLoginSession::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = MdUserLoginSession::Allocate();
				memcpy(record, *it, sizeof(MdUserLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(MdUserLoginSession::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool MdUserLoginSessionTable::Insert(MdUserLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUserLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		sessionIDIndex->Insert(record);
		mdUserIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(MdUserLoginSession::TableID, record);
		}
		return true;
	}
	void MdUserLoginSessionTable::BatchInsert(std::vector<mdb::MdUserLoginSession*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUserLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(MdUserLoginSession));
				primaryKey->Insert(newRecord);

				sessionIDIndex->Insert(newRecord);
				mdUserIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(MdUserLoginSession::TableID, dbRecords);
		}
		delete records;
	}
	void MdUserLoginSessionTable::Erase(MdUserLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(MdUserLoginSession::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int MdUserLoginSessionTable::EraseBySessionIDIndex(const SessionIDType& SessionID)
	{
		sessionIDIndex->FillCompareRecord(SessionID);
		std::vector<MdUserLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = sessionIDIndex->index.equal_range(&CompareMdUserLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = MdUserLoginSession::Allocate();
			memcpy(record, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(MdUserLoginSession::TableID, MdUserLoginSessionIndexSessionID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int MdUserLoginSessionTable::EraseByMdUserIDIndex(const UserIDType& MdUserID)
	{
		mdUserIDIndex->FillCompareRecord(MdUserID);
		std::vector<MdUserLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = mdUserIDIndex->index.equal_range(&CompareMdUserLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = MdUserLoginSession::Allocate();
			memcpy(record, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(MdUserLoginSession::TableID, MdUserLoginSessionIndexMdUserID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool MdUserLoginSessionTable::Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUserLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUserLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIDIndexUpdate = sessionIDIndex->NeedUpdate(oldRecord, newRecord);
		MdUserLoginSessionIndexSessionID::iterator itSessionID;
		if (SessionIDIndexUpdate)
		{
			itSessionID = sessionIDIndex->FindNode(oldRecord);
		}
		bool MdUserIDIndexUpdate = mdUserIDIndex->NeedUpdate(oldRecord, newRecord);
		MdUserLoginSessionIndexMdUserID::iterator itMdUserID;
		if (MdUserIDIndexUpdate)
		{
			itMdUserID = mdUserIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(MdUserLoginSession));
		if (SessionIDIndexUpdate)
		{
			sessionIDIndex->Update(itSessionID);
		}
		if (MdUserIDIndexUpdate)
		{
			mdUserIDIndex->Update(itMdUserID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(MdUserLoginSession::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdUserLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		mdUserIDIndex->index.clear();
	}
	void MdUserLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		mdUserIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(MdUserLoginSession::TableID);
		}
	}
	void MdUserLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_MdUserLoginSession.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "MdUserID,SessionID,IPAddress\n");
		char buff[4096] = { 0 };
		set<MdUserLoginSession*, MdUserLoginSessionLessForMdUserLoginSessionPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void MdUserLoginSessionTable::EraseUniqueKey(MdUserLoginSession* record)
	{
		primaryKey->Erase(record);
	}
	void MdUserLoginSessionTable::EraseIndex(MdUserLoginSession* record)
	{
		sessionIDIndex->Erase(record);
		mdUserIDIndex->Erase(record);
	}

	PrimaryAccountTable::PrimaryAccountTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new PrimaryAccountPrimaryKey(this);
		offerIDIndex = new PrimaryAccountIndexOfferID(this);
	}
	PrimaryAccountTable::~PrimaryAccountTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete offerIDIndex;
		offerIDIndex = nullptr;
	}
	void PrimaryAccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void PrimaryAccountTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void PrimaryAccountTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void PrimaryAccountTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void PrimaryAccountTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(PrimaryAccount::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = PrimaryAccount::Allocate();
				memcpy(record, *it, sizeof(PrimaryAccount));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(PrimaryAccount::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool PrimaryAccountTable::Insert(PrimaryAccount* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PrimaryAccount:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		offerIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(PrimaryAccount::TableID, record);
		}
		return true;
	}
	void PrimaryAccountTable::BatchInsert(std::vector<mdb::PrimaryAccount*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PrimaryAccount::Allocate();
				memcpy(newRecord, record, sizeof(PrimaryAccount));
				primaryKey->Insert(newRecord);

				offerIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(PrimaryAccount::TableID, dbRecords);
		}
		delete records;
	}
	void PrimaryAccountTable::Erase(PrimaryAccount* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(PrimaryAccount::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PrimaryAccountTable::EraseByOfferIDIndex(const OfferIDType& OfferID)
	{
		offerIDIndex->FillCompareRecord(OfferID);
		std::vector<PrimaryAccount*> records;
		std::lock_guard guard(sharedMutex);
		auto range = offerIDIndex->index.equal_range(&ComparePrimaryAccount);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = PrimaryAccount::Allocate();
			memcpy(record, &ComparePrimaryAccount, sizeof(PrimaryAccount));
			mdbSubscriber->OnRecordEraseByIndex(PrimaryAccount::TableID, PrimaryAccountIndexOfferID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountTable::Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccount:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PrimaryAccount:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool OfferIDIndexUpdate = offerIDIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountIndexOfferID::iterator itOfferID;
		if (OfferIDIndexUpdate)
		{
			itOfferID = offerIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PrimaryAccount));
		if (OfferIDIndexUpdate)
		{
			offerIDIndex->Update(itOfferID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(PrimaryAccount::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PrimaryAccountTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		offerIDIndex->index.clear();
	}
	void PrimaryAccountTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		offerIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(PrimaryAccount::TableID);
		}
	}
	void PrimaryAccountTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_PrimaryAccount.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "PrimaryAccountID,PrimaryAccountName,AccountClass,Password,OfferID,IsAllowLogin,IsSimulateAccount,LoginStatus,InitStatus\n");
		char buff[4096] = { 0 };
		set<PrimaryAccount*, PrimaryAccountLessForPrimaryAccountPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void PrimaryAccountTable::EraseUniqueKey(PrimaryAccount* record)
	{
		primaryKey->Erase(record);
	}
	void PrimaryAccountTable::EraseIndex(PrimaryAccount* record)
	{
		offerIDIndex->Erase(record);
	}

	AccountTable::AccountTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new AccountPrimaryKey(this);
	}
	AccountTable::~AccountTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
	}
	void AccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void AccountTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void AccountTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void AccountTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void AccountTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Account::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Account::Allocate();
				memcpy(record, *it, sizeof(Account));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Account::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool AccountTable::Insert(Account* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Account:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Account::TableID, record);
		}
		return true;
	}
	void AccountTable::BatchInsert(std::vector<mdb::Account*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Account::Allocate();
				memcpy(newRecord, record, sizeof(Account));
				primaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Account::TableID, dbRecords);
		}
		delete records;
	}
	void AccountTable::Erase(Account* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Account::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool AccountTable::Update(Account* const oldRecord, Account* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Account:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Account:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Account));

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Account::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void AccountTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
	}
	void AccountTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Account::TableID);
		}
	}
	void AccountTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Account.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "AccountID,AccountName,AccountType,AccountStatus,Password,TradeGroupID,RiskGroupID,CommissionGroupID\n");
		char buff[4096] = { 0 };
		set<Account*, AccountLessForAccountPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void AccountTable::EraseUniqueKey(Account* record)
	{
		primaryKey->Erase(record);
	}
	void AccountTable::EraseIndex(Account* record)
	{
	}

	CapitalTable::CapitalTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new CapitalPrimaryKey(this);
		tradingDayIndex = new CapitalIndexTradingDay(this);
	}
	CapitalTable::~CapitalTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete tradingDayIndex;
		tradingDayIndex = nullptr;
	}
	void CapitalTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void CapitalTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void CapitalTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void CapitalTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void CapitalTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Capital::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Capital::Allocate();
				memcpy(record, *it, sizeof(Capital));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Capital::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool CapitalTable::Insert(Capital* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Capital:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		tradingDayIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Capital::TableID, record);
		}
		return true;
	}
	void CapitalTable::BatchInsert(std::vector<mdb::Capital*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Capital::Allocate();
				memcpy(newRecord, record, sizeof(Capital));
				primaryKey->Insert(newRecord);

				tradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Capital::TableID, dbRecords);
		}
		delete records;
	}
	void CapitalTable::Erase(Capital* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Capital::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int CapitalTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		tradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Capital*> records;
		std::lock_guard guard(sharedMutex);
		auto range = tradingDayIndex->index.equal_range(&CompareCapital);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Capital::Allocate();
			memcpy(record, &CompareCapital, sizeof(Capital));
			mdbSubscriber->OnRecordEraseByIndex(Capital::TableID, CapitalIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool CapitalTable::Update(Capital* const oldRecord, Capital* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Capital:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Capital:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradingDayIndexUpdate = tradingDayIndex->NeedUpdate(oldRecord, newRecord);
		CapitalIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = tradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Capital));
		if (TradingDayIndexUpdate)
		{
			tradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Capital::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void CapitalTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradingDayIndex->index.clear();
	}
	void CapitalTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradingDayIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Capital::TableID);
		}
	}
	void CapitalTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Capital.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountID,AccountType,Balance,PreBalance,Available,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,Deposit,Withdraw\n");
		char buff[4096] = { 0 };
		set<Capital*, CapitalLessForCapitalPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void CapitalTable::EraseUniqueKey(Capital* record)
	{
		primaryKey->Erase(record);
	}
	void CapitalTable::EraseIndex(Capital* record)
	{
		tradingDayIndex->Erase(record);
	}

	PositionTable::PositionTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new PositionPrimaryKey(this);
		accountIndex = new PositionIndexAccount(this);
		tradingDayIndex = new PositionIndexTradingDay(this);
	}
	PositionTable::~PositionTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete accountIndex;
		accountIndex = nullptr;
		delete tradingDayIndex;
		tradingDayIndex = nullptr;
	}
	void PositionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void PositionTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void PositionTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void PositionTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void PositionTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Position::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Position::Allocate();
				memcpy(record, *it, sizeof(Position));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Position::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool PositionTable::Insert(Position* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Position:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		accountIndex->Insert(record);
		tradingDayIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Position::TableID, record);
		}
		return true;
	}
	void PositionTable::BatchInsert(std::vector<mdb::Position*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Position::Allocate();
				memcpy(newRecord, record, sizeof(Position));
				primaryKey->Insert(newRecord);

				accountIndex->Insert(newRecord);
				tradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Position::TableID, dbRecords);
		}
		delete records;
	}
	void PositionTable::Erase(Position* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Position::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PositionTable::EraseByAccountIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		accountIndex->FillCompareRecord(TradingDay, AccountID);
		std::vector<Position*> records;
		std::lock_guard guard(sharedMutex);
		auto range = accountIndex->index.equal_range(&ComparePosition);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &ComparePosition, sizeof(Position));
			mdbSubscriber->OnRecordEraseByIndex(Position::TableID, PositionIndexAccount::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PositionTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		tradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Position*> records;
		std::lock_guard guard(sharedMutex);
		auto range = tradingDayIndex->index.equal_range(&ComparePosition);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &ComparePosition, sizeof(Position));
			mdbSubscriber->OnRecordEraseByIndex(Position::TableID, PositionIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PositionTable::Update(Position* const oldRecord, Position* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Position:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Position:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIndexUpdate = accountIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexAccount::iterator itAccount;
		if (AccountIndexUpdate)
		{
			itAccount = accountIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = tradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = tradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Position));
		if (AccountIndexUpdate)
		{
			accountIndex->Update(itAccount);
		}
		if (TradingDayIndexUpdate)
		{
			tradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Position::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PositionTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		accountIndex->index.clear();
		tradingDayIndex->index.clear();
	}
	void PositionTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		accountIndex->index.clear();
		tradingDayIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Position::TableID);
		}
	}
	void PositionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Position.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountID,AccountType,ExchangeID,InstrumentID,ProductClass,PosiDirection,TotalPosition,PositionFrozen,TodayPosition,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice\n");
		char buff[4096] = { 0 };
		set<Position*, PositionLessForPositionPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void PositionTable::EraseUniqueKey(Position* record)
	{
		primaryKey->Erase(record);
	}
	void PositionTable::EraseIndex(Position* record)
	{
		accountIndex->Erase(record);
		tradingDayIndex->Erase(record);
	}

	PositionDetailTable::PositionDetailTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new PositionDetailPrimaryKey(this);
		tradeMatchIndex = new PositionDetailIndexTradeMatch(this);
		tradingDayIndex = new PositionDetailIndexTradingDay(this);
	}
	PositionDetailTable::~PositionDetailTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete tradeMatchIndex;
		tradeMatchIndex = nullptr;
		delete tradingDayIndex;
		tradingDayIndex = nullptr;
	}
	void PositionDetailTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void PositionDetailTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void PositionDetailTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void PositionDetailTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void PositionDetailTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(PositionDetail::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = PositionDetail::Allocate();
				memcpy(record, *it, sizeof(PositionDetail));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(PositionDetail::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool PositionDetailTable::Insert(PositionDetail* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PositionDetail:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		tradeMatchIndex->Insert(record);
		tradingDayIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(PositionDetail::TableID, record);
		}
		return true;
	}
	void PositionDetailTable::BatchInsert(std::vector<mdb::PositionDetail*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PositionDetail::Allocate();
				memcpy(newRecord, record, sizeof(PositionDetail));
				primaryKey->Insert(newRecord);

				tradeMatchIndex->Insert(newRecord);
				tradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(PositionDetail::TableID, dbRecords);
		}
		delete records;
	}
	void PositionDetailTable::Erase(PositionDetail* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(PositionDetail::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PositionDetailTable::EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		tradeMatchIndex->FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::vector<PositionDetail*> records;
		std::lock_guard guard(sharedMutex);
		auto range = tradeMatchIndex->index.equal_range(&ComparePositionDetail);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &ComparePositionDetail, sizeof(PositionDetail));
			mdbSubscriber->OnRecordEraseByIndex(PositionDetail::TableID, PositionDetailIndexTradeMatch::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PositionDetailTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		tradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<PositionDetail*> records;
		std::lock_guard guard(sharedMutex);
		auto range = tradingDayIndex->index.equal_range(&ComparePositionDetail);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &ComparePositionDetail, sizeof(PositionDetail));
			mdbSubscriber->OnRecordEraseByIndex(PositionDetail::TableID, PositionDetailIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PositionDetailTable::Update(PositionDetail* const oldRecord, PositionDetail* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PositionDetail:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PositionDetail:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradeMatchIndexUpdate = tradeMatchIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradeMatch::iterator itTradeMatch;
		if (TradeMatchIndexUpdate)
		{
			itTradeMatch = tradeMatchIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = tradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = tradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PositionDetail));
		if (TradeMatchIndexUpdate)
		{
			tradeMatchIndex->Update(itTradeMatch);
		}
		if (TradingDayIndexUpdate)
		{
			tradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(PositionDetail::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PositionDetailTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradeMatchIndex->index.clear();
		tradingDayIndex->index.clear();
	}
	void PositionDetailTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		tradeMatchIndex->index.clear();
		tradingDayIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(PositionDetail::TableID);
		}
	}
	void PositionDetailTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_PositionDetail.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountID,AccountType,ExchangeID,InstrumentID,ProductClass,PosiDirection,OpenDate,TradeID,Volume,OpenPrice,MarketValue,CashIn,CashOut,Margin,Commission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice,CloseVolume,CloseAmount\n");
		char buff[4096] = { 0 };
		set<PositionDetail*, PositionDetailLessForPositionDetailPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void PositionDetailTable::EraseUniqueKey(PositionDetail* record)
	{
		primaryKey->Erase(record);
	}
	void PositionDetailTable::EraseIndex(PositionDetail* record)
	{
		tradeMatchIndex->Erase(record);
		tradingDayIndex->Erase(record);
	}

	OrderTable::OrderTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new OrderPrimaryKey(this);
		clientOrderIDUniqueKey = new OrderUniqueKeyClientOrderID(this);
		accountIDIndex = new OrderIndexAccountID(this);
	}
	OrderTable::~OrderTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete clientOrderIDUniqueKey;
		clientOrderIDUniqueKey = nullptr;
		delete accountIDIndex;
		accountIDIndex = nullptr;
	}
	void OrderTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void OrderTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void OrderTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void OrderTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void OrderTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Order::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Order::Allocate();
				memcpy(record, *it, sizeof(Order));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Order::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool OrderTable::Insert(Order* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record) || !(clientOrderIDUniqueKey->CheckInsert(record)))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Order:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);
		clientOrderIDUniqueKey->Insert(record);

		accountIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Order::TableID, record);
		}
		return true;
	}
	void OrderTable::BatchInsert(std::vector<mdb::Order*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Order::Allocate();
				memcpy(newRecord, record, sizeof(Order));
				primaryKey->Insert(newRecord);
				clientOrderIDUniqueKey->Insert(newRecord);

				accountIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Order::TableID, dbRecords);
		}
		delete records;
	}
	void OrderTable::Erase(Order* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Order::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int OrderTable::EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		accountIDIndex->FillCompareRecord(TradingDay, AccountID);
		std::vector<Order*> records;
		std::lock_guard guard(sharedMutex);
		auto range = accountIDIndex->index.equal_range(&CompareOrder);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Order::Allocate();
			memcpy(record, &CompareOrder, sizeof(Order));
			mdbSubscriber->OnRecordEraseByIndex(Order::TableID, OrderIndexAccountID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool OrderTable::Update(Order* const oldRecord, Order* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord) || !(clientOrderIDUniqueKey->CheckUpdate(oldRecord, newRecord)))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Order:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Order:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIDIndexUpdate = accountIDIndex->NeedUpdate(oldRecord, newRecord);
		OrderIndexAccountID::iterator itAccountID;
		if (AccountIDIndexUpdate)
		{
			itAccountID = accountIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Order));
		if (AccountIDIndexUpdate)
		{
			accountIDIndex->Update(itAccountID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Order::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void OrderTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		clientOrderIDUniqueKey->index.clear();
		accountIDIndex->index.clear();
	}
	void OrderTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		clientOrderIDUniqueKey->index.clear();
		accountIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Order::TableID);
		}
	}
	void OrderTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Order.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountID,AccountType,ExchangeID,InstrumentID,ProductClass,OrderID,OrderSysID,Direction,OffsetFlag,OrderPriceType,Price,Volume,VolumeTotal,VolumeTraded,VolumeMultiple,OrderStatus,OrderDate,OrderTime,CancelDate,CancelTime,SessionID,ClientOrderID,RequestID,OfferID,TradeGroupID,RiskGroupID,CommissionGroupID,FrozenCash,FrozenMargin,FrozenCommission,RebuildMark,IsForceClose\n");
		char buff[4096] = { 0 };
		set<Order*, OrderLessForOrderPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void OrderTable::EraseUniqueKey(Order* record)
	{
		primaryKey->Erase(record);
		clientOrderIDUniqueKey->Erase(record);
	}
	void OrderTable::EraseIndex(Order* record)
	{
		accountIDIndex->Erase(record);
	}

	TradeTable::TradeTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new TradePrimaryKey(this);
		accountIDIndex = new TradeIndexAccountID(this);
	}
	TradeTable::~TradeTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete accountIDIndex;
		accountIDIndex = nullptr;
	}
	void TradeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void TradeTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void TradeTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void TradeTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void TradeTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(Trade::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = Trade::Allocate();
				memcpy(record, *it, sizeof(Trade));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(Trade::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool TradeTable::Insert(Trade* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Trade:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		accountIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(Trade::TableID, record);
		}
		return true;
	}
	void TradeTable::BatchInsert(std::vector<mdb::Trade*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Trade::Allocate();
				memcpy(newRecord, record, sizeof(Trade));
				primaryKey->Insert(newRecord);

				accountIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(Trade::TableID, dbRecords);
		}
		delete records;
	}
	void TradeTable::Erase(Trade* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(Trade::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int TradeTable::EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		accountIDIndex->FillCompareRecord(TradingDay, AccountID);
		std::vector<Trade*> records;
		std::lock_guard guard(sharedMutex);
		auto range = accountIDIndex->index.equal_range(&CompareTrade);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = Trade::Allocate();
			memcpy(record, &CompareTrade, sizeof(Trade));
			mdbSubscriber->OnRecordEraseByIndex(Trade::TableID, TradeIndexAccountID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool TradeTable::Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Trade:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Trade:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIDIndexUpdate = accountIDIndex->NeedUpdate(oldRecord, newRecord);
		TradeIndexAccountID::iterator itAccountID;
		if (AccountIDIndexUpdate)
		{
			itAccountID = accountIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Trade));
		if (AccountIDIndexUpdate)
		{
			accountIDIndex->Update(itAccountID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(Trade::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void TradeTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		accountIDIndex->index.clear();
	}
	void TradeTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		accountIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(Trade::TableID);
		}
	}
	void TradeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_Trade.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountID,AccountType,ExchangeID,InstrumentID,ProductClass,OrderID,OrderSysID,TradeID,Direction,OffsetFlag,Price,Volume,VolumeMultiple,TradeAmount,Commission,TradeDate,TradeTime\n");
		char buff[4096] = { 0 };
		set<Trade*, TradeLessForTradePrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void TradeTable::EraseUniqueKey(Trade* record)
	{
		primaryKey->Erase(record);
	}
	void TradeTable::EraseIndex(Trade* record)
	{
		accountIDIndex->Erase(record);
	}

	AccountLoginSessionTable::AccountLoginSessionTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new AccountLoginSessionPrimaryKey(this);
		sessionIDIndex = new AccountLoginSessionIndexSessionID(this);
		accountIDIndex = new AccountLoginSessionIndexAccountID(this);
	}
	AccountLoginSessionTable::~AccountLoginSessionTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete sessionIDIndex;
		sessionIDIndex = nullptr;
		delete accountIDIndex;
		accountIDIndex = nullptr;
	}
	void AccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void AccountLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void AccountLoginSessionTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void AccountLoginSessionTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void AccountLoginSessionTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(AccountLoginSession::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = AccountLoginSession::Allocate();
				memcpy(record, *it, sizeof(AccountLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(AccountLoginSession::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool AccountLoginSessionTable::Insert(AccountLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for AccountLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		sessionIDIndex->Insert(record);
		accountIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(AccountLoginSession::TableID, record);
		}
		return true;
	}
	void AccountLoginSessionTable::BatchInsert(std::vector<mdb::AccountLoginSession*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = AccountLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(AccountLoginSession));
				primaryKey->Insert(newRecord);

				sessionIDIndex->Insert(newRecord);
				accountIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(AccountLoginSession::TableID, dbRecords);
		}
		delete records;
	}
	void AccountLoginSessionTable::Erase(AccountLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(AccountLoginSession::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int AccountLoginSessionTable::EraseBySessionIDIndex(const SessionIDType& SessionID)
	{
		sessionIDIndex->FillCompareRecord(SessionID);
		std::vector<AccountLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = sessionIDIndex->index.equal_range(&CompareAccountLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = AccountLoginSession::Allocate();
			memcpy(record, &CompareAccountLoginSession, sizeof(AccountLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(AccountLoginSession::TableID, AccountLoginSessionIndexSessionID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int AccountLoginSessionTable::EraseByAccountIDIndex(const AccountIDType& AccountID)
	{
		accountIDIndex->FillCompareRecord(AccountID);
		std::vector<AccountLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = accountIDIndex->index.equal_range(&CompareAccountLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = AccountLoginSession::Allocate();
			memcpy(record, &CompareAccountLoginSession, sizeof(AccountLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(AccountLoginSession::TableID, AccountLoginSessionIndexAccountID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool AccountLoginSessionTable::Update(AccountLoginSession* const oldRecord, AccountLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for AccountLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New AccountLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIDIndexUpdate = sessionIDIndex->NeedUpdate(oldRecord, newRecord);
		AccountLoginSessionIndexSessionID::iterator itSessionID;
		if (SessionIDIndexUpdate)
		{
			itSessionID = sessionIDIndex->FindNode(oldRecord);
		}
		bool AccountIDIndexUpdate = accountIDIndex->NeedUpdate(oldRecord, newRecord);
		AccountLoginSessionIndexAccountID::iterator itAccountID;
		if (AccountIDIndexUpdate)
		{
			itAccountID = accountIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(AccountLoginSession));
		if (SessionIDIndexUpdate)
		{
			sessionIDIndex->Update(itSessionID);
		}
		if (AccountIDIndexUpdate)
		{
			accountIDIndex->Update(itAccountID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(AccountLoginSession::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void AccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		accountIDIndex->index.clear();
	}
	void AccountLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		accountIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(AccountLoginSession::TableID);
		}
	}
	void AccountLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_AccountLoginSession.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "AccountID,SessionID,IPAddress\n");
		char buff[4096] = { 0 };
		set<AccountLoginSession*, AccountLoginSessionLessForAccountLoginSessionPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void AccountLoginSessionTable::EraseUniqueKey(AccountLoginSession* record)
	{
		primaryKey->Erase(record);
	}
	void AccountLoginSessionTable::EraseIndex(AccountLoginSession* record)
	{
		sessionIDIndex->Erase(record);
		accountIDIndex->Erase(record);
	}

	PrimaryAccountLoginSessionTable::PrimaryAccountLoginSessionTable()
	{
		mdbSubscriber = nullptr;
		primaryKey = new PrimaryAccountLoginSessionPrimaryKey(this);
		sessionIDIndex = new PrimaryAccountLoginSessionIndexSessionID(this);
		primaryAccountIDIndex = new PrimaryAccountLoginSessionIndexPrimaryAccountID(this);
	}
	PrimaryAccountLoginSessionTable::~PrimaryAccountLoginSessionTable()
	{
		delete primaryKey;
		primaryKey = nullptr;
		delete sessionIDIndex;
		sessionIDIndex = nullptr;
		delete primaryAccountIDIndex;
		primaryAccountIDIndex = nullptr;
	}
	void PrimaryAccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber = subscriber;
	}
	void PrimaryAccountLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber = nullptr;
	}
	void PrimaryAccountLoginSessionTable::LockShared()
	{
		sharedMutex.lock_shared();
	}
	void PrimaryAccountLoginSessionTable::UnlockShared()
	{
		sharedMutex.unlock_shared();
	}
	void PrimaryAccountLoginSessionTable::InitDB()
	{
		if (mdbSubscriber == nullptr)
		{
			dbInited = true;
			return;
		}
		mdbSubscriber->OnRecordTruncate(PrimaryAccountLoginSession::TableID);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(sharedMutex);
			for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
			{
				auto record = PrimaryAccountLoginSession::Allocate();
				memcpy(record, *it, sizeof(PrimaryAccountLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber->OnRecordBatchInsert(PrimaryAccountLoginSession::TableID, records);
		}
		else
		{
			delete records;
		}
		dbInited = true;
	}
	bool PrimaryAccountLoginSessionTable::Insert(PrimaryAccountLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PrimaryAccountLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		primaryKey->Insert(record);

		sessionIDIndex->Insert(record);
		primaryAccountIDIndex->Insert(record);
		
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordInsert(PrimaryAccountLoginSession::TableID, record);
		}
		return true;
	}
	void PrimaryAccountLoginSessionTable::BatchInsert(std::vector<mdb::PrimaryAccountLoginSession*>* records)
	{
		{
			std::lock_guard guard(sharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PrimaryAccountLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(PrimaryAccountLoginSession));
				primaryKey->Insert(newRecord);

				sessionIDIndex->Insert(newRecord);
				primaryAccountIDIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber->OnRecordBatchInsert(PrimaryAccountLoginSession::TableID, dbRecords);
		}
		delete records;
	}
	void PrimaryAccountLoginSessionTable::Erase(PrimaryAccountLoginSession* record)
	{
		std::lock_guard guard(sharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordErase(PrimaryAccountLoginSession::TableID, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PrimaryAccountLoginSessionTable::EraseBySessionIDIndex(const SessionIDType& SessionID)
	{
		sessionIDIndex->FillCompareRecord(SessionID);
		std::vector<PrimaryAccountLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = sessionIDIndex->index.equal_range(&ComparePrimaryAccountLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = PrimaryAccountLoginSession::Allocate();
			memcpy(record, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(PrimaryAccountLoginSession::TableID, PrimaryAccountLoginSessionIndexSessionID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PrimaryAccountLoginSessionTable::EraseByPrimaryAccountIDIndex(const AccountIDType& PrimaryAccountID)
	{
		primaryAccountIDIndex->FillCompareRecord(PrimaryAccountID);
		std::vector<PrimaryAccountLoginSession*> records;
		std::lock_guard guard(sharedMutex);
		auto range = primaryAccountIDIndex->index.equal_range(&ComparePrimaryAccountLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Deallocate();
		}
		if (mdbSubscriber != nullptr && dbInited)
		{
			auto record = PrimaryAccountLoginSession::Allocate();
			memcpy(record, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
			mdbSubscriber->OnRecordEraseByIndex(PrimaryAccountLoginSession::TableID, PrimaryAccountLoginSessionIndexPrimaryAccountID::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountLoginSessionTable::Update(PrimaryAccountLoginSession* const oldRecord, PrimaryAccountLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(sharedMutex);
		if (!primaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccountLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PrimaryAccountLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIDIndexUpdate = sessionIDIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountLoginSessionIndexSessionID::iterator itSessionID;
		if (SessionIDIndexUpdate)
		{
			itSessionID = sessionIDIndex->FindNode(oldRecord);
		}
		bool PrimaryAccountIDIndexUpdate = primaryAccountIDIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator itPrimaryAccountID;
		if (PrimaryAccountIDIndexUpdate)
		{
			itPrimaryAccountID = primaryAccountIDIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PrimaryAccountLoginSession));
		if (SessionIDIndexUpdate)
		{
			sessionIDIndex->Update(itSessionID);
		}
		if (PrimaryAccountIDIndexUpdate)
		{
			primaryAccountIDIndex->Update(itPrimaryAccountID);
		}

		if (updateDB && mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordUpdate(PrimaryAccountLoginSession::TableID, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PrimaryAccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		primaryAccountIDIndex->index.clear();
	}
	void PrimaryAccountLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			(*it)->Deallocate();
		}
		primaryKey->index.clear();
		sessionIDIndex->index.clear();
		primaryAccountIDIndex->index.clear();
		if (mdbSubscriber != nullptr && dbInited)
		{
			mdbSubscriber->OnRecordTruncate(PrimaryAccountLoginSession::TableID);
		}
	}
	void PrimaryAccountLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_PrimaryAccountLoginSession.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "PrimaryAccountID,SessionID,IPAddress\n");
		char buff[4096] = { 0 };
		set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountLoginSessionPrimaryKey> records;
		std::shared_lock guard(sharedMutex);
		for (auto it = primaryKey->index.begin(); it != primaryKey->index.end(); ++it)
		{
			records.insert(*it);
		}
		for (auto record : records)
		{
			fprintf(dumpFile, "%s\n", record->GetString());
		}
		records.clear();
		fclose(dumpFile);
	}
	void PrimaryAccountLoginSessionTable::EraseUniqueKey(PrimaryAccountLoginSession* record)
	{
		primaryKey->Erase(record);
	}
	void PrimaryAccountLoginSessionTable::EraseIndex(PrimaryAccountLoginSession* record)
	{
		sessionIDIndex->Erase(record);
		primaryAccountIDIndex->Erase(record);
	}

}

