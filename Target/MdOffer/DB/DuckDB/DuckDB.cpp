#include "DuckDB.h"
#include "Constant.h"
#include "Logger.h"
#include "Utility.h"
#include "TimeUtility.h"
#include "DuckDBCommon.h"
#include <string.h>
#include <cstring>

using namespace mdb;
using namespace std;
using namespace std::chrono;

DuckDB::DuckDB(const std::string& dbName)
	:m_DBName(dbName), m_DB(nullptr), m_Connection(nullptr)
{
	m_SqlBuff = new char[BuffSize];

	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
	m_InstrumentUpdateStatement = nullptr;
	m_InstrumentSelectStatement = nullptr;
	m_InstrumentTruncateStatement = nullptr;

	m_DepthMarketDataDeleteStatement = nullptr;
	m_DepthMarketDataUpdateStatement = nullptr;
	m_DepthMarketDataSelectStatement = nullptr;
	m_DepthMarketDataTruncateStatement = nullptr;

	m_BarMarketDataDeleteStatement = nullptr;
	m_BarMarketDataUpdateStatement = nullptr;
	m_BarMarketDataSelectStatement = nullptr;
	m_BarMarketDataTruncateStatement = nullptr;

	m_MdSubscribeDeleteStatement = nullptr;
	m_MdSubscribeUpdateStatement = nullptr;
	m_MdSubscribeSelectStatement = nullptr;
	m_MdSubscribeTruncateStatement = nullptr;

	m_MdUserDeleteStatement = nullptr;
	m_MdUserUpdateStatement = nullptr;
	m_MdUserSelectStatement = nullptr;
	m_MdUserTruncateStatement = nullptr;

	m_MdUserLoginSessionDeleteStatement = nullptr;
	m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	m_MdUserLoginSessionUpdateStatement = nullptr;
	m_MdUserLoginSessionSelectStatement = nullptr;
	m_MdUserLoginSessionTruncateStatement = nullptr;

}
DuckDB::~DuckDB()
{
	delete[] m_SqlBuff;
	DisConnect();
}
bool DuckDB::Connect()
{
	int result = duckdb_open(m_DBName.c_str(), &m_DB);
	if (result != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "Open DuckDB Failed.");
		return false;
	}
	if (duckdb_connect(m_DB, &m_Connection) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Error, "duckdb_connect Error.");
		return false;
	}
	return true;
}
void DuckDB::DisConnect()
{
	if (m_Connection != nullptr)
	{
		duckdb_disconnect(&m_Connection);
		m_Connection = nullptr;
	}
	if (m_DB != nullptr)
	{
		duckdb_close(&m_DB);
		m_DB = nullptr;
	}
	if (m_ExchangeDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ExchangeDeleteStatement);
		m_ExchangeDeleteStatement = nullptr;
	}
	if (m_ExchangeUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ExchangeUpdateStatement);
		m_ExchangeUpdateStatement = nullptr;
	}
	if (m_ExchangeSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ExchangeSelectStatement);
		m_ExchangeSelectStatement = nullptr;
	}
	if (m_ExchangeTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ExchangeTruncateStatement);
		m_ExchangeTruncateStatement = nullptr;
	}
	if (m_InstrumentDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_InstrumentDeleteStatement);
		m_InstrumentDeleteStatement = nullptr;
	}
	if (m_InstrumentDeleteByExchangeIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_InstrumentDeleteByExchangeIDIndexStatement);
		m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
	}
	if (m_InstrumentUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_InstrumentUpdateStatement);
		m_InstrumentUpdateStatement = nullptr;
	}
	if (m_InstrumentSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_InstrumentSelectStatement);
		m_InstrumentSelectStatement = nullptr;
	}
	if (m_InstrumentTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_InstrumentTruncateStatement);
		m_InstrumentTruncateStatement = nullptr;
	}
	if (m_DepthMarketDataDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_DepthMarketDataDeleteStatement);
		m_DepthMarketDataDeleteStatement = nullptr;
	}
	if (m_DepthMarketDataUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_DepthMarketDataUpdateStatement);
		m_DepthMarketDataUpdateStatement = nullptr;
	}
	if (m_DepthMarketDataSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_DepthMarketDataSelectStatement);
		m_DepthMarketDataSelectStatement = nullptr;
	}
	if (m_DepthMarketDataTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_DepthMarketDataTruncateStatement);
		m_DepthMarketDataTruncateStatement = nullptr;
	}
	if (m_BarMarketDataDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_BarMarketDataDeleteStatement);
		m_BarMarketDataDeleteStatement = nullptr;
	}
	if (m_BarMarketDataUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_BarMarketDataUpdateStatement);
		m_BarMarketDataUpdateStatement = nullptr;
	}
	if (m_BarMarketDataSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_BarMarketDataSelectStatement);
		m_BarMarketDataSelectStatement = nullptr;
	}
	if (m_BarMarketDataTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_BarMarketDataTruncateStatement);
		m_BarMarketDataTruncateStatement = nullptr;
	}
	if (m_MdSubscribeDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdSubscribeDeleteStatement);
		m_MdSubscribeDeleteStatement = nullptr;
	}
	if (m_MdSubscribeUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdSubscribeUpdateStatement);
		m_MdSubscribeUpdateStatement = nullptr;
	}
	if (m_MdSubscribeSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdSubscribeSelectStatement);
		m_MdSubscribeSelectStatement = nullptr;
	}
	if (m_MdSubscribeTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdSubscribeTruncateStatement);
		m_MdSubscribeTruncateStatement = nullptr;
	}
	if (m_MdUserDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserDeleteStatement);
		m_MdUserDeleteStatement = nullptr;
	}
	if (m_MdUserUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserUpdateStatement);
		m_MdUserUpdateStatement = nullptr;
	}
	if (m_MdUserSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserSelectStatement);
		m_MdUserSelectStatement = nullptr;
	}
	if (m_MdUserTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserTruncateStatement);
		m_MdUserTruncateStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserLoginSessionDeleteStatement);
		m_MdUserLoginSessionDeleteStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserLoginSessionDeleteByMdUserIDIndexStatement);
		m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	}
	if (m_MdUserLoginSessionUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserLoginSessionUpdateStatement);
		m_MdUserLoginSessionUpdateStatement = nullptr;
	}
	if (m_MdUserLoginSessionSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserLoginSessionSelectStatement);
		m_MdUserLoginSessionSelectStatement = nullptr;
	}
	if (m_MdUserLoginSessionTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_MdUserLoginSessionTruncateStatement);
		m_MdUserLoginSessionTruncateStatement = nullptr;
	}
}
void DuckDB::InitDB()
{
	Exec("Delete From t_Exchange;");
	Exec("Insert Into t_Exchange select * from Init.t_Exchange;");
	Exec("Delete From t_Instrument;");
	Exec("Insert Into t_Instrument select * from Init.t_Instrument;");
	Exec("Delete From t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Delete From t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	Exec("Delete From t_MdSubscribe;");
	Exec("Insert Into t_MdSubscribe select * from Init.t_MdSubscribe;");
	Exec("Delete From t_MdUser;");
	Exec("Insert Into t_MdUser select * from Init.t_MdUser;");
	Exec("Delete From t_MdUserLoginSession;");
	Exec("Insert Into t_MdUserLoginSession select * from Init.t_MdUserLoginSession;");
}
void DuckDB::CreateTables()
{
	CreateExchange();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreateMdSubscribe();
	CreateMdUser();
	CreateMdUserLoginSession();
}
void DuckDB::DropTables()
{
	DropExchange();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropMdSubscribe();
	DropMdUser();
	DropMdUserLoginSession();
}
void DuckDB::TruncateTables()
{
	TruncateExchange();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncateMdSubscribe();
	TruncateMdUser();
	TruncateMdUserLoginSession();
}
void DuckDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateMdUserLoginSession();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
bool DuckDB::Exec(const char* sql) const
{
	duckdb_prepared_statement stmt;
	if (duckdb_prepare(m_Connection, sql, &stmt) != DuckDBSuccess) 
	{
		WriteLog(LogLevel::Warning, "duckdb_prepare Failed While Exec Sql:%s, ErrorMsg:%s", sql, duckdb_prepare_error(stmt));
		duckdb_destroy_prepare(&stmt);
		return false;
	}
	duckdb_result result;
	auto ret = duckdb_execute_prepared(stmt, &result);
	if (ret != DuckDBSuccess) 
	{
		WriteLog(LogLevel::Warning, "duckdb_execute_prepared Failed While Exec Sql:%s, ErrorMsg:%s", sql, duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	duckdb_destroy_prepare(&stmt);
	return ret == DuckDBSuccess;
}

void DuckDB::CreateExchange()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Exchange (ExchangeID varchar, ExchangeName varchar, PRIMARY KEY(ExchangeID));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateExchange failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateExchange Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropExchange()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_Exchange;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropExchange failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropExchange Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertExchange(Exchange* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Exchange", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Exchange Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForExchangeRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertExchange(std::list<Exchange*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Exchange", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Exchange Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForExchangeRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertExchange RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Exchange where ExchangeID = ?;", &m_ExchangeDeleteStatement);
	}
	SetStatementForExchangePrimaryKey(m_ExchangeDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ExchangeDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteExchange Spend:%lldms", duration);
	}
}
void DuckDB::UpdateExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Exchange set ExchangeName = ? where ExchangeID = ?;", &m_ExchangeUpdateStatement);
	}
	SetStatementForExchangeRecordUpdate(m_ExchangeUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ExchangeUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateExchange Spend:%lldms", duration);
	}
}
void DuckDB::SelectExchange(std::list<Exchange*>& records)
{
	auto start = steady_clock::now();
	if (m_ExchangeSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Exchange;", &m_ExchangeSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ExchangeSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectExchange ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectExchange Spend:%lldms", duration);
	}
}
void DuckDB::TruncateExchange()
{
	auto start = steady_clock::now();
	if (m_ExchangeTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Exchange;", &m_ExchangeTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_ExchangeTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateExchange failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateExchange Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Exchange*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Exchange* record = Exchange::Allocate();
			memset(record, 0, sizeof(Exchange));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ExchangeName, dataColumn1[row]);
			}
			records.push_back(record);
		}
	}
}
void DuckDB::CreateInstrument()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Instrument (ExchangeID varchar, InstrumentID varchar, ExchangeInstID varchar, InstrumentName varchar, ProductID varchar, ProductClass int, InstrumentClass int, Rank int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName varchar, PRIMARY KEY(ExchangeID, InstrumentID));CREATE INDEX IF NOT EXISTS InstrumentExchangeID ON t_Instrument(ExchangeID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateInstrument failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateInstrument Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropInstrument()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX InstrumentExchangeID;DROP TABLE IF EXISTS t_Instrument;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropInstrument failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropInstrument Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertInstrument(Instrument* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Instrument", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Instrument Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForInstrumentRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertInstrument(std::list<Instrument*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Instrument", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Instrument Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForInstrumentRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Instrument where ExchangeID = ? and InstrumentID = ?;", &m_InstrumentDeleteStatement);
	}
	SetStatementForInstrumentPrimaryKey(m_InstrumentDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_InstrumentDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrument Spend:%lldms", duration);
	}
}
void DuckDB::DeleteInstrumentByExchangeIDIndex(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteByExchangeIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Instrument where ExchangeID = ?;", &m_InstrumentDeleteByExchangeIDIndexStatement);
	}
	SetStatementForInstrumentIndexExchangeID(m_InstrumentDeleteByExchangeIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_InstrumentDeleteByExchangeIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrumentByExchangeIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrumentByExchangeIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Instrument set ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, ProductClass = ?, InstrumentClass = ?, Rank = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;", &m_InstrumentUpdateStatement);
	}
	SetStatementForInstrumentRecordUpdate(m_InstrumentUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_InstrumentUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument Spend:%lldms", duration);
	}
}
void DuckDB::SelectInstrument(std::list<Instrument*>& records)
{
	auto start = steady_clock::now();
	if (m_InstrumentSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Instrument;", &m_InstrumentSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_InstrumentSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectInstrument ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectInstrument Spend:%lldms", duration);
	}
}
void DuckDB::TruncateInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Instrument;", &m_InstrumentTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_InstrumentTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateInstrument failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Instrument*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);
		duckdb_vector column7 = duckdb_data_chunk_get_vector(dataChunk, 7);
		duckdb_vector column8 = duckdb_data_chunk_get_vector(dataChunk, 8);
		duckdb_vector column9 = duckdb_data_chunk_get_vector(dataChunk, 9);
		duckdb_vector column10 = duckdb_data_chunk_get_vector(dataChunk, 10);
		duckdb_vector column11 = duckdb_data_chunk_get_vector(dataChunk, 11);
		duckdb_vector column12 = duckdb_data_chunk_get_vector(dataChunk, 12);
		duckdb_vector column13 = duckdb_data_chunk_get_vector(dataChunk, 13);
		duckdb_vector column14 = duckdb_data_chunk_get_vector(dataChunk, 14);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		int* dataColumn7 = (int*)duckdb_vector_get_data(column7);
		int* dataColumn8 = (int*)duckdb_vector_get_data(column8);
		double* dataColumn9 = (double*)duckdb_vector_get_data(column9);
		int64_t* dataColumn10 = (int64_t*)duckdb_vector_get_data(column10);
		int64_t* dataColumn11 = (int64_t*)duckdb_vector_get_data(column11);
		int64_t* dataColumn12 = (int64_t*)duckdb_vector_get_data(column12);
		int64_t* dataColumn13 = (int64_t*)duckdb_vector_get_data(column13);
		duckdb_string_t* dataColumn14 = (duckdb_string_t*)duckdb_vector_get_data(column14);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);
		uint64_t* validityColumn9 = duckdb_vector_get_validity(column9);
		uint64_t* validityColumn10 = duckdb_vector_get_validity(column10);
		uint64_t* validityColumn11 = duckdb_vector_get_validity(column11);
		uint64_t* validityColumn12 = duckdb_vector_get_validity(column12);
		uint64_t* validityColumn13 = duckdb_vector_get_validity(column13);
		uint64_t* validityColumn14 = duckdb_vector_get_validity(column14);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Instrument* record = Instrument::Allocate();
			memset(record, 0, sizeof(Instrument));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->ExchangeInstID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->InstrumentName, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->ProductID, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->ProductClass = ProductClassType(dataColumn5[row]);
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->InstrumentClass = InstrumentClassType(dataColumn6[row]);
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->Rank = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->VolumeMultiple = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->PriceTick = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->MaxMarketOrderVolume = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->MinMarketOrderVolume = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->MaxLimitOrderVolume = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->MinLimitOrderVolume = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row))
			{
				CpyDuckdbString(record->SessionName, dataColumn14[row]);
			}
			records.push_back(record);
		}
	}
}
void DuckDB::CreateDepthMarketData()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_DepthMarketData (TradingDay varchar, ExchangeID varchar, InstrumentID varchar, UpdateTs bigint, LastPrice double, PreSettlementPrice double, PreClosePrice double, PreOpenInterest double, OpenPrice double, HighestPrice double, LowestPrice double, ClosePrice double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, SettlementPrice double, UpperLimitPrice double, LowerLimitPrice double, AveragePrice double, AskPrice1 double, AskPrice2 double, AskPrice3 double, AskPrice4 double, AskPrice5 double, AskPrice6 double, AskPrice7 double, AskPrice8 double, AskPrice9 double, AskPrice10 double, AskVolume1 bigint, AskVolume2 bigint, AskVolume3 bigint, AskVolume4 bigint, AskVolume5 bigint, AskVolume6 bigint, AskVolume7 bigint, AskVolume8 bigint, AskVolume9 bigint, AskVolume10 bigint, BidPrice1 double, BidPrice2 double, BidPrice3 double, BidPrice4 double, BidPrice5 double, BidPrice6 double, BidPrice7 double, BidPrice8 double, BidPrice9 double, BidPrice10 double, BidVolume1 bigint, BidVolume2 bigint, BidVolume3 bigint, BidVolume4 bigint, BidVolume5 bigint, BidVolume6 bigint, BidVolume7 bigint, BidVolume8 bigint, BidVolume9 bigint, BidVolume10 bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateDepthMarketData failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateDepthMarketData Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropDepthMarketData()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_DepthMarketData;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropDepthMarketData failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropDepthMarketData Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertDepthMarketData(DepthMarketData* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_DepthMarketData", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_DepthMarketData Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForDepthMarketDataRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertDepthMarketData(std::list<DepthMarketData*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_DepthMarketData", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_DepthMarketData Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForDepthMarketDataRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertDepthMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_DepthMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;", &m_DepthMarketDataDeleteStatement);
	}
	SetStatementForDepthMarketDataPrimaryKey(m_DepthMarketDataDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_DepthMarketDataDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteDepthMarketData Spend:%lldms", duration);
	}
}
void DuckDB::UpdateDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_DepthMarketData set UpdateTs = ?, LastPrice = ?, PreSettlementPrice = ?, PreClosePrice = ?, PreOpenInterest = ?, OpenPrice = ?, HighestPrice = ?, LowestPrice = ?, ClosePrice = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ?, SettlementPrice = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, AveragePrice = ?, AskPrice1 = ?, AskPrice2 = ?, AskPrice3 = ?, AskPrice4 = ?, AskPrice5 = ?, AskPrice6 = ?, AskPrice7 = ?, AskPrice8 = ?, AskPrice9 = ?, AskPrice10 = ?, AskVolume1 = ?, AskVolume2 = ?, AskVolume3 = ?, AskVolume4 = ?, AskVolume5 = ?, AskVolume6 = ?, AskVolume7 = ?, AskVolume8 = ?, AskVolume9 = ?, AskVolume10 = ?, BidPrice1 = ?, BidPrice2 = ?, BidPrice3 = ?, BidPrice4 = ?, BidPrice5 = ?, BidPrice6 = ?, BidPrice7 = ?, BidPrice8 = ?, BidPrice9 = ?, BidPrice10 = ?, BidVolume1 = ?, BidVolume2 = ?, BidVolume3 = ?, BidVolume4 = ?, BidVolume5 = ?, BidVolume6 = ?, BidVolume7 = ?, BidVolume8 = ?, BidVolume9 = ?, BidVolume10 = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;", &m_DepthMarketDataUpdateStatement);
	}
	SetStatementForDepthMarketDataRecordUpdate(m_DepthMarketDataUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_DepthMarketDataUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData Spend:%lldms", duration);
	}
}
void DuckDB::SelectDepthMarketData(std::list<DepthMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_DepthMarketData where TradingDay >= ?;", &m_DepthMarketDataSelectStatement);
	}
	duckdb_bind_varchar(m_DepthMarketDataSelectStatement, 1, tradingDay);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_DepthMarketDataSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectDepthMarketData ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectDepthMarketData Spend:%lldms", duration);
	}
}
void DuckDB::TruncateDepthMarketData()
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_DepthMarketData;", &m_DepthMarketDataTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_DepthMarketDataTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateDepthMarketData failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateDepthMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<DepthMarketData*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);
		duckdb_vector column7 = duckdb_data_chunk_get_vector(dataChunk, 7);
		duckdb_vector column8 = duckdb_data_chunk_get_vector(dataChunk, 8);
		duckdb_vector column9 = duckdb_data_chunk_get_vector(dataChunk, 9);
		duckdb_vector column10 = duckdb_data_chunk_get_vector(dataChunk, 10);
		duckdb_vector column11 = duckdb_data_chunk_get_vector(dataChunk, 11);
		duckdb_vector column12 = duckdb_data_chunk_get_vector(dataChunk, 12);
		duckdb_vector column13 = duckdb_data_chunk_get_vector(dataChunk, 13);
		duckdb_vector column14 = duckdb_data_chunk_get_vector(dataChunk, 14);
		duckdb_vector column15 = duckdb_data_chunk_get_vector(dataChunk, 15);
		duckdb_vector column16 = duckdb_data_chunk_get_vector(dataChunk, 16);
		duckdb_vector column17 = duckdb_data_chunk_get_vector(dataChunk, 17);
		duckdb_vector column18 = duckdb_data_chunk_get_vector(dataChunk, 18);
		duckdb_vector column19 = duckdb_data_chunk_get_vector(dataChunk, 19);
		duckdb_vector column20 = duckdb_data_chunk_get_vector(dataChunk, 20);
		duckdb_vector column21 = duckdb_data_chunk_get_vector(dataChunk, 21);
		duckdb_vector column22 = duckdb_data_chunk_get_vector(dataChunk, 22);
		duckdb_vector column23 = duckdb_data_chunk_get_vector(dataChunk, 23);
		duckdb_vector column24 = duckdb_data_chunk_get_vector(dataChunk, 24);
		duckdb_vector column25 = duckdb_data_chunk_get_vector(dataChunk, 25);
		duckdb_vector column26 = duckdb_data_chunk_get_vector(dataChunk, 26);
		duckdb_vector column27 = duckdb_data_chunk_get_vector(dataChunk, 27);
		duckdb_vector column28 = duckdb_data_chunk_get_vector(dataChunk, 28);
		duckdb_vector column29 = duckdb_data_chunk_get_vector(dataChunk, 29);
		duckdb_vector column30 = duckdb_data_chunk_get_vector(dataChunk, 30);
		duckdb_vector column31 = duckdb_data_chunk_get_vector(dataChunk, 31);
		duckdb_vector column32 = duckdb_data_chunk_get_vector(dataChunk, 32);
		duckdb_vector column33 = duckdb_data_chunk_get_vector(dataChunk, 33);
		duckdb_vector column34 = duckdb_data_chunk_get_vector(dataChunk, 34);
		duckdb_vector column35 = duckdb_data_chunk_get_vector(dataChunk, 35);
		duckdb_vector column36 = duckdb_data_chunk_get_vector(dataChunk, 36);
		duckdb_vector column37 = duckdb_data_chunk_get_vector(dataChunk, 37);
		duckdb_vector column38 = duckdb_data_chunk_get_vector(dataChunk, 38);
		duckdb_vector column39 = duckdb_data_chunk_get_vector(dataChunk, 39);
		duckdb_vector column40 = duckdb_data_chunk_get_vector(dataChunk, 40);
		duckdb_vector column41 = duckdb_data_chunk_get_vector(dataChunk, 41);
		duckdb_vector column42 = duckdb_data_chunk_get_vector(dataChunk, 42);
		duckdb_vector column43 = duckdb_data_chunk_get_vector(dataChunk, 43);
		duckdb_vector column44 = duckdb_data_chunk_get_vector(dataChunk, 44);
		duckdb_vector column45 = duckdb_data_chunk_get_vector(dataChunk, 45);
		duckdb_vector column46 = duckdb_data_chunk_get_vector(dataChunk, 46);
		duckdb_vector column47 = duckdb_data_chunk_get_vector(dataChunk, 47);
		duckdb_vector column48 = duckdb_data_chunk_get_vector(dataChunk, 48);
		duckdb_vector column49 = duckdb_data_chunk_get_vector(dataChunk, 49);
		duckdb_vector column50 = duckdb_data_chunk_get_vector(dataChunk, 50);
		duckdb_vector column51 = duckdb_data_chunk_get_vector(dataChunk, 51);
		duckdb_vector column52 = duckdb_data_chunk_get_vector(dataChunk, 52);
		duckdb_vector column53 = duckdb_data_chunk_get_vector(dataChunk, 53);
		duckdb_vector column54 = duckdb_data_chunk_get_vector(dataChunk, 54);
		duckdb_vector column55 = duckdb_data_chunk_get_vector(dataChunk, 55);
		duckdb_vector column56 = duckdb_data_chunk_get_vector(dataChunk, 56);
		duckdb_vector column57 = duckdb_data_chunk_get_vector(dataChunk, 57);
		duckdb_vector column58 = duckdb_data_chunk_get_vector(dataChunk, 58);
		duckdb_vector column59 = duckdb_data_chunk_get_vector(dataChunk, 59);
		duckdb_vector column60 = duckdb_data_chunk_get_vector(dataChunk, 60);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		int64_t* dataColumn3 = (int64_t*)duckdb_vector_get_data(column3);
		double* dataColumn4 = (double*)duckdb_vector_get_data(column4);
		double* dataColumn5 = (double*)duckdb_vector_get_data(column5);
		double* dataColumn6 = (double*)duckdb_vector_get_data(column6);
		double* dataColumn7 = (double*)duckdb_vector_get_data(column7);
		double* dataColumn8 = (double*)duckdb_vector_get_data(column8);
		double* dataColumn9 = (double*)duckdb_vector_get_data(column9);
		double* dataColumn10 = (double*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		int64_t* dataColumn12 = (int64_t*)duckdb_vector_get_data(column12);
		int64_t* dataColumn13 = (int64_t*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		double* dataColumn16 = (double*)duckdb_vector_get_data(column16);
		double* dataColumn17 = (double*)duckdb_vector_get_data(column17);
		double* dataColumn18 = (double*)duckdb_vector_get_data(column18);
		double* dataColumn19 = (double*)duckdb_vector_get_data(column19);
		double* dataColumn20 = (double*)duckdb_vector_get_data(column20);
		double* dataColumn21 = (double*)duckdb_vector_get_data(column21);
		double* dataColumn22 = (double*)duckdb_vector_get_data(column22);
		double* dataColumn23 = (double*)duckdb_vector_get_data(column23);
		double* dataColumn24 = (double*)duckdb_vector_get_data(column24);
		double* dataColumn25 = (double*)duckdb_vector_get_data(column25);
		double* dataColumn26 = (double*)duckdb_vector_get_data(column26);
		double* dataColumn27 = (double*)duckdb_vector_get_data(column27);
		double* dataColumn28 = (double*)duckdb_vector_get_data(column28);
		double* dataColumn29 = (double*)duckdb_vector_get_data(column29);
		double* dataColumn30 = (double*)duckdb_vector_get_data(column30);
		int64_t* dataColumn31 = (int64_t*)duckdb_vector_get_data(column31);
		int64_t* dataColumn32 = (int64_t*)duckdb_vector_get_data(column32);
		int64_t* dataColumn33 = (int64_t*)duckdb_vector_get_data(column33);
		int64_t* dataColumn34 = (int64_t*)duckdb_vector_get_data(column34);
		int64_t* dataColumn35 = (int64_t*)duckdb_vector_get_data(column35);
		int64_t* dataColumn36 = (int64_t*)duckdb_vector_get_data(column36);
		int64_t* dataColumn37 = (int64_t*)duckdb_vector_get_data(column37);
		int64_t* dataColumn38 = (int64_t*)duckdb_vector_get_data(column38);
		int64_t* dataColumn39 = (int64_t*)duckdb_vector_get_data(column39);
		int64_t* dataColumn40 = (int64_t*)duckdb_vector_get_data(column40);
		double* dataColumn41 = (double*)duckdb_vector_get_data(column41);
		double* dataColumn42 = (double*)duckdb_vector_get_data(column42);
		double* dataColumn43 = (double*)duckdb_vector_get_data(column43);
		double* dataColumn44 = (double*)duckdb_vector_get_data(column44);
		double* dataColumn45 = (double*)duckdb_vector_get_data(column45);
		double* dataColumn46 = (double*)duckdb_vector_get_data(column46);
		double* dataColumn47 = (double*)duckdb_vector_get_data(column47);
		double* dataColumn48 = (double*)duckdb_vector_get_data(column48);
		double* dataColumn49 = (double*)duckdb_vector_get_data(column49);
		double* dataColumn50 = (double*)duckdb_vector_get_data(column50);
		int64_t* dataColumn51 = (int64_t*)duckdb_vector_get_data(column51);
		int64_t* dataColumn52 = (int64_t*)duckdb_vector_get_data(column52);
		int64_t* dataColumn53 = (int64_t*)duckdb_vector_get_data(column53);
		int64_t* dataColumn54 = (int64_t*)duckdb_vector_get_data(column54);
		int64_t* dataColumn55 = (int64_t*)duckdb_vector_get_data(column55);
		int64_t* dataColumn56 = (int64_t*)duckdb_vector_get_data(column56);
		int64_t* dataColumn57 = (int64_t*)duckdb_vector_get_data(column57);
		int64_t* dataColumn58 = (int64_t*)duckdb_vector_get_data(column58);
		int64_t* dataColumn59 = (int64_t*)duckdb_vector_get_data(column59);
		int64_t* dataColumn60 = (int64_t*)duckdb_vector_get_data(column60);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);
		uint64_t* validityColumn9 = duckdb_vector_get_validity(column9);
		uint64_t* validityColumn10 = duckdb_vector_get_validity(column10);
		uint64_t* validityColumn11 = duckdb_vector_get_validity(column11);
		uint64_t* validityColumn12 = duckdb_vector_get_validity(column12);
		uint64_t* validityColumn13 = duckdb_vector_get_validity(column13);
		uint64_t* validityColumn14 = duckdb_vector_get_validity(column14);
		uint64_t* validityColumn15 = duckdb_vector_get_validity(column15);
		uint64_t* validityColumn16 = duckdb_vector_get_validity(column16);
		uint64_t* validityColumn17 = duckdb_vector_get_validity(column17);
		uint64_t* validityColumn18 = duckdb_vector_get_validity(column18);
		uint64_t* validityColumn19 = duckdb_vector_get_validity(column19);
		uint64_t* validityColumn20 = duckdb_vector_get_validity(column20);
		uint64_t* validityColumn21 = duckdb_vector_get_validity(column21);
		uint64_t* validityColumn22 = duckdb_vector_get_validity(column22);
		uint64_t* validityColumn23 = duckdb_vector_get_validity(column23);
		uint64_t* validityColumn24 = duckdb_vector_get_validity(column24);
		uint64_t* validityColumn25 = duckdb_vector_get_validity(column25);
		uint64_t* validityColumn26 = duckdb_vector_get_validity(column26);
		uint64_t* validityColumn27 = duckdb_vector_get_validity(column27);
		uint64_t* validityColumn28 = duckdb_vector_get_validity(column28);
		uint64_t* validityColumn29 = duckdb_vector_get_validity(column29);
		uint64_t* validityColumn30 = duckdb_vector_get_validity(column30);
		uint64_t* validityColumn31 = duckdb_vector_get_validity(column31);
		uint64_t* validityColumn32 = duckdb_vector_get_validity(column32);
		uint64_t* validityColumn33 = duckdb_vector_get_validity(column33);
		uint64_t* validityColumn34 = duckdb_vector_get_validity(column34);
		uint64_t* validityColumn35 = duckdb_vector_get_validity(column35);
		uint64_t* validityColumn36 = duckdb_vector_get_validity(column36);
		uint64_t* validityColumn37 = duckdb_vector_get_validity(column37);
		uint64_t* validityColumn38 = duckdb_vector_get_validity(column38);
		uint64_t* validityColumn39 = duckdb_vector_get_validity(column39);
		uint64_t* validityColumn40 = duckdb_vector_get_validity(column40);
		uint64_t* validityColumn41 = duckdb_vector_get_validity(column41);
		uint64_t* validityColumn42 = duckdb_vector_get_validity(column42);
		uint64_t* validityColumn43 = duckdb_vector_get_validity(column43);
		uint64_t* validityColumn44 = duckdb_vector_get_validity(column44);
		uint64_t* validityColumn45 = duckdb_vector_get_validity(column45);
		uint64_t* validityColumn46 = duckdb_vector_get_validity(column46);
		uint64_t* validityColumn47 = duckdb_vector_get_validity(column47);
		uint64_t* validityColumn48 = duckdb_vector_get_validity(column48);
		uint64_t* validityColumn49 = duckdb_vector_get_validity(column49);
		uint64_t* validityColumn50 = duckdb_vector_get_validity(column50);
		uint64_t* validityColumn51 = duckdb_vector_get_validity(column51);
		uint64_t* validityColumn52 = duckdb_vector_get_validity(column52);
		uint64_t* validityColumn53 = duckdb_vector_get_validity(column53);
		uint64_t* validityColumn54 = duckdb_vector_get_validity(column54);
		uint64_t* validityColumn55 = duckdb_vector_get_validity(column55);
		uint64_t* validityColumn56 = duckdb_vector_get_validity(column56);
		uint64_t* validityColumn57 = duckdb_vector_get_validity(column57);
		uint64_t* validityColumn58 = duckdb_vector_get_validity(column58);
		uint64_t* validityColumn59 = duckdb_vector_get_validity(column59);
		uint64_t* validityColumn60 = duckdb_vector_get_validity(column60);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			DepthMarketData* record = DepthMarketData::Allocate();
			memset(record, 0, sizeof(DepthMarketData));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->UpdateTs = dataColumn3[row];
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->LastPrice = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->PreSettlementPrice = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->PreClosePrice = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->PreOpenInterest = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->OpenPrice = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->HighestPrice = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->LowestPrice = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->ClosePrice = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->CurrVolume = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->Volume = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->CurrTurnover = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->Turnover = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->OpenInterest = dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->SettlementPrice = dataColumn17[row];
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->UpperLimitPrice = dataColumn18[row];
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->LowerLimitPrice = dataColumn19[row];
			if (duckdb_validity_row_is_valid(validityColumn20, row)) record->AveragePrice = dataColumn20[row];
			if (duckdb_validity_row_is_valid(validityColumn21, row)) record->AskPrice1 = dataColumn21[row];
			if (duckdb_validity_row_is_valid(validityColumn22, row)) record->AskPrice2 = dataColumn22[row];
			if (duckdb_validity_row_is_valid(validityColumn23, row)) record->AskPrice3 = dataColumn23[row];
			if (duckdb_validity_row_is_valid(validityColumn24, row)) record->AskPrice4 = dataColumn24[row];
			if (duckdb_validity_row_is_valid(validityColumn25, row)) record->AskPrice5 = dataColumn25[row];
			if (duckdb_validity_row_is_valid(validityColumn26, row)) record->AskPrice6 = dataColumn26[row];
			if (duckdb_validity_row_is_valid(validityColumn27, row)) record->AskPrice7 = dataColumn27[row];
			if (duckdb_validity_row_is_valid(validityColumn28, row)) record->AskPrice8 = dataColumn28[row];
			if (duckdb_validity_row_is_valid(validityColumn29, row)) record->AskPrice9 = dataColumn29[row];
			if (duckdb_validity_row_is_valid(validityColumn30, row)) record->AskPrice10 = dataColumn30[row];
			if (duckdb_validity_row_is_valid(validityColumn31, row)) record->AskVolume1 = dataColumn31[row];
			if (duckdb_validity_row_is_valid(validityColumn32, row)) record->AskVolume2 = dataColumn32[row];
			if (duckdb_validity_row_is_valid(validityColumn33, row)) record->AskVolume3 = dataColumn33[row];
			if (duckdb_validity_row_is_valid(validityColumn34, row)) record->AskVolume4 = dataColumn34[row];
			if (duckdb_validity_row_is_valid(validityColumn35, row)) record->AskVolume5 = dataColumn35[row];
			if (duckdb_validity_row_is_valid(validityColumn36, row)) record->AskVolume6 = dataColumn36[row];
			if (duckdb_validity_row_is_valid(validityColumn37, row)) record->AskVolume7 = dataColumn37[row];
			if (duckdb_validity_row_is_valid(validityColumn38, row)) record->AskVolume8 = dataColumn38[row];
			if (duckdb_validity_row_is_valid(validityColumn39, row)) record->AskVolume9 = dataColumn39[row];
			if (duckdb_validity_row_is_valid(validityColumn40, row)) record->AskVolume10 = dataColumn40[row];
			if (duckdb_validity_row_is_valid(validityColumn41, row)) record->BidPrice1 = dataColumn41[row];
			if (duckdb_validity_row_is_valid(validityColumn42, row)) record->BidPrice2 = dataColumn42[row];
			if (duckdb_validity_row_is_valid(validityColumn43, row)) record->BidPrice3 = dataColumn43[row];
			if (duckdb_validity_row_is_valid(validityColumn44, row)) record->BidPrice4 = dataColumn44[row];
			if (duckdb_validity_row_is_valid(validityColumn45, row)) record->BidPrice5 = dataColumn45[row];
			if (duckdb_validity_row_is_valid(validityColumn46, row)) record->BidPrice6 = dataColumn46[row];
			if (duckdb_validity_row_is_valid(validityColumn47, row)) record->BidPrice7 = dataColumn47[row];
			if (duckdb_validity_row_is_valid(validityColumn48, row)) record->BidPrice8 = dataColumn48[row];
			if (duckdb_validity_row_is_valid(validityColumn49, row)) record->BidPrice9 = dataColumn49[row];
			if (duckdb_validity_row_is_valid(validityColumn50, row)) record->BidPrice10 = dataColumn50[row];
			if (duckdb_validity_row_is_valid(validityColumn51, row)) record->BidVolume1 = dataColumn51[row];
			if (duckdb_validity_row_is_valid(validityColumn52, row)) record->BidVolume2 = dataColumn52[row];
			if (duckdb_validity_row_is_valid(validityColumn53, row)) record->BidVolume3 = dataColumn53[row];
			if (duckdb_validity_row_is_valid(validityColumn54, row)) record->BidVolume4 = dataColumn54[row];
			if (duckdb_validity_row_is_valid(validityColumn55, row)) record->BidVolume5 = dataColumn55[row];
			if (duckdb_validity_row_is_valid(validityColumn56, row)) record->BidVolume6 = dataColumn56[row];
			if (duckdb_validity_row_is_valid(validityColumn57, row)) record->BidVolume7 = dataColumn57[row];
			if (duckdb_validity_row_is_valid(validityColumn58, row)) record->BidVolume8 = dataColumn58[row];
			if (duckdb_validity_row_is_valid(validityColumn59, row)) record->BidVolume9 = dataColumn59[row];
			if (duckdb_validity_row_is_valid(validityColumn60, row)) record->BidVolume10 = dataColumn60[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreateBarMarketData()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_BarMarketData (TradingDay varchar, ExchangeID varchar, InstrumentID varchar, BarPreces int, BarPeriod int, BarTime bigint, UpdateTs bigint, PreSettlementPrice double, PreClosePrice double, Open double, High double, Low double, Close double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateBarMarketData failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateBarMarketData Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropBarMarketData()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_BarMarketData;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropBarMarketData failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropBarMarketData Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertBarMarketData(BarMarketData* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_BarMarketData", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_BarMarketData Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForBarMarketDataRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertBarMarketData(std::list<BarMarketData*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_BarMarketData", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_BarMarketData Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForBarMarketDataRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertBarMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_BarMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;", &m_BarMarketDataDeleteStatement);
	}
	SetStatementForBarMarketDataPrimaryKey(m_BarMarketDataDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_BarMarketDataDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteBarMarketData Spend:%lldms", duration);
	}
}
void DuckDB::UpdateBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_BarMarketData set UpdateTs = ?, PreSettlementPrice = ?, PreClosePrice = ?, Open = ?, High = ?, Low = ?, Close = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;", &m_BarMarketDataUpdateStatement);
	}
	SetStatementForBarMarketDataRecordUpdate(m_BarMarketDataUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_BarMarketDataUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateBarMarketData Spend:%lldms", duration);
	}
}
void DuckDB::SelectBarMarketData(std::list<BarMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_BarMarketData where TradingDay >= ?;", &m_BarMarketDataSelectStatement);
	}
	duckdb_bind_varchar(m_BarMarketDataSelectStatement, 1, tradingDay);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_BarMarketDataSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectBarMarketData ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectBarMarketData Spend:%lldms", duration);
	}
}
void DuckDB::TruncateBarMarketData()
{
	auto start = steady_clock::now();
	if (m_BarMarketDataTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_BarMarketData;", &m_BarMarketDataTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_BarMarketDataTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateBarMarketData failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateBarMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<BarMarketData*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);
		duckdb_vector column7 = duckdb_data_chunk_get_vector(dataChunk, 7);
		duckdb_vector column8 = duckdb_data_chunk_get_vector(dataChunk, 8);
		duckdb_vector column9 = duckdb_data_chunk_get_vector(dataChunk, 9);
		duckdb_vector column10 = duckdb_data_chunk_get_vector(dataChunk, 10);
		duckdb_vector column11 = duckdb_data_chunk_get_vector(dataChunk, 11);
		duckdb_vector column12 = duckdb_data_chunk_get_vector(dataChunk, 12);
		duckdb_vector column13 = duckdb_data_chunk_get_vector(dataChunk, 13);
		duckdb_vector column14 = duckdb_data_chunk_get_vector(dataChunk, 14);
		duckdb_vector column15 = duckdb_data_chunk_get_vector(dataChunk, 15);
		duckdb_vector column16 = duckdb_data_chunk_get_vector(dataChunk, 16);
		duckdb_vector column17 = duckdb_data_chunk_get_vector(dataChunk, 17);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		int* dataColumn3 = (int*)duckdb_vector_get_data(column3);
		int* dataColumn4 = (int*)duckdb_vector_get_data(column4);
		int64_t* dataColumn5 = (int64_t*)duckdb_vector_get_data(column5);
		int64_t* dataColumn6 = (int64_t*)duckdb_vector_get_data(column6);
		double* dataColumn7 = (double*)duckdb_vector_get_data(column7);
		double* dataColumn8 = (double*)duckdb_vector_get_data(column8);
		double* dataColumn9 = (double*)duckdb_vector_get_data(column9);
		double* dataColumn10 = (double*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		double* dataColumn12 = (double*)duckdb_vector_get_data(column12);
		int64_t* dataColumn13 = (int64_t*)duckdb_vector_get_data(column13);
		int64_t* dataColumn14 = (int64_t*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		double* dataColumn16 = (double*)duckdb_vector_get_data(column16);
		double* dataColumn17 = (double*)duckdb_vector_get_data(column17);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);
		uint64_t* validityColumn9 = duckdb_vector_get_validity(column9);
		uint64_t* validityColumn10 = duckdb_vector_get_validity(column10);
		uint64_t* validityColumn11 = duckdb_vector_get_validity(column11);
		uint64_t* validityColumn12 = duckdb_vector_get_validity(column12);
		uint64_t* validityColumn13 = duckdb_vector_get_validity(column13);
		uint64_t* validityColumn14 = duckdb_vector_get_validity(column14);
		uint64_t* validityColumn15 = duckdb_vector_get_validity(column15);
		uint64_t* validityColumn16 = duckdb_vector_get_validity(column16);
		uint64_t* validityColumn17 = duckdb_vector_get_validity(column17);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			BarMarketData* record = BarMarketData::Allocate();
			memset(record, 0, sizeof(BarMarketData));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->BarPreces = BarPrecesType(dataColumn3[row]);
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->BarPeriod = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->BarTime = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->UpdateTs = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->PreSettlementPrice = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->PreClosePrice = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->Open = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->High = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->Low = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->Close = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->CurrVolume = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->Volume = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->CurrTurnover = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->Turnover = dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->OpenInterest = dataColumn17[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreateMdSubscribe()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdSubscribe (ExchangeID varchar, InstrumentID varchar, RealInstrumentID varchar, ProductID varchar, ProductClass int, StartTradingDay varchar, EndTradingDay varchar, PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateMdSubscribe failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdSubscribe Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropMdSubscribe()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_MdSubscribe;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropMdSubscribe failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdSubscribe Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertMdSubscribe(MdSubscribe* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdSubscribe", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdSubscribe Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForMdSubscribeRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertMdSubscribe(std::list<MdSubscribe*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdSubscribe", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdSubscribe Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForMdSubscribeRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertMdSubscribe RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdSubscribe where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;", &m_MdSubscribeDeleteStatement);
	}
	SetStatementForMdSubscribePrimaryKey(m_MdSubscribeDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdSubscribeDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdSubscribe Spend:%lldms", duration);
	}
}
void DuckDB::UpdateMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_MdSubscribe set RealInstrumentID = ?, ProductID = ?, ProductClass = ?, EndTradingDay = ? where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;", &m_MdSubscribeUpdateStatement);
	}
	SetStatementForMdSubscribeRecordUpdate(m_MdSubscribeUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdSubscribeUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdSubscribe Spend:%lldms", duration);
	}
}
void DuckDB::SelectMdSubscribe(std::list<MdSubscribe*>& records)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_MdSubscribe;", &m_MdSubscribeSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdSubscribeSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectMdSubscribe ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdSubscribe Spend:%lldms", duration);
	}
}
void DuckDB::TruncateMdSubscribe()
{
	auto start = steady_clock::now();
	if (m_MdSubscribeTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdSubscribe;", &m_MdSubscribeTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_MdSubscribeTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateMdSubscribe failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateMdSubscribe Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<MdSubscribe*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		int* dataColumn4 = (int*)duckdb_vector_get_data(column4);
		duckdb_string_t* dataColumn5 = (duckdb_string_t*)duckdb_vector_get_data(column5);
		duckdb_string_t* dataColumn6 = (duckdb_string_t*)duckdb_vector_get_data(column6);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			MdSubscribe* record = MdSubscribe::Allocate();
			memset(record, 0, sizeof(MdSubscribe));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->RealInstrumentID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->ProductID, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->ProductClass = ProductClassType(dataColumn4[row]);
			if (duckdb_validity_row_is_valid(validityColumn5, row))
			{
				CpyDuckdbString(record->StartTradingDay, dataColumn5[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn6, row))
			{
				CpyDuckdbString(record->EndTradingDay, dataColumn6[row]);
			}
			records.push_back(record);
		}
	}
}
void DuckDB::CreateMdUser()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdUser (MdUserID varchar, MdUserName varchar, Password varchar, PRIMARY KEY(MdUserID));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateMdUser failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUser Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropMdUser()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_MdUser;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropMdUser failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUser Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertMdUser(MdUser* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdUser", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdUser Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForMdUserRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertMdUser(std::list<MdUser*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdUser", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdUser Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForMdUserRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertMdUser RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdUser where MdUserID = ?;", &m_MdUserDeleteStatement);
	}
	SetStatementForMdUserPrimaryKey(m_MdUserDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUser Spend:%lldms", duration);
	}
}
void DuckDB::UpdateMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_MdUser set MdUserName = ?, Password = ? where MdUserID = ?;", &m_MdUserUpdateStatement);
	}
	SetStatementForMdUserRecordUpdate(m_MdUserUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUser Spend:%lldms", duration);
	}
}
void DuckDB::SelectMdUser(std::list<MdUser*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_MdUser;", &m_MdUserSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectMdUser ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUser Spend:%lldms", duration);
	}
}
void DuckDB::TruncateMdUser()
{
	auto start = steady_clock::now();
	if (m_MdUserTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdUser;", &m_MdUserTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_MdUserTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateMdUser failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateMdUser Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<MdUser*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			MdUser* record = MdUser::Allocate();
			memset(record, 0, sizeof(MdUser));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->MdUserID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->MdUserName, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->Password, dataColumn2[row]);
			}
			records.push_back(record);
		}
	}
}
void DuckDB::CreateMdUserLoginSession()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdUserLoginSession (MdUserID varchar, SessionID bigint, IPAddress varchar, PRIMARY KEY(SessionID));CREATE INDEX IF NOT EXISTS MdUserLoginSessionMdUserID ON t_MdUserLoginSession(MdUserID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateMdUserLoginSession failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUserLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropMdUserLoginSession()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX MdUserLoginSessionMdUserID;DROP TABLE IF EXISTS t_MdUserLoginSession;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropMdUserLoginSession failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUserLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertMdUserLoginSession(MdUserLoginSession* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdUserLoginSession", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdUserLoginSession Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForMdUserLoginSessionRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertMdUserLoginSession(std::list<MdUserLoginSession*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_MdUserLoginSession", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_MdUserLoginSession Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForMdUserLoginSessionRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertMdUserLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdUserLoginSession where SessionID = ?;", &m_MdUserLoginSessionDeleteStatement);
	}
	SetStatementForMdUserLoginSessionPrimaryKey(m_MdUserLoginSessionDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserLoginSessionDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::DeleteMdUserLoginSessionByMdUserIDIndex(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdUserLoginSession where MdUserID = ?;", &m_MdUserLoginSessionDeleteByMdUserIDIndexStatement);
	}
	SetStatementForMdUserLoginSessionIndexMdUserID(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSessionByMdUserIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSessionByMdUserIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_MdUserLoginSession set MdUserID = ?, IPAddress = ? where SessionID = ?;", &m_MdUserLoginSessionUpdateStatement);
	}
	SetStatementForMdUserLoginSessionRecordUpdate(m_MdUserLoginSessionUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserLoginSessionUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUserLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::SelectMdUserLoginSession(std::list<MdUserLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_MdUserLoginSession;", &m_MdUserLoginSessionSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_MdUserLoginSessionSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectMdUserLoginSession ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUserLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::TruncateMdUserLoginSession()
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_MdUserLoginSession;", &m_MdUserLoginSessionTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_MdUserLoginSessionTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateMdUserLoginSession failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateMdUserLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<MdUserLoginSession*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		int64_t* dataColumn1 = (int64_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			MdUserLoginSession* record = MdUserLoginSession::Allocate();
			memset(record, 0, sizeof(MdUserLoginSession));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->MdUserID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row)) record->SessionID = dataColumn1[row];
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->IPAddress, dataColumn2[row]);
			}
			records.push_back(record);
		}
	}
}


