#pragma once
#include "DB.h"
#include "duckdb.hpp"
#include <string>
#include <vector>
#include <list>


class DuckDB : public DB
{
public:
	DuckDB(const std::string& dbName);
	~DuckDB();
	virtual bool Connect() override;
	virtual void DisConnect() override;
	virtual void InitDB() override;
	virtual void TruncateSessionTables() override;
	virtual void TruncateTables() override;
	
	bool Exec(const char* sql);
	virtual void InsertTradingDay(mdb::TradingDay* record) override;
	virtual void DeleteTradingDay(mdb::TradingDay* record) override;
	virtual void UpdateTradingDay(mdb::TradingDay* record) override;
	virtual void ReplaceTradingDay(mdb::TradingDay* record) override;
	virtual void SelectTradingDay(std::vector<mdb::TradingDay*>& records) override;
	virtual void TruncateTradingDay() override;
	
	virtual void InsertExchange(mdb::Exchange* record) override;
	virtual void DeleteExchange(mdb::Exchange* record) override;
	virtual void UpdateExchange(mdb::Exchange* record) override;
	virtual void ReplaceExchange(mdb::Exchange* record) override;
	virtual void BatchUpdateExchange(std::list<mdb::Exchange*>* records) override;
	virtual void SelectExchange(std::vector<mdb::Exchange*>& records) override;
	virtual void TruncateExchange() override;
	
	virtual void InsertProduct(mdb::Product* record) override;
	virtual void DeleteProduct(mdb::Product* record) override;
	virtual void UpdateProduct(mdb::Product* record) override;
	virtual void ReplaceProduct(mdb::Product* record) override;
	virtual void SelectProduct(std::vector<mdb::Product*>& records) override;
	virtual void TruncateProduct() override;
	
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void ReplaceInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::vector<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	
	virtual void InsertAccount(mdb::Account* record) override;
	virtual void DeleteAccount(mdb::Account* record) override;
	virtual void UpdateAccount(mdb::Account* record) override;
	virtual void ReplaceAccount(mdb::Account* record) override;
	virtual void SelectAccount(std::vector<mdb::Account*>& records) override;
	virtual void TruncateAccount() override;
	
	virtual void InsertPosition(mdb::Position* record) override;
	virtual void DeletePosition(mdb::Position* record) override;
	virtual void DeletePositionByAccountIndex(mdb::Position* record) override;
	virtual void UpdatePosition(mdb::Position* record) override;
	virtual void ReplacePosition(mdb::Position* record) override;
	virtual void SelectPosition(std::vector<mdb::Position*>& records) override;
	virtual void TruncatePosition() override;
	
	virtual void InsertOrder(mdb::Order* record) override;
	virtual void DeleteOrder(mdb::Order* record) override;
	virtual void UpdateOrder(mdb::Order* record) override;
	virtual void ReplaceOrder(mdb::Order* record) override;
	virtual void SelectOrder(std::vector<mdb::Order*>& records) override;
	virtual void TruncateOrder() override;
	
	virtual void InsertTrade(mdb::Trade* record) override;
	virtual void DeleteTrade(mdb::Trade* record) override;
	virtual void UpdateTrade(mdb::Trade* record) override;
	virtual void ReplaceTrade(mdb::Trade* record) override;
	virtual void SelectTrade(std::vector<mdb::Trade*>& records) override;
	virtual void TruncateTrade() override;
	
