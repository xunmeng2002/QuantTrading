// 本文件由 ../Templates/Cpp/Mdb/MdbTables.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbTables.h"
#include <Spark/Core/Logger/Logger.h>
#include <string>
#include <cstring>
#include <set>
#include <vector>

using std::string;
using std::set;
using namespace Spark::Core;

namespace QuantTrading
{
	TradingDayTable::TradingDayTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new TradingDayPrimaryKey(this);
	}
	TradingDayTable::~TradingDayTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void TradingDayTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void TradingDayTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void TradingDayTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void TradingDayTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void TradingDayTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(TradingDay::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = TradingDay::Allocate();
				memcpy(record, *it, sizeof(TradingDay));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(TradingDay::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool TradingDayTable::Insert(TradingDay* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for TradingDay:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(TradingDay::TableId, record);
		}
		return true;
	}
	void TradingDayTable::BatchInsert(std::vector<TradingDay*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = TradingDay::Allocate();
				memcpy(newRecord, record, sizeof(TradingDay));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(TradingDay::TableId, dbRecords);
		}
		delete records;
	}
	void TradingDayTable::Erase(TradingDay* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(TradingDay::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool TradingDayTable::Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for TradingDay:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New TradingDay:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(TradingDay));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(TradingDay::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void TradingDayTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void TradingDayTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(TradingDay::TableId);
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

		fprintf(dumpFile, "Pk,CurrTradingDay,PreTradingDay\n");
		char buff[4096] = { 0 };
		set<TradingDay*, TradingDayLessForTradingDayPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void TradingDayTable::EraseIndex(TradingDay* record)
	{
	}

	ExchangeTable::ExchangeTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new ExchangePrimaryKey(this);
	}
	ExchangeTable::~ExchangeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void ExchangeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void ExchangeTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void ExchangeTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void ExchangeTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void ExchangeTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Exchange::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Exchange::Allocate();
				memcpy(record, *it, sizeof(Exchange));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Exchange::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool ExchangeTable::Insert(Exchange* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Exchange:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Exchange::TableId, record);
		}
		return true;
	}
	void ExchangeTable::BatchInsert(std::vector<Exchange*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Exchange::Allocate();
				memcpy(newRecord, record, sizeof(Exchange));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Exchange::TableId, dbRecords);
		}
		delete records;
	}
	void ExchangeTable::Erase(Exchange* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Exchange::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool ExchangeTable::Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Exchange:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Exchange:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Exchange));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Exchange::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void ExchangeTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void ExchangeTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Exchange::TableId);
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

		fprintf(dumpFile, "ExchangeId,ExchangeName\n");
		char buff[4096] = { 0 };
		set<Exchange*, ExchangeLessForExchangePrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void ExchangeTable::EraseIndex(Exchange* record)
	{
	}

	ProductTable::ProductTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new ProductPrimaryKey(this);
	}
	ProductTable::~ProductTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void ProductTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void ProductTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void ProductTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void ProductTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void ProductTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Product::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Product::Allocate();
				memcpy(record, *it, sizeof(Product));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Product::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool ProductTable::Insert(Product* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Product:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Product::TableId, record);
		}
		return true;
	}
	void ProductTable::BatchInsert(std::vector<Product*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Product::Allocate();
				memcpy(newRecord, record, sizeof(Product));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Product::TableId, dbRecords);
		}
		delete records;
	}
	void ProductTable::Erase(Product* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Product::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool ProductTable::Update(Product* const oldRecord, Product* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Product:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Product:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Product));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Product::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void ProductTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void ProductTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Product::TableId);
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

		fprintf(dumpFile, "ExchangeId,ProductId,ProductName,ProductClass,VolumeMultiple,PriceTick,MaxMarketOrderVolume,MinMarketOrderVolume,MaxLimitOrderVolume,MinLimitOrderVolume,SessionName\n");
		char buff[4096] = { 0 };
		set<Product*, ProductLessForProductPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void ProductTable::EraseIndex(Product* record)
	{
	}

	HotInstrumentTable::HotInstrumentTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new HotInstrumentPrimaryKey(this);
		TradingDayIndex = new HotInstrumentIndexTradingDay(this);
	}
	HotInstrumentTable::~HotInstrumentTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	void HotInstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void HotInstrumentTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void HotInstrumentTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void HotInstrumentTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void HotInstrumentTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(HotInstrument::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = HotInstrument::Allocate();
				memcpy(record, *it, sizeof(HotInstrument));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(HotInstrument::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool HotInstrumentTable::Insert(HotInstrument* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for HotInstrument:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		TradingDayIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(HotInstrument::TableId, record);
		}
		return true;
	}
	void HotInstrumentTable::BatchInsert(std::vector<HotInstrument*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = HotInstrument::Allocate();
				memcpy(newRecord, record, sizeof(HotInstrument));
				PrimaryKey->Insert(newRecord);

				TradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(HotInstrument::TableId, dbRecords);
		}
		delete records;
	}
	void HotInstrumentTable::Erase(HotInstrument* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(HotInstrument::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int HotInstrumentTable::EraseByTradingDayIndex(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		TradingDayIndex->FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::vector<HotInstrument*> records;
		std::lock_guard guard(SharedMutex);
		auto range = TradingDayIndex->index_.equal_range(&CompareHotInstrument);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = HotInstrument::Allocate();
			memcpy(record, &CompareHotInstrument, sizeof(HotInstrument));
			mdbSubscriber_->OnRecordEraseByIndex(HotInstrument::TableId, HotInstrumentIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool HotInstrumentTable::Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for HotInstrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New HotInstrument:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		HotInstrumentIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(HotInstrument));
		if (TradingDayIndexUpdate)
		{
			TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(HotInstrument::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void HotInstrumentTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradingDayIndex->index_.clear();
	}
	void HotInstrumentTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradingDayIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(HotInstrument::TableId);
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

		fprintf(dumpFile, "TradingDay,ExchangeId,ProductId,InstrumentId,ProductClass,Volume,MaxVolume,Turnover,MaxTurnover,OpenInterest,MaxOpenInterest,Rank\n");
		char buff[4096] = { 0 };
		set<HotInstrument*, HotInstrumentLessForHotInstrumentPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void HotInstrumentTable::EraseIndex(HotInstrument* record)
	{
		TradingDayIndex->Erase(record);
	}

	InstrumentTable::InstrumentTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new InstrumentPrimaryKey(this);
		ExchangeIdIndex = new InstrumentIndexExchangeId(this);
	}
	InstrumentTable::~InstrumentTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete ExchangeIdIndex;
		ExchangeIdIndex = nullptr;
	}
	void InstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void InstrumentTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void InstrumentTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void InstrumentTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void InstrumentTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Instrument::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Instrument::Allocate();
				memcpy(record, *it, sizeof(Instrument));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Instrument::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool InstrumentTable::Insert(Instrument* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Instrument:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		ExchangeIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Instrument::TableId, record);
		}
		return true;
	}
	void InstrumentTable::BatchInsert(std::vector<Instrument*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Instrument::Allocate();
				memcpy(newRecord, record, sizeof(Instrument));
				PrimaryKey->Insert(newRecord);

				ExchangeIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Instrument::TableId, dbRecords);
		}
		delete records;
	}
	void InstrumentTable::Erase(Instrument* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Instrument::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int InstrumentTable::EraseByExchangeIdIndex(const ExchangeIdType& ExchangeId)
	{
		ExchangeIdIndex->FillCompareRecord(ExchangeId);
		std::vector<Instrument*> records;
		std::lock_guard guard(SharedMutex);
		auto range = ExchangeIdIndex->index_.equal_range(&CompareInstrument);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Instrument::Allocate();
			memcpy(record, &CompareInstrument, sizeof(Instrument));
			mdbSubscriber_->OnRecordEraseByIndex(Instrument::TableId, InstrumentIndexExchangeId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool InstrumentTable::Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Instrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Instrument:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool ExchangeIdIndexUpdate = ExchangeIdIndex->NeedUpdate(oldRecord, newRecord);
		InstrumentIndexExchangeId::iterator itExchangeId;
		if (ExchangeIdIndexUpdate)
		{
			itExchangeId = ExchangeIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Instrument));
		if (ExchangeIdIndexUpdate)
		{
			ExchangeIdIndex->Update(itExchangeId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Instrument::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void InstrumentTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		ExchangeIdIndex->index_.clear();
	}
	void InstrumentTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		ExchangeIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Instrument::TableId);
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

		fprintf(dumpFile, "ExchangeId,InstrumentId,ExchangeInstId,InstrumentName,ProductId,ProductClass,InstrumentClass,Rank,VolumeMultiple,PriceTick,MaxMarketOrderVolume,MinMarketOrderVolume,MaxLimitOrderVolume,MinLimitOrderVolume,SessionName\n");
		char buff[4096] = { 0 };
		set<Instrument*, InstrumentLessForInstrumentPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void InstrumentTable::EraseIndex(Instrument* record)
	{
		ExchangeIdIndex->Erase(record);
	}

	DepthMarketDataTable::DepthMarketDataTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new DepthMarketDataPrimaryKey(this);
	}
	DepthMarketDataTable::~DepthMarketDataTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void DepthMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void DepthMarketDataTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void DepthMarketDataTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void DepthMarketDataTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void DepthMarketDataTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(DepthMarketData::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = DepthMarketData::Allocate();
				memcpy(record, *it, sizeof(DepthMarketData));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(DepthMarketData::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool DepthMarketDataTable::Insert(DepthMarketData* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for DepthMarketData:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(DepthMarketData::TableId, record);
		}
		return true;
	}
	void DepthMarketDataTable::BatchInsert(std::vector<DepthMarketData*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = DepthMarketData::Allocate();
				memcpy(newRecord, record, sizeof(DepthMarketData));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(DepthMarketData::TableId, dbRecords);
		}
		delete records;
	}
	void DepthMarketDataTable::Erase(DepthMarketData* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(DepthMarketData::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool DepthMarketDataTable::Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for DepthMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New DepthMarketData:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(DepthMarketData));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(DepthMarketData::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void DepthMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void DepthMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(DepthMarketData::TableId);
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

		fprintf(dumpFile, "TradingDay,ExchangeId,InstrumentId,UpdateTs,LastPrice,PreSettlementPrice,PreClosePrice,PreOpenInterest,OpenPrice,HighestPrice,LowestPrice,ClosePrice,CurrVolume,Volume,CurrTurnover,Turnover,OpenInterest,SettlementPrice,UpperLimitPrice,LowerLimitPrice,AveragePrice,AskPrice1,AskPrice2,AskPrice3,AskPrice4,AskPrice5,AskPrice6,AskPrice7,AskPrice8,AskPrice9,AskPrice10,AskVolume1,AskVolume2,AskVolume3,AskVolume4,AskVolume5,AskVolume6,AskVolume7,AskVolume8,AskVolume9,AskVolume10,BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,BidPrice6,BidPrice7,BidPrice8,BidPrice9,BidPrice10,BidVolume1,BidVolume2,BidVolume3,BidVolume4,BidVolume5,BidVolume6,BidVolume7,BidVolume8,BidVolume9,BidVolume10\n");
		char buff[4096] = { 0 };
		set<DepthMarketData*, DepthMarketDataLessForDepthMarketDataPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void DepthMarketDataTable::EraseIndex(DepthMarketData* record)
	{
	}

	BarMarketDataTable::BarMarketDataTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new BarMarketDataPrimaryKey(this);
	}
	BarMarketDataTable::~BarMarketDataTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void BarMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void BarMarketDataTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void BarMarketDataTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void BarMarketDataTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void BarMarketDataTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(BarMarketData::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = BarMarketData::Allocate();
				memcpy(record, *it, sizeof(BarMarketData));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(BarMarketData::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool BarMarketDataTable::Insert(BarMarketData* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for BarMarketData:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(BarMarketData::TableId, record);
		}
		return true;
	}
	void BarMarketDataTable::BatchInsert(std::vector<BarMarketData*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = BarMarketData::Allocate();
				memcpy(newRecord, record, sizeof(BarMarketData));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(BarMarketData::TableId, dbRecords);
		}
		delete records;
	}
	void BarMarketDataTable::Erase(BarMarketData* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(BarMarketData::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool BarMarketDataTable::Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for BarMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New BarMarketData:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(BarMarketData));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(BarMarketData::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void BarMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void BarMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(BarMarketData::TableId);
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

		fprintf(dumpFile, "TradingDay,ExchangeId,InstrumentId,BarPreces,BarPeriod,BarTime,UpdateTs,PreSettlementPrice,PreClosePrice,HighestPrice,LowestPrice,Open,High,Low,Close,CurrVolume,Volume,CurrTurnover,Turnover,OpenInterest\n");
		char buff[4096] = { 0 };
		set<BarMarketData*, BarMarketDataLessForBarMarketDataPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void BarMarketDataTable::EraseIndex(BarMarketData* record)
	{
	}

	MdSubscribeTable::MdSubscribeTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new MdSubscribePrimaryKey(this);
	}
	MdSubscribeTable::~MdSubscribeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void MdSubscribeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void MdSubscribeTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void MdSubscribeTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void MdSubscribeTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void MdSubscribeTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(MdSubscribe::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = MdSubscribe::Allocate();
				memcpy(record, *it, sizeof(MdSubscribe));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(MdSubscribe::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool MdSubscribeTable::Insert(MdSubscribe* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdSubscribe:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(MdSubscribe::TableId, record);
		}
		return true;
	}
	void MdSubscribeTable::BatchInsert(std::vector<MdSubscribe*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdSubscribe::Allocate();
				memcpy(newRecord, record, sizeof(MdSubscribe));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(MdSubscribe::TableId, dbRecords);
		}
		delete records;
	}
	void MdSubscribeTable::Erase(MdSubscribe* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(MdSubscribe::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool MdSubscribeTable::Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdSubscribe:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdSubscribe:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(MdSubscribe));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(MdSubscribe::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdSubscribeTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void MdSubscribeTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(MdSubscribe::TableId);
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

		fprintf(dumpFile, "ExchangeId,InstrumentId,RealInstrumentId,ProductId,ProductClass,StartTradingDay,EndTradingDay\n");
		char buff[4096] = { 0 };
		set<MdSubscribe*, MdSubscribeLessForMdSubscribePrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void MdSubscribeTable::EraseIndex(MdSubscribe* record)
	{
	}

	MdUserTable::MdUserTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new MdUserPrimaryKey(this);
	}
	MdUserTable::~MdUserTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void MdUserTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void MdUserTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void MdUserTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void MdUserTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void MdUserTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(MdUser::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = MdUser::Allocate();
				memcpy(record, *it, sizeof(MdUser));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(MdUser::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool MdUserTable::Insert(MdUser* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUser:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(MdUser::TableId, record);
		}
		return true;
	}
	void MdUserTable::BatchInsert(std::vector<MdUser*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUser::Allocate();
				memcpy(newRecord, record, sizeof(MdUser));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(MdUser::TableId, dbRecords);
		}
		delete records;
	}
	void MdUserTable::Erase(MdUser* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(MdUser::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool MdUserTable::Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUser:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUser:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(MdUser));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(MdUser::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdUserTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void MdUserTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(MdUser::TableId);
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

		fprintf(dumpFile, "MdUserId,MdUserName,Password\n");
		char buff[4096] = { 0 };
		set<MdUser*, MdUserLessForMdUserPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void MdUserTable::EraseIndex(MdUser* record)
	{
	}

	MdUserLoginSessionTable::MdUserLoginSessionTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new MdUserLoginSessionPrimaryKey(this);
		SessionIdIndex = new MdUserLoginSessionIndexSessionId(this);
		MdUserIdIndex = new MdUserLoginSessionIndexMdUserId(this);
	}
	MdUserLoginSessionTable::~MdUserLoginSessionTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete SessionIdIndex;
		SessionIdIndex = nullptr;
		delete MdUserIdIndex;
		MdUserIdIndex = nullptr;
	}
	void MdUserLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void MdUserLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void MdUserLoginSessionTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void MdUserLoginSessionTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void MdUserLoginSessionTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(MdUserLoginSession::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = MdUserLoginSession::Allocate();
				memcpy(record, *it, sizeof(MdUserLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(MdUserLoginSession::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool MdUserLoginSessionTable::Insert(MdUserLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUserLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		SessionIdIndex->Insert(record);
		MdUserIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(MdUserLoginSession::TableId, record);
		}
		return true;
	}
	void MdUserLoginSessionTable::BatchInsert(std::vector<MdUserLoginSession*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUserLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(MdUserLoginSession));
				PrimaryKey->Insert(newRecord);

				SessionIdIndex->Insert(newRecord);
				MdUserIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(MdUserLoginSession::TableId, dbRecords);
		}
		delete records;
	}
	void MdUserLoginSessionTable::Erase(MdUserLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(MdUserLoginSession::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int MdUserLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<MdUserLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = SessionIdIndex->index_.equal_range(&CompareMdUserLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = MdUserLoginSession::Allocate();
			memcpy(record, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(MdUserLoginSession::TableId, MdUserLoginSessionIndexSessionId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int MdUserLoginSessionTable::EraseByMdUserIdIndex(const UserIdType& MdUserId)
	{
		MdUserIdIndex->FillCompareRecord(MdUserId);
		std::vector<MdUserLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = MdUserIdIndex->index_.equal_range(&CompareMdUserLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = MdUserLoginSession::Allocate();
			memcpy(record, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(MdUserLoginSession::TableId, MdUserLoginSessionIndexMdUserId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool MdUserLoginSessionTable::Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUserLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUserLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(oldRecord, newRecord);
		MdUserLoginSessionIndexSessionId::iterator itSessionId;
		if (SessionIdIndexUpdate)
		{
			itSessionId = SessionIdIndex->FindNode(oldRecord);
		}
		bool MdUserIdIndexUpdate = MdUserIdIndex->NeedUpdate(oldRecord, newRecord);
		MdUserLoginSessionIndexMdUserId::iterator itMdUserId;
		if (MdUserIdIndexUpdate)
		{
			itMdUserId = MdUserIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(MdUserLoginSession));
		if (SessionIdIndexUpdate)
		{
			SessionIdIndex->Update(itSessionId);
		}
		if (MdUserIdIndexUpdate)
		{
			MdUserIdIndex->Update(itMdUserId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(MdUserLoginSession::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void MdUserLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		MdUserIdIndex->index_.clear();
	}
	void MdUserLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		MdUserIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(MdUserLoginSession::TableId);
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

		fprintf(dumpFile, "MdUserId,SessionId,IpAddress\n");
		char buff[4096] = { 0 };
		set<MdUserLoginSession*, MdUserLoginSessionLessForMdUserLoginSessionPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void MdUserLoginSessionTable::EraseIndex(MdUserLoginSession* record)
	{
		SessionIdIndex->Erase(record);
		MdUserIdIndex->Erase(record);
	}

	PrimaryAccountTable::PrimaryAccountTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new PrimaryAccountPrimaryKey(this);
		OfferIdIndex = new PrimaryAccountIndexOfferId(this);
	}
	PrimaryAccountTable::~PrimaryAccountTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete OfferIdIndex;
		OfferIdIndex = nullptr;
	}
	void PrimaryAccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void PrimaryAccountTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void PrimaryAccountTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void PrimaryAccountTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void PrimaryAccountTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(PrimaryAccount::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = PrimaryAccount::Allocate();
				memcpy(record, *it, sizeof(PrimaryAccount));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(PrimaryAccount::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool PrimaryAccountTable::Insert(PrimaryAccount* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PrimaryAccount:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		OfferIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(PrimaryAccount::TableId, record);
		}
		return true;
	}
	void PrimaryAccountTable::BatchInsert(std::vector<PrimaryAccount*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PrimaryAccount::Allocate();
				memcpy(newRecord, record, sizeof(PrimaryAccount));
				PrimaryKey->Insert(newRecord);

				OfferIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(PrimaryAccount::TableId, dbRecords);
		}
		delete records;
	}
	void PrimaryAccountTable::Erase(PrimaryAccount* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(PrimaryAccount::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PrimaryAccountTable::EraseByOfferIdIndex(const OfferIdType& OfferId)
	{
		OfferIdIndex->FillCompareRecord(OfferId);
		std::vector<PrimaryAccount*> records;
		std::lock_guard guard(SharedMutex);
		auto range = OfferIdIndex->index_.equal_range(&ComparePrimaryAccount);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = PrimaryAccount::Allocate();
			memcpy(record, &ComparePrimaryAccount, sizeof(PrimaryAccount));
			mdbSubscriber_->OnRecordEraseByIndex(PrimaryAccount::TableId, PrimaryAccountIndexOfferId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountTable::Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccount:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PrimaryAccount:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool OfferIdIndexUpdate = OfferIdIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountIndexOfferId::iterator itOfferId;
		if (OfferIdIndexUpdate)
		{
			itOfferId = OfferIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PrimaryAccount));
		if (OfferIdIndexUpdate)
		{
			OfferIdIndex->Update(itOfferId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(PrimaryAccount::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PrimaryAccountTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		OfferIdIndex->index_.clear();
	}
	void PrimaryAccountTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		OfferIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(PrimaryAccount::TableId);
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

		fprintf(dumpFile, "PrimaryAccountId,PrimaryAccountName,AccountClass,Password,OfferId,IsAllowLogin,IsSimulateAccount,LoginStatus,InitStatus\n");
		char buff[4096] = { 0 };
		set<PrimaryAccount*, PrimaryAccountLessForPrimaryAccountPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void PrimaryAccountTable::EraseIndex(PrimaryAccount* record)
	{
		OfferIdIndex->Erase(record);
	}

	AccountTable::AccountTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new AccountPrimaryKey(this);
	}
	AccountTable::~AccountTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	void AccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void AccountTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void AccountTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void AccountTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void AccountTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Account::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Account::Allocate();
				memcpy(record, *it, sizeof(Account));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Account::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool AccountTable::Insert(Account* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Account:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Account::TableId, record);
		}
		return true;
	}
	void AccountTable::BatchInsert(std::vector<Account*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Account::Allocate();
				memcpy(newRecord, record, sizeof(Account));
				PrimaryKey->Insert(newRecord);

			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Account::TableId, dbRecords);
		}
		delete records;
	}
	void AccountTable::Erase(Account* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Account::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	bool AccountTable::Update(Account* const oldRecord, Account* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Account:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Account:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		::memcpy(oldRecord, newRecord, sizeof(Account));

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Account::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void AccountTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void AccountTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Account::TableId);
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

		fprintf(dumpFile, "AccountId,AccountName,AccountType,AccountStatus,Password,TradeGroupId,RiskGroupId,CommissionGroupId\n");
		char buff[4096] = { 0 };
		set<Account*, AccountLessForAccountPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void AccountTable::EraseIndex(Account* record)
	{
	}

	CapitalTable::CapitalTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new CapitalPrimaryKey(this);
		TradingDayIndex = new CapitalIndexTradingDay(this);
	}
	CapitalTable::~CapitalTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	void CapitalTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void CapitalTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void CapitalTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void CapitalTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void CapitalTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Capital::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Capital::Allocate();
				memcpy(record, *it, sizeof(Capital));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Capital::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool CapitalTable::Insert(Capital* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Capital:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		TradingDayIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Capital::TableId, record);
		}
		return true;
	}
	void CapitalTable::BatchInsert(std::vector<Capital*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Capital::Allocate();
				memcpy(newRecord, record, sizeof(Capital));
				PrimaryKey->Insert(newRecord);

				TradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Capital::TableId, dbRecords);
		}
		delete records;
	}
	void CapitalTable::Erase(Capital* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Capital::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int CapitalTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Capital*> records;
		std::lock_guard guard(SharedMutex);
		auto range = TradingDayIndex->index_.equal_range(&CompareCapital);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Capital::Allocate();
			memcpy(record, &CompareCapital, sizeof(Capital));
			mdbSubscriber_->OnRecordEraseByIndex(Capital::TableId, CapitalIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool CapitalTable::Update(Capital* const oldRecord, Capital* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Capital:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Capital:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		CapitalIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Capital));
		if (TradingDayIndexUpdate)
		{
			TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Capital::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void CapitalTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradingDayIndex->index_.clear();
	}
	void CapitalTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradingDayIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Capital::TableId);
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

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,Balance,PreBalance,Available,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,Deposit,Withdraw\n");
		char buff[4096] = { 0 };
		set<Capital*, CapitalLessForCapitalPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void CapitalTable::EraseIndex(Capital* record)
	{
		TradingDayIndex->Erase(record);
	}

	PositionTable::PositionTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new PositionPrimaryKey(this);
		AccountIndex = new PositionIndexAccount(this);
		TradingDayIndex = new PositionIndexTradingDay(this);
	}
	PositionTable::~PositionTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete AccountIndex;
		AccountIndex = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	void PositionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void PositionTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void PositionTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void PositionTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void PositionTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Position::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Position::Allocate();
				memcpy(record, *it, sizeof(Position));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Position::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool PositionTable::Insert(Position* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Position:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		AccountIndex->Insert(record);
		TradingDayIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Position::TableId, record);
		}
		return true;
	}
	void PositionTable::BatchInsert(std::vector<Position*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Position::Allocate();
				memcpy(newRecord, record, sizeof(Position));
				PrimaryKey->Insert(newRecord);

				AccountIndex->Insert(newRecord);
				TradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Position::TableId, dbRecords);
		}
		delete records;
	}
	void PositionTable::Erase(Position* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Position::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PositionTable::EraseByAccountIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		AccountIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Position*> records;
		std::lock_guard guard(SharedMutex);
		auto range = AccountIndex->index_.equal_range(&ComparePosition);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &ComparePosition, sizeof(Position));
			mdbSubscriber_->OnRecordEraseByIndex(Position::TableId, PositionIndexAccount::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PositionTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Position*> records;
		std::lock_guard guard(SharedMutex);
		auto range = TradingDayIndex->index_.equal_range(&ComparePosition);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &ComparePosition, sizeof(Position));
			mdbSubscriber_->OnRecordEraseByIndex(Position::TableId, PositionIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PositionTable::Update(Position* const oldRecord, Position* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Position:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Position:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIndexUpdate = AccountIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexAccount::iterator itAccount;
		if (AccountIndexUpdate)
		{
			itAccount = AccountIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Position));
		if (AccountIndexUpdate)
		{
			AccountIndex->Update(itAccount);
		}
		if (TradingDayIndexUpdate)
		{
			TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Position::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PositionTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		AccountIndex->index_.clear();
		TradingDayIndex->index_.clear();
	}
	void PositionTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		AccountIndex->index_.clear();
		TradingDayIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Position::TableId);
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

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,PosiDirection,TotalPosition,PositionFrozen,TodayPosition,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice\n");
		char buff[4096] = { 0 };
		set<Position*, PositionLessForPositionPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void PositionTable::EraseIndex(Position* record)
	{
		AccountIndex->Erase(record);
		TradingDayIndex->Erase(record);
	}

	PositionDetailTable::PositionDetailTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new PositionDetailPrimaryKey(this);
		TradeMatchIndex = new PositionDetailIndexTradeMatch(this);
		TradingDayIndex = new PositionDetailIndexTradingDay(this);
	}
	PositionDetailTable::~PositionDetailTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete TradeMatchIndex;
		TradeMatchIndex = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	void PositionDetailTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void PositionDetailTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void PositionDetailTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void PositionDetailTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void PositionDetailTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(PositionDetail::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = PositionDetail::Allocate();
				memcpy(record, *it, sizeof(PositionDetail));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(PositionDetail::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool PositionDetailTable::Insert(PositionDetail* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PositionDetail:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		TradeMatchIndex->Insert(record);
		TradingDayIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(PositionDetail::TableId, record);
		}
		return true;
	}
	void PositionDetailTable::BatchInsert(std::vector<PositionDetail*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PositionDetail::Allocate();
				memcpy(newRecord, record, sizeof(PositionDetail));
				PrimaryKey->Insert(newRecord);

				TradeMatchIndex->Insert(newRecord);
				TradingDayIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(PositionDetail::TableId, dbRecords);
		}
		delete records;
	}
	void PositionDetailTable::Erase(PositionDetail* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(PositionDetail::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PositionDetailTable::EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		TradeMatchIndex->FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::vector<PositionDetail*> records;
		std::lock_guard guard(SharedMutex);
		auto range = TradeMatchIndex->index_.equal_range(&ComparePositionDetail);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &ComparePositionDetail, sizeof(PositionDetail));
			mdbSubscriber_->OnRecordEraseByIndex(PositionDetail::TableId, PositionDetailIndexTradeMatch::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PositionDetailTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<PositionDetail*> records;
		std::lock_guard guard(SharedMutex);
		auto range = TradingDayIndex->index_.equal_range(&ComparePositionDetail);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &ComparePositionDetail, sizeof(PositionDetail));
			mdbSubscriber_->OnRecordEraseByIndex(PositionDetail::TableId, PositionDetailIndexTradingDay::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PositionDetailTable::Update(PositionDetail* const oldRecord, PositionDetail* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PositionDetail:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PositionDetail:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool TradeMatchIndexUpdate = TradeMatchIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradeMatch::iterator itTradeMatch;
		if (TradeMatchIndexUpdate)
		{
			itTradeMatch = TradeMatchIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PositionDetail));
		if (TradeMatchIndexUpdate)
		{
			TradeMatchIndex->Update(itTradeMatch);
		}
		if (TradingDayIndexUpdate)
		{
			TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(PositionDetail::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PositionDetailTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradeMatchIndex->index_.clear();
		TradingDayIndex->index_.clear();
	}
	void PositionDetailTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		TradeMatchIndex->index_.clear();
		TradingDayIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(PositionDetail::TableId);
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

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,PosiDirection,OpenDate,TradeId,Volume,OpenPrice,MarketValue,CashIn,CashOut,Margin,Commission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice,CloseVolume,CloseAmount\n");
		char buff[4096] = { 0 };
		set<PositionDetail*, PositionDetailLessForPositionDetailPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void PositionDetailTable::EraseIndex(PositionDetail* record)
	{
		TradeMatchIndex->Erase(record);
		TradingDayIndex->Erase(record);
	}

	OrderTable::OrderTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new OrderPrimaryKey(this);
		ClientOrderIdUniqueKey = new OrderUniqueKeyClientOrderId(this);
		AccountIdIndex = new OrderIndexAccountId(this);
	}
	OrderTable::~OrderTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete ClientOrderIdUniqueKey;
		ClientOrderIdUniqueKey = nullptr;
		delete AccountIdIndex;
		AccountIdIndex = nullptr;
	}
	void OrderTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void OrderTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void OrderTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void OrderTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void OrderTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Order::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Order::Allocate();
				memcpy(record, *it, sizeof(Order));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Order::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool OrderTable::Insert(Order* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record) || !(ClientOrderIdUniqueKey->CheckInsert(record)))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Order:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);
		ClientOrderIdUniqueKey->Insert(record);

		AccountIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Order::TableId, record);
		}
		return true;
	}
	void OrderTable::BatchInsert(std::vector<Order*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Order::Allocate();
				memcpy(newRecord, record, sizeof(Order));
				PrimaryKey->Insert(newRecord);
				ClientOrderIdUniqueKey->Insert(newRecord);

				AccountIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Order::TableId, dbRecords);
		}
		delete records;
	}
	void OrderTable::Erase(Order* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Order::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int OrderTable::EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		AccountIdIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Order*> records;
		std::lock_guard guard(SharedMutex);
		auto range = AccountIdIndex->index_.equal_range(&CompareOrder);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Order::Allocate();
			memcpy(record, &CompareOrder, sizeof(Order));
			mdbSubscriber_->OnRecordEraseByIndex(Order::TableId, OrderIndexAccountId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool OrderTable::Update(Order* const oldRecord, Order* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord) || !(ClientOrderIdUniqueKey->CheckUpdate(oldRecord, newRecord)))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Order:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Order:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(oldRecord, newRecord);
		OrderIndexAccountId::iterator itAccountId;
		if (AccountIdIndexUpdate)
		{
			itAccountId = AccountIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Order));
		if (AccountIdIndexUpdate)
		{
			AccountIdIndex->Update(itAccountId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Order::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void OrderTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		ClientOrderIdUniqueKey->index_.clear();
		AccountIdIndex->index_.clear();
	}
	void OrderTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		ClientOrderIdUniqueKey->index_.clear();
		AccountIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Order::TableId);
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

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,OrderId,OrderSysId,Direction,OffsetFlag,OrderPriceType,Price,Volume,VolumeTotal,VolumeTraded,VolumeMultiple,OrderStatus,OrderDate,OrderTime,CancelDate,CancelTime,SessionId,ClientOrderId,RequestId,OfferId,TradeGroupId,RiskGroupId,CommissionGroupId,FrozenCash,FrozenMargin,FrozenCommission,RebuildMark,IsForceClose\n");
		char buff[4096] = { 0 };
		set<Order*, OrderLessForOrderPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
		ClientOrderIdUniqueKey->Erase(record);
	}
	void OrderTable::EraseIndex(Order* record)
	{
		AccountIdIndex->Erase(record);
	}

	TradeTable::TradeTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new TradePrimaryKey(this);
		AccountIdIndex = new TradeIndexAccountId(this);
	}
	TradeTable::~TradeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete AccountIdIndex;
		AccountIdIndex = nullptr;
	}
	void TradeTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void TradeTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void TradeTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void TradeTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void TradeTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(Trade::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = Trade::Allocate();
				memcpy(record, *it, sizeof(Trade));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(Trade::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool TradeTable::Insert(Trade* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Trade:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		AccountIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(Trade::TableId, record);
		}
		return true;
	}
	void TradeTable::BatchInsert(std::vector<Trade*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Trade::Allocate();
				memcpy(newRecord, record, sizeof(Trade));
				PrimaryKey->Insert(newRecord);

				AccountIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(Trade::TableId, dbRecords);
		}
		delete records;
	}
	void TradeTable::Erase(Trade* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(Trade::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int TradeTable::EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		AccountIdIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Trade*> records;
		std::lock_guard guard(SharedMutex);
		auto range = AccountIdIndex->index_.equal_range(&CompareTrade);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = Trade::Allocate();
			memcpy(record, &CompareTrade, sizeof(Trade));
			mdbSubscriber_->OnRecordEraseByIndex(Trade::TableId, TradeIndexAccountId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool TradeTable::Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Trade:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Trade:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(oldRecord, newRecord);
		TradeIndexAccountId::iterator itAccountId;
		if (AccountIdIndexUpdate)
		{
			itAccountId = AccountIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(Trade));
		if (AccountIdIndexUpdate)
		{
			AccountIdIndex->Update(itAccountId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(Trade::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void TradeTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		AccountIdIndex->index_.clear();
	}
	void TradeTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		AccountIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(Trade::TableId);
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

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,OrderId,OrderSysId,TradeId,Direction,OffsetFlag,Price,Volume,VolumeMultiple,TradeAmount,Commission,TradeDate,TradeTime\n");
		char buff[4096] = { 0 };
		set<Trade*, TradeLessForTradePrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void TradeTable::EraseIndex(Trade* record)
	{
		AccountIdIndex->Erase(record);
	}

	AccountLoginSessionTable::AccountLoginSessionTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new AccountLoginSessionPrimaryKey(this);
		SessionIdIndex = new AccountLoginSessionIndexSessionId(this);
		AccountIdIndex = new AccountLoginSessionIndexAccountId(this);
	}
	AccountLoginSessionTable::~AccountLoginSessionTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete SessionIdIndex;
		SessionIdIndex = nullptr;
		delete AccountIdIndex;
		AccountIdIndex = nullptr;
	}
	void AccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void AccountLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void AccountLoginSessionTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void AccountLoginSessionTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void AccountLoginSessionTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(AccountLoginSession::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = AccountLoginSession::Allocate();
				memcpy(record, *it, sizeof(AccountLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(AccountLoginSession::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool AccountLoginSessionTable::Insert(AccountLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for AccountLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		SessionIdIndex->Insert(record);
		AccountIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(AccountLoginSession::TableId, record);
		}
		return true;
	}
	void AccountLoginSessionTable::BatchInsert(std::vector<AccountLoginSession*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = AccountLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(AccountLoginSession));
				PrimaryKey->Insert(newRecord);

				SessionIdIndex->Insert(newRecord);
				AccountIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(AccountLoginSession::TableId, dbRecords);
		}
		delete records;
	}
	void AccountLoginSessionTable::Erase(AccountLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(AccountLoginSession::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int AccountLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<AccountLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = SessionIdIndex->index_.equal_range(&CompareAccountLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = AccountLoginSession::Allocate();
			memcpy(record, &CompareAccountLoginSession, sizeof(AccountLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(AccountLoginSession::TableId, AccountLoginSessionIndexSessionId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int AccountLoginSessionTable::EraseByAccountIdIndex(const AccountIdType& AccountId)
	{
		AccountIdIndex->FillCompareRecord(AccountId);
		std::vector<AccountLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = AccountIdIndex->index_.equal_range(&CompareAccountLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = AccountLoginSession::Allocate();
			memcpy(record, &CompareAccountLoginSession, sizeof(AccountLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(AccountLoginSession::TableId, AccountLoginSessionIndexAccountId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool AccountLoginSessionTable::Update(AccountLoginSession* const oldRecord, AccountLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for AccountLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New AccountLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(oldRecord, newRecord);
		AccountLoginSessionIndexSessionId::iterator itSessionId;
		if (SessionIdIndexUpdate)
		{
			itSessionId = SessionIdIndex->FindNode(oldRecord);
		}
		bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(oldRecord, newRecord);
		AccountLoginSessionIndexAccountId::iterator itAccountId;
		if (AccountIdIndexUpdate)
		{
			itAccountId = AccountIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(AccountLoginSession));
		if (SessionIdIndexUpdate)
		{
			SessionIdIndex->Update(itSessionId);
		}
		if (AccountIdIndexUpdate)
		{
			AccountIdIndex->Update(itAccountId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(AccountLoginSession::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void AccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		AccountIdIndex->index_.clear();
	}
	void AccountLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		AccountIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(AccountLoginSession::TableId);
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

		fprintf(dumpFile, "AccountId,SessionId,IpAddress\n");
		char buff[4096] = { 0 };
		set<AccountLoginSession*, AccountLoginSessionLessForAccountLoginSessionPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void AccountLoginSessionTable::EraseIndex(AccountLoginSession* record)
	{
		SessionIdIndex->Erase(record);
		AccountIdIndex->Erase(record);
	}

	PrimaryAccountLoginSessionTable::PrimaryAccountLoginSessionTable()
	{
		mdbSubscriber_ = nullptr;
		PrimaryKey = new PrimaryAccountLoginSessionPrimaryKey(this);
		SessionIdIndex = new PrimaryAccountLoginSessionIndexSessionId(this);
		PrimaryAccountIdIndex = new PrimaryAccountLoginSessionIndexPrimaryAccountId(this);
	}
	PrimaryAccountLoginSessionTable::~PrimaryAccountLoginSessionTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete SessionIdIndex;
		SessionIdIndex = nullptr;
		delete PrimaryAccountIdIndex;
		PrimaryAccountIdIndex = nullptr;
	}
	void PrimaryAccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		mdbSubscriber_ = subscriber;
	}
	void PrimaryAccountLoginSessionTable::UnSubscribe()
	{
		mdbSubscriber_ = nullptr;
	}
	void PrimaryAccountLoginSessionTable::LockShared()
	{
		SharedMutex.lock_shared();
	}
	void PrimaryAccountLoginSessionTable::UnlockShared()
	{
		SharedMutex.unlock_shared();
	}
	void PrimaryAccountLoginSessionTable::InitDb()
	{
		if (mdbSubscriber_ == nullptr)
		{
			DbInited = true;
			return;
		}
		mdbSubscriber_->OnRecordTruncate(PrimaryAccountLoginSession::TableId);

		auto records = new std::vector<const void*>();
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				auto record = PrimaryAccountLoginSession::Allocate();
				memcpy(record, *it, sizeof(PrimaryAccountLoginSession));
				records->push_back(record);
			}
		}
		if (!records->empty())
		{
			mdbSubscriber_->OnRecordBatchInsert(PrimaryAccountLoginSession::TableId, records);
		}
		else
		{
			delete records;
		}
		DbInited = true;
	}
	bool PrimaryAccountLoginSessionTable::Insert(PrimaryAccountLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PrimaryAccountLoginSession:[%s]", record->GetString());
			record->Deallocate();
			return false;
		}

		PrimaryKey->Insert(record);

		SessionIdIndex->Insert(record);
		PrimaryAccountIdIndex->Insert(record);
		
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordInsert(PrimaryAccountLoginSession::TableId, record);
		}
		return true;
	}
	void PrimaryAccountLoginSessionTable::BatchInsert(std::vector<PrimaryAccountLoginSession*>* records)
	{
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PrimaryAccountLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(PrimaryAccountLoginSession));
				PrimaryKey->Insert(newRecord);

				SessionIdIndex->Insert(newRecord);
				PrimaryAccountIdIndex->Insert(newRecord);
			}
		}
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto dbRecords = new std::vector<const void*>();
			dbRecords->reserve(records->size());
			for (auto* r : *records) dbRecords->push_back(r);
			mdbSubscriber_->OnRecordBatchInsert(PrimaryAccountLoginSession::TableId, dbRecords);
		}
		delete records;
	}
	void PrimaryAccountLoginSessionTable::Erase(PrimaryAccountLoginSession* record)
	{
		std::lock_guard guard(SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordErase(PrimaryAccountLoginSession::TableId, record);
		}
		else
		{
			record->Deallocate();
		}
	}
	int PrimaryAccountLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<PrimaryAccountLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = SessionIdIndex->index_.equal_range(&ComparePrimaryAccountLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = PrimaryAccountLoginSession::Allocate();
			memcpy(record, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(PrimaryAccountLoginSession::TableId, PrimaryAccountLoginSessionIndexSessionId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	int PrimaryAccountLoginSessionTable::EraseByPrimaryAccountIdIndex(const AccountIdType& PrimaryAccountId)
	{
		PrimaryAccountIdIndex->FillCompareRecord(PrimaryAccountId);
		std::vector<PrimaryAccountLoginSession*> records;
		std::lock_guard guard(SharedMutex);
		auto range = PrimaryAccountIdIndex->index_.equal_range(&ComparePrimaryAccountLoginSession);
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
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			auto record = PrimaryAccountLoginSession::Allocate();
			memcpy(record, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
			mdbSubscriber_->OnRecordEraseByIndex(PrimaryAccountLoginSession::TableId, PrimaryAccountLoginSessionIndexPrimaryAccountId::IndexID, record);
		}
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountLoginSessionTable::Update(PrimaryAccountLoginSession* const oldRecord, PrimaryAccountLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(SharedMutex);
		if (!PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccountLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PrimaryAccountLoginSession:[%s]", newRecord->GetString());
			newRecord->Deallocate();
			return false;
		}

		bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountLoginSessionIndexSessionId::iterator itSessionId;
		if (SessionIdIndexUpdate)
		{
			itSessionId = SessionIdIndex->FindNode(oldRecord);
		}
		bool PrimaryAccountIdIndexUpdate = PrimaryAccountIdIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator itPrimaryAccountId;
		if (PrimaryAccountIdIndexUpdate)
		{
			itPrimaryAccountId = PrimaryAccountIdIndex->FindNode(oldRecord);
		}
		::memcpy(oldRecord, newRecord, sizeof(PrimaryAccountLoginSession));
		if (SessionIdIndexUpdate)
		{
			SessionIdIndex->Update(itSessionId);
		}
		if (PrimaryAccountIdIndexUpdate)
		{
			PrimaryAccountIdIndex->Update(itPrimaryAccountId);
		}

		if (updateDB && mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordUpdate(PrimaryAccountLoginSession::TableId, newRecord);
		}
		else
		{
			newRecord->Deallocate();
		}
		return true;
	}
	void PrimaryAccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		PrimaryAccountIdIndex->index_.clear();
	}
	void PrimaryAccountLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
		SessionIdIndex->index_.clear();
		PrimaryAccountIdIndex->index_.clear();
		if (mdbSubscriber_ != nullptr && DbInited)
		{
			mdbSubscriber_->OnRecordTruncate(PrimaryAccountLoginSession::TableId);
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

		fprintf(dumpFile, "PrimaryAccountId,SessionId,IpAddress\n");
		char buff[4096] = { 0 };
		set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountLoginSessionPrimaryKey> records;
		std::shared_lock guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
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
		PrimaryKey->Erase(record);
	}
	void PrimaryAccountLoginSessionTable::EraseIndex(PrimaryAccountLoginSession* record)
	{
		SessionIdIndex->Erase(record);
		PrimaryAccountIdIndex->Erase(record);
	}

}

