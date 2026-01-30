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

	m_ExchangeInsertStatement = nullptr;
	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
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

	m_MdSubscribeInsertStatement = nullptr;
	m_MdSubscribeDeleteStatement = nullptr;
	m_MdSubscribeUpdateStatement = nullptr;
	m_MdSubscribeSelectStatement = nullptr;
	m_MdSubscribeTruncateStatement = nullptr;

	m_MdUserInsertStatement = nullptr;
	m_MdUserDeleteStatement = nullptr;
	m_MdUserUpdateStatement = nullptr;
	m_MdUserSelectStatement = nullptr;
	m_MdUserTruncateStatement = nullptr;

	m_MdUserLoginSessionInsertStatement = nullptr;
	m_MdUserLoginSessionDeleteStatement = nullptr;
	m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	m_MdUserLoginSessionUpdateStatement = nullptr;
	m_MdUserLoginSessionSelectStatement = nullptr;
	m_MdUserLoginSessionTruncateStatement = nullptr;

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
	if (m_InstrumentDeleteByExchangeIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_InstrumentDeleteByExchangeIDIndexStatement);
		m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
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
	if (m_MdSubscribeInsertStatement != nullptr)
	{
		sqlite3_finalize(m_MdSubscribeInsertStatement);
		m_MdSubscribeInsertStatement = nullptr;
	}
	if (m_MdSubscribeDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_MdSubscribeDeleteStatement);
		m_MdSubscribeDeleteStatement = nullptr;
	}
	if (m_MdSubscribeUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_MdSubscribeUpdateStatement);
		m_MdSubscribeUpdateStatement = nullptr;
	}
	if (m_MdSubscribeSelectStatement != nullptr)
	{
		sqlite3_finalize(m_MdSubscribeSelectStatement);
		m_MdSubscribeSelectStatement = nullptr;
	}
	if (m_MdSubscribeTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_MdSubscribeTruncateStatement);
		m_MdSubscribeTruncateStatement = nullptr;
	}
	if (m_MdUserInsertStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserInsertStatement);
		m_MdUserInsertStatement = nullptr;
	}
	if (m_MdUserDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserDeleteStatement);
		m_MdUserDeleteStatement = nullptr;
	}
	if (m_MdUserUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserUpdateStatement);
		m_MdUserUpdateStatement = nullptr;
	}
	if (m_MdUserSelectStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserSelectStatement);
		m_MdUserSelectStatement = nullptr;
	}
	if (m_MdUserTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserTruncateStatement);
		m_MdUserTruncateStatement = nullptr;
	}
	if (m_MdUserLoginSessionInsertStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionInsertStatement);
		m_MdUserLoginSessionInsertStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionDeleteStatement);
		m_MdUserLoginSessionDeleteStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement);
		m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	}
	if (m_MdUserLoginSessionUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionUpdateStatement);
		m_MdUserLoginSessionUpdateStatement = nullptr;
	}
	if (m_MdUserLoginSessionSelectStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionSelectStatement);
		m_MdUserLoginSessionSelectStatement = nullptr;
	}
	if (m_MdUserLoginSessionTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_MdUserLoginSessionTruncateStatement);
		m_MdUserLoginSessionTruncateStatement = nullptr;
	}
}
void SqliteDB::InitDB()
{
	Exec("Truncate Table t_Exchange;");
	Exec("Insert Into t_Exchange select * from Init.t_Exchange;");
	Exec("Truncate Table t_Instrument;");
	Exec("Insert Into t_Instrument select * from Init.t_Instrument;");
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Truncate Table t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	Exec("Truncate Table t_MdSubscribe;");
	Exec("Insert Into t_MdSubscribe select * from Init.t_MdSubscribe;");
	Exec("Truncate Table t_MdUser;");
	Exec("Insert Into t_MdUser select * from Init.t_MdUser;");
	Exec("Truncate Table t_MdUserLoginSession;");
	Exec("Insert Into t_MdUserLoginSession select * from Init.t_MdUserLoginSession;");
}
void SqliteDB::CreateTables()
{
	CreateExchange();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreateMdSubscribe();
	CreateMdUser();
	CreateMdUserLoginSession();
}
void SqliteDB::DropTables()
{
	DropExchange();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropMdSubscribe();
	DropMdUser();
	DropMdUserLoginSession();
}
void SqliteDB::TruncateTables()
{
	TruncateExchange();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncateMdSubscribe();
	TruncateMdUser();
	TruncateMdUserLoginSession();
}
void SqliteDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateMdUserLoginSession();
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