	virtual void InsertMdTick(mdb::MdTick* record) override;
	virtual void DeleteMdTick(mdb::MdTick* record) override;
	virtual void UpdateMdTick(mdb::MdTick* record) override;
	virtual void ReplaceMdTick(mdb::MdTick* record) override;
	virtual void SelectMdTick(std::vector<mdb::MdTick*>& records) override;
	virtual void TruncateMdTick() override;
	

private:
	void SetStatementForTradingDayRecord(duckdb_prepared_statement statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(duckdb_prepared_statement statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(duckdb_prepared_statement statement, mdb::TradingDay* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::TradingDay*>& records);
	void SetStatementForExchangeRecord(duckdb_prepared_statement statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(duckdb_prepared_statement statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(duckdb_prepared_statement statement, mdb::Exchange* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Exchange*>& records);
	void SetStatementForProductRecord(duckdb_prepared_statement statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(duckdb_prepared_statement statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(duckdb_prepared_statement statement, mdb::Product* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Product*>& records);
	void SetStatementForInstrumentRecord(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(duckdb_prepared_statement statement, mdb::Instrument* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Instrument*>& records);
	void SetStatementForAccountRecord(duckdb_prepared_statement statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(duckdb_prepared_statement statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(duckdb_prepared_statement statement, mdb::Account* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Account*>& records);
	void SetStatementForPositionRecord(duckdb_prepared_statement statement, mdb::Position* record);
	void SetStatementForPositionRecordUpdate(duckdb_prepared_statement statement, mdb::Position* record);
	void SetStatementForPositionPrimaryKey(duckdb_prepared_statement statement, mdb::Position* record);
	void SetStatementForPositionIndexAccount(duckdb_prepared_statement statement, mdb::Position* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Position*>& records);
	void SetStatementForOrderRecord(duckdb_prepared_statement statement, mdb::Order* record);
	void SetStatementForOrderRecordUpdate(duckdb_prepared_statement statement, mdb::Order* record);
	void SetStatementForOrderPrimaryKey(duckdb_prepared_statement statement, mdb::Order* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Order*>& records);
	void SetStatementForTradeRecord(duckdb_prepared_statement statement, mdb::Trade* record);
	void SetStatementForTradeRecordUpdate(duckdb_prepared_statement statement, mdb::Trade* record);
	void SetStatementForTradePrimaryKey(duckdb_prepared_statement statement, mdb::Trade* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::Trade*>& records);
	void SetStatementForMdTickRecord(duckdb_prepared_statement statement, mdb::MdTick* record);
	void SetStatementForMdTickRecordUpdate(duckdb_prepared_statement statement, mdb::MdTick* record);
	void SetStatementForMdTickPrimaryKey(duckdb_prepared_statement statement, mdb::MdTick* record);
	void ParseRecord(duckdb_result& result, std::vector<mdb::MdTick*>& records);


private:
	std::string m_DBName;
	duckdb_database m_DB;
	duckdb_connection m_Connection;
	char* m_SqlBuff;

	duckdb_appender m_TradingDayAppender;
	duckdb_prepared_statement m_TradingDayDeleteStatement;
	duckdb_prepared_statement m_TradingDayUpdateStatement;
	duckdb_prepared_statement m_TradingDayReplaceStatement;
	duckdb_prepared_statement m_TradingDaySelectStatement;
	duckdb_prepared_statement m_TradingDayTruncateStatement;
	duckdb_appender m_ExchangeAppender;
	duckdb_prepared_statement m_ExchangeDeleteStatement;
	duckdb_prepared_statement m_ExchangeUpdateStatement;
	duckdb_prepared_statement m_ExchangeReplaceStatement;
	duckdb_prepared_statement m_ExchangeSelectStatement;
	duckdb_prepared_statement m_ExchangeTruncateStatement;
	duckdb_appender m_ProductAppender;
	duckdb_prepared_statement m_ProductDeleteStatement;
	duckdb_prepared_statement m_ProductUpdateStatement;
	duckdb_prepared_statement m_ProductReplaceStatement;
	duckdb_prepared_statement m_ProductSelectStatement;
	duckdb_prepared_statement m_ProductTruncateStatement;
	duckdb_appender m_InstrumentAppender;
	duckdb_prepared_statement m_InstrumentDeleteStatement;
	duckdb_prepared_statement m_InstrumentUpdateStatement;
	duckdb_prepared_statement m_InstrumentReplaceStatement;
	duckdb_prepared_statement m_InstrumentSelectStatement;
	duckdb_prepared_statement m_InstrumentTruncateStatement;
	duckdb_appender m_AccountAppender;
	duckdb_prepared_statement m_AccountDeleteStatement;
	duckdb_prepared_statement m_AccountUpdateStatement;
	duckdb_prepared_statement m_AccountReplaceStatement;
	duckdb_prepared_statement m_AccountSelectStatement;
	duckdb_prepared_statement m_AccountTruncateStatement;
	duckdb_appender m_PositionAppender;
	duckdb_prepared_statement m_PositionDeleteStatement;
	duckdb_prepared_statement m_PositionDeleteByAccountIndexStatement;
	duckdb_prepared_statement m_PositionUpdateStatement;
	duckdb_prepared_statement m_PositionReplaceStatement;
	duckdb_prepared_statement m_PositionSelectStatement;
	duckdb_prepared_statement m_PositionTruncateStatement;
	duckdb_appender m_OrderAppender;
	duckdb_prepared_statement m_OrderDeleteStatement;
	duckdb_prepared_statement m_OrderUpdateStatement;
	duckdb_prepared_statement m_OrderReplaceStatement;
	duckdb_prepared_statement m_OrderSelectStatement;
	duckdb_prepared_statement m_OrderTruncateStatement;
	duckdb_appender m_TradeAppender;
	duckdb_prepared_statement m_TradeDeleteStatement;
	duckdb_prepared_statement m_TradeUpdateStatement;
	duckdb_prepared_statement m_TradeReplaceStatement;
	duckdb_prepared_statement m_TradeSelectStatement;
	duckdb_prepared_statement m_TradeTruncateStatement;
	duckdb_appender m_MdTickAppender;
	duckdb_prepared_statement m_MdTickDeleteStatement;
	duckdb_prepared_statement m_MdTickUpdateStatement;
	duckdb_prepared_statement m_MdTickReplaceStatement;
	duckdb_prepared_statement m_MdTickSelectStatement;
	duckdb_prepared_statement m_MdTickTruncateStatement;
};
