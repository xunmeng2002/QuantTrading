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

	m_HotInstrumentInsertStatement = nullptr;
	m_HotInstrumentDeleteStatement = nullptr;
	m_HotInstrumentDeleteByTradingDayIndexStatement = nullptr;
	m_HotInstrumentUpdateStatement = nullptr;
	m_HotInstrumentSelectStatement = nullptr;
	m_HotInstrumentTruncateStatement = nullptr;

	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentUpdateStatement = nullptr;
	m_InstrumentSelectStatement = nullptr;
	m_InstrumentTruncateStatement = nullptr;

	m_AccountInsertStatement = nullptr;
	m_AccountDeleteStatement = nullptr;
	m_AccountUpdateStatement = nullptr;
	m_AccountSelectStatement = nullptr;
	m_AccountTruncateStatement = nullptr;

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
	if (m_HotInstrumentInsertStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentInsertStatement);
		m_HotInstrumentInsertStatement = nullptr;
	}
	if (m_HotInstrumentDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentDeleteStatement);
		m_HotInstrumentDeleteStatement = nullptr;
	}
	if (m_HotInstrumentDeleteByTradingDayIndexStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentDeleteByTradingDayIndexStatement);
		m_HotInstrumentDeleteByTradingDayIndexStatement = nullptr;
	}
	if (m_HotInstrumentUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentUpdateStatement);
		m_HotInstrumentUpdateStatement = nullptr;
	}
	if (m_HotInstrumentSelectStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentSelectStatement);
		m_HotInstrumentSelectStatement = nullptr;
	}
	if (m_HotInstrumentTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_HotInstrumentTruncateStatement);
		m_HotInstrumentTruncateStatement = nullptr;
	}
	if (m_InstrumentInsertStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentInsertStatement);
		m_InstrumentInsertStatement = nullptr;
	}
	if (m_InstrumentDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentDeleteStatement);
		m_InstrumentDeleteStatement = nullptr;
	}
	if (m_InstrumentUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentUpdateStatement);
		m_InstrumentUpdateStatement = nullptr;
	}
	if (m_InstrumentSelectStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentSelectStatement);
		m_InstrumentSelectStatement = nullptr;
	}
	if (m_InstrumentTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentTruncateStatement);
		m_InstrumentTruncateStatement = nullptr;
	}
	if (m_AccountInsertStatement != nullptr)
	{
		sqlite3_finalize(m_AccountInsertStatement);
		m_AccountInsertStatement = nullptr;
	}
	if (m_AccountDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_AccountDeleteStatement);
		m_AccountDeleteStatement = nullptr;
	}
	if (m_AccountUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_AccountUpdateStatement);
		m_AccountUpdateStatement = nullptr;
	}
	if (m_AccountSelectStatement != nullptr)
	{
		sqlite3_finalize(m_AccountSelectStatement);
		m_AccountSelectStatement = nullptr;
	}
	if (m_AccountTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_AccountTruncateStatement);
		m_AccountTruncateStatement = nullptr;
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
	Exec("Truncate Table t_HotInstrument;");
	Exec("Insert Into t_HotInstrument select * from Init.t_HotInstrument;");
	Exec("Truncate Table t_Instrument;");
	Exec("Insert Into t_Instrument select * from Init.t_Instrument;");
	Exec("Truncate Table t_Account;");
	Exec("Insert Into t_Account select * from Init.t_Account;");
}
void SqliteDB::CreateTables()
{
	CreateTradingDay();
	CreateExchange();
	CreateProduct();
	CreateHotInstrument();
	CreateInstrument();
	CreateAccount();
}
void SqliteDB::DropTables()
{
	DropTradingDay();
	DropExchange();
	DropProduct();
	DropHotInstrument();
	DropInstrument();
	DropAccount();
}
void SqliteDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateHotInstrument();
	TruncateAccount();
}
void SqliteDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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

