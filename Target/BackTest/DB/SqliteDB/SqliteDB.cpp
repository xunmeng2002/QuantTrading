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

	m_CapitalInsertStatement = nullptr;
	m_CapitalDeleteStatement = nullptr;
	m_CapitalUpdateStatement = nullptr;
	m_CapitalSelectStatement = nullptr;
	m_CapitalTruncateStatement = nullptr;

	m_PositionInsertStatement = nullptr;
	m_PositionDeleteStatement = nullptr;
	m_PositionDeleteByAccountIndexStatement = nullptr;
	m_PositionUpdateStatement = nullptr;
	m_PositionSelectStatement = nullptr;
	m_PositionTruncateStatement = nullptr;

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

	m_DepthMarketDataInsertStatement = nullptr;
	m_DepthMarketDataDeleteStatement = nullptr;
	m_DepthMarketDataUpdateStatement = nullptr;
	m_DepthMarketDataSelectStatement = nullptr;
	m_DepthMarketDataTruncateStatement = nullptr;

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
	if (m_CapitalInsertStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalInsertStatement);
		m_CapitalInsertStatement = nullptr;
	}
	if (m_CapitalDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalDeleteStatement);
		m_CapitalDeleteStatement = nullptr;
	}
	if (m_CapitalUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalUpdateStatement);
		m_CapitalUpdateStatement = nullptr;
	}
	if (m_CapitalSelectStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalSelectStatement);
		m_CapitalSelectStatement = nullptr;
	}
	if (m_CapitalTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalTruncateStatement);
		m_CapitalTruncateStatement = nullptr;
	}
	if (m_PositionInsertStatement != nullptr)
	{
		sqlite3_finalize(m_PositionInsertStatement);
		m_PositionInsertStatement = nullptr;
	}
	if (m_PositionDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDeleteStatement);
		m_PositionDeleteStatement = nullptr;
	}
	if (m_PositionDeleteByAccountIndexStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDeleteByAccountIndexStatement);
		m_PositionDeleteByAccountIndexStatement = nullptr;
	}
	if (m_PositionUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_PositionUpdateStatement);
		m_PositionUpdateStatement = nullptr;
	}
	if (m_PositionSelectStatement != nullptr)
	{
		sqlite3_finalize(m_PositionSelectStatement);
		m_PositionSelectStatement = nullptr;
	}
	if (m_PositionTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_PositionTruncateStatement);
		m_PositionTruncateStatement = nullptr;
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
	Exec("Truncate Table t_PrimaryAccount;");
	Exec("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	Exec("Truncate Table t_Account;");
	Exec("Insert Into t_Account select * from Init.t_Account;");
	Exec("Truncate Table t_Capital;");
	Exec("Insert Into t_Capital select * from Init.t_Capital;");
	Exec("Truncate Table t_Position;");
	Exec("Insert Into t_Position select * from Init.t_Position;");
	Exec("Truncate Table t_Order;");
	Exec("Insert Into t_Order select * from Init.t_Order;");
	Exec("Truncate Table t_Trade;");
	Exec("Insert Into t_Trade select * from Init.t_Trade;");
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
}
void SqliteDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncatePrimaryAccount();
	TruncateAccount();
	TruncateCapital();
	TruncatePosition();
	TruncateOrder();
	TruncateTrade();
	TruncateDepthMarketData();
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
void SqliteDB::SelectTradingDay(std::vector<TradingDay*>& records)
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
void SqliteDB::SelectExchange(std::vector<Exchange*>& records)
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
		sqlite3_prepare_v2(m_DB, "update t_Product set ProductName = ?, SecurityType = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and ProductID = ?;", -1, &m_ProductUpdateStatement, nullptr);
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
void SqliteDB::SelectProduct(std::vector<Product*>& records)
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
		sqlite3_prepare_v2(m_DB, "update t_Instrument set TradingDay = ?, ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, SecurityType = ?, SecurityDetailType = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;", -1, &m_InstrumentUpdateStatement, nullptr);
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
void SqliteDB::SelectInstrument(std::vector<Instrument*>& records)
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
void SqliteDB::InsertPrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_PrimaryAccount Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_PrimaryAccountInsertStatement, nullptr);
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
		sqlite3_prepare_v2(m_DB, "update t_PrimaryAccount set TradingDay = ?, PrimaryAccountName = ?, AccountClass = ?, BrokerPassword = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;", -1, &m_PrimaryAccountUpdateStatement, nullptr);
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
void SqliteDB::SelectPrimaryAccount(std::vector<PrimaryAccount*>& records)
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
void SqliteDB::InsertAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Account Values(?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_AccountInsertStatement, nullptr);
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
		sqlite3_prepare_v2(m_DB, "update t_Account set TradingDay = ?, AccountName = ?, AccountType = ?, AccountStatus = ?, Password = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ? where AccountID = ?;", -1, &m_AccountUpdateStatement, nullptr);
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
void SqliteDB::SelectAccount(std::vector<Account*>& records)
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
void SqliteDB::InsertCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Capital Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_CapitalInsertStatement, nullptr);
	}
	SetStatementForCapitalRecord(m_CapitalInsertStatement, record);
	
	auto rc = sqlite3_step(m_CapitalInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_CapitalInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertCapital Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertCapital(std::list<Capital*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Capital Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertCapital Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Capital Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertCapital Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertCapital RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Capital where AccountID = ?;", -1, &m_CapitalDeleteStatement, nullptr);
	}
	SetStatementForCapitalPrimaryKey(m_CapitalDeleteStatement, record->AccountID);

	auto rc = sqlite3_step(m_CapitalDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_CapitalDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteCapital Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Capital set TradingDay = ?, AccountType = ?, Asset = ?, PreAsset = ?, CashAsset = ?, PreCashAsset = ?, Available = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, StampTax = ?, TransferFee = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, MarketValue = ?, TotalProfit = ?, TodayProfit = ?, Deposit = ?, Withdraw = ? where AccountID = ?;", -1, &m_CapitalUpdateStatement, nullptr);
	}
	SetStatementForCapitalRecordUpdate(m_CapitalUpdateStatement, record);
	
	auto rc = sqlite3_step(m_CapitalUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateCapital failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_CapitalUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateCapital Spend:%lldms", duration);
	}
}
void SqliteDB::SelectCapital(std::vector<Capital*>& records)
{
	auto start = steady_clock::now();
	if (m_CapitalSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Capital;", -1, &m_CapitalSelectStatement, nullptr);
	}

	while (sqlite3_step(m_CapitalSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_CapitalSelectStatement, records);
	}
	sqlite3_reset(m_CapitalSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectCapital Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateCapital()
{
	auto start = steady_clock::now();
	if (m_CapitalTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Capital;", -1, &m_CapitalTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_CapitalTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateCapital failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_CapitalTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateCapital Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertPosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Position Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_PositionInsertStatement, nullptr);
	}
	SetStatementForPositionRecord(m_PositionInsertStatement, record);
	
	auto rc = sqlite3_step(m_PositionInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertPosition failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertPosition Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertPosition(std::list<Position*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Position Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertPosition Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Position Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertPosition Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertPosition RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeletePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Position where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", -1, &m_PositionDeleteStatement, nullptr);
	}
	SetStatementForPositionPrimaryKey(m_PositionDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->PosiDirection);

	auto rc = sqlite3_step(m_PositionDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePosition failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePosition Spend:%lldms", duration);
	}
}
void SqliteDB::DeletePositionByAccountIndex(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteByAccountIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Position where TradingDay = ? and AccountID = ?;", -1, &m_PositionDeleteByAccountIndexStatement, nullptr);
	}
	SetStatementForPositionIndexAccount(m_PositionDeleteByAccountIndexStatement, record);
	
	auto rc = sqlite3_step(m_PositionDeleteByAccountIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByAccountIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDeleteByAccountIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByAccountIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdatePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Position set AccountType = ?, SecurityType = ?, TotalPosition = ?, PositionFrozen = ?, TodayPosition = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, StampTax = ?, TransferFee = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, MarketValue = ?, VolumeMultiple = ?, CloseProfit = ?, CloseProfitFloat = ?, PositionProfit = ?, PositionProfitFloat = ?, LastPrice = ?, PrePrice = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", -1, &m_PositionUpdateStatement, nullptr);
	}
	SetStatementForPositionRecordUpdate(m_PositionUpdateStatement, record);
	
	auto rc = sqlite3_step(m_PositionUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdatePosition failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePosition Spend:%lldms", duration);
	}
}
void SqliteDB::SelectPosition(std::vector<Position*>& records)
{
	auto start = steady_clock::now();
	if (m_PositionSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_Position;", -1, &m_PositionSelectStatement, nullptr);
	}

	while (sqlite3_step(m_PositionSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_PositionSelectStatement, records);
	}
	sqlite3_reset(m_PositionSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPosition Spend:%lldms", duration);
	}
}
void SqliteDB::TruncatePosition()
{
	auto start = steady_clock::now();
	if (m_PositionTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Position;", -1, &m_PositionTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_PositionTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncatePosition failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncatePosition Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::InsertOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Order Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_OrderInsertStatement, nullptr);
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
		sqlite3_prepare_v2(m_DB, "update t_Order set PrimaryAccountID = ?, AccountType = ?, SecurityType = ?, OrderSysID = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ?, RequestID = ?, OfferID = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, RebuildMark = ?, IsForceClose = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;", -1, &m_OrderUpdateStatement, nullptr);
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
void SqliteDB::SelectOrder(std::vector<Order*>& records)
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
void SqliteDB::InsertTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Trade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_TradeInsertStatement, nullptr);
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
		sqlite3_prepare_v2(m_DB, "update t_Trade set AccountID = ?, PrimaryAccountID = ?, AccountType = ?, InstrumentID = ?, SecurityType = ?, OrderID = ?, OrderSysID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, StampTax = ?, TransferFee = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;", -1, &m_TradeUpdateStatement, nullptr);
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
void SqliteDB::SelectTrade(std::vector<Trade*>& records)
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
		sqlite3_prepare_v2(m_DB, "update t_DepthMarketData set LastPrice = ?, PreSettlementPrice = ?, PreClosePrice = ?, PreOpenInterest = ?, OpenPrice = ?, HighestPrice = ?, LowestPrice = ?, ClosePrice = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ?, SettlementPrice = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, AveragePrice = ?, UpdateTs = ?, AskPrice1 = ?, AskPrice2 = ?, AskPrice3 = ?, AskPrice4 = ?, AskPrice5 = ?, AskPrice6 = ?, AskPrice7 = ?, AskPrice8 = ?, AskPrice9 = ?, AskPrice10 = ?, AskVolume1 = ?, AskVolume2 = ?, AskVolume3 = ?, AskVolume4 = ?, AskVolume5 = ?, AskVolume6 = ?, AskVolume7 = ?, AskVolume8 = ?, AskVolume9 = ?, AskVolume10 = ?, BidPrice1 = ?, BidPrice2 = ?, BidPrice3 = ?, BidPrice4 = ?, BidPrice5 = ?, BidPrice6 = ?, BidPrice7 = ?, BidPrice8 = ?, BidPrice9 = ?, BidPrice10 = ?, BidVolume1 = ?, BidVolume2 = ?, BidVolume3 = ?, BidVolume4 = ?, BidVolume5 = ?, BidVolume6 = ?, BidVolume7 = ?, BidVolume8 = ?, BidVolume9 = ?, BidVolume10 = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;", -1, &m_DepthMarketDataUpdateStatement, nullptr);
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
void SqliteDB::SelectDepthMarketData(std::vector<DepthMarketData*>& records)
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


void SqliteDB::SetStatementForTradingDayRecord(sqlite3_stmt* statement, TradingDay* record)
{
	sqlite3_bind_text(statement, 1, record->PK, sizeof(record->PK), nullptr);
	sqlite3_bind_text(statement, 2, record->CurrTradingDay, sizeof(record->CurrTradingDay), nullptr);
	sqlite3_bind_text(statement, 3, record->PreTradingDay, sizeof(record->PreTradingDay), nullptr);
}
void SqliteDB::SetStatementForTradingDayRecordUpdate(sqlite3_stmt* statement, TradingDay* record)
{
	sqlite3_bind_text(statement, 1, record->CurrTradingDay, sizeof(record->CurrTradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->PreTradingDay, sizeof(record->PreTradingDay), nullptr);
	sqlite3_bind_text(statement, 3, record->PK, sizeof(record->PK), nullptr);
}
void SqliteDB::SetStatementForTradingDayPrimaryKey(sqlite3_stmt* statement, const UserIDType& PK)
{
	sqlite3_bind_text(statement, 1, PK, sizeof(PK), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<TradingDay*>& records)
{
	TradingDay* record = TradingDay::Allocate();
	Strcpy(record->PK, (const char*)sqlite3_column_text(statement, 0));
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
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Exchange*>& records)
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
	sqlite3_bind_int(statement, 4, int(record->SecurityType));
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
	sqlite3_bind_int(statement, 2, int(record->SecurityType));
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
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Product*>& records)
{
	Product* record = Product::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->ProductName, (const char*)sqlite3_column_text(statement, 2));
	record->SecurityType = SecurityTypeType(sqlite3_column_int(statement, 3));
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
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_text(statement, 4, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 6, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 7, int(record->SecurityType));
	sqlite3_bind_int(statement, 8, int(record->SecurityDetailType));
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
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeInstID, sizeof(record->ExchangeInstID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentName, sizeof(record->InstrumentName), nullptr);
	sqlite3_bind_text(statement, 4, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->SecurityType));
	sqlite3_bind_int(statement, 6, int(record->SecurityDetailType));
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
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Instrument*>& records)
{
	Instrument* record = Instrument::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->ExchangeInstID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentName, (const char*)sqlite3_column_text(statement, 4));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 5));
	record->SecurityType = SecurityTypeType(sqlite3_column_int(statement, 6));
	record->SecurityDetailType = SecurityDetailTypeType(sqlite3_column_int(statement, 7));
	record->VolumeMultiple = sqlite3_column_int(statement, 8);
	record->PriceTick = sqlite3_column_double(statement, 9);
	record->MaxMarketOrderVolume = sqlite3_column_int64(statement, 10);
	record->MinMarketOrderVolume = sqlite3_column_int64(statement, 11);
	record->MaxLimitOrderVolume = sqlite3_column_int64(statement, 12);
	record->MinLimitOrderVolume = sqlite3_column_int64(statement, 13);
	Strcpy(record->SessionName, (const char*)sqlite3_column_text(statement, 14));
	records.push_back(record);
}
void SqliteDB::SetStatementForPrimaryAccountRecord(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->PrimaryAccountName, sizeof(record->PrimaryAccountName), nullptr);
	sqlite3_bind_int(statement, 4, int(record->AccountClass));
	sqlite3_bind_text(statement, 5, record->BrokerPassword, sizeof(record->BrokerPassword), nullptr);
	sqlite3_bind_int(statement, 6, record->OfferID);
	sqlite3_bind_int(statement, 7, record->IsAllowLogin);
	sqlite3_bind_int(statement, 8, record->IsSimulateAccount);
	sqlite3_bind_int(statement, 9, int(record->LoginStatus));
	sqlite3_bind_int(statement, 10, int(record->InitStatus));
}
void SqliteDB::SetStatementForPrimaryAccountRecordUpdate(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->PrimaryAccountName, sizeof(record->PrimaryAccountName), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountClass));
	sqlite3_bind_text(statement, 4, record->BrokerPassword, sizeof(record->BrokerPassword), nullptr);
	sqlite3_bind_int(statement, 5, record->OfferID);
	sqlite3_bind_int(statement, 6, record->IsAllowLogin);
	sqlite3_bind_int(statement, 7, record->IsSimulateAccount);
	sqlite3_bind_int(statement, 8, int(record->LoginStatus));
	sqlite3_bind_int(statement, 9, int(record->InitStatus));
	sqlite3_bind_text(statement, 10, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
}
void SqliteDB::SetStatementForPrimaryAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& PrimaryAccountID)
{
	sqlite3_bind_text(statement, 1, PrimaryAccountID, sizeof(PrimaryAccountID), nullptr);
}
void SqliteDB::SetStatementForPrimaryAccountIndexOfferID(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_int(statement, 1, record->OfferID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<PrimaryAccount*>& records)
{
	PrimaryAccount* record = PrimaryAccount::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->PrimaryAccountID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->PrimaryAccountName, (const char*)sqlite3_column_text(statement, 2));
	record->AccountClass = AccountClassType(sqlite3_column_int(statement, 3));
	Strcpy(record->BrokerPassword, (const char*)sqlite3_column_text(statement, 4));
	record->OfferID = sqlite3_column_int(statement, 5);
	record->IsAllowLogin = sqlite3_column_int(statement, 6);
	record->IsSimulateAccount = sqlite3_column_int(statement, 7);
	record->LoginStatus = LoginStatusType(sqlite3_column_int(statement, 8));
	record->InitStatus = InitStatusType(sqlite3_column_int(statement, 9));
	records.push_back(record);
}
void SqliteDB::SetStatementForAccountRecord(sqlite3_stmt* statement, Account* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->AccountName, sizeof(record->AccountName), nullptr);
	sqlite3_bind_int(statement, 4, int(record->AccountType));
	sqlite3_bind_int(statement, 5, int(record->AccountStatus));
	sqlite3_bind_text(statement, 6, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_int(statement, 7, record->TradeGroupID);
	sqlite3_bind_int(statement, 8, record->RiskGroupID);
	sqlite3_bind_int(statement, 9, record->CommissionGroupID);
}
void SqliteDB::SetStatementForAccountRecordUpdate(sqlite3_stmt* statement, Account* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountName, sizeof(record->AccountName), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_int(statement, 4, int(record->AccountStatus));
	sqlite3_bind_text(statement, 5, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_int(statement, 6, record->TradeGroupID);
	sqlite3_bind_int(statement, 7, record->RiskGroupID);
	sqlite3_bind_int(statement, 8, record->CommissionGroupID);
	sqlite3_bind_text(statement, 9, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::SetStatementForAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID)
{
	sqlite3_bind_text(statement, 1, AccountID, sizeof(AccountID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Account*>& records)
{
	Account* record = Account::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->AccountName, (const char*)sqlite3_column_text(statement, 2));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 3));
	record->AccountStatus = AccountStatusType(sqlite3_column_int(statement, 4));
	Strcpy(record->Password, (const char*)sqlite3_column_text(statement, 5));
	record->TradeGroupID = sqlite3_column_int(statement, 6);
	record->RiskGroupID = sqlite3_column_int(statement, 7);
	record->CommissionGroupID = sqlite3_column_int(statement, 8);
	records.push_back(record);
}
void SqliteDB::SetStatementForCapitalRecord(sqlite3_stmt* statement, Capital* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_double(statement, 4, record->Asset);
	sqlite3_bind_double(statement, 5, record->PreAsset);
	sqlite3_bind_double(statement, 6, record->CashAsset);
	sqlite3_bind_double(statement, 7, record->PreCashAsset);
	sqlite3_bind_double(statement, 8, record->Available);
	sqlite3_bind_double(statement, 9, record->CashIn);
	sqlite3_bind_double(statement, 10, record->CashOut);
	sqlite3_bind_double(statement, 11, record->Margin);
	sqlite3_bind_double(statement, 12, record->Commission);
	sqlite3_bind_double(statement, 13, record->StampTax);
	sqlite3_bind_double(statement, 14, record->TransferFee);
	sqlite3_bind_double(statement, 15, record->FrozenCash);
	sqlite3_bind_double(statement, 16, record->FrozenMargin);
	sqlite3_bind_double(statement, 17, record->FrozenCommission);
	sqlite3_bind_double(statement, 18, record->FrozenStampTax);
	sqlite3_bind_double(statement, 19, record->FrozenTransferFee);
	sqlite3_bind_double(statement, 20, record->MarketValue);
	sqlite3_bind_double(statement, 21, record->TotalProfit);
	sqlite3_bind_double(statement, 22, record->TodayProfit);
	sqlite3_bind_double(statement, 23, record->Deposit);
	sqlite3_bind_double(statement, 24, record->Withdraw);
}
void SqliteDB::SetStatementForCapitalRecordUpdate(sqlite3_stmt* statement, Capital* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_int(statement, 2, int(record->AccountType));
	sqlite3_bind_double(statement, 3, record->Asset);
	sqlite3_bind_double(statement, 4, record->PreAsset);
	sqlite3_bind_double(statement, 5, record->CashAsset);
	sqlite3_bind_double(statement, 6, record->PreCashAsset);
	sqlite3_bind_double(statement, 7, record->Available);
	sqlite3_bind_double(statement, 8, record->CashIn);
	sqlite3_bind_double(statement, 9, record->CashOut);
	sqlite3_bind_double(statement, 10, record->Margin);
	sqlite3_bind_double(statement, 11, record->Commission);
	sqlite3_bind_double(statement, 12, record->StampTax);
	sqlite3_bind_double(statement, 13, record->TransferFee);
	sqlite3_bind_double(statement, 14, record->FrozenCash);
	sqlite3_bind_double(statement, 15, record->FrozenMargin);
	sqlite3_bind_double(statement, 16, record->FrozenCommission);
	sqlite3_bind_double(statement, 17, record->FrozenStampTax);
	sqlite3_bind_double(statement, 18, record->FrozenTransferFee);
	sqlite3_bind_double(statement, 19, record->MarketValue);
	sqlite3_bind_double(statement, 20, record->TotalProfit);
	sqlite3_bind_double(statement, 21, record->TodayProfit);
	sqlite3_bind_double(statement, 22, record->Deposit);
	sqlite3_bind_double(statement, 23, record->Withdraw);
	sqlite3_bind_text(statement, 24, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::SetStatementForCapitalPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID)
{
	sqlite3_bind_text(statement, 1, AccountID, sizeof(AccountID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Capital*>& records)
{
	Capital* record = Capital::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	record->Asset = sqlite3_column_double(statement, 3);
	record->PreAsset = sqlite3_column_double(statement, 4);
	record->CashAsset = sqlite3_column_double(statement, 5);
	record->PreCashAsset = sqlite3_column_double(statement, 6);
	record->Available = sqlite3_column_double(statement, 7);
	record->CashIn = sqlite3_column_double(statement, 8);
	record->CashOut = sqlite3_column_double(statement, 9);
	record->Margin = sqlite3_column_double(statement, 10);
	record->Commission = sqlite3_column_double(statement, 11);
	record->StampTax = sqlite3_column_double(statement, 12);
	record->TransferFee = sqlite3_column_double(statement, 13);
	record->FrozenCash = sqlite3_column_double(statement, 14);
	record->FrozenMargin = sqlite3_column_double(statement, 15);
	record->FrozenCommission = sqlite3_column_double(statement, 16);
	record->FrozenStampTax = sqlite3_column_double(statement, 17);
	record->FrozenTransferFee = sqlite3_column_double(statement, 18);
	record->MarketValue = sqlite3_column_double(statement, 19);
	record->TotalProfit = sqlite3_column_double(statement, 20);
	record->TodayProfit = sqlite3_column_double(statement, 21);
	record->Deposit = sqlite3_column_double(statement, 22);
	record->Withdraw = sqlite3_column_double(statement, 23);
	records.push_back(record);
}
void SqliteDB::SetStatementForPositionRecord(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->SecurityType));
	sqlite3_bind_int(statement, 7, int(record->PosiDirection));
	sqlite3_bind_int64(statement, 8, record->TotalPosition);
	sqlite3_bind_int64(statement, 9, record->PositionFrozen);
	sqlite3_bind_int64(statement, 10, record->TodayPosition);
	sqlite3_bind_double(statement, 11, record->CashIn);
	sqlite3_bind_double(statement, 12, record->CashOut);
	sqlite3_bind_double(statement, 13, record->Margin);
	sqlite3_bind_double(statement, 14, record->Commission);
	sqlite3_bind_double(statement, 15, record->StampTax);
	sqlite3_bind_double(statement, 16, record->TransferFee);
	sqlite3_bind_double(statement, 17, record->FrozenCash);
	sqlite3_bind_double(statement, 18, record->FrozenMargin);
	sqlite3_bind_double(statement, 19, record->FrozenCommission);
	sqlite3_bind_double(statement, 20, record->FrozenStampTax);
	sqlite3_bind_double(statement, 21, record->FrozenTransferFee);
	sqlite3_bind_double(statement, 22, record->MarketValue);
	sqlite3_bind_int(statement, 23, record->VolumeMultiple);
	sqlite3_bind_double(statement, 24, record->CloseProfit);
	sqlite3_bind_double(statement, 25, record->CloseProfitFloat);
	sqlite3_bind_double(statement, 26, record->PositionProfit);
	sqlite3_bind_double(statement, 27, record->PositionProfitFloat);
	sqlite3_bind_double(statement, 28, record->LastPrice);
	sqlite3_bind_double(statement, 29, record->PrePrice);
}
void SqliteDB::SetStatementForPositionRecordUpdate(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_int(statement, 1, int(record->AccountType));
	sqlite3_bind_int(statement, 2, int(record->SecurityType));
	sqlite3_bind_int64(statement, 3, record->TotalPosition);
	sqlite3_bind_int64(statement, 4, record->PositionFrozen);
	sqlite3_bind_int64(statement, 5, record->TodayPosition);
	sqlite3_bind_double(statement, 6, record->CashIn);
	sqlite3_bind_double(statement, 7, record->CashOut);
	sqlite3_bind_double(statement, 8, record->Margin);
	sqlite3_bind_double(statement, 9, record->Commission);
	sqlite3_bind_double(statement, 10, record->StampTax);
	sqlite3_bind_double(statement, 11, record->TransferFee);
	sqlite3_bind_double(statement, 12, record->FrozenCash);
	sqlite3_bind_double(statement, 13, record->FrozenMargin);
	sqlite3_bind_double(statement, 14, record->FrozenCommission);
	sqlite3_bind_double(statement, 15, record->FrozenStampTax);
	sqlite3_bind_double(statement, 16, record->FrozenTransferFee);
	sqlite3_bind_double(statement, 17, record->MarketValue);
	sqlite3_bind_int(statement, 18, record->VolumeMultiple);
	sqlite3_bind_double(statement, 19, record->CloseProfit);
	sqlite3_bind_double(statement, 20, record->CloseProfitFloat);
	sqlite3_bind_double(statement, 21, record->PositionProfit);
	sqlite3_bind_double(statement, 22, record->PositionProfitFloat);
	sqlite3_bind_double(statement, 23, record->LastPrice);
	sqlite3_bind_double(statement, 24, record->PrePrice);
	sqlite3_bind_text(statement, 25, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 26, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 27, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 28, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 29, int(record->PosiDirection));
}
void SqliteDB::SetStatementForPositionPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
	sqlite3_bind_text(statement, 3, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, int(PosiDirection));
}
void SqliteDB::SetStatementForPositionIndexAccount(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Position*>& records)
{
	Position* record = Position::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->SecurityType = SecurityTypeType(sqlite3_column_int(statement, 5));
	record->PosiDirection = PosiDirectionType(sqlite3_column_int(statement, 6));
	record->TotalPosition = sqlite3_column_int64(statement, 7);
	record->PositionFrozen = sqlite3_column_int64(statement, 8);
	record->TodayPosition = sqlite3_column_int64(statement, 9);
	record->CashIn = sqlite3_column_double(statement, 10);
	record->CashOut = sqlite3_column_double(statement, 11);
	record->Margin = sqlite3_column_double(statement, 12);
	record->Commission = sqlite3_column_double(statement, 13);
	record->StampTax = sqlite3_column_double(statement, 14);
	record->TransferFee = sqlite3_column_double(statement, 15);
	record->FrozenCash = sqlite3_column_double(statement, 16);
	record->FrozenMargin = sqlite3_column_double(statement, 17);
	record->FrozenCommission = sqlite3_column_double(statement, 18);
	record->FrozenStampTax = sqlite3_column_double(statement, 19);
	record->FrozenTransferFee = sqlite3_column_double(statement, 20);
	record->MarketValue = sqlite3_column_double(statement, 21);
	record->VolumeMultiple = sqlite3_column_int(statement, 22);
	record->CloseProfit = sqlite3_column_double(statement, 23);
	record->CloseProfitFloat = sqlite3_column_double(statement, 24);
	record->PositionProfit = sqlite3_column_double(statement, 25);
	record->PositionProfitFloat = sqlite3_column_double(statement, 26);
	record->LastPrice = sqlite3_column_double(statement, 27);
	record->PrePrice = sqlite3_column_double(statement, 28);
	records.push_back(record);
}
void SqliteDB::SetStatementForOrderRecord(sqlite3_stmt* statement, Order* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->AccountType));
	sqlite3_bind_text(statement, 5, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 6, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 7, int(record->SecurityType));
	sqlite3_bind_int(statement, 8, record->OrderID);
	sqlite3_bind_text(statement, 9, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 10, int(record->Direction));
	sqlite3_bind_int(statement, 11, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 12, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 13, record->Price);
	sqlite3_bind_int64(statement, 14, record->Volume);
	sqlite3_bind_int64(statement, 15, record->VolumeTotal);
	sqlite3_bind_int64(statement, 16, record->VolumeTraded);
	sqlite3_bind_int(statement, 17, record->VolumeMultiple);
	sqlite3_bind_int(statement, 18, int(record->OrderStatus));
	sqlite3_bind_text(statement, 19, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 20, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 21, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 22, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 23, record->SessionID);
	sqlite3_bind_int(statement, 24, record->ClientOrderID);
	sqlite3_bind_int(statement, 25, record->RequestID);
	sqlite3_bind_int(statement, 26, record->OfferID);
	sqlite3_bind_int(statement, 27, record->TradeGroupID);
	sqlite3_bind_int(statement, 28, record->RiskGroupID);
	sqlite3_bind_int(statement, 29, record->CommissionGroupID);
	sqlite3_bind_double(statement, 30, record->FrozenCash);
	sqlite3_bind_double(statement, 31, record->FrozenMargin);
	sqlite3_bind_double(statement, 32, record->FrozenCommission);
	sqlite3_bind_double(statement, 33, record->FrozenStampTax);
	sqlite3_bind_double(statement, 34, record->FrozenTransferFee);
	sqlite3_bind_int(statement, 35, record->RebuildMark);
	sqlite3_bind_int(statement, 36, record->IsForceClose);
}
void SqliteDB::SetStatementForOrderRecordUpdate(sqlite3_stmt* statement, Order* record)
{
	sqlite3_bind_text(statement, 1, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_int(statement, 2, int(record->AccountType));
	sqlite3_bind_int(statement, 3, int(record->SecurityType));
	sqlite3_bind_text(statement, 4, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->Direction));
	sqlite3_bind_int(statement, 6, int(record->OffsetFlag));
	sqlite3_bind_int(statement, 7, int(record->OrderPriceType));
	sqlite3_bind_double(statement, 8, record->Price);
	sqlite3_bind_int64(statement, 9, record->Volume);
	sqlite3_bind_int64(statement, 10, record->VolumeTotal);
	sqlite3_bind_int64(statement, 11, record->VolumeTraded);
	sqlite3_bind_int(statement, 12, record->VolumeMultiple);
	sqlite3_bind_int(statement, 13, int(record->OrderStatus));
	sqlite3_bind_text(statement, 14, record->OrderDate, sizeof(record->OrderDate), nullptr);
	sqlite3_bind_text(statement, 15, record->OrderTime, sizeof(record->OrderTime), nullptr);
	sqlite3_bind_text(statement, 16, record->CancelDate, sizeof(record->CancelDate), nullptr);
	sqlite3_bind_text(statement, 17, record->CancelTime, sizeof(record->CancelTime), nullptr);
	sqlite3_bind_int64(statement, 18, record->SessionID);
	sqlite3_bind_int(statement, 19, record->ClientOrderID);
	sqlite3_bind_int(statement, 20, record->RequestID);
	sqlite3_bind_int(statement, 21, record->OfferID);
	sqlite3_bind_int(statement, 22, record->TradeGroupID);
	sqlite3_bind_int(statement, 23, record->RiskGroupID);
	sqlite3_bind_int(statement, 24, record->CommissionGroupID);
	sqlite3_bind_double(statement, 25, record->FrozenCash);
	sqlite3_bind_double(statement, 26, record->FrozenMargin);
	sqlite3_bind_double(statement, 27, record->FrozenCommission);
	sqlite3_bind_double(statement, 28, record->FrozenStampTax);
	sqlite3_bind_double(statement, 29, record->FrozenTransferFee);
	sqlite3_bind_int(statement, 30, record->RebuildMark);
	sqlite3_bind_int(statement, 31, record->IsForceClose);
	sqlite3_bind_text(statement, 32, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 33, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 34, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 35, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 36, record->OrderID);
}
void SqliteDB::SetStatementForOrderPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
	sqlite3_bind_text(statement, 3, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, OrderID);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Order*>& records)
{
	Order* record = Order::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->PrimaryAccountID, (const char*)sqlite3_column_text(statement, 2));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 3));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 4));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 5));
	record->SecurityType = SecurityTypeType(sqlite3_column_int(statement, 6));
	record->OrderID = sqlite3_column_int(statement, 7);
	Strcpy(record->OrderSysID, (const char*)sqlite3_column_text(statement, 8));
	record->Direction = DirectionType(sqlite3_column_int(statement, 9));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 10));
	record->OrderPriceType = OrderPriceTypeType(sqlite3_column_int(statement, 11));
	record->Price = sqlite3_column_double(statement, 12);
	record->Volume = sqlite3_column_int64(statement, 13);
	record->VolumeTotal = sqlite3_column_int64(statement, 14);
	record->VolumeTraded = sqlite3_column_int64(statement, 15);
	record->VolumeMultiple = sqlite3_column_int(statement, 16);
	record->OrderStatus = OrderStatusType(sqlite3_column_int(statement, 17));
	Strcpy(record->OrderDate, (const char*)sqlite3_column_text(statement, 18));
	Strcpy(record->OrderTime, (const char*)sqlite3_column_text(statement, 19));
	Strcpy(record->CancelDate, (const char*)sqlite3_column_text(statement, 20));
	Strcpy(record->CancelTime, (const char*)sqlite3_column_text(statement, 21));
	record->SessionID = sqlite3_column_int64(statement, 22);
	record->ClientOrderID = sqlite3_column_int(statement, 23);
	record->RequestID = sqlite3_column_int(statement, 24);
	record->OfferID = sqlite3_column_int(statement, 25);
	record->TradeGroupID = sqlite3_column_int(statement, 26);
	record->RiskGroupID = sqlite3_column_int(statement, 27);
	record->CommissionGroupID = sqlite3_column_int(statement, 28);
	record->FrozenCash = sqlite3_column_double(statement, 29);
	record->FrozenMargin = sqlite3_column_double(statement, 30);
	record->FrozenCommission = sqlite3_column_double(statement, 31);
	record->FrozenStampTax = sqlite3_column_double(statement, 32);
	record->FrozenTransferFee = sqlite3_column_double(statement, 33);
	record->RebuildMark = sqlite3_column_int(statement, 34);
	record->IsForceClose = sqlite3_column_int(statement, 35);
	records.push_back(record);
}
void SqliteDB::SetStatementForTradeRecord(sqlite3_stmt* statement, Trade* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_int(statement, 4, int(record->AccountType));
	sqlite3_bind_text(statement, 5, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 6, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 7, int(record->SecurityType));
	sqlite3_bind_int(statement, 8, record->OrderID);
	sqlite3_bind_text(statement, 9, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_text(statement, 10, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 11, int(record->Direction));
	sqlite3_bind_int(statement, 12, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 13, record->Price);
	sqlite3_bind_int64(statement, 14, record->Volume);
	sqlite3_bind_int(statement, 15, record->VolumeMultiple);
	sqlite3_bind_double(statement, 16, record->TradeAmount);
	sqlite3_bind_double(statement, 17, record->Commission);
	sqlite3_bind_double(statement, 18, record->StampTax);
	sqlite3_bind_double(statement, 19, record->TransferFee);
	sqlite3_bind_text(statement, 20, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 21, record->TradeTime, sizeof(record->TradeTime), nullptr);
}
void SqliteDB::SetStatementForTradeRecordUpdate(sqlite3_stmt* statement, Trade* record)
{
	sqlite3_bind_text(statement, 1, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 2, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->SecurityType));
	sqlite3_bind_int(statement, 6, record->OrderID);
	sqlite3_bind_text(statement, 7, record->OrderSysID, sizeof(record->OrderSysID), nullptr);
	sqlite3_bind_int(statement, 8, int(record->OffsetFlag));
	sqlite3_bind_double(statement, 9, record->Price);
	sqlite3_bind_int64(statement, 10, record->Volume);
	sqlite3_bind_int(statement, 11, record->VolumeMultiple);
	sqlite3_bind_double(statement, 12, record->TradeAmount);
	sqlite3_bind_double(statement, 13, record->Commission);
	sqlite3_bind_double(statement, 14, record->StampTax);
	sqlite3_bind_double(statement, 15, record->TransferFee);
	sqlite3_bind_text(statement, 16, record->TradeDate, sizeof(record->TradeDate), nullptr);
	sqlite3_bind_text(statement, 17, record->TradeTime, sizeof(record->TradeTime), nullptr);
	sqlite3_bind_text(statement, 18, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 19, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 20, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int(statement, 21, int(record->Direction));
}
void SqliteDB::SetStatementForTradePrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, TradeID, sizeof(TradeID), nullptr);
	sqlite3_bind_int(statement, 4, int(Direction));
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<Trade*>& records)
{
	Trade* record = Trade::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->PrimaryAccountID, (const char*)sqlite3_column_text(statement, 2));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 3));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 4));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 5));
	record->SecurityType = SecurityTypeType(sqlite3_column_int(statement, 6));
	record->OrderID = sqlite3_column_int(statement, 7);
	Strcpy(record->OrderSysID, (const char*)sqlite3_column_text(statement, 8));
	Strcpy(record->TradeID, (const char*)sqlite3_column_text(statement, 9));
	record->Direction = DirectionType(sqlite3_column_int(statement, 10));
	record->OffsetFlag = OffsetFlagType(sqlite3_column_int(statement, 11));
	record->Price = sqlite3_column_double(statement, 12);
	record->Volume = sqlite3_column_int64(statement, 13);
	record->VolumeMultiple = sqlite3_column_int(statement, 14);
	record->TradeAmount = sqlite3_column_double(statement, 15);
	record->Commission = sqlite3_column_double(statement, 16);
	record->StampTax = sqlite3_column_double(statement, 17);
	record->TransferFee = sqlite3_column_double(statement, 18);
	Strcpy(record->TradeDate, (const char*)sqlite3_column_text(statement, 19));
	Strcpy(record->TradeTime, (const char*)sqlite3_column_text(statement, 20));
	records.push_back(record);
}
void SqliteDB::SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, DepthMarketData* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 3, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_double(statement, 4, record->LastPrice);
	sqlite3_bind_double(statement, 5, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 6, record->PreClosePrice);
	sqlite3_bind_int64(statement, 7, record->PreOpenInterest);
	sqlite3_bind_double(statement, 8, record->OpenPrice);
	sqlite3_bind_double(statement, 9, record->HighestPrice);
	sqlite3_bind_double(statement, 10, record->LowestPrice);
	sqlite3_bind_double(statement, 11, record->ClosePrice);
	sqlite3_bind_int64(statement, 12, record->CurrVolume);
	sqlite3_bind_int64(statement, 13, record->Volume);
	sqlite3_bind_double(statement, 14, record->CurrTurnover);
	sqlite3_bind_double(statement, 15, record->Turnover);
	sqlite3_bind_int64(statement, 16, record->OpenInterest);
	sqlite3_bind_double(statement, 17, record->SettlementPrice);
	sqlite3_bind_double(statement, 18, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 19, record->LowerLimitPrice);
	sqlite3_bind_double(statement, 20, record->AveragePrice);
	sqlite3_bind_int64(statement, 21, record->UpdateTs);
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
	sqlite3_bind_double(statement, 1, record->LastPrice);
	sqlite3_bind_double(statement, 2, record->PreSettlementPrice);
	sqlite3_bind_double(statement, 3, record->PreClosePrice);
	sqlite3_bind_int64(statement, 4, record->PreOpenInterest);
	sqlite3_bind_double(statement, 5, record->OpenPrice);
	sqlite3_bind_double(statement, 6, record->HighestPrice);
	sqlite3_bind_double(statement, 7, record->LowestPrice);
	sqlite3_bind_double(statement, 8, record->ClosePrice);
	sqlite3_bind_int64(statement, 9, record->CurrVolume);
	sqlite3_bind_int64(statement, 10, record->Volume);
	sqlite3_bind_double(statement, 11, record->CurrTurnover);
	sqlite3_bind_double(statement, 12, record->Turnover);
	sqlite3_bind_int64(statement, 13, record->OpenInterest);
	sqlite3_bind_double(statement, 14, record->SettlementPrice);
	sqlite3_bind_double(statement, 15, record->UpperLimitPrice);
	sqlite3_bind_double(statement, 16, record->LowerLimitPrice);
	sqlite3_bind_double(statement, 17, record->AveragePrice);
	sqlite3_bind_int64(statement, 18, record->UpdateTs);
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
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::vector<DepthMarketData*>& records)
{
	DepthMarketData* record = DepthMarketData::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 2));
	record->LastPrice = sqlite3_column_double(statement, 3);
	record->PreSettlementPrice = sqlite3_column_double(statement, 4);
	record->PreClosePrice = sqlite3_column_double(statement, 5);
	record->PreOpenInterest = sqlite3_column_int64(statement, 6);
	record->OpenPrice = sqlite3_column_double(statement, 7);
	record->HighestPrice = sqlite3_column_double(statement, 8);
	record->LowestPrice = sqlite3_column_double(statement, 9);
	record->ClosePrice = sqlite3_column_double(statement, 10);
	record->CurrVolume = sqlite3_column_int64(statement, 11);
	record->Volume = sqlite3_column_int64(statement, 12);
	record->CurrTurnover = sqlite3_column_double(statement, 13);
	record->Turnover = sqlite3_column_double(statement, 14);
	record->OpenInterest = sqlite3_column_int64(statement, 15);
	record->SettlementPrice = sqlite3_column_double(statement, 16);
	record->UpperLimitPrice = sqlite3_column_double(statement, 17);
	record->LowerLimitPrice = sqlite3_column_double(statement, 18);
	record->AveragePrice = sqlite3_column_double(statement, 19);
	record->UpdateTs = sqlite3_column_int64(statement, 20);
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