void SqliteDB::CreateExchange()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Exchange(`ExchangeID` text, `ExchangeName` text, PRIMARY KEY(ExchangeID));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateExchange failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateExchange Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropExchange()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_Exchange;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropExchange failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropExchange Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::CreateInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Instrument(`ExchangeID` text, `InstrumentID` text, `ExchangeInstID` text, `InstrumentName` text, `ProductID` text, `ProductClass` int, `InstrumentClass` int, `Rank` int, `VolumeMultiple` int, `PriceTick` double, `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` text, PRIMARY KEY(ExchangeID, InstrumentID));CREATE INDEX IF NOT EXISTS InstrumentExchangeID ON t_Instrument(ExchangeID);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateInstrument Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX InstrumentExchangeID;DROP TABLE IF EXISTS t_Instrument;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropInstrument Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::DeleteInstrumentByExchangeIDIndex(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteByExchangeIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Instrument where ExchangeID = ?;", -1, &m_InstrumentDeleteByExchangeIDIndexStatement, nullptr);
	}
	SetStatementForInstrumentIndexExchangeID(m_InstrumentDeleteByExchangeIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_InstrumentDeleteByExchangeIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrumentByExchangeIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_InstrumentDeleteByExchangeIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrumentByExchangeIDIndex Spend:%lldms", duration);
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_DepthMarketData(`TradingDay` text, `ExchangeID` text, `InstrumentID` text, `UpdateTs` bigint, `LastPrice` double, `PreSettlementPrice` double, `PreClosePrice` double, `PreOpenInterest` double, `OpenPrice` double, `HighestPrice` double, `LowestPrice` double, `ClosePrice` double, `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` double, `Turnover` double, `OpenInterest` double, `SettlementPrice` double, `UpperLimitPrice` double, `LowerLimitPrice` double, `AveragePrice` double, `AskPrice1` double, `AskPrice2` double, `AskPrice3` double, `AskPrice4` double, `AskPrice5` double, `AskPrice6` double, `AskPrice7` double, `AskPrice8` double, `AskPrice9` double, `AskPrice10` double, `AskVolume1` bigint, `AskVolume2` bigint, `AskVolume3` bigint, `AskVolume4` bigint, `AskVolume5` bigint, `AskVolume6` bigint, `AskVolume7` bigint, `AskVolume8` bigint, `AskVolume9` bigint, `AskVolume10` bigint, `BidPrice1` double, `BidPrice2` double, `BidPrice3` double, `BidPrice4` double, `BidPrice5` double, `BidPrice6` double, `BidPrice7` double, `BidPrice8` double, `BidPrice9` double, `BidPrice10` double, `BidVolume1` bigint, `BidVolume2` bigint, `BidVolume3` bigint, `BidVolume4` bigint, `BidVolume5` bigint, `BidVolume6` bigint, `BidVolume7` bigint, `BidVolume8` bigint, `BidVolume9` bigint, `BidVolume10` bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateDepthMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateDepthMarketData Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropDepthMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_DepthMarketData;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropDepthMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropDepthMarketData Spend:%lldms, sql:%s", duration, sql);
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_BarMarketData(`TradingDay` text, `ExchangeID` text, `InstrumentID` text, `BarPreces` int, `BarPeriod` int, `BarTime` bigint, `UpdateTs` bigint, `PreSettlementPrice` double, `PreClosePrice` double, `Open` double, `High` double, `Low` double, `Close` double, `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` double, `Turnover` double, `OpenInterest` double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateBarMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateBarMarketData Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropBarMarketData()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_BarMarketData;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropBarMarketData failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropBarMarketData Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::CreateMdSubscribe()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdSubscribe(`ExchangeID` text, `InstrumentID` text, `RealInstrumentID` text, `ProductID` text, `ProductClass` int, `StartTradingDay` text, `EndTradingDay` text, PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateMdSubscribe failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdSubscribe Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropMdSubscribe()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_MdSubscribe;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropMdSubscribe failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdSubscribe Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_MdSubscribe Values(?, ?, ?, ?, ?, ?, ?);", -1, &m_MdSubscribeInsertStatement, nullptr);
	}
	SetStatementForMdSubscribeRecord(m_MdSubscribeInsertStatement, record);
	
	auto rc = sqlite3_step(m_MdSubscribeInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdSubscribeInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdSubscribe Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertMdSubscribe(std::list<MdSubscribe*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdSubscribe Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdSubscribe Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdSubscribe where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;", -1, &m_MdSubscribeDeleteStatement, nullptr);
	}
	SetStatementForMdSubscribePrimaryKey(m_MdSubscribeDeleteStatement, record->ExchangeID, record->InstrumentID, record->StartTradingDay);

	auto rc = sqlite3_step(m_MdSubscribeDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdSubscribeDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdSubscribe Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_MdSubscribe set RealInstrumentID = ?, ProductID = ?, ProductClass = ?, EndTradingDay = ? where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;", -1, &m_MdSubscribeUpdateStatement, nullptr);
	}
	SetStatementForMdSubscribeRecordUpdate(m_MdSubscribeUpdateStatement, record);
	
	auto rc = sqlite3_step(m_MdSubscribeUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateMdSubscribe failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdSubscribeUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdSubscribe Spend:%lldms", duration);
	}
}
void SqliteDB::SelectMdSubscribe(std::list<MdSubscribe*>& records)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_MdSubscribe;", -1, &m_MdSubscribeSelectStatement, nullptr);
	}

	while (sqlite3_step(m_MdSubscribeSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_MdSubscribeSelectStatement, records);
	}
	sqlite3_reset(m_MdSubscribeSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdSubscribe Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateMdSubscribe()
{
	auto start = steady_clock::now();
	if (m_MdSubscribeTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdSubscribe;", -1, &m_MdSubscribeTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_MdSubscribeTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateMdSubscribe failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdSubscribeTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateMdSubscribe Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateMdUser()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdUser(`MdUserID` text, `MdUserName` text, `Password` text, PRIMARY KEY(MdUserID));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateMdUser failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUser Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropMdUser()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_MdUser;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropMdUser failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUser Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_MdUser Values(?, ?, ?);", -1, &m_MdUserInsertStatement, nullptr);
	}
	SetStatementForMdUserRecord(m_MdUserInsertStatement, record);
	
	auto rc = sqlite3_step(m_MdUserInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdUser Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertMdUser(std::list<MdUser*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdUser Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertMdUser Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdUser Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdUser Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdUser RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdUser where MdUserID = ?;", -1, &m_MdUserDeleteStatement, nullptr);
	}
	SetStatementForMdUserPrimaryKey(m_MdUserDeleteStatement, record->MdUserID);

	auto rc = sqlite3_step(m_MdUserDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUser Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_MdUser set MdUserName = ?, Password = ? where MdUserID = ?;", -1, &m_MdUserUpdateStatement, nullptr);
	}
	SetStatementForMdUserRecordUpdate(m_MdUserUpdateStatement, record);
	
	auto rc = sqlite3_step(m_MdUserUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUser failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUser Spend:%lldms", duration);
	}
}
void SqliteDB::SelectMdUser(std::list<MdUser*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_MdUser;", -1, &m_MdUserSelectStatement, nullptr);
	}

	while (sqlite3_step(m_MdUserSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_MdUserSelectStatement, records);
	}
	sqlite3_reset(m_MdUserSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUser Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateMdUser()
{
	auto start = steady_clock::now();
	if (m_MdUserTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdUser;", -1, &m_MdUserTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_MdUserTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateMdUser failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateMdUser Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateMdUserLoginSession()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(`MdUserID` text, `SessionID` bigint, `IPAddress` text, PRIMARY KEY(SessionID));CREATE INDEX IF NOT EXISTS MdUserLoginSessionMdUserID ON t_MdUserLoginSession(MdUserID);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateMdUserLoginSession failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUserLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropMdUserLoginSession()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX MdUserLoginSessionMdUserID;DROP TABLE IF EXISTS t_MdUserLoginSession;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropMdUserLoginSession failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUserLoginSession Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_MdUserLoginSession Values(?, ?, ?);", -1, &m_MdUserLoginSessionInsertStatement, nullptr);
	}
	SetStatementForMdUserLoginSessionRecord(m_MdUserLoginSessionInsertStatement, record);
	
	auto rc = sqlite3_step(m_MdUserLoginSessionInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserLoginSessionInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdUserLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertMdUserLoginSession(std::list<MdUserLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdUserLoginSession Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdUserLoginSession Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeleteMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdUserLoginSession where SessionID = ?;", -1, &m_MdUserLoginSessionDeleteStatement, nullptr);
	}
	SetStatementForMdUserLoginSessionPrimaryKey(m_MdUserLoginSessionDeleteStatement, record->SessionID);

	auto rc = sqlite3_step(m_MdUserLoginSessionDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserLoginSessionDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::DeleteMdUserLoginSessionByMdUserIDIndex(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdUserLoginSession where MdUserID = ?;", -1, &m_MdUserLoginSessionDeleteByMdUserIDIndexStatement, nullptr);
	}
	SetStatementForMdUserLoginSessionIndexMdUserID(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSessionByMdUserIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSessionByMdUserIDIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_MdUserLoginSession set MdUserID = ?, IPAddress = ? where SessionID = ?;", -1, &m_MdUserLoginSessionUpdateStatement, nullptr);
	}
	SetStatementForMdUserLoginSessionRecordUpdate(m_MdUserLoginSessionUpdateStatement, record);
	
	auto rc = sqlite3_step(m_MdUserLoginSessionUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUserLoginSession failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserLoginSessionUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUserLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::SelectMdUserLoginSession(std::list<MdUserLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_MdUserLoginSession;", -1, &m_MdUserLoginSessionSelectStatement, nullptr);
	}

	while (sqlite3_step(m_MdUserLoginSessionSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_MdUserLoginSessionSelectStatement, records);
	}
	sqlite3_reset(m_MdUserLoginSessionSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUserLoginSession Spend:%lldms", duration);
	}
}
void SqliteDB::TruncateMdUserLoginSession()
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_MdUserLoginSession;", -1, &m_MdUserLoginSessionTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_MdUserLoginSessionTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncateMdUserLoginSession failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_MdUserLoginSessionTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncateMdUserLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void SqliteDB::SetStatementForInstrumentIndexExchangeID(sqlite3_stmt* statement, Instrument* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
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
void SqliteDB::SetStatementForMdSubscribeRecord(sqlite3_stmt* statement, MdSubscribe* record)
{
	sqlite3_bind_text(statement, 1, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_text(statement, 3, record->RealInstrumentID, sizeof(record->RealInstrumentID), nullptr);
	sqlite3_bind_text(statement, 4, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->ProductClass));
	sqlite3_bind_text(statement, 6, record->StartTradingDay, sizeof(record->StartTradingDay), nullptr);
	sqlite3_bind_text(statement, 7, record->EndTradingDay, sizeof(record->EndTradingDay), nullptr);
}
void SqliteDB::SetStatementForMdSubscribeRecordUpdate(sqlite3_stmt* statement, MdSubscribe* record)
{
	sqlite3_bind_text(statement, 1, record->RealInstrumentID, sizeof(record->RealInstrumentID), nullptr);
	sqlite3_bind_text(statement, 2, record->ProductID, sizeof(record->ProductID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->ProductClass));
	sqlite3_bind_text(statement, 4, record->EndTradingDay, sizeof(record->EndTradingDay), nullptr);
	sqlite3_bind_text(statement, 5, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 6, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_text(statement, 7, record->StartTradingDay, sizeof(record->StartTradingDay), nullptr);
}
void SqliteDB::SetStatementForMdSubscribePrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay)
{
	sqlite3_bind_text(statement, 1, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 2, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_text(statement, 3, StartTradingDay, sizeof(StartTradingDay), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<MdSubscribe*>& records)
{
	MdSubscribe* record = MdSubscribe::Allocate();
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->RealInstrumentID, (const char*)sqlite3_column_text(statement, 2));
	Strcpy(record->ProductID, (const char*)sqlite3_column_text(statement, 3));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 4));
	Strcpy(record->StartTradingDay, (const char*)sqlite3_column_text(statement, 5));
	Strcpy(record->EndTradingDay, (const char*)sqlite3_column_text(statement, 6));
	records.push_back(record);
}
void SqliteDB::SetStatementForMdUserRecord(sqlite3_stmt* statement, MdUser* record)
{
	sqlite3_bind_text(statement, 1, record->MdUserID, sizeof(record->MdUserID), nullptr);
	sqlite3_bind_text(statement, 2, record->MdUserName, sizeof(record->MdUserName), nullptr);
	sqlite3_bind_text(statement, 3, record->Password, sizeof(record->Password), nullptr);
}
void SqliteDB::SetStatementForMdUserRecordUpdate(sqlite3_stmt* statement, MdUser* record)
{
	sqlite3_bind_text(statement, 1, record->MdUserName, sizeof(record->MdUserName), nullptr);
	sqlite3_bind_text(statement, 2, record->Password, sizeof(record->Password), nullptr);
	sqlite3_bind_text(statement, 3, record->MdUserID, sizeof(record->MdUserID), nullptr);
}
void SqliteDB::SetStatementForMdUserPrimaryKey(sqlite3_stmt* statement, const UserIDType& MdUserID)
{
	sqlite3_bind_text(statement, 1, MdUserID, sizeof(MdUserID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<MdUser*>& records)
{
	MdUser* record = MdUser::Allocate();
	Strcpy(record->MdUserID, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->MdUserName, (const char*)sqlite3_column_text(statement, 1));
	Strcpy(record->Password, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}
void SqliteDB::SetStatementForMdUserLoginSessionRecord(sqlite3_stmt* statement, MdUserLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->MdUserID, sizeof(record->MdUserID), nullptr);
	sqlite3_bind_int64(statement, 2, record->SessionID);
	sqlite3_bind_text(statement, 3, record->IPAddress, sizeof(record->IPAddress), nullptr);
}
void SqliteDB::SetStatementForMdUserLoginSessionRecordUpdate(sqlite3_stmt* statement, MdUserLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->MdUserID, sizeof(record->MdUserID), nullptr);
	sqlite3_bind_text(statement, 2, record->IPAddress, sizeof(record->IPAddress), nullptr);
	sqlite3_bind_int64(statement, 3, record->SessionID);
}
void SqliteDB::SetStatementForMdUserLoginSessionPrimaryKey(sqlite3_stmt* statement, const SessionIDType& SessionID)
{
	sqlite3_bind_int64(statement, 1, SessionID);
}
void SqliteDB::SetStatementForMdUserLoginSessionIndexMdUserID(sqlite3_stmt* statement, MdUserLoginSession* record)
{
	sqlite3_bind_text(statement, 1, record->MdUserID, sizeof(record->MdUserID), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<MdUserLoginSession*>& records)
{
	MdUserLoginSession* record = MdUserLoginSession::Allocate();
	Strcpy(record->MdUserID, (const char*)sqlite3_column_text(statement, 0));
	record->SessionID = sqlite3_column_int64(statement, 1);
	Strcpy(record->IPAddress, (const char*)sqlite3_column_text(statement, 2));
	records.push_back(record);
}

