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

