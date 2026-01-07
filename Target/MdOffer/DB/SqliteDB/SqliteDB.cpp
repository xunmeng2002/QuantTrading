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
}
void SqliteDB::InitDB()
{
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Truncate Table t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
}
void SqliteDB::CreateTables()
{
	CreateDepthMarketData();
	CreateBarMarketData();
}
void SqliteDB::DropTables()
{
	DropDepthMarketData();
	DropBarMarketData();
}
void SqliteDB::TruncateTables()
{
	TruncateDepthMarketData();
	TruncateBarMarketData();
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
void SqliteDB::SelectBarMarketData(std::list<BarMarketData*>& records)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_BarMarketData;", -1, &m_BarMarketDataSelectStatement, nullptr);
	}

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

