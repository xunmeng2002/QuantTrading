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
	if (m_PrimaryAccountInsertStatement != nullptr)
	{
		m_PrimaryAccountInsertStatement->close();
		m_PrimaryAccountInsertStatement = nullptr;
	}
	if (m_PrimaryAccountDeleteStatement != nullptr)
	{
		m_PrimaryAccountDeleteStatement->close();
		m_PrimaryAccountDeleteStatement = nullptr;
	}
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement != nullptr)
	{
		m_PrimaryAccountDeleteByOfferIDIndexStatement->close();
		m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	}
	if (m_PrimaryAccountUpdateStatement != nullptr)
	{
		m_PrimaryAccountUpdateStatement->close();
		m_PrimaryAccountUpdateStatement = nullptr;
	}
	if (m_PrimaryAccountSelectStatement != nullptr)
	{
		m_PrimaryAccountSelectStatement->close();
		m_PrimaryAccountSelectStatement = nullptr;
	}
	if (m_PrimaryAccountTruncateStatement != nullptr)
	{
		m_PrimaryAccountTruncateStatement->close();
		m_PrimaryAccountTruncateStatement = nullptr;
	}
	if (m_AccountInsertStatement != nullptr)
	{
		m_AccountInsertStatement->close();
		m_AccountInsertStatement = nullptr;
	}
	if (m_AccountDeleteStatement != nullptr)
	{
		m_AccountDeleteStatement->close();
		m_AccountDeleteStatement = nullptr;
	}
	if (m_AccountUpdateStatement != nullptr)
	{
		m_AccountUpdateStatement->close();
		m_AccountUpdateStatement = nullptr;
	}
	if (m_AccountSelectStatement != nullptr)
	{
		m_AccountSelectStatement->close();
		m_AccountSelectStatement = nullptr;
	}
	if (m_AccountTruncateStatement != nullptr)
	{
		m_AccountTruncateStatement->close();
		m_AccountTruncateStatement = nullptr;
	}
	if (m_CapitalInsertStatement != nullptr)
	{
		m_CapitalInsertStatement->close();
		m_CapitalInsertStatement = nullptr;
	}
	if (m_CapitalDeleteStatement != nullptr)
	{
		m_CapitalDeleteStatement->close();
		m_CapitalDeleteStatement = nullptr;
	}
	if (m_CapitalUpdateStatement != nullptr)
	{
		m_CapitalUpdateStatement->close();
		m_CapitalUpdateStatement = nullptr;
	}
	if (m_CapitalSelectStatement != nullptr)
	{
		m_CapitalSelectStatement->close();
		m_CapitalSelectStatement = nullptr;
	}
	if (m_CapitalTruncateStatement != nullptr)
	{
		m_CapitalTruncateStatement->close();
		m_CapitalTruncateStatement = nullptr;
	}
	if (m_PositionInsertStatement != nullptr)
	{
		m_PositionInsertStatement->close();
		m_PositionInsertStatement = nullptr;
	}
	if (m_PositionDeleteStatement != nullptr)
	{
		m_PositionDeleteStatement->close();
		m_PositionDeleteStatement = nullptr;
	}
	if (m_PositionDeleteByAccountIndexStatement != nullptr)
	{
		m_PositionDeleteByAccountIndexStatement->close();
		m_PositionDeleteByAccountIndexStatement = nullptr;
	}
	if (m_PositionUpdateStatement != nullptr)
	{
		m_PositionUpdateStatement->close();
		m_PositionUpdateStatement = nullptr;
	}
	if (m_PositionSelectStatement != nullptr)
	{
		m_PositionSelectStatement->close();
		m_PositionSelectStatement = nullptr;
	}
	if (m_PositionTruncateStatement != nullptr)
	{
		m_PositionTruncateStatement->close();
		m_PositionTruncateStatement = nullptr;
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
	m_Statement->executeUpdate("Truncate Table t_PrimaryAccount;");
	m_Statement->executeUpdate("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	m_Statement->executeUpdate("Truncate Table t_Account;");
	m_Statement->executeUpdate("Insert Into t_Account select * from Init.t_Account;");
	m_Statement->executeUpdate("Truncate Table t_Capital;");
	m_Statement->executeUpdate("Insert Into t_Capital select * from Init.t_Capital;");
	m_Statement->executeUpdate("Truncate Table t_Position;");
	m_Statement->executeUpdate("Insert Into t_Position select * from Init.t_Position;");
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
	TruncatePrimaryAccount();
	TruncateAccount();
	TruncateCapital();
	TruncatePosition();
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
void MysqlDB::SelectTradingDay(std::vector<TradingDay*>& records)
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
void MysqlDB::SelectExchange(std::vector<Exchange*>& records)
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
		m_ProductUpdateStatement = m_DBConnection->prepareStatement("update t_Product set ProductName = ?, SecurityType = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and ProductID = ?;");
	}
	SetStatementForProductRecordUpdate(m_ProductUpdateStatement, record);
	m_ProductUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateProduct Spend:%lldms", duration);
	}
}
void MysqlDB::SelectProduct(std::vector<Product*>& records)
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
		m_InstrumentUpdateStatement = m_DBConnection->prepareStatement("update t_Instrument set TradingDay = ?, ExchangeInstID = ?, InstrumentName = ?, ProductID = ?, SecurityType = ?, SecurityDetailType = ?, VolumeMultiple = ?, PriceTick = ?, MaxMarketOrderVolume = ?, MinMarketOrderVolume = ?, MaxLimitOrderVolume = ?, MinLimitOrderVolume = ?, SessionName = ? where ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForInstrumentRecordUpdate(m_InstrumentUpdateStatement, record);
	m_InstrumentUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateInstrument Spend:%lldms", duration);
	}
}
void MysqlDB::SelectInstrument(std::vector<Instrument*>& records)
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
void MysqlDB::InsertPrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountInsertStatement == nullptr)
	{
		m_PrimaryAccountInsertStatement = m_DBConnection->prepareStatement("insert into t_PrimaryAccount Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForPrimaryAccountRecord(m_PrimaryAccountInsertStatement, record);
	
	m_PrimaryAccountInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertPrimaryAccount Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertPrimaryAccount(std::list<PrimaryAccount*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_PrimaryAccount Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_PrimaryAccount Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertPrimaryAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeletePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteStatement == nullptr)
	{
		m_PrimaryAccountDeleteStatement = m_DBConnection->prepareStatement("delete from t_PrimaryAccount where PrimaryAccountID = ?;");
	}
	SetStatementForPrimaryAccountPrimaryKey(m_PrimaryAccountDeleteStatement, record->PrimaryAccountID);
	m_PrimaryAccountDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccount Spend:%lldms", duration);
	}
}
void MysqlDB::DeletePrimaryAccountByOfferIDIndex(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDeleteByOfferIDIndexStatement == nullptr)
	{
		m_PrimaryAccountDeleteByOfferIDIndexStatement = m_DBConnection->prepareStatement("delete from t_PrimaryAccount where OfferID = ?;");
	}
	SetStatementForPrimaryAccountIndexOfferID(m_PrimaryAccountDeleteByOfferIDIndexStatement, record);
	m_PrimaryAccountDeleteByOfferIDIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePrimaryAccountByOfferIDIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdatePrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountUpdateStatement == nullptr)
	{
		m_PrimaryAccountUpdateStatement = m_DBConnection->prepareStatement("update t_PrimaryAccount set TradingDay = ?, PrimaryAccountName = ?, AccountClass = ?, BrokerPassword = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;");
	}
	SetStatementForPrimaryAccountRecordUpdate(m_PrimaryAccountUpdateStatement, record);
	m_PrimaryAccountUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount Spend:%lldms", duration);
	}
}
void MysqlDB::SelectPrimaryAccount(std::vector<PrimaryAccount*>& records)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountSelectStatement == nullptr)
	{
		m_PrimaryAccountSelectStatement = m_DBConnection->prepareStatement("select * from t_PrimaryAccount;");
	}
	auto result = m_PrimaryAccountSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPrimaryAccount Spend:%lldms", duration);
	}
}
void MysqlDB::TruncatePrimaryAccount()
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountTruncateStatement == nullptr)
	{
		m_PrimaryAccountTruncateStatement = m_DBConnection->prepareStatement("truncate table t_PrimaryAccount;");
	}
	m_PrimaryAccountTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncatePrimaryAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountInsertStatement == nullptr)
	{
		m_AccountInsertStatement = m_DBConnection->prepareStatement("insert into t_Account Values(?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForAccountRecord(m_AccountInsertStatement, record);
	
	m_AccountInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertAccount Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertAccount(std::list<Account*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Account Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertAccount Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Account Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertAccount Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertAccount RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountDeleteStatement == nullptr)
	{
		m_AccountDeleteStatement = m_DBConnection->prepareStatement("delete from t_Account where AccountID = ?;");
	}
	SetStatementForAccountPrimaryKey(m_AccountDeleteStatement, record->AccountID);
	m_AccountDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccount Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountUpdateStatement == nullptr)
	{
		m_AccountUpdateStatement = m_DBConnection->prepareStatement("update t_Account set TradingDay = ?, AccountName = ?, AccountType = ?, AccountStatus = ?, Password = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ? where AccountID = ?;");
	}
	SetStatementForAccountRecordUpdate(m_AccountUpdateStatement, record);
	m_AccountUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount Spend:%lldms", duration);
	}
}
void MysqlDB::SelectAccount(std::vector<Account*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountSelectStatement == nullptr)
	{
		m_AccountSelectStatement = m_DBConnection->prepareStatement("select * from t_Account;");
	}
	auto result = m_AccountSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccount Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateAccount()
{
	auto start = steady_clock::now();
	if (m_AccountTruncateStatement == nullptr)
	{
		m_AccountTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Account;");
	}
	m_AccountTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateAccount Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalInsertStatement == nullptr)
	{
		m_CapitalInsertStatement = m_DBConnection->prepareStatement("insert into t_Capital Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForCapitalRecord(m_CapitalInsertStatement, record);
	
	m_CapitalInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertCapital Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertCapital(std::list<Capital*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Capital Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertCapital Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Capital Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertCapital Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertCapital RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalDeleteStatement == nullptr)
	{
		m_CapitalDeleteStatement = m_DBConnection->prepareStatement("delete from t_Capital where AccountID = ?;");
	}
	SetStatementForCapitalPrimaryKey(m_CapitalDeleteStatement, record->AccountID);
	m_CapitalDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteCapital Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalUpdateStatement == nullptr)
	{
		m_CapitalUpdateStatement = m_DBConnection->prepareStatement("update t_Capital set TradingDay = ?, AccountType = ?, Asset = ?, PreAsset = ?, CashAsset = ?, PreCashAsset = ?, Available = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, StampTax = ?, TransferFee = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, MarketValue = ?, TotalProfit = ?, TodayProfit = ?, Deposit = ?, Withdraw = ? where AccountID = ?;");
	}
	SetStatementForCapitalRecordUpdate(m_CapitalUpdateStatement, record);
	m_CapitalUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateCapital Spend:%lldms", duration);
	}
}
void MysqlDB::SelectCapital(std::vector<Capital*>& records)
{
	auto start = steady_clock::now();
	if (m_CapitalSelectStatement == nullptr)
	{
		m_CapitalSelectStatement = m_DBConnection->prepareStatement("select * from t_Capital;");
	}
	auto result = m_CapitalSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectCapital Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateCapital()
{
	auto start = steady_clock::now();
	if (m_CapitalTruncateStatement == nullptr)
	{
		m_CapitalTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Capital;");
	}
	m_CapitalTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateCapital Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertPosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionInsertStatement == nullptr)
	{
		m_PositionInsertStatement = m_DBConnection->prepareStatement("insert into t_Position Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	}
	SetStatementForPositionRecord(m_PositionInsertStatement, record);
	
	m_PositionInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertPosition Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertPosition(std::list<Position*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_Position Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertPosition Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_Position Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertPosition Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertPosition RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeletePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteStatement == nullptr)
	{
		m_PositionDeleteStatement = m_DBConnection->prepareStatement("delete from t_Position where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;");
	}
	SetStatementForPositionPrimaryKey(m_PositionDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->PosiDirection);
	m_PositionDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePosition Spend:%lldms", duration);
	}
}
void MysqlDB::DeletePositionByAccountIndex(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteByAccountIndexStatement == nullptr)
	{
		m_PositionDeleteByAccountIndexStatement = m_DBConnection->prepareStatement("delete from t_Position where TradingDay = ? and AccountID = ?;");
	}
	SetStatementForPositionIndexAccount(m_PositionDeleteByAccountIndexStatement, record);
	m_PositionDeleteByAccountIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByAccountIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdatePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionUpdateStatement == nullptr)
	{
		m_PositionUpdateStatement = m_DBConnection->prepareStatement("update t_Position set AccountType = ?, SecurityType = ?, TotalPosition = ?, PositionFrozen = ?, TodayPosition = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, StampTax = ?, TransferFee = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, MarketValue = ?, VolumeMultiple = ?, CloseProfit = ?, CloseProfitFloat = ?, PositionProfit = ?, PositionProfitFloat = ?, LastPrice = ?, PrePrice = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;");
	}
	SetStatementForPositionRecordUpdate(m_PositionUpdateStatement, record);
	m_PositionUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePosition Spend:%lldms", duration);
	}
}
void MysqlDB::SelectPosition(std::vector<Position*>& records)
{
	auto start = steady_clock::now();
	if (m_PositionSelectStatement == nullptr)
	{
		m_PositionSelectStatement = m_DBConnection->prepareStatement("select * from t_Position;");
	}
	auto result = m_PositionSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPosition Spend:%lldms", duration);
	}
}
void MysqlDB::TruncatePosition()
{
	auto start = steady_clock::now();
	if (m_PositionTruncateStatement == nullptr)
	{
		m_PositionTruncateStatement = m_DBConnection->prepareStatement("truncate table t_Position;");
	}
	m_PositionTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncatePosition Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void MysqlDB::InsertOrder(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderInsertStatement == nullptr)
	{
		m_OrderInsertStatement = m_DBConnection->prepareStatement("insert into t_Order Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
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
		m_OrderUpdateStatement = m_DBConnection->prepareStatement("update t_Order set PrimaryAccountID = ?, AccountType = ?, SecurityType = ?, OrderSysID = ?, Direction = ?, OffsetFlag = ?, OrderPriceType = ?, Price = ?, Volume = ?, VolumeTotal = ?, VolumeTraded = ?, VolumeMultiple = ?, OrderStatus = ?, OrderDate = ?, OrderTime = ?, CancelDate = ?, CancelTime = ?, SessionID = ?, ClientOrderID = ?, RequestID = ?, OfferID = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, FrozenStampTax = ?, FrozenTransferFee = ?, RebuildMark = ?, IsForceClose = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and OrderID = ?;");
	}
	SetStatementForOrderRecordUpdate(m_OrderUpdateStatement, record);
	m_OrderUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateOrder Spend:%lldms", duration);
	}
}
void MysqlDB::SelectOrder(std::vector<Order*>& records)
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
		m_TradeInsertStatement = m_DBConnection->prepareStatement("insert into t_Trade Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
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
		m_TradeUpdateStatement = m_DBConnection->prepareStatement("update t_Trade set AccountID = ?, PrimaryAccountID = ?, AccountType = ?, InstrumentID = ?, SecurityType = ?, OrderID = ?, OrderSysID = ?, OffsetFlag = ?, Price = ?, Volume = ?, VolumeMultiple = ?, TradeAmount = ?, Commission = ?, StampTax = ?, TransferFee = ?, TradeDate = ?, TradeTime = ? where TradingDay = ? and ExchangeID = ? and TradeID = ? and Direction = ?;");
	}
	SetStatementForTradeRecordUpdate(m_TradeUpdateStatement, record);
	m_TradeUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateTrade Spend:%lldms", duration);
	}
}
void MysqlDB::SelectTrade(std::vector<Trade*>& records)
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
		m_DepthMarketDataUpdateStatement = m_DBConnection->prepareStatement("update t_DepthMarketData set LastPrice = ?, PreSettlementPrice = ?, PreClosePrice = ?, PreOpenInterest = ?, OpenPrice = ?, HighestPrice = ?, LowestPrice = ?, ClosePrice = ?, CurrVolume = ?, Volume = ?, CurrTurnover = ?, Turnover = ?, OpenInterest = ?, SettlementPrice = ?, UpperLimitPrice = ?, LowerLimitPrice = ?, AveragePrice = ?, UpdateTs = ?, AskPrice1 = ?, AskPrice2 = ?, AskPrice3 = ?, AskPrice4 = ?, AskPrice5 = ?, AskPrice6 = ?, AskPrice7 = ?, AskPrice8 = ?, AskPrice9 = ?, AskPrice10 = ?, AskVolume1 = ?, AskVolume2 = ?, AskVolume3 = ?, AskVolume4 = ?, AskVolume5 = ?, AskVolume6 = ?, AskVolume7 = ?, AskVolume8 = ?, AskVolume9 = ?, AskVolume10 = ?, BidPrice1 = ?, BidPrice2 = ?, BidPrice3 = ?, BidPrice4 = ?, BidPrice5 = ?, BidPrice6 = ?, BidPrice7 = ?, BidPrice8 = ?, BidPrice9 = ?, BidPrice10 = ?, BidVolume1 = ?, BidVolume2 = ?, BidVolume3 = ?, BidVolume4 = ?, BidVolume5 = ?, BidVolume6 = ?, BidVolume7 = ?, BidVolume8 = ?, BidVolume9 = ?, BidVolume10 = ? where TradingDay = ? and ExchangeID = ? and InstrumentID = ?;");
	}
	SetStatementForDepthMarketDataRecordUpdate(m_DepthMarketDataUpdateStatement, record);
	m_DepthMarketDataUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateDepthMarketData Spend:%lldms", duration);
	}
}
void MysqlDB::SelectDepthMarketData(std::vector<DepthMarketData*>& records)
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
	statement->setString(1, record->PK);
	statement->setString(2, record->CurrTradingDay);
	statement->setString(3, record->PreTradingDay);
}
void MysqlDB::SetStatementForTradingDayRecordUpdate(sql::PreparedStatement* statement, TradingDay* record)
{
	statement->setString(1, record->CurrTradingDay);
	statement->setString(2, record->PreTradingDay);
	statement->setString(3, record->PK);
}
void MysqlDB::SetStatementForTradingDayPrimaryKey(sql::PreparedStatement* statement, const UserIDType& PK)
{
	statement->setString(1, PK);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<TradingDay*>& records)
{
	TradingDay* record = TradingDay::Allocate();
	Strcpy(record->PK, result->getString(1).c_str());
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
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Exchange*>& records)
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
	statement->setInt(4, int(record->SecurityType));
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
	statement->setInt(2, int(record->SecurityType));
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
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Product*>& records)
{
	Product* record = Product::Allocate();
	Strcpy(record->ExchangeID, result->getString(1).c_str());
	Strcpy(record->ProductID, result->getString(2).c_str());
	Strcpy(record->ProductName, result->getString(3).c_str());
	record->SecurityType = SecurityTypeType(result->getInt(4));
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
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->ExchangeID);
	statement->setString(3, record->InstrumentID);
	statement->setString(4, record->ExchangeInstID);
	statement->setString(5, record->InstrumentName);
	statement->setString(6, record->ProductID);
	statement->setInt(7, int(record->SecurityType));
	statement->setInt(8, int(record->SecurityDetailType));
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
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->ExchangeInstID);
	statement->setString(3, record->InstrumentName);
	statement->setString(4, record->ProductID);
	statement->setInt(5, int(record->SecurityType));
	statement->setInt(6, int(record->SecurityDetailType));
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
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Instrument*>& records)
{
	Instrument* record = Instrument::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->ExchangeID, result->getString(2).c_str());
	Strcpy(record->InstrumentID, result->getString(3).c_str());
	Strcpy(record->ExchangeInstID, result->getString(4).c_str());
	Strcpy(record->InstrumentName, result->getString(5).c_str());
	Strcpy(record->ProductID, result->getString(6).c_str());
	record->SecurityType = SecurityTypeType(result->getInt(7));
	record->SecurityDetailType = SecurityDetailTypeType(result->getInt(8));
	record->VolumeMultiple = result->getInt(9);
	record->PriceTick = result->getDouble(10);
	record->MaxMarketOrderVolume = result->getInt64(11);
	record->MinMarketOrderVolume = result->getInt64(12);
	record->MaxLimitOrderVolume = result->getInt64(13);
	record->MinLimitOrderVolume = result->getInt64(14);
	Strcpy(record->SessionName, result->getString(15).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForPrimaryAccountRecord(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->PrimaryAccountID);
	statement->setString(3, record->PrimaryAccountName);
	statement->setInt(4, int(record->AccountClass));
	statement->setString(5, record->BrokerPassword);
	statement->setInt(6, record->OfferID);
	statement->setBoolean(7, record->IsAllowLogin);
	statement->setBoolean(8, record->IsSimulateAccount);
	statement->setInt(9, int(record->LoginStatus));
	statement->setInt(10, int(record->InitStatus));
}
void MysqlDB::SetStatementForPrimaryAccountRecordUpdate(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->PrimaryAccountName);
	statement->setInt(3, int(record->AccountClass));
	statement->setString(4, record->BrokerPassword);
	statement->setInt(5, record->OfferID);
	statement->setBoolean(6, record->IsAllowLogin);
	statement->setBoolean(7, record->IsSimulateAccount);
	statement->setInt(8, int(record->LoginStatus));
	statement->setInt(9, int(record->InitStatus));
	statement->setString(10, record->PrimaryAccountID);
}
void MysqlDB::SetStatementForPrimaryAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& PrimaryAccountID)
{
	statement->setString(1, PrimaryAccountID);
}
void MysqlDB::SetStatementForPrimaryAccountIndexOfferID(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setInt(1, record->OfferID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<PrimaryAccount*>& records)
{
	PrimaryAccount* record = PrimaryAccount::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->PrimaryAccountID, result->getString(2).c_str());
	Strcpy(record->PrimaryAccountName, result->getString(3).c_str());
	record->AccountClass = AccountClassType(result->getInt(4));
	Strcpy(record->BrokerPassword, result->getString(5).c_str());
	record->OfferID = result->getInt(6);
	record->IsAllowLogin = result->getBoolean(7);
	record->IsSimulateAccount = result->getBoolean(8);
	record->LoginStatus = LoginStatusType(result->getInt(9));
	record->InitStatus = InitStatusType(result->getInt(10));
	records.push_back(record);
}
void MysqlDB::SetStatementForAccountRecord(sql::PreparedStatement* statement, Account* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setString(3, record->AccountName);
	statement->setInt(4, int(record->AccountType));
	statement->setInt(5, int(record->AccountStatus));
	statement->setString(6, record->Password);
	statement->setInt(7, record->TradeGroupID);
	statement->setInt(8, record->RiskGroupID);
	statement->setInt(9, record->CommissionGroupID);
}
void MysqlDB::SetStatementForAccountRecordUpdate(sql::PreparedStatement* statement, Account* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountName);
	statement->setInt(3, int(record->AccountType));
	statement->setInt(4, int(record->AccountStatus));
	statement->setString(5, record->Password);
	statement->setInt(6, record->TradeGroupID);
	statement->setInt(7, record->RiskGroupID);
	statement->setInt(8, record->CommissionGroupID);
	statement->setString(9, record->AccountID);
}
void MysqlDB::SetStatementForAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID)
{
	statement->setString(1, AccountID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Account*>& records)
{
	Account* record = Account::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	Strcpy(record->AccountName, result->getString(3).c_str());
	record->AccountType = AccountTypeType(result->getInt(4));
	record->AccountStatus = AccountStatusType(result->getInt(5));
	Strcpy(record->Password, result->getString(6).c_str());
	record->TradeGroupID = result->getInt(7);
	record->RiskGroupID = result->getInt(8);
	record->CommissionGroupID = result->getInt(9);
	records.push_back(record);
}
void MysqlDB::SetStatementForCapitalRecord(sql::PreparedStatement* statement, Capital* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setInt(3, int(record->AccountType));
	statement->setDouble(4, record->Asset);
	statement->setDouble(5, record->PreAsset);
	statement->setDouble(6, record->CashAsset);
	statement->setDouble(7, record->PreCashAsset);
	statement->setDouble(8, record->Available);
	statement->setDouble(9, record->CashIn);
	statement->setDouble(10, record->CashOut);
	statement->setDouble(11, record->Margin);
	statement->setDouble(12, record->Commission);
	statement->setDouble(13, record->StampTax);
	statement->setDouble(14, record->TransferFee);
	statement->setDouble(15, record->FrozenCash);
	statement->setDouble(16, record->FrozenMargin);
	statement->setDouble(17, record->FrozenCommission);
	statement->setDouble(18, record->FrozenStampTax);
	statement->setDouble(19, record->FrozenTransferFee);
	statement->setDouble(20, record->MarketValue);
	statement->setDouble(21, record->TotalProfit);
	statement->setDouble(22, record->TodayProfit);
	statement->setDouble(23, record->Deposit);
	statement->setDouble(24, record->Withdraw);
}
void MysqlDB::SetStatementForCapitalRecordUpdate(sql::PreparedStatement* statement, Capital* record)
{
	statement->setString(1, record->TradingDay);
	statement->setInt(2, int(record->AccountType));
	statement->setDouble(3, record->Asset);
	statement->setDouble(4, record->PreAsset);
	statement->setDouble(5, record->CashAsset);
	statement->setDouble(6, record->PreCashAsset);
	statement->setDouble(7, record->Available);
	statement->setDouble(8, record->CashIn);
	statement->setDouble(9, record->CashOut);
	statement->setDouble(10, record->Margin);
	statement->setDouble(11, record->Commission);
	statement->setDouble(12, record->StampTax);
	statement->setDouble(13, record->TransferFee);
	statement->setDouble(14, record->FrozenCash);
	statement->setDouble(15, record->FrozenMargin);
	statement->setDouble(16, record->FrozenCommission);
	statement->setDouble(17, record->FrozenStampTax);
	statement->setDouble(18, record->FrozenTransferFee);
	statement->setDouble(19, record->MarketValue);
	statement->setDouble(20, record->TotalProfit);
	statement->setDouble(21, record->TodayProfit);
	statement->setDouble(22, record->Deposit);
	statement->setDouble(23, record->Withdraw);
	statement->setString(24, record->AccountID);
}
void MysqlDB::SetStatementForCapitalPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID)
{
	statement->setString(1, AccountID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Capital*>& records)
{
	Capital* record = Capital::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	record->AccountType = AccountTypeType(result->getInt(3));
	record->Asset = result->getDouble(4);
	record->PreAsset = result->getDouble(5);
	record->CashAsset = result->getDouble(6);
	record->PreCashAsset = result->getDouble(7);
	record->Available = result->getDouble(8);
	record->CashIn = result->getDouble(9);
	record->CashOut = result->getDouble(10);
	record->Margin = result->getDouble(11);
	record->Commission = result->getDouble(12);
	record->StampTax = result->getDouble(13);
	record->TransferFee = result->getDouble(14);
	record->FrozenCash = result->getDouble(15);
	record->FrozenMargin = result->getDouble(16);
	record->FrozenCommission = result->getDouble(17);
	record->FrozenStampTax = result->getDouble(18);
	record->FrozenTransferFee = result->getDouble(19);
	record->MarketValue = result->getDouble(20);
	record->TotalProfit = result->getDouble(21);
	record->TodayProfit = result->getDouble(22);
	record->Deposit = result->getDouble(23);
	record->Withdraw = result->getDouble(24);
	records.push_back(record);
}
void MysqlDB::SetStatementForPositionRecord(sql::PreparedStatement* statement, Position* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setInt(3, int(record->AccountType));
	statement->setString(4, record->ExchangeID);
	statement->setString(5, record->InstrumentID);
	statement->setInt(6, int(record->SecurityType));
	statement->setInt(7, int(record->PosiDirection));
	statement->setInt64(8, record->TotalPosition);
	statement->setInt64(9, record->PositionFrozen);
	statement->setInt64(10, record->TodayPosition);
	statement->setDouble(11, record->CashIn);
	statement->setDouble(12, record->CashOut);
	statement->setDouble(13, record->Margin);
	statement->setDouble(14, record->Commission);
	statement->setDouble(15, record->StampTax);
	statement->setDouble(16, record->TransferFee);
	statement->setDouble(17, record->FrozenCash);
	statement->setDouble(18, record->FrozenMargin);
	statement->setDouble(19, record->FrozenCommission);
	statement->setDouble(20, record->FrozenStampTax);
	statement->setDouble(21, record->FrozenTransferFee);
	statement->setDouble(22, record->MarketValue);
	statement->setInt(23, record->VolumeMultiple);
	statement->setDouble(24, record->CloseProfit);
	statement->setDouble(25, record->CloseProfitFloat);
	statement->setDouble(26, record->PositionProfit);
	statement->setDouble(27, record->PositionProfitFloat);
	statement->setDouble(28, record->LastPrice);
	statement->setDouble(29, record->PrePrice);
}
void MysqlDB::SetStatementForPositionRecordUpdate(sql::PreparedStatement* statement, Position* record)
{
	statement->setInt(1, int(record->AccountType));
	statement->setInt(2, int(record->SecurityType));
	statement->setInt64(3, record->TotalPosition);
	statement->setInt64(4, record->PositionFrozen);
	statement->setInt64(5, record->TodayPosition);
	statement->setDouble(6, record->CashIn);
	statement->setDouble(7, record->CashOut);
	statement->setDouble(8, record->Margin);
	statement->setDouble(9, record->Commission);
	statement->setDouble(10, record->StampTax);
	statement->setDouble(11, record->TransferFee);
	statement->setDouble(12, record->FrozenCash);
	statement->setDouble(13, record->FrozenMargin);
	statement->setDouble(14, record->FrozenCommission);
	statement->setDouble(15, record->FrozenStampTax);
	statement->setDouble(16, record->FrozenTransferFee);
	statement->setDouble(17, record->MarketValue);
	statement->setInt(18, record->VolumeMultiple);
	statement->setDouble(19, record->CloseProfit);
	statement->setDouble(20, record->CloseProfitFloat);
	statement->setDouble(21, record->PositionProfit);
	statement->setDouble(22, record->PositionProfitFloat);
	statement->setDouble(23, record->LastPrice);
	statement->setDouble(24, record->PrePrice);
	statement->setString(25, record->TradingDay);
	statement->setString(26, record->AccountID);
	statement->setString(27, record->ExchangeID);
	statement->setString(28, record->InstrumentID);
	statement->setInt(29, int(record->PosiDirection));
}
void MysqlDB::SetStatementForPositionPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
{
	statement->setString(1, TradingDay);
	statement->setString(2, AccountID);
	statement->setString(3, ExchangeID);
	statement->setString(4, InstrumentID);
	statement->setInt(5, int(PosiDirection));
}
void MysqlDB::SetStatementForPositionIndexAccount(sql::PreparedStatement* statement, Position* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Position*>& records)
{
	Position* record = Position::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	record->AccountType = AccountTypeType(result->getInt(3));
	Strcpy(record->ExchangeID, result->getString(4).c_str());
	Strcpy(record->InstrumentID, result->getString(5).c_str());
	record->SecurityType = SecurityTypeType(result->getInt(6));
	record->PosiDirection = PosiDirectionType(result->getInt(7));
	record->TotalPosition = result->getInt64(8);
	record->PositionFrozen = result->getInt64(9);
	record->TodayPosition = result->getInt64(10);
	record->CashIn = result->getDouble(11);
	record->CashOut = result->getDouble(12);
	record->Margin = result->getDouble(13);
	record->Commission = result->getDouble(14);
	record->StampTax = result->getDouble(15);
	record->TransferFee = result->getDouble(16);
	record->FrozenCash = result->getDouble(17);
	record->FrozenMargin = result->getDouble(18);
	record->FrozenCommission = result->getDouble(19);
	record->FrozenStampTax = result->getDouble(20);
	record->FrozenTransferFee = result->getDouble(21);
	record->MarketValue = result->getDouble(22);
	record->VolumeMultiple = result->getInt(23);
	record->CloseProfit = result->getDouble(24);
	record->CloseProfitFloat = result->getDouble(25);
	record->PositionProfit = result->getDouble(26);
	record->PositionProfitFloat = result->getDouble(27);
	record->LastPrice = result->getDouble(28);
	record->PrePrice = result->getDouble(29);
	records.push_back(record);
}
void MysqlDB::SetStatementForOrderRecord(sql::PreparedStatement* statement, Order* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setString(3, record->PrimaryAccountID);
	statement->setInt(4, int(record->AccountType));
	statement->setString(5, record->ExchangeID);
	statement->setString(6, record->InstrumentID);
	statement->setInt(7, int(record->SecurityType));
	statement->setInt(8, record->OrderID);
	statement->setString(9, record->OrderSysID);
	statement->setInt(10, int(record->Direction));
	statement->setInt(11, int(record->OffsetFlag));
	statement->setInt(12, int(record->OrderPriceType));
	statement->setDouble(13, record->Price);
	statement->setInt64(14, record->Volume);
	statement->setInt64(15, record->VolumeTotal);
	statement->setInt64(16, record->VolumeTraded);
	statement->setInt(17, record->VolumeMultiple);
	statement->setInt(18, int(record->OrderStatus));
	statement->setString(19, record->OrderDate);
	statement->setString(20, record->OrderTime);
	statement->setString(21, record->CancelDate);
	statement->setString(22, record->CancelTime);
	statement->setInt64(23, record->SessionID);
	statement->setInt(24, record->ClientOrderID);
	statement->setInt(25, record->RequestID);
	statement->setInt(26, record->OfferID);
	statement->setInt(27, record->TradeGroupID);
	statement->setInt(28, record->RiskGroupID);
	statement->setInt(29, record->CommissionGroupID);
	statement->setDouble(30, record->FrozenCash);
	statement->setDouble(31, record->FrozenMargin);
	statement->setDouble(32, record->FrozenCommission);
	statement->setDouble(33, record->FrozenStampTax);
	statement->setDouble(34, record->FrozenTransferFee);
	statement->setBoolean(35, record->RebuildMark);
	statement->setBoolean(36, record->IsForceClose);
}
void MysqlDB::SetStatementForOrderRecordUpdate(sql::PreparedStatement* statement, Order* record)
{
	statement->setString(1, record->PrimaryAccountID);
	statement->setInt(2, int(record->AccountType));
	statement->setInt(3, int(record->SecurityType));
	statement->setString(4, record->OrderSysID);
	statement->setInt(5, int(record->Direction));
	statement->setInt(6, int(record->OffsetFlag));
	statement->setInt(7, int(record->OrderPriceType));
	statement->setDouble(8, record->Price);
	statement->setInt64(9, record->Volume);
	statement->setInt64(10, record->VolumeTotal);
	statement->setInt64(11, record->VolumeTraded);
	statement->setInt(12, record->VolumeMultiple);
	statement->setInt(13, int(record->OrderStatus));
	statement->setString(14, record->OrderDate);
	statement->setString(15, record->OrderTime);
	statement->setString(16, record->CancelDate);
	statement->setString(17, record->CancelTime);
	statement->setInt64(18, record->SessionID);
	statement->setInt(19, record->ClientOrderID);
	statement->setInt(20, record->RequestID);
	statement->setInt(21, record->OfferID);
	statement->setInt(22, record->TradeGroupID);
	statement->setInt(23, record->RiskGroupID);
	statement->setInt(24, record->CommissionGroupID);
	statement->setDouble(25, record->FrozenCash);
	statement->setDouble(26, record->FrozenMargin);
	statement->setDouble(27, record->FrozenCommission);
	statement->setDouble(28, record->FrozenStampTax);
	statement->setDouble(29, record->FrozenTransferFee);
	statement->setBoolean(30, record->RebuildMark);
	statement->setBoolean(31, record->IsForceClose);
	statement->setString(32, record->TradingDay);
	statement->setString(33, record->AccountID);
	statement->setString(34, record->ExchangeID);
	statement->setString(35, record->InstrumentID);
	statement->setInt(36, record->OrderID);
}
void MysqlDB::SetStatementForOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
{
	statement->setString(1, TradingDay);
	statement->setString(2, AccountID);
	statement->setString(3, ExchangeID);
	statement->setString(4, InstrumentID);
	statement->setInt(5, OrderID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Order*>& records)
{
	Order* record = Order::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	Strcpy(record->PrimaryAccountID, result->getString(3).c_str());
	record->AccountType = AccountTypeType(result->getInt(4));
	Strcpy(record->ExchangeID, result->getString(5).c_str());
	Strcpy(record->InstrumentID, result->getString(6).c_str());
	record->SecurityType = SecurityTypeType(result->getInt(7));
	record->OrderID = result->getInt(8);
	Strcpy(record->OrderSysID, result->getString(9).c_str());
	record->Direction = DirectionType(result->getInt(10));
	record->OffsetFlag = OffsetFlagType(result->getInt(11));
	record->OrderPriceType = OrderPriceTypeType(result->getInt(12));
	record->Price = result->getDouble(13);
	record->Volume = result->getInt64(14);
	record->VolumeTotal = result->getInt64(15);
	record->VolumeTraded = result->getInt64(16);
	record->VolumeMultiple = result->getInt(17);
	record->OrderStatus = OrderStatusType(result->getInt(18));
	Strcpy(record->OrderDate, result->getString(19).c_str());
	Strcpy(record->OrderTime, result->getString(20).c_str());
	Strcpy(record->CancelDate, result->getString(21).c_str());
	Strcpy(record->CancelTime, result->getString(22).c_str());
	record->SessionID = result->getInt64(23);
	record->ClientOrderID = result->getInt(24);
	record->RequestID = result->getInt(25);
	record->OfferID = result->getInt(26);
	record->TradeGroupID = result->getInt(27);
	record->RiskGroupID = result->getInt(28);
	record->CommissionGroupID = result->getInt(29);
	record->FrozenCash = result->getDouble(30);
	record->FrozenMargin = result->getDouble(31);
	record->FrozenCommission = result->getDouble(32);
	record->FrozenStampTax = result->getDouble(33);
	record->FrozenTransferFee = result->getDouble(34);
	record->RebuildMark = result->getBoolean(35);
	record->IsForceClose = result->getBoolean(36);
	records.push_back(record);
}
void MysqlDB::SetStatementForTradeRecord(sql::PreparedStatement* statement, Trade* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->AccountID);
	statement->setString(3, record->PrimaryAccountID);
	statement->setInt(4, int(record->AccountType));
	statement->setString(5, record->ExchangeID);
	statement->setString(6, record->InstrumentID);
	statement->setInt(7, int(record->SecurityType));
	statement->setInt(8, record->OrderID);
	statement->setString(9, record->OrderSysID);
	statement->setString(10, record->TradeID);
	statement->setInt(11, int(record->Direction));
	statement->setInt(12, int(record->OffsetFlag));
	statement->setDouble(13, record->Price);
	statement->setInt64(14, record->Volume);
	statement->setInt(15, record->VolumeMultiple);
	statement->setDouble(16, record->TradeAmount);
	statement->setDouble(17, record->Commission);
	statement->setDouble(18, record->StampTax);
	statement->setDouble(19, record->TransferFee);
	statement->setString(20, record->TradeDate);
	statement->setString(21, record->TradeTime);
}
void MysqlDB::SetStatementForTradeRecordUpdate(sql::PreparedStatement* statement, Trade* record)
{
	statement->setString(1, record->AccountID);
	statement->setString(2, record->PrimaryAccountID);
	statement->setInt(3, int(record->AccountType));
	statement->setString(4, record->InstrumentID);
	statement->setInt(5, int(record->SecurityType));
	statement->setInt(6, record->OrderID);
	statement->setString(7, record->OrderSysID);
	statement->setInt(8, int(record->OffsetFlag));
	statement->setDouble(9, record->Price);
	statement->setInt64(10, record->Volume);
	statement->setInt(11, record->VolumeMultiple);
	statement->setDouble(12, record->TradeAmount);
	statement->setDouble(13, record->Commission);
	statement->setDouble(14, record->StampTax);
	statement->setDouble(15, record->TransferFee);
	statement->setString(16, record->TradeDate);
	statement->setString(17, record->TradeTime);
	statement->setString(18, record->TradingDay);
	statement->setString(19, record->ExchangeID);
	statement->setString(20, record->TradeID);
	statement->setInt(21, int(record->Direction));
}
void MysqlDB::SetStatementForTradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
{
	statement->setString(1, TradingDay);
	statement->setString(2, ExchangeID);
	statement->setString(3, TradeID);
	statement->setInt(4, int(Direction));
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<Trade*>& records)
{
	Trade* record = Trade::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->AccountID, result->getString(2).c_str());
	Strcpy(record->PrimaryAccountID, result->getString(3).c_str());
	record->AccountType = AccountTypeType(result->getInt(4));
	Strcpy(record->ExchangeID, result->getString(5).c_str());
	Strcpy(record->InstrumentID, result->getString(6).c_str());
	record->SecurityType = SecurityTypeType(result->getInt(7));
	record->OrderID = result->getInt(8);
	Strcpy(record->OrderSysID, result->getString(9).c_str());
	Strcpy(record->TradeID, result->getString(10).c_str());
	record->Direction = DirectionType(result->getInt(11));
	record->OffsetFlag = OffsetFlagType(result->getInt(12));
	record->Price = result->getDouble(13);
	record->Volume = result->getInt64(14);
	record->VolumeMultiple = result->getInt(15);
	record->TradeAmount = result->getDouble(16);
	record->Commission = result->getDouble(17);
	record->StampTax = result->getDouble(18);
	record->TransferFee = result->getDouble(19);
	Strcpy(record->TradeDate, result->getString(20).c_str());
	Strcpy(record->TradeTime, result->getString(21).c_str());
	records.push_back(record);
}
void MysqlDB::SetStatementForDepthMarketDataRecord(sql::PreparedStatement* statement, DepthMarketData* record)
{
	statement->setString(1, record->TradingDay);
	statement->setString(2, record->ExchangeID);
	statement->setString(3, record->InstrumentID);
	statement->setDouble(4, record->LastPrice);
	statement->setDouble(5, record->PreSettlementPrice);
	statement->setDouble(6, record->PreClosePrice);
	statement->setInt64(7, record->PreOpenInterest);
	statement->setDouble(8, record->OpenPrice);
	statement->setDouble(9, record->HighestPrice);
	statement->setDouble(10, record->LowestPrice);
	statement->setDouble(11, record->ClosePrice);
	statement->setInt64(12, record->CurrVolume);
	statement->setInt64(13, record->Volume);
	statement->setDouble(14, record->CurrTurnover);
	statement->setDouble(15, record->Turnover);
	statement->setInt64(16, record->OpenInterest);
	statement->setDouble(17, record->SettlementPrice);
	statement->setDouble(18, record->UpperLimitPrice);
	statement->setDouble(19, record->LowerLimitPrice);
	statement->setDouble(20, record->AveragePrice);
	statement->setInt64(21, record->UpdateTs);
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
	statement->setDouble(1, record->LastPrice);
	statement->setDouble(2, record->PreSettlementPrice);
	statement->setDouble(3, record->PreClosePrice);
	statement->setInt64(4, record->PreOpenInterest);
	statement->setDouble(5, record->OpenPrice);
	statement->setDouble(6, record->HighestPrice);
	statement->setDouble(7, record->LowestPrice);
	statement->setDouble(8, record->ClosePrice);
	statement->setInt64(9, record->CurrVolume);
	statement->setInt64(10, record->Volume);
	statement->setDouble(11, record->CurrTurnover);
	statement->setDouble(12, record->Turnover);
	statement->setInt64(13, record->OpenInterest);
	statement->setDouble(14, record->SettlementPrice);
	statement->setDouble(15, record->UpperLimitPrice);
	statement->setDouble(16, record->LowerLimitPrice);
	statement->setDouble(17, record->AveragePrice);
	statement->setInt64(18, record->UpdateTs);
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
void MysqlDB::ParseRecord(sql::ResultSet* result, std::vector<DepthMarketData*>& records)
{
	DepthMarketData* record = DepthMarketData::Allocate();
	Strcpy(record->TradingDay, result->getString(1).c_str());
	Strcpy(record->ExchangeID, result->getString(2).c_str());
	Strcpy(record->InstrumentID, result->getString(3).c_str());
	record->LastPrice = result->getDouble(4);
	record->PreSettlementPrice = result->getDouble(5);
	record->PreClosePrice = result->getDouble(6);
	record->PreOpenInterest = result->getInt64(7);
	record->OpenPrice = result->getDouble(8);
	record->HighestPrice = result->getDouble(9);
	record->LowestPrice = result->getDouble(10);
	record->ClosePrice = result->getDouble(11);
	record->CurrVolume = result->getInt64(12);
	record->Volume = result->getInt64(13);
	record->CurrTurnover = result->getDouble(14);
	record->Turnover = result->getDouble(15);
	record->OpenInterest = result->getInt64(16);
	record->SettlementPrice = result->getDouble(17);
	record->UpperLimitPrice = result->getDouble(18);
	record->LowerLimitPrice = result->getDouble(19);
	record->AveragePrice = result->getDouble(20);
	record->UpdateTs = result->getInt64(21);
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

