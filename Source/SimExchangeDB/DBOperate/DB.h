#pragma once
#include "MdbStructs.h"
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_error.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <string>
#include <vector>
#include <list>


class DB
{
public:
	DB(const std::string& host, const std::string& user, const std::string& passwd);
	~DB();
	bool Connect();
	void DisConnect();
	void TruncateTables();
	
	template<typename T>
	void CustomSelectSql(const char* sql, std::vector<T*>& records)
	{
		if (m_Statement == nullptr)
		{
			m_Statement = m_DBConnection->createStatement();
		}
		auto result = m_Statement->executeQuery(sql);
		while (result->next())
		{
			ParseRecord(result, records);
		}
	}
	inline void CustomExecuteSql(const char* sql)
	{
		if (m_Statement == nullptr)
		{
			m_Statement = m_DBConnection->createStatement();
		}
		m_Statement->executeUpdate(sql);
	}
	
	void InsertTradingDay(mdb::TradingDay* record);
	void DeleteTradingDay(mdb::TradingDay* record);
	void UpdateTradingDay(mdb::TradingDay* record);
	void ReplaceTradingDay(mdb::TradingDay* record);
	void SelectTradingDay(std::vector<mdb::TradingDay*>& records);
	void TruncateTradingDay();
	
	void InsertExchange(mdb::Exchange* record);
	void DeleteExchange(mdb::Exchange* record);
	void UpdateExchange(mdb::Exchange* record);
	void ReplaceExchange(mdb::Exchange* record);
	void SelectExchange(std::vector<mdb::Exchange*>& records);
	void TruncateExchange();
	
	void InsertProduct(mdb::Product* record);
	void DeleteProduct(mdb::Product* record);
	void UpdateProduct(mdb::Product* record);
	void ReplaceProduct(mdb::Product* record);
	void SelectProduct(std::vector<mdb::Product*>& records);
	void TruncateProduct();
	
	void InsertInstrument(mdb::Instrument* record);
	void DeleteInstrument(mdb::Instrument* record);
	void UpdateInstrument(mdb::Instrument* record);
	void ReplaceInstrument(mdb::Instrument* record);
	void SelectInstrument(std::vector<mdb::Instrument*>& records);
	void TruncateInstrument();
	
	void InsertAccount(mdb::Account* record);
	void DeleteAccount(mdb::Account* record);
	void UpdateAccount(mdb::Account* record);
	void ReplaceAccount(mdb::Account* record);
	void SelectAccount(std::vector<mdb::Account*>& records);
	void TruncateAccount();
	
	void InsertPosition(mdb::Position* record);
	void DeletePosition(mdb::Position* record);
	void UpdatePosition(mdb::Position* record);
	void ReplacePosition(mdb::Position* record);
	void SelectPosition(std::vector<mdb::Position*>& records);
	void TruncatePosition();
	
	void InsertOrder(mdb::Order* record);
	void DeleteOrder(mdb::Order* record);
	void UpdateOrder(mdb::Order* record);
	void ReplaceOrder(mdb::Order* record);
	void SelectOrder(std::vector<mdb::Order*>& records);
	void TruncateOrder();
	
	void InsertTrade(mdb::Trade* record);
	void DeleteTrade(mdb::Trade* record);
	void UpdateTrade(mdb::Trade* record);
	void ReplaceTrade(mdb::Trade* record);
	void SelectTrade(std::vector<mdb::Trade*>& records);
	void TruncateTrade();
	
	void InsertMdTick(mdb::MdTick* record);
	void DeleteMdTick(mdb::MdTick* record);
	void UpdateMdTick(mdb::MdTick* record);
	void ReplaceMdTick(mdb::MdTick* record);
	void SelectMdTick(std::vector<mdb::MdTick*>& records);
	void TruncateMdTick();
	

private:
	void SetStatementForTradingDayRecord(sql::PreparedStatement* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(sql::PreparedStatement* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(sql::PreparedStatement* statement, const IntType& PK);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::TradingDay*>& records);
	void SetStatementForExchangeRecord(sql::PreparedStatement* statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(sql::PreparedStatement* statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Exchange*>& records);
	void SetStatementForProductRecord(sql::PreparedStatement* statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(sql::PreparedStatement* statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Product*>& records);
	void SetStatementForInstrumentRecord(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Instrument*>& records);
	void SetStatementForAccountRecord(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Account*>& records);
	void SetStatementForPositionRecord(sql::PreparedStatement* statement, mdb::Position* record);
	void SetStatementForPositionRecordUpdate(sql::PreparedStatement* statement, mdb::Position* record);
	void SetStatementForPositionPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Position*>& records);
	void SetStatementForOrderRecord(sql::PreparedStatement* statement, mdb::Order* record);
	void SetStatementForOrderRecordUpdate(sql::PreparedStatement* statement, mdb::Order* record);
	void SetStatementForOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Order*>& records);
	void SetStatementForTradeRecord(sql::PreparedStatement* statement, mdb::Trade* record);
	void SetStatementForTradeRecordUpdate(sql::PreparedStatement* statement, mdb::Trade* record);
	void SetStatementForTradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::Trade*>& records);
	void SetStatementForMdTickRecord(sql::PreparedStatement* statement, mdb::MdTick* record);
	void SetStatementForMdTickRecordUpdate(sql::PreparedStatement* statement, mdb::MdTick* record);
	void SetStatementForMdTickPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sql::ResultSet* result, std::vector<mdb::MdTick*>& records);


