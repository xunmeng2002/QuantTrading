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

void DBWriter::OnExchangeInsert(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnExchangeBatchInsert(std::list<mdb::Exchange*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnExchangeErase(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnExchangeUpdate(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnExchangeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}

void DBWriter::OnInstrumentInsert(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnInstrumentErase(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnInstrumentUpdate(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnInstrumentTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Instrument::TableID;
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

void DBWriter::OnMdSubscribeInsert(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdSubscribeBatchInsert(std::list<mdb::MdSubscribe*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdSubscribeErase(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdSubscribeUpdate(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdSubscribeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}

void DBWriter::OnMdUserInsert(mdb::MdUser* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = MdUser::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserBatchInsert(std::list<mdb::MdUser*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = MdUser::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserErase(mdb::MdUser* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = MdUser::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserUpdate(mdb::MdUser* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = MdUser::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = MdUser::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}

void DBWriter::OnMdUserLoginSessionInsert(mdb::MdUserLoginSession* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = MdUserLoginSession::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserLoginSessionBatchInsert(std::list<mdb::MdUserLoginSession*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = MdUserLoginSession::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserLoginSessionErase(mdb::MdUserLoginSession* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = MdUserLoginSession::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserLoginSessionEraseByMdUserIDIndex(mdb::MdUserLoginSession* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = MdUserLoginSession::TableID;
	dbOperate->IndexID = MdUserLoginSessionIndexMdUserID::IndexID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserLoginSessionUpdate(mdb::MdUserLoginSession* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = MdUserLoginSession::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnMdUserLoginSessionTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = MdUserLoginSession::TableID;
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
	case Exchange::TableID:
		m_DB->InsertExchange((Exchange*)dbOperate->Record);
		break;
	case Instrument::TableID:
		m_DB->InsertInstrument((Instrument*)dbOperate->Record);
		break;
	case DepthMarketData::TableID:
		m_DB->InsertDepthMarketData((DepthMarketData*)dbOperate->Record);
		break;
	case BarMarketData::TableID:
		m_DB->InsertBarMarketData((BarMarketData*)dbOperate->Record);
		break;
	case MdSubscribe::TableID:
		m_DB->InsertMdSubscribe((MdSubscribe*)dbOperate->Record);
		break;
	case MdUser::TableID:
		m_DB->InsertMdUser((MdUser*)dbOperate->Record);
		break;
	case MdUserLoginSession::TableID:
		m_DB->InsertMdUserLoginSession((MdUserLoginSession*)dbOperate->Record);
		break;
	default:
		break;
	}
}
void DBWriter::BatchInsertRecords(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case Exchange::TableID:
	{
		auto records = (std::list<Exchange*>*)dbOperate->Record;
		m_DB->BatchInsertExchange(records);
		records->clear();
		delete records;
		break;
	}
	case Instrument::TableID:
	{
		auto records = (std::list<Instrument*>*)dbOperate->Record;
		m_DB->BatchInsertInstrument(records);
		records->clear();
		delete records;
		break;
	}
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
	case MdSubscribe::TableID:
	{
		auto records = (std::list<MdSubscribe*>*)dbOperate->Record;
		m_DB->BatchInsertMdSubscribe(records);
		records->clear();
		delete records;
		break;
	}
	case MdUser::TableID:
	{
		auto records = (std::list<MdUser*>*)dbOperate->Record;
		m_DB->BatchInsertMdUser(records);
		records->clear();
		delete records;
		break;
	}
	case MdUserLoginSession::TableID:
	{
		auto records = (std::list<MdUserLoginSession*>*)dbOperate->Record;
		m_DB->BatchInsertMdUserLoginSession(records);
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
	case Exchange::TableID:
		m_DB->DeleteExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->DeleteInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case DepthMarketData::TableID:
		m_DB->DeleteDepthMarketData((DepthMarketData*)dbOperate->Record);
		((DepthMarketData*)dbOperate->Record)->Free();
		break;
	case BarMarketData::TableID:
		m_DB->DeleteBarMarketData((BarMarketData*)dbOperate->Record);
		((BarMarketData*)dbOperate->Record)->Free();
		break;
	case MdSubscribe::TableID:
		m_DB->DeleteMdSubscribe((MdSubscribe*)dbOperate->Record);
		((MdSubscribe*)dbOperate->Record)->Free();
		break;
	case MdUser::TableID:
		m_DB->DeleteMdUser((MdUser*)dbOperate->Record);
		((MdUser*)dbOperate->Record)->Free();
		break;
	case MdUserLoginSession::TableID:
		m_DB->DeleteMdUserLoginSession((MdUserLoginSession*)dbOperate->Record);
		((MdUserLoginSession*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::DeleteRecordByIndex(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case MdUserLoginSession::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case MdUserLoginSessionIndexMdUserID::IndexID:
		{
			m_DB->DeleteMdUserLoginSessionByMdUserIDIndex((MdUserLoginSession*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((MdUserLoginSession*)dbOperate->Record)->Free();
		break;
	}
	default:
		WriteLog(LogLevel::Error, "Incorrect TableID for DeleteRecordByIndex. TableID:0x%X", dbOperate->TableID);
		break;
	}
}
void DBWriter::UpdateRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case Exchange::TableID:
		m_DB->UpdateExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->UpdateInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case DepthMarketData::TableID:
		m_DB->UpdateDepthMarketData((DepthMarketData*)dbOperate->Record);
		((DepthMarketData*)dbOperate->Record)->Free();
		break;
	case BarMarketData::TableID:
		m_DB->UpdateBarMarketData((BarMarketData*)dbOperate->Record);
		((BarMarketData*)dbOperate->Record)->Free();
		break;
	case MdSubscribe::TableID:
		m_DB->UpdateMdSubscribe((MdSubscribe*)dbOperate->Record);
		((MdSubscribe*)dbOperate->Record)->Free();
		break;
	case MdUser::TableID:
		m_DB->UpdateMdUser((MdUser*)dbOperate->Record);
		((MdUser*)dbOperate->Record)->Free();
		break;
	case MdUserLoginSession::TableID:
		m_DB->UpdateMdUserLoginSession((MdUserLoginSession*)dbOperate->Record);
		((MdUserLoginSession*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}

void DBWriter::TruncateTable(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case Exchange::TableID:
		m_DB->TruncateExchange();
		break;
	case Instrument::TableID:
		m_DB->TruncateInstrument();
		break;
	case DepthMarketData::TableID:
		m_DB->TruncateDepthMarketData();
		break;
	case BarMarketData::TableID:
		m_DB->TruncateBarMarketData();
		break;
	case MdSubscribe::TableID:
		m_DB->TruncateMdSubscribe();
		break;
	case MdUser::TableID:
		m_DB->TruncateMdUser();
		break;
	case MdUserLoginSession::TableID:
		m_DB->TruncateMdUserLoginSession();
		break;
	default:
		break;
	}
}

