#include "DBWriter.h"
#include "Logger.h"
#include "MdbIndexes.h"
#include <cstring>
#include <mutex>

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

void DBWriter::TruncateTables()
{
	m_DB->TruncateTables();
}
void DBWriter::OnTradingDayInsert(mdb::TradingDay* record)
{
	TradingDay* newRecord = TradingDay::Allocate();
	memcpy(newRecord, record, sizeof(TradingDay));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradingDayErase(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradingDayUpdate(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradingDayReplace(mdb::TradingDay* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradingDayTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnExchangeInsert(mdb::Exchange* record)
{
	Exchange* newRecord = Exchange::Allocate();
	memcpy(newRecord, record, sizeof(Exchange));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnExchangeErase(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnExchangeUpdate(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnExchangeReplace(mdb::Exchange* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnExchangeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnProductInsert(mdb::Product* record)
{
	Product* newRecord = Product::Allocate();
	memcpy(newRecord, record, sizeof(Product));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnProductErase(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnProductUpdate(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnProductReplace(mdb::Product* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnProductTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnInstrumentInsert(mdb::Instrument* record)
{
	Instrument* newRecord = Instrument::Allocate();
	memcpy(newRecord, record, sizeof(Instrument));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnInstrumentErase(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnInstrumentUpdate(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnInstrumentReplace(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnInstrumentTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnAccountInsert(mdb::Account* record)
{
	Account* newRecord = Account::Allocate();
	memcpy(newRecord, record, sizeof(Account));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnAccountErase(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnAccountUpdate(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnAccountReplace(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnAccountTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnPositionInsert(mdb::Position* record)
{
	Position* newRecord = Position::Allocate();
	memcpy(newRecord, record, sizeof(Position));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionErase(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionUpdate(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionReplace(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnOrderInsert(mdb::Order* record)
{
	Order* newRecord = Order::Allocate();
	memcpy(newRecord, record, sizeof(Order));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnOrderErase(mdb::Order* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnOrderUpdate(mdb::Order* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnOrderReplace(mdb::Order* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnOrderTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnTradeInsert(mdb::Trade* record)
{
	Trade* newRecord = Trade::Allocate();
	memcpy(newRecord, record, sizeof(Trade));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradeErase(mdb::Trade* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradeUpdate(mdb::Trade* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradeReplace(mdb::Trade* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnMdTickInsert(mdb::MdTick* record)
{
	MdTick* newRecord = MdTick::Allocate();
	memcpy(newRecord, record, sizeof(MdTick));

	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = MdTick::TableID;
	dbOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdTickErase(mdb::MdTick* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = MdTick::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdTickUpdate(mdb::MdTick* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = MdTick::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdTickReplace(mdb::MdTick* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Replace;
	dbOperate->TableID = MdTick::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdTickTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = MdTick::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
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
	m_ThreadConditionVariable.wait_for(guard, m_TimeOut, [&] {return !m_DBOperates.empty(); });
}
void DBWriter::HandleDBOperate()
{
	DBOperate* dbOperate = nullptr;
	try
	{
		while ((dbOperate = GetDBOperate()) != nullptr)
		{
			switch (dbOperate->Operate)
			{
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
			case DBOperateType::Replace:
			{
				ReplaceRecord(dbOperate);
				break;
			}
			case DBOperateType::BatchUpdate:
			{
				BatchUpdateRecords(dbOperate);
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
	catch (exception e)
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
	static int i = 0;
	if (++i % 100 == 0)
	{
		WriteLog(LogLevel::Info, "TotalOperate:%d, m_DBOperate.size:%d", i, m_DBOperates.size());
	}
	auto item = m_DBOperates.front();
	m_DBOperates.pop_front();
	return item;
}

void DBWriter::InsertRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->InsertTradingDay((TradingDay*)dbOperate->Record);
		((TradingDay*)dbOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->InsertExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->InsertProduct((Product*)dbOperate->Record);
		((Product*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->InsertInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->InsertAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->InsertPosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->InsertOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->InsertTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->InsertMdTick((MdTick*)dbOperate->Record);
		((MdTick*)dbOperate->Record)->Free();
		break;
	default:
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
	case Instrument::TableID:
		m_DB->DeleteInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->DeleteAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->DeletePosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->DeleteOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->DeleteTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->DeleteMdTick((MdTick*)dbOperate->Record);
		((MdTick*)dbOperate->Record)->Free();
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
	case Instrument::TableID:
		m_DB->UpdateInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->UpdateAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->UpdatePosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->UpdateOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->UpdateTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->UpdateMdTick((MdTick*)dbOperate->Record);
		((MdTick*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::ReplaceRecord(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->ReplaceTradingDay((TradingDay*)dbOperate->Record);
		((TradingDay*)dbOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->ReplaceExchange((Exchange*)dbOperate->Record);
		((Exchange*)dbOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->ReplaceProduct((Product*)dbOperate->Record);
		((Product*)dbOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->ReplaceInstrument((Instrument*)dbOperate->Record);
		((Instrument*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->ReplaceAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->ReplacePosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->ReplaceOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->ReplaceTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->ReplaceMdTick((MdTick*)dbOperate->Record);
		((MdTick*)dbOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::BatchUpdateRecords(DBOperate* dbOperate)
{
	switch (dbOperate->TableID)
	{
	default:
		WriteLog(LogLevel::Error, "Unexpected BatchUpdate TableID:0x%X", dbOperate->TableID);
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
	case Instrument::TableID:
		m_DB->TruncateInstrument();
		break;
	case Account::TableID:
		m_DB->TruncateAccount();
		break;
	case Position::TableID:
		m_DB->TruncatePosition();
		break;
	case Order::TableID:
		m_DB->TruncateOrder();
		break;
	case Trade::TableID:
		m_DB->TruncateTrade();
		break;
	case MdTick::TableID:
		m_DB->TruncateMdTick();
		break;
	default:
		break;
	}
}

