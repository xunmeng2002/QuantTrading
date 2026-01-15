#pragma warning(disable: 4311)
#include "MysqlDB.h"
#include "Constant.h"
#include "Logger.h"
#include "Utility.h"
#include "TimeUtility.h"
#include <string.h>
#include <cstring>

using namespace mdb;
using namespace std;
using namespace std::chrono;

MysqlDB::MysqlDB(const std::string& host, const std::string& user, const std::string& passwd)
{
	m_Host = host;
	m_User = user;
	m_Passwd = passwd;
	m_SqlBuff = new char[BuffSize];

	m_Driver = sql::mysql::get_driver_instance();
	m_DBConnection = nullptr;
	m_Statement = nullptr;
	
	m_ExchangeCreateStatement = nullptr;
	m_ExchangeDropStatement = nullptr;
	m_ExchangeInsertStatement = nullptr;
	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_InstrumentCreateStatement = nullptr;
	m_InstrumentDropStatement = nullptr;
	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
	m_InstrumentUpdateStatement = nullptr;
	m_InstrumentSelectStatement = nullptr;
	m_InstrumentTruncateStatement = nullptr;

	m_DepthMarketDataCreateStatement = nullptr;
	m_DepthMarketDataDropStatement = nullptr;
	m_DepthMarketDataInsertStatement = nullptr;
	m_DepthMarketDataDeleteStatement = nullptr;
	m_DepthMarketDataUpdateStatement = nullptr;
	m_DepthMarketDataSelectStatement = nullptr;
	m_DepthMarketDataTruncateStatement = nullptr;

	m_BarMarketDataCreateStatement = nullptr;
	m_BarMarketDataDropStatement = nullptr;
	m_BarMarketDataInsertStatement = nullptr;
	m_BarMarketDataDeleteStatement = nullptr;
	m_BarMarketDataUpdateStatement = nullptr;
	m_BarMarketDataSelectStatement = nullptr;
	m_BarMarketDataTruncateStatement = nullptr;

	m_MdSubscribeCreateStatement = nullptr;
	m_MdSubscribeDropStatement = nullptr;
	m_MdSubscribeInsertStatement = nullptr;
	m_MdSubscribeDeleteStatement = nullptr;
	m_MdSubscribeUpdateStatement = nullptr;
	m_MdSubscribeSelectStatement = nullptr;
	m_MdSubscribeTruncateStatement = nullptr;

	m_MdUserCreateStatement = nullptr;
	m_MdUserDropStatement = nullptr;
	m_MdUserInsertStatement = nullptr;
	m_MdUserDeleteStatement = nullptr;
	m_MdUserUpdateStatement = nullptr;
	m_MdUserSelectStatement = nullptr;
	m_MdUserTruncateStatement = nullptr;

	m_MdUserLoginSessionCreateStatement = nullptr;
	m_MdUserLoginSessionDropStatement = nullptr;
	m_MdUserLoginSessionInsertStatement = nullptr;
	m_MdUserLoginSessionDeleteStatement = nullptr;
	m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	m_MdUserLoginSessionUpdateStatement = nullptr;
	m_MdUserLoginSessionSelectStatement = nullptr;
	m_MdUserLoginSessionTruncateStatement = nullptr;

}
MysqlDB::~MysqlDB()
{
	delete[] m_SqlBuff;
	DisConnect();
	if (m_DBConnection != nullptr)
	{
		m_DBConnection->close();
	}
}
bool MysqlDB::Connect()
{
	try
	{
		if (m_Driver == nullptr)
		{
			m_Driver = sql::mysql::get_driver_instance();
		}
		if (m_DBConnection == nullptr)
		{
			m_DBConnection = m_Driver->connect(m_Host, m_User, m_Passwd);
			if (m_DBConnection == nullptr)
			{
				WriteLog(LogLevel::Info, "MysqlDB Connect Failed");
				return false;
			}
		}
		else
		{
			auto result = m_DBConnection->reconnect();
			WriteLog(LogLevel::Info, "MysqlDB Reconnect Result:[%d]", result);
			if (!result)
			{
				m_Driver = nullptr;
				m_DBConnection = nullptr;
				return false;
			}
		}
		m_Statement = m_DBConnection->createStatement();
	}
	catch (std::exception e)
	{
		WriteLog(LogLevel::Warning, "Connect MysqlDB Failed. Msg:%s", e.what());
		return false;
	}
	return true;
}
void MysqlDB::DisConnect()
{
	if (m_Statement != nullptr)
	{
		m_Statement->close();
		m_Statement = nullptr;
	}
	if (m_ExchangeCreateStatement != nullptr)
	{
		m_ExchangeCreateStatement->close();
		m_ExchangeCreateStatement = nullptr;
	}
	if (m_ExchangeDropStatement != nullptr)
	{
		m_ExchangeDropStatement->close();
		m_ExchangeDropStatement = nullptr;
	}
	if (m_ExchangeInsertStatement != nullptr)
	{
		m_ExchangeInsertStatement->close();
		m_ExchangeInsertStatement = nullptr;
	}
	if (m_ExchangeDeleteStatement != nullptr)
	{
		m_ExchangeDeleteStatement->close();
		m_ExchangeDeleteStatement = nullptr;
	}
	if (m_ExchangeUpdateStatement != nullptr)
	{
		m_ExchangeUpdateStatement->close();
		m_ExchangeUpdateStatement = nullptr;
	}
	if (m_ExchangeSelectStatement != nullptr)
	{
		m_ExchangeSelectStatement->close();
		m_ExchangeSelectStatement = nullptr;
	}
	if (m_ExchangeTruncateStatement != nullptr)
	{
		m_ExchangeTruncateStatement->close();
		m_ExchangeTruncateStatement = nullptr;
	}
	if (m_InstrumentCreateStatement != nullptr)
	{
		m_InstrumentCreateStatement->close();
		m_InstrumentCreateStatement = nullptr;
	}
	if (m_InstrumentDropStatement != nullptr)
	{
		m_InstrumentDropStatement->close();
		m_InstrumentDropStatement = nullptr;
	}
	if (m_InstrumentInsertStatement != nullptr)
	{
		m_InstrumentInsertStatement->close();
		m_InstrumentInsertStatement = nullptr;
	}
	if (m_InstrumentDeleteStatement != nullptr)
	{
		m_InstrumentDeleteStatement->close();
		m_InstrumentDeleteStatement = nullptr;
	}
	if (m_InstrumentDeleteByExchangeIDIndexStatement != nullptr)
	{
		m_InstrumentDeleteByExchangeIDIndexStatement->close();
		m_InstrumentDeleteByExchangeIDIndexStatement = nullptr;
	}
	if (m_InstrumentUpdateStatement != nullptr)
	{
		m_InstrumentUpdateStatement->close();
		m_InstrumentUpdateStatement = nullptr;
	}
	if (m_InstrumentSelectStatement != nullptr)
	{
		m_InstrumentSelectStatement->close();
		m_InstrumentSelectStatement = nullptr;
	}
	if (m_InstrumentTruncateStatement != nullptr)
	{
		m_InstrumentTruncateStatement->close();
		m_InstrumentTruncateStatement = nullptr;
	}
	if (m_DepthMarketDataCreateStatement != nullptr)
	{
		m_DepthMarketDataCreateStatement->close();
		m_DepthMarketDataCreateStatement = nullptr;
	}
	if (m_DepthMarketDataDropStatement != nullptr)
	{
		m_DepthMarketDataDropStatement->close();
		m_DepthMarketDataDropStatement = nullptr;
	}
	if (m_DepthMarketDataInsertStatement != nullptr)
	{
		m_DepthMarketDataInsertStatement->close();
		m_DepthMarketDataInsertStatement = nullptr;
	}
	if (m_DepthMarketDataDeleteStatement != nullptr)
	{
		m_DepthMarketDataDeleteStatement->close();
		m_DepthMarketDataDeleteStatement = nullptr;
	}
	if (m_DepthMarketDataUpdateStatement != nullptr)
	{
		m_DepthMarketDataUpdateStatement->close();
		m_DepthMarketDataUpdateStatement = nullptr;
	}
	if (m_DepthMarketDataSelectStatement != nullptr)
	{
		m_DepthMarketDataSelectStatement->close();
		m_DepthMarketDataSelectStatement = nullptr;
	}
	if (m_DepthMarketDataTruncateStatement != nullptr)
	{
		m_DepthMarketDataTruncateStatement->close();
		m_DepthMarketDataTruncateStatement = nullptr;
	}
	if (m_BarMarketDataCreateStatement != nullptr)
	{
		m_BarMarketDataCreateStatement->close();
		m_BarMarketDataCreateStatement = nullptr;
	}
	if (m_BarMarketDataDropStatement != nullptr)
	{
		m_BarMarketDataDropStatement->close();
		m_BarMarketDataDropStatement = nullptr;
	}
	if (m_BarMarketDataInsertStatement != nullptr)
	{
		m_BarMarketDataInsertStatement->close();
		m_BarMarketDataInsertStatement = nullptr;
	}
	if (m_BarMarketDataDeleteStatement != nullptr)
	{
		m_BarMarketDataDeleteStatement->close();
		m_BarMarketDataDeleteStatement = nullptr;
	}
	if (m_BarMarketDataUpdateStatement != nullptr)
	{
		m_BarMarketDataUpdateStatement->close();
		m_BarMarketDataUpdateStatement = nullptr;
	}
	if (m_BarMarketDataSelectStatement != nullptr)
	{
		m_BarMarketDataSelectStatement->close();
		m_BarMarketDataSelectStatement = nullptr;
	}
	if (m_BarMarketDataTruncateStatement != nullptr)
	{
		m_BarMarketDataTruncateStatement->close();
		m_BarMarketDataTruncateStatement = nullptr;
	}
	if (m_MdSubscribeCreateStatement != nullptr)
	{
		m_MdSubscribeCreateStatement->close();
		m_MdSubscribeCreateStatement = nullptr;
	}
	if (m_MdSubscribeDropStatement != nullptr)
	{
		m_MdSubscribeDropStatement->close();
		m_MdSubscribeDropStatement = nullptr;
	}
	if (m_MdSubscribeInsertStatement != nullptr)
	{
		m_MdSubscribeInsertStatement->close();
		m_MdSubscribeInsertStatement = nullptr;
	}
	if (m_MdSubscribeDeleteStatement != nullptr)
	{
		m_MdSubscribeDeleteStatement->close();
		m_MdSubscribeDeleteStatement = nullptr;
	}
	if (m_MdSubscribeUpdateStatement != nullptr)
	{
		m_MdSubscribeUpdateStatement->close();
		m_MdSubscribeUpdateStatement = nullptr;
	}
	if (m_MdSubscribeSelectStatement != nullptr)
	{
		m_MdSubscribeSelectStatement->close();
		m_MdSubscribeSelectStatement = nullptr;
	}
	if (m_MdSubscribeTruncateStatement != nullptr)
	{
		m_MdSubscribeTruncateStatement->close();
		m_MdSubscribeTruncateStatement = nullptr;
	}
	if (m_MdUserCreateStatement != nullptr)
	{
		m_MdUserCreateStatement->close();
		m_MdUserCreateStatement = nullptr;
	}
	if (m_MdUserDropStatement != nullptr)
	{
		m_MdUserDropStatement->close();
		m_MdUserDropStatement = nullptr;
	}
	if (m_MdUserInsertStatement != nullptr)
	{
		m_MdUserInsertStatement->close();
		m_MdUserInsertStatement = nullptr;
	}
	if (m_MdUserDeleteStatement != nullptr)
	{
		m_MdUserDeleteStatement->close();
		m_MdUserDeleteStatement = nullptr;
	}
	if (m_MdUserUpdateStatement != nullptr)
	{
		m_MdUserUpdateStatement->close();
		m_MdUserUpdateStatement = nullptr;
	}
	if (m_MdUserSelectStatement != nullptr)
	{
		m_MdUserSelectStatement->close();
		m_MdUserSelectStatement = nullptr;
	}
	if (m_MdUserTruncateStatement != nullptr)
	{
		m_MdUserTruncateStatement->close();
		m_MdUserTruncateStatement = nullptr;
	}
	if (m_MdUserLoginSessionCreateStatement != nullptr)
	{
		m_MdUserLoginSessionCreateStatement->close();
		m_MdUserLoginSessionCreateStatement = nullptr;
	}
	if (m_MdUserLoginSessionDropStatement != nullptr)
	{
		m_MdUserLoginSessionDropStatement->close();
		m_MdUserLoginSessionDropStatement = nullptr;
	}
	if (m_MdUserLoginSessionInsertStatement != nullptr)
	{
		m_MdUserLoginSessionInsertStatement->close();
		m_MdUserLoginSessionInsertStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteStatement != nullptr)
	{
		m_MdUserLoginSessionDeleteStatement->close();
		m_MdUserLoginSessionDeleteStatement = nullptr;
	}
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement != nullptr)
	{
		m_MdUserLoginSessionDeleteByMdUserIDIndexStatement->close();
		m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = nullptr;
	}
	if (m_MdUserLoginSessionUpdateStatement != nullptr)
	{
		m_MdUserLoginSessionUpdateStatement->close();
		m_MdUserLoginSessionUpdateStatement = nullptr;
	}
	if (m_MdUserLoginSessionSelectStatement != nullptr)
	{
		m_MdUserLoginSessionSelectStatement->close();
		m_MdUserLoginSessionSelectStatement = nullptr;
	}
	if (m_MdUserLoginSessionTruncateStatement != nullptr)
	{
		m_MdUserLoginSessionTruncateStatement->close();
		m_MdUserLoginSessionTruncateStatement = nullptr;
	}
}
void MysqlDB::InitDB()
{
	m_Statement->executeUpdate("Truncate Table t_Exchange;");
	m_Statement->executeUpdate("Insert Into t_Exchange select * from Init.t_Exchange;");
	m_Statement->executeUpdate("Truncate Table t_Instrument;");
	m_Statement->executeUpdate("Insert Into t_Instrument select * from Init.t_Instrument;");
	m_Statement->executeUpdate("Truncate Table t_DepthMarketData;");
	m_Statement->executeUpdate("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	m_Statement->executeUpdate("Truncate Table t_BarMarketData;");
	m_Statement->executeUpdate("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	m_Statement->executeUpdate("Truncate Table t_MdSubscribe;");
	m_Statement->executeUpdate("Insert Into t_MdSubscribe select * from Init.t_MdSubscribe;");
	m_Statement->executeUpdate("Truncate Table t_MdUser;");
	m_Statement->executeUpdate("Insert Into t_MdUser select * from Init.t_MdUser;");
	m_Statement->executeUpdate("Truncate Table t_MdUserLoginSession;");
	m_Statement->executeUpdate("Insert Into t_MdUserLoginSession select * from Init.t_MdUserLoginSession;");
}
void MysqlDB::CreateTables()
{
	CreateExchange();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreateMdSubscribe();
	CreateMdUser();
	CreateMdUserLoginSession();
}
void MysqlDB::DropTables()
{
	DropExchange();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropMdSubscribe();
	DropMdUser();
	DropMdUserLoginSession();
}
void MysqlDB::TruncateTables()
{
	TruncateExchange();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncateMdSubscribe();
	TruncateMdUser();
	TruncateMdUserLoginSession();
}
void MysqlDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateMdUserLoginSession();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}

void MysqlDB::CreateExchange()
{
	auto start = steady_clock::now();
	if (m_ExchangeCreateStatement == nullptr)
	{
		m_ExchangeCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Exchange(`ExchangeID` char(8), `ExchangeName` char(64), PRIMARY KEY(ExchangeID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_ExchangeCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateExchange Spend:%lldms", duration);
}
void MysqlDB::DropExchange()
{
	auto start = steady_clock::now();
	if (m_ExchangeDropStatement == nullptr)
	{
		m_ExchangeDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Exchange;");
	}
	m_ExchangeDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropExchange Spend:%lldms", duration);
}
void MysqlDB::InsertExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeInsertStatement == nullptr)
	{
		m_ExchangeInsertStatement = m_DBConnection->prepareStatement("insert into t_Exchange Values(?, ?);");
	}
	SetStatementForExchangeRecord(m_ExchangeInsertStatement, record);
	
	m_ExchangeInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertExchange Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertExchange(std::list<Exchange*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Exchange Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertExchange Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Exchange Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertExchange Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertExchange RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeDeleteStatement == nullptr)
	{
		m_ExchangeDeleteStatement = m_DBConnection->prepareStatement("delete from t_Exchange where ExchangeID = ?;");
	}
	SetStatementForExchangePrimaryKey(m_ExchangeDeleteStatement, record->ExchangeID);
	m_ExchangeDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteExchange Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateExchange(Exchange* record)
{
	auto start = steady_clock::now();
	if (m_ExchangeUpdateStatement == nullptr)
	{
		m_ExchangeUpdateStatement = m_DBConnection->prepareStatement("update t_Exchange set ExchangeName = ? where ExchangeID = ?;");
	}
	SetStatementForExchangeRecordUpdate(m_ExchangeUpdateStatement, record);
	m_ExchangeUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateExchange Spend:%lldms", duration);
	}
}
void MysqlDB::SelectExchange(std::list<Exchange*>& records)
{
	auto start = steady_clock::now();
	if (m_ExchangeSelectStatement == nullptr)
	{
		m_ExchangeSelectStatement = m_DBConnection->prepareStatement("select * from t_Exchange;");
	}
	auto result = m_ExchangeSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectExchange Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateExchange()
{
	auto start = steady_clock::now();
	if (m_ExchangeTruncateStatement == nullptr)
	{
		m_ExchangeTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Exchange;");
	}
	m_ExchangeTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateExchange Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentCreateStatement == nullptr)
	{
		m_InstrumentCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Instrument(`ExchangeID` char(8), `InstrumentID` char(32), `ExchangeInstID` char(32), `InstrumentName` char(64), `ProductID` char(32), `ProductClass` int, `InstrumentClass` int, `Rank` int, `VolumeMultiple` int, `PriceTick` decimal(24,8), `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` char(32), INDEX InstrumentExchangeID(ExchangeID), PRIMARY KEY(ExchangeID, InstrumentID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_InstrumentCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateInstrument Spend:%lldms", duration);
}
void MysqlDB::DropInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentDropStatement == nullptr)
	{
		m_InstrumentDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Instrument;");
	}
	m_InstrumentDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropInstrument Spend:%lldms", duration);
}
void MysqlDB::InsertInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentInsertStatement == nullptr)
	{
		m_InstrumentInsertStatement = m_DBConnection->prepareStatement("insert into t_Instrument Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForInstrumentRecord(m_InstrumentInsertStatement, record);
	
	m_InstrumentInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertInstrument(std::list<Instrument*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Instrument Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertInstrument Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Instrument Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertInstrument Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteStatement == nullptr)
	{
		m_InstrumentDeleteStatement = m_DBConnection->prepareStatement("delete from t_Instrument where ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForInstrumentPrimaryKey(m_InstrumentDeleteStatement, record->ExchangeID, record->InstrumentID);
	m_InstrumentDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::DeleteInstrumentByExchangeIDIndex(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentDeleteByExchangeIDIndexStatement == nullptr)
	{
		m_InstrumentDeleteByExchangeIDIndexStatement = m_DBConnection->prepareStatement("delete from t_Instrument where ExchangeID = ?;");
	}
	SetStatementForInstrumentIndexExchangeID(m_InstrumentDeleteByExchangeIDIndexStatement, record);
	m_InstrumentDeleteByExchangeIDIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteInstrumentByExchangeIDIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateInstrument(Instrument* record)
{
	auto start = steady_clock::now();
	if (m_InstrumentUpdateStatement == nullptr)
	{
		m_InstrumentUpdateStatement = m_DBConnection->prepareStatement("update t_Instrument set ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, ProductClass = ?, InstrumentClass = ?, Rank = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForInstrumentRecordUpdate(m_InstrumentUpdateStatement, record);
	m_InstrumentUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::SelectInstrument(std::list<Instrument*>& records)
{
	auto start = steady_clock::now();
	if (m_InstrumentSelectStatement == nullptr)
	{
		m_InstrumentSelectStatement = m_DBConnection->prepareStatement("select * from t_Instrument;");
	}
	auto result = m_InstrumentSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentTruncateStatement == nullptr)
	{
		m_InstrumentTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Instrument;");
	}
	m_InstrumentTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateDepthMarketData()
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataCreateStatement == nullptr)
	{
		m_DepthMarketDataCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_DepthMarketData(`TradingDay` char(9), `ExchangeID` char(8), `InstrumentID` char(32), `UpdateTs` bigint, `LastPrice` decimal(24,8), `PreSettlementPrice` decimal(24,8), `PreClosePrice` decimal(24,8), `PreOpenInterest` decimal(24,8), `OpenPrice` decimal(24,8), `HighestPrice` decimal(24,8), `LowestPrice` decimal(24,8), `ClosePrice` decimal(24,8), `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` decimal(24,8), `Turnover` decimal(24,8), `OpenInterest` decimal(24,8), `SettlementPrice` decimal(24,8), `UpperLimitPrice` decimal(24,8), `LowerLimitPrice` decimal(24,8), `AveragePrice` decimal(24,8), `AskPrice1` decimal(24,8), `AskPrice2` decimal(24,8), `AskPrice3` decimal(24,8), `AskPrice4` decimal(24,8), `AskPrice5` decimal(24,8), `AskPrice6` decimal(24,8), `AskPrice7` decimal(24,8), `AskPrice8` decimal(24,8), `AskPrice9` decimal(24,8), `AskPrice10` decimal(24,8), `AskVolume1` bigint, `AskVolume2` bigint, `AskVolume3` bigint, `AskVolume4` bigint, `AskVolume5` bigint, `AskVolume6` bigint, `AskVolume7` bigint, `AskVolume8` bigint, `AskVolume9` bigint, `AskVolume10` bigint, `BidPrice1` decimal(24,8), `BidPrice2` decimal(24,8), `BidPrice3` decimal(24,8), `BidPrice4` decimal(24,8), `BidPrice5` decimal(24,8), `BidPrice6` decimal(24,8), `BidPrice7` decimal(24,8), `BidPrice8` decimal(24,8), `BidPrice9` decimal(24,8), `BidPrice10` decimal(24,8), `BidVolume1` bigint, `BidVolume2` bigint, `BidVolume3` bigint, `BidVolume4` bigint, `BidVolume5` bigint, `BidVolume6` bigint, `BidVolume7` bigint, `BidVolume8` bigint, `BidVolume9` bigint, `BidVolume10` bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_DepthMarketDataCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateDepthMarketData Spend:%lldms", duration);
}
void MysqlDB::DropDepthMarketData()
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataDropStatement == nullptr)
	{
		m_DepthMarketDataDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_DepthMarketData;");
	}
	m_DepthMarketDataDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropDepthMarketData Spend:%lldms", duration);
}
void MysqlDB::InsertDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataInsertStatement == nullptr)
	{
		m_DepthMarketDataInsertStatement = m_DBConnection->prepareStatement("insert into t_DepthMarketData Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForDepthMarketDataRecord(m_DepthMarketDataInsertStatement, record);
	
	m_DepthMarketDataInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertDepthMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertDepthMarketData(std::list<DepthMarketData*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_DepthMarketData Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_DepthMarketData Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertDepthMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataDeleteStatement == nullptr)
	{
		m_DepthMarketDataDeleteStatement = m_DBConnection->prepareStatement("delete from t_DepthMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForDepthMarketDataPrimaryKey(m_DepthMarketDataDeleteStatement, record->TradingDay, record->ExchangeID, record->InstrumentID);
	m_DepthMarketDataDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteDepthMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateDepthMarketData(DepthMarketData* record)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataUpdateStatement == nullptr)
	{
		m_DepthMarketDataUpdateStatement = m_DBConnection->prepareStatement("update t_DepthMarketData set UpdateTs = ?, LastPrice = ?, PreSettlementPrice = ?, PreClosePrice = ?, PreOpenInterest = ?, OpenPrice = ?, HighestPrice = ?, LowestPrice = ?, ClosePrice = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ?, SettlementPrice = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, AveragePrice = ?, AskPrice1 = ?, AskPrice2 = ?, AskPrice3 = ?, AskPrice4 = ?, AskPrice5 = ?, AskPrice6 = ?, AskPrice7 = ?, AskPrice8 = ?, AskPrice9 = ?, AskPrice10 = ?, AskVolume1 = ?, AskVolume2 = ?, AskVolume3 = ?, AskVolume4 = ?, AskVolume5 = ?, AskVolume6 = ?, AskVolume7 = ?, AskVolume8 = ?, AskVolume9 = ?, AskVolume10 = ?, BidPrice1 = ?, BidPrice2 = ?, BidPrice3 = ?, BidPrice4 = ?, BidPrice5 = ?, BidPrice6 = ?, BidPrice7 = ?, BidPrice8 = ?, BidPrice9 = ?, BidPrice10 = ?, BidVolume1 = ?, BidVolume2 = ?, BidVolume3 = ?, BidVolume4 = ?, BidVolume5 = ?, BidVolume6 = ?, BidVolume7 = ?, BidVolume8 = ?, BidVolume9 = ?, BidVolume10 = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForDepthMarketDataRecordUpdate(m_DepthMarketDataUpdateStatement, record);
	m_DepthMarketDataUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::SelectDepthMarketData(std::list<DepthMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataSelectStatement == nullptr)
	{
		m_DepthMarketDataSelectStatement = m_DBConnection->prepareStatement("select * from t_DepthMarketData where TradingDay >= ?;");
	}
	m_DepthMarketDataSelectStatement->setString(1, tradingDay);
	auto result = m_DepthMarketDataSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectDepthMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateDepthMarketData()
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataTruncateStatement == nullptr)
	{
		m_DepthMarketDataTruncateStatement = m_DBConnection->prepareStatement("truncate table t_DepthMarketData;");
	}
	m_DepthMarketDataTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateDepthMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateBarMarketData()
{
	auto start = steady_clock::now();
	if (m_BarMarketDataCreateStatement == nullptr)
	{
		m_BarMarketDataCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_BarMarketData(`TradingDay` char(9), `ExchangeID` char(8), `InstrumentID` char(32), `BarPreces` int, `BarPeriod` int, `BarTime` bigint, `UpdateTs` bigint, `PreSettlementPrice` decimal(24,8), `PreClosePrice` decimal(24,8), `Open` decimal(24,8), `High` decimal(24,8), `Low` decimal(24,8), `Close` decimal(24,8), `CurrVolume` bigint, `Volume` bigint, `CurrTurnover` decimal(24,8), `Turnover` decimal(24,8), `OpenInterest` decimal(24,8), PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_BarMarketDataCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateBarMarketData Spend:%lldms", duration);
}
void MysqlDB::DropBarMarketData()
{
	auto start = steady_clock::now();
	if (m_BarMarketDataDropStatement == nullptr)
	{
		m_BarMarketDataDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_BarMarketData;");
	}
	m_BarMarketDataDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropBarMarketData Spend:%lldms", duration);
}
void MysqlDB::InsertBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataInsertStatement == nullptr)
	{
		m_BarMarketDataInsertStatement = m_DBConnection->prepareStatement("insert into t_BarMarketData Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForBarMarketDataRecord(m_BarMarketDataInsertStatement, record);
	
	m_BarMarketDataInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertBarMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertBarMarketData(std::list<BarMarketData*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_BarMarketData Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertBarMarketData Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_BarMarketData Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertBarMarketData Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertBarMarketData RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataDeleteStatement == nullptr)
	{
		m_BarMarketDataDeleteStatement = m_DBConnection->prepareStatement("delete from t_BarMarketData where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;");
	}
	SetStatementForBarMarketDataPrimaryKey(m_BarMarketDataDeleteStatement, record->TradingDay, record->ExchangeID, record->InstrumentID, record->BarPreces, record->BarPeriod, record->BarTime);
	m_BarMarketDataDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteBarMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateBarMarketData(BarMarketData* record)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataUpdateStatement == nullptr)
	{
		m_BarMarketDataUpdateStatement = m_DBConnection->prepareStatement("update t_BarMarketData set UpdateTs = ?, PreSettlementPrice = ?, PreClosePrice = ?, Open = ?, High = ?, Low = ?, Close = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ? and BarPreces = ? and BarPeriod = ? and BarTime = ?;");
	}
	SetStatementForBarMarketDataRecordUpdate(m_BarMarketDataUpdateStatement, record);
	m_BarMarketDataUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateBarMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::SelectBarMarketData(std::list<BarMarketData*>& records, const DateType& tradingDay)
{
	auto start = steady_clock::now();
	if (m_BarMarketDataSelectStatement == nullptr)
	{
		m_BarMarketDataSelectStatement = m_DBConnection->prepareStatement("select * from t_BarMarketData where TradingDay >= ?;");
	}
	m_BarMarketDataSelectStatement->setString(1, tradingDay);
	auto result = m_BarMarketDataSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectBarMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateBarMarketData()
{
	auto start = steady_clock::now();
	if (m_BarMarketDataTruncateStatement == nullptr)
	{
		m_BarMarketDataTruncateStatement = m_DBConnection->prepareStatement("truncate table t_BarMarketData;");
	}
	m_BarMarketDataTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateBarMarketData Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateMdSubscribe()
{
	auto start = steady_clock::now();
	if (m_MdSubscribeCreateStatement == nullptr)
	{
		m_MdSubscribeCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_MdSubscribe(`ExchangeID` char(8), `InstrumentID` char(32), `RealInstrumentID` char(32), `ProductID` char(32), `ProductClass` int, `StartTradingDay` char(9), `EndTradingDay` char(9), PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_MdSubscribeCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdSubscribe Spend:%lldms", duration);
}
void MysqlDB::DropMdSubscribe()
{
	auto start = steady_clock::now();
	if (m_MdSubscribeDropStatement == nullptr)
	{
		m_MdSubscribeDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_MdSubscribe;");
	}
	m_MdSubscribeDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdSubscribe Spend:%lldms", duration);
}
void MysqlDB::InsertMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeInsertStatement == nullptr)
	{
		m_MdSubscribeInsertStatement = m_DBConnection->prepareStatement("insert into t_MdSubscribe Values(?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForMdSubscribeRecord(m_MdSubscribeInsertStatement, record);
	
	m_MdSubscribeInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdSubscribe Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertMdSubscribe(std::list<MdSubscribe*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdSubscribe Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdSubscribe Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdSubscribe RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeDeleteStatement == nullptr)
	{
		m_MdSubscribeDeleteStatement = m_DBConnection->prepareStatement("delete from t_MdSubscribe where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;");
	}
	SetStatementForMdSubscribePrimaryKey(m_MdSubscribeDeleteStatement, record->ExchangeID, record->InstrumentID, record->StartTradingDay);
	m_MdSubscribeDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdSubscribe Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateMdSubscribe(MdSubscribe* record)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeUpdateStatement == nullptr)
	{
		m_MdSubscribeUpdateStatement = m_DBConnection->prepareStatement("update t_MdSubscribe set RealInstrumentID = ?, ProductID = ?, ProductClass = ?, EndTradingDay = ? where ExchangeID = ? and InstrumentID = ? and StartTradingDay = ?;");
	}
	SetStatementForMdSubscribeRecordUpdate(m_MdSubscribeUpdateStatement, record);
	m_MdSubscribeUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdSubscribe Spend:%lldms", duration);
	}
}
void MysqlDB::SelectMdSubscribe(std::list<MdSubscribe*>& records)
{
	auto start = steady_clock::now();
	if (m_MdSubscribeSelectStatement == nullptr)
	{
		m_MdSubscribeSelectStatement = m_DBConnection->prepareStatement("select * from t_MdSubscribe;");
	}
	auto result = m_MdSubscribeSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdSubscribe Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateMdSubscribe()
{
	auto start = steady_clock::now();
	if (m_MdSubscribeTruncateStatement == nullptr)
	{
		m_MdSubscribeTruncateStatement = m_DBConnection->prepareStatement("truncate table t_MdSubscribe;");
	}
	m_MdSubscribeTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateMdSubscribe Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateMdUser()
{
	auto start = steady_clock::now();
	if (m_MdUserCreateStatement == nullptr)
	{
		m_MdUserCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_MdUser(`MdUserID` char(32), `MdUserName` char(64), `Password` char(64), PRIMARY KEY(MdUserID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_MdUserCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUser Spend:%lldms", duration);
}
void MysqlDB::DropMdUser()
{
	auto start = steady_clock::now();
	if (m_MdUserDropStatement == nullptr)
	{
		m_MdUserDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_MdUser;");
	}
	m_MdUserDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUser Spend:%lldms", duration);
}
void MysqlDB::InsertMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserInsertStatement == nullptr)
	{
		m_MdUserInsertStatement = m_DBConnection->prepareStatement("insert into t_MdUser Values(?, ?, ?);");
	}
	SetStatementForMdUserRecord(m_MdUserInsertStatement, record);
	
	m_MdUserInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdUser Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertMdUser(std::list<MdUser*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdUser Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertMdUser Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdUser Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdUser Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdUser RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserDeleteStatement == nullptr)
	{
		m_MdUserDeleteStatement = m_DBConnection->prepareStatement("delete from t_MdUser where MdUserID = ?;");
	}
	SetStatementForMdUserPrimaryKey(m_MdUserDeleteStatement, record->MdUserID);
	m_MdUserDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUser Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateMdUser(MdUser* record)
{
	auto start = steady_clock::now();
	if (m_MdUserUpdateStatement == nullptr)
	{
		m_MdUserUpdateStatement = m_DBConnection->prepareStatement("update t_MdUser set MdUserName = ?, Password = ? where MdUserID = ?;");
	}
	SetStatementForMdUserRecordUpdate(m_MdUserUpdateStatement, record);
	m_MdUserUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUser Spend:%lldms", duration);
	}
}
void MysqlDB::SelectMdUser(std::list<MdUser*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserSelectStatement == nullptr)
	{
		m_MdUserSelectStatement = m_DBConnection->prepareStatement("select * from t_MdUser;");
	}
	auto result = m_MdUserSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUser Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateMdUser()
{
	auto start = steady_clock::now();
	if (m_MdUserTruncateStatement == nullptr)
	{
		m_MdUserTruncateStatement = m_DBConnection->prepareStatement("truncate table t_MdUser;");
	}
	m_MdUserTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateMdUser Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::CreateMdUserLoginSession()
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionCreateStatement == nullptr)
	{
		m_MdUserLoginSessionCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(`MdUserID` char(32), `SessionID` bigint, `IPAddress` char(16), INDEX MdUserLoginSessionMdUserID(MdUserID), PRIMARY KEY(SessionID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_MdUserLoginSessionCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateMdUserLoginSession Spend:%lldms", duration);
}
void MysqlDB::DropMdUserLoginSession()
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDropStatement == nullptr)
	{
		m_MdUserLoginSessionDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_MdUserLoginSession;");
	}
	m_MdUserLoginSessionDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropMdUserLoginSession Spend:%lldms", duration);
}
void MysqlDB::InsertMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionInsertStatement == nullptr)
	{
		m_MdUserLoginSessionInsertStatement = m_DBConnection->prepareStatement("insert into t_MdUserLoginSession Values(?, ?, ?);");
	}
	SetStatementForMdUserLoginSessionRecord(m_MdUserLoginSessionInsertStatement, record);
	
	m_MdUserLoginSessionInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertMdUserLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertMdUserLoginSession(std::list<MdUserLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_MdUserLoginSession Values");
	int n = (int)strlen(m_SqlBuff);
	int i = 0;
	for (auto it = records->begin(); it != records->end(); ++it, ++i)
	{
		if (n > 60000)
		{
			m_SqlBuff[n - 1] = ';';
			try
			{
				m_Statement->executeUpdate(m_SqlBuff);
			}
			catch(exception e)
			{
				WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_MdUserLoginSession Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';
	try
	{
		m_Statement->executeUpdate(m_SqlBuff);
	}
	catch(exception e)
	{
		WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertMdUserLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteStatement == nullptr)
	{
		m_MdUserLoginSessionDeleteStatement = m_DBConnection->prepareStatement("delete from t_MdUserLoginSession where SessionID = ?;");
	}
	SetStatementForMdUserLoginSessionPrimaryKey(m_MdUserLoginSessionDeleteStatement, record->SessionID);
	m_MdUserLoginSessionDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::DeleteMdUserLoginSessionByMdUserIDIndex(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionDeleteByMdUserIDIndexStatement == nullptr)
	{
		m_MdUserLoginSessionDeleteByMdUserIDIndexStatement = m_DBConnection->prepareStatement("delete from t_MdUserLoginSession where MdUserID = ?;");
	}
	SetStatementForMdUserLoginSessionIndexMdUserID(m_MdUserLoginSessionDeleteByMdUserIDIndexStatement, record);
	m_MdUserLoginSessionDeleteByMdUserIDIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteMdUserLoginSessionByMdUserIDIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateMdUserLoginSession(MdUserLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionUpdateStatement == nullptr)
	{
		m_MdUserLoginSessionUpdateStatement = m_DBConnection->prepareStatement("update t_MdUserLoginSession set MdUserID = ?, IPAddress = ? where SessionID = ?;");
	}
	SetStatementForMdUserLoginSessionRecordUpdate(m_MdUserLoginSessionUpdateStatement, record);
	m_MdUserLoginSessionUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateMdUserLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::SelectMdUserLoginSession(std::list<MdUserLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionSelectStatement == nullptr)
	{
		m_MdUserLoginSessionSelectStatement = m_DBConnection->prepareStatement("select * from t_MdUserLoginSession;");
	}
	auto result = m_MdUserLoginSessionSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectMdUserLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateMdUserLoginSession()
{
	auto start = steady_clock::now();
	if (m_MdUserLoginSessionTruncateStatement == nullptr)
	{
		m_MdUserLoginSessionTruncateStatement = m_DBConnection->prepareStatement("truncate table t_MdUserLoginSession;");
	}
	m_MdUserLoginSessionTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateMdUserLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}


void MysqlDB::SetStatementForExchangeRecord(sql::PreparedStatement* statement, Exchange* record)
{
	statement->setString(1, record->ExchangeID);
	statement->setString(2, record->ExchangeName);
}
void MysqlDB::SetStatementForExchangeRecordUpdate(sql::PreparedStatement* statement, Exchange* record)
{
	statement->setString(1, record->ExchangeName);
	statement->setString(2, record->ExchangeID);
}
void MysqlDB::SetStatementForExchangePrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID)
{
	statement->setString(1, ExchangeID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Exchange*>& records)
{
	Exchange* record = Exchange::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->ExchangeName, result->getString(2).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForInstrumentRecord(sql::PreparedStatement* statement, Instrument* record)
{
	statement->setString(1, record->ExchangeID);
	statement->setString(2, record->InstrumentID);
	statement->setString(3, record->ExchangeInstID);
	statement->setString(4, record->InstrumentName);
	statement->setString(5, record->ProductID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt(7, int(record->InstrumentClass));
	statement->setInt(8, record->Rank);
	statement->setInt(9, record->VolumeMultiple);
	statement->setDouble(10, record->PriceTick);
	statement->setInt64(11, record->MaxMarketOrderVolume);
	statement->setInt64(12, record->MinMarketOrderVolume);
	statement->setInt64(13, record->MaxLimitOrderVolume);
	statement->setInt64(14, record->MinLimitOrderVolume);
	statement->setString(15, record->SessionName);
}
void MysqlDB::SetStatementForInstrumentRecordUpdate(sql::PreparedStatement* statement, Instrument* record)
{
	statement->setString(1, record->ExchangeInstID);
	statement->setString(2, record->InstrumentName);
	statement->setString(3, record->ProductID);
	statement->setInt(4, int(record->ProductClass));
	statement->setInt(5, int(record->InstrumentClass));
	statement->setInt(6, record->Rank);
	statement->setInt(7, record->VolumeMultiple);
	statement->setDouble(8, record->PriceTick);
	statement->setInt64(9, record->MaxMarketOrderVolume);
	statement->setInt64(10, record->MinMarketOrderVolume);
	statement->setInt64(11, record->MaxLimitOrderVolume);
	statement->setInt64(12, record->MinLimitOrderVolume);
	statement->setString(13, record->SessionName);
	statement->setString(14, record->ExchangeID);
	statement->setString(15, record->InstrumentID);
}
void MysqlDB::SetStatementForInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	statement->setString(1, ExchangeID);
	statement->setString(2, InstrumentID);
}
void MysqlDB::SetStatementForInstrumentIndexExchangeID(sql::PreparedStatement* statement, Instrument* record)
{
	statement->setString(1, record->ExchangeID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Instrument*>& records)
{
	Instrument* record = Instrument::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->InstrumentID, result->getString(2).c_str());
	Strcpy(record->ExchangeInstID, result->getString(3).c_str());
	Strcpy(record->InstrumentName, result->getString(4).c_str());
	Strcpy(record->ProductID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->InstrumentClass = InstrumentClassType(result->getInt(7));
	record->Rank = result->getInt(8);
	record->VolumeMultiple = result->getInt(9);
	record->PriceTick = result->getDouble(10);
	record->MaxMarketOrderVolume = result->getInt64(11);
	record->MinMarketOrderVolume = result->getInt64(12);
	record->MaxLimitOrderVolume = result->getInt64(13);
	record->MinLimitOrderVolume = result->getInt64(14);
	Strcpy(record->SessionName, result->getString(15).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForDepthMarketDataRecord(sql::PreparedStatement* statement, DepthMarketData* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->ExchangeID);
	statement->setString(3, record->InstrumentID);
	statement->setInt64(4, record->UpdateTs);
	statement->setDouble(5, record->LastPrice);
	statement->setDouble(6, record->PreSettlementPrice);
	statement->setDouble(7, record->PreClosePrice);
	statement->setDouble(8, record->PreOpenInterest);
	statement->setDouble(9, record->OpenPrice);
	statement->setDouble(10, record->HighestPrice);
	statement->setDouble(11, record->LowestPrice);
	statement->setDouble(12, record->ClosePrice);
	statement->setInt64(13, record->CurrVolume);
	statement->setInt64(14, record->Volume);
	statement->setDouble(15, record->CurrTurnover);
	statement->setDouble(16, record->Turnover);
	statement->setDouble(17, record->OpenInterest);
	statement->setDouble(18, record->SettlementPrice);
	statement->setDouble(19, record->UpperLimitPrice);
	statement->setDouble(20, record->LowerLimitPrice);
	statement->setDouble(21, record->AveragePrice);
	statement->setDouble(22, record->AskPrice1);
	statement->setDouble(23, record->AskPrice2);
	statement->setDouble(24, record->AskPrice3);
	statement->setDouble(25, record->AskPrice4);
	statement->setDouble(26, record->AskPrice5);
	statement->setDouble(27, record->AskPrice6);
	statement->setDouble(28, record->AskPrice7);
	statement->setDouble(29, record->AskPrice8);
	statement->setDouble(30, record->AskPrice9);
	statement->setDouble(31, record->AskPrice10);
	statement->setInt64(32, record->AskVolume1);
	statement->setInt64(33, record->AskVolume2);
	statement->setInt64(34, record->AskVolume3);
	statement->setInt64(35, record->AskVolume4);
	statement->setInt64(36, record->AskVolume5);
	statement->setInt64(37, record->AskVolume6);
	statement->setInt64(38, record->AskVolume7);
	statement->setInt64(39, record->AskVolume8);
	statement->setInt64(40, record->AskVolume9);
	statement->setInt64(41, record->AskVolume10);
	statement->setDouble(42, record->BidPrice1);
	statement->setDouble(43, record->BidPrice2);
	statement->setDouble(44, record->BidPrice3);
	statement->setDouble(45, record->BidPrice4);
	statement->setDouble(46, record->BidPrice5);
	statement->setDouble(47, record->BidPrice6);
	statement->setDouble(48, record->BidPrice7);
	statement->setDouble(49, record->BidPrice8);
	statement->setDouble(50, record->BidPrice9);
	statement->setDouble(51, record->BidPrice10);
	statement->setInt64(52, record->BidVolume1);
	statement->setInt64(53, record->BidVolume2);
	statement->setInt64(54, record->BidVolume3);
	statement->setInt64(55, record->BidVolume4);
	statement->setInt64(56, record->BidVolume5);
	statement->setInt64(57, record->BidVolume6);
	statement->setInt64(58, record->BidVolume7);
	statement->setInt64(59, record->BidVolume8);
	statement->setInt64(60, record->BidVolume9);
	statement->setInt64(61, record->BidVolume10);
}
void MysqlDB::SetStatementForDepthMarketDataRecordUpdate(sql::PreparedStatement* statement, DepthMarketData* record)
{
	statement->setInt64(1, record->UpdateTs);
	statement->setDouble(2, record->LastPrice);
	statement->setDouble(3, record->PreSettlementPrice);
	statement->setDouble(4, record->PreClosePrice);
	statement->setDouble(5, record->PreOpenInterest);
	statement->setDouble(6, record->OpenPrice);
	statement->setDouble(7, record->HighestPrice);
	statement->setDouble(8, record->LowestPrice);
	statement->setDouble(9, record->ClosePrice);
	statement->setInt64(10, record->CurrVolume);
	statement->setInt64(11, record->Volume);
	statement->setDouble(12, record->CurrTurnover);
	statement->setDouble(13, record->Turnover);
	statement->setDouble(14, record->OpenInterest);
	statement->setDouble(15, record->SettlementPrice);
	statement->setDouble(16, record->UpperLimitPrice);
	statement->setDouble(17, record->LowerLimitPrice);
	statement->setDouble(18, record->AveragePrice);
	statement->setDouble(19, record->AskPrice1);
	statement->setDouble(20, record->AskPrice2);
	statement->setDouble(21, record->AskPrice3);
	statement->setDouble(22, record->AskPrice4);
	statement->setDouble(23, record->AskPrice5);
	statement->setDouble(24, record->AskPrice6);
	statement->setDouble(25, record->AskPrice7);
	statement->setDouble(26, record->AskPrice8);
	statement->setDouble(27, record->AskPrice9);
	statement->setDouble(28, record->AskPrice10);
	statement->setInt64(29, record->AskVolume1);
	statement->setInt64(30, record->AskVolume2);
	statement->setInt64(31, record->AskVolume3);
	statement->setInt64(32, record->AskVolume4);
	statement->setInt64(33, record->AskVolume5);
	statement->setInt64(34, record->AskVolume6);
	statement->setInt64(35, record->AskVolume7);
	statement->setInt64(36, record->AskVolume8);
	statement->setInt64(37, record->AskVolume9);
	statement->setInt64(38, record->AskVolume10);
	statement->setDouble(39, record->BidPrice1);
	statement->setDouble(40, record->BidPrice2);
	statement->setDouble(41, record->BidPrice3);
	statement->setDouble(42, record->BidPrice4);
	statement->setDouble(43, record->BidPrice5);
	statement->setDouble(44, record->BidPrice6);
	statement->setDouble(45, record->BidPrice7);
	statement->setDouble(46, record->BidPrice8);
	statement->setDouble(47, record->BidPrice9);
	statement->setDouble(48, record->BidPrice10);
	statement->setInt64(49, record->BidVolume1);
	statement->setInt64(50, record->BidVolume2);
	statement->setInt64(51, record->BidVolume3);
	statement->setInt64(52, record->BidVolume4);
	statement->setInt64(53, record->BidVolume5);
	statement->setInt64(54, record->BidVolume6);
	statement->setInt64(55, record->BidVolume7);
	statement->setInt64(56, record->BidVolume8);
	statement->setInt64(57, record->BidVolume9);
	statement->setInt64(58, record->BidVolume10);
	statement->setString(59, record->TradingDay);
	statement->setString(60, record->ExchangeID);
	statement->setString(61, record->InstrumentID);
}
void MysqlDB::SetStatementForDepthMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	statement->setString(1, TradingDay);
	statement->setString(2, ExchangeID);
	statement->setString(3, InstrumentID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<DepthMarketData*>& records)
{
	DepthMarketData* record = DepthMarketData::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->ExchangeID, result->getString(2).c_str());
	Strcpy(record->InstrumentID, result->getString(3).c_str());
	record->UpdateTs = result->getInt64(4);
	record->LastPrice = result->getDouble(5);
	record->PreSettlementPrice = result->getDouble(6);
	record->PreClosePrice = result->getDouble(7);
	record->PreOpenInterest = result->getDouble(8);
	record->OpenPrice = result->getDouble(9);
	record->HighestPrice = result->getDouble(10);
	record->LowestPrice = result->getDouble(11);
	record->ClosePrice = result->getDouble(12);
	record->CurrVolume = result->getInt64(13);
	record->Volume = result->getInt64(14);
	record->CurrTurnover = result->getDouble(15);
	record->Turnover = result->getDouble(16);
	record->OpenInterest = result->getDouble(17);
	record->SettlementPrice = result->getDouble(18);
	record->UpperLimitPrice = result->getDouble(19);
	record->LowerLimitPrice = result->getDouble(20);
	record->AveragePrice = result->getDouble(21);
	record->AskPrice1 = result->getDouble(22);
	record->AskPrice2 = result->getDouble(23);
	record->AskPrice3 = result->getDouble(24);
	record->AskPrice4 = result->getDouble(25);
	record->AskPrice5 = result->getDouble(26);
	record->AskPrice6 = result->getDouble(27);
	record->AskPrice7 = result->getDouble(28);
	record->AskPrice8 = result->getDouble(29);
	record->AskPrice9 = result->getDouble(30);
	record->AskPrice10 = result->getDouble(31);
	record->AskVolume1 = result->getInt64(32);
	record->AskVolume2 = result->getInt64(33);
	record->AskVolume3 = result->getInt64(34);
	record->AskVolume4 = result->getInt64(35);
	record->AskVolume5 = result->getInt64(36);
	record->AskVolume6 = result->getInt64(37);
	record->AskVolume7 = result->getInt64(38);
	record->AskVolume8 = result->getInt64(39);
	record->AskVolume9 = result->getInt64(40);
	record->AskVolume10 = result->getInt64(41);
	record->BidPrice1 = result->getDouble(42);
	record->BidPrice2 = result->getDouble(43);
	record->BidPrice3 = result->getDouble(44);
	record->BidPrice4 = result->getDouble(45);
	record->BidPrice5 = result->getDouble(46);
	record->BidPrice6 = result->getDouble(47);
	record->BidPrice7 = result->getDouble(48);
	record->BidPrice8 = result->getDouble(49);
	record->BidPrice9 = result->getDouble(50);
	record->BidPrice10 = result->getDouble(51);
	record->BidVolume1 = result->getInt64(52);
	record->BidVolume2 = result->getInt64(53);
	record->BidVolume3 = result->getInt64(54);
	record->BidVolume4 = result->getInt64(55);
	record->BidVolume5 = result->getInt64(56);
	record->BidVolume6 = result->getInt64(57);
	record->BidVolume7 = result->getInt64(58);
	record->BidVolume8 = result->getInt64(59);
	record->BidVolume9 = result->getInt64(60);
	record->BidVolume10 = result->getInt64(61);
	records.push_back(record);
}
void MysqlDB::SetStatementForBarMarketDataRecord(sql::PreparedStatement* statement, BarMarketData* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->ExchangeID);
	statement->setString(3, record->InstrumentID);
	statement->setInt(4, int(record->BarPreces));
	statement->setInt(5, record->BarPeriod);
	statement->setInt64(6, record->BarTime);
	statement->setInt64(7, record->UpdateTs);
	statement->setDouble(8, record->PreSettlementPrice);
	statement->setDouble(9, record->PreClosePrice);
	statement->setDouble(10, record->Open);
	statement->setDouble(11, record->High);
	statement->setDouble(12, record->Low);
	statement->setDouble(13, record->Close);
	statement->setInt64(14, record->CurrVolume);
	statement->setInt64(15, record->Volume);
	statement->setDouble(16, record->CurrTurnover);
	statement->setDouble(17, record->Turnover);
	statement->setDouble(18, record->OpenInterest);
}
void MysqlDB::SetStatementForBarMarketDataRecordUpdate(sql::PreparedStatement* statement, BarMarketData* record)
{
	statement->setInt64(1, record->UpdateTs);
	statement->setDouble(2, record->PreSettlementPrice);
	statement->setDouble(3, record->PreClosePrice);
	statement->setDouble(4, record->Open);
	statement->setDouble(5, record->High);
	statement->setDouble(6, record->Low);
	statement->setDouble(7, record->Close);
	statement->setInt64(8, record->CurrVolume);
	statement->setInt64(9, record->Volume);
	statement->setDouble(10, record->CurrTurnover);
	statement->setDouble(11, record->Turnover);
	statement->setDouble(12, record->OpenInterest);
	statement->setString(13, record->TradingDay);
	statement->setString(14, record->ExchangeID);
	statement->setString(15, record->InstrumentID);
	statement->setInt(16, int(record->BarPreces));
	statement->setInt(17, record->BarPeriod);
	statement->setInt64(18, record->BarTime);
}
void MysqlDB::SetStatementForBarMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime)
{
	statement->setString(1, TradingDay);
	statement->setString(2, ExchangeID);
	statement->setString(3, InstrumentID);
	statement->setInt(4, int(BarPreces));
	statement->setInt(5, BarPeriod);
	statement->setInt64(6, BarTime);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<BarMarketData*>& records)
{
	BarMarketData* record = BarMarketData::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->ExchangeID, result->getString(2).c_str());
	Strcpy(record->InstrumentID, result->getString(3).c_str());
	record->BarPreces = BarPrecesType(result->getInt(4));
	record->BarPeriod = result->getInt(5);
	record->BarTime = result->getInt64(6);
	record->UpdateTs = result->getInt64(7);
	record->PreSettlementPrice = result->getDouble(8);
	record->PreClosePrice = result->getDouble(9);
	record->Open = result->getDouble(10);
	record->High = result->getDouble(11);
	record->Low = result->getDouble(12);
	record->Close = result->getDouble(13);
	record->CurrVolume = result->getInt64(14);
	record->Volume = result->getInt64(15);
	record->CurrTurnover = result->getDouble(16);
	record->Turnover = result->getDouble(17);
	record->OpenInterest = result->getDouble(18);
	records.push_back(record);
}
void MysqlDB::SetStatementForMdSubscribeRecord(sql::PreparedStatement* statement, MdSubscribe* record)
{
	statement->setString(1, record->ExchangeID);
	statement->setString(2, record->InstrumentID);
	statement->setString(3, record->RealInstrumentID);
	statement->setString(4, record->ProductID);
	statement->setInt(5, int(record->ProductClass));
	statement->setString(6, record->StartTradingDay);
	statement->setString(7, record->EndTradingDay);
}
void MysqlDB::SetStatementForMdSubscribeRecordUpdate(sql::PreparedStatement* statement, MdSubscribe* record)
{
	statement->setString(1, record->RealInstrumentID);
	statement->setString(2, record->ProductID);
	statement->setInt(3, int(record->ProductClass));
	statement->setString(4, record->EndTradingDay);
	statement->setString(5, record->ExchangeID);
	statement->setString(6, record->InstrumentID);
	statement->setString(7, record->StartTradingDay);
}
void MysqlDB::SetStatementForMdSubscribePrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay)
{
	statement->setString(1, ExchangeID);
	statement->setString(2, InstrumentID);
	statement->setString(3, StartTradingDay);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<MdSubscribe*>& records)
{
	MdSubscribe* record = MdSubscribe::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->InstrumentID, result->getString(2).c_str());
	Strcpy(record->RealInstrumentID, result->getString(3).c_str());
	Strcpy(record->ProductID, result->getString(4).c_str());
	record->ProductClass = ProductClassType(result->getInt(5));
	Strcpy(record->StartTradingDay, result->getString(6).c_str());
	Strcpy(record->EndTradingDay, result->getString(7).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForMdUserRecord(sql::PreparedStatement* statement, MdUser* record)
{
	statement->setString(1, record->MdUserID);
	statement->setString(2, record->MdUserName);
	statement->setString(3, record->Password);
}
void MysqlDB::SetStatementForMdUserRecordUpdate(sql::PreparedStatement* statement, MdUser* record)
{
	statement->setString(1, record->MdUserName);
	statement->setString(2, record->Password);
	statement->setString(3, record->MdUserID);
}
void MysqlDB::SetStatementForMdUserPrimaryKey(sql::PreparedStatement* statement, const UserIDType& MdUserID)
{
	statement->setString(1, MdUserID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<MdUser*>& records)
{
	MdUser* record = MdUser::Allocate();
	Strcpy(record->MdUserID, result->getString(1).c_str());
	Strcpy(record->MdUserName, result->getString(2).c_str());
	Strcpy(record->Password, result->getString(3).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForMdUserLoginSessionRecord(sql::PreparedStatement* statement, MdUserLoginSession* record)
{
	statement->setString(1, record->MdUserID);
	statement->setInt64(2, record->SessionID);
	statement->setString(3, record->IPAddress);
}
void MysqlDB::SetStatementForMdUserLoginSessionRecordUpdate(sql::PreparedStatement* statement, MdUserLoginSession* record)
{
	statement->setString(1, record->MdUserID);
	statement->setString(2, record->IPAddress);
	statement->setInt64(3, record->SessionID);
}
void MysqlDB::SetStatementForMdUserLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID)
{
	statement->setInt64(1, SessionID);
}
void MysqlDB::SetStatementForMdUserLoginSessionIndexMdUserID(sql::PreparedStatement* statement, MdUserLoginSession* record)
{
	statement->setString(1, record->MdUserID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<MdUserLoginSession*>& records)
{
	MdUserLoginSession* record = MdUserLoginSession::Allocate();
	Strcpy(record->MdUserID, result->getString(1).c_str());
	record->SessionID = result->getInt64(2);
	Strcpy(record->IPAddress, result->getString(3).c_str());
	records.push_back(record);
}

