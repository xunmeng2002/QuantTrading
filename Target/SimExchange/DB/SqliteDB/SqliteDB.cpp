#include "SqliteDB.h"
#include "Constant.h"
#include "Logger.h"
#include "Utility.h"
#include "TimeUtility.h"
#include <string.h>
#include <cstring>

using namespace mdb;
using namespace std;
using namespace std::chrono;

SqliteDB::SqliteDB(const std::string& dbName)
	:m_DBName(dbName), m_DB(nullptr)
{
	m_SqlBuff = new char[BuffSize];

	m_TradingDayInsertStatement = nullptr;
	m_TradingDayDeleteStatement = nullptr;
	m_TradingDayUpdateStatement = nullptr;
	m_TradingDaySelectStatement = nullptr;
	m_TradingDayTruncateStatement = nullptr;

	m_ExchangeInsertStatement = nullptr;
	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_ProductInsertStatement = nullptr;
	m_ProductDeleteStatement = nullptr;
	m_ProductUpdateStatement = nullptr;
	m_ProductSelectStatement = nullptr;
	m_ProductTruncateStatement = nullptr;

	m_DepthMarketDataInsertStatement = nullptr;
	m_DepthMarketDataDeleteStatement = nullptr;
	m_DepthMarketDataUpdateStatement = nullptr;
	m_DepthMarketDataSelectStatement = nullptr;
	m_DepthMarketDataTruncateStatement = nullptr;

	m_SEBrokerInsertStatement = nullptr;
	m_SEBrokerDeleteStatement = nullptr;
	m_SEBrokerUpdateStatement = nullptr;
	m_SEBrokerSelectStatement = nullptr;
	m_SEBrokerTruncateStatement = nullptr;

	m_SEInstrumentInsertStatement = nullptr;
	m_SEInstrumentDeleteStatement = nullptr;
	m_SEInstrumentUpdateStatement = nullptr;
	m_SEInstrumentSelectStatement = nullptr;
	m_SEInstrumentTruncateStatement = nullptr;

	m_SEOrderInsertStatement = nullptr;
	m_SEOrderDeleteStatement = nullptr;
	m_SEOrderUpdateStatement = nullptr;
	m_SEOrderSelectStatement = nullptr;
	m_SEOrderTruncateStatement = nullptr;

	m_SETradeInsertStatement = nullptr;
	m_SETradeDeleteStatement = nullptr;
	m_SETradeUpdateStatement = nullptr;
	m_SETradeSelectStatement = nullptr;
	m_SETradeTruncateStatement = nullptr;

	m_SEBrokerLoginSessionInsertStatement = nullptr;
	m_SEBrokerLoginSessionDeleteStatement = nullptr;
	m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement = nullptr;
	m_SEBrokerLoginSessionUpdateStatement = nullptr;
	m_SEBrokerLoginSessionSelectStatement = nullptr;
	m_SEBrokerLoginSessionTruncateStatement = nullptr;

}
SqliteDB::~SqliteDB()
{
	delete[] m_SqlBuff;
	DisConnect();
	if (m_DB != nullptr)
	{
		sqlite3_close(m_DB);
	}
}
bool SqliteDB::Connect()
{
	int result = sqlite3_open(m_DBName.c_str(), &m_DB);
	if (result != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "Open SqliteDB Failed.");
		return false;
	}
	return true;
}
void SqliteDB::DisConnect()
{
	if (m_DB != nullptr)
	{
		sqlite3_close(m_DB);
		m_DB = nullptr;
	}
	if (m_TradingDayInsertStatement != nullptr)
	{
		sqlite3_finalize(m_TradingDayInsertStatement);
		m_TradingDayInsertStatement = nullptr;
	}
	if (m_TradingDayDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_TradingDayDeleteStatement);
		m_TradingDayDeleteStatement = nullptr;
	}
	if (m_TradingDayUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_TradingDayUpdateStatement);
		m_TradingDayUpdateStatement = nullptr;
	}
	if (m_TradingDaySelectStatement != nullptr)
	{
		sqlite3_finalize(m_TradingDaySelectStatement);
		m_TradingDaySelectStatement = nullptr;
	}
	if (m_TradingDayTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_TradingDayTruncateStatement);
		m_TradingDayTruncateStatement = nullptr;
	}
	if (m_ExchangeInsertStatement != nullptr)
	{
		sqlite3_finalize(m_ExchangeInsertStatement);
		m_ExchangeInsertStatement = nullptr;
	}
	if (m_ExchangeDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_ExchangeDeleteStatement);
		m_ExchangeDeleteStatement = nullptr;
	}
	if (m_ExchangeUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_ExchangeUpdateStatement);
		m_ExchangeUpdateStatement = nullptr;
	}
	if (m_ExchangeSelectStatement != nullptr)
	{
		sqlite3_finalize(m_ExchangeSelectStatement);
		m_ExchangeSelectStatement = nullptr;
	}
	if (m_ExchangeTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_ExchangeTruncateStatement);
		m_ExchangeTruncateStatement = nullptr;
	}
	if (m_ProductInsertStatement != nullptr)
	{
		sqlite3_finalize(m_ProductInsertStatement);
		m_ProductInsertStatement = nullptr;
	}
	if (m_ProductDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_ProductDeleteStatement);
		m_ProductDeleteStatement = nullptr;
	}
	if (m_ProductUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_ProductUpdateStatement);
		m_ProductUpdateStatement = nullptr;
	}
	if (m_ProductSelectStatement != nullptr)
	{
		sqlite3_finalize(m_ProductSelectStatement);
		m_ProductSelectStatement = nullptr;
	}
	if (m_ProductTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_ProductTruncateStatement);
		m_ProductTruncateStatement = nullptr;
	}
	if (m_DepthMarketDataInsertStatement != nullptr)
	{
		sqlite3_finalize(m_DepthMarketDataInsertStatement);
		m_DepthMarketDataInsertStatement = nullptr;
	}
	if (m_DepthMarketDataDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_DepthMarketDataDeleteStatement);
		m_DepthMarketDataDeleteStatement = nullptr;
	}
	if (m_DepthMarketDataUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_DepthMarketDataUpdateStatement);
		m_DepthMarketDataUpdateStatement = nullptr;
	}
	if (m_DepthMarketDataSelectStatement != nullptr)
	{
		sqlite3_finalize(m_DepthMarketDataSelectStatement);
		m_DepthMarketDataSelectStatement = nullptr;
	}
	if (m_DepthMarketDataTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_DepthMarketDataTruncateStatement);
		m_DepthMarketDataTruncateStatement = nullptr;
	}
	if (m_SEBrokerInsertStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerInsertStatement);
		m_SEBrokerInsertStatement = nullptr;
	}
	if (m_SEBrokerDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerDeleteStatement);
		m_SEBrokerDeleteStatement = nullptr;
	}
	if (m_SEBrokerUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerUpdateStatement);
		m_SEBrokerUpdateStatement = nullptr;
	}
	if (m_SEBrokerSelectStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerSelectStatement);
		m_SEBrokerSelectStatement = nullptr;
	}
	if (m_SEBrokerTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerTruncateStatement);
		m_SEBrokerTruncateStatement = nullptr;
	}
	if (m_SEInstrumentInsertStatement != nullptr)
	{
		sqlite3_finalize(m_SEInstrumentInsertStatement);
		m_SEInstrumentInsertStatement = nullptr;
	}
	if (m_SEInstrumentDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_SEInstrumentDeleteStatement);
		m_SEInstrumentDeleteStatement = nullptr;
	}
	if (m_SEInstrumentUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_SEInstrumentUpdateStatement);
		m_SEInstrumentUpdateStatement = nullptr;
	}
	if (m_SEInstrumentSelectStatement != nullptr)
	{
		sqlite3_finalize(m_SEInstrumentSelectStatement);
		m_SEInstrumentSelectStatement = nullptr;
	}
	if (m_SEInstrumentTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_SEInstrumentTruncateStatement);
		m_SEInstrumentTruncateStatement = nullptr;
	}
	if (m_SEOrderInsertStatement != nullptr)
	{
		sqlite3_finalize(m_SEOrderInsertStatement);
		m_SEOrderInsertStatement = nullptr;
	}
	if (m_SEOrderDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_SEOrderDeleteStatement);
		m_SEOrderDeleteStatement = nullptr;
	}
	if (m_SEOrderUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_SEOrderUpdateStatement);
		m_SEOrderUpdateStatement = nullptr;
	}
	if (m_SEOrderSelectStatement != nullptr)
	{
		sqlite3_finalize(m_SEOrderSelectStatement);
		m_SEOrderSelectStatement = nullptr;
	}
	if (m_SEOrderTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_SEOrderTruncateStatement);
		m_SEOrderTruncateStatement = nullptr;
	}
	if (m_SETradeInsertStatement != nullptr)
	{
		sqlite3_finalize(m_SETradeInsertStatement);
		m_SETradeInsertStatement = nullptr;
	}
	if (m_SETradeDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_SETradeDeleteStatement);
		m_SETradeDeleteStatement = nullptr;
	}
	if (m_SETradeUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_SETradeUpdateStatement);
		m_SETradeUpdateStatement = nullptr;
	}
	if (m_SETradeSelectStatement != nullptr)
	{
		sqlite3_finalize(m_SETradeSelectStatement);
		m_SETradeSelectStatement = nullptr;
	}
	if (m_SETradeTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_SETradeTruncateStatement);
		m_SETradeTruncateStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionInsertStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionInsertStatement);
		m_SEBrokerLoginSessionInsertStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionDeleteStatement);
		m_SEBrokerLoginSessionDeleteStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement);
		m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionUpdateStatement);
		m_SEBrokerLoginSessionUpdateStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionSelectStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionSelectStatement);
		m_SEBrokerLoginSessionSelectStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_SEBrokerLoginSessionTruncateStatement);
		m_SEBrokerLoginSessionTruncateStatement = nullptr;
	}
}
void SqliteDB::InitDB()
{
	Exec("Truncate Table t_TradingDay;");
	Exec("Insert Into t_TradingDay select * from Init.t_TradingDay;");
	Exec("Truncate Table t_Exchange;");
	Exec("Insert Into t_Exchange select * from Init.t_Exchange;");
	Exec("Truncate Table t_Product;");
	Exec("Insert Into t_Product select * from Init.t_Product;");
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Truncate Table t_SEBroker;");
	Exec("Insert Into t_SEBroker select * from Init.t_SEBroker;");
	Exec("Truncate Table t_SEInstrument;");
	Exec("Insert Into t_SEInstrument select * from Init.t_SEInstrument;");
	Exec("Truncate Table t_SEOrder;");
	Exec("Insert Into t_SEOrder select * from Init.t_SEOrder;");
	Exec("Truncate Table t_SETrade;");
	Exec("Insert Into t_SETrade select * from Init.t_SETrade;");
	Exec("Truncate Table t_SEBrokerLoginSession;");
	Exec("Insert Into t_SEBrokerLoginSession select * from Init.t_SEBrokerLoginSession;");
}
void SqliteDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateSEBrokerLoginSession();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateDepthMarketData();
	TruncateSEBroker();
	TruncateSEInstrument();
	TruncateSEOrder();
	TruncateSETrade();
	TruncateSEBrokerLoginSession();
}
bool SqliteDB::Exec(const char* sql)
{
	char* t_ErrorMsg;
	auto ret = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "Sqlitedb::Exec Failed. Sql:%s, Error: %s\n", sql, t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
		return false;
	}
	return true;
}

