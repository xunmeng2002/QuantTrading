#include "MdbTables.h"
#include "Mdb.h"
#include "Logger.h"
#include <string>
#include <string.h>
#include <set>
#include <list>

using std::string;
using std::set;
using std::list;

namespace mdb
{
	TradingDayTable::TradingDayTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new TradingDayPrimaryKey(this);
	}
	TradingDayTable::~TradingDayTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void TradingDayTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void TradingDayTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void TradingDayTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void TradingDayTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void TradingDayTable::InitDB()
	{
		m_MdbSubscriber->OnTradingDayTruncate();
		
		std::list<TradingDay*>* records = new std::list<TradingDay*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new TradingDay(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnTradingDayBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool TradingDayTable::Insert(TradingDay* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for TradingDay:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradingDayInsert(record);
		}
		return true;
	}
	void TradingDayTable::BatchInsert(std::list<mdb::TradingDay*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = TradingDay::Allocate();
				memcpy(newRecord, record, sizeof(TradingDay));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradingDayBatchInsert(records);
		}
	}
	void TradingDayTable::Erase(TradingDay* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradingDayErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool TradingDayTable::Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for TradingDay:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New TradingDay:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(TradingDay));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradingDayUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void TradingDayTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void TradingDayTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradingDayTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void TradingDayTable::EraseIndex(TradingDay* record)
	{
	}

	ExchangeTable::ExchangeTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new ExchangePrimaryKey(this);
	}
	ExchangeTable::~ExchangeTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void ExchangeTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void ExchangeTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void ExchangeTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void ExchangeTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void ExchangeTable::InitDB()
	{
		m_MdbSubscriber->OnExchangeTruncate();
		
		std::list<Exchange*>* records = new std::list<Exchange*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Exchange(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnExchangeBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool ExchangeTable::Insert(Exchange* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Exchange:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnExchangeInsert(record);
		}
		return true;
	}
	void ExchangeTable::BatchInsert(std::list<mdb::Exchange*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Exchange::Allocate();
				memcpy(newRecord, record, sizeof(Exchange));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnExchangeBatchInsert(records);
		}
	}
	void ExchangeTable::Erase(Exchange* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnExchangeErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool ExchangeTable::Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Exchange:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Exchange:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Exchange));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnExchangeUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void ExchangeTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void ExchangeTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnExchangeTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void ExchangeTable::EraseIndex(Exchange* record)
	{
	}

	ProductTable::ProductTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new ProductPrimaryKey(this);
	}
	ProductTable::~ProductTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void ProductTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void ProductTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void ProductTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void ProductTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void ProductTable::InitDB()
	{
		m_MdbSubscriber->OnProductTruncate();
		
		std::list<Product*>* records = new std::list<Product*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Product(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnProductBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool ProductTable::Insert(Product* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Product:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnProductInsert(record);
		}
		return true;
	}
	void ProductTable::BatchInsert(std::list<mdb::Product*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Product::Allocate();
				memcpy(newRecord, record, sizeof(Product));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnProductBatchInsert(records);
		}
	}
	void ProductTable::Erase(Product* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnProductErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool ProductTable::Update(Product* const oldRecord, Product* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Product:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Product:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Product));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnProductUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void ProductTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void ProductTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnProductTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void ProductTable::EraseIndex(Product* record)
	{
	}

	HotInstrumentTable::HotInstrumentTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new HotInstrumentPrimaryKey(this);
		m_TradingDayIndex = new HotInstrumentIndexTradingDay(this);
	}
	HotInstrumentTable::~HotInstrumentTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_TradingDayIndex;
		m_TradingDayIndex = nullptr;
	}
	void HotInstrumentTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void HotInstrumentTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void HotInstrumentTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void HotInstrumentTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void HotInstrumentTable::InitDB()
	{
		m_MdbSubscriber->OnHotInstrumentTruncate();
		
		std::list<HotInstrument*>* records = new std::list<HotInstrument*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new HotInstrument(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnHotInstrumentBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool HotInstrumentTable::Insert(HotInstrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for HotInstrument:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_TradingDayIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnHotInstrumentInsert(record);
		}
		return true;
	}
	void HotInstrumentTable::BatchInsert(std::list<mdb::HotInstrument*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = HotInstrument::Allocate();
				memcpy(newRecord, record, sizeof(HotInstrument));
				m_PrimaryKey->Insert(newRecord);

				m_TradingDayIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnHotInstrumentBatchInsert(records);
		}
	}
	void HotInstrumentTable::Erase(HotInstrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnHotInstrumentErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int HotInstrumentTable::EraseByTradingDayIndex(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay)
	{
		m_TradingDayIndex->FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		list<HotInstrument*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_TradingDayIndex->m_Index.equal_range(&t_CompareHotInstrument);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = HotInstrument::Allocate();
			memcpy(record, &t_CompareHotInstrument, sizeof(HotInstrument));
			m_MdbSubscriber->OnHotInstrumentEraseByTradingDayIndex(record);
		}
		return (int)records.size();
	}
	bool HotInstrumentTable::Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for HotInstrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New HotInstrument:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool TradingDayIndexUpdate = m_TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		HotInstrumentIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = m_TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(HotInstrument));
		if (TradingDayIndexUpdate)
		{
			m_TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnHotInstrumentUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void HotInstrumentTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
	}
	void HotInstrumentTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnHotInstrumentTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void HotInstrumentTable::EraseIndex(HotInstrument* record)
	{
		m_TradingDayIndex->Erase(record);
	}

	InstrumentTable::InstrumentTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new InstrumentPrimaryKey(this);
	}
	InstrumentTable::~InstrumentTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void InstrumentTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void InstrumentTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void InstrumentTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void InstrumentTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void InstrumentTable::InitDB()
	{
		m_DBInited = true;
	}
	bool InstrumentTable::Insert(Instrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Instrument:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnInstrumentInsert(record);
		}
		return true;
	}
	void InstrumentTable::BatchInsert(std::list<mdb::Instrument*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Instrument::Allocate();
				memcpy(newRecord, record, sizeof(Instrument));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnInstrumentBatchInsert(records);
		}
	}
	void InstrumentTable::Erase(Instrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnInstrumentErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool InstrumentTable::Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Instrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Instrument:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Instrument));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnInstrumentUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void InstrumentTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void InstrumentTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnInstrumentTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void InstrumentTable::EraseIndex(Instrument* record)
	{
	}

	PrimaryAccountTable::PrimaryAccountTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new PrimaryAccountPrimaryKey(this);
		m_OfferIDIndex = new PrimaryAccountIndexOfferID(this);
	}
	PrimaryAccountTable::~PrimaryAccountTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_OfferIDIndex;
		m_OfferIDIndex = nullptr;
	}
	void PrimaryAccountTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void PrimaryAccountTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void PrimaryAccountTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void PrimaryAccountTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void PrimaryAccountTable::InitDB()
	{
		m_MdbSubscriber->OnPrimaryAccountTruncate();
		
		std::list<PrimaryAccount*>* records = new std::list<PrimaryAccount*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new PrimaryAccount(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnPrimaryAccountBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool PrimaryAccountTable::Insert(PrimaryAccount* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PrimaryAccount:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_OfferIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPrimaryAccountInsert(record);
		}
		return true;
	}
	void PrimaryAccountTable::BatchInsert(std::list<mdb::PrimaryAccount*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PrimaryAccount::Allocate();
				memcpy(newRecord, record, sizeof(PrimaryAccount));
				m_PrimaryKey->Insert(newRecord);

				m_OfferIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPrimaryAccountBatchInsert(records);
		}
	}
	void PrimaryAccountTable::Erase(PrimaryAccount* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPrimaryAccountErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int PrimaryAccountTable::EraseByOfferIDIndex(const OfferIDType& OfferID)
	{
		m_OfferIDIndex->FillCompareRecord(OfferID);
		list<PrimaryAccount*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_OfferIDIndex->m_Index.equal_range(&t_ComparePrimaryAccount);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = PrimaryAccount::Allocate();
			memcpy(record, &t_ComparePrimaryAccount, sizeof(PrimaryAccount));
			m_MdbSubscriber->OnPrimaryAccountEraseByOfferIDIndex(record);
		}
		return (int)records.size();
	}
	bool PrimaryAccountTable::Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PrimaryAccount:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PrimaryAccount:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool OfferIDIndexUpdate = m_OfferIDIndex->NeedUpdate(oldRecord, newRecord);
		PrimaryAccountIndexOfferID::iterator itOfferID;
		if (OfferIDIndexUpdate)
		{
			itOfferID = m_OfferIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(PrimaryAccount));
		if (OfferIDIndexUpdate)
		{
			m_OfferIDIndex->Update(itOfferID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPrimaryAccountUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void PrimaryAccountTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_OfferIDIndex->m_Index.clear();
	}
	void PrimaryAccountTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_OfferIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPrimaryAccountTruncate();
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

		fprintf(dumpFile, "PrimaryAccountID,PrimaryAccountName,AccountClass,BrokerPassword,OfferID,IsAllowLogin,IsSimulateAccount,LoginStatus,InitStatus\n");
		char buff[4096] = { 0 };
		set<PrimaryAccount*, PrimaryAccountLessForPrimaryAccountPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void PrimaryAccountTable::EraseIndex(PrimaryAccount* record)
	{
		m_OfferIDIndex->Erase(record);
	}

	AccountTable::AccountTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new AccountPrimaryKey(this);
	}
	AccountTable::~AccountTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void AccountTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void AccountTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void AccountTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void AccountTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void AccountTable::InitDB()
	{
		m_MdbSubscriber->OnAccountTruncate();
		
		std::list<Account*>* records = new std::list<Account*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Account(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnAccountBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool AccountTable::Insert(Account* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Account:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnAccountInsert(record);
		}
		return true;
	}
	void AccountTable::BatchInsert(std::list<mdb::Account*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Account::Allocate();
				memcpy(newRecord, record, sizeof(Account));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnAccountBatchInsert(records);
		}
	}
	void AccountTable::Erase(Account* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnAccountErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool AccountTable::Update(Account* const oldRecord, Account* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Account:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Account:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Account));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnAccountUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void AccountTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void AccountTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnAccountTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void AccountTable::EraseIndex(Account* record)
	{
	}

	CapitalTable::CapitalTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new CapitalPrimaryKey(this);
		m_TradingDayIndex = new CapitalIndexTradingDay(this);
	}
	CapitalTable::~CapitalTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_TradingDayIndex;
		m_TradingDayIndex = nullptr;
	}
	void CapitalTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void CapitalTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void CapitalTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void CapitalTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void CapitalTable::InitDB()
	{
		m_MdbSubscriber->OnCapitalTruncate();
		
		std::list<Capital*>* records = new std::list<Capital*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Capital(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnCapitalBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool CapitalTable::Insert(Capital* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Capital:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_TradingDayIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnCapitalInsert(record);
		}
		return true;
	}
	void CapitalTable::BatchInsert(std::list<mdb::Capital*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Capital::Allocate();
				memcpy(newRecord, record, sizeof(Capital));
				m_PrimaryKey->Insert(newRecord);

				m_TradingDayIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnCapitalBatchInsert(records);
		}
	}
	void CapitalTable::Erase(Capital* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnCapitalErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int CapitalTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		m_TradingDayIndex->FillCompareRecord(TradingDay);
		list<Capital*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_TradingDayIndex->m_Index.equal_range(&t_CompareCapital);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = Capital::Allocate();
			memcpy(record, &t_CompareCapital, sizeof(Capital));
			m_MdbSubscriber->OnCapitalEraseByTradingDayIndex(record);
		}
		return (int)records.size();
	}
	bool CapitalTable::Update(Capital* const oldRecord, Capital* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Capital:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Capital:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool TradingDayIndexUpdate = m_TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		CapitalIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = m_TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(Capital));
		if (TradingDayIndexUpdate)
		{
			m_TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnCapitalUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void CapitalTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
	}
	void CapitalTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnCapitalTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void CapitalTable::EraseIndex(Capital* record)
	{
		m_TradingDayIndex->Erase(record);
	}

	PositionTable::PositionTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new PositionPrimaryKey(this);
		m_AccountIndex = new PositionIndexAccount(this);
		m_TradingDayIndex = new PositionIndexTradingDay(this);
	}
	PositionTable::~PositionTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_AccountIndex;
		m_AccountIndex = nullptr;
		delete m_TradingDayIndex;
		m_TradingDayIndex = nullptr;
	}
	void PositionTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void PositionTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void PositionTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void PositionTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void PositionTable::InitDB()
	{
		m_MdbSubscriber->OnPositionTruncate();
		
		std::list<Position*>* records = new std::list<Position*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Position(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnPositionBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool PositionTable::Insert(Position* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Position:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_AccountIndex->Insert(record);
		m_TradingDayIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionInsert(record);
		}
		return true;
	}
	void PositionTable::BatchInsert(std::list<mdb::Position*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Position::Allocate();
				memcpy(newRecord, record, sizeof(Position));
				m_PrimaryKey->Insert(newRecord);

				m_AccountIndex->Insert(newRecord);
				m_TradingDayIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionBatchInsert(records);
		}
	}
	void PositionTable::Erase(Position* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int PositionTable::EraseByAccountIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		m_AccountIndex->FillCompareRecord(TradingDay, AccountID);
		list<Position*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_AccountIndex->m_Index.equal_range(&t_ComparePosition);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &t_ComparePosition, sizeof(Position));
			m_MdbSubscriber->OnPositionEraseByAccountIndex(record);
		}
		return (int)records.size();
	}
	int PositionTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		m_TradingDayIndex->FillCompareRecord(TradingDay);
		list<Position*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_TradingDayIndex->m_Index.equal_range(&t_ComparePosition);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = Position::Allocate();
			memcpy(record, &t_ComparePosition, sizeof(Position));
			m_MdbSubscriber->OnPositionEraseByTradingDayIndex(record);
		}
		return (int)records.size();
	}
	bool PositionTable::Update(Position* const oldRecord, Position* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Position:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Position:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool AccountIndexUpdate = m_AccountIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexAccount::iterator itAccount;
		if (AccountIndexUpdate)
		{
			itAccount = m_AccountIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = m_TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = m_TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(Position));
		if (AccountIndexUpdate)
		{
			m_AccountIndex->Update(itAccount);
		}
		if (TradingDayIndexUpdate)
		{
			m_TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void PositionTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIndex->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
	}
	void PositionTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIndex->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void PositionTable::EraseIndex(Position* record)
	{
		m_AccountIndex->Erase(record);
		m_TradingDayIndex->Erase(record);
	}

	PositionDetailTable::PositionDetailTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new PositionDetailPrimaryKey(this);
		m_TradeMatchIndex = new PositionDetailIndexTradeMatch(this);
		m_TradingDayIndex = new PositionDetailIndexTradingDay(this);
	}
	PositionDetailTable::~PositionDetailTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_TradeMatchIndex;
		m_TradeMatchIndex = nullptr;
		delete m_TradingDayIndex;
		m_TradingDayIndex = nullptr;
	}
	void PositionDetailTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void PositionDetailTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void PositionDetailTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void PositionDetailTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void PositionDetailTable::InitDB()
	{
		m_MdbSubscriber->OnPositionDetailTruncate();
		
		std::list<PositionDetail*>* records = new std::list<PositionDetail*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new PositionDetail(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnPositionDetailBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool PositionDetailTable::Insert(PositionDetail* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for PositionDetail:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_TradeMatchIndex->Insert(record);
		m_TradingDayIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionDetailInsert(record);
		}
		return true;
	}
	void PositionDetailTable::BatchInsert(std::list<mdb::PositionDetail*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = PositionDetail::Allocate();
				memcpy(newRecord, record, sizeof(PositionDetail));
				m_PrimaryKey->Insert(newRecord);

				m_TradeMatchIndex->Insert(newRecord);
				m_TradingDayIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionDetailBatchInsert(records);
		}
	}
	void PositionDetailTable::Erase(PositionDetail* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionDetailErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int PositionDetailTable::EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		m_TradeMatchIndex->FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		list<PositionDetail*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_TradeMatchIndex->m_Index.equal_range(&t_ComparePositionDetail);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &t_ComparePositionDetail, sizeof(PositionDetail));
			m_MdbSubscriber->OnPositionDetailEraseByTradeMatchIndex(record);
		}
		return (int)records.size();
	}
	int PositionDetailTable::EraseByTradingDayIndex(const DateType& TradingDay)
	{
		m_TradingDayIndex->FillCompareRecord(TradingDay);
		list<PositionDetail*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_TradingDayIndex->m_Index.equal_range(&t_ComparePositionDetail);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = PositionDetail::Allocate();
			memcpy(record, &t_ComparePositionDetail, sizeof(PositionDetail));
			m_MdbSubscriber->OnPositionDetailEraseByTradingDayIndex(record);
		}
		return (int)records.size();
	}
	bool PositionDetailTable::Update(PositionDetail* const oldRecord, PositionDetail* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for PositionDetail:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New PositionDetail:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool TradeMatchIndexUpdate = m_TradeMatchIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradeMatch::iterator itTradeMatch;
		if (TradeMatchIndexUpdate)
		{
			itTradeMatch = m_TradeMatchIndex->FindNode(oldRecord);
		}
		bool TradingDayIndexUpdate = m_TradingDayIndex->NeedUpdate(oldRecord, newRecord);
		PositionDetailIndexTradingDay::iterator itTradingDay;
		if (TradingDayIndexUpdate)
		{
			itTradingDay = m_TradingDayIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(PositionDetail));
		if (TradeMatchIndexUpdate)
		{
			m_TradeMatchIndex->Update(itTradeMatch);
		}
		if (TradingDayIndexUpdate)
		{
			m_TradingDayIndex->Update(itTradingDay);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionDetailUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void PositionDetailTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradeMatchIndex->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
	}
	void PositionDetailTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_TradeMatchIndex->m_Index.clear();
		m_TradingDayIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnPositionDetailTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void PositionDetailTable::EraseIndex(PositionDetail* record)
	{
		m_TradeMatchIndex->Erase(record);
		m_TradingDayIndex->Erase(record);
	}

	OrderTable::OrderTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new OrderPrimaryKey(this);
		m_ClientOrderIDUniqueKey = new OrderUniqueKeyClientOrderID(this);
	}
	OrderTable::~OrderTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_ClientOrderIDUniqueKey;
		m_ClientOrderIDUniqueKey = nullptr;
	}
	void OrderTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void OrderTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void OrderTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void OrderTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void OrderTable::InitDB()
	{
		m_MdbSubscriber->OnOrderTruncate();
		
		std::list<Order*>* records = new std::list<Order*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Order(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnOrderBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool OrderTable::Insert(Order* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record) || !m_ClientOrderIDUniqueKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Order:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);
		m_ClientOrderIDUniqueKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnOrderInsert(record);
		}
		return true;
	}
	void OrderTable::BatchInsert(std::list<mdb::Order*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Order::Allocate();
				memcpy(newRecord, record, sizeof(Order));
				m_PrimaryKey->Insert(newRecord);
				m_ClientOrderIDUniqueKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnOrderBatchInsert(records);
		}
	}
	void OrderTable::Erase(Order* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnOrderErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool OrderTable::Update(Order* const oldRecord, Order* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord) || !m_ClientOrderIDUniqueKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Order:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Order:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Order));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnOrderUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void OrderTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_ClientOrderIDUniqueKey->m_Index.clear();
	}
	void OrderTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_ClientOrderIDUniqueKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnOrderTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
		m_ClientOrderIDUniqueKey->Erase(record);
	}
	void OrderTable::EraseIndex(Order* record)
	{
	}

	TradeTable::TradeTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new TradePrimaryKey(this);
	}
	TradeTable::~TradeTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void TradeTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void TradeTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void TradeTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void TradeTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void TradeTable::InitDB()
	{
		m_MdbSubscriber->OnTradeTruncate();
		
		std::list<Trade*>* records = new std::list<Trade*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new Trade(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnTradeBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool TradeTable::Insert(Trade* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for Trade:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradeInsert(record);
		}
		return true;
	}
	void TradeTable::BatchInsert(std::list<mdb::Trade*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = Trade::Allocate();
				memcpy(newRecord, record, sizeof(Trade));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradeBatchInsert(records);
		}
	}
	void TradeTable::Erase(Trade* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradeErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool TradeTable::Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for Trade:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New Trade:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(Trade));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradeUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void TradeTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void TradeTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnTradeTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void TradeTable::EraseIndex(Trade* record)
	{
	}

	DepthMarketDataTable::DepthMarketDataTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new DepthMarketDataPrimaryKey(this);
	}
	DepthMarketDataTable::~DepthMarketDataTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void DepthMarketDataTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void DepthMarketDataTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void DepthMarketDataTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void DepthMarketDataTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void DepthMarketDataTable::InitDB()
	{
		m_MdbSubscriber->OnDepthMarketDataTruncate();
		
		std::list<DepthMarketData*>* records = new std::list<DepthMarketData*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new DepthMarketData(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnDepthMarketDataBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool DepthMarketDataTable::Insert(DepthMarketData* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for DepthMarketData:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnDepthMarketDataInsert(record);
		}
		return true;
	}
	void DepthMarketDataTable::BatchInsert(std::list<mdb::DepthMarketData*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = DepthMarketData::Allocate();
				memcpy(newRecord, record, sizeof(DepthMarketData));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnDepthMarketDataBatchInsert(records);
		}
	}
	void DepthMarketDataTable::Erase(DepthMarketData* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnDepthMarketDataErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool DepthMarketDataTable::Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for DepthMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New DepthMarketData:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(DepthMarketData));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnDepthMarketDataUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void DepthMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void DepthMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnDepthMarketDataTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void DepthMarketDataTable::EraseIndex(DepthMarketData* record)
	{
	}

	BarMarketDataTable::BarMarketDataTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new BarMarketDataPrimaryKey(this);
	}
	BarMarketDataTable::~BarMarketDataTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void BarMarketDataTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void BarMarketDataTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void BarMarketDataTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void BarMarketDataTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void BarMarketDataTable::InitDB()
	{
		m_MdbSubscriber->OnBarMarketDataTruncate();
		
		std::list<BarMarketData*>* records = new std::list<BarMarketData*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new BarMarketData(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnBarMarketDataBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool BarMarketDataTable::Insert(BarMarketData* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for BarMarketData:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnBarMarketDataInsert(record);
		}
		return true;
	}
	void BarMarketDataTable::BatchInsert(std::list<mdb::BarMarketData*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = BarMarketData::Allocate();
				memcpy(newRecord, record, sizeof(BarMarketData));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnBarMarketDataBatchInsert(records);
		}
	}
	void BarMarketDataTable::Erase(BarMarketData* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnBarMarketDataErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool BarMarketDataTable::Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for BarMarketData:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New BarMarketData:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(BarMarketData));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnBarMarketDataUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void BarMarketDataTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void BarMarketDataTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnBarMarketDataTruncate();
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

		fprintf(dumpFile, "TradingDay,ExchangeID,InstrumentID,BarPreces,BarPeriod,BarTime,UpdateTs,PreSettlementPrice,PreClosePrice,Open,High,Low,Close,CurrVolume,Volume,CurrTurnover,Turnover,OpenInterest\n");
		char buff[4096] = { 0 };
		set<BarMarketData*, BarMarketDataLessForBarMarketDataPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void BarMarketDataTable::EraseIndex(BarMarketData* record)
	{
	}

	MdSubscribeTable::MdSubscribeTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new MdSubscribePrimaryKey(this);
	}
	MdSubscribeTable::~MdSubscribeTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void MdSubscribeTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void MdSubscribeTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void MdSubscribeTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void MdSubscribeTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void MdSubscribeTable::InitDB()
	{
		m_MdbSubscriber->OnMdSubscribeTruncate();
		
		std::list<MdSubscribe*>* records = new std::list<MdSubscribe*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new MdSubscribe(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnMdSubscribeBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool MdSubscribeTable::Insert(MdSubscribe* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdSubscribe:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdSubscribeInsert(record);
		}
		return true;
	}
	void MdSubscribeTable::BatchInsert(std::list<mdb::MdSubscribe*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdSubscribe::Allocate();
				memcpy(newRecord, record, sizeof(MdSubscribe));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdSubscribeBatchInsert(records);
		}
	}
	void MdSubscribeTable::Erase(MdSubscribe* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdSubscribeErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool MdSubscribeTable::Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdSubscribe:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdSubscribe:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(MdSubscribe));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdSubscribeUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void MdSubscribeTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void MdSubscribeTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdSubscribeTruncate();
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
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
		m_PrimaryKey->Erase(record);
	}
	void MdSubscribeTable::EraseIndex(MdSubscribe* record)
	{
	}

	SEBrokerTable::SEBrokerTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new SEBrokerPrimaryKey(this);
	}
	SEBrokerTable::~SEBrokerTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void SEBrokerTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void SEBrokerTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void SEBrokerTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void SEBrokerTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void SEBrokerTable::InitDB()
	{
		m_MdbSubscriber->OnSEBrokerTruncate();
		
		std::list<SEBroker*>* records = new std::list<SEBroker*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new SEBroker(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnSEBrokerBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool SEBrokerTable::Insert(SEBroker* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for SEBroker:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerInsert(record);
		}
		return true;
	}
	void SEBrokerTable::BatchInsert(std::list<mdb::SEBroker*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = SEBroker::Allocate();
				memcpy(newRecord, record, sizeof(SEBroker));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerBatchInsert(records);
		}
	}
	void SEBrokerTable::Erase(SEBroker* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool SEBrokerTable::Update(SEBroker* const oldRecord, SEBroker* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for SEBroker:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New SEBroker:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(SEBroker));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void SEBrokerTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void SEBrokerTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerTruncate();
		}
	}
	void SEBrokerTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_SEBroker.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "BrokerID,BrokerName,Password\n");
		char buff[4096] = { 0 };
		set<SEBroker*, SEBrokerLessForSEBrokerPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
	void SEBrokerTable::EraseUniqueKey(SEBroker* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void SEBrokerTable::EraseIndex(SEBroker* record)
	{
	}

	SEInstrumentTable::SEInstrumentTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new SEInstrumentPrimaryKey(this);
		m_ExchangeIDIndex = new SEInstrumentIndexExchangeID(this);
	}
	SEInstrumentTable::~SEInstrumentTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_ExchangeIDIndex;
		m_ExchangeIDIndex = nullptr;
	}
	void SEInstrumentTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void SEInstrumentTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void SEInstrumentTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void SEInstrumentTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void SEInstrumentTable::InitDB()
	{
		m_MdbSubscriber->OnSEInstrumentTruncate();
		
		std::list<SEInstrument*>* records = new std::list<SEInstrument*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new SEInstrument(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnSEInstrumentBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool SEInstrumentTable::Insert(SEInstrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for SEInstrument:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_ExchangeIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEInstrumentInsert(record);
		}
		return true;
	}
	void SEInstrumentTable::BatchInsert(std::list<mdb::SEInstrument*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = SEInstrument::Allocate();
				memcpy(newRecord, record, sizeof(SEInstrument));
				m_PrimaryKey->Insert(newRecord);

				m_ExchangeIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEInstrumentBatchInsert(records);
		}
	}
	void SEInstrumentTable::Erase(SEInstrument* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEInstrumentErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int SEInstrumentTable::EraseByExchangeIDIndex(const ExchangeIDType& ExchangeID)
	{
		m_ExchangeIDIndex->FillCompareRecord(ExchangeID);
		list<SEInstrument*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_ExchangeIDIndex->m_Index.equal_range(&t_CompareSEInstrument);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = SEInstrument::Allocate();
			memcpy(record, &t_CompareSEInstrument, sizeof(SEInstrument));
			m_MdbSubscriber->OnSEInstrumentEraseByExchangeIDIndex(record);
		}
		return (int)records.size();
	}
	bool SEInstrumentTable::Update(SEInstrument* const oldRecord, SEInstrument* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for SEInstrument:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New SEInstrument:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool ExchangeIDIndexUpdate = m_ExchangeIDIndex->NeedUpdate(oldRecord, newRecord);
		SEInstrumentIndexExchangeID::iterator itExchangeID;
		if (ExchangeIDIndexUpdate)
		{
			itExchangeID = m_ExchangeIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(SEInstrument));
		if (ExchangeIDIndexUpdate)
		{
			m_ExchangeIDIndex->Update(itExchangeID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEInstrumentUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void SEInstrumentTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_ExchangeIDIndex->m_Index.clear();
	}
	void SEInstrumentTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_ExchangeIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEInstrumentTruncate();
		}
	}
	void SEInstrumentTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_SEInstrument.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "ExchangeID,InstrumentID,ExchangeInstID,InstrumentName,ProductID,ProductClass,MaxMarketOrderVolume,MinMarketOrderVolume,MaxLimitOrderVolume,MinLimitOrderVolume,VolumeMultiple,PriceTick,UpperLimitPrice,LowerLimitPrice,SessionName\n");
		char buff[4096] = { 0 };
		set<SEInstrument*, SEInstrumentLessForSEInstrumentPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
	void SEInstrumentTable::EraseUniqueKey(SEInstrument* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void SEInstrumentTable::EraseIndex(SEInstrument* record)
	{
		m_ExchangeIDIndex->Erase(record);
	}

	SEOrderTable::SEOrderTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new SEOrderPrimaryKey(this);
		m_AccountIDIndex = new SEOrderIndexAccountID(this);
	}
	SEOrderTable::~SEOrderTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_AccountIDIndex;
		m_AccountIDIndex = nullptr;
	}
	void SEOrderTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void SEOrderTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void SEOrderTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void SEOrderTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void SEOrderTable::InitDB()
	{
		m_MdbSubscriber->OnSEOrderTruncate();
		
		std::list<SEOrder*>* records = new std::list<SEOrder*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new SEOrder(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnSEOrderBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool SEOrderTable::Insert(SEOrder* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for SEOrder:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_AccountIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEOrderInsert(record);
		}
		return true;
	}
	void SEOrderTable::BatchInsert(std::list<mdb::SEOrder*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = SEOrder::Allocate();
				memcpy(newRecord, record, sizeof(SEOrder));
				m_PrimaryKey->Insert(newRecord);

				m_AccountIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEOrderBatchInsert(records);
		}
	}
	void SEOrderTable::Erase(SEOrder* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEOrderErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int SEOrderTable::EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		m_AccountIDIndex->FillCompareRecord(TradingDay, AccountID);
		list<SEOrder*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_AccountIDIndex->m_Index.equal_range(&t_CompareSEOrder);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = SEOrder::Allocate();
			memcpy(record, &t_CompareSEOrder, sizeof(SEOrder));
			m_MdbSubscriber->OnSEOrderEraseByAccountIDIndex(record);
		}
		return (int)records.size();
	}
	bool SEOrderTable::Update(SEOrder* const oldRecord, SEOrder* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for SEOrder:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New SEOrder:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool AccountIDIndexUpdate = m_AccountIDIndex->NeedUpdate(oldRecord, newRecord);
		SEOrderIndexAccountID::iterator itAccountID;
		if (AccountIDIndexUpdate)
		{
			itAccountID = m_AccountIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(SEOrder));
		if (AccountIDIndexUpdate)
		{
			m_AccountIDIndex->Update(itAccountID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEOrderUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void SEOrderTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIDIndex->m_Index.clear();
	}
	void SEOrderTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEOrderTruncate();
		}
	}
	void SEOrderTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_SEOrder.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,BrokerID,AccountID,ExchangeID,InstrumentID,ProductClass,OrderID,Direction,OffsetFlag,OrderPriceType,Price,Volume,VolumeTotal,VolumeTraded,VolumeMultiple,OrderStatus,OrderDate,OrderTime,CancelDate,CancelTime,SessionID,ClientOrderID\n");
		char buff[4096] = { 0 };
		set<SEOrder*, SEOrderLessForSEOrderPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
	void SEOrderTable::EraseUniqueKey(SEOrder* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void SEOrderTable::EraseIndex(SEOrder* record)
	{
		m_AccountIDIndex->Erase(record);
	}

	SETradeTable::SETradeTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new SETradePrimaryKey(this);
		m_AccountIDIndex = new SETradeIndexAccountID(this);
	}
	SETradeTable::~SETradeTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_AccountIDIndex;
		m_AccountIDIndex = nullptr;
	}
	void SETradeTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void SETradeTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void SETradeTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void SETradeTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void SETradeTable::InitDB()
	{
		m_MdbSubscriber->OnSETradeTruncate();
		
		std::list<SETrade*>* records = new std::list<SETrade*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new SETrade(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnSETradeBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool SETradeTable::Insert(SETrade* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for SETrade:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_AccountIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSETradeInsert(record);
		}
		return true;
	}
	void SETradeTable::BatchInsert(std::list<mdb::SETrade*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = SETrade::Allocate();
				memcpy(newRecord, record, sizeof(SETrade));
				m_PrimaryKey->Insert(newRecord);

				m_AccountIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSETradeBatchInsert(records);
		}
	}
	void SETradeTable::Erase(SETrade* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSETradeErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int SETradeTable::EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		m_AccountIDIndex->FillCompareRecord(TradingDay, AccountID);
		list<SETrade*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_AccountIDIndex->m_Index.equal_range(&t_CompareSETrade);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = SETrade::Allocate();
			memcpy(record, &t_CompareSETrade, sizeof(SETrade));
			m_MdbSubscriber->OnSETradeEraseByAccountIDIndex(record);
		}
		return (int)records.size();
	}
	bool SETradeTable::Update(SETrade* const oldRecord, SETrade* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for SETrade:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New SETrade:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool AccountIDIndexUpdate = m_AccountIDIndex->NeedUpdate(oldRecord, newRecord);
		SETradeIndexAccountID::iterator itAccountID;
		if (AccountIDIndexUpdate)
		{
			itAccountID = m_AccountIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(SETrade));
		if (AccountIDIndexUpdate)
		{
			m_AccountIDIndex->Update(itAccountID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSETradeUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void SETradeTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIDIndex->m_Index.clear();
	}
	void SETradeTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_AccountIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSETradeTruncate();
		}
	}
	void SETradeTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_SETrade.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "TradingDay,BrokerID,AccountID,ExchangeID,InstrumentID,ProductClass,OrderID,TradeID,Direction,OffsetFlag,Price,Volume,VolumeMultiple,TradeAmount,Commission,TradeDate,TradeTime\n");
		char buff[4096] = { 0 };
		set<SETrade*, SETradeLessForSETradePrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
	void SETradeTable::EraseUniqueKey(SETrade* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void SETradeTable::EraseIndex(SETrade* record)
	{
		m_AccountIDIndex->Erase(record);
	}

	SEBrokerLoginSessionTable::SEBrokerLoginSessionTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new SEBrokerLoginSessionPrimaryKey(this);
		m_BrokerIDIndex = new SEBrokerLoginSessionIndexBrokerID(this);
	}
	SEBrokerLoginSessionTable::~SEBrokerLoginSessionTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_BrokerIDIndex;
		m_BrokerIDIndex = nullptr;
	}
	void SEBrokerLoginSessionTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void SEBrokerLoginSessionTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void SEBrokerLoginSessionTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void SEBrokerLoginSessionTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void SEBrokerLoginSessionTable::InitDB()
	{
		m_MdbSubscriber->OnSEBrokerLoginSessionTruncate();
		
		std::list<SEBrokerLoginSession*>* records = new std::list<SEBrokerLoginSession*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new SEBrokerLoginSession(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool SEBrokerLoginSessionTable::Insert(SEBrokerLoginSession* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for SEBrokerLoginSession:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_BrokerIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionInsert(record);
		}
		return true;
	}
	void SEBrokerLoginSessionTable::BatchInsert(std::list<mdb::SEBrokerLoginSession*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = SEBrokerLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(SEBrokerLoginSession));
				m_PrimaryKey->Insert(newRecord);

				m_BrokerIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionBatchInsert(records);
		}
	}
	void SEBrokerLoginSessionTable::Erase(SEBrokerLoginSession* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int SEBrokerLoginSessionTable::EraseByBrokerIDIndex(const BrokerIDType& BrokerID)
	{
		m_BrokerIDIndex->FillCompareRecord(BrokerID);
		list<SEBrokerLoginSession*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_BrokerIDIndex->m_Index.equal_range(&t_CompareSEBrokerLoginSession);
		for (auto& it = range.first; it != range.second; ++it)
		{
			records.push_back(*it);
		}
		for (auto record : records)
		{
			EraseUniqueKey(record);
			EraseIndex(record);
			record->Free();
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			auto record = SEBrokerLoginSession::Allocate();
			memcpy(record, &t_CompareSEBrokerLoginSession, sizeof(SEBrokerLoginSession));
			m_MdbSubscriber->OnSEBrokerLoginSessionEraseByBrokerIDIndex(record);
		}
		return (int)records.size();
	}
	bool SEBrokerLoginSessionTable::Update(SEBrokerLoginSession* const oldRecord, SEBrokerLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for SEBrokerLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New SEBrokerLoginSession:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool BrokerIDIndexUpdate = m_BrokerIDIndex->NeedUpdate(oldRecord, newRecord);
		SEBrokerLoginSessionIndexBrokerID::iterator itBrokerID;
		if (BrokerIDIndexUpdate)
		{
			itBrokerID = m_BrokerIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(SEBrokerLoginSession));
		if (BrokerIDIndexUpdate)
		{
			m_BrokerIDIndex->Update(itBrokerID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void SEBrokerLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_BrokerIDIndex->m_Index.clear();
	}
	void SEBrokerLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_BrokerIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnSEBrokerLoginSessionTruncate();
		}
	}
	void SEBrokerLoginSessionTable::Dump(const char* dir)
	{
		string fileName = string(dir) + "//t_SEBrokerLoginSession.csv";
		FILE* dumpFile = fopen(fileName.c_str(), "w");
		if (dumpFile == nullptr)
		{
			return;
		}

		fprintf(dumpFile, "BrokerID,SessionID,IPAddress\n");
		char buff[4096] = { 0 };
		set<SEBrokerLoginSession*, SEBrokerLoginSessionLessForSEBrokerLoginSessionPrimaryKey> records;
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
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
	void SEBrokerLoginSessionTable::EraseUniqueKey(SEBrokerLoginSession* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void SEBrokerLoginSessionTable::EraseIndex(SEBrokerLoginSession* record)
	{
		m_BrokerIDIndex->Erase(record);
	}

}

