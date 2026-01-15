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

	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentUpdateStatement = nullptr;
	m_InstrumentSelectStatement = nullptr;
	m_InstrumentTruncateStatement = nullptr;

	m_DepthMarketDataInsertStatement = nullptr;
	m_DepthMarketDataDeleteStatement = nullptr;
	m_DepthMarketDataUpdateStatement = nullptr;
	m_DepthMarketDataSelectStatement = nullptr;
	m_DepthMarketDataTruncateStatement = nullptr;

	m_BarMarketDataInsertStatement = nullptr;
	m_BarMarketDataDeleteStatement = nullptr;
	m_BarMarketDataUpdateStatement = nullptr;
	m_BarMarketDataSelectStatement = nullptr;
	m_BarMarketDataTruncateStatement = nullptr;

	m_PrimaryAccountInsertStatement = nullptr;
	m_PrimaryAccountDeleteStatement = nullptr;
	m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	m_PrimaryAccountUpdateStatement = nullptr;
	m_PrimaryAccountSelectStatement = nullptr;
	m_PrimaryAccountTruncateStatement = nullptr;

	m_AccountInsertStatement = nullptr;
	m_AccountDeleteStatement = nullptr;
	m_AccountUpdateStatement = nullptr;
	m_AccountSelectStatement = nullptr;
	m_AccountTruncateStatement = nullptr;

	m_OrderInsertStatement = nullptr;
	m_OrderDeleteStatement = nullptr;
	m_OrderUpdateStatement = nullptr;
	m_OrderSelectStatement = nullptr;
	m_OrderTruncateStatement = nullptr;

	m_TradeInsertStatement = nullptr;
	m_TradeDeleteStatement = nullptr;
	m_TradeUpdateStatement = nullptr;
	m_TradeSelectStatement = nullptr;
	m_TradeTruncateStatement = nullptr;

	m_AccountLoginSessionInsertStatement = nullptr;
	m_AccountLoginSessionDeleteStatement = nullptr;
	m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	m_AccountLoginSessionUpdateStatement = nullptr;
	m_AccountLoginSessionSelectStatement = nullptr;
	m_AccountLoginSessionTruncateStatement = nullptr;

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
	if (m_BarMarketDataInsertStatement != nullptr)
	{
		sqlite3_finalize(m_BarMarketDataInsertStatement);
		m_BarMarketDataInsertStatement = nullptr;
	}
	if (m_BarMarketDataDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_BarMarketDataDeleteStatement);
		m_BarMarketDataDeleteStatement = nullptr;
	}
	if (m_BarMarketDataUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_BarMarketDataUpdateStatement);
		m_BarMarketDataUpdateStatement = nullptr;
	}
	if (m_BarMarketDataSelectStatement != nullptr)
	{
		sqlite3_finalize(m_BarMarketDataSelectStatement);
		m_BarMarketDataSelectStatement = nullptr;
	}
	if (m_BarMarketDataTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_BarMarketDataTruncateStatement);
		m_BarMarketDataTruncateStatement = nullptr;
	}
	if (m_PrimaryAccountInsertStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountInsertStatement);
		m_PrimaryAccountInsertStatement = nullptr;
	}
	if (m_PrimaryAccountDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountDeleteStatement);
		m_PrimaryAccountDeleteStatement = nullptr;
	}
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountDeleteByOfferIDIndexStatement);
		m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	}
	if (m_PrimaryAccountUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountUpdateStatement);
		m_PrimaryAccountUpdateStatement = nullptr;
	}
	if (m_PrimaryAccountSelectStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountSelectStatement);
		m_PrimaryAccountSelectStatement = nullptr;
	}
	if (m_PrimaryAccountTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_PrimaryAccountTruncateStatement);
		m_PrimaryAccountTruncateStatement = nullptr;
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
	if (m_OrderInsertStatement != nullptr)
	{
		sqlite3_finalize(m_OrderInsertStatement);
		m_OrderInsertStatement = nullptr;
	}
	if (m_OrderDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_OrderDeleteStatement);
		m_OrderDeleteStatement = nullptr;
	}
	if (m_OrderUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_OrderUpdateStatement);
		m_OrderUpdateStatement = nullptr;
	}
	if (m_OrderSelectStatement != nullptr)
	{
		sqlite3_finalize(m_OrderSelectStatement);
		m_OrderSelectStatement = nullptr;
	}
	if (m_OrderTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_OrderTruncateStatement);
		m_OrderTruncateStatement = nullptr;
	}
	if (m_TradeInsertStatement != nullptr)
	{
		sqlite3_finalize(m_TradeInsertStatement);
		m_TradeInsertStatement = nullptr;
	}
	if (m_TradeDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_TradeDeleteStatement);
		m_TradeDeleteStatement = nullptr;
	}
	if (m_TradeUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_TradeUpdateStatement);
		m_TradeUpdateStatement = nullptr;
	}
	if (m_TradeSelectStatement != nullptr)
	{
		sqlite3_finalize(m_TradeSelectStatement);
		m_TradeSelectStatement = nullptr;
	}
	if (m_TradeTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_TradeTruncateStatement);
		m_TradeTruncateStatement = nullptr;
	}
	if (m_AccountLoginSessionInsertStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionInsertStatement);
		m_AccountLoginSessionInsertStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionDeleteStatement);
		m_AccountLoginSessionDeleteStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionDeleteByAccountIDIndexStatement);
		m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	}
	if (m_AccountLoginSessionUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionUpdateStatement);
		m_AccountLoginSessionUpdateStatement = nullptr;
	}
	if (m_AccountLoginSessionSelectStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionSelectStatement);
		m_AccountLoginSessionSelectStatement = nullptr;
	}
	if (m_AccountLoginSessionTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_AccountLoginSessionTruncateStatement);
		m_AccountLoginSessionTruncateStatement = nullptr;
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
	Exec("Truncate Table t_Instrument;");
	Exec("Insert Into t_Instrument select * from Init.t_Instrument;");
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Truncate Table t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	Exec("Truncate Table t_PrimaryAccount;");
	Exec("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	Exec("Truncate Table t_Account;");
	Exec("Insert Into t_Account select * from Init.t_Account;");
	Exec("Truncate Table t_Order;");
	Exec("Insert Into t_Order select * from Init.t_Order;");
	Exec("Truncate Table t_Trade;");
	Exec("Insert Into t_Trade select * from Init.t_Trade;");
	Exec("Truncate Table t_AccountLoginSession;");
	Exec("Insert Into t_AccountLoginSession select * from Init.t_AccountLoginSession;");
}
void SqliteDB::CreateTables()
{
	CreateTradingDay();
	CreateExchange();
	CreateProduct();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreatePrimaryAccount();
	CreateAccount();
	CreateOrder();
	CreateTrade();
	CreateAccountLoginSession();
}
void SqliteDB::DropTables()
{
	DropTradingDay();
	DropExchange();
	DropProduct();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropPrimaryAccount();
	DropAccount();
	DropOrder();
	DropTrade();
	DropAccountLoginSession();
}
void SqliteDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncatePrimaryAccount();
	TruncateAccount();
	TruncateOrder();
	TruncateTrade();
	TruncateAccountLoginSession();
}
void SqliteDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateAccountLoginSession();
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
void SqliteDB::CreateDepthMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_DepthMarketData(`TradingDay` text, `ExchangeID` text, `InstrumentID` text, `UpdateTs` bigint, `LastPrice` double, `PreSettlementPrice` double, `PreClosePrice` double, `PreOpenInterest` double, `OpenPrice` double, `HighestPrice` double, `LowestPrice` double, `ClosePrice` double, `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` double, `Turnover` double, `OpenInterest` double, `SettlementPrice` double, `UpperLimitPrice` double, `LowerLimitPrice` double, `AveragePrice` double, `AskPrice1` double, `AskPrice2` double, `AskPrice3` double, `AskPrice4` double, `AskPrice5` double, `AskPrice6` double, `AskPrice7` double, `AskPrice8` double, `AskPrice9` double, `AskPrice10` double, `AskVolume1` bigint, `AskVolume2` bigint, `AskVolume3` bigint, `AskVolume4` bigint, `AskVolume5` bigint, `AskVolume6` bigint, `AskVolume7` bigint, `AskVolume8` bigint, `AskVolume9` bigint, `AskVolume10` bigint, `BidPrice1` double, `BidPrice2` double, `BidPrice3` double, `BidPrice4` double, `BidPrice5` double, `BidPrice6` double, `BidPrice7` double, `BidPrice8` double, `BidPrice9` double, `BidPrice10` double, `BidVolume1` bigint, `BidVolume2` bigint, `BidVolume3` bigint, `BidVolume4` bigint, `BidVolume5` bigint, `BidVolume6` bigint, `BidVolume7` bigint, `BidVolume8` bigint, `BidVolume9` bigint, `BidVolume10` bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateDepthMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateDepthMarketData Spend:%lldms", duration);
}
void SqliteDB::DropDepthMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_DepthMarketData;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropDepthMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropDepthMarketData Spend:%lldms", duration);
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
void SqliteDB::SelectDepthMarketData(std::list<DepthMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_DepthMarketData where TradingDay >= ?;", -1, &m_DepthMarketDataSelectStatement, nullptr);
	}
	sqlite3_bind_text(m_DepthMarketDataSelectStatement, 1, tradingDay, sizeof(tradingDay), nullptr);

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
void SqliteDB::CreateBarMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_BarMarketData(`TradingDay` text, `ExchangeID` text, `InstrumentID` text, `BarPreces` int, `BarPeriod` int, `BarTime` bigint, `UpdateTs` bigint, `PreSettlementPrice` double, `PreClosePrice` double, `Open` double, `High` double, `Low` double, `Close` double, `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` double, `Turnover` double, `OpenInterest` double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateBarMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateBarMarketData Spend:%lldms", duration);
}
void SqliteDB::DropBarMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_BarMarketData;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropBarMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropBarMarketData Spend:%lldms", duration);
}
void SqliteDB::InsertBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_BarMarketData Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_BarMarketDataInsertStatement, nullptr);
	}
	SetStatementForBarMarketDataRecord(m_BarMarketDataInsertStatement, record);
	
	auto rc = sqlite3_step(m_BarMarketDataInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_BarMarketDataInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertBarMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertBarMarketData(std::list<BarMarketData*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_BarMarketData Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertBarMarketData Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_BarMarketData Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertBarMarketData Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertBarMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_BarMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;", -1, &m_BarMarketDataDeleteStatement, nullptr);
	}
	SetStatementForBarMarketDataPrimaryKey(m_BarMarketDataDeleteStatement, record->TradingDay, record->ExchangeID, record->InstrumentID, record->BarPreces, record->BarPeriod, record->BarTime);

	auto rc = sqlite3_step(m_BarMarketDataDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_BarMarketDataDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteBarMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_BarMarketData set UpdateTs = ?, PreSettlementPrice = ?, PreClosePrice = ?, Open = ?, High = ?, Low = ?, Close = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;", -1, &m_BarMarketDataUpdateStatement, nullptr);
	}
	SetStatementForBarMarketDataRecordUpdate(m_BarMarketDataUpdateStatement, record);
	
	auto rc = sqlite3_step(m_BarMarketDataUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateBarMarketData failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_BarMarketDataUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateBarMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::SelectBarMarketData(std::list<BarMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_BarMarketData where TradingDay >= ?;", -1, &m_BarMarketDataSelectStatement, nullptr);
	}
	sqlite3_bind_text(m_BarMarketDataSelectStatement, 1, tradingDay, sizeof(tradingDay), nullptr);

	while (sqlite3_step(m_BarMarketDataSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_BarMarketDataSelectStatement, records);
	}
	sqlite3_reset(m_BarMarketDataSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectBarMarketData Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateBarMarketData()
{
	auto start = steady_clock::now();
	if (m_BarMarketDataTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_BarMarketData;", -1, &m_BarMarketDataTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_BarMarketDataTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateBarMarketData failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_BarMarketDataTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateBarMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreatePrimaryAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_PrimaryAccount(`PrimaryAccountID` text, `PrimaryAccountName` text, `AccountClass` int, `BrokerPassword` text, `OfferID` int, `IsAllowLogin` int, `IsSimulateAccount` int, `LoginStatus` int, `InitStatus` int, PRIMARY KEY(PrimaryAccountID));CREATE INDEX PrimaryAccountOfferID ON t_PrimaryAccount(OfferID);", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreatePrimaryAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePrimaryAccount Spend:%lldms", duration);
}
void SqliteDB::DropPrimaryAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP INDEX PrimaryAccountOfferID;DROP TABLE IF EXISTS t_PrimaryAccount;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropPrimaryAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPrimaryAccount Spend:%lldms", duration);
}
void SqliteDB::InsertPrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_PrimaryAccount Values(?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_PrimaryAccountInsertStatement, nullptr);
	}
	SetStatementForPrimaryAccountRecord(m_PrimaryAccountInsertStatement, record);
	
	auto rc = sqlite3_step(m_PrimaryAccountInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertPrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PrimaryAccountInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertPrimaryAccount Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertPrimaryAccount(std::list<PrimaryAccount*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_PrimaryAccount Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_PrimaryAccount Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeletePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PrimaryAccount where PrimaryAccountID = ?;", -1, &m_PrimaryAccountDeleteStatement, nullptr);
	}
	SetStatementForPrimaryAccountPrimaryKey(m_PrimaryAccountDeleteStatement, record->PrimaryAccountID);

	auto rc = sqlite3_step(m_PrimaryAccountDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PrimaryAccountDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccount Spend:%lldms", duration);
	}
}
void SqliteDB::DeletePrimaryAccountByOfferIDIndex(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PrimaryAccount where OfferID = ?;", -1, &m_PrimaryAccountDeleteByOfferIDIndexStatement, nullptr);
	}
	SetStatementForPrimaryAccountIndexOfferID(m_PrimaryAccountDeleteByOfferIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_PrimaryAccountDeleteByOfferIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccountByOfferIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PrimaryAccountDeleteByOfferIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccountByOfferIDIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdatePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_PrimaryAccount set PrimaryAccountName = ?, AccountClass = ?, BrokerPassword = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;", -1, &m_PrimaryAccountUpdateStatement, nullptr);
	}
	SetStatementForPrimaryAccountRecordUpdate(m_PrimaryAccountUpdateStatement, record);
	
	auto rc = sqlite3_step(m_PrimaryAccountUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PrimaryAccountUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount Spend:%lldms", duration);
	}
}
void SqliteDB::SelectPrimaryAccount(std::list<PrimaryAccount*>& records)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_PrimaryAccount;", -1, &m_PrimaryAccountSelectStatement, nullptr);
	}

	while (sqlite3_step(m_PrimaryAccountSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_PrimaryAccountSelectStatement, records);
	}
	sqlite3_reset(m_PrimaryAccountSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPrimaryAccount Spend:%lldms", duration);
	}
}
void SqliteDB::TruncatePrimaryAccount()
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PrimaryAccount;", -1, &m_PrimaryAccountTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_PrimaryAccountTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncatePrimaryAccount failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PrimaryAccountTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncatePrimaryAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void SqliteDB::CreateOrder()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Order(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `OrderID` int, `OrderSysID` text, `Direction` int, `OffsetFlag` int, `OrderPriceType` int, `Price` double, `Volume` bigint, `VolumeTotal` bigint, `VolumeTraded` bigint, `VolumeMultiple` int, `OrderStatus` int, `OrderDate` text, `OrderTime` text, `CancelDate` text, `CancelTime` text, `SessionID` bigint, `ClientOrderID` int, `RequestID` int, `OfferID` int, `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, `FrozenCash` double, `FrozenMargin` double, `FrozenCommission` double, `RebuildMark` int, `IsForceClose` int, UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateOrder failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateOrder Spend:%lldms", duration);
}
void SqliteDB::DropOrder()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Order;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropOrder failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropOrder Spend:%lldms", duration);
}
void SqliteDB::InsertOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Order Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_OrderInsertStatement, nullptr);
	}
	SetStatementForOrderRecord(m_OrderInsertStatement, record);
	
	auto rc = sqlite3_step(m_OrderInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_OrderInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertOrder Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertOrder(std::list<Order*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Order Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertOrder Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Order Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertOrder Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertOrder RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Order where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", -1, &m_OrderDeleteStatement, nullptr);
	}
	SetStatementForOrderPrimaryKey(m_OrderDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->OrderID);

	auto rc = sqlite3_step(m_OrderDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_OrderDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteOrder Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Order set AccountType = ?, ProductClass = ?, OrderSysID = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ?, RequestID = ?, OfferID = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, RebuildMark = ?, IsForceClose = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", -1, &m_OrderUpdateStatement, nullptr);
	}
	SetStatementForOrderRecordUpdate(m_OrderUpdateStatement, record);
	
	auto rc = sqlite3_step(m_OrderUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_OrderUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder Spend:%lldms", duration);
	}
}
void SqliteDB::SelectOrder(std::list<Order*>& records)
{
	auto start = steady_clock::now();
	if (m_OrderSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Order;", -1, &m_OrderSelectStatement, nullptr);
	}

	while (sqlite3_step(m_OrderSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_OrderSelectStatement, records);
	}
	sqlite3_reset(m_OrderSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectOrder Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateOrder()
{
	auto start = steady_clock::now();
	if (m_OrderTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Order;", -1, &m_OrderTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_OrderTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateOrder failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_OrderTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateOrder Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateTrade()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_Trade(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `OrderID` int, `OrderSysID` text, `TradeID` text, `Direction` int, `OffsetFlag` int, `Price` double, `Volume` bigint, `VolumeMultiple` int, `TradeAmount` double, `Commission` double, `TradeDate` text, `TradeTime` text, PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction));", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateTrade failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTrade Spend:%lldms", duration);
}
void SqliteDB::DropTrade()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP TABLE IF EXISTS t_Trade;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropTrade failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTrade Spend:%lldms", duration);
}
void SqliteDB::InsertTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Trade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_TradeInsertStatement, nullptr);
	}
	SetStatementForTradeRecord(m_TradeInsertStatement, record);
	
	auto rc = sqlite3_step(m_TradeInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradeInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertTrade Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertTrade(std::list<Trade*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Trade Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertTrade Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Trade Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertTrade Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertTrade RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Trade where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", -1, &m_TradeDeleteStatement, nullptr);
	}
	SetStatementForTradePrimaryKey(m_TradeDeleteStatement, record->TradingDay, record->ExchangeID, record->TradeID, record->Direction);

	auto rc = sqlite3_step(m_TradeDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradeDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTrade Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Trade set AccountID = ?, AccountType = ?, InstrumentID = ?, ProductClass = ?, OrderID = ?, OrderSysID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", -1, &m_TradeUpdateStatement, nullptr);
	}
	SetStatementForTradeRecordUpdate(m_TradeUpdateStatement, record);
	
	auto rc = sqlite3_step(m_TradeUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradeUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade Spend:%lldms", duration);
	}
}
void SqliteDB::SelectTrade(std::list<Trade*>& records)
{
	auto start = steady_clock::now();
	if (m_TradeSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Trade;", -1, &m_TradeSelectStatement, nullptr);
	}

	while (sqlite3_step(m_TradeSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_TradeSelectStatement, records);
	}
	sqlite3_reset(m_TradeSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTrade Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateTrade()
{
	auto start = steady_clock::now();
	if (m_TradeTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Trade;", -1, &m_TradeTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_TradeTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateTrade failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradeTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateTrade Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateAccountLoginSession()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "CREATE TABLE IF NOT EXISTS t_AccountLoginSession(`AccountID` text, `SessionID` bigint, `IPAddress` text, PRIMARY KEY(SessionID));CREATE INDEX AccountLoginSessionAccountID ON t_AccountLoginSession(AccountID);", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateAccountLoginSession failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccountLoginSession Spend:%lldms", duration);
}
void SqliteDB::DropAccountLoginSession()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	auto rc = sqlite3_exec(m_DB, "DROP INDEX AccountLoginSessionAccountID;DROP TABLE IF EXISTS t_AccountLoginSession;", nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropAccountLoginSession failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccountLoginSession Spend:%lldms", duration);
}
void SqliteDB::InsertAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_AccountLoginSession Values(?, ?, ?);", -1, &m_AccountLoginSessionInsertStatement, nullptr);
	}
	SetStatementForAccountLoginSessionRecord(m_AccountLoginSessionInsertStatement, record);
	
	auto rc = sqlite3_step(m_AccountLoginSessionInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountLoginSessionInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertAccountLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertAccountLoginSession(std::list<AccountLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_AccountLoginSession Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_AccountLoginSession Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_AccountLoginSession where SessionID = ?;", -1, &m_AccountLoginSessionDeleteStatement, nullptr);
	}
	SetStatementForAccountLoginSessionPrimaryKey(m_AccountLoginSessionDeleteStatement, record->SessionID);

	auto rc = sqlite3_step(m_AccountLoginSessionDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountLoginSessionDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::DeleteAccountLoginSessionByAccountIDIndex(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_AccountLoginSession where AccountID = ?;", -1, &m_AccountLoginSessionDeleteByAccountIDIndexStatement, nullptr);
	}
	SetStatementForAccountLoginSessionIndexAccountID(m_AccountLoginSessionDeleteByAccountIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_AccountLoginSessionDeleteByAccountIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSessionByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountLoginSessionDeleteByAccountIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSessionByAccountIDIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_AccountLoginSession set AccountID = ?, IPAddress = ? where SessionID = ?;", -1, &m_AccountLoginSessionUpdateStatement, nullptr);
	}
	SetStatementForAccountLoginSessionRecordUpdate(m_AccountLoginSessionUpdateStatement, record);
	
	auto rc = sqlite3_step(m_AccountLoginSessionUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateAccountLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountLoginSessionUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccountLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::SelectAccountLoginSession(std::list<AccountLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_AccountLoginSession;", -1, &m_AccountLoginSessionSelectStatement, nullptr);
	}

	while (sqlite3_step(m_AccountLoginSessionSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_AccountLoginSessionSelectStatement, records);
	}
	sqlite3_reset(m_AccountLoginSessionSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccountLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateAccountLoginSession()
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_AccountLoginSession;", -1, &m_AccountLoginSessionTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_AccountLoginSessionTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateAccountLoginSession failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_AccountLoginSessionTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateAccountLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void SqliteDB::SetStatementForBarMarketDataRecord(sqlite3_stmt* statement, BarMarketData* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->BarPreces));
	sqlite3_bind_int(statement, 5, record->BarPeriod);
	sqlite3_bind_int64(statement, 6, record->BarTime);
	sqlite3_bind_int64(statement, 7, record->UpdateTs);
	sqlite3_bind_double(statement, 8, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 9, record->PreClosePrice);
	sqlite3_bind_double(statement, 10, record->Open);
	sqlite3_bind_double(statement, 11, record->High);
	sqlite3_bind_double(statement, 12, record->Low);
	sqlite3_bind_double(statement, 13, record->Close);
	sqlite3_bind_int64(statement, 14, record->CurrVolume);
	sqlite3_bind_int64(statement, 15, record->Volume);
	sqlite3_bind_double(statement, 16, record->CurrTurnover);
	sqlite3_bind_double(statement, 17, record->Turnover);
	sqlite3_bind_double(statement, 18, record->OpenInterest);
}
void SqliteDB::SetStatementForBarMarketDataRecordUpdate(sqlite3_stmt* statement, BarMarketData* record)
{
	sqlite3_bind_int64(statement, 1, record->UpdateTs);
	sqlite3_bind_double(statement, 2, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 3, record->PreClosePrice);
	sqlite3_bind_double(statement, 4, record->Open);
	sqlite3_bind_double(statement, 5, record->High);
	sqlite3_bind_double(statement, 6, record->Low);
	sqlite3_bind_double(statement, 7, record->Close);
	sqlite3_bind_int64(statement, 8, record->CurrVolume);
	sqlite3_bind_int64(statement, 9, record->Volume);
	sqlite3_bind_double(statement, 10, record->CurrTurnover);
	sqlite3_bind_double(statement, 11, record->Turnover);
	sqlite3_bind_double(statement, 12, record->OpenInterest);
	sqlite3_bind_text(statement, 13, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 14, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 15, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 16, int(record->BarPreces));
	sqlite3_bind_int(statement, 17, record->BarPeriod);
	sqlite3_bind_int64(statement, 18, record->BarTime);
}
void SqliteDB::SetStatementForBarMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 4, int(BarPreces));
	sqlite3_bind_int(statement, 5, BarPeriod);
	sqlite3_bind_int64(statement, 6, BarTime);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<BarMarketData*>& records)
{
	BarMarketData* record = BarMarketData::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 2));
	record->BarPreces = BarPrecesType(sqlite3_column_int(statement, 3));
	record->BarPeriod = sqlite3_column_int(statement, 4);
	record->BarTime = sqlite3_column_int64(statement, 5);
	record->UpdateTs = sqlite3_column_int64(statement, 6);
	record->PreSettlementPrice = sqlite3_column_double(statement, 7);
	record->PreClosePrice = sqlite3_column_double(statement, 8);
	record->Open = sqlite3_column_double(statement, 9);
	record->High = sqlite3_column_double(statement, 10);
	record->Low = sqlite3_column_double(statement, 11);
	record->Close = sqlite3_column_double(statement, 12);
	record->CurrVolume = sqlite3_column_int64(statement, 13);
	record->Volume = sqlite3_column_int64(statement, 14);
	record->CurrTurnover = sqlite3_column_double(statement, 15);
	record->Turnover = sqlite3_column_double(statement, 16);
	record->OpenInterest = sqlite3_column_double(statement, 17);
	records.push_back(record);
}
void SqliteDB::SetStatementForPrimaryAccountRecord(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_text(statement, 1, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_text(statement, 2, record->PrimaryAccountName, sizeof(record->PrimaryAccountName), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountClass));
	sqlite3_bind_text(statement, 4, record->BrokerPassword, sizeof(record->BrokerPassword), nullptr);
	sqlite3_bind_int(statement, 5, record->OfferID);
	sqlite3_bind_int(statement, 6, record->IsAllowLogin);
	sqlite3_bind_int(statement, 7, record->IsSimulateAccount);
	sqlite3_bind_int(statement, 8, int(record->LoginStatus));
	sqlite3_bind_int(statement, 9, int(record->InitStatus));
}
void SqliteDB::SetStatementForPrimaryAccountRecordUpdate(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_text(statement, 1, record->PrimaryAccountName, sizeof(record->PrimaryAccountName), nullptr);
	sqlite3_bind_int(statement, 2, int(record->AccountClass));
	sqlite3_bind_text(statement, 3, record->BrokerPassword, sizeof(record->BrokerPassword), nullptr);
	sqlite3_bind_int(statement, 4, record->OfferID);
	sqlite3_bind_int(statement, 5, record->IsAllowLogin);
	sqlite3_bind_int(statement, 6, record->IsSimulateAccount);
	sqlite3_bind_int(statement, 7, int(record->LoginStatus));
	sqlite3_bind_int(statement, 8, int(record->InitStatus));
	sqlite3_bind_text(statement, 9, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
}
void SqliteDB::SetStatementForPrimaryAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& PrimaryAccountID)
{
	sqlite3_bind_text(statement, 1, PrimaryAccountID, sizeof(PrimaryAccountID), nullptr);
}
void SqliteDB::SetStatementForPrimaryAccountIndexOfferID(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_int(statement, 1, record->OfferID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<PrimaryAccount*>& records)
{
	PrimaryAccount* record = PrimaryAccount::Allocate();
	Strcpy(record->PrimaryAccountID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->PrimaryAccountName, (const char*)sqlite3_column_text(statement, 1));
	record->AccountClass = AccountClassType(sqlite3_column_int(statement, 2));
	Strcpy(record->BrokerPassword, (const char*)sqlite3_column_text(statement, 3));
	record->OfferID = sqlite3_column_int(statement, 4);
	record->IsAllowLogin = sqlite3_column_int(statement, 5);
	record->IsSimulateAccount = sqlite3_column_int(statement, 6);
	record->LoginStatus = LoginStatusType(sqlite3_column_int(statement, 7));
	record->InitStatus = InitStatusType(sqlite3_column_int(statement, 8));
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
void SqliteDB::SetStatementForOrderRecord(sqlite3_stmt* statement, Order* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, record->OrderID);
	sqlite3_bind_text(statement, 8, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 9, int(record->Direction));
	sqlite3_bind_int(statement, 10, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 11, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 12, record->Price);
	sqlite3_bind_int64(statement, 13, record->Volume);
	sqlite3_bind_int64(statement, 14, record->VolumeTotal);
	sqlite3_bind_int64(statement, 15, record->VolumeTraded);
	sqlite3_bind_int(statement, 16, record->VolumeMultiple);
	sqlite3_bind_int(statement, 17, int(record->OrderStatus));
	sqlite3_bind_text(statement, 18, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 19, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 20, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 21, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 22, record->SessionID);
	sqlite3_bind_int(statement, 23, record->ClientOrderID);
	sqlite3_bind_int(statement, 24, record->RequestID);
	sqlite3_bind_int(statement, 25, record->OfferID);
	sqlite3_bind_int(statement, 26, record->TradeGroupID);
	sqlite3_bind_int(statement, 27, record->RiskGroupID);
	sqlite3_bind_int(statement, 28, record->CommissionGroupID);
	sqlite3_bind_double(statement, 29, record->FrozenCash);
	sqlite3_bind_double(statement, 30, record->FrozenMargin);
	sqlite3_bind_double(statement, 31, record->FrozenCommission);
	sqlite3_bind_int(statement, 32, record->RebuildMark);
	sqlite3_bind_int(statement, 33, record->IsForceClose);
}
void SqliteDB::SetStatementForOrderRecordUpdate(sqlite3_stmt* statement, Order* record)
{
	sqlite3_bind_int(statement, 1, int(record->AccountType));
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_text(statement, 3, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->Direction));
	sqlite3_bind_int(statement, 5, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 6, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 7, record->Price);
	sqlite3_bind_int64(statement, 8, record->Volume);
	sqlite3_bind_int64(statement, 9, record->VolumeTotal);
	sqlite3_bind_int64(statement, 10, record->VolumeTraded);
	sqlite3_bind_int(statement, 11, record->VolumeMultiple);
	sqlite3_bind_int(statement, 12, int(record->OrderStatus));
	sqlite3_bind_text(statement, 13, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 14, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 15, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 16, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 17, record->SessionID);
	sqlite3_bind_int(statement, 18, record->ClientOrderID);
	sqlite3_bind_int(statement, 19, record->RequestID);
	sqlite3_bind_int(statement, 20, record->OfferID);
	sqlite3_bind_int(statement, 21, record->TradeGroupID);
	sqlite3_bind_int(statement, 22, record->RiskGroupID);
	sqlite3_bind_int(statement, 23, record->CommissionGroupID);
	sqlite3_bind_double(statement, 24, record->FrozenCash);
	sqlite3_bind_double(statement, 25, record->FrozenMargin);
	sqlite3_bind_double(statement, 26, record->FrozenCommission);
	sqlite3_bind_int(statement, 27, record->RebuildMark);
	sqlite3_bind_int(statement, 28, record->IsForceClose);
	sqlite3_bind_text(statement, 29, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 30, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 31, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 32, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 33, record->OrderID);
}
void SqliteDB::SetStatementForOrderPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
	sqlite3_bind_text(statement, 3, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, OrderID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Order*>& records)
{
	Order* record = Order::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->OrderID = sqlite3_column_int(statement, 6);
	Strcpy(record->OrderSysID, (const char*)sqlite3_column_text(statement, 7));
	record->Direction = DirectionType(sqlite3_column_int(statement, 8));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 9));
	record->OrderPriceType = OrderPriceTypeType(sqlite3_column_int(statement, 10));
	record->Price = sqlite3_column_double(statement, 11);
	record->Volume = sqlite3_column_int64(statement, 12);
	record->VolumeTotal = sqlite3_column_int64(statement, 13);
	record->VolumeTraded = sqlite3_column_int64(statement, 14);
	record->VolumeMultiple = sqlite3_column_int(statement, 15);
	record->OrderStatus = OrderStatusType(sqlite3_column_int(statement, 16));
	Strcpy(record->OrderDate, (const char*)sqlite3_column_text(statement, 17));
	Strcpy(record->OrderTime, (const char*)sqlite3_column_text(statement, 18));
	Strcpy(record->CancelDate, (const char*)sqlite3_column_text(statement, 19));
	Strcpy(record->CancelTime, (const char*)sqlite3_column_text(statement, 20));
	record->SessionID = sqlite3_column_int64(statement, 21);
	record->ClientOrderID = sqlite3_column_int(statement, 22);
	record->RequestID = sqlite3_column_int(statement, 23);
	record->OfferID = sqlite3_column_int(statement, 24);
	record->TradeGroupID = sqlite3_column_int(statement, 25);
	record->RiskGroupID = sqlite3_column_int(statement, 26);
	record->CommissionGroupID = sqlite3_column_int(statement, 27);
	record->FrozenCash = sqlite3_column_double(statement, 28);
	record->FrozenMargin = sqlite3_column_double(statement, 29);
	record->FrozenCommission = sqlite3_column_double(statement, 30);
	record->RebuildMark = sqlite3_column_int(statement, 31);
	record->IsForceClose = sqlite3_column_int(statement, 32);
	records.push_back(record);
}
void SqliteDB::SetStatementForTradeRecord(sqlite3_stmt* statement, Trade* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, record->OrderID);
	sqlite3_bind_text(statement, 8, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_text(statement, 9, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 10, int(record->Direction));
	sqlite3_bind_int(statement, 11, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 12, record->Price);
	sqlite3_bind_int64(statement, 13, record->Volume);
	sqlite3_bind_int(statement, 14, record->VolumeMultiple);
	sqlite3_bind_double(statement, 15, record->TradeAmount);
	sqlite3_bind_double(statement, 16, record->Commission);
	sqlite3_bind_text(statement, 17, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 18, record->TradeTime, sizeof(record->TradeTime), nullptr);
}
void SqliteDB::SetStatementForTradeRecordUpdate(sqlite3_stmt* statement, Trade* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 2, int(record->AccountType));
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->ProductClass));
	sqlite3_bind_int(statement, 5, record->OrderID);
	sqlite3_bind_text(statement, 6, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 7, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 8, record->Price);
	sqlite3_bind_int64(statement, 9, record->Volume);
	sqlite3_bind_int(statement, 10, record->VolumeMultiple);
	sqlite3_bind_double(statement, 11, record->TradeAmount);
	sqlite3_bind_double(statement, 12, record->Commission);
	sqlite3_bind_text(statement, 13, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 14, record->TradeTime, sizeof(record->TradeTime), nullptr);
	sqlite3_bind_text(statement, 15, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 16, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 17, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 18, int(record->Direction));
}
void SqliteDB::SetStatementForTradePrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, TradeID, sizeof(TradeID), nullptr);
	sqlite3_bind_int(statement, 4, int(Direction));
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Trade*>& records)
{
	Trade* record = Trade::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->OrderID = sqlite3_column_int(statement, 6);
	Strcpy(record->OrderSysID, (const char*)sqlite3_column_text(statement, 7));
	Strcpy(record->TradeID, (const char*)sqlite3_column_text(statement, 8));
	record->Direction = DirectionType(sqlite3_column_int(statement, 9));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 10));
	record->Price = sqlite3_column_double(statement, 11);
	record->Volume = sqlite3_column_int64(statement, 12);
	record->VolumeMultiple = sqlite3_column_int(statement, 13);
	record->TradeAmount = sqlite3_column_double(statement, 14);
	record->Commission = sqlite3_column_double(statement, 15);
	Strcpy(record->TradeDate, (const char*)sqlite3_column_text(statement, 16));
	Strcpy(record->TradeTime, (const char*)sqlite3_column_text(statement, 17));
	records.push_back(record);
}
void SqliteDB::SetStatementForAccountLoginSessionRecord(sqlite3_stmt* statement, AccountLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int64(statement, 2, record->SessionID);
	sqlite3_bind_text(statement, 3, record->IPAddress, sizeof(record->IPAddress), nullptr);
}
void SqliteDB::SetStatementForAccountLoginSessionRecordUpdate(sqlite3_stmt* statement, AccountLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 2, record->IPAddress, sizeof(record->IPAddress), nullptr);
	sqlite3_bind_int64(statement, 3, record->SessionID);
}
void SqliteDB::SetStatementForAccountLoginSessionPrimaryKey(sqlite3_stmt* statement, const SessionIDType& SessionID)
{
	sqlite3_bind_int64(statement, 1, SessionID);
}
void SqliteDB::SetStatementForAccountLoginSessionIndexAccountID(sqlite3_stmt* statement, AccountLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<AccountLoginSession*>& records)
{
	AccountLoginSession* record = AccountLoginSession::Allocate();
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 0));
	record->SessionID = sqlite3_column_int64(statement, 1);
	Strcpy(record->IPAddress, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}

