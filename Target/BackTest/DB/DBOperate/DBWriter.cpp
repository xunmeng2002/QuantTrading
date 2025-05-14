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
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradingDayBatchInsert(std::list<mdb::TradingDay*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = TradingDay::TableID;
	dbOperate->Record = records;

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
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnExchangeBatchInsert(std::list<mdb::Exchange*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Exchange::TableID;
	dbOperate->Record = records;

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
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnProductBatchInsert(std::list<mdb::Product*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = records;

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
void DBWriter::OnProductTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Product::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnHotInstrumentInsert(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnHotInstrumentBatchInsert(std::list<mdb::HotInstrument*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnHotInstrumentErase(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnHotInstrumentEraseByTradingDayIndex(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->IndexID = HotInstrumentIndexTradingDay::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnHotInstrumentUpdate(mdb::HotInstrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnHotInstrumentTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = HotInstrument::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnInstrumentInsert(mdb::Instrument* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = records;

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
void DBWriter::OnInstrumentTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Instrument::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnPrimaryAccountInsert(mdb::PrimaryAccount* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPrimaryAccountBatchInsert(std::list<mdb::PrimaryAccount*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPrimaryAccountErase(mdb::PrimaryAccount* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPrimaryAccountEraseByOfferIDIndex(mdb::PrimaryAccount* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->IndexID = PrimaryAccountIndexOfferID::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPrimaryAccountUpdate(mdb::PrimaryAccount* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPrimaryAccountTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = PrimaryAccount::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnAccountInsert(mdb::Account* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnAccountBatchInsert(std::list<mdb::Account*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = records;

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
void DBWriter::OnAccountTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Account::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnCapitalInsert(mdb::Capital* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Capital::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnCapitalBatchInsert(std::list<mdb::Capital*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Capital::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnCapitalErase(mdb::Capital* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = Capital::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnCapitalEraseByTradingDayIndex(mdb::Capital* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = Capital::TableID;
	dbOperate->IndexID = CapitalIndexTradingDay::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnCapitalUpdate(mdb::Capital* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = Capital::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnCapitalTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Capital::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnPositionInsert(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionBatchInsert(std::list<mdb::Position*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = records;

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
void DBWriter::OnPositionEraseByAccountIndex(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = Position::TableID;
	dbOperate->IndexID = PositionIndexAccount::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionEraseByTradingDayIndex(mdb::Position* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = Position::TableID;
	dbOperate->IndexID = PositionIndexTradingDay::IndexID;
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
void DBWriter::OnPositionTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Position::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnPositionDetailInsert(mdb::PositionDetail* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailBatchInsert(std::list<mdb::PositionDetail*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailErase(mdb::PositionDetail* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailEraseByTradeMatchIndex(mdb::PositionDetail* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->IndexID = PositionDetailIndexTradeMatch::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailEraseByTradingDayIndex(mdb::PositionDetail* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::DeleteByIndex;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->IndexID = PositionDetailIndexTradingDay::IndexID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailUpdate(mdb::PositionDetail* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnPositionDetailTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = PositionDetail::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnOrderInsert(mdb::Order* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnOrderBatchInsert(std::list<mdb::Order*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Order::TableID;
	dbOperate->Record = records;

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
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnTradeBatchInsert(std::list<mdb::Trade*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = records;

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
void DBWriter::OnTradeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = Trade::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnDepthMarketDataInsert(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnDepthMarketDataErase(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnDepthMarketDataUpdate(mdb::DepthMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnDepthMarketDataTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = DepthMarketData::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnBarMarketDataInsert(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnBarMarketDataBatchInsert(std::list<mdb::BarMarketData*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnBarMarketDataErase(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnBarMarketDataUpdate(mdb::BarMarketData* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnBarMarketDataTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = BarMarketData::TableID;
	dbOperate->Record = nullptr;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}

void DBWriter::OnMdSubscribeInsert(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Insert;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdSubscribeBatchInsert(std::list<mdb::MdSubscribe*>* records)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::BatchInsert;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = records;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdSubscribeErase(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Delete;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdSubscribeUpdate(mdb::MdSubscribe* record)
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Update;
	dbOperate->TableID = MdSubscribe::TableID;
	dbOperate->Record = record;

	lock_guard<mutex> guard(m_Mutex);
	m_DBOperates.push_back(dbOperate);
}
void DBWriter::OnMdSubscribeTruncate()
{
	DBOperate* dbOperate = DBOperate::Allocate();
	dbOperate->Operate = DBOperateType::Truncate;
	dbOperate->TableID = MdSubscribe::TableID;
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
	if (!m_Connected)
		return;
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
	case PrimaryAccount::TableID:
		m_DB->InsertPrimaryAccount((PrimaryAccount*)dbOperate->Record);
		break;
	case Account::TableID:
		m_DB->InsertAccount((Account*)dbOperate->Record);
		break;
	case Capital::TableID:
		m_DB->InsertCapital((Capital*)dbOperate->Record);
		break;
	case Position::TableID:
		m_DB->InsertPosition((Position*)dbOperate->Record);
		break;
	case PositionDetail::TableID:
		m_DB->InsertPositionDetail((PositionDetail*)dbOperate->Record);
		break;
	case Order::TableID:
		m_DB->InsertOrder((Order*)dbOperate->Record);
		break;
	case Trade::TableID:
		m_DB->InsertTrade((Trade*)dbOperate->Record);
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
	case PrimaryAccount::TableID:
	{
		auto records = (std::list<PrimaryAccount*>*)dbOperate->Record;
		m_DB->BatchInsertPrimaryAccount(records);
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
	case Capital::TableID:
	{
		auto records = (std::list<Capital*>*)dbOperate->Record;
		m_DB->BatchInsertCapital(records);
		records->clear();
		delete records;
		break;
	}
	case Position::TableID:
	{
		auto records = (std::list<Position*>*)dbOperate->Record;
		m_DB->BatchInsertPosition(records);
		records->clear();
		delete records;
		break;
	}
	case PositionDetail::TableID:
	{
		auto records = (std::list<PositionDetail*>*)dbOperate->Record;
		m_DB->BatchInsertPositionDetail(records);
		records->clear();
		delete records;
		break;
	}
	case Order::TableID:
	{
		auto records = (std::list<Order*>*)dbOperate->Record;
		m_DB->BatchInsertOrder(records);
		records->clear();
		delete records;
		break;
	}
	case Trade::TableID:
	{
		auto records = (std::list<Trade*>*)dbOperate->Record;
		m_DB->BatchInsertTrade(records);
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
	case PrimaryAccount::TableID:
		m_DB->DeletePrimaryAccount((PrimaryAccount*)dbOperate->Record);
		((PrimaryAccount*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->DeleteAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Capital::TableID:
		m_DB->DeleteCapital((Capital*)dbOperate->Record);
		((Capital*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->DeletePosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case PositionDetail::TableID:
		m_DB->DeletePositionDetail((PositionDetail*)dbOperate->Record);
		((PositionDetail*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->DeleteOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->DeleteTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
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
	case PrimaryAccount::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case PrimaryAccountIndexOfferID::IndexID:
		{
			m_DB->DeletePrimaryAccountByOfferIDIndex((PrimaryAccount*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((PrimaryAccount*)dbOperate->Record)->Free();
		break;
	}
	case Capital::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case CapitalIndexTradingDay::IndexID:
		{
			m_DB->DeleteCapitalByTradingDayIndex((Capital*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((Capital*)dbOperate->Record)->Free();
		break;
	}
	case Position::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case PositionIndexAccount::IndexID:
		{
			m_DB->DeletePositionByAccountIndex((Position*)dbOperate->Record);
			break;
		}
		case PositionIndexTradingDay::IndexID:
		{
			m_DB->DeletePositionByTradingDayIndex((Position*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((Position*)dbOperate->Record)->Free();
		break;
	}
	case PositionDetail::TableID:
	{
		switch (dbOperate->IndexID)
		{
		case PositionDetailIndexTradeMatch::IndexID:
		{
			m_DB->DeletePositionDetailByTradeMatchIndex((PositionDetail*)dbOperate->Record);
			break;
		}
		case PositionDetailIndexTradingDay::IndexID:
		{
			m_DB->DeletePositionDetailByTradingDayIndex((PositionDetail*)dbOperate->Record);
			break;
		}
		default:
			WriteLog(LogLevel::Error, "Incorrect IndexID for DeleteRecordByIndex. TableID:0x%X, IndexID:%d", dbOperate->TableID, dbOperate->IndexID);
			break;
		}
		((PositionDetail*)dbOperate->Record)->Free();
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
	case PrimaryAccount::TableID:
		m_DB->UpdatePrimaryAccount((PrimaryAccount*)dbOperate->Record);
		((PrimaryAccount*)dbOperate->Record)->Free();
		break;
	case Account::TableID:
		m_DB->UpdateAccount((Account*)dbOperate->Record);
		((Account*)dbOperate->Record)->Free();
		break;
	case Capital::TableID:
		m_DB->UpdateCapital((Capital*)dbOperate->Record);
		((Capital*)dbOperate->Record)->Free();
		break;
	case Position::TableID:
		m_DB->UpdatePosition((Position*)dbOperate->Record);
		((Position*)dbOperate->Record)->Free();
		break;
	case PositionDetail::TableID:
		m_DB->UpdatePositionDetail((PositionDetail*)dbOperate->Record);
		((PositionDetail*)dbOperate->Record)->Free();
		break;
	case Order::TableID:
		m_DB->UpdateOrder((Order*)dbOperate->Record);
		((Order*)dbOperate->Record)->Free();
		break;
	case Trade::TableID:
		m_DB->UpdateTrade((Trade*)dbOperate->Record);
		((Trade*)dbOperate->Record)->Free();
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
	case PrimaryAccount::TableID:
		m_DB->TruncatePrimaryAccount();
		break;
	case Account::TableID:
		m_DB->TruncateAccount();
		break;
	case Capital::TableID:
		m_DB->TruncateCapital();
		break;
	case Position::TableID:
		m_DB->TruncatePosition();
		break;
	case PositionDetail::TableID:
		m_DB->TruncatePositionDetail();
		break;
	case Order::TableID:
		m_DB->TruncateOrder();
		break;
	case Trade::TableID:
		m_DB->TruncateTrade();
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
	default:
		break;
	}
}

