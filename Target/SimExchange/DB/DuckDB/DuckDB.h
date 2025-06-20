#pragma once
#include "DB.h"
#include "duckdb.hpp"
#include <string>
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
	
	bool Exec(const char* sql) const;
	virtual void InsertTradingDay(mdb::TradingDay* record) override;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) override;
	virtual void DeleteTradingDay(mdb::TradingDay* record) override;
	virtual void UpdateTradingDay(mdb::TradingDay* record) override;
	virtual void SelectTradingDay(std::list<mdb::TradingDay*>& records) override;
	virtual void TruncateTradingDay() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::TradingDay*>& records);
	
	virtual void InsertExchange(mdb::Exchange* record) override;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) override;
	virtual void DeleteExchange(mdb::Exchange* record) override;
	virtual void UpdateExchange(mdb::Exchange* record) override;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) override;
	virtual void TruncateExchange() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Exchange*>& records);
	
	virtual void InsertProduct(mdb::Product* record) override;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) override;
	virtual void DeleteProduct(mdb::Product* record) override;
	virtual void UpdateProduct(mdb::Product* record) override;
	virtual void SelectProduct(std::list<mdb::Product*>& records) override;
	virtual void TruncateProduct() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Product*>& records);
	
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Instrument*>& records);
	
	virtual void InsertOrder(mdb::Order* record) override;
	virtual void BatchInsertOrder(std::list<mdb::Order*>* records) override;
	virtual void DeleteOrder(mdb::Order* record) override;
	virtual void UpdateOrder(mdb::Order* record) override;
	virtual void SelectOrder(std::list<mdb::Order*>& records) override;
	virtual void TruncateOrder() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Order*>& records);
	
	virtual void InsertTrade(mdb::Trade* record) override;
	virtual void BatchInsertTrade(std::list<mdb::Trade*>* records) override;
	virtual void DeleteTrade(mdb::Trade* record) override;
	virtual void UpdateTrade(mdb::Trade* record) override;
	virtual void SelectTrade(std::list<mdb::Trade*>& records) override;
	virtual void TruncateTrade() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Trade*>& records);
	
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) override;
	virtual void TruncateDepthMarketData() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::DepthMarketData*>& records);
	

private:
	bool AppendForTradingDayRecord(duckdb_appender appender, mdb::TradingDay* record);
	void SetStatementForTradingDayRecord(duckdb_prepared_statement statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(duckdb_prepared_statement statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(duckdb_prepared_statement statement, mdb::TradingDay* record);
	bool AppendForExchangeRecord(duckdb_appender appender, mdb::Exchange* record);
	void SetStatementForExchangeRecord(duckdb_prepared_statement statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(duckdb_prepared_statement statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(duckdb_prepared_statement statement, mdb::Exchange* record);
	bool AppendForProductRecord(duckdb_appender appender, mdb::Product* record);
	void SetStatementForProductRecord(duckdb_prepared_statement statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(duckdb_prepared_statement statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(duckdb_prepared_statement statement, mdb::Product* record);
	bool AppendForInstrumentRecord(duckdb_appender appender, mdb::Instrument* record);
	void SetStatementForInstrumentRecord(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(duckdb_prepared_statement statement, mdb::Instrument* record);
	bool AppendForOrderRecord(duckdb_appender appender, mdb::Order* record);
	void SetStatementForOrderRecord(duckdb_prepared_statement statement, mdb::Order* record);
	void SetStatementForOrderRecordUpdate(duckdb_prepared_statement statement, mdb::Order* record);
	void SetStatementForOrderPrimaryKey(duckdb_prepared_statement statement, mdb::Order* record);
	bool AppendForTradeRecord(duckdb_appender appender, mdb::Trade* record);
	void SetStatementForTradeRecord(duckdb_prepared_statement statement, mdb::Trade* record);
	void SetStatementForTradeRecordUpdate(duckdb_prepared_statement statement, mdb::Trade* record);
	void SetStatementForTradePrimaryKey(duckdb_prepared_statement statement, mdb::Trade* record);
	bool AppendForDepthMarketDataRecord(duckdb_appender appender, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecord(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::DepthMarketData* record);


private:
	std::string m_DBName;
	duckdb_database m_DB;
	duckdb_connection m_Connection;
	char* m_SqlBuff;

	duckdb_prepared_statement m_TradingDayDeleteStatement;
	duckdb_prepared_statement m_TradingDayUpdateStatement;
	duckdb_prepared_statement m_TradingDaySelectStatement;
	duckdb_prepared_statement m_TradingDayTruncateStatement;
	duckdb_prepared_statement m_ExchangeDeleteStatement;
	duckdb_prepared_statement m_ExchangeUpdateStatement;
	duckdb_prepared_statement m_ExchangeSelectStatement;
	duckdb_prepared_statement m_ExchangeTruncateStatement;
	duckdb_prepared_statement m_ProductDeleteStatement;
	duckdb_prepared_statement m_ProductUpdateStatement;
	duckdb_prepared_statement m_ProductSelectStatement;
	duckdb_prepared_statement m_ProductTruncateStatement;
	duckdb_prepared_statement m_InstrumentDeleteStatement;
	duckdb_prepared_statement m_InstrumentUpdateStatement;
	duckdb_prepared_statement m_InstrumentSelectStatement;
	duckdb_prepared_statement m_InstrumentTruncateStatement;
	duckdb_prepared_statement m_OrderDeleteStatement;
	duckdb_prepared_statement m_OrderUpdateStatement;
	duckdb_prepared_statement m_OrderSelectStatement;
	duckdb_prepared_statement m_OrderTruncateStatement;
	duckdb_prepared_statement m_TradeDeleteStatement;
	duckdb_prepared_statement m_TradeUpdateStatement;
	duckdb_prepared_statement m_TradeSelectStatement;
	duckdb_prepared_statement m_TradeTruncateStatement;
	duckdb_prepared_statement m_DepthMarketDataDeleteStatement;
	duckdb_prepared_statement m_DepthMarketDataUpdateStatement;
	duckdb_prepared_statement m_DepthMarketDataSelectStatement;
	duckdb_prepared_statement m_DepthMarketDataTruncateStatement;
};
