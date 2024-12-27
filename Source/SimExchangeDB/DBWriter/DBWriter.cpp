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
	for (auto item : m_TableOperates)
	{
		item->FreeRecord();
		item->Free();
	}
	m_TableOperates.clear();
}

void DBWriter::TruncateTables()
{
	m_DB->TruncateTables();
}
void DBWriter::OnTradingDayInsert(mdb::TradingDay* record)
{
	TradingDay* newRecord = TradingDay::Allocate();
	memcpy(newRecord, record, sizeof(TradingDay));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = TradingDay::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradingDayErase(mdb::TradingDay* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = TradingDay::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradingDayUpdate(mdb::TradingDay* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = TradingDay::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradingDayReplace(mdb::TradingDay* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = TradingDay::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradingDayTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = TradingDay::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnExchangeInsert(mdb::Exchange* record)
{
	Exchange* newRecord = Exchange::Allocate();
	memcpy(newRecord, record, sizeof(Exchange));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Exchange::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnExchangeErase(mdb::Exchange* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Exchange::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnExchangeUpdate(mdb::Exchange* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Exchange::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnExchangeReplace(mdb::Exchange* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Exchange::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnExchangeTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Exchange::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnProductInsert(mdb::Product* record)
{
	Product* newRecord = Product::Allocate();
	memcpy(newRecord, record, sizeof(Product));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Product::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnProductErase(mdb::Product* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Product::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnProductUpdate(mdb::Product* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Product::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnProductReplace(mdb::Product* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Product::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnProductTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Product::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnInstrumentInsert(mdb::Instrument* record)
{
	Instrument* newRecord = Instrument::Allocate();
	memcpy(newRecord, record, sizeof(Instrument));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Instrument::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnInstrumentErase(mdb::Instrument* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Instrument::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnInstrumentUpdate(mdb::Instrument* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Instrument::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnInstrumentReplace(mdb::Instrument* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Instrument::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnInstrumentTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Instrument::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnAccountInsert(mdb::Account* record)
{
	Account* newRecord = Account::Allocate();
	memcpy(newRecord, record, sizeof(Account));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Account::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnAccountErase(mdb::Account* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Account::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnAccountUpdate(mdb::Account* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Account::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnAccountReplace(mdb::Account* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Account::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnAccountTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Account::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnPositionInsert(mdb::Position* record)
{
	Position* newRecord = Position::Allocate();
	memcpy(newRecord, record, sizeof(Position));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Position::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnPositionErase(mdb::Position* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Position::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnPositionUpdate(mdb::Position* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Position::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnPositionReplace(mdb::Position* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Position::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnPositionTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Position::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnOrderInsert(mdb::Order* record)
{
	Order* newRecord = Order::Allocate();
	memcpy(newRecord, record, sizeof(Order));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Order::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnOrderErase(mdb::Order* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Order::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnOrderUpdate(mdb::Order* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Order::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnOrderReplace(mdb::Order* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Order::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnOrderTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Order::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnTradeInsert(mdb::Trade* record)
{
	Trade* newRecord = Trade::Allocate();
	memcpy(newRecord, record, sizeof(Trade));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = Trade::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradeErase(mdb::Trade* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = Trade::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradeUpdate(mdb::Trade* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = Trade::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradeReplace(mdb::Trade* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = Trade::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnTradeTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = Trade::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}

void DBWriter::OnMdTickInsert(mdb::MdTick* record)
{
	MdTick* newRecord = MdTick::Allocate();
	memcpy(newRecord, record, sizeof(MdTick));

	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Insert;
	tableOperate->TableID = MdTick::TableID;
	tableOperate->Record = newRecord;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnMdTickErase(mdb::MdTick* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Delete;
	tableOperate->TableID = MdTick::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnMdTickUpdate(mdb::MdTick* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Update;
	tableOperate->TableID = MdTick::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnMdTickReplace(mdb::MdTick* record)
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Replace;
	tableOperate->TableID = MdTick::TableID;
	tableOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}
void DBWriter::OnMdTickTruncate()
{
	TableOperate* tableOperate = TableOperate::Allocate();
	tableOperate->Operate = DBOperateType::Truncate;
	tableOperate->TableID = MdTick::TableID;
	tableOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_TableOperates.push_back(tableOperate);
}


void DBWriter::Run()
{
	CheckConnect();
	CheckTableOperate();
	HandleTableOperate();
}
void DBWriter::CheckConnect()
{
	if (!m_Connected)
	{
		Connect();
	}
}
void DBWriter::CheckTableOperate()
{
	unique_lock<mutex> guard(m_Mutex);
	m_ThreadConditionVariable.wait_for(guard, m_TimeOut, [&] {return !m_TableOperates.empty(); });
}
void DBWriter::HandleTableOperate()
{
	TableOperate* tableOperate = nullptr;
	try
	{
		while ((tableOperate = GetTableOperate()) != nullptr)
		{
			switch (tableOperate->Operate)
			{
			case DBOperateType::Insert:
			{
				InsertRecord(tableOperate);
				break;
			}
			case DBOperateType::Delete:
			{
				DeleteRecord(tableOperate);
				break;
			}
			case DBOperateType::DeleteByIndex:
			{
				DeleteRecordByIndex(tableOperate);
				break;
			}
			case DBOperateType::Update:
			{
				UpdateRecord(tableOperate);
				break;
			}
			case DBOperateType::Replace:
			{
				ReplaceRecord(tableOperate);
				break;
			}
			case DBOperateType::BatchUpdate:
			{
				BatchUpdateRecords(tableOperate);
				break;
			}
			case DBOperateType::Truncate:
			{
				TruncateTable(tableOperate);
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unknown DBOperateType:%d", tableOperate->Operate);
				break;
			}
			tableOperate->Free();
		}
	}
	catch (exception e)
	{
		WriteLog(LogLevel::Warning, "HandleTableOperate Failed. TableID;0x%X, Operate:%d, Message:%s", tableOperate->TableID, (int)tableOperate->Operate, e.what());
		DisConnect();
		tableOperate->FreeRecord();
		tableOperate->Free();
		this_thread::sleep_for(chrono::seconds(5));
	}
}
TableOperate* DBWriter::GetTableOperate()
{
	lock_guard<mutex> guard(m_Mutex);
	if (m_TableOperates.empty())
	{
		return nullptr;
	}
	static int i = 0;
	if (++i % 100 == 0)
	{
		WriteLog(LogLevel::Info, "TotalOperate:%d, m_TableOperate.size:%d", i, m_TableOperates.size());
	}
	auto item = m_TableOperates.front();
	m_TableOperates.pop_front();
	return item;
}

void DBWriter::InsertRecord(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->InsertTradingDay((TradingDay*)tableOperate->Record);
		((TradingDay*)tableOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->InsertExchange((Exchange*)tableOperate->Record);
		((Exchange*)tableOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->InsertProduct((Product*)tableOperate->Record);
		((Product*)tableOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->InsertInstrument((Instrument*)tableOperate->Record);
		((Instrument*)tableOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->InsertAccount((Account*)tableOperate->Record);
		((Account*)tableOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->InsertPosition((Position*)tableOperate->Record);
		((Position*)tableOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->InsertOrder((Order*)tableOperate->Record);
		((Order*)tableOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->InsertTrade((Trade*)tableOperate->Record);
		((Trade*)tableOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->InsertMdTick((MdTick*)tableOperate->Record);
		((MdTick*)tableOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::DeleteRecord(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->DeleteTradingDay((TradingDay*)tableOperate->Record);
		((TradingDay*)tableOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->DeleteExchange((Exchange*)tableOperate->Record);
		((Exchange*)tableOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->DeleteProduct((Product*)tableOperate->Record);
		((Product*)tableOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->DeleteInstrument((Instrument*)tableOperate->Record);
		((Instrument*)tableOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->DeleteAccount((Account*)tableOperate->Record);
		((Account*)tableOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->DeletePosition((Position*)tableOperate->Record);
		((Position*)tableOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->DeleteOrder((Order*)tableOperate->Record);
		((Order*)tableOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->DeleteTrade((Trade*)tableOperate->Record);
		((Trade*)tableOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->DeleteMdTick((MdTick*)tableOperate->Record);
		((MdTick*)tableOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::DeleteRecordByIndex(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	default:
		WriteLog(LogLevel::Error, "Incorrect TableID for DeleteRecordByIndex. TableID:0x%X", tableOperate->TableID);
		break;
	}
}
void DBWriter::UpdateRecord(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->UpdateTradingDay((TradingDay*)tableOperate->Record);
		((TradingDay*)tableOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->UpdateExchange((Exchange*)tableOperate->Record);
		((Exchange*)tableOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->UpdateProduct((Product*)tableOperate->Record);
		((Product*)tableOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->UpdateInstrument((Instrument*)tableOperate->Record);
		((Instrument*)tableOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->UpdateAccount((Account*)tableOperate->Record);
		((Account*)tableOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->UpdatePosition((Position*)tableOperate->Record);
		((Position*)tableOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->UpdateOrder((Order*)tableOperate->Record);
		((Order*)tableOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->UpdateTrade((Trade*)tableOperate->Record);
		((Trade*)tableOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->UpdateMdTick((MdTick*)tableOperate->Record);
		((MdTick*)tableOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::ReplaceRecord(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	case TradingDay::TableID:
		m_DB->ReplaceTradingDay((TradingDay*)tableOperate->Record);
		((TradingDay*)tableOperate->Record)->Free();
		break;
	case Exchange::TableID:
		m_DB->ReplaceExchange((Exchange*)tableOperate->Record);
		((Exchange*)tableOperate->Record)->Free();
		break;
	case Product::TableID:
		m_DB->ReplaceProduct((Product*)tableOperate->Record);
		((Product*)tableOperate->Record)->Free();
		break;
	case Instrument::TableID:
		m_DB->ReplaceInstrument((Instrument*)tableOperate->Record);
		((Instrument*)tableOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->ReplaceAccount((Account*)tableOperate->Record);
		((Account*)tableOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->ReplacePosition((Position*)tableOperate->Record);
		((Position*)tableOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->ReplaceOrder((Order*)tableOperate->Record);
		((Order*)tableOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->ReplaceTrade((Trade*)tableOperate->Record);
		((Trade*)tableOperate->Record)->Free();
		break;
	case MdTick::TableID:
		m_DB->ReplaceMdTick((MdTick*)tableOperate->Record);
		((MdTick*)tableOperate->Record)->Free();
		break;
	default:
		break;
	}
}
void DBWriter::BatchUpdateRecords(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
	{
	default:
		WriteLog(LogLevel::Error, "Unexpected BatchUpdate TableID:0x%X", tableOperate->TableID);
		break;
	}
}
void DBWriter::TruncateTable(TableOperate* tableOperate)
{
	switch (tableOperate->TableID)
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

