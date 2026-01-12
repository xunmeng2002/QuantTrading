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

void DBWriter::OnTradingDayInsert(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnTradingDayBatchInsert(std::list<mdb::TradingDay*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnTradingDayErase(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnTradingDayUpdate(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnTradingDayTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = TradingDay::TableID;
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

void DBWriter::OnProductInsert(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnProductBatchInsert(std::list<mdb::Product*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnProductErase(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnProductUpdate(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnProductTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = nullptr;

	AddDBOperate(dbOperate);
}

void DBWriter::OnHotInstrumentInsert(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnHotInstrumentBatchInsert(std::list<mdb::HotInstrument*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnHotInstrumentErase(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnHotInstrumentEraseByTradingDayIndex(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->IndexID = HotInstrumentIndexTradingDay::IndexID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnHotInstrumentUpdate(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnHotInstrumentTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = HotInstrument::TableID;
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

void DBWriter::OnAccountInsert(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnAccountBatchInsert(std::list<mdb::Account*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = records;

	AddDBOperate(dbOperate);
}
void DBWriter::OnAccountErase(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnAccountUpdate(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	AddDBOperate(dbOperate);
}
void DBWriter::OnAccountTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Account::TableID;
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
	case TradingDay::TableID:
		m_DB->InsertTradingDay((TradingDay*)dbOperate->Record);
		break;
	case Exchange::TableID:
		m_DB->InsertExchange((Exchange*)dbOperate->Record);
		break;
	case Product::TableID:
		m_DB->InsertProduct((Product*)dbOperate->Record);
		break;
	case HotInstrument::TableID:
		m_DB->InsertHotInstrument((HotInstrument*)dbOperate->Record);
		break;
	case Instrument::TableID:
		m_DB->InsertInstrument((Instrument*)dbOperate->Record);
		break;
	case Account::TableID:
		m_DB->InsertAccount((Account*)dbOperate->Record);
		break;
	default:
		break;
	}
}
void DBWriter::BatchInsertRecords(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case TradingDay::TableID:
	{
		auto records = (std::list<TradingDay*>*)dbOperate->Record;
		m_DB->BatchInsertTradingDay(records);
		records->clear();
		delete records;
		break;
	}
	case Exchange::TableID:
	{
		auto records = (std::list<Exchange*>*)dbOperate->Record;
		m_DB->BatchInsertExchange(records);
		records->clear();
		delete records;
		break;
	}
	case Product::TableID:
	{
		auto records = (std::list<Product*>*)dbOperate->Record;
		m_DB->BatchInsertProduct(records);
		records->clear();
		delete records;
		break;
	}
	case HotInstrument::TableID:
	{
		auto records = (std::list<HotInstrument*>*)dbOperate->Record;
		m_DB->BatchInsertHotInstrument(records);
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
	case Account::TableID:
	{
		auto records = (std::list<Account*>*)dbOperate->Record;
		m_DB->BatchInsertAccount(records);
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
	case TradingDay::TableID:
		m_DB->DeleteTradingDay((TradingDay*)dbOperate->Record);
		((TradingDay*)dbOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->DeleteExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->DeleteProduct((Product*)dbOperate->Record);
		((Product*)dbOperate->Record)->Free();
		break;
	case HotInstrument::TableID:
		m_DB->DeleteHotInstrument((HotInstrument*)dbOperate->Record);
		((HotInstrument*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->DeleteInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->DeleteAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::DeleteRecordByIndex(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case HotInstrument::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case HotInstrumentIndexTradingDay::IndexID:
		{
			m_DB->DeleteHotInstrumentByTradingDayIndex((HotInstrument*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((HotInstrument*)dbOperate->Record)->Free();
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
	case TradingDay::TableID:
		m_DB->UpdateTradingDay((TradingDay*)dbOperate->Record);
		((TradingDay*)dbOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->UpdateExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->UpdateProduct((Product*)dbOperate->Record);
		((Product*)dbOperate->Record)->Free();
		break;
	case HotInstrument::TableID:
		m_DB->UpdateHotInstrument((HotInstrument*)dbOperate->Record);
		((HotInstrument*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->UpdateInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->UpdateAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}

void DBWriter::TruncateTable(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->TruncateTradingDay();
		break;
	case Exchange::TableID:
		m_DB->TruncateExchange();
		break;
	case Product::TableID:
		m_DB->TruncateProduct();
		break;
	case HotInstrument::TableID:
		m_DB->TruncateHotInstrument();
		break;
	case Instrument::TableID:
		m_DB->TruncateInstrument();
		break;
	case Account::TableID:
		m_DB->TruncateAccount();
		break;
	default:
		break;
	}
}

