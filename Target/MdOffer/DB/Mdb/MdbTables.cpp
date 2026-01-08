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

	MdUserTable::MdUserTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new MdUserPrimaryKey(this);
	}
	MdUserTable::~MdUserTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
	}
	void MdUserTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void MdUserTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void MdUserTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void MdUserTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void MdUserTable::InitDB()
	{
		m_MdbSubscriber->OnMdUserTruncate();
		
		std::list<MdUser*>* records = new std::list<MdUser*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new MdUser(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnMdUserBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool MdUserTable::Insert(MdUser* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUser:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserInsert(record);
		}
		return true;
	}
	void MdUserTable::BatchInsert(std::list<mdb::MdUser*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUser::Allocate();
				memcpy(newRecord, record, sizeof(MdUser));
				m_PrimaryKey->Insert(newRecord);

			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserBatchInsert(records);
		}
	}
	void MdUserTable::Erase(MdUser* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserErase(record);
		}
		else
		{
			record->Free();
		}
	}
	bool MdUserTable::Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUser:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUser:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		::memcpy((void*)oldRecord, newRecord, sizeof(MdUser));

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void MdUserTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
	}
	void MdUserTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserTruncate();
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
	void MdUserTable::EraseUniqueKey(MdUser* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void MdUserTable::EraseIndex(MdUser* record)
	{
	}

	MdUserLoginSessionTable::MdUserLoginSessionTable(Mdb* mdb)
		:m_Mdb(mdb)
	{
		m_MdbSubscriber = nullptr;
		m_PrimaryKey = new MdUserLoginSessionPrimaryKey(this);
		m_MdUserIDIndex = new MdUserLoginSessionIndexMdUserID(this);
	}
	MdUserLoginSessionTable::~MdUserLoginSessionTable()
	{
		delete m_PrimaryKey;
		m_PrimaryKey = nullptr;
		delete m_MdUserIDIndex;
		m_MdUserIDIndex = nullptr;
	}
	void MdUserLoginSessionTable::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
	}
	void MdUserLoginSessionTable::UnSubscribe()
	{
		m_MdbSubscriber = nullptr;
	}
	void MdUserLoginSessionTable::LockShared()
	{
		m_SharedMutex.lock_shared();
	}
	void MdUserLoginSessionTable::UnlockShared()
	{
		m_SharedMutex.unlock_shared();
	}
	void MdUserLoginSessionTable::InitDB()
	{
		m_MdbSubscriber->OnMdUserLoginSessionTruncate();
		
		std::list<MdUserLoginSession*>* records = new std::list<MdUserLoginSession*>();
		std::shared_lock guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			records->push_back(new MdUserLoginSession(**it));
		}
		if (records->empty())
		{
			delete records;
		}
		else
		{
			m_MdbSubscriber->OnMdUserLoginSessionBatchInsert(records);
		}
		m_DBInited = true;
	}
	bool MdUserLoginSessionTable::Insert(MdUserLoginSession* record)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckInsert(record))
		{
			WriteLog(LogLevel::Warning, "Insert Failed for MdUserLoginSession:[%s]", record->GetString());
			record->Free();
			return false;
		}

		m_PrimaryKey->Insert(record);

		m_MdUserIDIndex->Insert(record);
		
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserLoginSessionInsert(record);
		}
		return true;
	}
	void MdUserLoginSessionTable::BatchInsert(std::list<mdb::MdUserLoginSession*>* records)
	{
		{
			std::lock_guard guard(m_SharedMutex);
			for (auto record : *records)
			{
				auto newRecord = MdUserLoginSession::Allocate();
				memcpy(newRecord, record, sizeof(MdUserLoginSession));
				m_PrimaryKey->Insert(newRecord);

				m_MdUserIDIndex->Insert(newRecord);
			}
		}
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserLoginSessionBatchInsert(records);
		}
	}
	void MdUserLoginSessionTable::Erase(MdUserLoginSession* record)
	{
		std::lock_guard guard(m_SharedMutex);
		EraseUniqueKey(record);
		EraseIndex(record);
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserLoginSessionErase(record);
		}
		else
		{
			record->Free();
		}
	}
	int MdUserLoginSessionTable::EraseByMdUserIDIndex(const UserIDType& MdUserID)
	{
		m_MdUserIDIndex->FillCompareRecord(MdUserID);
		list<MdUserLoginSession*> records;
		std::lock_guard guard(m_SharedMutex);
		auto range = m_MdUserIDIndex->m_Index.equal_range(&t_CompareMdUserLoginSession);
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
			auto record = MdUserLoginSession::Allocate();
			memcpy(record, &t_CompareMdUserLoginSession, sizeof(MdUserLoginSession));
			m_MdbSubscriber->OnMdUserLoginSessionEraseByMdUserIDIndex(record);
		}
		return (int)records.size();
	}
	bool MdUserLoginSessionTable::Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB)
	{
		std::lock_guard guard(m_SharedMutex);
		if (!m_PrimaryKey->CheckUpdate(oldRecord, newRecord))
		{
			WriteLog(LogLevel::Warning, "Update Failed for MdUserLoginSession:[%s]", oldRecord->GetString());
			WriteLog(LogLevel::Warning, "              New MdUserLoginSession:[%s]", newRecord->GetString());
			newRecord->Free();
			return false;
		}

		bool MdUserIDIndexUpdate = m_MdUserIDIndex->NeedUpdate(oldRecord, newRecord);
		MdUserLoginSessionIndexMdUserID::iterator itMdUserID;
		if (MdUserIDIndexUpdate)
		{
			itMdUserID = m_MdUserIDIndex->FindNode(oldRecord);
		}
		::memcpy((void*)oldRecord, newRecord, sizeof(MdUserLoginSession));
		if (MdUserIDIndexUpdate)
		{
			m_MdUserIDIndex->Update(itMdUserID);
		}

		if (updateDB && m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserLoginSessionUpdate(newRecord);
		}
		else
		{
			newRecord->Free();
		}
		return true;
	}
	void MdUserLoginSessionTable::TruncateTables()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_MdUserIDIndex->m_Index.clear();
	}
	void MdUserLoginSessionTable::TruncateTable()
	{
		std::lock_guard guard(m_SharedMutex);
		for (auto it = m_PrimaryKey->m_Index.begin(); it != m_PrimaryKey->m_Index.end(); ++it)
		{
			(*it)->Free();
		}
		m_PrimaryKey->m_Index.clear();
		m_MdUserIDIndex->m_Index.clear();
		if (m_MdbSubscriber != nullptr && m_DBInited)
		{
			m_MdbSubscriber->OnMdUserLoginSessionTruncate();
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
	void MdUserLoginSessionTable::EraseUniqueKey(MdUserLoginSession* record)
	{
		m_PrimaryKey->Erase(record);
	}
	void MdUserLoginSessionTable::EraseIndex(MdUserLoginSession* record)
	{
		m_MdUserIDIndex->Erase(record);
	}

}

