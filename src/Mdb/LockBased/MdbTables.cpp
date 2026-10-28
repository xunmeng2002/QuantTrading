// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbTables.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbTables.h"
#include <DbAdapters/DbInterface/RecordHandle.h>
#include <Spark/Core/Logger/Logger.h>
#include <cassert>
#include <string>
#include <cstring>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using std::string;
using std::set;
using namespace Spark::Core;
using namespace DbAdapters;

namespace QuantTrading
{
	TradingDayTable::TradingDayTable()
	{
		PrimaryKey = new TradingDayTablePrimaryKey(this);
	}
	TradingDayTable::~TradingDayTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int TradingDayTable::GetTableId() const
	{
		return TradingDay::TableId;
	}
	void TradingDayTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void TradingDayTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void TradingDayTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void TradingDayTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(TradingDay::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(TradingDay::TableId);
	}
	bool TradingDayTable::Insert(TradingDay* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for TradingDay:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void TradingDayTable::BatchInsert(std::vector<TradingDay*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool TradingDayTable::Erase(const TradingDay& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			TradingDay* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool TradingDayTable::Update(const TradingDay& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			TradingDay* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for TradingDay:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(TradingDay));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void TradingDayTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void TradingDayTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void TradingDayTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//TradingDays.csv";
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
	bool TradingDayTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr TradingDayTable::MakeInsertEvent(const TradingDay* record)
	{
		auto eventRecord = TradingDay::Allocate();
		memcpy(eventRecord, record, sizeof(TradingDay));
		return std::make_shared<const RowChangeEvent>(TradingDay::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void TradingDayTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void TradingDayTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr TradingDayTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(TradingDay::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr TradingDayTable::BuildInsertEvent(const TradingDay* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr TradingDayTable::BuildUpdateEvent(const TradingDay& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		TradingDay* eventRecord = TradingDay::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(TradingDay));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			TradingDay::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> TradingDayTable::BuildBatchInsertEvents(const std::vector<TradingDay*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const TradingDay* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	ExchangeTable::ExchangeTable()
	{
		PrimaryKey = new ExchangeTablePrimaryKey(this);
	}
	ExchangeTable::~ExchangeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int ExchangeTable::GetTableId() const
	{
		return Exchange::TableId;
	}
	void ExchangeTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void ExchangeTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void ExchangeTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void ExchangeTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Exchange::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Exchange::TableId);
	}
	bool ExchangeTable::Insert(Exchange* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for Exchange:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void ExchangeTable::BatchInsert(std::vector<Exchange*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool ExchangeTable::Erase(const Exchange& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Exchange* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool ExchangeTable::Update(const Exchange& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Exchange* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Exchange:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(Exchange));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void ExchangeTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void ExchangeTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void ExchangeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Exchanges.csv";
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
	bool ExchangeTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr ExchangeTable::MakeInsertEvent(const Exchange* record)
	{
		auto eventRecord = Exchange::Allocate();
		memcpy(eventRecord, record, sizeof(Exchange));
		return std::make_shared<const RowChangeEvent>(Exchange::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void ExchangeTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void ExchangeTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr ExchangeTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Exchange::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr ExchangeTable::BuildInsertEvent(const Exchange* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr ExchangeTable::BuildUpdateEvent(const Exchange& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Exchange* eventRecord = Exchange::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Exchange));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Exchange::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> ExchangeTable::BuildBatchInsertEvents(const std::vector<Exchange*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Exchange* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	ProductTable::ProductTable()
	{
		PrimaryKey = new ProductTablePrimaryKey(this);
	}
	ProductTable::~ProductTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int ProductTable::GetTableId() const
	{
		return Product::TableId;
	}
	void ProductTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void ProductTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void ProductTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void ProductTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Product::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Product::TableId);
	}
	bool ProductTable::Insert(Product* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for Product:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void ProductTable::BatchInsert(std::vector<Product*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool ProductTable::Erase(const Product& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Product* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool ProductTable::Update(const Product& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Product* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Product:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(Product));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void ProductTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void ProductTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void ProductTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Products.csv";
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
	bool ProductTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr ProductTable::MakeInsertEvent(const Product* record)
	{
		auto eventRecord = Product::Allocate();
		memcpy(eventRecord, record, sizeof(Product));
		return std::make_shared<const RowChangeEvent>(Product::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void ProductTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void ProductTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr ProductTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Product::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr ProductTable::BuildInsertEvent(const Product* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr ProductTable::BuildUpdateEvent(const Product& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Product* eventRecord = Product::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Product));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Product::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> ProductTable::BuildBatchInsertEvents(const std::vector<Product*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Product* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	HotInstrumentTable::HotInstrumentTable()
	{
		PrimaryKey = new HotInstrumentTablePrimaryKey(this);
		TradingDayIndex = new HotInstrumentTableIndexTradingDay(this);
	}
	HotInstrumentTable::~HotInstrumentTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	unsigned int HotInstrumentTable::GetTableId() const
	{
		return HotInstrument::TableId;
	}
	void HotInstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void HotInstrumentTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void HotInstrumentTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void HotInstrumentTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(HotInstrument::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(HotInstrument::TableId);
	}
	bool HotInstrumentTable::Insert(HotInstrument* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void HotInstrumentTable::BatchInsert(std::vector<HotInstrument*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				TradingDayIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool HotInstrumentTable::Erase(const HotInstrument& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			HotInstrument* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int HotInstrumentTable::EraseByTradingDayIndex(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		std::lock_guard publishGuard(publishMutex_);
		TradingDayIndex->FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::vector<HotInstrument*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = HotInstrument::Allocate();
				memcpy(compareRecord, &CompareHotInstrument, sizeof(HotInstrument));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, HotInstrumentTableIndexTradingDay::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool HotInstrumentTable::Update(const HotInstrument& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			HotInstrument* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for HotInstrument:[%s]", newRecord.GetString());
				return false;
			}

			bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(liveRecord, &newRecord);
			HotInstrumentTableIndexTradingDay::iterator itTradingDay;
			if (TradingDayIndexUpdate)
			{
				itTradingDay = TradingDayIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(HotInstrument));
			if (TradingDayIndexUpdate)
			{
				TradingDayIndex->Update(itTradingDay);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void HotInstrumentTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			TradingDayIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void HotInstrumentTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//HotInstruments.csv";
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
	bool HotInstrumentTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr HotInstrumentTable::MakeInsertEvent(const HotInstrument* record)
	{
		auto eventRecord = HotInstrument::Allocate();
		memcpy(eventRecord, record, sizeof(HotInstrument));
		return std::make_shared<const RowChangeEvent>(HotInstrument::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void HotInstrumentTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void HotInstrumentTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr HotInstrumentTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(HotInstrument::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr HotInstrumentTable::BuildInsertEvent(const HotInstrument* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr HotInstrumentTable::BuildUpdateEvent(const HotInstrument& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		HotInstrument* eventRecord = HotInstrument::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(HotInstrument));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			HotInstrument::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> HotInstrumentTable::BuildBatchInsertEvents(const std::vector<HotInstrument*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const HotInstrument* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	InstrumentTable::InstrumentTable()
	{
		PrimaryKey = new InstrumentTablePrimaryKey(this);
		ExchangeIdIndex = new InstrumentTableIndexExchangeId(this);
	}
	InstrumentTable::~InstrumentTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete ExchangeIdIndex;
		ExchangeIdIndex = nullptr;
	}
	unsigned int InstrumentTable::GetTableId() const
	{
		return Instrument::TableId;
	}
	void InstrumentTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void InstrumentTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void InstrumentTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void InstrumentTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Instrument::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Instrument::TableId);
	}
	bool InstrumentTable::Insert(Instrument* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void InstrumentTable::BatchInsert(std::vector<Instrument*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				ExchangeIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool InstrumentTable::Erase(const Instrument& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Instrument* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int InstrumentTable::EraseByExchangeIdIndex(const ExchangeIdType& ExchangeId)
	{
		std::lock_guard publishGuard(publishMutex_);
		ExchangeIdIndex->FillCompareRecord(ExchangeId);
		std::vector<Instrument*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Instrument::Allocate();
				memcpy(compareRecord, &CompareInstrument, sizeof(Instrument));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, InstrumentTableIndexExchangeId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool InstrumentTable::Update(const Instrument& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Instrument* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Instrument:[%s]", newRecord.GetString());
				return false;
			}

			bool ExchangeIdIndexUpdate = ExchangeIdIndex->NeedUpdate(liveRecord, &newRecord);
			InstrumentTableIndexExchangeId::iterator itExchangeId;
			if (ExchangeIdIndexUpdate)
			{
				itExchangeId = ExchangeIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(Instrument));
			if (ExchangeIdIndexUpdate)
			{
				ExchangeIdIndex->Update(itExchangeId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void InstrumentTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			ExchangeIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void InstrumentTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Instruments.csv";
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
	bool InstrumentTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr InstrumentTable::MakeInsertEvent(const Instrument* record)
	{
		auto eventRecord = Instrument::Allocate();
		memcpy(eventRecord, record, sizeof(Instrument));
		return std::make_shared<const RowChangeEvent>(Instrument::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void InstrumentTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void InstrumentTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr InstrumentTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Instrument::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr InstrumentTable::BuildInsertEvent(const Instrument* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr InstrumentTable::BuildUpdateEvent(const Instrument& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Instrument* eventRecord = Instrument::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Instrument));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Instrument::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> InstrumentTable::BuildBatchInsertEvents(const std::vector<Instrument*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Instrument* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	DepthMarketDataTable::DepthMarketDataTable()
	{
		PrimaryKey = new DepthMarketDataTablePrimaryKey(this);
	}
	DepthMarketDataTable::~DepthMarketDataTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int DepthMarketDataTable::GetTableId() const
	{
		return DepthMarketData::TableId;
	}
	void DepthMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void DepthMarketDataTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void DepthMarketDataTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void DepthMarketDataTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(DepthMarketData::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(DepthMarketData::TableId);
	}
	bool DepthMarketDataTable::Insert(DepthMarketData* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for DepthMarketData:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void DepthMarketDataTable::BatchInsert(std::vector<DepthMarketData*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool DepthMarketDataTable::Erase(const DepthMarketData& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			DepthMarketData* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool DepthMarketDataTable::Update(const DepthMarketData& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			DepthMarketData* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for DepthMarketData:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(DepthMarketData));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void DepthMarketDataTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void DepthMarketDataTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void DepthMarketDataTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//DepthMarketDatas.csv";
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
	bool DepthMarketDataTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr DepthMarketDataTable::MakeInsertEvent(const DepthMarketData* record)
	{
		auto eventRecord = DepthMarketData::Allocate();
		memcpy(eventRecord, record, sizeof(DepthMarketData));
		return std::make_shared<const RowChangeEvent>(DepthMarketData::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void DepthMarketDataTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void DepthMarketDataTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr DepthMarketDataTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(DepthMarketData::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr DepthMarketDataTable::BuildInsertEvent(const DepthMarketData* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr DepthMarketDataTable::BuildUpdateEvent(const DepthMarketData& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		DepthMarketData* eventRecord = DepthMarketData::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(DepthMarketData));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			DepthMarketData::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> DepthMarketDataTable::BuildBatchInsertEvents(const std::vector<DepthMarketData*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const DepthMarketData* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	BarMarketDataTable::BarMarketDataTable()
	{
		PrimaryKey = new BarMarketDataTablePrimaryKey(this);
	}
	BarMarketDataTable::~BarMarketDataTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int BarMarketDataTable::GetTableId() const
	{
		return BarMarketData::TableId;
	}
	void BarMarketDataTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void BarMarketDataTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void BarMarketDataTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void BarMarketDataTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(BarMarketData::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(BarMarketData::TableId);
	}
	bool BarMarketDataTable::Insert(BarMarketData* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for BarMarketData:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void BarMarketDataTable::BatchInsert(std::vector<BarMarketData*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool BarMarketDataTable::Erase(const BarMarketData& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			BarMarketData* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool BarMarketDataTable::Update(const BarMarketData& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			BarMarketData* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for BarMarketData:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(BarMarketData));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void BarMarketDataTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void BarMarketDataTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void BarMarketDataTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//BarMarketDatas.csv";
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
	bool BarMarketDataTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr BarMarketDataTable::MakeInsertEvent(const BarMarketData* record)
	{
		auto eventRecord = BarMarketData::Allocate();
		memcpy(eventRecord, record, sizeof(BarMarketData));
		return std::make_shared<const RowChangeEvent>(BarMarketData::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void BarMarketDataTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void BarMarketDataTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr BarMarketDataTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(BarMarketData::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr BarMarketDataTable::BuildInsertEvent(const BarMarketData* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr BarMarketDataTable::BuildUpdateEvent(const BarMarketData& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		BarMarketData* eventRecord = BarMarketData::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(BarMarketData));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			BarMarketData::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> BarMarketDataTable::BuildBatchInsertEvents(const std::vector<BarMarketData*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const BarMarketData* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	MdSubscribeTable::MdSubscribeTable()
	{
		PrimaryKey = new MdSubscribeTablePrimaryKey(this);
	}
	MdSubscribeTable::~MdSubscribeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int MdSubscribeTable::GetTableId() const
	{
		return MdSubscribe::TableId;
	}
	void MdSubscribeTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void MdSubscribeTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void MdSubscribeTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void MdSubscribeTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(MdSubscribe::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(MdSubscribe::TableId);
	}
	bool MdSubscribeTable::Insert(MdSubscribe* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for MdSubscribe:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void MdSubscribeTable::BatchInsert(std::vector<MdSubscribe*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool MdSubscribeTable::Erase(const MdSubscribe& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdSubscribe* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool MdSubscribeTable::Update(const MdSubscribe& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdSubscribe* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for MdSubscribe:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(MdSubscribe));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void MdSubscribeTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void MdSubscribeTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void MdSubscribeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//MdSubscribes.csv";
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
	bool MdSubscribeTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr MdSubscribeTable::MakeInsertEvent(const MdSubscribe* record)
	{
		auto eventRecord = MdSubscribe::Allocate();
		memcpy(eventRecord, record, sizeof(MdSubscribe));
		return std::make_shared<const RowChangeEvent>(MdSubscribe::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void MdSubscribeTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void MdSubscribeTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr MdSubscribeTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(MdSubscribe::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr MdSubscribeTable::BuildInsertEvent(const MdSubscribe* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr MdSubscribeTable::BuildUpdateEvent(const MdSubscribe& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		MdSubscribe* eventRecord = MdSubscribe::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(MdSubscribe));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			MdSubscribe::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> MdSubscribeTable::BuildBatchInsertEvents(const std::vector<MdSubscribe*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const MdSubscribe* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	MdUserTable::MdUserTable()
	{
		PrimaryKey = new MdUserTablePrimaryKey(this);
	}
	MdUserTable::~MdUserTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int MdUserTable::GetTableId() const
	{
		return MdUser::TableId;
	}
	void MdUserTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void MdUserTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void MdUserTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void MdUserTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(MdUser::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(MdUser::TableId);
	}
	bool MdUserTable::Insert(MdUser* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for MdUser:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void MdUserTable::BatchInsert(std::vector<MdUser*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool MdUserTable::Erase(const MdUser& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdUser* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool MdUserTable::Update(const MdUser& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdUser* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for MdUser:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(MdUser));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void MdUserTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void MdUserTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void MdUserTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//MdUsers.csv";
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
	bool MdUserTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr MdUserTable::MakeInsertEvent(const MdUser* record)
	{
		auto eventRecord = MdUser::Allocate();
		memcpy(eventRecord, record, sizeof(MdUser));
		return std::make_shared<const RowChangeEvent>(MdUser::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void MdUserTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void MdUserTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr MdUserTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(MdUser::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr MdUserTable::BuildInsertEvent(const MdUser* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr MdUserTable::BuildUpdateEvent(const MdUser& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		MdUser* eventRecord = MdUser::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(MdUser));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			MdUser::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> MdUserTable::BuildBatchInsertEvents(const std::vector<MdUser*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const MdUser* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	MdUserLoginSessionTable::MdUserLoginSessionTable()
	{
		PrimaryKey = new MdUserLoginSessionTablePrimaryKey(this);
		SessionIdIndex = new MdUserLoginSessionTableIndexSessionId(this);
		MdUserIdIndex = new MdUserLoginSessionTableIndexMdUserId(this);
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
	unsigned int MdUserLoginSessionTable::GetTableId() const
	{
		return MdUserLoginSession::TableId;
	}
	void MdUserLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void MdUserLoginSessionTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void MdUserLoginSessionTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void MdUserLoginSessionTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(MdUserLoginSession::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(MdUserLoginSession::TableId);
	}
	bool MdUserLoginSessionTable::Insert(MdUserLoginSession* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void MdUserLoginSessionTable::BatchInsert(std::vector<MdUserLoginSession*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				SessionIdIndex->Insert(record);
				MdUserIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool MdUserLoginSessionTable::Erase(const MdUserLoginSession& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdUserLoginSession* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int MdUserLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		std::lock_guard publishGuard(publishMutex_);
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<MdUserLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = MdUserLoginSession::Allocate();
				memcpy(compareRecord, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, MdUserLoginSessionTableIndexSessionId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	int MdUserLoginSessionTable::EraseByMdUserIdIndex(const UserIdType& MdUserId)
	{
		std::lock_guard publishGuard(publishMutex_);
		MdUserIdIndex->FillCompareRecord(MdUserId);
		std::vector<MdUserLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = MdUserLoginSession::Allocate();
				memcpy(compareRecord, &CompareMdUserLoginSession, sizeof(MdUserLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, MdUserLoginSessionTableIndexMdUserId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool MdUserLoginSessionTable::Update(const MdUserLoginSession& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			MdUserLoginSession* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for MdUserLoginSession:[%s]", newRecord.GetString());
				return false;
			}

			bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(liveRecord, &newRecord);
			MdUserLoginSessionTableIndexSessionId::iterator itSessionId;
			if (SessionIdIndexUpdate)
			{
				itSessionId = SessionIdIndex->FindNode(liveRecord);
			}
			bool MdUserIdIndexUpdate = MdUserIdIndex->NeedUpdate(liveRecord, &newRecord);
			MdUserLoginSessionTableIndexMdUserId::iterator itMdUserId;
			if (MdUserIdIndexUpdate)
			{
				itMdUserId = MdUserIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(MdUserLoginSession));
			if (SessionIdIndexUpdate)
			{
				SessionIdIndex->Update(itSessionId);
			}
			if (MdUserIdIndexUpdate)
			{
				MdUserIdIndex->Update(itMdUserId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void MdUserLoginSessionTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			SessionIdIndex->index_.clear();
			MdUserIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void MdUserLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//MdUserLoginSessions.csv";
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
	bool MdUserLoginSessionTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr MdUserLoginSessionTable::MakeInsertEvent(const MdUserLoginSession* record)
	{
		auto eventRecord = MdUserLoginSession::Allocate();
		memcpy(eventRecord, record, sizeof(MdUserLoginSession));
		return std::make_shared<const RowChangeEvent>(MdUserLoginSession::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void MdUserLoginSessionTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void MdUserLoginSessionTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr MdUserLoginSessionTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(MdUserLoginSession::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr MdUserLoginSessionTable::BuildInsertEvent(const MdUserLoginSession* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr MdUserLoginSessionTable::BuildUpdateEvent(const MdUserLoginSession& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		MdUserLoginSession* eventRecord = MdUserLoginSession::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(MdUserLoginSession));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			MdUserLoginSession::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> MdUserLoginSessionTable::BuildBatchInsertEvents(const std::vector<MdUserLoginSession*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const MdUserLoginSession* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	PrimaryAccountTable::PrimaryAccountTable()
	{
		PrimaryKey = new PrimaryAccountTablePrimaryKey(this);
		OfferIdIndex = new PrimaryAccountTableIndexOfferId(this);
	}
	PrimaryAccountTable::~PrimaryAccountTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete OfferIdIndex;
		OfferIdIndex = nullptr;
	}
	unsigned int PrimaryAccountTable::GetTableId() const
	{
		return PrimaryAccount::TableId;
	}
	void PrimaryAccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void PrimaryAccountTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void PrimaryAccountTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void PrimaryAccountTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(PrimaryAccount::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(PrimaryAccount::TableId);
	}
	bool PrimaryAccountTable::Insert(PrimaryAccount* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void PrimaryAccountTable::BatchInsert(std::vector<PrimaryAccount*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				OfferIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool PrimaryAccountTable::Erase(const PrimaryAccount& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PrimaryAccount* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int PrimaryAccountTable::EraseByOfferIdIndex(const OfferIdType& OfferId)
	{
		std::lock_guard publishGuard(publishMutex_);
		OfferIdIndex->FillCompareRecord(OfferId);
		std::vector<PrimaryAccount*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = PrimaryAccount::Allocate();
				memcpy(compareRecord, &ComparePrimaryAccount, sizeof(PrimaryAccount));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PrimaryAccountTableIndexOfferId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountTable::Update(const PrimaryAccount& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PrimaryAccount* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccount:[%s]", newRecord.GetString());
				return false;
			}

			bool OfferIdIndexUpdate = OfferIdIndex->NeedUpdate(liveRecord, &newRecord);
			PrimaryAccountTableIndexOfferId::iterator itOfferId;
			if (OfferIdIndexUpdate)
			{
				itOfferId = OfferIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(PrimaryAccount));
			if (OfferIdIndexUpdate)
			{
				OfferIdIndex->Update(itOfferId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void PrimaryAccountTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			OfferIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void PrimaryAccountTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//PrimaryAccounts.csv";
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
	bool PrimaryAccountTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr PrimaryAccountTable::MakeInsertEvent(const PrimaryAccount* record)
	{
		auto eventRecord = PrimaryAccount::Allocate();
		memcpy(eventRecord, record, sizeof(PrimaryAccount));
		return std::make_shared<const RowChangeEvent>(PrimaryAccount::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void PrimaryAccountTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void PrimaryAccountTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr PrimaryAccountTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(PrimaryAccount::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr PrimaryAccountTable::BuildInsertEvent(const PrimaryAccount* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr PrimaryAccountTable::BuildUpdateEvent(const PrimaryAccount& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		PrimaryAccount* eventRecord = PrimaryAccount::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(PrimaryAccount));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			PrimaryAccount::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> PrimaryAccountTable::BuildBatchInsertEvents(const std::vector<PrimaryAccount*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const PrimaryAccount* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	AccountTable::AccountTable()
	{
		PrimaryKey = new AccountTablePrimaryKey(this);
	}
	AccountTable::~AccountTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int AccountTable::GetTableId() const
	{
		return Account::TableId;
	}
	void AccountTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void AccountTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void AccountTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void AccountTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Account::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Account::TableId);
	}
	bool AccountTable::Insert(Account* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for Account:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void AccountTable::BatchInsert(std::vector<Account*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool AccountTable::Erase(const Account& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Account* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool AccountTable::Update(const Account& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Account* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Account:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(Account));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void AccountTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void AccountTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void AccountTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Accounts.csv";
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
	bool AccountTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr AccountTable::MakeInsertEvent(const Account* record)
	{
		auto eventRecord = Account::Allocate();
		memcpy(eventRecord, record, sizeof(Account));
		return std::make_shared<const RowChangeEvent>(Account::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void AccountTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void AccountTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr AccountTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Account::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr AccountTable::BuildInsertEvent(const Account* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr AccountTable::BuildUpdateEvent(const Account& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Account* eventRecord = Account::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Account));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Account::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> AccountTable::BuildBatchInsertEvents(const std::vector<Account*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Account* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	CapitalTable::CapitalTable()
	{
		PrimaryKey = new CapitalTablePrimaryKey(this);
		TradingDayIndex = new CapitalTableIndexTradingDay(this);
	}
	CapitalTable::~CapitalTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete TradingDayIndex;
		TradingDayIndex = nullptr;
	}
	unsigned int CapitalTable::GetTableId() const
	{
		return Capital::TableId;
	}
	void CapitalTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void CapitalTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void CapitalTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void CapitalTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Capital::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Capital::TableId);
	}
	bool CapitalTable::Insert(Capital* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void CapitalTable::BatchInsert(std::vector<Capital*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				TradingDayIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool CapitalTable::Erase(const Capital& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Capital* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int CapitalTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		std::lock_guard publishGuard(publishMutex_);
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Capital*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Capital::Allocate();
				memcpy(compareRecord, &CompareCapital, sizeof(Capital));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, CapitalTableIndexTradingDay::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool CapitalTable::Update(const Capital& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Capital* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Capital:[%s]", newRecord.GetString());
				return false;
			}

			bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(liveRecord, &newRecord);
			CapitalTableIndexTradingDay::iterator itTradingDay;
			if (TradingDayIndexUpdate)
			{
				itTradingDay = TradingDayIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(Capital));
			if (TradingDayIndexUpdate)
			{
				TradingDayIndex->Update(itTradingDay);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void CapitalTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			TradingDayIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void CapitalTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Capitals.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,Balance,PreBalance,Available,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,Deposit,Withdraw,StampTax,TransferFee\n");
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
	bool CapitalTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr CapitalTable::MakeInsertEvent(const Capital* record)
	{
		auto eventRecord = Capital::Allocate();
		memcpy(eventRecord, record, sizeof(Capital));
		return std::make_shared<const RowChangeEvent>(Capital::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void CapitalTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void CapitalTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr CapitalTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Capital::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr CapitalTable::BuildInsertEvent(const Capital* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr CapitalTable::BuildUpdateEvent(const Capital& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Capital* eventRecord = Capital::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Capital));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Capital::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> CapitalTable::BuildBatchInsertEvents(const std::vector<Capital*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Capital* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	PositionTable::PositionTable()
	{
		PrimaryKey = new PositionTablePrimaryKey(this);
		AccountIndex = new PositionTableIndexAccount(this);
		TradingDayIndex = new PositionTableIndexTradingDay(this);
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
	unsigned int PositionTable::GetTableId() const
	{
		return Position::TableId;
	}
	void PositionTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void PositionTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void PositionTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void PositionTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Position::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Position::TableId);
	}
	bool PositionTable::Insert(Position* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void PositionTable::BatchInsert(std::vector<Position*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				AccountIndex->Insert(record);
				TradingDayIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool PositionTable::Erase(const Position& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Position* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int PositionTable::EraseByAccountIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		std::lock_guard publishGuard(publishMutex_);
		AccountIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Position*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Position::Allocate();
				memcpy(compareRecord, &ComparePosition, sizeof(Position));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PositionTableIndexAccount::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	int PositionTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		std::lock_guard publishGuard(publishMutex_);
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<Position*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Position::Allocate();
				memcpy(compareRecord, &ComparePosition, sizeof(Position));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PositionTableIndexTradingDay::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool PositionTable::Update(const Position& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Position* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Position:[%s]", newRecord.GetString());
				return false;
			}

			bool AccountIndexUpdate = AccountIndex->NeedUpdate(liveRecord, &newRecord);
			PositionTableIndexAccount::iterator itAccount;
			if (AccountIndexUpdate)
			{
				itAccount = AccountIndex->FindNode(liveRecord);
			}
			bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(liveRecord, &newRecord);
			PositionTableIndexTradingDay::iterator itTradingDay;
			if (TradingDayIndexUpdate)
			{
				itTradingDay = TradingDayIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(Position));
			if (AccountIndexUpdate)
			{
				AccountIndex->Update(itAccount);
			}
			if (TradingDayIndexUpdate)
			{
				TradingDayIndex->Update(itTradingDay);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void PositionTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			AccountIndex->index_.clear();
			TradingDayIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void PositionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Positions.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,PosiDirection,TotalPosition,PositionFrozen,TodayPosition,MarketValue,CashIn,CashOut,Margin,Commission,FrozenCash,FrozenMargin,FrozenCommission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice,StampTax,TransferFee\n");
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
	bool PositionTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr PositionTable::MakeInsertEvent(const Position* record)
	{
		auto eventRecord = Position::Allocate();
		memcpy(eventRecord, record, sizeof(Position));
		return std::make_shared<const RowChangeEvent>(Position::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void PositionTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void PositionTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr PositionTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Position::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr PositionTable::BuildInsertEvent(const Position* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr PositionTable::BuildUpdateEvent(const Position& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Position* eventRecord = Position::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Position));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Position::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> PositionTable::BuildBatchInsertEvents(const std::vector<Position*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Position* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	PositionDetailTable::PositionDetailTable()
	{
		PrimaryKey = new PositionDetailTablePrimaryKey(this);
		TradeMatchIndex = new PositionDetailTableIndexTradeMatch(this);
		TradingDayIndex = new PositionDetailTableIndexTradingDay(this);
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
	unsigned int PositionDetailTable::GetTableId() const
	{
		return PositionDetail::TableId;
	}
	void PositionDetailTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void PositionDetailTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void PositionDetailTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void PositionDetailTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(PositionDetail::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(PositionDetail::TableId);
	}
	bool PositionDetailTable::Insert(PositionDetail* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void PositionDetailTable::BatchInsert(std::vector<PositionDetail*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				TradeMatchIndex->Insert(record);
				TradingDayIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool PositionDetailTable::Erase(const PositionDetail& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PositionDetail* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int PositionDetailTable::EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		std::lock_guard publishGuard(publishMutex_);
		TradeMatchIndex->FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::vector<PositionDetail*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = PositionDetail::Allocate();
				memcpy(compareRecord, &ComparePositionDetail, sizeof(PositionDetail));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PositionDetailTableIndexTradeMatch::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	int PositionDetailTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		std::lock_guard publishGuard(publishMutex_);
		TradingDayIndex->FillCompareRecord(TradingDay);
		std::vector<PositionDetail*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = PositionDetail::Allocate();
				memcpy(compareRecord, &ComparePositionDetail, sizeof(PositionDetail));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PositionDetailTableIndexTradingDay::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool PositionDetailTable::Update(const PositionDetail& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PositionDetail* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for PositionDetail:[%s]", newRecord.GetString());
				return false;
			}

			bool TradeMatchIndexUpdate = TradeMatchIndex->NeedUpdate(liveRecord, &newRecord);
			PositionDetailTableIndexTradeMatch::iterator itTradeMatch;
			if (TradeMatchIndexUpdate)
			{
				itTradeMatch = TradeMatchIndex->FindNode(liveRecord);
			}
			bool TradingDayIndexUpdate = TradingDayIndex->NeedUpdate(liveRecord, &newRecord);
			PositionDetailTableIndexTradingDay::iterator itTradingDay;
			if (TradingDayIndexUpdate)
			{
				itTradingDay = TradingDayIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(PositionDetail));
			if (TradeMatchIndexUpdate)
			{
				TradeMatchIndex->Update(itTradeMatch);
			}
			if (TradingDayIndexUpdate)
			{
				TradingDayIndex->Update(itTradingDay);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void PositionDetailTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			TradeMatchIndex->index_.clear();
			TradingDayIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void PositionDetailTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//PositionDetails.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,PosiDirection,OpenDate,TradeId,Volume,OpenPrice,MarketValue,CashIn,CashOut,Margin,Commission,VolumeMultiple,CloseProfitByDate,CloseProfitByTrade,PositionProfitByDate,PositionProfitByTrade,SettlementPrice,PreSettlementPrice,CloseVolume,CloseAmount,StampTax,TransferFee\n");
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
	bool PositionDetailTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr PositionDetailTable::MakeInsertEvent(const PositionDetail* record)
	{
		auto eventRecord = PositionDetail::Allocate();
		memcpy(eventRecord, record, sizeof(PositionDetail));
		return std::make_shared<const RowChangeEvent>(PositionDetail::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void PositionDetailTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void PositionDetailTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr PositionDetailTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(PositionDetail::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr PositionDetailTable::BuildInsertEvent(const PositionDetail* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr PositionDetailTable::BuildUpdateEvent(const PositionDetail& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		PositionDetail* eventRecord = PositionDetail::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(PositionDetail));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			PositionDetail::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> PositionDetailTable::BuildBatchInsertEvents(const std::vector<PositionDetail*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const PositionDetail* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	OrderTable::OrderTable()
	{
		PrimaryKey = new OrderTablePrimaryKey(this);
		ClientOrderIdUniqueKey = new OrderTableUniqueKeyClientOrderId(this);
		AccountIdIndex = new OrderTableIndexAccountId(this);
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
	unsigned int OrderTable::GetTableId() const
	{
		return Order::TableId;
	}
	void OrderTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void OrderTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void OrderTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void OrderTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Order::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Order::TableId);
	}
	bool OrderTable::Insert(Order* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void OrderTable::BatchInsert(std::vector<Order*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);
				[[maybe_unused]] const bool insertedIntoClientOrderIdUniqueKey = ClientOrderIdUniqueKey->Insert(record);
				assert(insertedIntoClientOrderIdUniqueKey);

				AccountIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool OrderTable::Erase(const Order& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Order* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int OrderTable::EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		std::lock_guard publishGuard(publishMutex_);
		AccountIdIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Order*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Order::Allocate();
				memcpy(compareRecord, &CompareOrder, sizeof(Order));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, OrderTableIndexAccountId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool OrderTable::Update(const Order& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Order* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Order:[%s]", newRecord.GetString());
				return false;
			}
			// 唯一键字段不允许经 Update 改写
			if (!(ClientOrderIdUniqueKey->CheckUpdate(liveRecord, &newRecord)))
			{
				WriteLog(LogLevel::Warning, "Update Failed for Order:[%s]", newRecord.GetString());
				return false;
			}

			bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(liveRecord, &newRecord);
			OrderTableIndexAccountId::iterator itAccountId;
			if (AccountIdIndexUpdate)
			{
				itAccountId = AccountIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(Order));
			if (AccountIdIndexUpdate)
			{
				AccountIdIndex->Update(itAccountId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void OrderTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			ClientOrderIdUniqueKey->index_.clear();
			AccountIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void OrderTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Orders.csv";
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
	bool OrderTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr OrderTable::MakeInsertEvent(const Order* record)
	{
		auto eventRecord = Order::Allocate();
		memcpy(eventRecord, record, sizeof(Order));
		return std::make_shared<const RowChangeEvent>(Order::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void OrderTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void OrderTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr OrderTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Order::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr OrderTable::BuildInsertEvent(const Order* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr OrderTable::BuildUpdateEvent(const Order& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Order* eventRecord = Order::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Order));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Order::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> OrderTable::BuildBatchInsertEvents(const std::vector<Order*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Order* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	TradeTable::TradeTable()
	{
		PrimaryKey = new TradeTablePrimaryKey(this);
		AccountIdIndex = new TradeTableIndexAccountId(this);
	}
	TradeTable::~TradeTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
		delete AccountIdIndex;
		AccountIdIndex = nullptr;
	}
	unsigned int TradeTable::GetTableId() const
	{
		return Trade::TableId;
	}
	void TradeTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void TradeTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void TradeTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void TradeTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(Trade::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(Trade::TableId);
	}
	bool TradeTable::Insert(Trade* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void TradeTable::BatchInsert(std::vector<Trade*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				AccountIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool TradeTable::Erase(const Trade& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Trade* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int TradeTable::EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		std::lock_guard publishGuard(publishMutex_);
		AccountIdIndex->FillCompareRecord(TradingDay, AccountId);
		std::vector<Trade*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = Trade::Allocate();
				memcpy(compareRecord, &CompareTrade, sizeof(Trade));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, TradeTableIndexAccountId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool TradeTable::Update(const Trade& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			Trade* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for Trade:[%s]", newRecord.GetString());
				return false;
			}

			bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(liveRecord, &newRecord);
			TradeTableIndexAccountId::iterator itAccountId;
			if (AccountIdIndexUpdate)
			{
				itAccountId = AccountIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(Trade));
			if (AccountIdIndexUpdate)
			{
				AccountIdIndex->Update(itAccountId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void TradeTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			AccountIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void TradeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//Trades.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,AccountId,AccountType,ExchangeId,InstrumentId,ProductClass,OrderId,OrderSysId,TradeId,Direction,OffsetFlag,Price,Volume,VolumeMultiple,TradeAmount,Commission,TradeDate,TradeTime,StampTax,TransferFee\n");
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
	bool TradeTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr TradeTable::MakeInsertEvent(const Trade* record)
	{
		auto eventRecord = Trade::Allocate();
		memcpy(eventRecord, record, sizeof(Trade));
		return std::make_shared<const RowChangeEvent>(Trade::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void TradeTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void TradeTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr TradeTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(Trade::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr TradeTable::BuildInsertEvent(const Trade* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr TradeTable::BuildUpdateEvent(const Trade& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		Trade* eventRecord = Trade::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(Trade));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			Trade::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> TradeTable::BuildBatchInsertEvents(const std::vector<Trade*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const Trade* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	AccountLoginSessionTable::AccountLoginSessionTable()
	{
		PrimaryKey = new AccountLoginSessionTablePrimaryKey(this);
		SessionIdIndex = new AccountLoginSessionTableIndexSessionId(this);
		AccountIdIndex = new AccountLoginSessionTableIndexAccountId(this);
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
	unsigned int AccountLoginSessionTable::GetTableId() const
	{
		return AccountLoginSession::TableId;
	}
	void AccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void AccountLoginSessionTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void AccountLoginSessionTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void AccountLoginSessionTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(AccountLoginSession::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(AccountLoginSession::TableId);
	}
	bool AccountLoginSessionTable::Insert(AccountLoginSession* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void AccountLoginSessionTable::BatchInsert(std::vector<AccountLoginSession*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				SessionIdIndex->Insert(record);
				AccountIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool AccountLoginSessionTable::Erase(const AccountLoginSession& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			AccountLoginSession* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int AccountLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		std::lock_guard publishGuard(publishMutex_);
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<AccountLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = AccountLoginSession::Allocate();
				memcpy(compareRecord, &CompareAccountLoginSession, sizeof(AccountLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, AccountLoginSessionTableIndexSessionId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	int AccountLoginSessionTable::EraseByAccountIdIndex(const AccountIdType& AccountId)
	{
		std::lock_guard publishGuard(publishMutex_);
		AccountIdIndex->FillCompareRecord(AccountId);
		std::vector<AccountLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = AccountLoginSession::Allocate();
				memcpy(compareRecord, &CompareAccountLoginSession, sizeof(AccountLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, AccountLoginSessionTableIndexAccountId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool AccountLoginSessionTable::Update(const AccountLoginSession& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			AccountLoginSession* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for AccountLoginSession:[%s]", newRecord.GetString());
				return false;
			}

			bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(liveRecord, &newRecord);
			AccountLoginSessionTableIndexSessionId::iterator itSessionId;
			if (SessionIdIndexUpdate)
			{
				itSessionId = SessionIdIndex->FindNode(liveRecord);
			}
			bool AccountIdIndexUpdate = AccountIdIndex->NeedUpdate(liveRecord, &newRecord);
			AccountLoginSessionTableIndexAccountId::iterator itAccountId;
			if (AccountIdIndexUpdate)
			{
				itAccountId = AccountIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(AccountLoginSession));
			if (SessionIdIndexUpdate)
			{
				SessionIdIndex->Update(itSessionId);
			}
			if (AccountIdIndexUpdate)
			{
				AccountIdIndex->Update(itAccountId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void AccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			SessionIdIndex->index_.clear();
			AccountIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void AccountLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//AccountLoginSessions.csv";
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
	bool AccountLoginSessionTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr AccountLoginSessionTable::MakeInsertEvent(const AccountLoginSession* record)
	{
		auto eventRecord = AccountLoginSession::Allocate();
		memcpy(eventRecord, record, sizeof(AccountLoginSession));
		return std::make_shared<const RowChangeEvent>(AccountLoginSession::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void AccountLoginSessionTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void AccountLoginSessionTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr AccountLoginSessionTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(AccountLoginSession::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr AccountLoginSessionTable::BuildInsertEvent(const AccountLoginSession* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr AccountLoginSessionTable::BuildUpdateEvent(const AccountLoginSession& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		AccountLoginSession* eventRecord = AccountLoginSession::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(AccountLoginSession));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			AccountLoginSession::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> AccountLoginSessionTable::BuildBatchInsertEvents(const std::vector<AccountLoginSession*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const AccountLoginSession* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	PrimaryAccountLoginSessionTable::PrimaryAccountLoginSessionTable()
	{
		PrimaryKey = new PrimaryAccountLoginSessionTablePrimaryKey(this);
		SessionIdIndex = new PrimaryAccountLoginSessionTableIndexSessionId(this);
		PrimaryAccountIdIndex = new PrimaryAccountLoginSessionTableIndexPrimaryAccountId(this);
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
	unsigned int PrimaryAccountLoginSessionTable::GetTableId() const
	{
		return PrimaryAccountLoginSession::TableId;
	}
	void PrimaryAccountLoginSessionTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void PrimaryAccountLoginSessionTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void PrimaryAccountLoginSessionTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void PrimaryAccountLoginSessionTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(PrimaryAccountLoginSession::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(PrimaryAccountLoginSession::TableId);
	}
	bool PrimaryAccountLoginSessionTable::Insert(PrimaryAccountLoginSession* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
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
			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void PrimaryAccountLoginSessionTable::BatchInsert(std::vector<PrimaryAccountLoginSession*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

				SessionIdIndex->Insert(record);
				PrimaryAccountIdIndex->Insert(record);
			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool PrimaryAccountLoginSessionTable::Erase(const PrimaryAccountLoginSession& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PrimaryAccountLoginSession* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	int PrimaryAccountLoginSessionTable::EraseBySessionIdIndex(const SessionIdType& SessionId)
	{
		std::lock_guard publishGuard(publishMutex_);
		SessionIdIndex->FillCompareRecord(SessionId);
		std::vector<PrimaryAccountLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = PrimaryAccountLoginSession::Allocate();
				memcpy(compareRecord, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PrimaryAccountLoginSessionTableIndexSessionId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	int PrimaryAccountLoginSessionTable::EraseByPrimaryAccountIdIndex(const AccountIdType& PrimaryAccountId)
	{
		std::lock_guard publishGuard(publishMutex_);
		PrimaryAccountIdIndex->FillCompareRecord(PrimaryAccountId);
		std::vector<PrimaryAccountLoginSession*> records;
		RowChangeEventPtr event;
		{
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
			if (HasSubscribers())
			{
				auto compareRecord = PrimaryAccountLoginSession::Allocate();
				memcpy(compareRecord, &ComparePrimaryAccountLoginSession, sizeof(PrimaryAccountLoginSession));
				event = BuildRowChangeEvent(RowChangeType::EraseByIndex, PrimaryAccountLoginSessionTableIndexPrimaryAccountId::IndexID, true, AdoptRecord(compareRecord));
			}
		}
		PublishRowChange(event);
		return static_cast<int>(records.size());
	}
	bool PrimaryAccountLoginSessionTable::Update(const PrimaryAccountLoginSession& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			PrimaryAccountLoginSession* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccountLoginSession:[%s]", newRecord.GetString());
				return false;
			}

			bool SessionIdIndexUpdate = SessionIdIndex->NeedUpdate(liveRecord, &newRecord);
			PrimaryAccountLoginSessionTableIndexSessionId::iterator itSessionId;
			if (SessionIdIndexUpdate)
			{
				itSessionId = SessionIdIndex->FindNode(liveRecord);
			}
			bool PrimaryAccountIdIndexUpdate = PrimaryAccountIdIndex->NeedUpdate(liveRecord, &newRecord);
			PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator itPrimaryAccountId;
			if (PrimaryAccountIdIndexUpdate)
			{
				itPrimaryAccountId = PrimaryAccountIdIndex->FindNode(liveRecord);
			}
			::memcpy(liveRecord, &newRecord, sizeof(PrimaryAccountLoginSession));
			if (SessionIdIndexUpdate)
			{
				SessionIdIndex->Update(itSessionId);
			}
			if (PrimaryAccountIdIndexUpdate)
			{
				PrimaryAccountIdIndex->Update(itPrimaryAccountId);
			}

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void PrimaryAccountLoginSessionTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
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
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			SessionIdIndex->index_.clear();
			PrimaryAccountIdIndex->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void PrimaryAccountLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//PrimaryAccountLoginSessions.csv";
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
	bool PrimaryAccountLoginSessionTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr PrimaryAccountLoginSessionTable::MakeInsertEvent(const PrimaryAccountLoginSession* record)
	{
		auto eventRecord = PrimaryAccountLoginSession::Allocate();
		memcpy(eventRecord, record, sizeof(PrimaryAccountLoginSession));
		return std::make_shared<const RowChangeEvent>(PrimaryAccountLoginSession::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void PrimaryAccountLoginSessionTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void PrimaryAccountLoginSessionTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr PrimaryAccountLoginSessionTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(PrimaryAccountLoginSession::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr PrimaryAccountLoginSessionTable::BuildInsertEvent(const PrimaryAccountLoginSession* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr PrimaryAccountLoginSessionTable::BuildUpdateEvent(const PrimaryAccountLoginSession& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		PrimaryAccountLoginSession* eventRecord = PrimaryAccountLoginSession::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(PrimaryAccountLoginSession));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			PrimaryAccountLoginSession::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> PrimaryAccountLoginSessionTable::BuildBatchInsertEvents(const std::vector<PrimaryAccountLoginSession*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const PrimaryAccountLoginSession* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	CommissionGroupTable::CommissionGroupTable()
	{
		PrimaryKey = new CommissionGroupTablePrimaryKey(this);
	}
	CommissionGroupTable::~CommissionGroupTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int CommissionGroupTable::GetTableId() const
	{
		return CommissionGroup::TableId;
	}
	void CommissionGroupTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void CommissionGroupTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void CommissionGroupTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void CommissionGroupTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(CommissionGroup::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(CommissionGroup::TableId);
	}
	bool CommissionGroupTable::Insert(CommissionGroup* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for CommissionGroup:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void CommissionGroupTable::BatchInsert(std::vector<CommissionGroup*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool CommissionGroupTable::Erase(const CommissionGroup& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			CommissionGroup* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool CommissionGroupTable::Update(const CommissionGroup& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			CommissionGroup* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for CommissionGroup:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(CommissionGroup));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void CommissionGroupTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void CommissionGroupTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void CommissionGroupTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//CommissionGroups.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "CommissionGroupId,CommissionGroupName\n");
		char buff[4096] = { 0 };
		set<CommissionGroup*, CommissionGroupLessForCommissionGroupPrimaryKey> records;
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
	void CommissionGroupTable::EraseUniqueKey(CommissionGroup* record)
	{
		PrimaryKey->Erase(record);
	}
	void CommissionGroupTable::EraseIndex(CommissionGroup* record)
	{
	}
	bool CommissionGroupTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr CommissionGroupTable::MakeInsertEvent(const CommissionGroup* record)
	{
		auto eventRecord = CommissionGroup::Allocate();
		memcpy(eventRecord, record, sizeof(CommissionGroup));
		return std::make_shared<const RowChangeEvent>(CommissionGroup::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void CommissionGroupTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void CommissionGroupTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr CommissionGroupTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(CommissionGroup::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr CommissionGroupTable::BuildInsertEvent(const CommissionGroup* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr CommissionGroupTable::BuildUpdateEvent(const CommissionGroup& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		CommissionGroup* eventRecord = CommissionGroup::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(CommissionGroup));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			CommissionGroup::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> CommissionGroupTable::BuildBatchInsertEvents(const std::vector<CommissionGroup*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const CommissionGroup* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

	BaseCommissionTable::BaseCommissionTable()
	{
		PrimaryKey = new BaseCommissionTablePrimaryKey(this);
	}
	BaseCommissionTable::~BaseCommissionTable()
	{
		delete PrimaryKey;
		PrimaryKey = nullptr;
	}
	unsigned int BaseCommissionTable::GetTableId() const
	{
		return BaseCommission::TableId;
	}
	void BaseCommissionTable::Subscribe(MdbSubscriber* subscriber)
	{
		if (subscriber == nullptr)
		{
			return;
		}
		subscribers_.push_back(subscriber);
	}
	void BaseCommissionTable::SubscribeReplica(MdbReplicaSubscriber* replica)
	{
		replicaSubscriber_ = replica;
	}
	void BaseCommissionTable::UnSubscribe()
	{
		subscribers_.clear();
		replicaSubscriber_ = nullptr;
	}
	void BaseCommissionTable::InitDb()
	{
		if (replicaSubscriber_ == nullptr)
		{
			return;
		}
		// 清表、拷贝、批量、就绪置位在发布屏障与读租约内完成：写事务要么已发布，要么被挡在屏障外，
		// 释放后到达的增量必然排在批量之后
		std::lock_guard publishGuard(publishMutex_);
		std::shared_lock guard(SharedMutex);
		replicaSubscriber_->OnSnapshotBegin(BaseCommission::TableId);
		if (!PrimaryKey->index_.empty())
		{
			std::vector<RowChangeEventPtr> events;
			events.reserve(PrimaryKey->index_.size());
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				events.push_back(MakeInsertEvent(*it));
			}
			replicaSubscriber_->OnRowBatchChange(events);
		}
		replicaSubscriber_->OnSnapshotComplete(BaseCommission::TableId);
	}
	bool BaseCommissionTable::Insert(BaseCommission* record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			if (!PrimaryKey->CheckInsert(record))
			{
				WriteLog(LogLevel::Warning, "Insert Failed for BaseCommission:[%s]", record->GetString());
				record->Deallocate();
				return false;
			}

			PrimaryKey->Insert(record);

			event = BuildInsertEvent(record);
		}
		PublishRowChange(event);
		return true;
	}
	void BaseCommissionTable::BatchInsert(std::vector<BaseCommission*>& records)
	{
		std::lock_guard publishGuard(publishMutex_);
		std::vector<RowChangeEventPtr> events;
		{
			std::lock_guard guard(SharedMutex);
			for (auto record : records)
			{
				[[maybe_unused]] const bool insertedIntoPrimaryKey = PrimaryKey->Insert(record);
				assert(insertedIntoPrimaryKey);

			}
			events = BuildBatchInsertEvents(records);
			records.clear();
		}
		PublishRowBatchChange(events);
	}
	bool BaseCommissionTable::Erase(const BaseCommission& record)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			BaseCommission* liveRecord = PrimaryKey->Find(&record);
			if (liveRecord == nullptr)
			{
				return false;
			}
			EraseUniqueKey(liveRecord);
			EraseIndex(liveRecord);
			// 离表的是表内那条记录，传进来的只是个带主键的副本
			event = BuildRowChangeEvent(RowChangeType::Erase, 0, true, AdoptRecord(liveRecord));
		}
		PublishRowChange(event);
		return true;
	}
	bool BaseCommissionTable::Update(const BaseCommission& newRecord, bool updateDB)
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			BaseCommission* liveRecord = PrimaryKey->Find(&newRecord);
			if (liveRecord == nullptr)
			{
				WriteLog(LogLevel::Warning, "Update Failed for BaseCommission:[%s]", newRecord.GetString());
				return false;
			}

			::memcpy(liveRecord, &newRecord, sizeof(BaseCommission));

			event = BuildUpdateEvent(newRecord, updateDB);
		}
		PublishRowChange(event);
		return true;
	}
	void BaseCommissionTable::TruncateTables()
	{
		std::lock_guard publishGuard(publishMutex_);
		std::lock_guard guard(SharedMutex);
		for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
		{
			(*it)->Deallocate();
		}
		PrimaryKey->index_.clear();
	}
	void BaseCommissionTable::TruncateTable()
	{
		std::lock_guard publishGuard(publishMutex_);
		RowChangeEventPtr event;
		{
			std::lock_guard guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				(*it)->Deallocate();
			}
			PrimaryKey->index_.clear();
			event = BuildRowChangeEvent(RowChangeType::Truncate, 0, true, RecordHandle());
		}
		PublishRowChange(event);
	}
	void BaseCommissionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//BaseCommissions.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "CommissionGroupId,ExchangeId,InstrumentId,Direction,OpenByMoney,CloseByMoney,OpenByVolume,CloseByVolume,OpenStampTaxByMoney,CloseStampTaxByMoney,OpenTransferFeeByMoney,CloseTransferFeeByMoney,MinCommission,MaxCommission\n");
		char buff[4096] = { 0 };
		set<BaseCommission*, BaseCommissionLessForBaseCommissionPrimaryKey> records;
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
	void BaseCommissionTable::EraseUniqueKey(BaseCommission* record)
	{
		PrimaryKey->Erase(record);
	}
	void BaseCommissionTable::EraseIndex(BaseCommission* record)
	{
	}
	bool BaseCommissionTable::HasSubscribers() const
	{
		return replicaSubscriber_ != nullptr || !subscribers_.empty();
	}
	RowChangeEventPtr BaseCommissionTable::MakeInsertEvent(const BaseCommission* record)
	{
		auto eventRecord = BaseCommission::Allocate();
		memcpy(eventRecord, record, sizeof(BaseCommission));
		return std::make_shared<const RowChangeEvent>(BaseCommission::TableId, RowChangeType::Insert, 0, ++sequence_, true, AdoptRecord(eventRecord));
	}
	void BaseCommissionTable::PublishRowChange(const RowChangeEventPtr& event)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowChange(event);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowChange(event);
		}
	}
	void BaseCommissionTable::PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events)
	{
		if (replicaSubscriber_ != nullptr)
		{
			replicaSubscriber_->OnRowBatchChange(events);
		}
		for (MdbSubscriber* subscriber : subscribers_)
		{
			subscriber->OnRowBatchChange(events);
		}
	}
	RowChangeEventPtr BaseCommissionTable::BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return std::make_shared<const RowChangeEvent>(BaseCommission::TableId, type, indexId, ++sequence_, persistDatabase, std::move(record));
	}
	RowChangeEventPtr BaseCommissionTable::BuildInsertEvent(const BaseCommission* record)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		return MakeInsertEvent(record);
	}
	RowChangeEventPtr BaseCommissionTable::BuildUpdateEvent(const BaseCommission& newRecord, bool updateDB)
	{
		if (!HasSubscribers())
		{
			return nullptr;
		}
		BaseCommission* eventRecord = BaseCommission::Allocate();
		memcpy(eventRecord, &newRecord, sizeof(BaseCommission));
		// updateDB 只表示"这条变更不落库"，行变更照常广播，由副本订阅者自行忽略
		return std::make_shared<const RowChangeEvent>(
			BaseCommission::TableId, RowChangeType::Update, 0, ++sequence_, updateDB, AdoptRecord(eventRecord));
	}
	std::vector<RowChangeEventPtr> BaseCommissionTable::BuildBatchInsertEvents(const std::vector<BaseCommission*>& records)
	{
		std::vector<RowChangeEventPtr> events;
		if (!HasSubscribers())
		{
			return events;
		}
		events.reserve(records.size());
		for (const BaseCommission* record : records)
		{
			events.push_back(MakeInsertEvent(record));
		}
		return events;
	}

}