void SqliteDB::CreateTradingDay()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_TradingDay(`PK` int, `CurrTradingDay` text, `PreTradingDay` text, PRIMARY KEY(PK));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateTradingDay failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTradingDay Spend:%lldms", duration);
}
void SqliteDB::DropTradingDay()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_TradingDay;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropTradingDay failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTradingDay Spend:%lldms", duration);
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
void SqliteDB::CreateExchange()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Exchange(`ExchangeID` text, `ExchangeName` text, PRIMARY KEY(ExchangeID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateExchange failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateExchange Spend:%lldms", duration);
}
void SqliteDB::DropExchange()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Exchange;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropExchange failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropExchange Spend:%lldms", duration);
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
void SqliteDB::CreateProduct()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Product(`ExchangeID` text, `ProductID` text, `ProductName` text, `ProductClass` int, `VolumeMultiple` int, `PriceTick` double, `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` text, PRIMARY KEY(ExchangeID, ProductID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateProduct failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateProduct Spend:%lldms", duration);
}
void SqliteDB::DropProduct()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Product;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropProduct failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropProduct Spend:%lldms", duration);
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
void SqliteDB::CreateHotInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_HotInstrument(`TradingDay` text, `ExchangeID` text, `ProductID` text, `InstrumentID` text, `ProductClass` int, `Volume` bigint, `MaxVolume` bigint, `Turnover` double, `MaxTurnover` double, `OpenInterest` double, `MaxOpenInterest` double, `Rank` int, PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank));CREATE INDEX HotInstrumentTradingDay ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateHotInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateHotInstrument Spend:%lldms", duration);
}
void SqliteDB::DropHotInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP INDEX HotInstrumentTradingDay;DROP TABLE IF EXISTS t_HotInstrument;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropHotInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropHotInstrument Spend:%lldms", duration);
}
void SqliteDB::InsertHotInstrument(HotInstrument* record)
{
	auto start = steady_clock::now();
	if (m_HotInstrumentInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_HotInstrument Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_HotInstrumentInsertStatement, nullptr);
	}
	SetStatementForHotInstrumentRecord(m_HotInstrumentInsertStatement, record);
	
	auto rc = sqlite3_step(m_HotInstrumentInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertHotInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_HotInstrumentInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertHotInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertHotInstrument(std::list<HotInstrument*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_HotInstrument Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertHotInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_HotInstrument Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertHotInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertHotInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteHotInstrument(HotInstrument* record)
{
	auto start = steady_clock::now();
	if (m_HotInstrumentDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_HotInstrument where TradingDay = ? and ExchangeID = ? and ProductID = ? and Rank = ?;", -1, &m_HotInstrumentDeleteStatement, nullptr);
	}
	SetStatementForHotInstrumentPrimaryKey(m_HotInstrumentDeleteStatement, record->TradingDay, record->ExchangeID, record->ProductID, record->Rank);

	auto rc = sqlite3_step(m_HotInstrumentDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteHotInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_HotInstrumentDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteHotInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::DeleteHotInstrumentByTradingDayIndex(HotInstrument* record)
{
	auto start = steady_clock::now();
	if (m_HotInstrumentDeleteByTradingDayIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_HotInstrument where ExchangeID = ? and ProductID = ? and Rank = ? and TradingDay = ?;", -1, &m_HotInstrumentDeleteByTradingDayIndexStatement, nullptr);
	}
	SetStatementForHotInstrumentIndexTradingDay(m_HotInstrumentDeleteByTradingDayIndexStatement, record);
	
	auto rc = sqlite3_step(m_HotInstrumentDeleteByTradingDayIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteHotInstrumentByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_HotInstrumentDeleteByTradingDayIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteHotInstrumentByTradingDayIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateHotInstrument(HotInstrument* record)
{
	auto start = steady_clock::now();
	if (m_HotInstrumentUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_HotInstrument set InstrumentID = ?, ProductClass = ?, Volume = ?, MaxVolume = ?, Turnover = ?, MaxTurnover = ?, OpenInterest = ?, MaxOpenInterest = ? where TradingDay = ? and ExchangeID = ? and ProductID = ? and Rank = ?;", -1, &m_HotInstrumentUpdateStatement, nullptr);
	}
	SetStatementForHotInstrumentRecordUpdate(m_HotInstrumentUpdateStatement, record);
	
	auto rc = sqlite3_step(m_HotInstrumentUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateHotInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_HotInstrumentUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateHotInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::SelectHotInstrument(std::list<HotInstrument*>& records)
{
	auto start = steady_clock::now();
	if (m_HotInstrumentSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_HotInstrument;", -1, &m_HotInstrumentSelectStatement, nullptr);
	}

	while (sqlite3_step(m_HotInstrumentSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_HotInstrumentSelectStatement, records);
	}
	sqlite3_reset(m_HotInstrumentSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectHotInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateHotInstrument()
{
	auto start = steady_clock::now();
	if (m_HotInstrumentTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_HotInstrument;", -1, &m_HotInstrumentTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_HotInstrumentTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateHotInstrument failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_HotInstrumentTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateHotInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Instrument(`ExchangeID` text, `InstrumentID` text, `ExchangeInstID` text, `InstrumentName` text, `ProductID` text, `ProductClass` int, `InstrumentClass` int, `Rank` int, `VolumeMultiple` int, `PriceTick` double, `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` text, PRIMARY KEY(ExchangeID, InstrumentID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateInstrument Spend:%lldms", duration);
}
void SqliteDB::DropInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Instrument;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropInstrument Spend:%lldms", duration);
}
void SqliteDB::InsertInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Instrument Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_InstrumentInsertStatement, nullptr);
	}
	SetStatementForInstrumentRecord(m_InstrumentInsertStatement, record);
	
	auto rc = sqlite3_step(m_InstrumentInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_InstrumentInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertInstrument(std::list<Instrument*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Instrument Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Instrument Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertInstrument Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Instrument where ExchangeID = ? and InstrumentID = ?;", -1, &m_InstrumentDeleteStatement, nullptr);
	}
	SetStatementForInstrumentPrimaryKey(m_InstrumentDeleteStatement, record->ExchangeID, record->InstrumentID);

	auto rc = sqlite3_step(m_InstrumentDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_InstrumentDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Instrument set ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, ProductClass = ?, InstrumentClass = ?, Rank = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;", -1, &m_InstrumentUpdateStatement, nullptr);
	}
	SetStatementForInstrumentRecordUpdate(m_InstrumentUpdateStatement, record);
	
	auto rc = sqlite3_step(m_InstrumentUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_InstrumentUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::SelectInstrument(std::list<Instrument*>& records)
{
	auto start = steady_clock::now();
	if (m_InstrumentSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Instrument;", -1, &m_InstrumentSelectStatement, nullptr);
	}

	while (sqlite3_step(m_InstrumentSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_InstrumentSelectStatement, records);
	}
	sqlite3_reset(m_InstrumentSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectInstrument Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Instrument;", -1, &m_InstrumentTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_InstrumentTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateInstrument failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_InstrumentTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Account(`AccountID` text, `AccountName` text, `AccountType` int, `AccountStatus` int, `Password` text, `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, PRIMARY KEY(AccountID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccount Spend:%lldms", duration);
}
void SqliteDB::DropAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Account;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccount Spend:%lldms", duration);
}
void SqliteDB::InsertAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Account Values(?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_AccountInsertStatement, nullptr);
	}
	SetStatementForAccountRecord(m_AccountInsertStatement, record);
	
	auto rc = sqlite3_step(m_AccountInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertAccount Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertAccount(std::list<Account*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Account Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertAccount Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Account Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertAccount Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Account where AccountID = ?;", -1, &m_AccountDeleteStatement, nullptr);
	}
	SetStatementForAccountPrimaryKey(m_AccountDeleteStatement, record->AccountID);

	auto rc = sqlite3_step(m_AccountDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccount Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Account set AccountName = ?, AccountType = ?, AccountStatus = ?, Password = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ? where AccountID = ?;", -1, &m_AccountUpdateStatement, nullptr);
	}
	SetStatementForAccountRecordUpdate(m_AccountUpdateStatement, record);
	
	auto rc = sqlite3_step(m_AccountUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount Spend:%lldms", duration);
	}
}
void SqliteDB::SelectAccount(std::list<Account*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Account;", -1, &m_AccountSelectStatement, nullptr);
	}

	while (sqlite3_step(m_AccountSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_AccountSelectStatement, records);
	}
	sqlite3_reset(m_AccountSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccount Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateAccount()
{
	auto start = steady_clock::now();
	if (m_AccountTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Account;", -1, &m_AccountTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_AccountTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateAccount failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void SqliteDB::SetStatementForHotInstrumentRecord(sqlite3_stmt* statement, HotInstrument* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_text(statement, 4, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->ProductClass));
	sqlite3_bind_int64(statement, 6, record->Volume);
	sqlite3_bind_int64(statement, 7, record->MaxVolume);
	sqlite3_bind_double(statement, 8, record->Turnover);
	sqlite3_bind_double(statement, 9, record->MaxTurnover);
	sqlite3_bind_double(statement, 10, record->OpenInterest);
	sqlite3_bind_double(statement, 11, record->MaxOpenInterest);
	sqlite3_bind_int(statement, 12, record->Rank);
}
void SqliteDB::SetStatementForHotInstrumentRecordUpdate(sqlite3_stmt* statement, HotInstrument* record)
{
	sqlite3_bind_text(statement, 1, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_int64(statement, 3, record->Volume);
	sqlite3_bind_int64(statement, 4, record->MaxVolume);
	sqlite3_bind_double(statement, 5, record->Turnover);
	sqlite3_bind_double(statement, 6, record->MaxTurnover);
	sqlite3_bind_double(statement, 7, record->OpenInterest);
	sqlite3_bind_double(statement, 8, record->MaxOpenInterest);
	sqlite3_bind_text(statement, 9, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 10, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 11, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 12, record->Rank);
}
void SqliteDB::SetStatementForHotInstrumentPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, ProductID, sizeof(ProductID), nullptr);
	sqlite3_bind_int(statement, 4, Rank);
}
void SqliteDB::SetStatementForHotInstrumentIndexTradingDay(sqlite3_stmt* statement, HotInstrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 3, record->Rank);
	sqlite3_bind_text(statement, 4, record->TradingDay, sizeof(record->TradingDay), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<HotInstrument*>& records)
{
	HotInstrument* record = HotInstrument::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 3));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 4));
	record->Volume = sqlite3_column_int64(statement, 5);
	record->MaxVolume = sqlite3_column_int64(statement, 6);
	record->Turnover = sqlite3_column_double(statement, 7);
	record->MaxTurnover = sqlite3_column_double(statement, 8);
	record->OpenInterest = sqlite3_column_double(statement, 9);
	record->MaxOpenInterest = sqlite3_column_double(statement, 10);
	record->Rank = sqlite3_column_int(statement, 11);
	records.push_back(record);
}
void SqliteDB::SetStatementForInstrumentRecord(sqlite3_stmt* statement, Instrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_text(statement, 3, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 4, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 5, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, int(record->InstrumentClass));
	sqlite3_bind_int(statement, 8, record->Rank);
	sqlite3_bind_int(statement, 9, record->VolumeMultiple);
	sqlite3_bind_double(statement, 10, record->PriceTick);
	sqlite3_bind_int64(statement, 11, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 12, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 13, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 14, record->MinLimitOrderVolume);
	sqlite3_bind_text(statement, 15, record->SessionName, sizeof(record->SessionName), nullptr);
}
void SqliteDB::SetStatementForInstrumentRecordUpdate(sqlite3_stmt* statement, Instrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 2, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 3, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->ProductClass));
	sqlite3_bind_int(statement, 5, int(record->InstrumentClass));
	sqlite3_bind_int(statement, 6, record->Rank);
	sqlite3_bind_int(statement, 7, record->VolumeMultiple);
	sqlite3_bind_double(statement, 8, record->PriceTick);
	sqlite3_bind_int64(statement, 9, record->MaxMarketOrderVolume);
	sqlite3_bind_int64(statement, 10, record->MinMarketOrderVolume);
	sqlite3_bind_int64(statement, 11, record->MaxLimitOrderVolume);
	sqlite3_bind_int64(statement, 12, record->MinLimitOrderVolume);
	sqlite3_bind_text(statement, 13, record->SessionName, sizeof(record->SessionName), nullptr);
	sqlite3_bind_text(statement, 14, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 15, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
}
void SqliteDB::SetStatementForInstrumentPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	sqlite3_bind_text(statement, 1, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, InstrumentID, sizeof(InstrumentID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Instrument*>& records)
{
	Instrument* record = Instrument::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->ExchangeInstID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->InstrumentName, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->InstrumentClass = InstrumentClassType(sqlite3_column_int(statement, 6));
	record->Rank = sqlite3_column_int(statement, 7);
	record->VolumeMultiple = sqlite3_column_int(statement, 8);
	record->PriceTick = sqlite3_column_double(statement, 9);
	record->MaxMarketOrderVolume = sqlite3_column_int64(statement, 10);
	record->MinMarketOrderVolume = sqlite3_column_int64(statement, 11);
	record->MaxLimitOrderVolume = sqlite3_column_int64(statement, 12);
	record->MinLimitOrderVolume = sqlite3_column_int64(statement, 13);
	Strcpy(record->SessionName, (const char*)sqlite3_column_text(statement, 14));
	records.push_back(record);
}
void SqliteDB::SetStatementForAccountRecord(sqlite3_stmt* statement, Account* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountName, sizeof(record->AccountName), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_int(statement, 4, int(record->AccountStatus));
	sqlite3_bind_text(statement, 5, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_int(statement, 6, record->TradeGroupID);
	sqlite3_bind_int(statement, 7, record->RiskGroupID);
	sqlite3_bind_int(statement, 8, record->CommissionGroupID);
}
void SqliteDB::SetStatementForAccountRecordUpdate(sqlite3_stmt* statement, Account* record)
{
	sqlite3_bind_text(statement, 1, record->AccountName, sizeof(record->AccountName), nullptr);
	sqlite3_bind_int(statement, 2, int(record->AccountType));
	sqlite3_bind_int(statement, 3, int(record->AccountStatus));
	sqlite3_bind_text(statement, 4, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_int(statement, 5, record->TradeGroupID);
	sqlite3_bind_int(statement, 6, record->RiskGroupID);
	sqlite3_bind_int(statement, 7, record->CommissionGroupID);
	sqlite3_bind_text(statement, 8, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::SetStatementForAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID)
{
	sqlite3_bind_text(statement, 1, AccountID, sizeof(AccountID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Account*>& records)
{
	Account* record = Account::Allocate();
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountName, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	record->AccountStatus = AccountStatusType(sqlite3_column_int(statement, 3));
	Strcpy(record->Password, (const char*)sqlite3_column_text(statement, 4));
	record->TradeGroupID = sqlite3_column_int(statement, 5);
	record->RiskGroupID = sqlite3_column_int(statement, 6);
	record->CommissionGroupID = sqlite3_column_int(statement, 7);
	records.push_back(record);
}