void SqliteDB::InsertTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_TradingDay Values(?, ?, ?);", -1, &m_TradingDayInsertStatement, nullptr);
	}
	SetStatementForTradingDayRecord(m_TradingDayInsertStatement, record);
	
	auto rc = sqlite3_step(m_TradingDayInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradingDayInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertTradingDay Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertTradingDay(std::list<TradingDay*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_TradingDay Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertTradingDay Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_TradingDay Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertTradingDay Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertTradingDay RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_TradingDay where PK = ?;", -1, &m_TradingDayDeleteStatement, nullptr);
	}
	SetStatementForTradingDayPrimaryKey(m_TradingDayDeleteStatement, record->PK);

	auto rc = sqlite3_step(m_TradingDayDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradingDayDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTradingDay Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_TradingDay set CurrTradingDay = ?, PreTradingDay = ? where PK = ?;", -1, &m_TradingDayUpdateStatement, nullptr);
	}
	SetStatementForTradingDayRecordUpdate(m_TradingDayUpdateStatement, record);
	
	auto rc = sqlite3_step(m_TradingDayUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateTradingDay failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradingDayUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTradingDay Spend:%lldms", duration);
	}
}
void SqliteDB::SelectTradingDay(std::list<TradingDay*>& records)
{
	auto start = steady_clock::now();
	if (m_TradingDaySelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_TradingDay;", -1, &m_TradingDaySelectStatement, nullptr);
	}

	while (sqlite3_step(m_TradingDaySelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_TradingDaySelectStatement, records);
	}
	sqlite3_reset(m_TradingDaySelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTradingDay Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateTradingDay()
{
	auto start = steady_clock::now();
	if (m_TradingDayTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_TradingDay;", -1, &m_TradingDayTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_TradingDayTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateTradingDay failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradingDayTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateTradingDay Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Exchange Values(?, ?);", -1, &m_ExchangeInsertStatement, nullptr);
	}
	SetStatementForExchangeRecord(m_ExchangeInsertStatement, record);
	
	auto rc = sqlite3_step(m_ExchangeInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ExchangeInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertExchange Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertExchange(std::list<Exchange*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Exchange Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertExchange Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Exchange Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertExchange Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertExchange RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Exchange where ExchangeID = ?;", -1, &m_ExchangeDeleteStatement, nullptr);
	}
	SetStatementForExchangePrimaryKey(m_ExchangeDeleteStatement, record->ExchangeID);

	auto rc = sqlite3_step(m_ExchangeDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ExchangeDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteExchange Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Exchange set ExchangeName = ? where ExchangeID = ?;", -1, &m_ExchangeUpdateStatement, nullptr);
	}
	SetStatementForExchangeRecordUpdate(m_ExchangeUpdateStatement, record);
	
	auto rc = sqlite3_step(m_ExchangeUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateExchange failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ExchangeUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateExchange Spend:%lldms", duration);
	}
}
void SqliteDB::SelectExchange(std::list<Exchange*>& records)
{
	auto start = steady_clock::now();
	if (m_ExchangeSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Exchange;", -1, &m_ExchangeSelectStatement, nullptr);
	}

	while (sqlite3_step(m_ExchangeSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_ExchangeSelectStatement, records);
	}
	sqlite3_reset(m_ExchangeSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectExchange Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateExchange()
{
	auto start = steady_clock::now();
	if (m_ExchangeTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Exchange;", -1, &m_ExchangeTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_ExchangeTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateExchange failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ExchangeTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateExchange Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Product Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_ProductInsertStatement, nullptr);
	}
	SetStatementForProductRecord(m_ProductInsertStatement, record);
	
	auto rc = sqlite3_step(m_ProductInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ProductInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertProduct Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertProduct(std::list<Product*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Product Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertProduct Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Product Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertProduct Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertProduct RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Product where ExchangeID = ? and ProductID = ?;", -1, &m_ProductDeleteStatement, nullptr);
	}
	SetStatementForProductPrimaryKey(m_ProductDeleteStatement, record->ExchangeID, record->ProductID);

	auto rc = sqlite3_step(m_ProductDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ProductDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteProduct Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Product set ProductName = ?, ProductClass = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and ProductID = ?;", -1, &m_ProductUpdateStatement, nullptr);
	}
	SetStatementForProductRecordUpdate(m_ProductUpdateStatement, record);
	
	auto rc = sqlite3_step(m_ProductUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ProductUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct Spend:%lldms", duration);
	}
}
void SqliteDB::SelectProduct(std::list<Product*>& records)
{
	auto start = steady_clock::now();
	if (m_ProductSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Product;", -1, &m_ProductSelectStatement, nullptr);
	}

	while (sqlite3_step(m_ProductSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_ProductSelectStatement, records);
	}
	sqlite3_reset(m_ProductSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectProduct Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateProduct()
{
	auto start = steady_clock::now();
	if (m_ProductTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Product;", -1, &m_ProductTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_ProductTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateProduct failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_ProductTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateProduct Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_DepthMarketData Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_DepthMarketDataInsertStatement, nullptr);
	}
	SetStatementForDepthMarketDataRecord(m_DepthMarketDataInsertStatement, record);
	
	auto rc = sqlite3_step(m_DepthMarketDataInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_DepthMarketDataInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertDepthMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertDepthMarketData(std::list<DepthMarketData*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_DepthMarketData Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_DepthMarketData Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_DepthMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;", -1, &m_DepthMarketDataDeleteStatement, nullptr);
	}
	SetStatementForDepthMarketDataPrimaryKey(m_DepthMarketDataDeleteStatement, record->TradingDay, record->ExchangeID, record->InstrumentID);

	auto rc = sqlite3_step(m_DepthMarketDataDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_DepthMarketDataDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteDepthMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_DepthMarketData set UpdateTs = ?, LastPrice = ?, PreSettlementPrice = ?, PreClosePrice = ?, PreOpenInterest = ?, OpenPrice = ?, HighestPrice = ?, LowestPrice = ?, ClosePrice = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ?, SettlementPrice = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, AveragePrice = ?, AskPrice1 = ?, AskPrice2 = ?, AskPrice3 = ?, AskPrice4 = ?, AskPrice5 = ?, AskPrice6 = ?, AskPrice7 = ?, AskPrice8 = ?, AskPrice9 = ?, AskPrice10 = ?, AskVolume1 = ?, AskVolume2 = ?, AskVolume3 = ?, AskVolume4 = ?, AskVolume5 = ?, AskVolume6 = ?, AskVolume7 = ?, AskVolume8 = ?, AskVolume9 = ?, AskVolume10 = ?, BidPrice1 = ?, BidPrice2 = ?, BidPrice3 = ?, BidPrice4 = ?, BidPrice5 = ?, BidPrice6 = ?, BidPrice7 = ?, BidPrice8 = ?, BidPrice9 = ?, BidPrice10 = ?, BidVolume1 = ?, BidVolume2 = ?, BidVolume3 = ?, BidVolume4 = ?, BidVolume5 = ?, BidVolume6 = ?, BidVolume7 = ?, BidVolume8 = ?, BidVolume9 = ?, BidVolume10 = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;", -1, &m_DepthMarketDataUpdateStatement, nullptr);
	}
	SetStatementForDepthMarketDataRecordUpdate(m_DepthMarketDataUpdateStatement, record);
	
	auto rc = sqlite3_step(m_DepthMarketDataUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_DepthMarketDataUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::SelectDepthMarketData(std::list<DepthMarketData*>& records)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_DepthMarketData;", -1, &m_DepthMarketDataSelectStatement, nullptr);
	}

	while (sqlite3_step(m_DepthMarketDataSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_DepthMarketDataSelectStatement, records);
	}
	sqlite3_reset(m_DepthMarketDataSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectDepthMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateDepthMarketData()
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_DepthMarketData;", -1, &m_DepthMarketDataTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_DepthMarketDataTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateDepthMarketData failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_DepthMarketDataTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateDepthMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_SEBroker Values(?, ?, ?);", -1, &m_SEBrokerInsertStatement, nullptr);
	}
	SetStatementForSEBrokerRecord(m_SEBrokerInsertStatement, record);
	
	auto rc = sqlite3_step(m_SEBrokerInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertSEBroker failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEBroker Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertSEBroker(std::list<SEBroker*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEBroker Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertSEBroker Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEBroker Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertSEBroker Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEBroker RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEBroker where BrokerID = ?;", -1, &m_SEBrokerDeleteStatement, nullptr);
	}
	SetStatementForSEBrokerPrimaryKey(m_SEBrokerDeleteStatement, record->BrokerID);

	auto rc = sqlite3_step(m_SEBrokerDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBroker failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBroker Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_SEBroker set BrokerName = ?, Password = ? where BrokerID = ?;", -1, &m_SEBrokerUpdateStatement, nullptr);
	}
	SetStatementForSEBrokerRecordUpdate(m_SEBrokerUpdateStatement, record);
	
	auto rc = sqlite3_step(m_SEBrokerUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBroker failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBroker Spend:%lldms", duration);
	}
}
void SqliteDB::SelectSEBroker(std::list<SEBroker*>& records)
{
	auto start = steady_clock::now();
	if (m_SEBrokerSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_SEBroker;", -1, &m_SEBrokerSelectStatement, nullptr);
	}

	while (sqlite3_step(m_SEBrokerSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_SEBrokerSelectStatement, records);
	}
	sqlite3_reset(m_SEBrokerSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEBroker Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateSEBroker()
{
	auto start = steady_clock::now();
	if (m_SEBrokerTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEBroker;", -1, &m_SEBrokerTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_SEBrokerTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateSEBroker failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateSEBroker Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_SEInstrument Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_SEInstrumentInsertStatement, nullptr);
	}
	SetStatementForSEInstrumentRecord(m_SEInstrumentInsertStatement, record);
	
	auto rc = sqlite3_step(m_SEInstrumentInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertSEInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEInstrumentInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertSEInstrument(std::list<SEInstrument*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEInstrument Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertSEInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEInstrument Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertSEInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEInstrument where ExchangeID = ? and InstrumentID = ?;", -1, &m_SEInstrumentDeleteStatement, nullptr);
	}
	SetStatementForSEInstrumentPrimaryKey(m_SEInstrumentDeleteStatement, record->ExchangeID, record->InstrumentID);

	auto rc = sqlite3_step(m_SEInstrumentDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSEInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEInstrumentDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_SEInstrument set ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, ProductClass = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, VolumeMultiple = ?, PriceTick = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;", -1, &m_SEInstrumentUpdateStatement, nullptr);
	}
	SetStatementForSEInstrumentRecordUpdate(m_SEInstrumentUpdateStatement, record);
	
	auto rc = sqlite3_step(m_SEInstrumentUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateSEInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEInstrumentUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::SelectSEInstrument(std::list<SEInstrument*>& records)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_SEInstrument;", -1, &m_SEInstrumentSelectStatement, nullptr);
	}

	while (sqlite3_step(m_SEInstrumentSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_SEInstrumentSelectStatement, records);
	}
	sqlite3_reset(m_SEInstrumentSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateSEInstrument()
{
	auto start = steady_clock::now();
	if (m_SEInstrumentTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEInstrument;", -1, &m_SEInstrumentTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_SEInstrumentTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateSEInstrument failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEInstrumentTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateSEInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_SEOrder Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_SEOrderInsertStatement, nullptr);
	}
	SetStatementForSEOrderRecord(m_SEOrderInsertStatement, record);
	
	auto rc = sqlite3_step(m_SEOrderInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertSEOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEOrderInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEOrder Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertSEOrder(std::list<SEOrder*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEOrder Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertSEOrder Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEOrder Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertSEOrder Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEOrder RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEOrder where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", -1, &m_SEOrderDeleteStatement, nullptr);
	}
	SetStatementForSEOrderPrimaryKey(m_SEOrderDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->OrderID);

	auto rc = sqlite3_step(m_SEOrderDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSEOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEOrderDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEOrder Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_SEOrder set BrokerID = ?, ProductClass = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", -1, &m_SEOrderUpdateStatement, nullptr);
	}
	SetStatementForSEOrderRecordUpdate(m_SEOrderUpdateStatement, record);
	
	auto rc = sqlite3_step(m_SEOrderUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateSEOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEOrderUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEOrder Spend:%lldms", duration);
	}
}
void SqliteDB::SelectSEOrder(std::list<SEOrder*>& records)
{
	auto start = steady_clock::now();
	if (m_SEOrderSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_SEOrder;", -1, &m_SEOrderSelectStatement, nullptr);
	}

	while (sqlite3_step(m_SEOrderSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_SEOrderSelectStatement, records);
	}
	sqlite3_reset(m_SEOrderSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEOrder Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateSEOrder()
{
	auto start = steady_clock::now();
	if (m_SEOrderTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEOrder;", -1, &m_SEOrderTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_SEOrderTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateSEOrder failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEOrderTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateSEOrder Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_SETrade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_SETradeInsertStatement, nullptr);
	}
	SetStatementForSETradeRecord(m_SETradeInsertStatement, record);
	
	auto rc = sqlite3_step(m_SETradeInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertSETrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SETradeInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSETrade Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertSETrade(std::list<SETrade*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SETrade Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertSETrade Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SETrade Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertSETrade Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSETrade RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SETrade where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", -1, &m_SETradeDeleteStatement, nullptr);
	}
	SetStatementForSETradePrimaryKey(m_SETradeDeleteStatement, record->TradingDay, record->ExchangeID, record->TradeID, record->Direction);

	auto rc = sqlite3_step(m_SETradeDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSETrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SETradeDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSETrade Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_SETrade set BrokerID = ?, AccountID = ?, InstrumentID = ?, ProductClass = ?, OrderID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", -1, &m_SETradeUpdateStatement, nullptr);
	}
	SetStatementForSETradeRecordUpdate(m_SETradeUpdateStatement, record);
	
	auto rc = sqlite3_step(m_SETradeUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateSETrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SETradeUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSETrade Spend:%lldms", duration);
	}
}
void SqliteDB::SelectSETrade(std::list<SETrade*>& records)
{
	auto start = steady_clock::now();
	if (m_SETradeSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_SETrade;", -1, &m_SETradeSelectStatement, nullptr);
	}

	while (sqlite3_step(m_SETradeSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_SETradeSelectStatement, records);
	}
	sqlite3_reset(m_SETradeSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSETrade Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateSETrade()
{
	auto start = steady_clock::now();
	if (m_SETradeTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SETrade;", -1, &m_SETradeTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_SETradeTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateSETrade failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SETradeTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateSETrade Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_SEBrokerLoginSession Values(?, ?, ?);", -1, &m_SEBrokerLoginSessionInsertStatement, nullptr);
	}
	SetStatementForSEBrokerLoginSessionRecord(m_SEBrokerLoginSessionInsertStatement, record);
	
	auto rc = sqlite3_step(m_SEBrokerLoginSessionInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertSEBrokerLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerLoginSessionInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertSEBrokerLoginSession(std::list<SEBrokerLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEBrokerLoginSession Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	char* t_ErrorMsg;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > BuffSize - 1024)
		{
			m_SqlBuff[n - 1] = ';';
			auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
			if (ret != SQLITE_OK)
			{
				WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEBrokerLoginSession Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEBrokerLoginSession where SessionID = ?;", -1, &m_SEBrokerLoginSessionDeleteStatement, nullptr);
	}
	SetStatementForSEBrokerLoginSessionPrimaryKey(m_SEBrokerLoginSessionDeleteStatement, record->SessionID);

	auto rc = sqlite3_step(m_SEBrokerLoginSessionDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerLoginSessionDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::DeleteSEBrokerLoginSessionByBrokerIDIndex(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEBrokerLoginSession where BrokerID = ?;", -1, &m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement, nullptr);
	}
	SetStatementForSEBrokerLoginSessionIndexBrokerID(m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSessionByBrokerIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSessionByBrokerIDIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_SEBrokerLoginSession set BrokerID = ?, IPAddress = ? where SessionID = ?;", -1, &m_SEBrokerLoginSessionUpdateStatement, nullptr);
	}
	SetStatementForSEBrokerLoginSessionRecordUpdate(m_SEBrokerLoginSessionUpdateStatement, record);
	
	auto rc = sqlite3_step(m_SEBrokerLoginSessionUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBrokerLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerLoginSessionUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::SelectSEBrokerLoginSession(std::list<SEBrokerLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_SEBrokerLoginSession;", -1, &m_SEBrokerLoginSessionSelectStatement, nullptr);
	}

	while (sqlite3_step(m_SEBrokerLoginSessionSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_SEBrokerLoginSessionSelectStatement, records);
	}
	sqlite3_reset(m_SEBrokerLoginSessionSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateSEBrokerLoginSession()
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_SEBrokerLoginSession;", -1, &m_SEBrokerLoginSessionTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_SEBrokerLoginSessionTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateSEBrokerLoginSession failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_SEBrokerLoginSessionTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateSEBrokerLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}


void SqliteDB::SetStatementForTradingDayRecord(sqlite3_stmt* statement, TradingDay* record)
{
	sqlite3_bind_int(statement, 1, record->PK);
	sqlite3_bind_text(statement, 2, record->CurrTradingDay, sizeof(record->CurrTradingDay), nullptr);
	sqlite3_bind_text(statement, 3, record->PreTradingDay, sizeof(record->PreTradingDay), nullptr);
}
void SqliteDB::SetStatementForTradingDayRecordUpdate(sqlite3_stmt* statement, TradingDay* record)
{
	sqlite3_bind_text(statement, 1, record->CurrTradingDay, sizeof(record->CurrTradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->PreTradingDay, sizeof(record->PreTradingDay), nullptr);
	sqlite3_bind_int(statement, 3, record->PK);
}
void SqliteDB::SetStatementForTradingDayPrimaryKey(sqlite3_stmt* statement, const IntType& PK)
{
	sqlite3_bind_int(statement, 1, PK);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<TradingDay*>& records)
{
	TradingDay* record = TradingDay::Allocate();
	record->PK = sqlite3_column_int(statement, 0);
	Strcpy(record->CurrTradingDay, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->PreTradingDay, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}
void SqliteDB::SetStatementForExchangeRecord(sqlite3_stmt* statement, Exchange* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeName, sizeof(record->ExchangeName), nullptr);
}
void SqliteDB::SetStatementForExchangeRecordUpdate(sqlite3_stmt* statement, Exchange* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeName, sizeof(record->ExchangeName), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
}
void SqliteDB::SetStatementForExchangePrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID)
{
	sqlite3_bind_text(statement, 1, ExchangeID, sizeof(ExchangeID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Exchange*>& records)
{
	Exchange* record = Exchange::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeName, (const char*)sqlite3_column_text(statement, 1));
	records.push_back(record);
}
void SqliteDB::SetStatementForProductRecord(sqlite3_stmt* statement, Product* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_text(statement, 3, record->ProductName, sizeof(record->ProductName), nullptr);
	sqlite3_bind_int(statement, 4, int(record->ProductClass));
	sqlite3_bind_int(statement, 5, record->VolumeMultiple);
	sqlite3_bind_double(statement, 6, record->PriceTick);
	sqlite3_bind_int64(statement, 7, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 8, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 9, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 10, record->MinLimitOrderVolume);
	sqlite3_bind_text(statement, 11, record->SessionName, sizeof(record->SessionName), nullptr);
}
void SqliteDB::SetStatementForProductRecordUpdate(sqlite3_stmt* statement, Product* record)
{
	sqlite3_bind_text(statement, 1, record->ProductName, sizeof(record->ProductName), nullptr);
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_int(statement, 3, record->VolumeMultiple);
	sqlite3_bind_double(statement, 4, record->PriceTick);
	sqlite3_bind_int64(statement, 5, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 6, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 7, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 8, record->MinLimitOrderVolume);
	sqlite3_bind_text(statement, 9, record->SessionName, sizeof(record->SessionName), nullptr);
	sqlite3_bind_text(statement, 10, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 11, record->ProductID, sizeof(record->ProductID), nullptr);
}
void SqliteDB::SetStatementForProductPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID)
{
	sqlite3_bind_text(statement, 1, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, ProductID, sizeof(ProductID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Product*>& records)
{
	Product* record = Product::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->ProductName, (const char*)sqlite3_column_text(statement, 2));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 3));
	record->VolumeMultiple = sqlite3_column_int(statement, 4);
	record->PriceTick = sqlite3_column_double(statement, 5);
	record->MaxMarketOrderVolume = sqlite3_column_int64(statement, 6);
	record->MinMarketOrderVolume = sqlite3_column_int64(statement, 7);
	record->MaxLimitOrderVolume = sqlite3_column_int64(statement, 8);
	record->MinLimitOrderVolume = sqlite3_column_int64(statement, 9);
	Strcpy(record->SessionName, (const char*)sqlite3_column_text(statement, 10));
	records.push_back(record);
}
void SqliteDB::SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, DepthMarketData* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int64(statement, 4, record->UpdateTs);
	sqlite3_bind_double(statement, 5, record->LastPrice);
	sqlite3_bind_double(statement, 6, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 7, record->PreClosePrice);
	sqlite3_bind_double(statement, 8, record->PreOpenInterest);
	sqlite3_bind_double(statement, 9, record->OpenPrice);
	sqlite3_bind_double(statement, 10, record->HighestPrice);
	sqlite3_bind_double(statement, 11, record->LowestPrice);
	sqlite3_bind_double(statement, 12, record->ClosePrice);
	sqlite3_bind_int64(statement, 13, record->CurrVolume);
	sqlite3_bind_int64(statement, 14, record->Volume);
	sqlite3_bind_double(statement, 15, record->CurrTurnover);
	sqlite3_bind_double(statement, 16, record->Turnover);
	sqlite3_bind_double(statement, 17, record->OpenInterest);
	sqlite3_bind_double(statement, 18, record->SettlementPrice);
	sqlite3_bind_double(statement, 19, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 20, record->LowerLimitPrice);
	sqlite3_bind_double(statement, 21, record->AveragePrice);
	sqlite3_bind_double(statement, 22, record->AskPrice1);
	sqlite3_bind_double(statement, 23, record->AskPrice2);
	sqlite3_bind_double(statement, 24, record->AskPrice3);
	sqlite3_bind_double(statement, 25, record->AskPrice4);
	sqlite3_bind_double(statement, 26, record->AskPrice5);
	sqlite3_bind_double(statement, 27, record->AskPrice6);
	sqlite3_bind_double(statement, 28, record->AskPrice7);
	sqlite3_bind_double(statement, 29, record->AskPrice8);
	sqlite3_bind_double(statement, 30, record->AskPrice9);
	sqlite3_bind_double(statement, 31, record->AskPrice10);
	sqlite3_bind_int64(statement, 32, record->AskVolume1);
	sqlite3_bind_int64(statement, 33, record->AskVolume2);
	sqlite3_bind_int64(statement, 34, record->AskVolume3);
	sqlite3_bind_int64(statement, 35, record->AskVolume4);
	sqlite3_bind_int64(statement, 36, record->AskVolume5);
	sqlite3_bind_int64(statement, 37, record->AskVolume6);
	sqlite3_bind_int64(statement, 38, record->AskVolume7);
	sqlite3_bind_int64(statement, 39, record->AskVolume8);
	sqlite3_bind_int64(statement, 40, record->AskVolume9);
	sqlite3_bind_int64(statement, 41, record->AskVolume10);
	sqlite3_bind_double(statement, 42, record->BidPrice1);
	sqlite3_bind_double(statement, 43, record->BidPrice2);
	sqlite3_bind_double(statement, 44, record->BidPrice3);
	sqlite3_bind_double(statement, 45, record->BidPrice4);
	sqlite3_bind_double(statement, 46, record->BidPrice5);
	sqlite3_bind_double(statement, 47, record->BidPrice6);
	sqlite3_bind_double(statement, 48, record->BidPrice7);
	sqlite3_bind_double(statement, 49, record->BidPrice8);
	sqlite3_bind_double(statement, 50, record->BidPrice9);
	sqlite3_bind_double(statement, 51, record->BidPrice10);
	sqlite3_bind_int64(statement, 52, record->BidVolume1);
	sqlite3_bind_int64(statement, 53, record->BidVolume2);
	sqlite3_bind_int64(statement, 54, record->BidVolume3);
	sqlite3_bind_int64(statement, 55, record->BidVolume4);
	sqlite3_bind_int64(statement, 56, record->BidVolume5);
	sqlite3_bind_int64(statement, 57, record->BidVolume6);
	sqlite3_bind_int64(statement, 58, record->BidVolume7);
	sqlite3_bind_int64(statement, 59, record->BidVolume8);
	sqlite3_bind_int64(statement, 60, record->BidVolume9);
	sqlite3_bind_int64(statement, 61, record->BidVolume10);
}
void SqliteDB::SetStatementForDepthMarketDataRecordUpdate(sqlite3_stmt* statement, DepthMarketData* record)
{
	sqlite3_bind_int64(statement, 1, record->UpdateTs);
	sqlite3_bind_double(statement, 2, record->LastPrice);
	sqlite3_bind_double(statement, 3, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 4, record->PreClosePrice);
	sqlite3_bind_double(statement, 5, record->PreOpenInterest);
	sqlite3_bind_double(statement, 6, record->OpenPrice);
	sqlite3_bind_double(statement, 7, record->HighestPrice);
	sqlite3_bind_double(statement, 8, record->LowestPrice);
	sqlite3_bind_double(statement, 9, record->ClosePrice);
	sqlite3_bind_int64(statement, 10, record->CurrVolume);
	sqlite3_bind_int64(statement, 11, record->Volume);
	sqlite3_bind_double(statement, 12, record->CurrTurnover);
	sqlite3_bind_double(statement, 13, record->Turnover);
	sqlite3_bind_double(statement, 14, record->OpenInterest);
	sqlite3_bind_double(statement, 15, record->SettlementPrice);
	sqlite3_bind_double(statement, 16, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 17, record->LowerLimitPrice);
	sqlite3_bind_double(statement, 18, record->AveragePrice);
	sqlite3_bind_double(statement, 19, record->AskPrice1);
	sqlite3_bind_double(statement, 20, record->AskPrice2);
	sqlite3_bind_double(statement, 21, record->AskPrice3);
	sqlite3_bind_double(statement, 22, record->AskPrice4);
	sqlite3_bind_double(statement, 23, record->AskPrice5);
	sqlite3_bind_double(statement, 24, record->AskPrice6);
	sqlite3_bind_double(statement, 25, record->AskPrice7);
	sqlite3_bind_double(statement, 26, record->AskPrice8);
	sqlite3_bind_double(statement, 27, record->AskPrice9);
	sqlite3_bind_double(statement, 28, record->AskPrice10);
	sqlite3_bind_int64(statement, 29, record->AskVolume1);
	sqlite3_bind_int64(statement, 30, record->AskVolume2);
	sqlite3_bind_int64(statement, 31, record->AskVolume3);
	sqlite3_bind_int64(statement, 32, record->AskVolume4);
	sqlite3_bind_int64(statement, 33, record->AskVolume5);
	sqlite3_bind_int64(statement, 34, record->AskVolume6);
	sqlite3_bind_int64(statement, 35, record->AskVolume7);
	sqlite3_bind_int64(statement, 36, record->AskVolume8);
	sqlite3_bind_int64(statement, 37, record->AskVolume9);
	sqlite3_bind_int64(statement, 38, record->AskVolume10);
	sqlite3_bind_double(statement, 39, record->BidPrice1);
	sqlite3_bind_double(statement, 40, record->BidPrice2);
	sqlite3_bind_double(statement, 41, record->BidPrice3);
	sqlite3_bind_double(statement, 42, record->BidPrice4);
	sqlite3_bind_double(statement, 43, record->BidPrice5);
	sqlite3_bind_double(statement, 44, record->BidPrice6);
	sqlite3_bind_double(statement, 45, record->BidPrice7);
	sqlite3_bind_double(statement, 46, record->BidPrice8);
	sqlite3_bind_double(statement, 47, record->BidPrice9);
	sqlite3_bind_double(statement, 48, record->BidPrice10);
	sqlite3_bind_int64(statement, 49, record->BidVolume1);
	sqlite3_bind_int64(statement, 50, record->BidVolume2);
	sqlite3_bind_int64(statement, 51, record->BidVolume3);
	sqlite3_bind_int64(statement, 52, record->BidVolume4);
	sqlite3_bind_int64(statement, 53, record->BidVolume5);
	sqlite3_bind_int64(statement, 54, record->BidVolume6);
	sqlite3_bind_int64(statement, 55, record->BidVolume7);
	sqlite3_bind_int64(statement, 56, record->BidVolume8);
	sqlite3_bind_int64(statement, 57, record->BidVolume9);
	sqlite3_bind_int64(statement, 58, record->BidVolume10);
	sqlite3_bind_text(statement, 59, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 60, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 61, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
}
void SqliteDB::SetStatementForDepthMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, InstrumentID, sizeof(InstrumentID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<DepthMarketData*>& records)
{
	DepthMarketData* record = DepthMarketData::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 2));
	record->UpdateTs = sqlite3_column_int64(statement, 3);
	record->LastPrice = sqlite3_column_double(statement, 4);
	record->PreSettlementPrice = sqlite3_column_double(statement, 5);
	record->PreClosePrice = sqlite3_column_double(statement, 6);
	record->PreOpenInterest = sqlite3_column_double(statement, 7);
	record->OpenPrice = sqlite3_column_double(statement, 8);
	record->HighestPrice = sqlite3_column_double(statement, 9);
	record->LowestPrice = sqlite3_column_double(statement, 10);
	record->ClosePrice = sqlite3_column_double(statement, 11);
	record->CurrVolume = sqlite3_column_int64(statement, 12);
	record->Volume = sqlite3_column_int64(statement, 13);
	record->CurrTurnover = sqlite3_column_double(statement, 14);
	record->Turnover = sqlite3_column_double(statement, 15);
	record->OpenInterest = sqlite3_column_double(statement, 16);
	record->SettlementPrice = sqlite3_column_double(statement, 17);
	record->UpperLimitPrice = sqlite3_column_double(statement, 18);
	record->LowerLimitPrice = sqlite3_column_double(statement, 19);
	record->AveragePrice = sqlite3_column_double(statement, 20);
	record->AskPrice1 = sqlite3_column_double(statement, 21);
	record->AskPrice2 = sqlite3_column_double(statement, 22);
	record->AskPrice3 = sqlite3_column_double(statement, 23);
	record->AskPrice4 = sqlite3_column_double(statement, 24);
	record->AskPrice5 = sqlite3_column_double(statement, 25);
	record->AskPrice6 = sqlite3_column_double(statement, 26);
	record->AskPrice7 = sqlite3_column_double(statement, 27);
	record->AskPrice8 = sqlite3_column_double(statement, 28);
	record->AskPrice9 = sqlite3_column_double(statement, 29);
	record->AskPrice10 = sqlite3_column_double(statement, 30);
	record->AskVolume1 = sqlite3_column_int64(statement, 31);
	record->AskVolume2 = sqlite3_column_int64(statement, 32);
	record->AskVolume3 = sqlite3_column_int64(statement, 33);
	record->AskVolume4 = sqlite3_column_int64(statement, 34);
	record->AskVolume5 = sqlite3_column_int64(statement, 35);
	record->AskVolume6 = sqlite3_column_int64(statement, 36);
	record->AskVolume7 = sqlite3_column_int64(statement, 37);
	record->AskVolume8 = sqlite3_column_int64(statement, 38);
	record->AskVolume9 = sqlite3_column_int64(statement, 39);
	record->AskVolume10 = sqlite3_column_int64(statement, 40);
	record->BidPrice1 = sqlite3_column_double(statement, 41);
	record->BidPrice2 = sqlite3_column_double(statement, 42);
	record->BidPrice3 = sqlite3_column_double(statement, 43);
	record->BidPrice4 = sqlite3_column_double(statement, 44);
	record->BidPrice5 = sqlite3_column_double(statement, 45);
	record->BidPrice6 = sqlite3_column_double(statement, 46);
	record->BidPrice7 = sqlite3_column_double(statement, 47);
	record->BidPrice8 = sqlite3_column_double(statement, 48);
	record->BidPrice9 = sqlite3_column_double(statement, 49);
	record->BidPrice10 = sqlite3_column_double(statement, 50);
	record->BidVolume1 = sqlite3_column_int64(statement, 51);
	record->BidVolume2 = sqlite3_column_int64(statement, 52);
	record->BidVolume3 = sqlite3_column_int64(statement, 53);
	record->BidVolume4 = sqlite3_column_int64(statement, 54);
	record->BidVolume5 = sqlite3_column_int64(statement, 55);
	record->BidVolume6 = sqlite3_column_int64(statement, 56);
	record->BidVolume7 = sqlite3_column_int64(statement, 57);
	record->BidVolume8 = sqlite3_column_int64(statement, 58);
	record->BidVolume9 = sqlite3_column_int64(statement, 59);
	record->BidVolume10 = sqlite3_column_int64(statement, 60);
	records.push_back(record);
}
void SqliteDB::SetStatementForSEBrokerRecord(sqlite3_stmt* statement, SEBroker* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
	sqlite3_bind_text(statement, 2, record->BrokerName, sizeof(record->BrokerName), nullptr);
	sqlite3_bind_text(statement, 3, record->Password, sizeof(record->Password), nullptr);
}
void SqliteDB::SetStatementForSEBrokerRecordUpdate(sqlite3_stmt* statement, SEBroker* record)
{
	sqlite3_bind_text(statement, 1, record->BrokerName, sizeof(record->BrokerName), nullptr);
	sqlite3_bind_text(statement, 2, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_int(statement, 3, record->BrokerID);
}
void SqliteDB::SetStatementForSEBrokerPrimaryKey(sqlite3_stmt* statement, const BrokerIDType& BrokerID)
{
	sqlite3_bind_int(statement, 1, BrokerID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<SEBroker*>& records)
{
	SEBroker* record = SEBroker::Allocate();
	record->BrokerID = sqlite3_column_int(statement, 0);
	Strcpy(record->BrokerName, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->Password, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}
void SqliteDB::SetStatementForSEInstrumentRecord(sqlite3_stmt* statement, SEInstrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_text(statement, 3, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 4, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 5, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int64(statement, 7, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 8, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 9, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 10, record->MinLimitOrderVolume);
	sqlite3_bind_int(statement, 11, record->VolumeMultiple);
	sqlite3_bind_double(statement, 12, record->PriceTick);
	sqlite3_bind_double(statement, 13, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 14, record->LowerLimitPrice);
	sqlite3_bind_text(statement, 15, record->SessionName, sizeof(record->SessionName), nullptr);
}
void SqliteDB::SetStatementForSEInstrumentRecordUpdate(sqlite3_stmt* statement, SEInstrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 2, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 3, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->ProductClass));
	sqlite3_bind_int64(statement, 5, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 6, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 7, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 8, record->MinLimitOrderVolume);
	sqlite3_bind_int(statement, 9, record->VolumeMultiple);
	sqlite3_bind_double(statement, 10, record->PriceTick);
	sqlite3_bind_double(statement, 11, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 12, record->LowerLimitPrice);
	sqlite3_bind_text(statement, 13, record->SessionName, sizeof(record->SessionName), nullptr);
	sqlite3_bind_text(statement, 14, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 15, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
}
void SqliteDB::SetStatementForSEInstrumentPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	sqlite3_bind_text(statement, 1, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, InstrumentID, sizeof(InstrumentID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<SEInstrument*>& records)
{
	SEInstrument* record = SEInstrument::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->ExchangeInstID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->InstrumentName, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->MaxMarketOrderVolume = sqlite3_column_int64(statement, 6);
	record->MinMarketOrderVolume = sqlite3_column_int64(statement, 7);
	record->MaxLimitOrderVolume = sqlite3_column_int64(statement, 8);
	record->MinLimitOrderVolume = sqlite3_column_int64(statement, 9);
	record->VolumeMultiple = sqlite3_column_int(statement, 10);
	record->PriceTick = sqlite3_column_double(statement, 11);
	record->UpperLimitPrice = sqlite3_column_double(statement, 12);
	record->LowerLimitPrice = sqlite3_column_double(statement, 13);
	Strcpy(record->SessionName, (const char*)sqlite3_column_text(statement, 14));
	records.push_back(record);
}
void SqliteDB::SetStatementForSEOrderRecord(sqlite3_stmt* statement, SEOrder* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_int(statement, 2, record->BrokerID);
	sqlite3_bind_text(statement, 3, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, record->OrderID);
	sqlite3_bind_int(statement, 8, int(record->Direction));
	sqlite3_bind_int(statement, 9, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 10, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 11, record->Price);
	sqlite3_bind_int64(statement, 12, record->Volume);
	sqlite3_bind_int64(statement, 13, record->VolumeTotal);
	sqlite3_bind_int64(statement, 14, record->VolumeTraded);
	sqlite3_bind_int(statement, 15, record->VolumeMultiple);
	sqlite3_bind_int(statement, 16, int(record->OrderStatus));
	sqlite3_bind_text(statement, 17, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 18, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 19, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 20, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 21, record->SessionID);
	sqlite3_bind_int(statement, 22, record->ClientOrderID);
}
void SqliteDB::SetStatementForSEOrderRecordUpdate(sqlite3_stmt* statement, SEOrder* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_int(statement, 3, int(record->Direction));
	sqlite3_bind_int(statement, 4, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 5, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 6, record->Price);
	sqlite3_bind_int64(statement, 7, record->Volume);
	sqlite3_bind_int64(statement, 8, record->VolumeTotal);
	sqlite3_bind_int64(statement, 9, record->VolumeTraded);
	sqlite3_bind_int(statement, 10, record->VolumeMultiple);
	sqlite3_bind_int(statement, 11, int(record->OrderStatus));
	sqlite3_bind_text(statement, 12, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 13, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 14, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 15, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 16, record->SessionID);
	sqlite3_bind_int(statement, 17, record->ClientOrderID);
	sqlite3_bind_text(statement, 18, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 19, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 20, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 21, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 22, record->OrderID);
}
void SqliteDB::SetStatementForSEOrderPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
	sqlite3_bind_text(statement, 3, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, OrderID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<SEOrder*>& records)
{
	SEOrder* record = SEOrder::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	record->BrokerID = sqlite3_column_int(statement, 1);
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->OrderID = sqlite3_column_int(statement, 6);
	record->Direction = DirectionType(sqlite3_column_int(statement, 7));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 8));
	record->OrderPriceType = OrderPriceTypeType(sqlite3_column_int(statement, 9));
	record->Price = sqlite3_column_double(statement, 10);
	record->Volume = sqlite3_column_int64(statement, 11);
	record->VolumeTotal = sqlite3_column_int64(statement, 12);
	record->VolumeTraded = sqlite3_column_int64(statement, 13);
	record->VolumeMultiple = sqlite3_column_int(statement, 14);
	record->OrderStatus = OrderStatusType(sqlite3_column_int(statement, 15));
	Strcpy(record->OrderDate, (const char*)sqlite3_column_text(statement, 16));
	Strcpy(record->OrderTime, (const char*)sqlite3_column_text(statement, 17));
	Strcpy(record->CancelDate, (const char*)sqlite3_column_text(statement, 18));
	Strcpy(record->CancelTime, (const char*)sqlite3_column_text(statement, 19));
	record->SessionID = sqlite3_column_int64(statement, 20);
	record->ClientOrderID = sqlite3_column_int(statement, 21);
	records.push_back(record);
}
void SqliteDB::SetStatementForSETradeRecord(sqlite3_stmt* statement, SETrade* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_int(statement, 2, record->BrokerID);
	sqlite3_bind_text(statement, 3, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, record->OrderID);
	sqlite3_bind_text(statement, 8, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 9, int(record->Direction));
	sqlite3_bind_int(statement, 10, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 11, record->Price);
	sqlite3_bind_int64(statement, 12, record->Volume);
	sqlite3_bind_int(statement, 13, record->VolumeMultiple);
	sqlite3_bind_double(statement, 14, record->TradeAmount);
	sqlite3_bind_double(statement, 15, record->Commission);
	sqlite3_bind_text(statement, 16, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 17, record->TradeTime, sizeof(record->TradeTime), nullptr);
}
void SqliteDB::SetStatementForSETradeRecordUpdate(sqlite3_stmt* statement, SETrade* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->ProductClass));
	sqlite3_bind_int(statement, 5, record->OrderID);
	sqlite3_bind_int(statement, 6, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 7, record->Price);
	sqlite3_bind_int64(statement, 8, record->Volume);
	sqlite3_bind_int(statement, 9, record->VolumeMultiple);
	sqlite3_bind_double(statement, 10, record->TradeAmount);
	sqlite3_bind_double(statement, 11, record->Commission);
	sqlite3_bind_text(statement, 12, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 13, record->TradeTime, sizeof(record->TradeTime), nullptr);
	sqlite3_bind_text(statement, 14, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 15, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 16, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 17, int(record->Direction));
}
void SqliteDB::SetStatementForSETradePrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, TradeID, sizeof(TradeID), nullptr);
	sqlite3_bind_int(statement, 4, int(Direction));
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<SETrade*>& records)
{
	SETrade* record = SETrade::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	record->BrokerID = sqlite3_column_int(statement, 1);
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->OrderID = sqlite3_column_int(statement, 6);
	Strcpy(record->TradeID, (const char*)sqlite3_column_text(statement, 7));
	record->Direction = DirectionType(sqlite3_column_int(statement, 8));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 9));
	record->Price = sqlite3_column_double(statement, 10);
	record->Volume = sqlite3_column_int64(statement, 11);
	record->VolumeMultiple = sqlite3_column_int(statement, 12);
	record->TradeAmount = sqlite3_column_double(statement, 13);
	record->Commission = sqlite3_column_double(statement, 14);
	Strcpy(record->TradeDate, (const char*)sqlite3_column_text(statement, 15));
	Strcpy(record->TradeTime, (const char*)sqlite3_column_text(statement, 16));
	records.push_back(record);
}
void SqliteDB::SetStatementForSEBrokerLoginSessionRecord(sqlite3_stmt* statement, SEBrokerLoginSession* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
	sqlite3_bind_int64(statement, 2, record->SessionID);
	sqlite3_bind_text(statement, 3, record->IPAddress, sizeof(record->IPAddress), nullptr);
}
void SqliteDB::SetStatementForSEBrokerLoginSessionRecordUpdate(sqlite3_stmt* statement, SEBrokerLoginSession* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
	sqlite3_bind_text(statement, 2, record->IPAddress, sizeof(record->IPAddress), nullptr);
	sqlite3_bind_int64(statement, 3, record->SessionID);
}
void SqliteDB::SetStatementForSEBrokerLoginSessionPrimaryKey(sqlite3_stmt* statement, const SessionIDType& SessionID)
{
	sqlite3_bind_int64(statement, 1, SessionID);
}
void SqliteDB::SetStatementForSEBrokerLoginSessionIndexBrokerID(sqlite3_stmt* statement, SEBrokerLoginSession* record)
{
	sqlite3_bind_int(statement, 1, record->BrokerID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<SEBrokerLoginSession*>& records)
{
	SEBrokerLoginSession* record = SEBrokerLoginSession::Allocate();
	record->BrokerID = sqlite3_column_int(statement, 0);
	record->SessionID = sqlite3_column_int64(statement, 1);
	Strcpy(record->IPAddress, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}

