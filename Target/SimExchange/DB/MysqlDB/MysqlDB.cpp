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

	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
	m_InstrumentUpdateStatement = nullptr;
	m_InstrumentSelectStatement = nullptr;
	m_InstrumentTruncateStatement = nullptr;

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
	if (m_OrderInsertStatement != nullptr)
	{
		m_OrderInsertStatement->close();
		m_OrderInsertStatement = nullptr;
	}
	if (m_OrderDeleteStatement != nullptr)
	{
		m_OrderDeleteStatement->close();
		m_OrderDeleteStatement = nullptr;
	}
	if (m_OrderUpdateStatement != nullptr)
	{
		m_OrderUpdateStatement->close();
		m_OrderUpdateStatement = nullptr;
	}
	if (m_OrderSelectStatement != nullptr)
	{
		m_OrderSelectStatement->close();
		m_OrderSelectStatement = nullptr;
	}
	if (m_OrderTruncateStatement != nullptr)
	{
		m_OrderTruncateStatement->close();
		m_OrderTruncateStatement = nullptr;
	}
	if (m_TradeInsertStatement != nullptr)
	{
		m_TradeInsertStatement->close();
		m_TradeInsertStatement = nullptr;
	}
	if (m_TradeDeleteStatement != nullptr)
	{
		m_TradeDeleteStatement->close();
		m_TradeDeleteStatement = nullptr;
	}
	if (m_TradeUpdateStatement != nullptr)
	{
		m_TradeUpdateStatement->close();
		m_TradeUpdateStatement = nullptr;
	}
	if (m_TradeSelectStatement != nullptr)
	{
		m_TradeSelectStatement->close();
		m_TradeSelectStatement = nullptr;
	}
	if (m_TradeTruncateStatement != nullptr)
	{
		m_TradeTruncateStatement->close();
		m_TradeTruncateStatement = nullptr;
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
}
void MysqlDB::InitDB()
{
	m_Statement->executeUpdate("Truncate Table t_TradingDay;");
	m_Statement->executeUpdate("Insert Into t_TradingDay select * from Init.t_TradingDay;");
	m_Statement->executeUpdate("Truncate Table t_Exchange;");
	m_Statement->executeUpdate("Insert Into t_Exchange select * from Init.t_Exchange;");
	m_Statement->executeUpdate("Truncate Table t_Product;");
	m_Statement->executeUpdate("Insert Into t_Product select * from Init.t_Product;");
	m_Statement->executeUpdate("Truncate Table t_Instrument;");
	m_Statement->executeUpdate("Insert Into t_Instrument select * from Init.t_Instrument;");
	m_Statement->executeUpdate("Truncate Table t_Order;");
	m_Statement->executeUpdate("Insert Into t_Order select * from Init.t_Order;");
	m_Statement->executeUpdate("Truncate Table t_Trade;");
	m_Statement->executeUpdate("Insert Into t_Trade select * from Init.t_Trade;");
	m_Statement->executeUpdate("Truncate Table t_DepthMarketData;");
	m_Statement->executeUpdate("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
}
void MysqlDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateOrder();
	TruncateTrade();
	TruncateDepthMarketData();
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
void MysqlDB::InsertOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderInsertStatement == nullptr)
	{
		m_OrderInsertStatement = m_DBConnection->prepareStatement("insert into t_Order Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForOrderRecord(m_OrderInsertStatement, record);
	
	m_OrderInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertOrder Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertOrder(std::list<Order*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Order Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertOrder Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Order Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertOrder Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertOrder RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderDeleteStatement == nullptr)
	{
		m_OrderDeleteStatement = m_DBConnection->prepareStatement("delete from t_Order where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;");
	}
	SetStatementForOrderPrimaryKey(m_OrderDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->OrderID);
	m_OrderDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteOrder Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderUpdateStatement == nullptr)
	{
		m_OrderUpdateStatement = m_DBConnection->prepareStatement("update t_Order set AccountType = ?, ProductClass = ?, OrderSysID = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ?, RequestID = ?, OfferID = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, RebuildMark = ?, IsForceClose = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;");
	}
	SetStatementForOrderRecordUpdate(m_OrderUpdateStatement, record);
	m_OrderUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder Spend:%lldms", duration);
	}
}
void MysqlDB::SelectOrder(std::list<Order*>& records)
{
	auto start = steady_clock::now();
	if (m_OrderSelectStatement == nullptr)
	{
		m_OrderSelectStatement = m_DBConnection->prepareStatement("select * from t_Order;");
	}
	auto result = m_OrderSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectOrder Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateOrder()
{
	auto start = steady_clock::now();
	if (m_OrderTruncateStatement == nullptr)
	{
		m_OrderTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Order;");
	}
	m_OrderTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateOrder Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeInsertStatement == nullptr)
	{
		m_TradeInsertStatement = m_DBConnection->prepareStatement("insert into t_Trade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForTradeRecord(m_TradeInsertStatement, record);
	
	m_TradeInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertTrade Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertTrade(std::list<Trade*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Trade Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertTrade Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Trade Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertTrade Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertTrade RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeDeleteStatement == nullptr)
	{
		m_TradeDeleteStatement = m_DBConnection->prepareStatement("delete from t_Trade where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;");
	}
	SetStatementForTradePrimaryKey(m_TradeDeleteStatement, record->TradingDay, record->ExchangeID, record->TradeID, record->Direction);
	m_TradeDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTrade Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateTrade(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeUpdateStatement == nullptr)
	{
		m_TradeUpdateStatement = m_DBConnection->prepareStatement("update t_Trade set AccountID = ?, AccountType = ?, InstrumentID = ?, ProductClass = ?, OrderID = ?, OrderSysID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;");
	}
	SetStatementForTradeRecordUpdate(m_TradeUpdateStatement, record);
	m_TradeUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade Spend:%lldms", duration);
	}
}
void MysqlDB::SelectTrade(std::list<Trade*>& records)
{
	auto start = steady_clock::now();
	if (m_TradeSelectStatement == nullptr)
	{
		m_TradeSelectStatement = m_DBConnection->prepareStatement("select * from t_Trade;");
	}
	auto result = m_TradeSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectTrade Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateTrade()
{
	auto start = steady_clock::now();
	if (m_TradeTruncateStatement == nullptr)
	{
		m_TradeTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Trade;");
	}
	m_TradeTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateTrade Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void MysqlDB::SetStatementForOrderRecord(sql::PreparedStatement* statement, Order* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setInt(3, int(record->AccountType));
	statement->setString(4, record->ExchangeID);
	statement->setString(5, record->InstrumentID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt(7, record->OrderID);
	statement->setString(8, record->OrderSysID);
	statement->setInt(9, int(record->Direction));
	statement->setInt(10, int(record->OffsetFlag));
	statement->setInt(11, int(record->OrderPriceType));
	statement->setDouble(12, record->Price);
	statement->setInt64(13, record->Volume);
	statement->setInt64(14, record->VolumeTotal);
	statement->setInt64(15, record->VolumeTraded);
	statement->setInt(16, record->VolumeMultiple);
	statement->setInt(17, int(record->OrderStatus));
	statement->setString(18, record->OrderDate);
	statement->setString(19, record->OrderTime);
	statement->setString(20, record->CancelDate);
	statement->setString(21, record->CancelTime);
	statement->setInt64(22, record->SessionID);
	statement->setInt(23, record->ClientOrderID);
	statement->setInt(24, record->RequestID);
	statement->setInt(25, record->OfferID);
	statement->setInt(26, record->TradeGroupID);
	statement->setInt(27, record->RiskGroupID);
	statement->setInt(28, record->CommissionGroupID);
	statement->setDouble(29, record->FrozenCash);
	statement->setDouble(30, record->FrozenMargin);
	statement->setDouble(31, record->FrozenCommission);
	statement->setBoolean(32, record->RebuildMark);
	statement->setBoolean(33, record->IsForceClose);
}
void MysqlDB::SetStatementForOrderRecordUpdate(sql::PreparedStatement* statement, Order* record)
{
	statement->setInt(1, int(record->AccountType));
	statement->setInt(2, int(record->ProductClass));
	statement->setString(3, record->OrderSysID);
	statement->setInt(4, int(record->Direction));
	statement->setInt(5, int(record->OffsetFlag));
	statement->setInt(6, int(record->OrderPriceType));
	statement->setDouble(7, record->Price);
	statement->setInt64(8, record->Volume);
	statement->setInt64(9, record->VolumeTotal);
	statement->setInt64(10, record->VolumeTraded);
	statement->setInt(11, record->VolumeMultiple);
	statement->setInt(12, int(record->OrderStatus));
	statement->setString(13, record->OrderDate);
	statement->setString(14, record->OrderTime);
	statement->setString(15, record->CancelDate);
	statement->setString(16, record->CancelTime);
	statement->setInt64(17, record->SessionID);
	statement->setInt(18, record->ClientOrderID);
	statement->setInt(19, record->RequestID);
	statement->setInt(20, record->OfferID);
	statement->setInt(21, record->TradeGroupID);
	statement->setInt(22, record->RiskGroupID);
	statement->setInt(23, record->CommissionGroupID);
	statement->setDouble(24, record->FrozenCash);
	statement->setDouble(25, record->FrozenMargin);
	statement->setDouble(26, record->FrozenCommission);
	statement->setBoolean(27, record->RebuildMark);
	statement->setBoolean(28, record->IsForceClose);
	statement->setString(29, record->TradingDay);
	statement->setString(30, record->AccountID);
	statement->setString(31, record->ExchangeID);
	statement->setString(32, record->InstrumentID);
	statement->setInt(33, record->OrderID);
}
void MysqlDB::SetStatementForOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	statement->setString(1, TradingDay);
	statement->setString(2, AccountID);
	statement->setString(3, ExchangeID);
	statement->setString(4, InstrumentID);
	statement->setInt(5, OrderID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Order*>& records)
{
	Order* record = Order::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	record->AccountType = AccountTypeType(result->getInt(3));
	Strcpy(record->ExchangeID, result->getString(4).c_str());
	Strcpy(record->InstrumentID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->OrderID = result->getInt(7);
	Strcpy(record->OrderSysID, result->getString(8).c_str());
	record->Direction = DirectionType(result->getInt(9));
	record->OffsetFlag = OffsetFlagType(result->getInt(10));
	record->OrderPriceType = OrderPriceTypeType(result->getInt(11));
	record->Price = result->getDouble(12);
	record->Volume = result->getInt64(13);
	record->VolumeTotal = result->getInt64(14);
	record->VolumeTraded = result->getInt64(15);
	record->VolumeMultiple = result->getInt(16);
	record->OrderStatus = OrderStatusType(result->getInt(17));
	Strcpy(record->OrderDate, result->getString(18).c_str());
	Strcpy(record->OrderTime, result->getString(19).c_str());
	Strcpy(record->CancelDate, result->getString(20).c_str());
	Strcpy(record->CancelTime, result->getString(21).c_str());
	record->SessionID = result->getInt64(22);
	record->ClientOrderID = result->getInt(23);
	record->RequestID = result->getInt(24);
	record->OfferID = result->getInt(25);
	record->TradeGroupID = result->getInt(26);
	record->RiskGroupID = result->getInt(27);
	record->CommissionGroupID = result->getInt(28);
	record->FrozenCash = result->getDouble(29);
	record->FrozenMargin = result->getDouble(30);
	record->FrozenCommission = result->getDouble(31);
	record->RebuildMark = result->getBoolean(32);
	record->IsForceClose = result->getBoolean(33);
	records.push_back(record);
}
void MysqlDB::SetStatementForTradeRecord(sql::PreparedStatement* statement, Trade* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setInt(3, int(record->AccountType));
	statement->setString(4, record->ExchangeID);
	statement->setString(5, record->InstrumentID);
	statement->setInt(6, int(record->ProductClass));
	statement->setInt(7, record->OrderID);
	statement->setString(8, record->OrderSysID);
	statement->setString(9, record->TradeID);
	statement->setInt(10, int(record->Direction));
	statement->setInt(11, int(record->OffsetFlag));
	statement->setDouble(12, record->Price);
	statement->setInt64(13, record->Volume);
	statement->setInt(14, record->VolumeMultiple);
	statement->setDouble(15, record->TradeAmount);
	statement->setDouble(16, record->Commission);
	statement->setString(17, record->TradeDate);
	statement->setString(18, record->TradeTime);
}
void MysqlDB::SetStatementForTradeRecordUpdate(sql::PreparedStatement* statement, Trade* record)
{
	statement->setString(1, record->AccountID);
	statement->setInt(2, int(record->AccountType));
	statement->setString(3, record->InstrumentID);
	statement->setInt(4, int(record->ProductClass));
	statement->setInt(5, record->OrderID);
	statement->setString(6, record->OrderSysID);
	statement->setInt(7, int(record->OffsetFlag));
	statement->setDouble(8, record->Price);
	statement->setInt64(9, record->Volume);
	statement->setInt(10, record->VolumeMultiple);
	statement->setDouble(11, record->TradeAmount);
	statement->setDouble(12, record->Commission);
	statement->setString(13, record->TradeDate);
	statement->setString(14, record->TradeTime);
	statement->setString(15, record->TradingDay);
	statement->setString(16, record->ExchangeID);
	statement->setString(17, record->TradeID);
	statement->setInt(18, int(record->Direction));
}
void MysqlDB::SetStatementForTradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	statement->setString(1, TradingDay);
	statement->setString(2, ExchangeID);
	statement->setString(3, TradeID);
	statement->setInt(4, int(Direction));
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Trade*>& records)
{
	Trade* record = Trade::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	record->AccountType = AccountTypeType(result->getInt(3));
	Strcpy(record->ExchangeID, result->getString(4).c_str());
	Strcpy(record->InstrumentID, result->getString(5).c_str());
	record->ProductClass = ProductClassType(result->getInt(6));
	record->OrderID = result->getInt(7);
	Strcpy(record->OrderSysID, result->getString(8).c_str());
	Strcpy(record->TradeID, result->getString(9).c_str());
	record->Direction = DirectionType(result->getInt(10));
	record->OffsetFlag = OffsetFlagType(result->getInt(11));
	record->Price = result->getDouble(12);
	record->Volume = result->getInt64(13);
	record->VolumeMultiple = result->getInt(14);
	record->TradeAmount = result->getDouble(15);
	record->Commission = result->getDouble(16);
	Strcpy(record->TradeDate, result->getString(17).c_str());
	Strcpy(record->TradeTime, result->getString(18).c_str());
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

