#include "DBWriter.h"
#include "Logger.h"
#include "MdbIndexes.h"
#include <cstring>

using namespace std;
using namespace mdb;


DBWriter::DBWriter(DB* db)
	:ThreadBase("DBWriter"), m_DB(db), m_DBSubscriber(nullptr)
{
}
DBWriter::~DBWriter()
{
	if (m_DB != nullptr)
	{
		delete m_DB;
		m_DB = nullptr;
	}
}
void DBWriter::Subscribe(DBSubscriber* dbSubscriber)
{
	m_DBSubscriber = dbSubscriber;
}
DB* DBWriter::GetDB()
{
	return m_DB;
}
bool DBWriter::Connect()
{
	if (m_DB->Connect())
	{
		m_Connected = true;
		if (m_DBSubscriber != nullptr)
		{
			m_DBSubscriber->OnDBConnected();
		}
		return true;
	}
	return false;
}
void DBWriter::DisConnect()
{
	m_Connected = false;
	if (m_DBSubscriber != nullptr)
	{
		m_DBSubscriber->OnDBDisConnected();
	}
	m_DB->DisConnect();
	lock_guard<mutex> guard(m_Mutex);
	for (auto item : m_DBOperates)
	{
		item->FreeRecord();
		item->Free();
	}
	m_DBOperates.clear();
}

void DBWriter::OnCreateTables()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::CreateTables;
	dbOperate->TableID = 0;
	dbOperate->Record = nullptr;
	AddDBOperate(dbOperate);
}
void DBWriter::OnDropTables()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DropTables;
	dbOperate->TableID = 0;
	dbOperate->Record = nullptr;
	AddDBOperate(dbOperate);
}
void DBWriter::OnTruncateTables()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::TruncateTables;
	dbOperate->TableID = 0;
	dbOperate->Record = nullptr;
	AddDBOperate(dbOperate);
}

void DBWriter::OnDepthMarketDataInsert(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnDepthMarketDataErase(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnDepthMarketDataUpdate(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnDepthMarketDataTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}

void DBWriter::OnBarMarketDataInsert(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnBarMarketDataBatchInsert(std::list<mdb::BarMarketData*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnBarMarketDataErase(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnBarMarketDataUpdate(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnBarMarketDataTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}


void DBWriter::Run()
{
	CheckConnect();
	CheckDBOperate();
	HandleDBOperate();
}
void DBWriter::CheckConnect()
{
	if (!m_Connected)
	{
		Connect();
	}
}
void DBWriter::CheckDBOperate()
{
	unique_lock<mutex> guard(m_Mutex);
	m_ConditionVariable.wait_for(guard, m_TimeOut, [&] {return !m_DBOperates.empty(); });
}
void DBWriter::HandleDBOperate()
{
	if (!m_Connected)
		return;
	DBOperate* dbOperate = nullptr;
	try
	{
		while ((dbOperate = GetDBOperate()) != nullptr)
		{
			switch (dbOperate->Operate)
			{
			case DBOperateType::CreateTables:
			{
				CreateTables(dbOperate);
				break;
			}
			case DBOperateType::DropTables:
			{
				DropTables(dbOperate);
				break;
			}
			case DBOperateType::TruncateTables:
			{
				TruncateTables(dbOperate);
				break;
			}
			case DBOperateType::Insert:
			{
				InsertRecord(dbOperate);
				break;
			}
			case DBOperateType::Delete:
			{
				DeleteRecord(dbOperate);
				break;
			}
			case DBOperateType::DeleteByIndex:
			{
				DeleteRecordByIndex(dbOperate);
				break;
			}
			case DBOperateType::Update:
			{
				UpdateRecord(dbOperate);
				break;
			}
			case DBOperateType::BatchInsert:
			{
				BatchInsertRecords(dbOperate);
				break;
			}
			case DBOperateType::Truncate:
			{
				TruncateTable(dbOperate);
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unknown DBOperateType:%d", dbOperate->Operate);
				break;
			}
			dbOperate->Free();
		}
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "HandleDBOperate Failed. TableID;0x%X, Operate:%d, Message:%s", dbOperate->TableID, (int)dbOperate->Operate, e.what());
		DisConnect();
		dbOperate->FreeRecord();
		dbOperate->Free();
		this_thread::sleep_for(chrono::seconds(5));
	}
}
DBOperate* DBWriter::GetDBOperate()
{
	lock_guard<mutex> guard(m_Mutex);
	if (m_DBOperates.empty())
	{
		return nullptr;
	}
	auto item = m_DBOperates.front();
	m_DBOperates.pop_front();
	return item;
}


void DBWriter::AddDBOperate(DBOperate* dbOperate)
{
	{
		lock_guard<mutex> guard(m_Mutex);
		m_DBOperates.push_back(dbOperate);
	}
	m_ConditionVariable.notify_one();
}

void DBWriter::CreateTables(DBOperate* dbOperate)
{
	m_DB->CreateTables();
}
void DBWriter::DropTables(DBOperate* dbOperate)
{
	m_DB->DropTables();
}
void DBWriter::TruncateTables(DBOperate* dbOperate)
{
	m_DB->TruncateTables();
}
void DBWriter::InsertRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case DepthMarketData::TableID:
		m_DB->InsertDepthMarketData((DepthMarketData*)dbOperate->Record);
		break;
	case BarMarketData::TableID:
		m_DB->InsertBarMarketData((BarMarketData*)dbOperate->Record);
		break;
	default:
		break;
	}
}
void DBWriter::BatchInsertRecords(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case DepthMarketData::TableID:
	{
		auto records = (std::list<DepthMarketData*>*)dbOperate->Record;
		m_DB->BatchInsertDepthMarketData(records);
		records->clear();
		delete records;
		break;
	}
	case BarMarketData::TableID:
	{
		auto records = (std::list<BarMarketData*>*)dbOperate->Record;
		m_DB->BatchInsertBarMarketData(records);
		records->clear();
		delete records;
		break;
	}
	default:
		WriteLog(LogLevel::Error, "Unexpected BatchInsert TableID:0x%X", dbOperate->TableID);
		break;
	}
}
void DBWriter::DeleteRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case DepthMarketData::TableID:
		m_DB->DeleteDepthMarketData((DepthMarketData*)dbOperate->Record);
		((DepthMarketData*)dbOperate->Record)->Free();
		break;
	case BarMarketData::TableID:
		m_DB->DeleteBarMarketData((BarMarketData*)dbOperate->Record);
		((BarMarketData*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::DeleteRecordByIndex(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	default:
		WriteLog(LogLevel::Error, "Incorrect TableID for DeleteRecordByIndex. TableID:0x%X", dbOperate->TableID);
		break;
	}
}
void DBWriter::UpdateRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case DepthMarketData::TableID:
		m_DB->UpdateDepthMarketData((DepthMarketData*)dbOperate->Record);
		((DepthMarketData*)dbOperate->Record)->Free();
		break;
	case BarMarketData::TableID:
		m_DB->UpdateBarMarketData((BarMarketData*)dbOperate->Record);
		((BarMarketData*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}

void DBWriter::TruncateTable(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case DepthMarketData::TableID:
		m_DB->TruncateDepthMarketData();
		break;
	case BarMarketData::TableID:
		m_DB->TruncateBarMarketData();
		break;
	default:
		break;
	}
}

