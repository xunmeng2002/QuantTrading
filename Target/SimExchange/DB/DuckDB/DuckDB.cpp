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

	m_TradingDayDeleteStatement = nullptr;
	m_TradingDayUpdateStatement = nullptr;
	m_TradingDaySelectStatement = nullptr;
	m_TradingDayTruncateStatement = nullptr;

	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_ProductDeleteStatement = nullptr;
	m_ProductUpdateStatement = nullptr;
	m_ProductSelectStatement = nullptr;
	m_ProductTruncateStatement = nullptr;

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

	m_PrimaryAccountDeleteStatement = nullptr;
	m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	m_PrimaryAccountUpdateStatement = nullptr;
	m_PrimaryAccountSelectStatement = nullptr;
	m_PrimaryAccountTruncateStatement = nullptr;

	m_AccountDeleteStatement = nullptr;
	m_AccountUpdateStatement = nullptr;
	m_AccountSelectStatement = nullptr;
	m_AccountTruncateStatement = nullptr;

	m_CapitalDeleteStatement = nullptr;
	m_CapitalDeleteByTradingDayIndexStatement = nullptr;
	m_CapitalUpdateStatement = nullptr;
	m_CapitalSelectStatement = nullptr;
	m_CapitalTruncateStatement = nullptr;

	m_PositionDeleteStatement = nullptr;
	m_PositionDeleteByAccountIndexStatement = nullptr;
	m_PositionDeleteByTradingDayIndexStatement = nullptr;
	m_PositionUpdateStatement = nullptr;
	m_PositionSelectStatement = nullptr;
	m_PositionTruncateStatement = nullptr;

	m_PositionDetailDeleteStatement = nullptr;
	m_PositionDetailDeleteByTradeMatchIndexStatement = nullptr;
	m_PositionDetailDeleteByTradingDayIndexStatement = nullptr;
	m_PositionDetailUpdateStatement = nullptr;
	m_PositionDetailSelectStatement = nullptr;
	m_PositionDetailTruncateStatement = nullptr;

	m_OrderDeleteStatement = nullptr;
	m_OrderDeleteByAccountIDIndexStatement = nullptr;
	m_OrderUpdateStatement = nullptr;
	m_OrderSelectStatement = nullptr;
	m_OrderTruncateStatement = nullptr;

	m_TradeDeleteStatement = nullptr;
	m_TradeDeleteByAccountIDIndexStatement = nullptr;
	m_TradeUpdateStatement = nullptr;
	m_TradeSelectStatement = nullptr;
	m_TradeTruncateStatement = nullptr;

	m_AccountLoginSessionDeleteStatement = nullptr;
	m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	m_AccountLoginSessionUpdateStatement = nullptr;
	m_AccountLoginSessionSelectStatement = nullptr;
	m_AccountLoginSessionTruncateStatement = nullptr;

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
	if (m_TradingDayDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradingDayDeleteStatement);
		m_TradingDayDeleteStatement = nullptr;
	}
	if (m_TradingDayUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradingDayUpdateStatement);
		m_TradingDayUpdateStatement = nullptr;
	}
	if (m_TradingDaySelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradingDaySelectStatement);
		m_TradingDaySelectStatement = nullptr;
	}
	if (m_TradingDayTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradingDayTruncateStatement);
		m_TradingDayTruncateStatement = nullptr;
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
	if (m_ProductDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ProductDeleteStatement);
		m_ProductDeleteStatement = nullptr;
	}
	if (m_ProductUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ProductUpdateStatement);
		m_ProductUpdateStatement = nullptr;
	}
	if (m_ProductSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ProductSelectStatement);
		m_ProductSelectStatement = nullptr;
	}
	if (m_ProductTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_ProductTruncateStatement);
		m_ProductTruncateStatement = nullptr;
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
	if (m_PrimaryAccountDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PrimaryAccountDeleteStatement);
		m_PrimaryAccountDeleteStatement = nullptr;
	}
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PrimaryAccountDeleteByOfferIDIndexStatement);
		m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	}
	if (m_PrimaryAccountUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PrimaryAccountUpdateStatement);
		m_PrimaryAccountUpdateStatement = nullptr;
	}
	if (m_PrimaryAccountSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PrimaryAccountSelectStatement);
		m_PrimaryAccountSelectStatement = nullptr;
	}
	if (m_PrimaryAccountTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PrimaryAccountTruncateStatement);
		m_PrimaryAccountTruncateStatement = nullptr;
	}
	if (m_AccountDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountDeleteStatement);
		m_AccountDeleteStatement = nullptr;
	}
	if (m_AccountUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountUpdateStatement);
		m_AccountUpdateStatement = nullptr;
	}
	if (m_AccountSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountSelectStatement);
		m_AccountSelectStatement = nullptr;
	}
	if (m_AccountTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountTruncateStatement);
		m_AccountTruncateStatement = nullptr;
	}
	if (m_CapitalDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_CapitalDeleteStatement);
		m_CapitalDeleteStatement = nullptr;
	}
	if (m_CapitalDeleteByTradingDayIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_CapitalDeleteByTradingDayIndexStatement);
		m_CapitalDeleteByTradingDayIndexStatement = nullptr;
	}
	if (m_CapitalUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_CapitalUpdateStatement);
		m_CapitalUpdateStatement = nullptr;
	}
	if (m_CapitalSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_CapitalSelectStatement);
		m_CapitalSelectStatement = nullptr;
	}
	if (m_CapitalTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_CapitalTruncateStatement);
		m_CapitalTruncateStatement = nullptr;
	}
	if (m_PositionDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDeleteStatement);
		m_PositionDeleteStatement = nullptr;
	}
	if (m_PositionDeleteByAccountIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDeleteByAccountIndexStatement);
		m_PositionDeleteByAccountIndexStatement = nullptr;
	}
	if (m_PositionDeleteByTradingDayIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDeleteByTradingDayIndexStatement);
		m_PositionDeleteByTradingDayIndexStatement = nullptr;
	}
	if (m_PositionUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionUpdateStatement);
		m_PositionUpdateStatement = nullptr;
	}
	if (m_PositionSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionSelectStatement);
		m_PositionSelectStatement = nullptr;
	}
	if (m_PositionTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionTruncateStatement);
		m_PositionTruncateStatement = nullptr;
	}
	if (m_PositionDetailDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailDeleteStatement);
		m_PositionDetailDeleteStatement = nullptr;
	}
	if (m_PositionDetailDeleteByTradeMatchIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailDeleteByTradeMatchIndexStatement);
		m_PositionDetailDeleteByTradeMatchIndexStatement = nullptr;
	}
	if (m_PositionDetailDeleteByTradingDayIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailDeleteByTradingDayIndexStatement);
		m_PositionDetailDeleteByTradingDayIndexStatement = nullptr;
	}
	if (m_PositionDetailUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailUpdateStatement);
		m_PositionDetailUpdateStatement = nullptr;
	}
	if (m_PositionDetailSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailSelectStatement);
		m_PositionDetailSelectStatement = nullptr;
	}
	if (m_PositionDetailTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_PositionDetailTruncateStatement);
		m_PositionDetailTruncateStatement = nullptr;
	}
	if (m_OrderDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_OrderDeleteStatement);
		m_OrderDeleteStatement = nullptr;
	}
	if (m_OrderDeleteByAccountIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_OrderDeleteByAccountIDIndexStatement);
		m_OrderDeleteByAccountIDIndexStatement = nullptr;
	}
	if (m_OrderUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_OrderUpdateStatement);
		m_OrderUpdateStatement = nullptr;
	}
	if (m_OrderSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_OrderSelectStatement);
		m_OrderSelectStatement = nullptr;
	}
	if (m_OrderTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_OrderTruncateStatement);
		m_OrderTruncateStatement = nullptr;
	}
	if (m_TradeDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradeDeleteStatement);
		m_TradeDeleteStatement = nullptr;
	}
	if (m_TradeDeleteByAccountIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradeDeleteByAccountIDIndexStatement);
		m_TradeDeleteByAccountIDIndexStatement = nullptr;
	}
	if (m_TradeUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradeUpdateStatement);
		m_TradeUpdateStatement = nullptr;
	}
	if (m_TradeSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradeSelectStatement);
		m_TradeSelectStatement = nullptr;
	}
	if (m_TradeTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_TradeTruncateStatement);
		m_TradeTruncateStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountLoginSessionDeleteStatement);
		m_AccountLoginSessionDeleteStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountLoginSessionDeleteByAccountIDIndexStatement);
		m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	}
	if (m_AccountLoginSessionUpdateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountLoginSessionUpdateStatement);
		m_AccountLoginSessionUpdateStatement = nullptr;
	}
	if (m_AccountLoginSessionSelectStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountLoginSessionSelectStatement);
		m_AccountLoginSessionSelectStatement = nullptr;
	}
	if (m_AccountLoginSessionTruncateStatement != nullptr)
	{
		duckdb_destroy_prepare(&m_AccountLoginSessionTruncateStatement);
		m_AccountLoginSessionTruncateStatement = nullptr;
	}
}
void DuckDB::InitDB()
{
	Exec("Delete From t_TradingDay;");
	Exec("Insert Into t_TradingDay select * from Init.t_TradingDay;");
	Exec("Delete From t_Exchange;");
	Exec("Insert Into t_Exchange select * from Init.t_Exchange;");
	Exec("Delete From t_Product;");
	Exec("Insert Into t_Product select * from Init.t_Product;");
	Exec("Delete From t_Instrument;");
	Exec("Insert Into t_Instrument select * from Init.t_Instrument;");
	Exec("Delete From t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Delete From t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	Exec("Delete From t_PrimaryAccount;");
	Exec("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	Exec("Delete From t_Account;");
	Exec("Insert Into t_Account select * from Init.t_Account;");
	Exec("Delete From t_Capital;");
	Exec("Insert Into t_Capital select * from Init.t_Capital;");
	Exec("Delete From t_Position;");
	Exec("Insert Into t_Position select * from Init.t_Position;");
	Exec("Delete From t_PositionDetail;");
	Exec("Insert Into t_PositionDetail select * from Init.t_PositionDetail;");
	Exec("Delete From t_Order;");
	Exec("Insert Into t_Order select * from Init.t_Order;");
	Exec("Delete From t_Trade;");
	Exec("Insert Into t_Trade select * from Init.t_Trade;");
	Exec("Delete From t_AccountLoginSession;");
	Exec("Insert Into t_AccountLoginSession select * from Init.t_AccountLoginSession;");
}
void DuckDB::CreateTables()
{
	CreateTradingDay();
	CreateExchange();
	CreateProduct();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreatePrimaryAccount();
	CreateAccount();
	CreateCapital();
	CreatePosition();
	CreatePositionDetail();
	CreateOrder();
	CreateTrade();
	CreateAccountLoginSession();
}
void DuckDB::DropTables()
{
	DropTradingDay();
	DropExchange();
	DropProduct();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropPrimaryAccount();
	DropAccount();
	DropCapital();
	DropPosition();
	DropPositionDetail();
	DropOrder();
	DropTrade();
	DropAccountLoginSession();
}
void DuckDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncatePrimaryAccount();
	TruncateAccount();
	TruncateCapital();
	TruncatePosition();
	TruncatePositionDetail();
	TruncateOrder();
	TruncateTrade();
	TruncateAccountLoginSession();
}
void DuckDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateAccountLoginSession();
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

void DuckDB::CreateTradingDay()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_TradingDay (PK int, CurrTradingDay varchar, PreTradingDay varchar, PRIMARY KEY(PK));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateTradingDay failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTradingDay Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropTradingDay()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_TradingDay;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropTradingDay failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTradingDay Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertTradingDay(TradingDay* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_TradingDay", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_TradingDay Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForTradingDayRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertTradingDay(std::list<TradingDay*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_TradingDay", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_TradingDay Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForTradingDayRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertTradingDay RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_TradingDay where PK = ?;", &m_TradingDayDeleteStatement);
	}
	SetStatementForTradingDayPrimaryKey(m_TradingDayDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradingDayDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTradingDay Spend:%lldms", duration);
	}
}
void DuckDB::UpdateTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_TradingDay set CurrTradingDay = ?, PreTradingDay = ? where PK = ?;", &m_TradingDayUpdateStatement);
	}
	SetStatementForTradingDayRecordUpdate(m_TradingDayUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradingDayUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTradingDay Spend:%lldms", duration);
	}
}
void DuckDB::SelectTradingDay(std::list<TradingDay*>& records)
{
	auto start = steady_clock::now();
	if (m_TradingDaySelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_TradingDay;", &m_TradingDaySelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradingDaySelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectTradingDay ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTradingDay Spend:%lldms", duration);
	}
}
void DuckDB::TruncateTradingDay()
{
	auto start = steady_clock::now();
	if (m_TradingDayTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_TradingDay;", &m_TradingDayTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_TradingDayTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateTradingDay failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateTradingDay Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<TradingDay*>& records)
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

		int* dataColumn0 = (int*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			TradingDay* record = TradingDay::Allocate();
			memset(record, 0, sizeof(TradingDay));
			if (duckdb_validity_row_is_valid(validityColumn0, row)) record->PK = dataColumn0[row];
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->CurrTradingDay, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->PreTradingDay, dataColumn2[row]);
			}
			records.push_back(record);
		}
	}
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
void DuckDB::CreateProduct()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Product (ExchangeID varchar, ProductID varchar, ProductName varchar, ProductClass int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName varchar, PRIMARY KEY(ExchangeID, ProductID));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateProduct failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateProduct Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropProduct()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_Product;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropProduct failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropProduct Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertProduct(Product* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Product", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Product Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForProductRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertProduct(std::list<Product*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Product", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Product Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForProductRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertProduct RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Product where ExchangeID = ? and ProductID = ?;", &m_ProductDeleteStatement);
	}
	SetStatementForProductPrimaryKey(m_ProductDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ProductDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteProduct Spend:%lldms", duration);
	}
}
void DuckDB::UpdateProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Product set ProductName = ?, ProductClass = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and ProductID = ?;", &m_ProductUpdateStatement);
	}
	SetStatementForProductRecordUpdate(m_ProductUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ProductUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct Spend:%lldms", duration);
	}
}
void DuckDB::SelectProduct(std::list<Product*>& records)
{
	auto start = steady_clock::now();
	if (m_ProductSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Product;", &m_ProductSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_ProductSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectProduct ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectProduct Spend:%lldms", duration);
	}
}
void DuckDB::TruncateProduct()
{
	auto start = steady_clock::now();
	if (m_ProductTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Product;", &m_ProductTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_ProductTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateProduct failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateProduct Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Product*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		int* dataColumn3 = (int*)duckdb_vector_get_data(column3);
		int* dataColumn4 = (int*)duckdb_vector_get_data(column4);
		double* dataColumn5 = (double*)duckdb_vector_get_data(column5);
		int64_t* dataColumn6 = (int64_t*)duckdb_vector_get_data(column6);
		int64_t* dataColumn7 = (int64_t*)duckdb_vector_get_data(column7);
		int64_t* dataColumn8 = (int64_t*)duckdb_vector_get_data(column8);
		int64_t* dataColumn9 = (int64_t*)duckdb_vector_get_data(column9);
		duckdb_string_t* dataColumn10 = (duckdb_string_t*)duckdb_vector_get_data(column10);

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

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Product* record = Product::Allocate();
			memset(record, 0, sizeof(Product));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ProductID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->ProductName, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->ProductClass = ProductClassType(dataColumn3[row]);
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->VolumeMultiple = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->PriceTick = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->MaxMarketOrderVolume = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->MinMarketOrderVolume = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->MaxLimitOrderVolume = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->MinLimitOrderVolume = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row))
			{
				CpyDuckdbString(record->SessionName, dataColumn10[row]);
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
void DuckDB::CreatePrimaryAccount()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_PrimaryAccount (PrimaryAccountID varchar, PrimaryAccountName varchar, AccountClass int, Password varchar, OfferID int, IsAllowLogin int, IsSimulateAccount int, LoginStatus int, InitStatus int, PRIMARY KEY(PrimaryAccountID));CREATE INDEX IF NOT EXISTS PrimaryAccountOfferID ON t_PrimaryAccount(OfferID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreatePrimaryAccount failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePrimaryAccount Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropPrimaryAccount()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX PrimaryAccountOfferID;DROP TABLE IF EXISTS t_PrimaryAccount;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropPrimaryAccount failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPrimaryAccount Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertPrimaryAccount(PrimaryAccount* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_PrimaryAccount", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_PrimaryAccount Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForPrimaryAccountRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertPrimaryAccount(std::list<PrimaryAccount*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_PrimaryAccount", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_PrimaryAccount Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForPrimaryAccountRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertPrimaryAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeletePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PrimaryAccount where PrimaryAccountID = ?;", &m_PrimaryAccountDeleteStatement);
	}
	SetStatementForPrimaryAccountPrimaryKey(m_PrimaryAccountDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PrimaryAccountDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccount Spend:%lldms", duration);
	}
}
void DuckDB::DeletePrimaryAccountByOfferIDIndex(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PrimaryAccount where OfferID = ?;", &m_PrimaryAccountDeleteByOfferIDIndexStatement);
	}
	SetStatementForPrimaryAccountIndexOfferID(m_PrimaryAccountDeleteByOfferIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PrimaryAccountDeleteByOfferIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccountByOfferIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccountByOfferIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdatePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_PrimaryAccount set PrimaryAccountName = ?, AccountClass = ?, Password = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;", &m_PrimaryAccountUpdateStatement);
	}
	SetStatementForPrimaryAccountRecordUpdate(m_PrimaryAccountUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PrimaryAccountUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount Spend:%lldms", duration);
	}
}
void DuckDB::SelectPrimaryAccount(std::list<PrimaryAccount*>& records)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_PrimaryAccount;", &m_PrimaryAccountSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PrimaryAccountSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectPrimaryAccount ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPrimaryAccount Spend:%lldms", duration);
	}
}
void DuckDB::TruncatePrimaryAccount()
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PrimaryAccount;", &m_PrimaryAccountTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_PrimaryAccountTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncatePrimaryAccount failed");
	}
	
	WriteLog(LogLevel::Info, "TruncatePrimaryAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<PrimaryAccount*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		int* dataColumn4 = (int*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		int* dataColumn7 = (int*)duckdb_vector_get_data(column7);
		int* dataColumn8 = (int*)duckdb_vector_get_data(column8);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			PrimaryAccount* record = PrimaryAccount::Allocate();
			memset(record, 0, sizeof(PrimaryAccount));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->PrimaryAccountID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->PrimaryAccountName, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountClass = AccountClassType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->Password, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->OfferID = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->IsAllowLogin = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->IsSimulateAccount = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->LoginStatus = LoginStatusType(dataColumn7[row]);
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->InitStatus = InitStatusType(dataColumn8[row]);
			records.push_back(record);
		}
	}
}
void DuckDB::CreateAccount()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Account (AccountID varchar, AccountName varchar, AccountType int, AccountStatus int, Password varchar, TradeGroupID int, RiskGroupID int, CommissionGroupID int, PRIMARY KEY(AccountID));";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateAccount failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccount Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropAccount()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP TABLE IF EXISTS t_Account;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropAccount failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccount Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertAccount(Account* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Account", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Account Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForAccountRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertAccount(std::list<Account*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Account", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Account Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForAccountRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Account where AccountID = ?;", &m_AccountDeleteStatement);
	}
	SetStatementForAccountPrimaryKey(m_AccountDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccount Spend:%lldms", duration);
	}
}
void DuckDB::UpdateAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Account set AccountName = ?, AccountType = ?, AccountStatus = ?, Password = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ? where AccountID = ?;", &m_AccountUpdateStatement);
	}
	SetStatementForAccountRecordUpdate(m_AccountUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount Spend:%lldms", duration);
	}
}
void DuckDB::SelectAccount(std::list<Account*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Account;", &m_AccountSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectAccount ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccount Spend:%lldms", duration);
	}
}
void DuckDB::TruncateAccount()
{
	auto start = steady_clock::now();
	if (m_AccountTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Account;", &m_AccountTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_AccountTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateAccount failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Account*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		int* dataColumn3 = (int*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		int* dataColumn7 = (int*)duckdb_vector_get_data(column7);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Account* record = Account::Allocate();
			memset(record, 0, sizeof(Account));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountName, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->AccountStatus = AccountStatusType(dataColumn3[row]);
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->Password, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->TradeGroupID = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->RiskGroupID = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->CommissionGroupID = dataColumn7[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreateCapital()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Capital (TradingDay varchar, AccountID varchar, AccountType int, Balance double, PreBalance double, Available double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, Deposit double, Withdraw double, PRIMARY KEY(TradingDay, AccountID));CREATE INDEX IF NOT EXISTS CapitalTradingDay ON t_Capital(TradingDay);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateCapital failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateCapital Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropCapital()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX CapitalTradingDay;DROP TABLE IF EXISTS t_Capital;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropCapital failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropCapital Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertCapital(Capital* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Capital", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Capital Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForCapitalRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertCapital(std::list<Capital*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Capital", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Capital Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForCapitalRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertCapital RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Capital where TradingDay = ? and AccountID = ?;", &m_CapitalDeleteStatement);
	}
	SetStatementForCapitalPrimaryKey(m_CapitalDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_CapitalDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteCapital Spend:%lldms", duration);
	}
}
void DuckDB::DeleteCapitalByTradingDayIndex(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalDeleteByTradingDayIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Capital where TradingDay = ?;", &m_CapitalDeleteByTradingDayIndexStatement);
	}
	SetStatementForCapitalIndexTradingDay(m_CapitalDeleteByTradingDayIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_CapitalDeleteByTradingDayIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteCapitalByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteCapitalByTradingDayIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Capital set AccountType = ?, Balance = ?, PreBalance = ?, Available = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, Deposit = ?, Withdraw = ? where TradingDay = ? and AccountID = ?;", &m_CapitalUpdateStatement);
	}
	SetStatementForCapitalRecordUpdate(m_CapitalUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_CapitalUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateCapital Spend:%lldms", duration);
	}
}
void DuckDB::SelectCapital(std::list<Capital*>& records)
{
	auto start = steady_clock::now();
	if (m_CapitalSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Capital;", &m_CapitalSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_CapitalSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectCapital ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectCapital Spend:%lldms", duration);
	}
}
void DuckDB::TruncateCapital()
{
	auto start = steady_clock::now();
	if (m_CapitalTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Capital;", &m_CapitalTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_CapitalTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateCapital failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateCapital Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Capital*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		double* dataColumn3 = (double*)duckdb_vector_get_data(column3);
		double* dataColumn4 = (double*)duckdb_vector_get_data(column4);
		double* dataColumn5 = (double*)duckdb_vector_get_data(column5);
		double* dataColumn6 = (double*)duckdb_vector_get_data(column6);
		double* dataColumn7 = (double*)duckdb_vector_get_data(column7);
		double* dataColumn8 = (double*)duckdb_vector_get_data(column8);
		double* dataColumn9 = (double*)duckdb_vector_get_data(column9);
		double* dataColumn10 = (double*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		double* dataColumn12 = (double*)duckdb_vector_get_data(column12);
		double* dataColumn13 = (double*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		double* dataColumn16 = (double*)duckdb_vector_get_data(column16);
		double* dataColumn17 = (double*)duckdb_vector_get_data(column17);
		double* dataColumn18 = (double*)duckdb_vector_get_data(column18);
		double* dataColumn19 = (double*)duckdb_vector_get_data(column19);

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

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Capital* record = Capital::Allocate();
			memset(record, 0, sizeof(Capital));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->Balance = dataColumn3[row];
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->PreBalance = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->Available = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->MarketValue = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->CashIn = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->CashOut = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->Margin = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->Commission = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->FrozenCash = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->FrozenMargin = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->FrozenCommission = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->CloseProfitByDate = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->CloseProfitByTrade = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->PositionProfitByDate = dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->PositionProfitByTrade = dataColumn17[row];
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->Deposit = dataColumn18[row];
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->Withdraw = dataColumn19[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreatePosition()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Position (TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, PosiDirection int, TotalPosition bigint, PositionFrozen bigint, TodayPosition bigint, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection));CREATE INDEX IF NOT EXISTS PositionAccount ON t_Position(TradingDay, AccountID);CREATE INDEX IF NOT EXISTS PositionTradingDay ON t_Position(TradingDay);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreatePosition failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePosition Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropPosition()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX PositionAccount;DROP INDEX PositionTradingDay;DROP TABLE IF EXISTS t_Position;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropPosition failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPosition Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertPosition(Position* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Position", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Position Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForPositionRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertPosition(std::list<Position*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Position", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Position Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForPositionRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertPosition RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeletePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Position where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", &m_PositionDeleteStatement);
	}
	SetStatementForPositionPrimaryKey(m_PositionDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePosition failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePosition Spend:%lldms", duration);
	}
}
void DuckDB::DeletePositionByAccountIndex(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteByAccountIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Position where TradingDay = ? and AccountID = ?;", &m_PositionDeleteByAccountIndexStatement);
	}
	SetStatementForPositionIndexAccount(m_PositionDeleteByAccountIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDeleteByAccountIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByAccountIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByAccountIndex Spend:%lldms", duration);
	}
}
void DuckDB::DeletePositionByTradingDayIndex(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteByTradingDayIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Position where TradingDay = ?;", &m_PositionDeleteByTradingDayIndexStatement);
	}
	SetStatementForPositionIndexTradingDay(m_PositionDeleteByTradingDayIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDeleteByTradingDayIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByTradingDayIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdatePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Position set AccountType = ?, ProductClass = ?, TotalPosition = ?, PositionFrozen = ?, TodayPosition = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, VolumeMultiple = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, SettlementPrice = ?, PreSettlementPrice = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", &m_PositionUpdateStatement);
	}
	SetStatementForPositionRecordUpdate(m_PositionUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdatePosition failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePosition Spend:%lldms", duration);
	}
}
void DuckDB::SelectPosition(std::list<Position*>& records)
{
	auto start = steady_clock::now();
	if (m_PositionSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Position;", &m_PositionSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectPosition ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPosition Spend:%lldms", duration);
	}
}
void DuckDB::TruncatePosition()
{
	auto start = steady_clock::now();
	if (m_PositionTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Position;", &m_PositionTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_PositionTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncatePosition failed");
	}
	
	WriteLog(LogLevel::Info, "TruncatePosition Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Position*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		int64_t* dataColumn7 = (int64_t*)duckdb_vector_get_data(column7);
		int64_t* dataColumn8 = (int64_t*)duckdb_vector_get_data(column8);
		int64_t* dataColumn9 = (int64_t*)duckdb_vector_get_data(column9);
		double* dataColumn10 = (double*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		double* dataColumn12 = (double*)duckdb_vector_get_data(column12);
		double* dataColumn13 = (double*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		double* dataColumn16 = (double*)duckdb_vector_get_data(column16);
		double* dataColumn17 = (double*)duckdb_vector_get_data(column17);
		int* dataColumn18 = (int*)duckdb_vector_get_data(column18);
		double* dataColumn19 = (double*)duckdb_vector_get_data(column19);
		double* dataColumn20 = (double*)duckdb_vector_get_data(column20);
		double* dataColumn21 = (double*)duckdb_vector_get_data(column21);
		double* dataColumn22 = (double*)duckdb_vector_get_data(column22);
		double* dataColumn23 = (double*)duckdb_vector_get_data(column23);
		double* dataColumn24 = (double*)duckdb_vector_get_data(column24);

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

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Position* record = Position::Allocate();
			memset(record, 0, sizeof(Position));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->ProductClass = ProductClassType(dataColumn5[row]);
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->PosiDirection = PosiDirectionType(dataColumn6[row]);
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->TotalPosition = dataColumn7[row];
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->PositionFrozen = dataColumn8[row];
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->TodayPosition = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->MarketValue = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->CashIn = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->CashOut = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->Margin = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->Commission = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->FrozenCash = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->FrozenMargin = dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->FrozenCommission = dataColumn17[row];
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->VolumeMultiple = dataColumn18[row];
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->CloseProfitByDate = dataColumn19[row];
			if (duckdb_validity_row_is_valid(validityColumn20, row)) record->CloseProfitByTrade = dataColumn20[row];
			if (duckdb_validity_row_is_valid(validityColumn21, row)) record->PositionProfitByDate = dataColumn21[row];
			if (duckdb_validity_row_is_valid(validityColumn22, row)) record->PositionProfitByTrade = dataColumn22[row];
			if (duckdb_validity_row_is_valid(validityColumn23, row)) record->SettlementPrice = dataColumn23[row];
			if (duckdb_validity_row_is_valid(validityColumn24, row)) record->PreSettlementPrice = dataColumn24[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreatePositionDetail()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_PositionDetail (TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, PosiDirection int, OpenDate varchar, TradeID varchar, Volume bigint, OpenPrice double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, CloseVolume bigint, CloseAmount double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID));CREATE INDEX IF NOT EXISTS PositionDetailTradeMatch ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);CREATE INDEX IF NOT EXISTS PositionDetailTradingDay ON t_PositionDetail(TradingDay);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreatePositionDetail failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePositionDetail Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropPositionDetail()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX PositionDetailTradeMatch;DROP INDEX PositionDetailTradingDay;DROP TABLE IF EXISTS t_PositionDetail;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropPositionDetail failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPositionDetail Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertPositionDetail(PositionDetail* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_PositionDetail", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_PositionDetail Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForPositionDetailRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertPositionDetail(std::list<PositionDetail*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_PositionDetail", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_PositionDetail Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForPositionDetailRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertPositionDetail RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeletePositionDetail(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PositionDetail where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ? and OpenDate = ? and TradeID = ?;", &m_PositionDetailDeleteStatement);
	}
	SetStatementForPositionDetailPrimaryKey(m_PositionDetailDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDetailDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetail Spend:%lldms", duration);
	}
}
void DuckDB::DeletePositionDetailByTradeMatchIndex(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteByTradeMatchIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PositionDetail where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", &m_PositionDetailDeleteByTradeMatchIndexStatement);
	}
	SetStatementForPositionDetailIndexTradeMatch(m_PositionDetailDeleteByTradeMatchIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDetailDeleteByTradeMatchIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradeMatchIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradeMatchIndex Spend:%lldms", duration);
	}
}
void DuckDB::DeletePositionDetailByTradingDayIndex(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteByTradingDayIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PositionDetail where TradingDay = ?;", &m_PositionDetailDeleteByTradingDayIndexStatement);
	}
	SetStatementForPositionDetailIndexTradingDay(m_PositionDetailDeleteByTradingDayIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDetailDeleteByTradingDayIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradingDayIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdatePositionDetail(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_PositionDetail set AccountType = ?, ProductClass = ?, Volume = ?, OpenPrice = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, VolumeMultiple = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, SettlementPrice = ?, PreSettlementPrice = ?, CloseVolume = ?, CloseAmount = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ? and OpenDate = ? and TradeID = ?;", &m_PositionDetailUpdateStatement);
	}
	SetStatementForPositionDetailRecordUpdate(m_PositionDetailUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDetailUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdatePositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePositionDetail Spend:%lldms", duration);
	}
}
void DuckDB::SelectPositionDetail(std::list<PositionDetail*>& records)
{
	auto start = steady_clock::now();
	if (m_PositionDetailSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_PositionDetail;", &m_PositionDetailSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_PositionDetailSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectPositionDetail ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPositionDetail Spend:%lldms", duration);
	}
}
void DuckDB::TruncatePositionDetail()
{
	auto start = steady_clock::now();
	if (m_PositionDetailTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_PositionDetail;", &m_PositionDetailTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_PositionDetailTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncatePositionDetail failed");
	}
	
	WriteLog(LogLevel::Info, "TruncatePositionDetail Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<PositionDetail*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		duckdb_string_t* dataColumn7 = (duckdb_string_t*)duckdb_vector_get_data(column7);
		duckdb_string_t* dataColumn8 = (duckdb_string_t*)duckdb_vector_get_data(column8);
		int64_t* dataColumn9 = (int64_t*)duckdb_vector_get_data(column9);
		double* dataColumn10 = (double*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		double* dataColumn12 = (double*)duckdb_vector_get_data(column12);
		double* dataColumn13 = (double*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		int* dataColumn16 = (int*)duckdb_vector_get_data(column16);
		double* dataColumn17 = (double*)duckdb_vector_get_data(column17);
		double* dataColumn18 = (double*)duckdb_vector_get_data(column18);
		double* dataColumn19 = (double*)duckdb_vector_get_data(column19);
		double* dataColumn20 = (double*)duckdb_vector_get_data(column20);
		double* dataColumn21 = (double*)duckdb_vector_get_data(column21);
		double* dataColumn22 = (double*)duckdb_vector_get_data(column22);
		int64_t* dataColumn23 = (int64_t*)duckdb_vector_get_data(column23);
		double* dataColumn24 = (double*)duckdb_vector_get_data(column24);

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

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			PositionDetail* record = PositionDetail::Allocate();
			memset(record, 0, sizeof(PositionDetail));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->ProductClass = ProductClassType(dataColumn5[row]);
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->PosiDirection = PosiDirectionType(dataColumn6[row]);
			if (duckdb_validity_row_is_valid(validityColumn7, row))
			{
				CpyDuckdbString(record->OpenDate, dataColumn7[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn8, row))
			{
				CpyDuckdbString(record->TradeID, dataColumn8[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->Volume = dataColumn9[row];
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->OpenPrice = dataColumn10[row];
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->MarketValue = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->CashIn = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->CashOut = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->Margin = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->Commission = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->VolumeMultiple = dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->CloseProfitByDate = dataColumn17[row];
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->CloseProfitByTrade = dataColumn18[row];
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->PositionProfitByDate = dataColumn19[row];
			if (duckdb_validity_row_is_valid(validityColumn20, row)) record->PositionProfitByTrade = dataColumn20[row];
			if (duckdb_validity_row_is_valid(validityColumn21, row)) record->SettlementPrice = dataColumn21[row];
			if (duckdb_validity_row_is_valid(validityColumn22, row)) record->PreSettlementPrice = dataColumn22[row];
			if (duckdb_validity_row_is_valid(validityColumn23, row)) record->CloseVolume = dataColumn23[row];
			if (duckdb_validity_row_is_valid(validityColumn24, row)) record->CloseAmount = dataColumn24[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreateOrder()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Order (TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, OrderSysID varchar, Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate varchar, OrderTime varchar, CancelDate varchar, CancelTime varchar, SessionID bigint, ClientOrderID int, RequestID int, OfferID int, TradeGroupID int, RiskGroupID int, CommissionGroupID int, FrozenCash double, FrozenMargin double, FrozenCommission double, RebuildMark int, IsForceClose int, UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID));CREATE INDEX IF NOT EXISTS OrderAccountID ON t_Order(TradingDay, AccountID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateOrder failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateOrder Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropOrder()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX OrderAccountID;DROP TABLE IF EXISTS t_Order;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropOrder failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropOrder Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertOrder(Order* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Order", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Order Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForOrderRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertOrder(std::list<Order*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Order", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Order Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForOrderRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertOrder RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Order where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", &m_OrderDeleteStatement);
	}
	SetStatementForOrderPrimaryKey(m_OrderDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_OrderDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteOrder Spend:%lldms", duration);
	}
}
void DuckDB::DeleteOrderByAccountIDIndex(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderDeleteByAccountIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Order where TradingDay = ? and AccountID = ?;", &m_OrderDeleteByAccountIDIndexStatement);
	}
	SetStatementForOrderIndexAccountID(m_OrderDeleteByAccountIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_OrderDeleteByAccountIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteOrderByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteOrderByAccountIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Order set AccountType = ?, ProductClass = ?, OrderSysID = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ?, RequestID = ?, OfferID = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, RebuildMark = ?, IsForceClose = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", &m_OrderUpdateStatement);
	}
	SetStatementForOrderRecordUpdate(m_OrderUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_OrderUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder Spend:%lldms", duration);
	}
}
void DuckDB::SelectOrder(std::list<Order*>& records)
{
	auto start = steady_clock::now();
	if (m_OrderSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Order;", &m_OrderSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_OrderSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectOrder ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectOrder Spend:%lldms", duration);
	}
}
void DuckDB::TruncateOrder()
{
	auto start = steady_clock::now();
	if (m_OrderTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Order;", &m_OrderTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_OrderTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateOrder failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateOrder Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Order*>& records)
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

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		duckdb_string_t* dataColumn7 = (duckdb_string_t*)duckdb_vector_get_data(column7);
		int* dataColumn8 = (int*)duckdb_vector_get_data(column8);
		int* dataColumn9 = (int*)duckdb_vector_get_data(column9);
		int* dataColumn10 = (int*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		int64_t* dataColumn12 = (int64_t*)duckdb_vector_get_data(column12);
		int64_t* dataColumn13 = (int64_t*)duckdb_vector_get_data(column13);
		int64_t* dataColumn14 = (int64_t*)duckdb_vector_get_data(column14);
		int* dataColumn15 = (int*)duckdb_vector_get_data(column15);
		int* dataColumn16 = (int*)duckdb_vector_get_data(column16);
		duckdb_string_t* dataColumn17 = (duckdb_string_t*)duckdb_vector_get_data(column17);
		duckdb_string_t* dataColumn18 = (duckdb_string_t*)duckdb_vector_get_data(column18);
		duckdb_string_t* dataColumn19 = (duckdb_string_t*)duckdb_vector_get_data(column19);
		duckdb_string_t* dataColumn20 = (duckdb_string_t*)duckdb_vector_get_data(column20);
		int64_t* dataColumn21 = (int64_t*)duckdb_vector_get_data(column21);
		int* dataColumn22 = (int*)duckdb_vector_get_data(column22);
		int* dataColumn23 = (int*)duckdb_vector_get_data(column23);
		int* dataColumn24 = (int*)duckdb_vector_get_data(column24);
		int* dataColumn25 = (int*)duckdb_vector_get_data(column25);
		int* dataColumn26 = (int*)duckdb_vector_get_data(column26);
		int* dataColumn27 = (int*)duckdb_vector_get_data(column27);
		double* dataColumn28 = (double*)duckdb_vector_get_data(column28);
		double* dataColumn29 = (double*)duckdb_vector_get_data(column29);
		double* dataColumn30 = (double*)duckdb_vector_get_data(column30);
		int* dataColumn31 = (int*)duckdb_vector_get_data(column31);
		int* dataColumn32 = (int*)duckdb_vector_get_data(column32);

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

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Order* record = Order::Allocate();
			memset(record, 0, sizeof(Order));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->ProductClass = ProductClassType(dataColumn5[row]);
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->OrderID = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row))
			{
				CpyDuckdbString(record->OrderSysID, dataColumn7[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->Direction = DirectionType(dataColumn8[row]);
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->OffsetFlag = OffsetFlagType(dataColumn9[row]);
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->OrderPriceType = OrderPriceTypeType(dataColumn10[row]);
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->Price = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->Volume = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->VolumeTotal = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->VolumeTraded = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->VolumeMultiple = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->OrderStatus = OrderStatusType(dataColumn16[row]);
			if (duckdb_validity_row_is_valid(validityColumn17, row))
			{
				CpyDuckdbString(record->OrderDate, dataColumn17[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn18, row))
			{
				CpyDuckdbString(record->OrderTime, dataColumn18[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn19, row))
			{
				CpyDuckdbString(record->CancelDate, dataColumn19[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn20, row))
			{
				CpyDuckdbString(record->CancelTime, dataColumn20[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn21, row)) record->SessionID = dataColumn21[row];
			if (duckdb_validity_row_is_valid(validityColumn22, row)) record->ClientOrderID = dataColumn22[row];
			if (duckdb_validity_row_is_valid(validityColumn23, row)) record->RequestID = dataColumn23[row];
			if (duckdb_validity_row_is_valid(validityColumn24, row)) record->OfferID = dataColumn24[row];
			if (duckdb_validity_row_is_valid(validityColumn25, row)) record->TradeGroupID = dataColumn25[row];
			if (duckdb_validity_row_is_valid(validityColumn26, row)) record->RiskGroupID = dataColumn26[row];
			if (duckdb_validity_row_is_valid(validityColumn27, row)) record->CommissionGroupID = dataColumn27[row];
			if (duckdb_validity_row_is_valid(validityColumn28, row)) record->FrozenCash = dataColumn28[row];
			if (duckdb_validity_row_is_valid(validityColumn29, row)) record->FrozenMargin = dataColumn29[row];
			if (duckdb_validity_row_is_valid(validityColumn30, row)) record->FrozenCommission = dataColumn30[row];
			if (duckdb_validity_row_is_valid(validityColumn31, row)) record->RebuildMark = dataColumn31[row];
			if (duckdb_validity_row_is_valid(validityColumn32, row)) record->IsForceClose = dataColumn32[row];
			records.push_back(record);
		}
	}
}
void DuckDB::CreateTrade()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Trade (TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, OrderSysID varchar, TradeID varchar, Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate varchar, TradeTime varchar, PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction));CREATE INDEX IF NOT EXISTS TradeAccountID ON t_Trade(TradingDay, AccountID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateTrade failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTrade Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropTrade()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX TradeAccountID;DROP TABLE IF EXISTS t_Trade;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropTrade failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTrade Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertTrade(Trade* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Trade", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Trade Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForTradeRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertTrade(std::list<Trade*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_Trade", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_Trade Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForTradeRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertTrade RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Trade where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", &m_TradeDeleteStatement);
	}
	SetStatementForTradePrimaryKey(m_TradeDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradeDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTrade Spend:%lldms", duration);
	}
}
void DuckDB::DeleteTradeByAccountIDIndex(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeDeleteByAccountIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Trade where TradingDay = ? and AccountID = ?;", &m_TradeDeleteByAccountIDIndexStatement);
	}
	SetStatementForTradeIndexAccountID(m_TradeDeleteByAccountIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradeDeleteByAccountIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteTradeByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTradeByAccountIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_Trade set AccountID = ?, AccountType = ?, InstrumentID = ?, ProductClass = ?, OrderID = ?, OrderSysID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", &m_TradeUpdateStatement);
	}
	SetStatementForTradeRecordUpdate(m_TradeUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradeUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade Spend:%lldms", duration);
	}
}
void DuckDB::SelectTrade(std::list<Trade*>& records)
{
	auto start = steady_clock::now();
	if (m_TradeSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_Trade;", &m_TradeSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_TradeSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectTrade ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTrade Spend:%lldms", duration);
	}
}
void DuckDB::TruncateTrade()
{
	auto start = steady_clock::now();
	if (m_TradeTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_Trade;", &m_TradeTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_TradeTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateTrade failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateTrade Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<Trade*>& records)
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
		int* dataColumn2 = (int*)duckdb_vector_get_data(column2);
		duckdb_string_t* dataColumn3 = (duckdb_string_t*)duckdb_vector_get_data(column3);
		duckdb_string_t* dataColumn4 = (duckdb_string_t*)duckdb_vector_get_data(column4);
		int* dataColumn5 = (int*)duckdb_vector_get_data(column5);
		int* dataColumn6 = (int*)duckdb_vector_get_data(column6);
		duckdb_string_t* dataColumn7 = (duckdb_string_t*)duckdb_vector_get_data(column7);
		duckdb_string_t* dataColumn8 = (duckdb_string_t*)duckdb_vector_get_data(column8);
		int* dataColumn9 = (int*)duckdb_vector_get_data(column9);
		int* dataColumn10 = (int*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		int64_t* dataColumn12 = (int64_t*)duckdb_vector_get_data(column12);
		int* dataColumn13 = (int*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		duckdb_string_t* dataColumn16 = (duckdb_string_t*)duckdb_vector_get_data(column16);
		duckdb_string_t* dataColumn17 = (duckdb_string_t*)duckdb_vector_get_data(column17);

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
			Trade* record = Trade::Allocate();
			memset(record, 0, sizeof(Trade));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->TradingDay, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row)) record->AccountType = AccountTypeType(dataColumn2[row]);
			if (duckdb_validity_row_is_valid(validityColumn3, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn3[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn4, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn4[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->ProductClass = ProductClassType(dataColumn5[row]);
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->OrderID = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row))
			{
				CpyDuckdbString(record->OrderSysID, dataColumn7[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn8, row))
			{
				CpyDuckdbString(record->TradeID, dataColumn8[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->Direction = DirectionType(dataColumn9[row]);
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->OffsetFlag = OffsetFlagType(dataColumn10[row]);
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->Price = dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->Volume = dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->VolumeMultiple = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->TradeAmount = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->Commission = dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row))
			{
				CpyDuckdbString(record->TradeDate, dataColumn16[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn17, row))
			{
				CpyDuckdbString(record->TradeTime, dataColumn17[row]);
			}
			records.push_back(record);
		}
	}
}
void DuckDB::CreateAccountLoginSession()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_AccountLoginSession (AccountID varchar, SessionID bigint, IPAddress varchar, PRIMARY KEY(SessionID));CREATE INDEX IF NOT EXISTS AccountLoginSessionAccountID ON t_AccountLoginSession(AccountID);";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "CreateAccountLoginSession failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccountLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::DropAccountLoginSession()
{
	auto start = steady_clock::now();
	duckdb_result result;
	const char* sql = "DROP INDEX AccountLoginSessionAccountID;DROP TABLE IF EXISTS t_AccountLoginSession;";
	auto rc = duckdb_query(m_Connection, sql, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DropAccountLoginSession failed, ErrorMsg:%s", duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccountLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void DuckDB::InsertAccountLoginSession(AccountLoginSession* record)
{
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_AccountLoginSession", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_AccountLoginSession Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	AppendForAccountLoginSessionRecord(appender, record);
	duckdb_appender_destroy(&appender);
}
void DuckDB::BatchInsertAccountLoginSession(std::list<AccountLoginSession*>* records)
{
	auto start = steady_clock::now();
	duckdb_appender appender;
	if (duckdb_appender_create(m_Connection, nullptr, "t_AccountLoginSession", &appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "duckdb_appender_create For Table:t_AccountLoginSession Failed. ErrorMsg:%s", duckdb_appender_error(appender));
		duckdb_appender_destroy(&appender);
		return;
	}
	for (auto record : *records)
	{
		AppendForAccountLoginSessionRecord(appender, record);
	}
	duckdb_appender_destroy(&appender);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "BatchInsertAccountLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void DuckDB::DeleteAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_AccountLoginSession where SessionID = ?;", &m_AccountLoginSessionDeleteStatement);
	}
	SetStatementForAccountLoginSessionPrimaryKey(m_AccountLoginSessionDeleteStatement, record);

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountLoginSessionDeleteStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::DeleteAccountLoginSessionByAccountIDIndex(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_AccountLoginSession where AccountID = ?;", &m_AccountLoginSessionDeleteByAccountIDIndexStatement);
	}
	SetStatementForAccountLoginSessionIndexAccountID(m_AccountLoginSessionDeleteByAccountIDIndexStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountLoginSessionDeleteByAccountIDIndexStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSessionByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSessionByAccountIDIndex Spend:%lldms", duration);
	}
}
void DuckDB::UpdateAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionUpdateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "update t_AccountLoginSession set AccountID = ?, IPAddress = ? where SessionID = ?;", &m_AccountLoginSessionUpdateStatement);
	}
	SetStatementForAccountLoginSessionRecordUpdate(m_AccountLoginSessionUpdateStatement, record);
	
	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountLoginSessionUpdateStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "UpdateAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_result_error(&result));
	}
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccountLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::SelectAccountLoginSession(std::list<AccountLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionSelectStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "select * from t_AccountLoginSession;", &m_AccountLoginSessionSelectStatement);
	}

	duckdb_result result;
	auto rc = duckdb_execute_prepared(m_AccountLoginSessionSelectStatement, &result);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "SelectAccountLoginSession ErrorMsg:%s", duckdb_result_error(&result));
		duckdb_destroy_result(&result);
		return;
	}

	ParseRecord(result, records);
	duckdb_destroy_result(&result);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccountLoginSession Spend:%lldms", duration);
	}
}
void DuckDB::TruncateAccountLoginSession()
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionTruncateStatement == nullptr)
	{
		duckdb_prepare(m_Connection, "delete from t_AccountLoginSession;", &m_AccountLoginSessionTruncateStatement);
	}

	auto rc = duckdb_execute_prepared(m_AccountLoginSessionTruncateStatement, nullptr);
	if (rc != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "TruncateAccountLoginSession failed");
	}
	
	WriteLog(LogLevel::Info, "TruncateAccountLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void DuckDB::ParseRecord(duckdb_result& result, std::list<AccountLoginSession*>& records)
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
			AccountLoginSession* record = AccountLoginSession::Allocate();
			memset(record, 0, sizeof(AccountLoginSession));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->AccountID, dataColumn0[row]);
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


bool DuckDB::AppendForTradingDayRecord(duckdb_appender appender, TradingDay* record)
{
	duckdb_append_int32(appender, record->PK);
	duckdb_append_varchar(appender, record->CurrTradingDay);
	duckdb_append_varchar(appender, record->PreTradingDay);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForTradingDayRecord(duckdb_prepared_statement statement, TradingDay* record)
{
	duckdb_bind_int32(statement, 1, record->PK);
	duckdb_bind_varchar(statement, 2, record->CurrTradingDay);
	duckdb_bind_varchar(statement, 3, record->PreTradingDay);
}
void DuckDB::SetStatementForTradingDayRecordUpdate(duckdb_prepared_statement statement, TradingDay* record)
{
	duckdb_bind_varchar(statement, 1, record->CurrTradingDay);
	duckdb_bind_varchar(statement, 2, record->PreTradingDay);
	duckdb_bind_int32(statement, 3, record->PK);
}
void DuckDB::SetStatementForTradingDayPrimaryKey(duckdb_prepared_statement statement, TradingDay* record)
{
	duckdb_bind_int32(statement, 1, record->PK);
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
bool DuckDB::AppendForProductRecord(duckdb_appender appender, Product* record)
{
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->ProductID);
	duckdb_append_varchar(appender, record->ProductName);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_double(appender, record->PriceTick);
	duckdb_append_int64(appender, record->MaxMarketOrderVolume);
	duckdb_append_int64(appender, record->MinMarketOrderVolume);
	duckdb_append_int64(appender, record->MaxLimitOrderVolume);
	duckdb_append_int64(appender, record->MinLimitOrderVolume);
	duckdb_append_varchar(appender, record->SessionName);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForProductRecord(duckdb_prepared_statement statement, Product* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->ProductID);
	duckdb_bind_varchar(statement, 3, record->ProductName);
	duckdb_bind_int32(statement, 4, int(record->ProductClass));
	duckdb_bind_int32(statement, 5, record->VolumeMultiple);
	duckdb_bind_double(statement, 6, record->PriceTick);
	duckdb_bind_int64(statement, 7, record->MaxMarketOrderVolume);
	duckdb_bind_int64(statement, 8, record->MinMarketOrderVolume);
	duckdb_bind_int64(statement, 9, record->MaxLimitOrderVolume);
	duckdb_bind_int64(statement, 10, record->MinLimitOrderVolume);
	duckdb_bind_varchar(statement, 11, record->SessionName);
}
void DuckDB::SetStatementForProductRecordUpdate(duckdb_prepared_statement statement, Product* record)
{
	duckdb_bind_varchar(statement, 1, record->ProductName);
	duckdb_bind_int32(statement, 2, int(record->ProductClass));
	duckdb_bind_int32(statement, 3, record->VolumeMultiple);
	duckdb_bind_double(statement, 4, record->PriceTick);
	duckdb_bind_int64(statement, 5, record->MaxMarketOrderVolume);
	duckdb_bind_int64(statement, 6, record->MinMarketOrderVolume);
	duckdb_bind_int64(statement, 7, record->MaxLimitOrderVolume);
	duckdb_bind_int64(statement, 8, record->MinLimitOrderVolume);
	duckdb_bind_varchar(statement, 9, record->SessionName);
	duckdb_bind_varchar(statement, 10, record->ExchangeID);
	duckdb_bind_varchar(statement, 11, record->ProductID);
}
void DuckDB::SetStatementForProductPrimaryKey(duckdb_prepared_statement statement, Product* record)
{
	duckdb_bind_varchar(statement, 1, record->ExchangeID);
	duckdb_bind_varchar(statement, 2, record->ProductID);
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
bool DuckDB::AppendForPrimaryAccountRecord(duckdb_appender appender, PrimaryAccount* record)
{
	duckdb_append_varchar(appender, record->PrimaryAccountID);
	duckdb_append_varchar(appender, record->PrimaryAccountName);
	duckdb_append_int32(appender, int(record->AccountClass));
	duckdb_append_varchar(appender, record->Password);
	duckdb_append_int32(appender, record->OfferID);
	duckdb_append_int32(appender, record->IsAllowLogin);
	duckdb_append_int32(appender, record->IsSimulateAccount);
	duckdb_append_int32(appender, int(record->LoginStatus));
	duckdb_append_int32(appender, int(record->InitStatus));
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertPrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForPrimaryAccountRecord(duckdb_prepared_statement statement, PrimaryAccount* record)
{
	duckdb_bind_varchar(statement, 1, record->PrimaryAccountID);
	duckdb_bind_varchar(statement, 2, record->PrimaryAccountName);
	duckdb_bind_int32(statement, 3, int(record->AccountClass));
	duckdb_bind_varchar(statement, 4, record->Password);
	duckdb_bind_int32(statement, 5, record->OfferID);
	duckdb_bind_int32(statement, 6, record->IsAllowLogin);
	duckdb_bind_int32(statement, 7, record->IsSimulateAccount);
	duckdb_bind_int32(statement, 8, int(record->LoginStatus));
	duckdb_bind_int32(statement, 9, int(record->InitStatus));
}
void DuckDB::SetStatementForPrimaryAccountRecordUpdate(duckdb_prepared_statement statement, PrimaryAccount* record)
{
	duckdb_bind_varchar(statement, 1, record->PrimaryAccountName);
	duckdb_bind_int32(statement, 2, int(record->AccountClass));
	duckdb_bind_varchar(statement, 3, record->Password);
	duckdb_bind_int32(statement, 4, record->OfferID);
	duckdb_bind_int32(statement, 5, record->IsAllowLogin);
	duckdb_bind_int32(statement, 6, record->IsSimulateAccount);
	duckdb_bind_int32(statement, 7, int(record->LoginStatus));
	duckdb_bind_int32(statement, 8, int(record->InitStatus));
	duckdb_bind_varchar(statement, 9, record->PrimaryAccountID);
}
void DuckDB::SetStatementForPrimaryAccountPrimaryKey(duckdb_prepared_statement statement, PrimaryAccount* record)
{
	duckdb_bind_varchar(statement, 1, record->PrimaryAccountID);
}
void DuckDB::SetStatementForPrimaryAccountIndexOfferID(duckdb_prepared_statement statement, PrimaryAccount* record)
{
	duckdb_bind_int32(statement, 1, record->OfferID);
}
bool DuckDB::AppendForAccountRecord(duckdb_appender appender, Account* record)
{
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_varchar(appender, record->AccountName);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_int32(appender, int(record->AccountStatus));
	duckdb_append_varchar(appender, record->Password);
	duckdb_append_int32(appender, record->TradeGroupID);
	duckdb_append_int32(appender, record->RiskGroupID);
	duckdb_append_int32(appender, record->CommissionGroupID);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForAccountRecord(duckdb_prepared_statement statement, Account* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
	duckdb_bind_varchar(statement, 2, record->AccountName);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_int32(statement, 4, int(record->AccountStatus));
	duckdb_bind_varchar(statement, 5, record->Password);
	duckdb_bind_int32(statement, 6, record->TradeGroupID);
	duckdb_bind_int32(statement, 7, record->RiskGroupID);
	duckdb_bind_int32(statement, 8, record->CommissionGroupID);
}
void DuckDB::SetStatementForAccountRecordUpdate(duckdb_prepared_statement statement, Account* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountName);
	duckdb_bind_int32(statement, 2, int(record->AccountType));
	duckdb_bind_int32(statement, 3, int(record->AccountStatus));
	duckdb_bind_varchar(statement, 4, record->Password);
	duckdb_bind_int32(statement, 5, record->TradeGroupID);
	duckdb_bind_int32(statement, 6, record->RiskGroupID);
	duckdb_bind_int32(statement, 7, record->CommissionGroupID);
	duckdb_bind_varchar(statement, 8, record->AccountID);
}
void DuckDB::SetStatementForAccountPrimaryKey(duckdb_prepared_statement statement, Account* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
}
bool DuckDB::AppendForCapitalRecord(duckdb_appender appender, Capital* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_double(appender, record->Balance);
	duckdb_append_double(appender, record->PreBalance);
	duckdb_append_double(appender, record->Available);
	duckdb_append_double(appender, record->MarketValue);
	duckdb_append_double(appender, record->CashIn);
	duckdb_append_double(appender, record->CashOut);
	duckdb_append_double(appender, record->Margin);
	duckdb_append_double(appender, record->Commission);
	duckdb_append_double(appender, record->FrozenCash);
	duckdb_append_double(appender, record->FrozenMargin);
	duckdb_append_double(appender, record->FrozenCommission);
	duckdb_append_double(appender, record->CloseProfitByDate);
	duckdb_append_double(appender, record->CloseProfitByTrade);
	duckdb_append_double(appender, record->PositionProfitByDate);
	duckdb_append_double(appender, record->PositionProfitByTrade);
	duckdb_append_double(appender, record->Deposit);
	duckdb_append_double(appender, record->Withdraw);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForCapitalRecord(duckdb_prepared_statement statement, Capital* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_double(statement, 4, record->Balance);
	duckdb_bind_double(statement, 5, record->PreBalance);
	duckdb_bind_double(statement, 6, record->Available);
	duckdb_bind_double(statement, 7, record->MarketValue);
	duckdb_bind_double(statement, 8, record->CashIn);
	duckdb_bind_double(statement, 9, record->CashOut);
	duckdb_bind_double(statement, 10, record->Margin);
	duckdb_bind_double(statement, 11, record->Commission);
	duckdb_bind_double(statement, 12, record->FrozenCash);
	duckdb_bind_double(statement, 13, record->FrozenMargin);
	duckdb_bind_double(statement, 14, record->FrozenCommission);
	duckdb_bind_double(statement, 15, record->CloseProfitByDate);
	duckdb_bind_double(statement, 16, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 17, record->PositionProfitByDate);
	duckdb_bind_double(statement, 18, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 19, record->Deposit);
	duckdb_bind_double(statement, 20, record->Withdraw);
}
void DuckDB::SetStatementForCapitalRecordUpdate(duckdb_prepared_statement statement, Capital* record)
{
	duckdb_bind_int32(statement, 1, int(record->AccountType));
	duckdb_bind_double(statement, 2, record->Balance);
	duckdb_bind_double(statement, 3, record->PreBalance);
	duckdb_bind_double(statement, 4, record->Available);
	duckdb_bind_double(statement, 5, record->MarketValue);
	duckdb_bind_double(statement, 6, record->CashIn);
	duckdb_bind_double(statement, 7, record->CashOut);
	duckdb_bind_double(statement, 8, record->Margin);
	duckdb_bind_double(statement, 9, record->Commission);
	duckdb_bind_double(statement, 10, record->FrozenCash);
	duckdb_bind_double(statement, 11, record->FrozenMargin);
	duckdb_bind_double(statement, 12, record->FrozenCommission);
	duckdb_bind_double(statement, 13, record->CloseProfitByDate);
	duckdb_bind_double(statement, 14, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 15, record->PositionProfitByDate);
	duckdb_bind_double(statement, 16, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 17, record->Deposit);
	duckdb_bind_double(statement, 18, record->Withdraw);
	duckdb_bind_varchar(statement, 19, record->TradingDay);
	duckdb_bind_varchar(statement, 20, record->AccountID);
}
void DuckDB::SetStatementForCapitalPrimaryKey(duckdb_prepared_statement statement, Capital* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
}
void DuckDB::SetStatementForCapitalIndexTradingDay(duckdb_prepared_statement statement, Capital* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
}
bool DuckDB::AppendForPositionRecord(duckdb_appender appender, Position* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, int(record->PosiDirection));
	duckdb_append_int64(appender, record->TotalPosition);
	duckdb_append_int64(appender, record->PositionFrozen);
	duckdb_append_int64(appender, record->TodayPosition);
	duckdb_append_double(appender, record->MarketValue);
	duckdb_append_double(appender, record->CashIn);
	duckdb_append_double(appender, record->CashOut);
	duckdb_append_double(appender, record->Margin);
	duckdb_append_double(appender, record->Commission);
	duckdb_append_double(appender, record->FrozenCash);
	duckdb_append_double(appender, record->FrozenMargin);
	duckdb_append_double(appender, record->FrozenCommission);
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_double(appender, record->CloseProfitByDate);
	duckdb_append_double(appender, record->CloseProfitByTrade);
	duckdb_append_double(appender, record->PositionProfitByDate);
	duckdb_append_double(appender, record->PositionProfitByTrade);
	duckdb_append_double(appender, record->SettlementPrice);
	duckdb_append_double(appender, record->PreSettlementPrice);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertPosition failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForPositionRecord(duckdb_prepared_statement statement, Position* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_varchar(statement, 4, record->ExchangeID);
	duckdb_bind_varchar(statement, 5, record->InstrumentID);
	duckdb_bind_int32(statement, 6, int(record->ProductClass));
	duckdb_bind_int32(statement, 7, int(record->PosiDirection));
	duckdb_bind_int64(statement, 8, record->TotalPosition);
	duckdb_bind_int64(statement, 9, record->PositionFrozen);
	duckdb_bind_int64(statement, 10, record->TodayPosition);
	duckdb_bind_double(statement, 11, record->MarketValue);
	duckdb_bind_double(statement, 12, record->CashIn);
	duckdb_bind_double(statement, 13, record->CashOut);
	duckdb_bind_double(statement, 14, record->Margin);
	duckdb_bind_double(statement, 15, record->Commission);
	duckdb_bind_double(statement, 16, record->FrozenCash);
	duckdb_bind_double(statement, 17, record->FrozenMargin);
	duckdb_bind_double(statement, 18, record->FrozenCommission);
	duckdb_bind_int32(statement, 19, record->VolumeMultiple);
	duckdb_bind_double(statement, 20, record->CloseProfitByDate);
	duckdb_bind_double(statement, 21, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 22, record->PositionProfitByDate);
	duckdb_bind_double(statement, 23, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 24, record->SettlementPrice);
	duckdb_bind_double(statement, 25, record->PreSettlementPrice);
}
void DuckDB::SetStatementForPositionRecordUpdate(duckdb_prepared_statement statement, Position* record)
{
	duckdb_bind_int32(statement, 1, int(record->AccountType));
	duckdb_bind_int32(statement, 2, int(record->ProductClass));
	duckdb_bind_int64(statement, 3, record->TotalPosition);
	duckdb_bind_int64(statement, 4, record->PositionFrozen);
	duckdb_bind_int64(statement, 5, record->TodayPosition);
	duckdb_bind_double(statement, 6, record->MarketValue);
	duckdb_bind_double(statement, 7, record->CashIn);
	duckdb_bind_double(statement, 8, record->CashOut);
	duckdb_bind_double(statement, 9, record->Margin);
	duckdb_bind_double(statement, 10, record->Commission);
	duckdb_bind_double(statement, 11, record->FrozenCash);
	duckdb_bind_double(statement, 12, record->FrozenMargin);
	duckdb_bind_double(statement, 13, record->FrozenCommission);
	duckdb_bind_int32(statement, 14, record->VolumeMultiple);
	duckdb_bind_double(statement, 15, record->CloseProfitByDate);
	duckdb_bind_double(statement, 16, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 17, record->PositionProfitByDate);
	duckdb_bind_double(statement, 18, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 19, record->SettlementPrice);
	duckdb_bind_double(statement, 20, record->PreSettlementPrice);
	duckdb_bind_varchar(statement, 21, record->TradingDay);
	duckdb_bind_varchar(statement, 22, record->AccountID);
	duckdb_bind_varchar(statement, 23, record->ExchangeID);
	duckdb_bind_varchar(statement, 24, record->InstrumentID);
	duckdb_bind_int32(statement, 25, int(record->PosiDirection));
}
void DuckDB::SetStatementForPositionPrimaryKey(duckdb_prepared_statement statement, Position* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_varchar(statement, 3, record->ExchangeID);
	duckdb_bind_varchar(statement, 4, record->InstrumentID);
	duckdb_bind_int32(statement, 5, int(record->PosiDirection));
}
void DuckDB::SetStatementForPositionIndexAccount(duckdb_prepared_statement statement, Position* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
}
void DuckDB::SetStatementForPositionIndexTradingDay(duckdb_prepared_statement statement, Position* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
}
bool DuckDB::AppendForPositionDetailRecord(duckdb_appender appender, PositionDetail* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, int(record->PosiDirection));
	duckdb_append_varchar(appender, record->OpenDate);
	duckdb_append_varchar(appender, record->TradeID);
	duckdb_append_int64(appender, record->Volume);
	duckdb_append_double(appender, record->OpenPrice);
	duckdb_append_double(appender, record->MarketValue);
	duckdb_append_double(appender, record->CashIn);
	duckdb_append_double(appender, record->CashOut);
	duckdb_append_double(appender, record->Margin);
	duckdb_append_double(appender, record->Commission);
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_double(appender, record->CloseProfitByDate);
	duckdb_append_double(appender, record->CloseProfitByTrade);
	duckdb_append_double(appender, record->PositionProfitByDate);
	duckdb_append_double(appender, record->PositionProfitByTrade);
	duckdb_append_double(appender, record->SettlementPrice);
	duckdb_append_double(appender, record->PreSettlementPrice);
	duckdb_append_int64(appender, record->CloseVolume);
	duckdb_append_double(appender, record->CloseAmount);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertPositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForPositionDetailRecord(duckdb_prepared_statement statement, PositionDetail* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_varchar(statement, 4, record->ExchangeID);
	duckdb_bind_varchar(statement, 5, record->InstrumentID);
	duckdb_bind_int32(statement, 6, int(record->ProductClass));
	duckdb_bind_int32(statement, 7, int(record->PosiDirection));
	duckdb_bind_varchar(statement, 8, record->OpenDate);
	duckdb_bind_varchar(statement, 9, record->TradeID);
	duckdb_bind_int64(statement, 10, record->Volume);
	duckdb_bind_double(statement, 11, record->OpenPrice);
	duckdb_bind_double(statement, 12, record->MarketValue);
	duckdb_bind_double(statement, 13, record->CashIn);
	duckdb_bind_double(statement, 14, record->CashOut);
	duckdb_bind_double(statement, 15, record->Margin);
	duckdb_bind_double(statement, 16, record->Commission);
	duckdb_bind_int32(statement, 17, record->VolumeMultiple);
	duckdb_bind_double(statement, 18, record->CloseProfitByDate);
	duckdb_bind_double(statement, 19, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 20, record->PositionProfitByDate);
	duckdb_bind_double(statement, 21, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 22, record->SettlementPrice);
	duckdb_bind_double(statement, 23, record->PreSettlementPrice);
	duckdb_bind_int64(statement, 24, record->CloseVolume);
	duckdb_bind_double(statement, 25, record->CloseAmount);
}
void DuckDB::SetStatementForPositionDetailRecordUpdate(duckdb_prepared_statement statement, PositionDetail* record)
{
	duckdb_bind_int32(statement, 1, int(record->AccountType));
	duckdb_bind_int32(statement, 2, int(record->ProductClass));
	duckdb_bind_int64(statement, 3, record->Volume);
	duckdb_bind_double(statement, 4, record->OpenPrice);
	duckdb_bind_double(statement, 5, record->MarketValue);
	duckdb_bind_double(statement, 6, record->CashIn);
	duckdb_bind_double(statement, 7, record->CashOut);
	duckdb_bind_double(statement, 8, record->Margin);
	duckdb_bind_double(statement, 9, record->Commission);
	duckdb_bind_int32(statement, 10, record->VolumeMultiple);
	duckdb_bind_double(statement, 11, record->CloseProfitByDate);
	duckdb_bind_double(statement, 12, record->CloseProfitByTrade);
	duckdb_bind_double(statement, 13, record->PositionProfitByDate);
	duckdb_bind_double(statement, 14, record->PositionProfitByTrade);
	duckdb_bind_double(statement, 15, record->SettlementPrice);
	duckdb_bind_double(statement, 16, record->PreSettlementPrice);
	duckdb_bind_int64(statement, 17, record->CloseVolume);
	duckdb_bind_double(statement, 18, record->CloseAmount);
	duckdb_bind_varchar(statement, 19, record->TradingDay);
	duckdb_bind_varchar(statement, 20, record->AccountID);
	duckdb_bind_varchar(statement, 21, record->ExchangeID);
	duckdb_bind_varchar(statement, 22, record->InstrumentID);
	duckdb_bind_int32(statement, 23, int(record->PosiDirection));
	duckdb_bind_varchar(statement, 24, record->OpenDate);
	duckdb_bind_varchar(statement, 25, record->TradeID);
}
void DuckDB::SetStatementForPositionDetailPrimaryKey(duckdb_prepared_statement statement, PositionDetail* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_varchar(statement, 3, record->ExchangeID);
	duckdb_bind_varchar(statement, 4, record->InstrumentID);
	duckdb_bind_int32(statement, 5, int(record->PosiDirection));
	duckdb_bind_varchar(statement, 6, record->OpenDate);
	duckdb_bind_varchar(statement, 7, record->TradeID);
}
void DuckDB::SetStatementForPositionDetailIndexTradeMatch(duckdb_prepared_statement statement, PositionDetail* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_varchar(statement, 3, record->ExchangeID);
	duckdb_bind_varchar(statement, 4, record->InstrumentID);
	duckdb_bind_int32(statement, 5, int(record->PosiDirection));
}
void DuckDB::SetStatementForPositionDetailIndexTradingDay(duckdb_prepared_statement statement, PositionDetail* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
}
bool DuckDB::AppendForOrderRecord(duckdb_appender appender, Order* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, record->OrderID);
	duckdb_append_varchar(appender, record->OrderSysID);
	duckdb_append_int32(appender, int(record->Direction));
	duckdb_append_int32(appender, int(record->OffsetFlag));
	duckdb_append_int32(appender, int(record->OrderPriceType));
	duckdb_append_double(appender, record->Price);
	duckdb_append_int64(appender, record->Volume);
	duckdb_append_int64(appender, record->VolumeTotal);
	duckdb_append_int64(appender, record->VolumeTraded);
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_int32(appender, int(record->OrderStatus));
	duckdb_append_varchar(appender, record->OrderDate);
	duckdb_append_varchar(appender, record->OrderTime);
	duckdb_append_varchar(appender, record->CancelDate);
	duckdb_append_varchar(appender, record->CancelTime);
	duckdb_append_int64(appender, record->SessionID);
	duckdb_append_int32(appender, record->ClientOrderID);
	duckdb_append_int32(appender, record->RequestID);
	duckdb_append_int32(appender, record->OfferID);
	duckdb_append_int32(appender, record->TradeGroupID);
	duckdb_append_int32(appender, record->RiskGroupID);
	duckdb_append_int32(appender, record->CommissionGroupID);
	duckdb_append_double(appender, record->FrozenCash);
	duckdb_append_double(appender, record->FrozenMargin);
	duckdb_append_double(appender, record->FrozenCommission);
	duckdb_append_int32(appender, record->RebuildMark);
	duckdb_append_int32(appender, record->IsForceClose);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForOrderRecord(duckdb_prepared_statement statement, Order* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_varchar(statement, 4, record->ExchangeID);
	duckdb_bind_varchar(statement, 5, record->InstrumentID);
	duckdb_bind_int32(statement, 6, int(record->ProductClass));
	duckdb_bind_int32(statement, 7, record->OrderID);
	duckdb_bind_varchar(statement, 8, record->OrderSysID);
	duckdb_bind_int32(statement, 9, int(record->Direction));
	duckdb_bind_int32(statement, 10, int(record->OffsetFlag));
	duckdb_bind_int32(statement, 11, int(record->OrderPriceType));
	duckdb_bind_double(statement, 12, record->Price);
	duckdb_bind_int64(statement, 13, record->Volume);
	duckdb_bind_int64(statement, 14, record->VolumeTotal);
	duckdb_bind_int64(statement, 15, record->VolumeTraded);
	duckdb_bind_int32(statement, 16, record->VolumeMultiple);
	duckdb_bind_int32(statement, 17, int(record->OrderStatus));
	duckdb_bind_varchar(statement, 18, record->OrderDate);
	duckdb_bind_varchar(statement, 19, record->OrderTime);
	duckdb_bind_varchar(statement, 20, record->CancelDate);
	duckdb_bind_varchar(statement, 21, record->CancelTime);
	duckdb_bind_int64(statement, 22, record->SessionID);
	duckdb_bind_int32(statement, 23, record->ClientOrderID);
	duckdb_bind_int32(statement, 24, record->RequestID);
	duckdb_bind_int32(statement, 25, record->OfferID);
	duckdb_bind_int32(statement, 26, record->TradeGroupID);
	duckdb_bind_int32(statement, 27, record->RiskGroupID);
	duckdb_bind_int32(statement, 28, record->CommissionGroupID);
	duckdb_bind_double(statement, 29, record->FrozenCash);
	duckdb_bind_double(statement, 30, record->FrozenMargin);
	duckdb_bind_double(statement, 31, record->FrozenCommission);
	duckdb_bind_int32(statement, 32, record->RebuildMark);
	duckdb_bind_int32(statement, 33, record->IsForceClose);
}
void DuckDB::SetStatementForOrderRecordUpdate(duckdb_prepared_statement statement, Order* record)
{
	duckdb_bind_int32(statement, 1, int(record->AccountType));
	duckdb_bind_int32(statement, 2, int(record->ProductClass));
	duckdb_bind_varchar(statement, 3, record->OrderSysID);
	duckdb_bind_int32(statement, 4, int(record->Direction));
	duckdb_bind_int32(statement, 5, int(record->OffsetFlag));
	duckdb_bind_int32(statement, 6, int(record->OrderPriceType));
	duckdb_bind_double(statement, 7, record->Price);
	duckdb_bind_int64(statement, 8, record->Volume);
	duckdb_bind_int64(statement, 9, record->VolumeTotal);
	duckdb_bind_int64(statement, 10, record->VolumeTraded);
	duckdb_bind_int32(statement, 11, record->VolumeMultiple);
	duckdb_bind_int32(statement, 12, int(record->OrderStatus));
	duckdb_bind_varchar(statement, 13, record->OrderDate);
	duckdb_bind_varchar(statement, 14, record->OrderTime);
	duckdb_bind_varchar(statement, 15, record->CancelDate);
	duckdb_bind_varchar(statement, 16, record->CancelTime);
	duckdb_bind_int64(statement, 17, record->SessionID);
	duckdb_bind_int32(statement, 18, record->ClientOrderID);
	duckdb_bind_int32(statement, 19, record->RequestID);
	duckdb_bind_int32(statement, 20, record->OfferID);
	duckdb_bind_int32(statement, 21, record->TradeGroupID);
	duckdb_bind_int32(statement, 22, record->RiskGroupID);
	duckdb_bind_int32(statement, 23, record->CommissionGroupID);
	duckdb_bind_double(statement, 24, record->FrozenCash);
	duckdb_bind_double(statement, 25, record->FrozenMargin);
	duckdb_bind_double(statement, 26, record->FrozenCommission);
	duckdb_bind_int32(statement, 27, record->RebuildMark);
	duckdb_bind_int32(statement, 28, record->IsForceClose);
	duckdb_bind_varchar(statement, 29, record->TradingDay);
	duckdb_bind_varchar(statement, 30, record->AccountID);
	duckdb_bind_varchar(statement, 31, record->ExchangeID);
	duckdb_bind_varchar(statement, 32, record->InstrumentID);
	duckdb_bind_int32(statement, 33, record->OrderID);
}
void DuckDB::SetStatementForOrderPrimaryKey(duckdb_prepared_statement statement, Order* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_varchar(statement, 3, record->ExchangeID);
	duckdb_bind_varchar(statement, 4, record->InstrumentID);
	duckdb_bind_int32(statement, 5, record->OrderID);
}
void DuckDB::SetStatementForOrderIndexAccountID(duckdb_prepared_statement statement, Order* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
}
bool DuckDB::AppendForTradeRecord(duckdb_appender appender, Trade* record)
{
	duckdb_append_varchar(appender, record->TradingDay);
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int32(appender, int(record->AccountType));
	duckdb_append_varchar(appender, record->ExchangeID);
	duckdb_append_varchar(appender, record->InstrumentID);
	duckdb_append_int32(appender, int(record->ProductClass));
	duckdb_append_int32(appender, record->OrderID);
	duckdb_append_varchar(appender, record->OrderSysID);
	duckdb_append_varchar(appender, record->TradeID);
	duckdb_append_int32(appender, int(record->Direction));
	duckdb_append_int32(appender, int(record->OffsetFlag));
	duckdb_append_double(appender, record->Price);
	duckdb_append_int64(appender, record->Volume);
	duckdb_append_int32(appender, record->VolumeMultiple);
	duckdb_append_double(appender, record->TradeAmount);
	duckdb_append_double(appender, record->Commission);
	duckdb_append_varchar(appender, record->TradeDate);
	duckdb_append_varchar(appender, record->TradeTime);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForTradeRecord(duckdb_prepared_statement statement, Trade* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
	duckdb_bind_int32(statement, 3, int(record->AccountType));
	duckdb_bind_varchar(statement, 4, record->ExchangeID);
	duckdb_bind_varchar(statement, 5, record->InstrumentID);
	duckdb_bind_int32(statement, 6, int(record->ProductClass));
	duckdb_bind_int32(statement, 7, record->OrderID);
	duckdb_bind_varchar(statement, 8, record->OrderSysID);
	duckdb_bind_varchar(statement, 9, record->TradeID);
	duckdb_bind_int32(statement, 10, int(record->Direction));
	duckdb_bind_int32(statement, 11, int(record->OffsetFlag));
	duckdb_bind_double(statement, 12, record->Price);
	duckdb_bind_int64(statement, 13, record->Volume);
	duckdb_bind_int32(statement, 14, record->VolumeMultiple);
	duckdb_bind_double(statement, 15, record->TradeAmount);
	duckdb_bind_double(statement, 16, record->Commission);
	duckdb_bind_varchar(statement, 17, record->TradeDate);
	duckdb_bind_varchar(statement, 18, record->TradeTime);
}
void DuckDB::SetStatementForTradeRecordUpdate(duckdb_prepared_statement statement, Trade* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
	duckdb_bind_int32(statement, 2, int(record->AccountType));
	duckdb_bind_varchar(statement, 3, record->InstrumentID);
	duckdb_bind_int32(statement, 4, int(record->ProductClass));
	duckdb_bind_int32(statement, 5, record->OrderID);
	duckdb_bind_varchar(statement, 6, record->OrderSysID);
	duckdb_bind_int32(statement, 7, int(record->OffsetFlag));
	duckdb_bind_double(statement, 8, record->Price);
	duckdb_bind_int64(statement, 9, record->Volume);
	duckdb_bind_int32(statement, 10, record->VolumeMultiple);
	duckdb_bind_double(statement, 11, record->TradeAmount);
	duckdb_bind_double(statement, 12, record->Commission);
	duckdb_bind_varchar(statement, 13, record->TradeDate);
	duckdb_bind_varchar(statement, 14, record->TradeTime);
	duckdb_bind_varchar(statement, 15, record->TradingDay);
	duckdb_bind_varchar(statement, 16, record->ExchangeID);
	duckdb_bind_varchar(statement, 17, record->TradeID);
	duckdb_bind_int32(statement, 18, int(record->Direction));
}
void DuckDB::SetStatementForTradePrimaryKey(duckdb_prepared_statement statement, Trade* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->ExchangeID);
	duckdb_bind_varchar(statement, 3, record->TradeID);
	duckdb_bind_int32(statement, 4, int(record->Direction));
}
void DuckDB::SetStatementForTradeIndexAccountID(duckdb_prepared_statement statement, Trade* record)
{
	duckdb_bind_varchar(statement, 1, record->TradingDay);
	duckdb_bind_varchar(statement, 2, record->AccountID);
}
bool DuckDB::AppendForAccountLoginSessionRecord(duckdb_appender appender, AccountLoginSession* record)
{
	duckdb_append_varchar(appender, record->AccountID);
	duckdb_append_int64(appender, record->SessionID);
	duckdb_append_varchar(appender, record->IPAddress);
	if (duckdb_appender_end_row(appender) != DuckDBSuccess)
	{
		WriteLog(LogLevel::Warning, "InsertAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), duckdb_appender_error(appender));
		return false;
	}
	return true;
}
void DuckDB::SetStatementForAccountLoginSessionRecord(duckdb_prepared_statement statement, AccountLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
	duckdb_bind_int64(statement, 2, record->SessionID);
	duckdb_bind_varchar(statement, 3, record->IPAddress);
}
void DuckDB::SetStatementForAccountLoginSessionRecordUpdate(duckdb_prepared_statement statement, AccountLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
	duckdb_bind_varchar(statement, 2, record->IPAddress);
	duckdb_bind_int64(statement, 3, record->SessionID);
}
void DuckDB::SetStatementForAccountLoginSessionPrimaryKey(duckdb_prepared_statement statement, AccountLoginSession* record)
{
	duckdb_bind_int64(statement, 1, record->SessionID);
}
void DuckDB::SetStatementForAccountLoginSessionIndexAccountID(duckdb_prepared_statement statement, AccountLoginSession* record)
{
	duckdb_bind_varchar(statement, 1, record->AccountID);
}

