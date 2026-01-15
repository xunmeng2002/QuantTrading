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
	
	m_TradingDayCreateStatement = nullptr;
	m_TradingDayDropStatement = nullptr;
	m_TradingDayInsertStatement = nullptr;
	m_TradingDayDeleteStatement = nullptr;
	m_TradingDayUpdateStatement = nullptr;
	m_TradingDaySelectStatement = nullptr;
	m_TradingDayTruncateStatement = nullptr;

	m_ExchangeCreateStatement = nullptr;
	m_ExchangeDropStatement = nullptr;
	m_ExchangeInsertStatement = nullptr;
	m_ExchangeDeleteStatement = nullptr;
	m_ExchangeUpdateStatement = nullptr;
	m_ExchangeSelectStatement = nullptr;
	m_ExchangeTruncateStatement = nullptr;

	m_ProductCreateStatement = nullptr;
	m_ProductDropStatement = nullptr;
	m_ProductInsertStatement = nullptr;
	m_ProductDeleteStatement = nullptr;
	m_ProductUpdateStatement = nullptr;
	m_ProductSelectStatement = nullptr;
	m_ProductTruncateStatement = nullptr;

	m_InstrumentCreateStatement = nullptr;
	m_InstrumentDropStatement = nullptr;
	m_InstrumentInsertStatement = nullptr;
	m_InstrumentDeleteStatement = nullptr;
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

	m_PrimaryAccountCreateStatement = nullptr;
	m_PrimaryAccountDropStatement = nullptr;
	m_PrimaryAccountInsertStatement = nullptr;
	m_PrimaryAccountDeleteStatement = nullptr;
	m_PrimaryAccountDeleteByOfferIDIndexStatement = nullptr;
	m_PrimaryAccountUpdateStatement = nullptr;
	m_PrimaryAccountSelectStatement = nullptr;
	m_PrimaryAccountTruncateStatement = nullptr;

	m_AccountCreateStatement = nullptr;
	m_AccountDropStatement = nullptr;
	m_AccountInsertStatement = nullptr;
	m_AccountDeleteStatement = nullptr;
	m_AccountUpdateStatement = nullptr;
	m_AccountSelectStatement = nullptr;
	m_AccountTruncateStatement = nullptr;

	m_OrderCreateStatement = nullptr;
	m_OrderDropStatement = nullptr;
	m_OrderInsertStatement = nullptr;
	m_OrderDeleteStatement = nullptr;
	m_OrderUpdateStatement = nullptr;
	m_OrderSelectStatement = nullptr;
	m_OrderTruncateStatement = nullptr;

	m_TradeCreateStatement = nullptr;
	m_TradeDropStatement = nullptr;
	m_TradeInsertStatement = nullptr;
	m_TradeDeleteStatement = nullptr;
	m_TradeUpdateStatement = nullptr;
	m_TradeSelectStatement = nullptr;
	m_TradeTruncateStatement = nullptr;

	m_AccountLoginSessionCreateStatement = nullptr;
	m_AccountLoginSessionDropStatement = nullptr;
	m_AccountLoginSessionInsertStatement = nullptr;
	m_AccountLoginSessionDeleteStatement = nullptr;
	m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	m_AccountLoginSessionUpdateStatement = nullptr;
	m_AccountLoginSessionSelectStatement = nullptr;
	m_AccountLoginSessionTruncateStatement = nullptr;

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
	if (m_TradingDayCreateStatement != nullptr)
	{
		m_TradingDayCreateStatement->close();
		m_TradingDayCreateStatement = nullptr;
	}
	if (m_TradingDayDropStatement != nullptr)
	{
		m_TradingDayDropStatement->close();
		m_TradingDayDropStatement = nullptr;
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
	if (m_ProductCreateStatement != nullptr)
	{
		m_ProductCreateStatement->close();
		m_ProductCreateStatement = nullptr;
	}
	if (m_ProductDropStatement != nullptr)
	{
		m_ProductDropStatement->close();
		m_ProductDropStatement = nullptr;
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
	if (m_PrimaryAccountCreateStatement != nullptr)
	{
		m_PrimaryAccountCreateStatement->close();
		m_PrimaryAccountCreateStatement = nullptr;
	}
	if (m_PrimaryAccountDropStatement != nullptr)
	{
		m_PrimaryAccountDropStatement->close();
		m_PrimaryAccountDropStatement = nullptr;
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
	if (m_AccountCreateStatement != nullptr)
	{
		m_AccountCreateStatement->close();
		m_AccountCreateStatement = nullptr;
	}
	if (m_AccountDropStatement != nullptr)
	{
		m_AccountDropStatement->close();
		m_AccountDropStatement = nullptr;
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
	if (m_OrderCreateStatement != nullptr)
	{
		m_OrderCreateStatement->close();
		m_OrderCreateStatement = nullptr;
	}
	if (m_OrderDropStatement != nullptr)
	{
		m_OrderDropStatement->close();
		m_OrderDropStatement = nullptr;
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
	if (m_TradeCreateStatement != nullptr)
	{
		m_TradeCreateStatement->close();
		m_TradeCreateStatement = nullptr;
	}
	if (m_TradeDropStatement != nullptr)
	{
		m_TradeDropStatement->close();
		m_TradeDropStatement = nullptr;
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
	if (m_AccountLoginSessionCreateStatement != nullptr)
	{
		m_AccountLoginSessionCreateStatement->close();
		m_AccountLoginSessionCreateStatement = nullptr;
	}
	if (m_AccountLoginSessionDropStatement != nullptr)
	{
		m_AccountLoginSessionDropStatement->close();
		m_AccountLoginSessionDropStatement = nullptr;
	}
	if (m_AccountLoginSessionInsertStatement != nullptr)
	{
		m_AccountLoginSessionInsertStatement->close();
		m_AccountLoginSessionInsertStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteStatement != nullptr)
	{
		m_AccountLoginSessionDeleteStatement->close();
		m_AccountLoginSessionDeleteStatement = nullptr;
	}
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement != nullptr)
	{
		m_AccountLoginSessionDeleteByAccountIDIndexStatement->close();
		m_AccountLoginSessionDeleteByAccountIDIndexStatement = nullptr;
	}
	if (m_AccountLoginSessionUpdateStatement != nullptr)
	{
		m_AccountLoginSessionUpdateStatement->close();
		m_AccountLoginSessionUpdateStatement = nullptr;
	}
	if (m_AccountLoginSessionSelectStatement != nullptr)
	{
		m_AccountLoginSessionSelectStatement->close();
		m_AccountLoginSessionSelectStatement = nullptr;
	}
	if (m_AccountLoginSessionTruncateStatement != nullptr)
	{
		m_AccountLoginSessionTruncateStatement->close();
		m_AccountLoginSessionTruncateStatement = nullptr;
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
	m_Statement->executeUpdate("Truncate Table t_DepthMarketData;");
	m_Statement->executeUpdate("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	m_Statement->executeUpdate("Truncate Table t_BarMarketData;");
	m_Statement->executeUpdate("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	m_Statement->executeUpdate("Truncate Table t_PrimaryAccount;");
	m_Statement->executeUpdate("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	m_Statement->executeUpdate("Truncate Table t_Account;");
	m_Statement->executeUpdate("Insert Into t_Account select * from Init.t_Account;");
	m_Statement->executeUpdate("Truncate Table t_Order;");
	m_Statement->executeUpdate("Insert Into t_Order select * from Init.t_Order;");
	m_Statement->executeUpdate("Truncate Table t_Trade;");
	m_Statement->executeUpdate("Insert Into t_Trade select * from Init.t_Trade;");
	m_Statement->executeUpdate("Truncate Table t_AccountLoginSession;");
	m_Statement->executeUpdate("Insert Into t_AccountLoginSession select * from Init.t_AccountLoginSession;");
}
void MysqlDB::CreateTables()
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
void MysqlDB::DropTables()
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
void MysqlDB::TruncateTables()
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
void MysqlDB::TruncateSessionTables()
{
	auto start = steady_clock::now();
	TruncateAccountLoginSession();
	WriteLog(LogLevel::Info, "TruncateSessionTables Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}

void MysqlDB::CreateTradingDay()
{
	auto start = steady_clock::now();
	if (m_TradingDayCreateStatement == nullptr)
	{
		m_TradingDayCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_TradingDay(`PK` int, `CurrTradingDay` char(9), `PreTradingDay` char(9), PRIMARY KEY(PK)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_TradingDayCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTradingDay Spend:%lldms", duration);
}
void MysqlDB::DropTradingDay()
{
	auto start = steady_clock::now();
	if (m_TradingDayDropStatement == nullptr)
	{
		m_TradingDayDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_TradingDay;");
	}
	m_TradingDayDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTradingDay Spend:%lldms", duration);
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
void MysqlDB::CreateProduct()
{
	auto start = steady_clock::now();
	if (m_ProductCreateStatement == nullptr)
	{
		m_ProductCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Product(`ExchangeID` char(8), `ProductID` char(32), `ProductName` char(32), `ProductClass` int, `VolumeMultiple` int, `PriceTick` decimal(24,8), `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` char(32), PRIMARY KEY(ExchangeID, ProductID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_ProductCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateProduct Spend:%lldms", duration);
}
void MysqlDB::DropProduct()
{
	auto start = steady_clock::now();
	if (m_ProductDropStatement == nullptr)
	{
		m_ProductDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Product;");
	}
	m_ProductDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropProduct Spend:%lldms", duration);
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
void MysqlDB::CreateInstrument()
{
	auto start = steady_clock::now();
	if (m_InstrumentCreateStatement == nullptr)
	{
		m_InstrumentCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Instrument(`ExchangeID` char(8), `InstrumentID` char(32), `ExchangeInstID` char(32), `InstrumentName` char(64), `ProductID` char(32), `ProductClass` int, `InstrumentClass` int, `Rank` int, `VolumeMultiple` int, `PriceTick` decimal(24,8), `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` char(32), PRIMARY KEY(ExchangeID, InstrumentID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
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
void MysqlDB::CreatePrimaryAccount()
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountCreateStatement == nullptr)
	{
		m_PrimaryAccountCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_PrimaryAccount(`PrimaryAccountID` char(32), `PrimaryAccountName` char(64), `AccountClass` int, `BrokerPassword` char(64), `OfferID` int, `IsAllowLogin` bool, `IsSimulateAccount` bool, `LoginStatus` int, `InitStatus` int, INDEX PrimaryAccountOfferID(OfferID), PRIMARY KEY(PrimaryAccountID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_PrimaryAccountCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePrimaryAccount Spend:%lldms", duration);
}
void MysqlDB::DropPrimaryAccount()
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountDropStatement == nullptr)
	{
		m_PrimaryAccountDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_PrimaryAccount;");
	}
	m_PrimaryAccountDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPrimaryAccount Spend:%lldms", duration);
}
void MysqlDB::InsertPrimaryAccount(PrimaryAccount* record)
{
	auto start = steady_clock::now();
	if (m_PrimaryAccountInsertStatement == nullptr)
	{
		m_PrimaryAccountInsertStatement = m_DBConnection->prepareStatement("insert into t_PrimaryAccount Values(?, ?, ?, ?, ?, ?, ?, ?, ?);");
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
		m_PrimaryAccountUpdateStatement = m_DBConnection->prepareStatement("update t_PrimaryAccount set PrimaryAccountName = ?, AccountClass = ?, BrokerPassword = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;");
	}
	SetStatementForPrimaryAccountRecordUpdate(m_PrimaryAccountUpdateStatement, record);
	m_PrimaryAccountUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePrimaryAccount Spend:%lldms", duration);
	}
}
void MysqlDB::SelectPrimaryAccount(std::list<PrimaryAccount*>& records)
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
void MysqlDB::CreateAccount()
{
	auto start = steady_clock::now();
	if (m_AccountCreateStatement == nullptr)
	{
		m_AccountCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Account(`AccountID` char(32), `AccountName` char(64), `AccountType` int, `AccountStatus` int, `Password` char(64), `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, PRIMARY KEY(AccountID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_AccountCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccount Spend:%lldms", duration);
}
void MysqlDB::DropAccount()
{
	auto start = steady_clock::now();
	if (m_AccountDropStatement == nullptr)
	{
		m_AccountDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Account;");
	}
	m_AccountDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccount Spend:%lldms", duration);
}
void MysqlDB::InsertAccount(Account* record)
{
	auto start = steady_clock::now();
	if (m_AccountInsertStatement == nullptr)
	{
		m_AccountInsertStatement = m_DBConnection->prepareStatement("insert into t_Account Values(?, ?, ?, ?, ?, ?, ?, ?);");
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
		m_AccountUpdateStatement = m_DBConnection->prepareStatement("update t_Account set AccountName = ?, AccountType = ?, AccountStatus = ?, Password = ?, TradeGroupID = ?, RiskGroupID = ?, CommissionGroupID = ? where AccountID = ?;");
	}
	SetStatementForAccountRecordUpdate(m_AccountUpdateStatement, record);
	m_AccountUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccount Spend:%lldms", duration);
	}
}
void MysqlDB::SelectAccount(std::list<Account*>& records)
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
void MysqlDB::CreateOrder()
{
	auto start = steady_clock::now();
	if (m_OrderCreateStatement == nullptr)
	{
		m_OrderCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Order(`TradingDay` char(9), `AccountID` char(32), `AccountType` int, `ExchangeID` char(8), `InstrumentID` char(32), `ProductClass` int, `OrderID` int, `OrderSysID` char(64), `Direction` int, `OffsetFlag` int, `OrderPriceType` int, `Price` decimal(24,8), `Volume` bigint, `VolumeTotal` bigint, `VolumeTraded` bigint, `VolumeMultiple` int, `OrderStatus` int, `OrderDate` char(9), `OrderTime` char(9), `CancelDate` char(9), `CancelTime` char(9), `SessionID` bigint, `ClientOrderID` int, `RequestID` int, `OfferID` int, `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, `FrozenCash` decimal(24,8), `FrozenMargin` decimal(24,8), `FrozenCommission` decimal(24,8), `RebuildMark` bool, `IsForceClose` bool, UNIQUE ClientOrderID(TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_OrderCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateOrder Spend:%lldms", duration);
}
void MysqlDB::DropOrder()
{
	auto start = steady_clock::now();
	if (m_OrderDropStatement == nullptr)
	{
		m_OrderDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Order;");
	}
	m_OrderDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropOrder Spend:%lldms", duration);
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
void MysqlDB::CreateTrade()
{
	auto start = steady_clock::now();
	if (m_TradeCreateStatement == nullptr)
	{
		m_TradeCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_Trade(`TradingDay` char(9), `AccountID` char(32), `AccountType` int, `ExchangeID` char(8), `InstrumentID` char(32), `ProductClass` int, `OrderID` int, `OrderSysID` char(64), `TradeID` char(64), `Direction` int, `OffsetFlag` int, `Price` decimal(24,8), `Volume` bigint, `VolumeMultiple` int, `TradeAmount` decimal(24,8), `Commission` decimal(24,8), `TradeDate` char(9), `TradeTime` char(9), PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_TradeCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTrade Spend:%lldms", duration);
}
void MysqlDB::DropTrade()
{
	auto start = steady_clock::now();
	if (m_TradeDropStatement == nullptr)
	{
		m_TradeDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_Trade;");
	}
	m_TradeDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTrade Spend:%lldms", duration);
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
void MysqlDB::CreateAccountLoginSession()
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionCreateStatement == nullptr)
	{
		m_AccountLoginSessionCreateStatement = m_DBConnection->prepareStatement("CREATE TABLE IF NOT EXISTS t_AccountLoginSession(`AccountID` char(32), `SessionID` bigint, `IPAddress` char(16), INDEX AccountLoginSessionAccountID(AccountID), PRIMARY KEY(SessionID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';");
	}
	m_AccountLoginSessionCreateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccountLoginSession Spend:%lldms", duration);
}
void MysqlDB::DropAccountLoginSession()
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDropStatement == nullptr)
	{
		m_AccountLoginSessionDropStatement = m_DBConnection->prepareStatement("DROP TABLE IF EXISTS t_AccountLoginSession;");
	}
	m_AccountLoginSessionDropStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccountLoginSession Spend:%lldms", duration);
}
void MysqlDB::InsertAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionInsertStatement == nullptr)
	{
		m_AccountLoginSessionInsertStatement = m_DBConnection->prepareStatement("insert into t_AccountLoginSession Values(?, ?, ?);");
	}
	SetStatementForAccountLoginSessionRecord(m_AccountLoginSessionInsertStatement, record);
	
	m_AccountLoginSessionInsertStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertAccountLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::BatchInsertAccountLoginSession(std::list<AccountLoginSession*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_AccountLoginSession Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
			}
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_AccountLoginSession Values");
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
		WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession Failed. Error: %s, Sql:[%s]", e.what(), m_SqlBuff);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertAccountLoginSession RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void MysqlDB::DeleteAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteStatement == nullptr)
	{
		m_AccountLoginSessionDeleteStatement = m_DBConnection->prepareStatement("delete from t_AccountLoginSession where SessionID = ?;");
	}
	SetStatementForAccountLoginSessionPrimaryKey(m_AccountLoginSessionDeleteStatement, record->SessionID);
	m_AccountLoginSessionDeleteStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::DeleteAccountLoginSessionByAccountIDIndex(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionDeleteByAccountIDIndexStatement == nullptr)
	{
		m_AccountLoginSessionDeleteByAccountIDIndexStatement = m_DBConnection->prepareStatement("delete from t_AccountLoginSession where AccountID = ?;");
	}
	SetStatementForAccountLoginSessionIndexAccountID(m_AccountLoginSessionDeleteByAccountIDIndexStatement, record);
	m_AccountLoginSessionDeleteByAccountIDIndexStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteAccountLoginSessionByAccountIDIndex Spend:%lldms", duration);
	}
}
void MysqlDB::UpdateAccountLoginSession(AccountLoginSession* record)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionUpdateStatement == nullptr)
	{
		m_AccountLoginSessionUpdateStatement = m_DBConnection->prepareStatement("update t_AccountLoginSession set AccountID = ?, IPAddress = ? where SessionID = ?;");
	}
	SetStatementForAccountLoginSessionRecordUpdate(m_AccountLoginSessionUpdateStatement, record);
	m_AccountLoginSessionUpdateStatement->executeUpdate();
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdateAccountLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::SelectAccountLoginSession(std::list<AccountLoginSession*>& records)
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionSelectStatement == nullptr)
	{
		m_AccountLoginSessionSelectStatement = m_DBConnection->prepareStatement("select * from t_AccountLoginSession;");
	}
	auto result = m_AccountLoginSessionSelectStatement->executeQuery();
	while (result->next())
	{
		ParseRecord(result, records);
	}
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectAccountLoginSession Spend:%lldms", duration);
	}
}
void MysqlDB::TruncateAccountLoginSession()
{
	auto start = steady_clock::now();
	if (m_AccountLoginSessionTruncateStatement == nullptr)
	{
		m_AccountLoginSessionTruncateStatement = m_DBConnection->prepareStatement("truncate table t_AccountLoginSession;");
	}
	m_AccountLoginSessionTruncateStatement->executeQuery();
	WriteLog(LogLevel::Info, "TruncateAccountLoginSession Spend:%lldms", GetDuration<chrono::milliseconds>(start));
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
void MysqlDB::SetStatementForPrimaryAccountRecord(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setString(1, record->PrimaryAccountID);
	statement->setString(2, record->PrimaryAccountName);
	statement->setInt(3, int(record->AccountClass));
	statement->setString(4, record->BrokerPassword);
	statement->setInt(5, record->OfferID);
	statement->setBoolean(6, record->IsAllowLogin);
	statement->setBoolean(7, record->IsSimulateAccount);
	statement->setInt(8, int(record->LoginStatus));
	statement->setInt(9, int(record->InitStatus));
}
void MysqlDB::SetStatementForPrimaryAccountRecordUpdate(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setString(1, record->PrimaryAccountName);
	statement->setInt(2, int(record->AccountClass));
	statement->setString(3, record->BrokerPassword);
	statement->setInt(4, record->OfferID);
	statement->setBoolean(5, record->IsAllowLogin);
	statement->setBoolean(6, record->IsSimulateAccount);
	statement->setInt(7, int(record->LoginStatus));
	statement->setInt(8, int(record->InitStatus));
	statement->setString(9, record->PrimaryAccountID);
}
void MysqlDB::SetStatementForPrimaryAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& PrimaryAccountID)
{
	statement->setString(1, PrimaryAccountID);
}
void MysqlDB::SetStatementForPrimaryAccountIndexOfferID(sql::PreparedStatement* statement, PrimaryAccount* record)
{
	statement->setInt(1, record->OfferID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<PrimaryAccount*>& records)
{
	PrimaryAccount* record = PrimaryAccount::Allocate();
	Strcpy(record->PrimaryAccountID, result->getString(1).c_str());
	Strcpy(record->PrimaryAccountName, result->getString(2).c_str());
	record->AccountClass = AccountClassType(result->getInt(3));
	Strcpy(record->BrokerPassword, result->getString(4).c_str());
	record->OfferID = result->getInt(5);
	record->IsAllowLogin = result->getBoolean(6);
	record->IsSimulateAccount = result->getBoolean(7);
	record->LoginStatus = LoginStatusType(result->getInt(8));
	record->InitStatus = InitStatusType(result->getInt(9));
	records.push_back(record);
}
void MysqlDB::SetStatementForAccountRecord(sql::PreparedStatement* statement, Account* record)
{
	statement->setString(1, record->AccountID);
	statement->setString(2, record->AccountName);
	statement->setInt(3, int(record->AccountType));
	statement->setInt(4, int(record->AccountStatus));
	statement->setString(5, record->Password);
	statement->setInt(6, record->TradeGroupID);
	statement->setInt(7, record->RiskGroupID);
	statement->setInt(8, record->CommissionGroupID);
}
void MysqlDB::SetStatementForAccountRecordUpdate(sql::PreparedStatement* statement, Account* record)
{
	statement->setString(1, record->AccountName);
	statement->setInt(2, int(record->AccountType));
	statement->setInt(3, int(record->AccountStatus));
	statement->setString(4, record->Password);
	statement->setInt(5, record->TradeGroupID);
	statement->setInt(6, record->RiskGroupID);
	statement->setInt(7, record->CommissionGroupID);
	statement->setString(8, record->AccountID);
}
void MysqlDB::SetStatementForAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID)
{
	statement->setString(1, AccountID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<Account*>& records)
{
	Account* record = Account::Allocate();
	Strcpy(record->AccountID, result->getString(1).c_str());
	Strcpy(record->AccountName, result->getString(2).c_str());
	record->AccountType = AccountTypeType(result->getInt(3));
	record->AccountStatus = AccountStatusType(result->getInt(4));
	Strcpy(record->Password, result->getString(5).c_str());
	record->TradeGroupID = result->getInt(6);
	record->RiskGroupID = result->getInt(7);
	record->CommissionGroupID = result->getInt(8);
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
void MysqlDB::SetStatementForAccountLoginSessionRecord(sql::PreparedStatement* statement, AccountLoginSession* record)
{
	statement->setString(1, record->AccountID);
	statement->setInt64(2, record->SessionID);
	statement->setString(3, record->IPAddress);
}
void MysqlDB::SetStatementForAccountLoginSessionRecordUpdate(sql::PreparedStatement* statement, AccountLoginSession* record)
{
	statement->setString(1, record->AccountID);
	statement->setString(2, record->IPAddress);
	statement->setInt64(3, record->SessionID);
}
void MysqlDB::SetStatementForAccountLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID)
{
	statement->setInt64(1, SessionID);
}
void MysqlDB::SetStatementForAccountLoginSessionIndexAccountID(sql::PreparedStatement* statement, AccountLoginSession* record)
{
	statement->setString(1, record->AccountID);
}
void MysqlDB::ParseRecord(sql::ResultSet* result, std::list<AccountLoginSession*>& records)
{
	AccountLoginSession* record = AccountLoginSession::Allocate();
	Strcpy(record->AccountID, result->getString(1).c_str());
	record->SessionID = result->getInt64(2);
	Strcpy(record->IPAddress, result->getString(3).c_str());
	records.push_back(record);
}

