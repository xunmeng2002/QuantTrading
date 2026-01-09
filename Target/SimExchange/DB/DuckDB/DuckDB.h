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
	virtual void CreateTables() override;
	virtual void DropTables() override;
	virtual void TruncateTables() override;
	virtual void TruncateSessionTables() override;
	
	bool Exec(const char* sql) const;
	virtual void CreateTradingDay() override;
	virtual void DropTradingDay() override;
	virtual void InsertTradingDay(mdb::TradingDay* record) override;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) override;
	virtual void DeleteTradingDay(mdb::TradingDay* record) override;
	virtual void UpdateTradingDay(mdb::TradingDay* record) override;
	virtual void SelectTradingDay(std::list<mdb::TradingDay*>& records) override;
	virtual void TruncateTradingDay() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::TradingDay*>& records);
	
	virtual void CreateExchange() override;
	virtual void DropExchange() override;
	virtual void InsertExchange(mdb::Exchange* record) override;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) override;
	virtual void DeleteExchange(mdb::Exchange* record) override;
	virtual void UpdateExchange(mdb::Exchange* record) override;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) override;
	virtual void TruncateExchange() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Exchange*>& records);
	
	virtual void CreateProduct() override;
	virtual void DropProduct() override;
	virtual void InsertProduct(mdb::Product* record) override;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) override;
	virtual void DeleteProduct(mdb::Product* record) override;
	virtual void UpdateProduct(mdb::Product* record) override;
	virtual void SelectProduct(std::list<mdb::Product*>& records) override;
	virtual void TruncateProduct() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Product*>& records);
	
	virtual void CreateDepthMarketData() override;
	virtual void DropDepthMarketData() override;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records, const DateType& tradingDay) override;
	virtual void TruncateDepthMarketData() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::DepthMarketData*>& records);
	
	virtual void CreateSEBroker() override;
	virtual void DropSEBroker() override;
	virtual void InsertSEBroker(mdb::SEBroker* record) override;
	virtual void BatchInsertSEBroker(std::list<mdb::SEBroker*>* records) override;
	virtual void DeleteSEBroker(mdb::SEBroker* record) override;
	virtual void UpdateSEBroker(mdb::SEBroker* record) override;
	virtual void SelectSEBroker(std::list<mdb::SEBroker*>& records) override;
	virtual void TruncateSEBroker() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::SEBroker*>& records);
	
	virtual void CreateSEInstrument() override;
	virtual void DropSEInstrument() override;
	virtual void InsertSEInstrument(mdb::SEInstrument* record) override;
	virtual void BatchInsertSEInstrument(std::list<mdb::SEInstrument*>* records) override;
	virtual void DeleteSEInstrument(mdb::SEInstrument* record) override;
	virtual void DeleteSEInstrumentByExchangeIDIndex(mdb::SEInstrument* record) override;
	virtual void UpdateSEInstrument(mdb::SEInstrument* record) override;
	virtual void SelectSEInstrument(std::list<mdb::SEInstrument*>& records) override;
	virtual void TruncateSEInstrument() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::SEInstrument*>& records);
	
	virtual void CreateSEOrder() override;
	virtual void DropSEOrder() override;
	virtual void InsertSEOrder(mdb::SEOrder* record) override;
	virtual void BatchInsertSEOrder(std::list<mdb::SEOrder*>* records) override;
	virtual void DeleteSEOrder(mdb::SEOrder* record) override;
	virtual void DeleteSEOrderByAccountIDIndex(mdb::SEOrder* record) override;
	virtual void UpdateSEOrder(mdb::SEOrder* record) override;
	virtual void SelectSEOrder(std::list<mdb::SEOrder*>& records) override;
	virtual void TruncateSEOrder() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::SEOrder*>& records);
	
	virtual void CreateSETrade() override;
	virtual void DropSETrade() override;
	virtual void InsertSETrade(mdb::SETrade* record) override;
	virtual void BatchInsertSETrade(std::list<mdb::SETrade*>* records) override;
	virtual void DeleteSETrade(mdb::SETrade* record) override;
	virtual void DeleteSETradeByAccountIDIndex(mdb::SETrade* record) override;
	virtual void UpdateSETrade(mdb::SETrade* record) override;
	virtual void SelectSETrade(std::list<mdb::SETrade*>& records) override;
	virtual void TruncateSETrade() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::SETrade*>& records);
	
	virtual void CreateSEBrokerLoginSession() override;
	virtual void DropSEBrokerLoginSession() override;
	virtual void InsertSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void BatchInsertSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>* records) override;
	virtual void DeleteSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void DeleteSEBrokerLoginSessionByBrokerIDIndex(mdb::SEBrokerLoginSession* record) override;
	virtual void UpdateSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void SelectSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>& records) override;
	virtual void TruncateSEBrokerLoginSession() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::SEBrokerLoginSession*>& records);
	

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
	bool AppendForDepthMarketDataRecord(duckdb_appender appender, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecord(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	bool AppendForSEBrokerRecord(duckdb_appender appender, mdb::SEBroker* record);
	void SetStatementForSEBrokerRecord(duckdb_prepared_statement statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerRecordUpdate(duckdb_prepared_statement statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerPrimaryKey(duckdb_prepared_statement statement, mdb::SEBroker* record);
	bool AppendForSEInstrumentRecord(duckdb_appender appender, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentRecord(duckdb_prepared_statement statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentRecordUpdate(duckdb_prepared_statement statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentPrimaryKey(duckdb_prepared_statement statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentIndexExchangeID(duckdb_prepared_statement statement, mdb::SEInstrument* record);
	bool AppendForSEOrderRecord(duckdb_appender appender, mdb::SEOrder* record);
	void SetStatementForSEOrderRecord(duckdb_prepared_statement statement, mdb::SEOrder* record);
	void SetStatementForSEOrderRecordUpdate(duckdb_prepared_statement statement, mdb::SEOrder* record);
	void SetStatementForSEOrderPrimaryKey(duckdb_prepared_statement statement, mdb::SEOrder* record);
	void SetStatementForSEOrderIndexAccountID(duckdb_prepared_statement statement, mdb::SEOrder* record);
	bool AppendForSETradeRecord(duckdb_appender appender, mdb::SETrade* record);
	void SetStatementForSETradeRecord(duckdb_prepared_statement statement, mdb::SETrade* record);
	void SetStatementForSETradeRecordUpdate(duckdb_prepared_statement statement, mdb::SETrade* record);
	void SetStatementForSETradePrimaryKey(duckdb_prepared_statement statement, mdb::SETrade* record);
	void SetStatementForSETradeIndexAccountID(duckdb_prepared_statement statement, mdb::SETrade* record);
	bool AppendForSEBrokerLoginSessionRecord(duckdb_appender appender, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionRecord(duckdb_prepared_statement statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionRecordUpdate(duckdb_prepared_statement statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionPrimaryKey(duckdb_prepared_statement statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionIndexBrokerID(duckdb_prepared_statement statement, mdb::SEBrokerLoginSession* record);


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
	duckdb_prepared_statement m_DepthMarketDataDeleteStatement;
	duckdb_prepared_statement m_DepthMarketDataUpdateStatement;
	duckdb_prepared_statement m_DepthMarketDataSelectStatement;
	duckdb_prepared_statement m_DepthMarketDataTruncateStatement;
	duckdb_prepared_statement m_SEBrokerDeleteStatement;
	duckdb_prepared_statement m_SEBrokerUpdateStatement;
	duckdb_prepared_statement m_SEBrokerSelectStatement;
	duckdb_prepared_statement m_SEBrokerTruncateStatement;
	duckdb_prepared_statement m_SEInstrumentDeleteStatement;
	duckdb_prepared_statement m_SEInstrumentDeleteByExchangeIDIndexStatement;
	duckdb_prepared_statement m_SEInstrumentUpdateStatement;
	duckdb_prepared_statement m_SEInstrumentSelectStatement;
	duckdb_prepared_statement m_SEInstrumentTruncateStatement;
	duckdb_prepared_statement m_SEOrderDeleteStatement;
	duckdb_prepared_statement m_SEOrderDeleteByAccountIDIndexStatement;
	duckdb_prepared_statement m_SEOrderUpdateStatement;
	duckdb_prepared_statement m_SEOrderSelectStatement;
	duckdb_prepared_statement m_SEOrderTruncateStatement;
	duckdb_prepared_statement m_SETradeDeleteStatement;
	duckdb_prepared_statement m_SETradeDeleteByAccountIDIndexStatement;
	duckdb_prepared_statement m_SETradeUpdateStatement;
	duckdb_prepared_statement m_SETradeSelectStatement;
	duckdb_prepared_statement m_SETradeTruncateStatement;
	duckdb_prepared_statement m_SEBrokerLoginSessionDeleteStatement;
	duckdb_prepared_statement m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement;
	duckdb_prepared_statement m_SEBrokerLoginSessionUpdateStatement;
	duckdb_prepared_statement m_SEBrokerLoginSessionSelectStatement;
	duckdb_prepared_statement m_SEBrokerLoginSessionTruncateStatement;
};