bool DuckDB::AppendForExchangeRecord(duckdb_appender appender, Exchange* record)
{
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->ExchangeName);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForExchangeRecord(duckdb_prepared_statement statement, Exchange* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->ExchangeName);
}
void DuckDB::SetStatementForExchangeRecordUpdate(duckdb_prepared_statement statement, Exchange* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeName);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
}
void DuckDB::SetStatementForExchangePrimaryKey(duckdb_prepared_statement statement, Exchange* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
}
bool DuckDB::AppendForInstrumentRecord(duckdb_appender appender, Instrument* record)
{
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_varchar(appender, record->ExchangeInstID);
	duckdb_append_varchar(appender, record->InstrumentName);
	duckdb_append_varchar(appender, record->ProductID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, int(record->InstrumentClass));
	duckdb_append_int32(appender, record->Rank);
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_double(appender, record->PriceTick);
	duckdb_append_int64(appender, record->MaxMarketOrderVolume);
	duckdb_append_int64(appender, record->MinMarketOrderVolume);
	duckdb_append_int64(appender, record->MaxLimitOrderVolume);
	duckdb_append_int64(appender, record->MinLimitOrderVolume);
	duckdb_append_varchar(appender, record->SessionName);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForInstrumentRecord(duckdb_prepared_statement statement, Instrument* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->InstrumentID);
	duckdb_bind_varchar(statement, 3, record->ExchangeInstID);
	duckdb_bind_varchar(statement, 4, record->InstrumentName);
	duckdb_bind_varchar(statement, 5, record->ProductID);
	duckdb_bind_int32(statement, 6, int(record->ProductClass));
	duckdb_bind_int32(statement, 7, int(record->InstrumentClass));
	duckdb_bind_int32(statement, 8, record->Rank);
	duckdb_bind_int32(statement, 9, record->VolumeMultiple);
	duckdb_bind_double(statement, 10, record->PriceTick);
	duckdb_bind_int64(statement, 11, record->MaxMarketOrderVolume);
	duckdb_bind_int64(statement, 12, record->MinMarketOrderVolume);
	duckdb_bind_int64(statement, 13, record->MaxLimitOrderVolume);
	duckdb_bind_int64(statement, 14, record->MinLimitOrderVolume);
	duckdb_bind_varchar(statement, 15, record->SessionName);
}
void DuckDB::SetStatementForInstrumentRecordUpdate(duckdb_prepared_statement statement, Instrument* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeInstID);
	duckdb_bind_varchar(statement, 2, record->InstrumentName);
	duckdb_bind_varchar(statement, 3, record->ProductID);
	duckdb_bind_int32(statement, 4, int(record->ProductClass));
	duckdb_bind_int32(statement, 5, int(record->InstrumentClass));
	duckdb_bind_int32(statement, 6, record->Rank);
	duckdb_bind_int32(statement, 7, record->VolumeMultiple);
	duckdb_bind_double(statement, 8, record->PriceTick);
	duckdb_bind_int64(statement, 9, record->MaxMarketOrderVolume);
	duckdb_bind_int64(statement, 10, record->MinMarketOrderVolume);
	duckdb_bind_int64(statement, 11, record->MaxLimitOrderVolume);
	duckdb_bind_int64(statement, 12, record->MinLimitOrderVolume);
	duckdb_bind_varchar(statement, 13, record->SessionName);
	duckdb_bind_varchar(statement, 14, record->ExchangeID);
	duckdb_bind_varchar(statement, 15, record->InstrumentID);
}
void DuckDB::SetStatementForInstrumentPrimaryKey(duckdb_prepared_statement statement, Instrument* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->InstrumentID);
}
void DuckDB::SetStatementForInstrumentIndexExchangeID(duckdb_prepared_statement statement, Instrument* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
}
bool DuckDB::AppendForDepthMarketDataRecord(duckdb_appender appender, DepthMarketData* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int64(appender, record->UpdateTs);
	duckdb_append_double(appender, record->LastPrice);
	duckdb_append_double(appender, record->PreSettlementPrice);
	duckdb_append_double(appender, record->PreClosePrice);
	duckdb_append_double(appender, record->PreOpenInterest);
	duckdb_append_double(appender, record->OpenPrice);
	duckdb_append_double(appender, record->HighestPrice);
	duckdb_append_double(appender, record->LowestPrice);
	duckdb_append_double(appender, record->ClosePrice);
	duckdb_append_int64(appender, record->CurrVolume);
	duckdb_append_int64(appender, record->Volume);
	duckdb_append_double(appender, record->CurrTurnover);
	duckdb_append_double(appender, record->Turnover);
	duckdb_append_double(appender, record->OpenInterest);
	duckdb_append_double(appender, record->SettlementPrice);
	duckdb_append_double(appender, record->UpperLimitPrice);
	duckdb_append_double(appender, record->LowerLimitPrice);
	duckdb_append_double(appender, record->AveragePrice);
	duckdb_append_double(appender, record->AskPrice1);
	duckdb_append_double(appender, record->AskPrice2);
	duckdb_append_double(appender, record->AskPrice3);
	duckdb_append_double(appender, record->AskPrice4);
	duckdb_append_double(appender, record->AskPrice5);
	duckdb_append_double(appender, record->AskPrice6);
	duckdb_append_double(appender, record->AskPrice7);
	duckdb_append_double(appender, record->AskPrice8);
	duckdb_append_double(appender, record->AskPrice9);
	duckdb_append_double(appender, record->AskPrice10);
	duckdb_append_int64(appender, record->AskVolume1);
	duckdb_append_int64(appender, record->AskVolume2);
	duckdb_append_int64(appender, record->AskVolume3);
	duckdb_append_int64(appender, record->AskVolume4);
	duckdb_append_int64(appender, record->AskVolume5);
	duckdb_append_int64(appender, record->AskVolume6);
	duckdb_append_int64(appender, record->AskVolume7);
	duckdb_append_int64(appender, record->AskVolume8);
	duckdb_append_int64(appender, record->AskVolume9);
	duckdb_append_int64(appender, record->AskVolume10);
	duckdb_append_double(appender, record->BidPrice1);
	duckdb_append_double(appender, record->BidPrice2);
	duckdb_append_double(appender, record->BidPrice3);
	duckdb_append_double(appender, record->BidPrice4);
	duckdb_append_double(appender, record->BidPrice5);
	duckdb_append_double(appender, record->BidPrice6);
	duckdb_append_double(appender, record->BidPrice7);
	duckdb_append_double(appender, record->BidPrice8);
	duckdb_append_double(appender, record->BidPrice9);
	duckdb_append_double(appender, record->BidPrice10);
	duckdb_append_int64(appender, record->BidVolume1);
	duckdb_append_int64(appender, record->BidVolume2);
	duckdb_append_int64(appender, record->BidVolume3);
	duckdb_append_int64(appender, record->BidVolume4);
	duckdb_append_int64(appender, record->BidVolume5);
	duckdb_append_int64(appender, record->BidVolume6);
	duckdb_append_int64(appender, record->BidVolume7);
	duckdb_append_int64(appender, record->BidVolume8);
	duckdb_append_int64(appender, record->BidVolume9);
	duckdb_append_int64(appender, record->BidVolume10);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForDepthMarketDataRecord(duckdb_prepared_statement statement, DepthMarketData* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
	duckdb_bind_varchar(statement, 3, record->InstrumentID);
	duckdb_bind_int64(statement, 4, record->UpdateTs);
	duckdb_bind_double(statement, 5, record->LastPrice);
	duckdb_bind_double(statement, 6, record->PreSettlementPrice);
	duckdb_bind_double(statement, 7, record->PreClosePrice);
	duckdb_bind_double(statement, 8, record->PreOpenInterest);
	duckdb_bind_double(statement, 9, record->OpenPrice);
	duckdb_bind_double(statement, 10, record->HighestPrice);
	duckdb_bind_double(statement, 11, record->LowestPrice);
	duckdb_bind_double(statement, 12, record->ClosePrice);
	duckdb_bind_int64(statement, 13, record->CurrVolume);
	duckdb_bind_int64(statement, 14, record->Volume);
	duckdb_bind_double(statement, 15, record->CurrTurnover);
	duckdb_bind_double(statement, 16, record->Turnover);
	duckdb_bind_double(statement, 17, record->OpenInterest);
	duckdb_bind_double(statement, 18, record->SettlementPrice);
	duckdb_bind_double(statement, 19, record->UpperLimitPrice);
	duckdb_bind_double(statement, 20, record->LowerLimitPrice);
	duckdb_bind_double(statement, 21, record->AveragePrice);
	duckdb_bind_double(statement, 22, record->AskPrice1);
	duckdb_bind_double(statement, 23, record->AskPrice2);
	duckdb_bind_double(statement, 24, record->AskPrice3);
	duckdb_bind_double(statement, 25, record->AskPrice4);
	duckdb_bind_double(statement, 26, record->AskPrice5);
	duckdb_bind_double(statement, 27, record->AskPrice6);
	duckdb_bind_double(statement, 28, record->AskPrice7);
	duckdb_bind_double(statement, 29, record->AskPrice8);
	duckdb_bind_double(statement, 30, record->AskPrice9);
	duckdb_bind_double(statement, 31, record->AskPrice10);
	duckdb_bind_int64(statement, 32, record->AskVolume1);
	duckdb_bind_int64(statement, 33, record->AskVolume2);
	duckdb_bind_int64(statement, 34, record->AskVolume3);
	duckdb_bind_int64(statement, 35, record->AskVolume4);
	duckdb_bind_int64(statement, 36, record->AskVolume5);
	duckdb_bind_int64(statement, 37, record->AskVolume6);
	duckdb_bind_int64(statement, 38, record->AskVolume7);
	duckdb_bind_int64(statement, 39, record->AskVolume8);
	duckdb_bind_int64(statement, 40, record->AskVolume9);
	duckdb_bind_int64(statement, 41, record->AskVolume10);
	duckdb_bind_double(statement, 42, record->BidPrice1);
	duckdb_bind_double(statement, 43, record->BidPrice2);
	duckdb_bind_double(statement, 44, record->BidPrice3);
	duckdb_bind_double(statement, 45, record->BidPrice4);
	duckdb_bind_double(statement, 46, record->BidPrice5);
	duckdb_bind_double(statement, 47, record->BidPrice6);
	duckdb_bind_double(statement, 48, record->BidPrice7);
	duckdb_bind_double(statement, 49, record->BidPrice8);
	duckdb_bind_double(statement, 50, record->BidPrice9);
	duckdb_bind_double(statement, 51, record->BidPrice10);
	duckdb_bind_int64(statement, 52, record->BidVolume1);
	duckdb_bind_int64(statement, 53, record->BidVolume2);
	duckdb_bind_int64(statement, 54, record->BidVolume3);
	duckdb_bind_int64(statement, 55, record->BidVolume4);
	duckdb_bind_int64(statement, 56, record->BidVolume5);
	duckdb_bind_int64(statement, 57, record->BidVolume6);
	duckdb_bind_int64(statement, 58, record->BidVolume7);
	duckdb_bind_int64(statement, 59, record->BidVolume8);
	duckdb_bind_int64(statement, 60, record->BidVolume9);
	duckdb_bind_int64(statement, 61, record->BidVolume10);
}
void DuckDB::SetStatementForDepthMarketDataRecordUpdate(duckdb_prepared_statement statement, DepthMarketData* record)
{
	duckdb_bind_int64(statement, 1, record->UpdateTs);
	duckdb_bind_double(statement, 2, record->LastPrice);
	duckdb_bind_double(statement, 3, record->PreSettlementPrice);
	duckdb_bind_double(statement, 4, record->PreClosePrice);
	duckdb_bind_double(statement, 5, record->PreOpenInterest);
	duckdb_bind_double(statement, 6, record->OpenPrice);
	duckdb_bind_double(statement, 7, record->HighestPrice);
	duckdb_bind_double(statement, 8, record->LowestPrice);
	duckdb_bind_double(statement, 9, record->ClosePrice);
	duckdb_bind_int64(statement, 10, record->CurrVolume);
	duckdb_bind_int64(statement, 11, record->Volume);
	duckdb_bind_double(statement, 12, record->CurrTurnover);
	duckdb_bind_double(statement, 13, record->Turnover);
	duckdb_bind_double(statement, 14, record->OpenInterest);
	duckdb_bind_double(statement, 15, record->SettlementPrice);
	duckdb_bind_double(statement, 16, record->UpperLimitPrice);
	duckdb_bind_double(statement, 17, record->LowerLimitPrice);
	duckdb_bind_double(statement, 18, record->AveragePrice);
	duckdb_bind_double(statement, 19, record->AskPrice1);
	duckdb_bind_double(statement, 20, record->AskPrice2);
	duckdb_bind_double(statement, 21, record->AskPrice3);
	duckdb_bind_double(statement, 22, record->AskPrice4);
	duckdb_bind_double(statement, 23, record->AskPrice5);
	duckdb_bind_double(statement, 24, record->AskPrice6);
	duckdb_bind_double(statement, 25, record->AskPrice7);
	duckdb_bind_double(statement, 26, record->AskPrice8);
	duckdb_bind_double(statement, 27, record->AskPrice9);
	duckdb_bind_double(statement, 28, record->AskPrice10);
	duckdb_bind_int64(statement, 29, record->AskVolume1);
	duckdb_bind_int64(statement, 30, record->AskVolume2);
	duckdb_bind_int64(statement, 31, record->AskVolume3);
	duckdb_bind_int64(statement, 32, record->AskVolume4);
	duckdb_bind_int64(statement, 33, record->AskVolume5);
	duckdb_bind_int64(statement, 34, record->AskVolume6);
	duckdb_bind_int64(statement, 35, record->AskVolume7);
	duckdb_bind_int64(statement, 36, record->AskVolume8);
	duckdb_bind_int64(statement, 37, record->AskVolume9);
	duckdb_bind_int64(statement, 38, record->AskVolume10);
	duckdb_bind_double(statement, 39, record->BidPrice1);
	duckdb_bind_double(statement, 40, record->BidPrice2);
	duckdb_bind_double(statement, 41, record->BidPrice3);
	duckdb_bind_double(statement, 42, record->BidPrice4);
	duckdb_bind_double(statement, 43, record->BidPrice5);
	duckdb_bind_double(statement, 44, record->BidPrice6);
	duckdb_bind_double(statement, 45, record->BidPrice7);
	duckdb_bind_double(statement, 46, record->BidPrice8);
	duckdb_bind_double(statement, 47, record->BidPrice9);
	duckdb_bind_double(statement, 48, record->BidPrice10);
	duckdb_bind_int64(statement, 49, record->BidVolume1);
	duckdb_bind_int64(statement, 50, record->BidVolume2);
	duckdb_bind_int64(statement, 51, record->BidVolume3);
	duckdb_bind_int64(statement, 52, record->BidVolume4);
	duckdb_bind_int64(statement, 53, record->BidVolume5);
	duckdb_bind_int64(statement, 54, record->BidVolume6);
	duckdb_bind_int64(statement, 55, record->BidVolume7);
	duckdb_bind_int64(statement, 56, record->BidVolume8);
	duckdb_bind_int64(statement, 57, record->BidVolume9);
	duckdb_bind_int64(statement, 58, record->BidVolume10);
	duckdb_bind_varchar(statement, 59, record->TradingDay);
	duckdb_bind_varchar(statement, 60, record->ExchangeID);
	duckdb_bind_varchar(statement, 61, record->InstrumentID);
}
void DuckDB::SetStatementForDepthMarketDataPrimaryKey(duckdb_prepared_statement statement, DepthMarketData* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
	duckdb_bind_varchar(statement, 3, record->InstrumentID);
}
bool DuckDB::AppendForBarMarketDataRecord(duckdb_appender appender, BarMarketData* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int32(appender, int(record->BarPreces));
	duckdb_append_int32(appender, record->BarPeriod);
	duckdb_append_int64(appender, record->BarTime);
	duckdb_append_int64(appender, record->UpdateTs);
	duckdb_append_double(appender, record->PreSettlementPrice);
	duckdb_append_double(appender, record->PreClosePrice);
	duckdb_append_double(appender, record->Open);
	duckdb_append_double(appender, record->High);
	duckdb_append_double(appender, record->Low);
	duckdb_append_double(appender, record->Close);
	duckdb_append_int64(appender, record->CurrVolume);
	duckdb_append_int64(appender, record->Volume);
	duckdb_append_double(appender, record->CurrTurnover);
	duckdb_append_double(appender, record->Turnover);
	duckdb_append_double(appender, record->OpenInterest);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForBarMarketDataRecord(duckdb_prepared_statement statement, BarMarketData* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
	duckdb_bind_varchar(statement, 3, record->InstrumentID);
	duckdb_bind_int32(statement, 4, int(record->BarPreces));
	duckdb_bind_int32(statement, 5, record->BarPeriod);
	duckdb_bind_int64(statement, 6, record->BarTime);
	duckdb_bind_int64(statement, 7, record->UpdateTs);
	duckdb_bind_double(statement, 8, record->PreSettlementPrice);
	duckdb_bind_double(statement, 9, record->PreClosePrice);
	duckdb_bind_double(statement, 10, record->Open);
	duckdb_bind_double(statement, 11, record->High);
	duckdb_bind_double(statement, 12, record->Low);
	duckdb_bind_double(statement, 13, record->Close);
	duckdb_bind_int64(statement, 14, record->CurrVolume);
	duckdb_bind_int64(statement, 15, record->Volume);
	duckdb_bind_double(statement, 16, record->CurrTurnover);
	duckdb_bind_double(statement, 17, record->Turnover);
	duckdb_bind_double(statement, 18, record->OpenInterest);
}
void DuckDB::SetStatementForBarMarketDataRecordUpdate(duckdb_prepared_statement statement, BarMarketData* record)
{
	duckdb_bind_int64(statement, 1, record->UpdateTs);
	duckdb_bind_double(statement, 2, record->PreSettlementPrice);
	duckdb_bind_double(statement, 3, record->PreClosePrice);
	duckdb_bind_double(statement, 4, record->Open);
	duckdb_bind_double(statement, 5, record->High);
	duckdb_bind_double(statement, 6, record->Low);
	duckdb_bind_double(statement, 7, record->Close);
	duckdb_bind_int64(statement, 8, record->CurrVolume);
	duckdb_bind_int64(statement, 9, record->Volume);
	duckdb_bind_double(statement, 10, record->CurrTurnover);
	duckdb_bind_double(statement, 11, record->Turnover);
	duckdb_bind_double(statement, 12, record->OpenInterest);
	duckdb_bind_varchar(statement, 13, record->TradingDay);
	duckdb_bind_varchar(statement, 14, record->ExchangeID);
	duckdb_bind_varchar(statement, 15, record->InstrumentID);
	duckdb_bind_int32(statement, 16, int(record->BarPreces));
	duckdb_bind_int32(statement, 17, record->BarPeriod);
	duckdb_bind_int64(statement, 18, record->BarTime);
}
void DuckDB::SetStatementForBarMarketDataPrimaryKey(duckdb_prepared_statement statement, BarMarketData* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
	duckdb_bind_varchar(statement, 3, record->InstrumentID);
	duckdb_bind_int32(statement, 4, int(record->BarPreces));
	duckdb_bind_int32(statement, 5, record->BarPeriod);
	duckdb_bind_int64(statement, 6, record->BarTime);
}
bool DuckDB::AppendForMdSubscribeRecord(duckdb_appender appender, MdSubscribe* record)
{
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_varchar(appender, record->RealInstrumentID);
	duckdb_append_varchar(appender, record->ProductID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_varchar(appender, record->StartTradingDay);
	duckdb_append_varchar(appender, record->EndTradingDay);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForMdSubscribeRecord(duckdb_prepared_statement statement, MdSubscribe* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->InstrumentID);
	duckdb_bind_varchar(statement, 3, record->RealInstrumentID);
	duckdb_bind_varchar(statement, 4, record->ProductID);
	duckdb_bind_int32(statement, 5, int(record->ProductClass));
	duckdb_bind_varchar(statement, 6, record->StartTradingDay);
	duckdb_bind_varchar(statement, 7, record->EndTradingDay);
}
void DuckDB::SetStatementForMdSubscribeRecordUpdate(duckdb_prepared_statement statement, MdSubscribe* record)
{
	duckdb_bind_varchar(statement, 1, record->RealInstrumentID);
	duckdb_bind_varchar(statement, 2, record->ProductID);
	duckdb_bind_int32(statement, 3, int(record->ProductClass));
	duckdb_bind_varchar(statement, 4, record->EndTradingDay);
	duckdb_bind_varchar(statement, 5, record->ExchangeID);
	duckdb_bind_varchar(statement, 6, record->InstrumentID);
	duckdb_bind_varchar(statement, 7, record->StartTradingDay);
}
void DuckDB::SetStatementForMdSubscribePrimaryKey(duckdb_prepared_statement statement, MdSubscribe* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->InstrumentID);
	duckdb_bind_varchar(statement, 3, record->StartTradingDay);
}
bool DuckDB::AppendForMdUserRecord(duckdb_appender appender, MdUser* record)
{
	duckdb_append_varchar(appender, record->MdUserID);
	duckdb_append_varchar(appender, record->MdUserName);
	duckdb_append_varchar(appender, record->Password);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForMdUserRecord(duckdb_prepared_statement statement, MdUser* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserID);
	duckdb_bind_varchar(statement, 2, record->MdUserName);
	duckdb_bind_varchar(statement, 3, record->Password);
}
void DuckDB::SetStatementForMdUserRecordUpdate(duckdb_prepared_statement statement, MdUser* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserName);
	duckdb_bind_varchar(statement, 2, record->Password);
	duckdb_bind_varchar(statement, 3, record->MdUserID);
}
void DuckDB::SetStatementForMdUserPrimaryKey(duckdb_prepared_statement statement, MdUser* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserID);
}
bool DuckDB::AppendForMdUserLoginSessionRecord(duckdb_appender appender, MdUserLoginSession* record)
{
	duckdb_append_varchar(appender, record->MdUserID);
	duckdb_append_int64(appender, record->SessionID);
	duckdb_append_varchar(appender, record->IPAddress);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForMdUserLoginSessionRecord(duckdb_prepared_statement statement, MdUserLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserID);
	duckdb_bind_int64(statement, 2, record->SessionID);
	duckdb_bind_varchar(statement, 3, record->IPAddress);
}
void DuckDB::SetStatementForMdUserLoginSessionRecordUpdate(duckdb_prepared_statement statement, MdUserLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserID);
	duckdb_bind_varchar(statement, 2, record->IPAddress);
	duckdb_bind_int64(statement, 3, record->SessionID);
}
void DuckDB::SetStatementForMdUserLoginSessionPrimaryKey(duckdb_prepared_statement statement, MdUserLoginSession* record)
{
	duckdb_bind_int64(statement, 1, record->SessionID);
}
void DuckDB::SetStatementForMdUserLoginSessionIndexMdUserID(duckdb_prepared_statement statement, MdUserLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->MdUserID);
}

