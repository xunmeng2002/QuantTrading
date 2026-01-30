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

	m_MdUserInsertStatement = nullptr;
	m_MdUserDeleteStatement = nullptr;
	m_MdUserUpdateStatement = nullptr;
	m_MdUserSelectStatement = nullptr;
	m_MdUserTruncateStatement = nullptr;

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
	m_CapitalDeleteByTradingDayIndexStatement = nullptr;
	m_CapitalUpdateStatement = nullptr;
	m_CapitalSelectStatement = nullptr;
	m_CapitalTruncateStatement = nullptr;

	m_PositionInsertStatement = nullptr;
	m_PositionDeleteStatement = nullptr;
	m_PositionDeleteByAccountIndexStatement = nullptr;
	m_PositionDeleteByTradingDayIndexStatement = nullptr;
	m_PositionUpdateStatement = nullptr;
	m_PositionSelectStatement = nullptr;
	m_PositionTruncateStatement = nullptr;

	m_PositionDetailInsertStatement = nullptr;
	m_PositionDetailDeleteStatement = nullptr;
	m_PositionDetailDeleteByTradeMatchIndexStatement = nullptr;
	m_PositionDetailDeleteByTradingDayIndexStatement = nullptr;
	m_PositionDetailUpdateStatement = nullptr;
	m_PositionDetailSelectStatement = nullptr;
	m_PositionDetailTruncateStatement = nullptr;

	m_OrderInsertStatement = nullptr;
	m_OrderDeleteStatement = nullptr;
	m_OrderDeleteByAccountIDIndexStatement = nullptr;
	m_OrderUpdateStatement = nullptr;
	m_OrderSelectStatement = nullptr;
	m_OrderTruncateStatement = nullptr;

	m_TradeInsertStatement = nullptr;
	m_TradeDeleteStatement = nullptr;
	m_TradeDeleteByAccountIDIndexStatement = nullptr;
	m_TradeUpdateStatement = nullptr;
	m_TradeSelectStatement = nullptr;
	m_TradeTruncateStatement = nullptr;

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
	if (m_CapitalDeleteByTradingDayIndexStatement != nullptr)
	{
		sqlite3_finalize(m_CapitalDeleteByTradingDayIndexStatement);
		m_CapitalDeleteByTradingDayIndexStatement = nullptr;
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
	if (m_PositionDeleteByTradingDayIndexStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDeleteByTradingDayIndexStatement);
		m_PositionDeleteByTradingDayIndexStatement = nullptr;
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
	if (m_PositionDetailInsertStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailInsertStatement);
		m_PositionDetailInsertStatement = nullptr;
	}
	if (m_PositionDetailDeleteStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailDeleteStatement);
		m_PositionDetailDeleteStatement = nullptr;
	}
	if (m_PositionDetailDeleteByTradeMatchIndexStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailDeleteByTradeMatchIndexStatement);
		m_PositionDetailDeleteByTradeMatchIndexStatement = nullptr;
	}
	if (m_PositionDetailDeleteByTradingDayIndexStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailDeleteByTradingDayIndexStatement);
		m_PositionDetailDeleteByTradingDayIndexStatement = nullptr;
	}
	if (m_PositionDetailUpdateStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailUpdateStatement);
		m_PositionDetailUpdateStatement = nullptr;
	}
	if (m_PositionDetailSelectStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailSelectStatement);
		m_PositionDetailSelectStatement = nullptr;
	}
	if (m_PositionDetailTruncateStatement != nullptr)
	{
		sqlite3_finalize(m_PositionDetailTruncateStatement);
		m_PositionDetailTruncateStatement = nullptr;
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
	if (m_OrderDeleteByAccountIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_OrderDeleteByAccountIDIndexStatement);
		m_OrderDeleteByAccountIDIndexStatement = nullptr;
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
	if (m_TradeDeleteByAccountIDIndexStatement != nullptr)
	{
		sqlite3_finalize(m_TradeDeleteByAccountIDIndexStatement);
		m_TradeDeleteByAccountIDIndexStatement = nullptr;
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
	Exec("Truncate Table t_DepthMarketData;");
	Exec("Insert Into t_DepthMarketData select * from Init.t_DepthMarketData;");
	Exec("Truncate Table t_BarMarketData;");
	Exec("Insert Into t_BarMarketData select * from Init.t_BarMarketData;");
	Exec("Truncate Table t_MdUser;");
	Exec("Insert Into t_MdUser select * from Init.t_MdUser;");
	Exec("Truncate Table t_PrimaryAccount;");
	Exec("Insert Into t_PrimaryAccount select * from Init.t_PrimaryAccount;");
	Exec("Truncate Table t_Account;");
	Exec("Insert Into t_Account select * from Init.t_Account;");
	Exec("Truncate Table t_Capital;");
	Exec("Insert Into t_Capital select * from Init.t_Capital;");
	Exec("Truncate Table t_Position;");
	Exec("Insert Into t_Position select * from Init.t_Position;");
	Exec("Truncate Table t_PositionDetail;");
	Exec("Insert Into t_PositionDetail select * from Init.t_PositionDetail;");
	Exec("Truncate Table t_Order;");
	Exec("Insert Into t_Order select * from Init.t_Order;");
	Exec("Truncate Table t_Trade;");
	Exec("Insert Into t_Trade select * from Init.t_Trade;");
}
void SqliteDB::CreateTables()
{
	CreateTradingDay();
	CreateExchange();
	CreateProduct();
	CreateHotInstrument();
	CreateInstrument();
	CreateDepthMarketData();
	CreateBarMarketData();
	CreateMdUser();
	CreatePrimaryAccount();
	CreateAccount();
	CreateCapital();
	CreatePosition();
	CreatePositionDetail();
	CreateOrder();
	CreateTrade();
}
void SqliteDB::DropTables()
{
	DropTradingDay();
	DropExchange();
	DropProduct();
	DropHotInstrument();
	DropInstrument();
	DropDepthMarketData();
	DropBarMarketData();
	DropMdUser();
	DropPrimaryAccount();
	DropAccount();
	DropCapital();
	DropPosition();
	DropPositionDetail();
	DropOrder();
	DropTrade();
}
void SqliteDB::TruncateTables()
{
	TruncateTradingDay();
	TruncateExchange();
	TruncateProduct();
	TruncateHotInstrument();
	TruncateDepthMarketData();
	TruncateBarMarketData();
	TruncateMdUser();
	TruncatePrimaryAccount();
	TruncateAccount();
	TruncateCapital();
	TruncatePosition();
	TruncatePositionDetail();
	TruncateOrder();
	TruncateTrade();
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_TradingDay(`PK` int, `CurrTradingDay` text, `PreTradingDay` text, PRIMARY KEY(PK));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateTradingDay failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTradingDay Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropTradingDay()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_TradingDay;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropTradingDay failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTradingDay Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::CreateProduct()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Product(`ExchangeID` text, `ProductID` text, `ProductName` text, `ProductClass` int, `VolumeMultiple` int, `PriceTick` double, `MaxMarketOrderVolume` bigint, `MinMarketOrderVolume` bigint, `MaxLimitOrderVolume` bigint, `MinLimitOrderVolume` bigint, `SessionName` text, PRIMARY KEY(ExchangeID, ProductID));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateProduct failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateProduct Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropProduct()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_Product;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropProduct failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropProduct Spend:%lldms, sql:%s", duration, sql);
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_HotInstrument(`TradingDay` text, `ExchangeID` text, `ProductID` text, `InstrumentID` text, `ProductClass` int, `Volume` bigint, `MaxVolume` bigint, `Turnover` double, `MaxTurnover` double, `OpenInterest` double, `MaxOpenInterest` double, `Rank` int, PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank));CREATE INDEX IF NOT EXISTS HotInstrumentTradingDay ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateHotInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateHotInstrument Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropHotInstrument()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX HotInstrumentTradingDay;DROP TABLE IF EXISTS t_HotInstrument;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropHotInstrument failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropHotInstrument Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::CreatePrimaryAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_PrimaryAccount(`PrimaryAccountID` text, `PrimaryAccountName` text, `AccountClass` int, `Password` text, `OfferID` int, `IsAllowLogin` int, `IsSimulateAccount` int, `LoginStatus` int, `InitStatus` int, PRIMARY KEY(PrimaryAccountID));CREATE INDEX IF NOT EXISTS PrimaryAccountOfferID ON t_PrimaryAccount(OfferID);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreatePrimaryAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePrimaryAccount Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropPrimaryAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX PrimaryAccountOfferID;DROP TABLE IF EXISTS t_PrimaryAccount;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropPrimaryAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPrimaryAccount Spend:%lldms, sql:%s", duration, sql);
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
		sqlite3_prepare_v2(m_DB, "update t_PrimaryAccount set PrimaryAccountName = ?, AccountClass = ?, Password = ?, OfferID = ?, IsAllowLogin = ?, IsSimulateAccount = ?, LoginStatus = ?, InitStatus = ? where PrimaryAccountID = ?;", -1, &m_PrimaryAccountUpdateStatement, nullptr);
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Account(`AccountID` text, `AccountName` text, `AccountType` int, `AccountStatus` int, `Password` text, `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, PRIMARY KEY(AccountID));";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateAccount Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropAccount()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP TABLE IF EXISTS t_Account;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropAccount failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropAccount Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::CreateCapital()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Capital(`TradingDay` text, `AccountID` text, `AccountType` int, `Balance` double, `PreBalance` double, `Available` double, `MarketValue` double, `CashIn` double, `CashOut` double, `Margin` double, `Commission` double, `FrozenCash` double, `FrozenMargin` double, `FrozenCommission` double, `CloseProfitByDate` double, `CloseProfitByTrade` double, `PositionProfitByDate` double, `PositionProfitByTrade` double, `Deposit` double, `Withdraw` double, PRIMARY KEY(TradingDay, AccountID));CREATE INDEX IF NOT EXISTS CapitalTradingDay ON t_Capital(TradingDay);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateCapital failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateCapital Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropCapital()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX CapitalTradingDay;DROP TABLE IF EXISTS t_Capital;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropCapital failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropCapital Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Capital Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_CapitalInsertStatement, nullptr);
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
		sqlite3_prepare_v2(m_DB, "delete from t_Capital where TradingDay = ? and AccountID = ?;", -1, &m_CapitalDeleteStatement, nullptr);
	}
	SetStatementForCapitalPrimaryKey(m_CapitalDeleteStatement, record->TradingDay, record->AccountID);

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
void SqliteDB::DeleteCapitalByTradingDayIndex(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalDeleteByTradingDayIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Capital where TradingDay = ?;", -1, &m_CapitalDeleteByTradingDayIndexStatement, nullptr);
	}
	SetStatementForCapitalIndexTradingDay(m_CapitalDeleteByTradingDayIndexStatement, record);
	
	auto rc = sqlite3_step(m_CapitalDeleteByTradingDayIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteCapitalByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_CapitalDeleteByTradingDayIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteCapitalByTradingDayIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdateCapital(Capital* record)
{
	auto start = steady_clock::now();
	if (m_CapitalUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Capital set AccountType = ?, Balance = ?, PreBalance = ?, Available = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, Deposit = ?, Withdraw = ? where TradingDay = ? and AccountID = ?;", -1, &m_CapitalUpdateStatement, nullptr);
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
void SqliteDB::SelectCapital(std::list<Capital*>& records)
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
void SqliteDB::CreatePosition()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Position(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `PosiDirection` int, `TotalPosition` bigint, `PositionFrozen` bigint, `TodayPosition` bigint, `MarketValue` double, `CashIn` double, `CashOut` double, `Margin` double, `Commission` double, `FrozenCash` double, `FrozenMargin` double, `FrozenCommission` double, `VolumeMultiple` int, `CloseProfitByDate` double, `CloseProfitByTrade` double, `PositionProfitByDate` double, `PositionProfitByTrade` double, `SettlementPrice` double, `PreSettlementPrice` double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection));CREATE INDEX IF NOT EXISTS PositionAccount ON t_Position(TradingDay, AccountID);CREATE INDEX IF NOT EXISTS PositionTradingDay ON t_Position(TradingDay);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreatePosition failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePosition Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropPosition()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX PositionAccount;DROP INDEX PositionTradingDay;DROP TABLE IF EXISTS t_Position;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropPosition failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPosition Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertPosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_Position Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_PositionInsertStatement, nullptr);
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
void SqliteDB::DeletePositionByTradingDayIndex(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionDeleteByTradingDayIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Position where TradingDay = ?;", -1, &m_PositionDeleteByTradingDayIndexStatement, nullptr);
	}
	SetStatementForPositionIndexTradingDay(m_PositionDeleteByTradingDayIndexStatement, record);
	
	auto rc = sqlite3_step(m_PositionDeleteByTradingDayIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDeleteByTradingDayIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionByTradingDayIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdatePosition(Position* record)
{
	auto start = steady_clock::now();
	if (m_PositionUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_Position set AccountType = ?, ProductClass = ?, TotalPosition = ?, PositionFrozen = ?, TodayPosition = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, FrozenCash = ?, FrozenMargin = ?, FrozenCommission = ?, VolumeMultiple = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, SettlementPrice = ?, PreSettlementPrice = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", -1, &m_PositionUpdateStatement, nullptr);
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
void SqliteDB::SelectPosition(std::list<Position*>& records)
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
void SqliteDB::CreatePositionDetail()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_PositionDetail(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `PosiDirection` int, `OpenDate` text, `TradeID` text, `Volume` bigint, `OpenPrice` double, `MarketValue` double, `CashIn` double, `CashOut` double, `Margin` double, `Commission` double, `VolumeMultiple` int, `CloseProfitByDate` double, `CloseProfitByTrade` double, `PositionProfitByDate` double, `PositionProfitByTrade` double, `SettlementPrice` double, `PreSettlementPrice` double, `CloseVolume` bigint, `CloseAmount` double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID));CREATE INDEX IF NOT EXISTS PositionDetailTradeMatch ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);CREATE INDEX IF NOT EXISTS PositionDetailTradingDay ON t_PositionDetail(TradingDay);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreatePositionDetail failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreatePositionDetail Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropPositionDetail()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX PositionDetailTradeMatch;DROP INDEX PositionDetailTradingDay;DROP TABLE IF EXISTS t_PositionDetail;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropPositionDetail failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropPositionDetail Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::InsertPositionDetail(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailInsertStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "insert into t_PositionDetail Values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", -1, &m_PositionDetailInsertStatement, nullptr);
	}
	SetStatementForPositionDetailRecord(m_PositionDetailInsertStatement, record);
	
	auto rc = sqlite3_step(m_PositionDetailInsertStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "InsertPositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailInsertStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "InsertPositionDetail Spend:%lldms", duration);
	}
}
void SqliteDB::BatchInsertPositionDetail(std::list<PositionDetail*>* records)
{
	auto start = steady_clock::now();
	memset(m_SqlBuff, 0, BuffSize);
	strcpy(m_SqlBuff, "Insert into t_PositionDetail Values");
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
				WriteLog(LogLevel::Warning, "BatchInsertPositionDetail Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
				sqlite3_free(t_ErrorMsg);
				return;
			}
			
			memset(m_SqlBuff, 0, BuffSize);
			strcpy(m_SqlBuff, "Insert into t_PositionDetail Values");
			n = (int)strlen(m_SqlBuff);
		}
		n += (*it)->GetSqlString(m_SqlBuff + n);
	}
	m_SqlBuff[n - 1] = ';';

	auto ret = sqlite3_exec(m_DB, m_SqlBuff, nullptr, nullptr, &t_ErrorMsg);
	if (ret != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "BatchInsertPositionDetail Failed. Error: %s, Sql:[%s]", t_ErrorMsg, m_SqlBuff);
		sqlite3_free(t_ErrorMsg);
		return;
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Warning, "BatchInsertPositionDetail RecordSize:%lld, Spend:%lldms", records->size(), duration);
}
void SqliteDB::DeletePositionDetail(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PositionDetail where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ? and OpenDate = ? and TradeID = ?;", -1, &m_PositionDetailDeleteStatement, nullptr);
	}
	SetStatementForPositionDetailPrimaryKey(m_PositionDetailDeleteStatement, record->TradingDay, record->AccountID, record->ExchangeID, record->InstrumentID, record->PosiDirection, record->OpenDate, record->TradeID);

	auto rc = sqlite3_step(m_PositionDetailDeleteStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailDeleteStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetail Spend:%lldms", duration);
	}
}
void SqliteDB::DeletePositionDetailByTradeMatchIndex(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteByTradeMatchIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PositionDetail where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ?;", -1, &m_PositionDetailDeleteByTradeMatchIndexStatement, nullptr);
	}
	SetStatementForPositionDetailIndexTradeMatch(m_PositionDetailDeleteByTradeMatchIndexStatement, record);
	
	auto rc = sqlite3_step(m_PositionDetailDeleteByTradeMatchIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradeMatchIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailDeleteByTradeMatchIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradeMatchIndex Spend:%lldms", duration);
	}
}
void SqliteDB::DeletePositionDetailByTradingDayIndex(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailDeleteByTradingDayIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PositionDetail where TradingDay = ?;", -1, &m_PositionDetailDeleteByTradingDayIndexStatement, nullptr);
	}
	SetStatementForPositionDetailIndexTradingDay(m_PositionDetailDeleteByTradingDayIndexStatement, record);
	
	auto rc = sqlite3_step(m_PositionDetailDeleteByTradingDayIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradingDayIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailDeleteByTradingDayIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeletePositionDetailByTradingDayIndex Spend:%lldms", duration);
	}
}
void SqliteDB::UpdatePositionDetail(PositionDetail* record)
{
	auto start = steady_clock::now();
	if (m_PositionDetailUpdateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "update t_PositionDetail set AccountType = ?, ProductClass = ?, Volume = ?, OpenPrice = ?, MarketValue = ?, CashIn = ?, CashOut = ?, Margin = ?, Commission = ?, VolumeMultiple = ?, CloseProfitByDate = ?, CloseProfitByTrade = ?, PositionProfitByDate = ?, PositionProfitByTrade = ?, SettlementPrice = ?, PreSettlementPrice = ?, CloseVolume = ?, CloseAmount = ? where TradingDay = ? and AccountID = ? and ExchangeID = ? and InstrumentID = ? and PosiDirection = ? and OpenDate = ? and TradeID = ?;", -1, &m_PositionDetailUpdateStatement, nullptr);
	}
	SetStatementForPositionDetailRecordUpdate(m_PositionDetailUpdateStatement, record);
	
	auto rc = sqlite3_step(m_PositionDetailUpdateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "UpdatePositionDetail failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailUpdateStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "UpdatePositionDetail Spend:%lldms", duration);
	}
}
void SqliteDB::SelectPositionDetail(std::list<PositionDetail*>& records)
{
	auto start = steady_clock::now();
	if (m_PositionDetailSelectStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "select * from t_PositionDetail;", -1, &m_PositionDetailSelectStatement, nullptr);
	}

	while (sqlite3_step(m_PositionDetailSelectStatement) == SQLITE_ROW)
	{
		ParseRecord(m_PositionDetailSelectStatement, records);
	}
	sqlite3_reset(m_PositionDetailSelectStatement);
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "SelectPositionDetail Spend:%lldms", duration);
	}
}
void SqliteDB::TruncatePositionDetail()
{
	auto start = steady_clock::now();
	if (m_PositionDetailTruncateStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_PositionDetail;", -1, &m_PositionDetailTruncateStatement, nullptr);
	}

	auto rc = sqlite3_step(m_PositionDetailTruncateStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "TruncatePositionDetail failed, ErrorMsg:%s", sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_PositionDetailTruncateStatement);
	
	WriteLog(LogLevel::Info, "TruncatePositionDetail Spend:%lldms", GetDuration<chrono::milliseconds>(start));
}
void SqliteDB::CreateOrder()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Order(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `OrderID` int, `OrderSysID` text, `Direction` int, `OffsetFlag` int, `OrderPriceType` int, `Price` double, `Volume` bigint, `VolumeTotal` bigint, `VolumeTraded` bigint, `VolumeMultiple` int, `OrderStatus` int, `OrderDate` text, `OrderTime` text, `CancelDate` text, `CancelTime` text, `SessionID` bigint, `ClientOrderID` int, `RequestID` int, `OfferID` int, `TradeGroupID` int, `RiskGroupID` int, `CommissionGroupID` int, `FrozenCash` double, `FrozenMargin` double, `FrozenCommission` double, `RebuildMark` int, `IsForceClose` int, UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID));CREATE INDEX IF NOT EXISTS OrderAccountID ON t_Order(TradingDay, AccountID);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateOrder failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateOrder Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropOrder()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX OrderAccountID;DROP TABLE IF EXISTS t_Order;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropOrder failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropOrder Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::DeleteOrderByAccountIDIndex(Order* record)
{
	auto start = steady_clock::now();
	if (m_OrderDeleteByAccountIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Order where TradingDay = ? and AccountID = ?;", -1, &m_OrderDeleteByAccountIDIndexStatement, nullptr);
	}
	SetStatementForOrderIndexAccountID(m_OrderDeleteByAccountIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_OrderDeleteByAccountIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteOrderByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_OrderDeleteByAccountIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteOrderByAccountIDIndex Spend:%lldms", duration);
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
	const char* sql = "CREATE TABLE IF NOT EXISTS t_Trade(`TradingDay` text, `AccountID` text, `AccountType` int, `ExchangeID` text, `InstrumentID` text, `ProductClass` int, `OrderID` int, `OrderSysID` text, `TradeID` text, `Direction` int, `OffsetFlag` int, `Price` double, `Volume` bigint, `VolumeMultiple` int, `TradeAmount` double, `Commission` double, `TradeDate` text, `TradeTime` text, PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction));CREATE INDEX IF NOT EXISTS TradeAccountID ON t_Trade(TradingDay, AccountID);";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "CreateTrade failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "CreateTrade Spend:%lldms, sql:%s", duration, sql);
}
void SqliteDB::DropTrade()
{
	auto start = steady_clock::now();
	char* t_ErrorMsg;
	const char* sql = "DROP INDEX TradeAccountID;DROP TABLE IF EXISTS t_Trade;";
	auto rc = sqlite3_exec(m_DB, sql, nullptr, nullptr, &t_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WriteLog(LogLevel::Warning, "DropTrade failed, ErrorMsg:%s", t_ErrorMsg);
		sqlite3_free(t_ErrorMsg);
	}
	
	auto duration = GetDuration<chrono::milliseconds>(start);
	WriteLog(LogLevel::Info, "DropTrade Spend:%lldms, sql:%s", duration, sql);
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
void SqliteDB::DeleteTradeByAccountIDIndex(Trade* record)
{
	auto start = steady_clock::now();
	if (m_TradeDeleteByAccountIDIndexStatement == nullptr)
	{
		sqlite3_prepare_v2(m_DB, "delete from t_Trade where TradingDay = ? and AccountID = ?;", -1, &m_TradeDeleteByAccountIDIndexStatement, nullptr);
	}
	SetStatementForTradeIndexAccountID(m_TradeDeleteByAccountIDIndexStatement, record);
	
	auto rc = sqlite3_step(m_TradeDeleteByAccountIDIndexStatement);
	if (rc != SQLITE_DONE)
	{
		WriteLog(LogLevel::Warning, "DeleteTradeByAccountIDIndex failed: %s, ErrorMsg:%s", record->GetDebugString(), sqlite3_errmsg(m_DB));
	}
	sqlite3_reset(m_TradeDeleteByAccountIDIndexStatement);

	auto duration = GetDuration<chrono::milliseconds>(start);
	if (duration >= 100)
	{
		WriteLog(LogLevel::Warning, "DeleteTradeByAccountIDIndex Spend:%lldms", duration);
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
void SqliteDB::SetStatementForPrimaryAccountRecord(sqlite3_stmt* statement, PrimaryAccount* record)
{
	sqlite3_bind_text(statement, 1, record->PrimaryAccountID, sizeof(record->PrimaryAccountID), nullptr);
	sqlite3_bind_text(statement, 2, record->PrimaryAccountName, sizeof(record->PrimaryAccountName), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountClass));
	sqlite3_bind_text(statement, 4, record->Password, sizeof(record->Password), nullptr);
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
	sqlite3_bind_text(statement, 3, record->Password, sizeof(record->Password), nullptr);
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
	Strcpy(record->Password, (const char*)sqlite3_column_text(statement, 3));
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
void SqliteDB::SetStatementForCapitalRecord(sqlite3_stmt* statement, Capital* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_double(statement, 4, record->Balance);
	sqlite3_bind_double(statement, 5, record->PreBalance);
	sqlite3_bind_double(statement, 6, record->Available);
	sqlite3_bind_double(statement, 7, record->MarketValue);
	sqlite3_bind_double(statement, 8, record->CashIn);
	sqlite3_bind_double(statement, 9, record->CashOut);
	sqlite3_bind_double(statement, 10, record->Margin);
	sqlite3_bind_double(statement, 11, record->Commission);
	sqlite3_bind_double(statement, 12, record->FrozenCash);
	sqlite3_bind_double(statement, 13, record->FrozenMargin);
	sqlite3_bind_double(statement, 14, record->FrozenCommission);
	sqlite3_bind_double(statement, 15, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 16, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 17, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 18, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 19, record->Deposit);
	sqlite3_bind_double(statement, 20, record->Withdraw);
}
void SqliteDB::SetStatementForCapitalRecordUpdate(sqlite3_stmt* statement, Capital* record)
{
	sqlite3_bind_int(statement, 1, int(record->AccountType));
	sqlite3_bind_double(statement, 2, record->Balance);
	sqlite3_bind_double(statement, 3, record->PreBalance);
	sqlite3_bind_double(statement, 4, record->Available);
	sqlite3_bind_double(statement, 5, record->MarketValue);
	sqlite3_bind_double(statement, 6, record->CashIn);
	sqlite3_bind_double(statement, 7, record->CashOut);
	sqlite3_bind_double(statement, 8, record->Margin);
	sqlite3_bind_double(statement, 9, record->Commission);
	sqlite3_bind_double(statement, 10, record->FrozenCash);
	sqlite3_bind_double(statement, 11, record->FrozenMargin);
	sqlite3_bind_double(statement, 12, record->FrozenCommission);
	sqlite3_bind_double(statement, 13, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 14, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 15, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 16, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 17, record->Deposit);
	sqlite3_bind_double(statement, 18, record->Withdraw);
	sqlite3_bind_text(statement, 19, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 20, record->AccountID, sizeof(record->AccountID), nullptr);
}
void SqliteDB::SetStatementForCapitalPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
}
void SqliteDB::SetStatementForCapitalIndexTradingDay(sqlite3_stmt* statement, Capital* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Capital*>& records)
{
	Capital* record = Capital::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	record->Balance = sqlite3_column_double(statement, 3);
	record->PreBalance = sqlite3_column_double(statement, 4);
	record->Available = sqlite3_column_double(statement, 5);
	record->MarketValue = sqlite3_column_double(statement, 6);
	record->CashIn = sqlite3_column_double(statement, 7);
	record->CashOut = sqlite3_column_double(statement, 8);
	record->Margin = sqlite3_column_double(statement, 9);
	record->Commission = sqlite3_column_double(statement, 10);
	record->FrozenCash = sqlite3_column_double(statement, 11);
	record->FrozenMargin = sqlite3_column_double(statement, 12);
	record->FrozenCommission = sqlite3_column_double(statement, 13);
	record->CloseProfitByDate = sqlite3_column_double(statement, 14);
	record->CloseProfitByTrade = sqlite3_column_double(statement, 15);
	record->PositionProfitByDate = sqlite3_column_double(statement, 16);
	record->PositionProfitByTrade = sqlite3_column_double(statement, 17);
	record->Deposit = sqlite3_column_double(statement, 18);
	record->Withdraw = sqlite3_column_double(statement, 19);
	records.push_back(record);
}
void SqliteDB::SetStatementForPositionRecord(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, int(record->PosiDirection));
	sqlite3_bind_int64(statement, 8, record->TotalPosition);
	sqlite3_bind_int64(statement, 9, record->PositionFrozen);
	sqlite3_bind_int64(statement, 10, record->TodayPosition);
	sqlite3_bind_double(statement, 11, record->MarketValue);
	sqlite3_bind_double(statement, 12, record->CashIn);
	sqlite3_bind_double(statement, 13, record->CashOut);
	sqlite3_bind_double(statement, 14, record->Margin);
	sqlite3_bind_double(statement, 15, record->Commission);
	sqlite3_bind_double(statement, 16, record->FrozenCash);
	sqlite3_bind_double(statement, 17, record->FrozenMargin);
	sqlite3_bind_double(statement, 18, record->FrozenCommission);
	sqlite3_bind_int(statement, 19, record->VolumeMultiple);
	sqlite3_bind_double(statement, 20, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 21, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 22, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 23, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 24, record->SettlementPrice);
	sqlite3_bind_double(statement, 25, record->PreSettlementPrice);
}
void SqliteDB::SetStatementForPositionRecordUpdate(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_int(statement, 1, int(record->AccountType));
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_int64(statement, 3, record->TotalPosition);
	sqlite3_bind_int64(statement, 4, record->PositionFrozen);
	sqlite3_bind_int64(statement, 5, record->TodayPosition);
	sqlite3_bind_double(statement, 6, record->MarketValue);
	sqlite3_bind_double(statement, 7, record->CashIn);
	sqlite3_bind_double(statement, 8, record->CashOut);
	sqlite3_bind_double(statement, 9, record->Margin);
	sqlite3_bind_double(statement, 10, record->Commission);
	sqlite3_bind_double(statement, 11, record->FrozenCash);
	sqlite3_bind_double(statement, 12, record->FrozenMargin);
	sqlite3_bind_double(statement, 13, record->FrozenCommission);
	sqlite3_bind_int(statement, 14, record->VolumeMultiple);
	sqlite3_bind_double(statement, 15, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 16, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 17, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 18, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 19, record->SettlementPrice);
	sqlite3_bind_double(statement, 20, record->PreSettlementPrice);
	sqlite3_bind_text(statement, 21, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 22, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 23, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 24, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 25, int(record->PosiDirection));
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
void SqliteDB::SetStatementForPositionIndexTradingDay(sqlite3_stmt* statement, Position* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<Position*>& records)
{
	Position* record = Position::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->PosiDirection = PosiDirectionType(sqlite3_column_int(statement, 6));
	record->TotalPosition = sqlite3_column_int64(statement, 7);
	record->PositionFrozen = sqlite3_column_int64(statement, 8);
	record->TodayPosition = sqlite3_column_int64(statement, 9);
	record->MarketValue = sqlite3_column_double(statement, 10);
	record->CashIn = sqlite3_column_double(statement, 11);
	record->CashOut = sqlite3_column_double(statement, 12);
	record->Margin = sqlite3_column_double(statement, 13);
	record->Commission = sqlite3_column_double(statement, 14);
	record->FrozenCash = sqlite3_column_double(statement, 15);
	record->FrozenMargin = sqlite3_column_double(statement, 16);
	record->FrozenCommission = sqlite3_column_double(statement, 17);
	record->VolumeMultiple = sqlite3_column_int(statement, 18);
	record->CloseProfitByDate = sqlite3_column_double(statement, 19);
	record->CloseProfitByTrade = sqlite3_column_double(statement, 20);
	record->PositionProfitByDate = sqlite3_column_double(statement, 21);
	record->PositionProfitByTrade = sqlite3_column_double(statement, 22);
	record->SettlementPrice = sqlite3_column_double(statement, 23);
	record->PreSettlementPrice = sqlite3_column_double(statement, 24);
	records.push_back(record);
}
void SqliteDB::SetStatementForPositionDetailRecord(sqlite3_stmt* statement, PositionDetail* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_int(statement, 3, int(record->AccountType));
	sqlite3_bind_text(statement, 4, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 5, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 6, int(record->ProductClass));
	sqlite3_bind_int(statement, 7, int(record->PosiDirection));
	sqlite3_bind_text(statement, 8, record->OpenDate, sizeof(record->OpenDate), nullptr);
	sqlite3_bind_text(statement, 9, record->TradeID, sizeof(record->TradeID), nullptr);
	sqlite3_bind_int64(statement, 10, record->Volume);
	sqlite3_bind_double(statement, 11, record->OpenPrice);
	sqlite3_bind_double(statement, 12, record->MarketValue);
	sqlite3_bind_double(statement, 13, record->CashIn);
	sqlite3_bind_double(statement, 14, record->CashOut);
	sqlite3_bind_double(statement, 15, record->Margin);
	sqlite3_bind_double(statement, 16, record->Commission);
	sqlite3_bind_int(statement, 17, record->VolumeMultiple);
	sqlite3_bind_double(statement, 18, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 19, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 20, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 21, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 22, record->SettlementPrice);
	sqlite3_bind_double(statement, 23, record->PreSettlementPrice);
	sqlite3_bind_int64(statement, 24, record->CloseVolume);
	sqlite3_bind_double(statement, 25, record->CloseAmount);
}
void SqliteDB::SetStatementForPositionDetailRecordUpdate(sqlite3_stmt* statement, PositionDetail* record)
{
	sqlite3_bind_int(statement, 1, int(record->AccountType));
	sqlite3_bind_int(statement, 2, int(record->ProductClass));
	sqlite3_bind_int64(statement, 3, record->Volume);
	sqlite3_bind_double(statement, 4, record->OpenPrice);
	sqlite3_bind_double(statement, 5, record->MarketValue);
	sqlite3_bind_double(statement, 6, record->CashIn);
	sqlite3_bind_double(statement, 7, record->CashOut);
	sqlite3_bind_double(statement, 8, record->Margin);
	sqlite3_bind_double(statement, 9, record->Commission);
	sqlite3_bind_int(statement, 10, record->VolumeMultiple);
	sqlite3_bind_double(statement, 11, record->CloseProfitByDate);
	sqlite3_bind_double(statement, 12, record->CloseProfitByTrade);
	sqlite3_bind_double(statement, 13, record->PositionProfitByDate);
	sqlite3_bind_double(statement, 14, record->PositionProfitByTrade);
	sqlite3_bind_double(statement, 15, record->SettlementPrice);
	sqlite3_bind_double(statement, 16, record->PreSettlementPrice);
	sqlite3_bind_int64(statement, 17, record->CloseVolume);
	sqlite3_bind_double(statement, 18, record->CloseAmount);
	sqlite3_bind_text(statement, 19, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 20, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 21, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 22, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 23, int(record->PosiDirection));
	sqlite3_bind_text(statement, 24, record->OpenDate, sizeof(record->OpenDate), nullptr);
	sqlite3_bind_text(statement, 25, record->TradeID, sizeof(record->TradeID), nullptr);
}
void SqliteDB::SetStatementForPositionDetailPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIDType& TradeID)
{
	sqlite3_bind_text(statement, 1, TradingDay, sizeof(TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, AccountID, sizeof(AccountID), nullptr);
	sqlite3_bind_text(statement, 3, ExchangeID, sizeof(ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, InstrumentID, sizeof(InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, int(PosiDirection));
	sqlite3_bind_text(statement, 6, OpenDate, sizeof(OpenDate), nullptr);
	sqlite3_bind_text(statement, 7, TradeID, sizeof(TradeID), nullptr);
}
void SqliteDB::SetStatementForPositionDetailIndexTradeMatch(sqlite3_stmt* statement, PositionDetail* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
	sqlite3_bind_text(statement, 3, record->ExchangeID, sizeof(record->ExchangeID), nullptr);
	sqlite3_bind_text(statement, 4, record->InstrumentID, sizeof(record->InstrumentID), nullptr);
	sqlite3_bind_int(statement, 5, int(record->PosiDirection));
}
void SqliteDB::SetStatementForPositionDetailIndexTradingDay(sqlite3_stmt* statement, PositionDetail* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
}
void SqliteDB::ParseRecord(sqlite3_stmt* statement, std::list<PositionDetail*>& records)
{
	PositionDetail* record = PositionDetail::Allocate();
	Strcpy(record->TradingDay, (const char*)sqlite3_column_text(statement, 0));
	Strcpy(record->AccountID, (const char*)sqlite3_column_text(statement, 1));
	record->AccountType = AccountTypeType(sqlite3_column_int(statement, 2));
	Strcpy(record->ExchangeID, (const char*)sqlite3_column_text(statement, 3));
	Strcpy(record->InstrumentID, (const char*)sqlite3_column_text(statement, 4));
	record->ProductClass = ProductClassType(sqlite3_column_int(statement, 5));
	record->PosiDirection = PosiDirectionType(sqlite3_column_int(statement, 6));
	Strcpy(record->OpenDate, (const char*)sqlite3_column_text(statement, 7));
	Strcpy(record->TradeID, (const char*)sqlite3_column_text(statement, 8));
	record->Volume = sqlite3_column_int64(statement, 9);
	record->OpenPrice = sqlite3_column_double(statement, 10);
	record->MarketValue = sqlite3_column_double(statement, 11);
	record->CashIn = sqlite3_column_double(statement, 12);
	record->CashOut = sqlite3_column_double(statement, 13);
	record->Margin = sqlite3_column_double(statement, 14);
	record->Commission = sqlite3_column_double(statement, 15);
	record->VolumeMultiple = sqlite3_column_int(statement, 16);
	record->CloseProfitByDate = sqlite3_column_double(statement, 17);
	record->CloseProfitByTrade = sqlite3_column_double(statement, 18);
	record->PositionProfitByDate = sqlite3_column_double(statement, 19);
	record->PositionProfitByTrade = sqlite3_column_double(statement, 20);
	record->SettlementPrice = sqlite3_column_double(statement, 21);
	record->PreSettlementPrice = sqlite3_column_double(statement, 22);
	record->CloseVolume = sqlite3_column_int64(statement, 23);
	record->CloseAmount = sqlite3_column_double(statement, 24);
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
void SqliteDB::SetStatementForOrderIndexAccountID(sqlite3_stmt* statement, Order* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
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
void SqliteDB::SetStatementForTradeIndexAccountID(sqlite3_stmt* statement, Trade* record)
{
	sqlite3_bind_text(statement, 1, record->TradingDay, sizeof(record->TradingDay), nullptr);
	sqlite3_bind_text(statement, 2, record->AccountID, sizeof(record->AccountID), nullptr);
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

