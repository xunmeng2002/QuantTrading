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
	if (m_TradingDayInsertStatement != nullptr)
	{
		m_TradingDayInsertStatement->close();
		m_TradingDayInsertStatement = nullptr;
	}
	if (m_TradingDayDeleteStatement != nullptr)
	{
		m_TradingDayDeleteStatement->close();
		m_TradingDayDeleteStatement = nullptr;
	}
	if (m_TradingDayUpdateStatement != nullptr)
	{
		m_TradingDayUpdateStatement->close();
		m_TradingDayUpdateStatement = nullptr;
	}
	if (m_TradingDaySelectStatement != nullptr)
	{
		m_TradingDaySelectStatement->close();
		m_TradingDaySelectStatement = nullptr;
	}
	if (m_TradingDayTruncateStatement != nullptr)
	{
		m_TradingDayTruncateStatement->close();
		m_TradingDayTruncateStatement = nullptr;
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
	if (m_ProductInsertStatement != nullptr)
	{
		m_ProductInsertStatement->close();
		m_ProductInsertStatement = nullptr;
	}
	if (m_ProductDeleteStatement != nullptr)
	{
		m_ProductDeleteStatement->close();
		m_ProductDeleteStatement = nullptr;
	}
	if (m_ProductUpdateStatement != nullptr)
	{
		m_ProductUpdateStatement->close();
		m_ProductUpdateStatement = nullptr;
	}
	if (m_ProductSelectStatement != nullptr)
	{
		m_ProductSelectStatement->close();
		m_ProductSelectStatement = nullptr;
	}
	if (m_ProductTruncateStatement != nullptr)
	{
		m_ProductTruncateStatement->close();
		m_ProductTruncateStatement = nullptr;
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
	if (m_SEBrokerInsertStatement != nullptr)
	{
		m_SEBrokerInsertStatement->close();
		m_SEBrokerInsertStatement = nullptr;
	}
	if (m_SEBrokerDeleteStatement != nullptr)
	{
		m_SEBrokerDeleteStatement->close();
		m_SEBrokerDeleteStatement = nullptr;
	}
	if (m_SEBrokerUpdateStatement != nullptr)
	{
		m_SEBrokerUpdateStatement->close();
		m_SEBrokerUpdateStatement = nullptr;
	}
	if (m_SEBrokerSelectStatement != nullptr)
	{
		m_SEBrokerSelectStatement->close();
		m_SEBrokerSelectStatement = nullptr;
	}
	if (m_SEBrokerTruncateStatement != nullptr)
	{
		m_SEBrokerTruncateStatement->close();
		m_SEBrokerTruncateStatement = nullptr;
	}
	if (m_SEInstrumentInsertStatement != nullptr)
	{
		m_SEInstrumentInsertStatement->close();
		m_SEInstrumentInsertStatement = nullptr;
	}
	if (m_SEInstrumentDeleteStatement != nullptr)
	{
		m_SEInstrumentDeleteStatement->close();
		m_SEInstrumentDeleteStatement = nullptr;
	}
	if (m_SEInstrumentUpdateStatement != nullptr)
	{
		m_SEInstrumentUpdateStatement->close();
		m_SEInstrumentUpdateStatement = nullptr;
	}
	if (m_SEInstrumentSelectStatement != nullptr)
	{
		m_SEInstrumentSelectStatement->close();
		m_SEInstrumentSelectStatement = nullptr;
	}
	if (m_SEInstrumentTruncateStatement != nullptr)
	{
		m_SEInstrumentTruncateStatement->close();
		m_SEInstrumentTruncateStatement = nullptr;
	}
	if (m_SEOrderInsertStatement != nullptr)
	{
		m_SEOrderInsertStatement->close();
		m_SEOrderInsertStatement = nullptr;
	}
	if (m_SEOrderDeleteStatement != nullptr)
	{
		m_SEOrderDeleteStatement->close();
		m_SEOrderDeleteStatement = nullptr;
	}
	if (m_SEOrderUpdateStatement != nullptr)
	{
		m_SEOrderUpdateStatement->close();
		m_SEOrderUpdateStatement = nullptr;
	}
	if (m_SEOrderSelectStatement != nullptr)
	{
		m_SEOrderSelectStatement->close();
		m_SEOrderSelectStatement = nullptr;
	}
	if (m_SEOrderTruncateStatement != nullptr)
	{
		m_SEOrderTruncateStatement->close();
		m_SEOrderTruncateStatement = nullptr;
	}
	if (m_SETradeInsertStatement != nullptr)
	{
		m_SETradeInsertStatement->close();
		m_SETradeInsertStatement = nullptr;
	}
	if (m_SETradeDeleteStatement != nullptr)
	{
		m_SETradeDeleteStatement->close();
		m_SETradeDeleteStatement = nullptr;
	}
	if (m_SETradeUpdateStatement != nullptr)
	{
		m_SETradeUpdateStatement->close();
		m_SETradeUpdateStatement = nullptr;
	}
	if (m_SETradeSelectStatement != nullptr)
	{
		m_SETradeSelectStatement->close();
		m_SETradeSelectStatement = nullptr;
	}
	if (m_SETradeTruncateStatement != nullptr)
	{
		m_SETradeTruncateStatement->close();
		m_SETradeTruncateStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionInsertStatement != nullptr)
	{
		m_SEBrokerLoginSessionInsertStatement->close();
		m_SEBrokerLoginSessionInsertStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionDeleteStatement != nullptr)
	{
		m_SEBrokerLoginSessionDeleteStatement->close();
		m_SEBrokerLoginSessionDeleteStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement != nullptr)
	{
		m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement->close();
		m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionUpdateStatement != nullptr)
	{
		m_SEBrokerLoginSessionUpdateStatement->close();
		m_SEBrokerLoginSessionUpdateStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionSelectStatement != nullptr)
	{
		m_SEBrokerLoginSessionSelectStatement->close();
		m_SEBrokerLoginSessionSelectStatement = nullptr;
	}
	if (m_SEBrokerLoginSessionTruncateStatement != nullptr)
	{
		m_SEBrokerLoginSessionTruncateStatement->close();
		m_SEBrokerLoginSessionTruncateStatement = nullptr;
	}
}
void MysqlDB::InitDB()
{
	m_Statement->executeUpdate("Truncate Table t_TradingDay;");
	m_Statement->executeUpdate("Insert Into t_TradingDay select * from Init.t_TradingDay;");
	m_Statement->executeUpdate("Truncate Table t_Exchange;");
	m_Statement->executeUpdate("Insert Into t_Exchange select * from Init.t_Exchange;");
	m_Statement->executeUpdate("Truncate Table t_Product;");
	m_Statement->executeUpdate("Insert Into t_Product select * from Init.t_Product;");
	m_Statement->executeUpdate("Truncate Table t_DepthMarketData;");
	m_Statement->executeUpdate("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	m_Statement->executeUpdate("Truncate Table t_SEBroker;");
	m_Statement->executeUpdate("Insert Into t_SEBroker select * from Init.t_SEBroker;");
	m_Statement->executeUpdate("Truncate Table t_SEInstrument;");
	m_Statement->executeUpdate("Insert Into t_SEInstrument select * from Init.t_SEInstrument;");
	m_Statement->executeUpdate("Truncate Table t_SEOrder;");
	m_Statement->executeUpdate("Insert Into t_SEOrder select * from Init.t_SEOrder;");
	m_Statement->executeUpdate("Truncate Table t_SETrade;");
	m_Statement->executeUpdate("Insert Into t_SETrade select * from Init.t_SETrade;");
	m_Statement->executeUpdate("Truncate Table t_SEBrokerLoginSession;");
	m_Statement->executeUpdate("Insert Into t_SEBrokerLoginSession select * from Init.t_SEBrokerLoginSession;");
}
void MysqlDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateSEBrokerLoginSession();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::TruncateTables()
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

void MysqlDB::InsertTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayInsertStatement == nullptr)
	{
		m_TradingDayInsertStatement = m_DBConnection->prepareStatement("insert into t_TradingDay Values(?, ?, ?);");
	}
	SetStatementForTradingDayRecord(m_TradingDayInsertStatement, record);
	
	m_TradingDayInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertTradingDay Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertTradingDay(std::list<TradingDay*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_TradingDay Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertTradingDay Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_TradingDay Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertTradingDay Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertTradingDay RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayDeleteStatement == nullptr)
	{
		m_TradingDayDeleteStatement = m_DBConnection->prepareStatement("delete from t_TradingDay where PK = ?;");
	}
	SetStatementForTradingDayPrimaryKey(m_TradingDayDeleteStatement, record->PK);
	m_TradingDayDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTradingDay Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateTradingDay(TradingDay* record)
{
	auto start = steady_clock::now();
	if (m_TradingDayUpdateStatement == nullptr)
	{
		m_TradingDayUpdateStatement = m_DBConnection->prepareStatement("update t_TradingDay set CurrTradingDay = ?, PreTradingDay = ? where PK = ?;");
	}
	SetStatementForTradingDayRecordUpdate(m_TradingDayUpdateStatement, record);
	m_TradingDayUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTradingDay Spend:%lldms", duration);
	}
}
void MysqlDB::SelectTradingDay(std::list<TradingDay*>& records)
{
	auto start = steady_clock::now();
	if (m_TradingDaySelectStatement == nullptr)
	{
		m_TradingDaySelectStatement = m_DBConnection->prepareStatement("select * from t_TradingDay;");
	}
	auto result = m_TradingDaySelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTradingDay Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateTradingDay()
{
	auto start = steady_clock::now();
	if (m_TradingDayTruncateStatement == nullptr)
	{
		m_TradingDayTruncateStatement = m_DBConnection->prepareStatement("truncate table t_TradingDay;");
	}
	m_TradingDayTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateTradingDay Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void MysqlDB::InsertProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductInsertStatement == nullptr)
	{
		m_ProductInsertStatement = m_DBConnection->prepareStatement("insert into t_Product Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForProductRecord(m_ProductInsertStatement, record);
	
	m_ProductInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertProduct Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertProduct(std::list<Product*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Product Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertProduct Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Product Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertProduct Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertProduct RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductDeleteStatement == nullptr)
	{
		m_ProductDeleteStatement = m_DBConnection->prepareStatement("delete from t_Product where ExchangeID = ? and ProductID = ?;");
	}
	SetStatementForProductPrimaryKey(m_ProductDeleteStatement, record->ExchangeID, record->ProductID);
	m_ProductDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteProduct Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateProduct(Product* record)
{
	auto start = steady_clock::now();
	if (m_ProductUpdateStatement == nullptr)
	{
		m_ProductUpdateStatement = m_DBConnection->prepareStatement("update t_Product set ProductName = ?, ProductClass = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and ProductID = ?;");
	}
	SetStatementForProductRecordUpdate(m_ProductUpdateStatement, record);
	m_ProductUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct Spend:%lldms", duration);
	}
}
void MysqlDB::SelectProduct(std::list<Product*>& records)
{
	auto start = steady_clock::now();
	if (m_ProductSelectStatement == nullptr)
	{
		m_ProductSelectStatement = m_DBConnection->prepareStatement("select * from t_Product;");
	}
	auto result = m_ProductSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectProduct Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateProduct()
{
	auto start = steady_clock::now();
	if (m_ProductTruncateStatement == nullptr)
	{
		m_ProductTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Product;");
	}
	m_ProductTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateProduct Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void MysqlDB::SelectDepthMarketData(std::list<DepthMarketData*>& records)
{
	auto start = steady_clock::now();
	if (m_DepthMarketDataSelectStatement == nullptr)
	{
		m_DepthMarketDataSelectStatement = m_DBConnection->prepareStatement("select * from t_DepthMarketData;");
	}
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
void MysqlDB::InsertSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerInsertStatement == nullptr)
	{
		m_SEBrokerInsertStatement = m_DBConnection->prepareStatement("insert into t_SEBroker Values(?, ?, ?);");
	}
	SetStatementForSEBrokerRecord(m_SEBrokerInsertStatement, record);
	
	m_SEBrokerInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEBroker Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertSEBroker(std::list<SEBroker*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEBroker Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertSEBroker Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEBroker Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertSEBroker Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEBroker RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerDeleteStatement == nullptr)
	{
		m_SEBrokerDeleteStatement = m_DBConnection->prepareStatement("delete from t_SEBroker where BrokerID = ?;");
	}
	SetStatementForSEBrokerPrimaryKey(m_SEBrokerDeleteStatement, record->BrokerID);
	m_SEBrokerDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBroker Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateSEBroker(SEBroker* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerUpdateStatement == nullptr)
	{
		m_SEBrokerUpdateStatement = m_DBConnection->prepareStatement("update t_SEBroker set BrokerName = ?, Password = ? where BrokerID = ?;");
	}
	SetStatementForSEBrokerRecordUpdate(m_SEBrokerUpdateStatement, record);
	m_SEBrokerUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBroker Spend:%lldms", duration);
	}
}
void MysqlDB::SelectSEBroker(std::list<SEBroker*>& records)
{
	auto start = steady_clock::now();
	if (m_SEBrokerSelectStatement == nullptr)
	{
		m_SEBrokerSelectStatement = m_DBConnection->prepareStatement("select * from t_SEBroker;");
	}
	auto result = m_SEBrokerSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEBroker Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateSEBroker()
{
	auto start = steady_clock::now();
	if (m_SEBrokerTruncateStatement == nullptr)
	{
		m_SEBrokerTruncateStatement = m_DBConnection->prepareStatement("truncate table t_SEBroker;");
	}
	m_SEBrokerTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateSEBroker Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentInsertStatement == nullptr)
	{
		m_SEInstrumentInsertStatement = m_DBConnection->prepareStatement("insert into t_SEInstrument Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForSEInstrumentRecord(m_SEInstrumentInsertStatement, record);
	
	m_SEInstrumentInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertSEInstrument(std::list<SEInstrument*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEInstrument Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertSEInstrument Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEInstrument Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertSEInstrument Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEInstrument RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentDeleteStatement == nullptr)
	{
		m_SEInstrumentDeleteStatement = m_DBConnection->prepareStatement("delete from t_SEInstrument where ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForSEInstrumentPrimaryKey(m_SEInstrumentDeleteStatement, record->ExchangeID, record->InstrumentID);
	m_SEInstrumentDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateSEInstrument(SEInstrument* record)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentUpdateStatement == nullptr)
	{
		m_SEInstrumentUpdateStatement = m_DBConnection->prepareStatement("update t_SEInstrument set ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, ProductClass = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, VolumeMultiple = ?, PriceTick = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForSEInstrumentRecordUpdate(m_SEInstrumentUpdateStatement, record);
	m_SEInstrumentUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::SelectSEInstrument(std::list<SEInstrument*>& records)
{
	auto start = steady_clock::now();
	if (m_SEInstrumentSelectStatement == nullptr)
	{
		m_SEInstrumentSelectStatement = m_DBConnection->prepareStatement("select * from t_SEInstrument;");
	}
	auto result = m_SEInstrumentSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateSEInstrument()
{
	auto start = steady_clock::now();
	if (m_SEInstrumentTruncateStatement == nullptr)
	{
		m_SEInstrumentTruncateStatement = m_DBConnection->prepareStatement("truncate table t_SEInstrument;");
	}
	m_SEInstrumentTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateSEInstrument Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderInsertStatement == nullptr)
	{
		m_SEOrderInsertStatement = m_DBConnection->prepareStatement("insert into t_SEOrder Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForSEOrderRecord(m_SEOrderInsertStatement, record);
	
	m_SEOrderInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEOrder Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertSEOrder(std::list<SEOrder*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEOrder Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertSEOrder Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEOrder Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertSEOrder Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEOrder RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderDeleteStatement == nullptr)
	{
		m_SEOrderDeleteStatement = m_DBConnection->prepareStatement("delete from t_SEOrder where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;");
	}
	SetStatementForSEOrderPrimaryKey(m_SEOrderDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->OrderID);
	m_SEOrderDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEOrder Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateSEOrder(SEOrder* record)
{
	auto start = steady_clock::now();
	if (m_SEOrderUpdateStatement == nullptr)
	{
		m_SEOrderUpdateStatement = m_DBConnection->prepareStatement("update t_SEOrder set BrokerID = ?, ProductClass = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;");
	}
	SetStatementForSEOrderRecordUpdate(m_SEOrderUpdateStatement, record);
	m_SEOrderUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEOrder Spend:%lldms", duration);
	}
}
void MysqlDB::SelectSEOrder(std::list<SEOrder*>& records)
{
	auto start = steady_clock::now();
	if (m_SEOrderSelectStatement == nullptr)
	{
		m_SEOrderSelectStatement = m_DBConnection->prepareStatement("select * from t_SEOrder;");
	}
	auto result = m_SEOrderSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEOrder Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateSEOrder()
{
	auto start = steady_clock::now();
	if (m_SEOrderTruncateStatement == nullptr)
	{
		m_SEOrderTruncateStatement = m_DBConnection->prepareStatement("truncate table t_SEOrder;");
	}
	m_SEOrderTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateSEOrder Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeInsertStatement == nullptr)
	{
		m_SETradeInsertStatement = m_DBConnection->prepareStatement("insert into t_SETrade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForSETradeRecord(m_SETradeInsertStatement, record);
	
	m_SETradeInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSETrade Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertSETrade(std::list<SETrade*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SETrade Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertSETrade Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SETrade Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertSETrade Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSETrade RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeDeleteStatement == nullptr)
	{
		m_SETradeDeleteStatement = m_DBConnection->prepareStatement("delete from t_SETrade where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;");
	}
	SetStatementForSETradePrimaryKey(m_SETradeDeleteStatement, record->TradingDay, record->ExchangeID, record->TradeID, record->Direction);
	m_SETradeDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSETrade Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateSETrade(SETrade* record)
{
	auto start = steady_clock::now();
	if (m_SETradeUpdateStatement == nullptr)
	{
		m_SETradeUpdateStatement = m_DBConnection->prepareStatement("update t_SETrade set BrokerID = ?, AccountID = ?, InstrumentID = ?, ProductClass = ?, OrderID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;");
	}
	SetStatementForSETradeRecordUpdate(m_SETradeUpdateStatement, record);
	m_SETradeUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSETrade Spend:%lldms", duration);
	}
}
void MysqlDB::SelectSETrade(std::list<SETrade*>& records)
{
	auto start = steady_clock::now();
	if (m_SETradeSelectStatement == nullptr)
	{
		m_SETradeSelectStatement = m_DBConnection->prepareStatement("select * from t_SETrade;");
	}
	auto result = m_SETradeSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSETrade Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateSETrade()
{
	auto start = steady_clock::now();
	if (m_SETradeTruncateStatement == nullptr)
	{
		m_SETradeTruncateStatement = m_DBConnection->prepareStatement("truncate table t_SETrade;");
	}
	m_SETradeTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateSETrade Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionInsertStatement == nullptr)
	{
		m_SEBrokerLoginSessionInsertStatement = m_DBConnection->prepareStatement("insert into t_SEBrokerLoginSession Values(?, ?, ?);");
	}
	SetStatementForSEBrokerLoginSessionRecord(m_SEBrokerLoginSessionInsertStatement, record);
	
	m_SEBrokerLoginSessionInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertSEBrokerLoginSession(std::list<SEBrokerLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_SEBrokerLoginSession Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_SEBrokerLoginSession Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertSEBrokerLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionDeleteStatement == nullptr)
	{
		m_SEBrokerLoginSessionDeleteStatement = m_DBConnection->prepareStatement("delete from t_SEBrokerLoginSession where SessionID = ?;");
	}
	SetStatementForSEBrokerLoginSessionPrimaryKey(m_SEBrokerLoginSessionDeleteStatement, record->SessionID);
	m_SEBrokerLoginSessionDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::DeleteSEBrokerLoginSessionByBrokerIDIndex(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement == nullptr)
	{
		m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement = m_DBConnection->prepareStatement("delete from t_SEBrokerLoginSession where BrokerID = ?;");
	}
	SetStatementForSEBrokerLoginSessionIndexBrokerID(m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement, record);
	m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteSEBrokerLoginSessionByBrokerIDIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateSEBrokerLoginSession(SEBrokerLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionUpdateStatement == nullptr)
	{
		m_SEBrokerLoginSessionUpdateStatement = m_DBConnection->prepareStatement("update t_SEBrokerLoginSession set BrokerID = ?, IPAddress = ? where SessionID = ?;");
	}
	SetStatementForSEBrokerLoginSessionRecordUpdate(m_SEBrokerLoginSessionUpdateStatement, record);
	m_SEBrokerLoginSessionUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::SelectSEBrokerLoginSession(std::list<SEBrokerLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionSelectStatement == nullptr)
	{
		m_SEBrokerLoginSessionSelectStatement = m_DBConnection->prepareStatement("select * from t_SEBrokerLoginSession;");
	}
	auto result = m_SEBrokerLoginSessionSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectSEBrokerLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateSEBrokerLoginSession()
{
	auto start = steady_clock::now();
	if (m_SEBrokerLoginSessionTruncateStatement == nullptr)
	{
		m_SEBrokerLoginSessionTruncateStatement = m_DBConnection->prepareStatement("truncate table t_SEBrokerLoginSession;");
	}
	m_SEBrokerLoginSessionTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateSEBrokerLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}


void MysqlDB::SetStatementForTradingDayRecord(sql::PreparedStatement* statement, TradingDay* record)
{
	statement->setInt(1, record->PK);
	statement->setString(2, record->CurrTradingDay);
	statement->setString(3, record->PreTradingDay);
}
void MysqlDB::SetStatementForTradingDayRecordUpdate(sql::PreparedStatement* statement, TradingDay* record)
{
	statement->setString(1, record->CurrTradingDay);
	statement->setString(2, record->PreTradingDay);
	statement->setInt(3, record->PK);
}
void MysqlDB::SetStatementForTradingDayPrimaryKey(sql::PreparedStatement* statement, const IntType& PK)
{
	statement->setInt(1, PK);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<TradingDay*>& records)
{
	TradingDay* record = TradingDay::Allocate();
	record->PK = result->getInt(1);
	Strcpy(record->CurrTradingDay, result->getString(2).c_str());
	Strcpy(record->PreTradingDay, result->getString(3).c_str());
	records.push_back(record);
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
void MysqlDB::SetStatementForProductRecord(sql::PreparedStatement* statement, Product* record)
{
	statement->setString(1, record->ExchangeID);
	statement->setString(2, record->ProductID);
	statement->setString(3, record->ProductName);
	statement->setInt(4, int(record->ProductClass));
	statement->setInt(5, record->VolumeMultiple);
	statement->setDouble(6, record->PriceTick);
	statement->setInt64(7, record->MaxMarketOrderVolume);
	statement->setInt64(8, record->MinMarketOrderVolume);
	statement->setInt64(9, record->MaxLimitOrderVolume);
	statement->setInt64(10, record->MinLimitOrderVolume);
	statement->setString(11, record->SessionName);
}
void MysqlDB::SetStatementForProductRecordUpdate(sql::PreparedStatement* statement, Product* record)
{
	statement->setString(1, record->ProductName);
	statement->setInt(2, int(record->ProductClass));
	statement->setInt(3, record->VolumeMultiple);
	statement->setDouble(4, record->PriceTick);
	statement->setInt64(5, record->MaxMarketOrderVolume);
	statement->setInt64(6, record->MinMarketOrderVolume);
	statement->setInt64(7, record->MaxLimitOrderVolume);
	statement->setInt64(8, record->MinLimitOrderVolume);
	statement->setString(9, record->SessionName);
	statement->setString(10, record->ExchangeID);
	statement->setString(11, record->ProductID);
}
void MysqlDB::SetStatementForProductPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID)
{
	statement->setString(1, ExchangeID);
	statement->setString(2, ProductID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Product*>& records)
{
	Product* record = Product::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->ProductID, result->getString(2).c_str());
	Strcpy(record->ProductName, result->getString(3).c_str());
	record->ProductClass = ProductClassType(result->getInt(4));
	record->VolumeMultiple = result->getInt(5);
	record->PriceTick = result->getDouble(6);
	record->MaxMarketOrderVolume = result->getInt64(7);
	record->MinMarketOrderVolume = result->getInt64(8);
	record->MaxLimitOrderVolume = result->getInt64(9);
	record->MinLimitOrderVolume = result->getInt64(10);
	Strcpy(record->SessionName, result->getString(11).c_str());
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
void MysqlDB::SetStatementForSEBrokerRecord(sql::PreparedStatement* statement, SEBroker* record)
{
	statement->setInt(1, record->BrokerID);
	statement->setString(2, record->BrokerName);
	statement->setString(3, record->Password);
}
void MysqlDB::SetStatementForSEBrokerRecordUpdate(sql::PreparedStatement* statement, SEBroker* record)
{
	statement->setString(1, record->BrokerName);
	statement->setString(2, record->Password);
	statement->setInt(3, record->BrokerID);
}
void MysqlDB::SetStatementForSEBrokerPrimaryKey(sql::PreparedStatement* statement, const BrokerIDType& BrokerID)
{
	statement->setInt(1, BrokerID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<SEBroker*>& records)
{
	SEBroker* record = SEBroker::Allocate();
	record->BrokerID = result->getInt(1);
	Strcpy(record->BrokerName, result->getString(2).c_str());
	Strcpy(record->Password, result->getString(3).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForSEInstrumentRecord(sql::PreparedStatement* statement, SEInstrument* record)
{
	statement->setString(1, record->ExchangeID);
	statement->setString(2, record->InstrumentID);
	statement->setString(3, record->ExchangeInstID);
	statement->setString(4, record->InstrumentName);
	statement->setString(5, record->ProductID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt64(7, record->MaxMarketOrderVolume);
	statement->setInt64(8, record->MinMarketOrderVolume);
	statement->setInt64(9, record->MaxLimitOrderVolume);
	statement->setInt64(10, record->MinLimitOrderVolume);
	statement->setInt(11, record->VolumeMultiple);
	statement->setDouble(12, record->PriceTick);
	statement->setDouble(13, record->UpperLimitPrice);
	statement->setDouble(14, record->LowerLimitPrice);
	statement->setString(15, record->SessionName);
}
void MysqlDB::SetStatementForSEInstrumentRecordUpdate(sql::PreparedStatement* statement, SEInstrument* record)
{
	statement->setString(1, record->ExchangeInstID);
	statement->setString(2, record->InstrumentName);
	statement->setString(3, record->ProductID);
	statement->setInt(4, int(record->ProductClass));
	statement->setInt64(5, record->MaxMarketOrderVolume);
	statement->setInt64(6, record->MinMarketOrderVolume);
	statement->setInt64(7, record->MaxLimitOrderVolume);
	statement->setInt64(8, record->MinLimitOrderVolume);
	statement->setInt(9, record->VolumeMultiple);
	statement->setDouble(10, record->PriceTick);
	statement->setDouble(11, record->UpperLimitPrice);
	statement->setDouble(12, record->LowerLimitPrice);
	statement->setString(13, record->SessionName);
	statement->setString(14, record->ExchangeID);
	statement->setString(15, record->InstrumentID);
}
void MysqlDB::SetStatementForSEInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
{
	statement->setString(1, ExchangeID);
	statement->setString(2, InstrumentID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<SEInstrument*>& records)
{
	SEInstrument* record = SEInstrument::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->InstrumentID, result->getString(2).c_str());
	Strcpy(record->ExchangeInstID, result->getString(3).c_str());
	Strcpy(record->InstrumentName, result->getString(4).c_str());
	Strcpy(record->ProductID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->MaxMarketOrderVolume = result->getInt64(7);
	record->MinMarketOrderVolume = result->getInt64(8);
	record->MaxLimitOrderVolume = result->getInt64(9);
	record->MinLimitOrderVolume = result->getInt64(10);
	record->VolumeMultiple = result->getInt(11);
	record->PriceTick = result->getDouble(12);
	record->UpperLimitPrice = result->getDouble(13);
	record->LowerLimitPrice = result->getDouble(14);
	Strcpy(record->SessionName, result->getString(15).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForSEOrderRecord(sql::PreparedStatement* statement, SEOrder* record)
{
	statement->setString(1, record->TradingDay);
	statement->setInt(2, record->BrokerID);
	statement->setString(3, record->AccountID);
	statement->setString(4, record->ExchangeID);
	statement->setString(5, record->InstrumentID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt(7, record->OrderID);
	statement->setInt(8, int(record->Direction));
	statement->setInt(9, int(record->OffsetFlag));
	statement->setInt(10, int(record->OrderPriceType));
	statement->setDouble(11, record->Price);
	statement->setInt64(12, record->Volume);
	statement->setInt64(13, record->VolumeTotal);
	statement->setInt64(14, record->VolumeTraded);
	statement->setInt(15, record->VolumeMultiple);
	statement->setInt(16, int(record->OrderStatus));
	statement->setString(17, record->OrderDate);
	statement->setString(18, record->OrderTime);
	statement->setString(19, record->CancelDate);
	statement->setString(20, record->CancelTime);
	statement->setInt64(21, record->SessionID);
	statement->setInt(22, record->ClientOrderID);
}
void MysqlDB::SetStatementForSEOrderRecordUpdate(sql::PreparedStatement* statement, SEOrder* record)
{
	statement->setInt(1, record->BrokerID);
	statement->setInt(2, int(record->ProductClass));
	statement->setInt(3, int(record->Direction));
	statement->setInt(4, int(record->OffsetFlag));
	statement->setInt(5, int(record->OrderPriceType));
	statement->setDouble(6, record->Price);
	statement->setInt64(7, record->Volume);
	statement->setInt64(8, record->VolumeTotal);
	statement->setInt64(9, record->VolumeTraded);
	statement->setInt(10, record->VolumeMultiple);
	statement->setInt(11, int(record->OrderStatus));
	statement->setString(12, record->OrderDate);
	statement->setString(13, record->OrderTime);
	statement->setString(14, record->CancelDate);
	statement->setString(15, record->CancelTime);
	statement->setInt64(16, record->SessionID);
	statement->setInt(17, record->ClientOrderID);
	statement->setString(18, record->TradingDay);
	statement->setString(19, record->AccountID);
	statement->setString(20, record->ExchangeID);
	statement->setString(21, record->InstrumentID);
	statement->setInt(22, record->OrderID);
}
void MysqlDB::SetStatementForSEOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	statement->setString(1, TradingDay);
	statement->setString(2, AccountID);
	statement->setString(3, ExchangeID);
	statement->setString(4, InstrumentID);
	statement->setInt(5, OrderID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<SEOrder*>& records)
{
	SEOrder* record = SEOrder::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	record->BrokerID = result->getInt(2);
	Strcpy(record->AccountID, result->getString(3).c_str());
	Strcpy(record->ExchangeID, result->getString(4).c_str());
	Strcpy(record->InstrumentID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->OrderID = result->getInt(7);
	record->Direction = DirectionType(result->getInt(8));
	record->OffsetFlag = OffsetFlagType(result->getInt(9));
	record->OrderPriceType = OrderPriceTypeType(result->getInt(10));
	record->Price = result->getDouble(11);
	record->Volume = result->getInt64(12);
	record->VolumeTotal = result->getInt64(13);
	record->VolumeTraded = result->getInt64(14);
	record->VolumeMultiple = result->getInt(15);
	record->OrderStatus = OrderStatusType(result->getInt(16));
	Strcpy(record->OrderDate, result->getString(17).c_str());
	Strcpy(record->OrderTime, result->getString(18).c_str());
	Strcpy(record->CancelDate, result->getString(19).c_str());
	Strcpy(record->CancelTime, result->getString(20).c_str());
	record->SessionID = result->getInt64(21);
	record->ClientOrderID = result->getInt(22);
	records.push_back(record);
}
void MysqlDB::SetStatementForSETradeRecord(sql::PreparedStatement* statement, SETrade* record)
{
	statement->setString(1, record->TradingDay);
	statement->setInt(2, record->BrokerID);
	statement->setString(3, record->AccountID);
	statement->setString(4, record->ExchangeID);
	statement->setString(5, record->InstrumentID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt(7, record->OrderID);
	statement->setString(8, record->TradeID);
	statement->setInt(9, int(record->Direction));
	statement->setInt(10, int(record->OffsetFlag));
	statement->setDouble(11, record->Price);
	statement->setInt64(12, record->Volume);
	statement->setInt(13, record->VolumeMultiple);
	statement->setDouble(14, record->TradeAmount);
	statement->setDouble(15, record->Commission);
	statement->setString(16, record->TradeDate);
	statement->setString(17, record->TradeTime);
}
void MysqlDB::SetStatementForSETradeRecordUpdate(sql::PreparedStatement* statement, SETrade* record)
{
	statement->setInt(1, record->BrokerID);
	statement->setString(2, record->AccountID);
	statement->setString(3, record->InstrumentID);
	statement->setInt(4, int(record->ProductClass));
	statement->setInt(5, record->OrderID);
	statement->setInt(6, int(record->OffsetFlag));
	statement->setDouble(7, record->Price);
	statement->setInt64(8, record->Volume);
	statement->setInt(9, record->VolumeMultiple);
	statement->setDouble(10, record->TradeAmount);
	statement->setDouble(11, record->Commission);
	statement->setString(12, record->TradeDate);
	statement->setString(13, record->TradeTime);
	statement->setString(14, record->TradingDay);
	statement->setString(15, record->ExchangeID);
	statement->setString(16, record->TradeID);
	statement->setInt(17, int(record->Direction));
}
void MysqlDB::SetStatementForSETradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	statement->setString(1, TradingDay);
	statement->setString(2, ExchangeID);
	statement->setString(3, TradeID);
	statement->setInt(4, int(Direction));
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<SETrade*>& records)
{
	SETrade* record = SETrade::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	record->BrokerID = result->getInt(2);
	Strcpy(record->AccountID, result->getString(3).c_str());
	Strcpy(record->ExchangeID, result->getString(4).c_str());
	Strcpy(record->InstrumentID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->OrderID = result->getInt(7);
	Strcpy(record->TradeID, result->getString(8).c_str());
	record->Direction = DirectionType(result->getInt(9));
	record->OffsetFlag = OffsetFlagType(result->getInt(10));
	record->Price = result->getDouble(11);
	record->Volume = result->getInt64(12);
	record->VolumeMultiple = result->getInt(13);
	record->TradeAmount = result->getDouble(14);
	record->Commission = result->getDouble(15);
	Strcpy(record->TradeDate, result->getString(16).c_str());
	Strcpy(record->TradeTime, result->getString(17).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForSEBrokerLoginSessionRecord(sql::PreparedStatement* statement, SEBrokerLoginSession* record)
{
	statement->setInt(1, record->BrokerID);
	statement->setInt64(2, record->SessionID);
	statement->setString(3, record->IPAddress);
}
void MysqlDB::SetStatementForSEBrokerLoginSessionRecordUpdate(sql::PreparedStatement* statement, SEBrokerLoginSession* record)
{
	statement->setInt(1, record->BrokerID);
	statement->setString(2, record->IPAddress);
	statement->setInt64(3, record->SessionID);
}
void MysqlDB::SetStatementForSEBrokerLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID)
{
	statement->setInt64(1, SessionID);
}
void MysqlDB::SetStatementForSEBrokerLoginSessionIndexBrokerID(sql::PreparedStatement* statement, SEBrokerLoginSession* record)
{
	statement->setInt(1, record->BrokerID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<SEBrokerLoginSession*>& records)
{
	SEBrokerLoginSession* record = SEBrokerLoginSession::Allocate();
	record->BrokerID = result->getInt(1);
	record->SessionID = result->getInt64(2);
	Strcpy(record->IPAddress, result->getString(3).c_str());
	records.push_back(record);
}