private:
	sql::Driver* m_Driver;
	sql::Connection* m_DBConnection;
	sql::Statement* m_Statement;

	std::string m_Host;
	std::string m_User;
	std::string m_Passwd;
	char* m_SqlBuff;

	sql::PreparedStatement* m_TradingDayInsertStatement;
	sql::PreparedStatement* m_TradingDayDeleteStatement;
	sql::PreparedStatement* m_TradingDayUpdateStatement;
	sql::PreparedStatement* m_TradingDayReplaceStatement;
	sql::PreparedStatement* m_TradingDaySelectStatement;
	sql::PreparedStatement* m_TradingDayTruncateStatement;
	sql::PreparedStatement* m_ExchangeInsertStatement;
	sql::PreparedStatement* m_ExchangeDeleteStatement;
	sql::PreparedStatement* m_ExchangeUpdateStatement;
	sql::PreparedStatement* m_ExchangeReplaceStatement;
	sql::PreparedStatement* m_ExchangeSelectStatement;
	sql::PreparedStatement* m_ExchangeTruncateStatement;
	sql::PreparedStatement* m_ProductInsertStatement;
	sql::PreparedStatement* m_ProductDeleteStatement;
	sql::PreparedStatement* m_ProductUpdateStatement;
	sql::PreparedStatement* m_ProductReplaceStatement;
	sql::PreparedStatement* m_ProductSelectStatement;
	sql::PreparedStatement* m_ProductTruncateStatement;
	sql::PreparedStatement* m_InstrumentInsertStatement;
	sql::PreparedStatement* m_InstrumentDeleteStatement;
	sql::PreparedStatement* m_InstrumentUpdateStatement;
	sql::PreparedStatement* m_InstrumentReplaceStatement;
	sql::PreparedStatement* m_InstrumentSelectStatement;
	sql::PreparedStatement* m_InstrumentTruncateStatement;
	sql::PreparedStatement* m_AccountInsertStatement;
	sql::PreparedStatement* m_AccountDeleteStatement;
	sql::PreparedStatement* m_AccountUpdateStatement;
	sql::PreparedStatement* m_AccountReplaceStatement;
	sql::PreparedStatement* m_AccountSelectStatement;
	sql::PreparedStatement* m_AccountTruncateStatement;
	sql::PreparedStatement* m_PositionInsertStatement;
	sql::PreparedStatement* m_PositionDeleteStatement;
	sql::PreparedStatement* m_PositionUpdateStatement;
	sql::PreparedStatement* m_PositionReplaceStatement;
	sql::PreparedStatement* m_PositionSelectStatement;
	sql::PreparedStatement* m_PositionTruncateStatement;
	sql::PreparedStatement* m_OrderInsertStatement;
	sql::PreparedStatement* m_OrderDeleteStatement;
	sql::PreparedStatement* m_OrderUpdateStatement;
	sql::PreparedStatement* m_OrderReplaceStatement;
	sql::PreparedStatement* m_OrderSelectStatement;
	sql::PreparedStatement* m_OrderTruncateStatement;
	sql::PreparedStatement* m_TradeInsertStatement;
	sql::PreparedStatement* m_TradeDeleteStatement;
	sql::PreparedStatement* m_TradeUpdateStatement;
	sql::PreparedStatement* m_TradeReplaceStatement;
	sql::PreparedStatement* m_TradeSelectStatement;
	sql::PreparedStatement* m_TradeTruncateStatement;
	sql::PreparedStatement* m_MdTickInsertStatement;
	sql::PreparedStatement* m_MdTickDeleteStatement;
	sql::PreparedStatement* m_MdTickUpdateStatement;
	sql::PreparedStatement* m_MdTickReplaceStatement;
	sql::PreparedStatement* m_MdTickSelectStatement;
	sql::PreparedStatement* m_MdTickTruncateStatement;
};
