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
	
	virtual void CreateHotInstrument() override;
	virtual void DropHotInstrument() override;
	virtual void InsertHotInstrument(mdb::HotInstrument* record) override;
	virtual void BatchInsertHotInstrument(std::list<mdb::HotInstrument*>* records) override;
	virtual void DeleteHotInstrument(mdb::HotInstrument* record) override;
	virtual void DeleteHotInstrumentByTradingDayIndex(mdb::HotInstrument* record) override;
	virtual void UpdateHotInstrument(mdb::HotInstrument* record) override;
	virtual void SelectHotInstrument(std::list<mdb::HotInstrument*>& records) override;
	virtual void TruncateHotInstrument() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::HotInstrument*>& records);
	
	virtual void CreateInstrument() override;
	virtual void DropInstrument() override;
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Instrument*>& records);
	
	virtual void CreateAccount() override;
	virtual void DropAccount() override;
	virtual void InsertAccount(mdb::Account* record) override;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) override;
	virtual void DeleteAccount(mdb::Account* record) override;
	virtual void UpdateAccount(mdb::Account* record) override;
	virtual void SelectAccount(std::list<mdb::Account*>& records) override;
	virtual void TruncateAccount() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::Account*>& records);
	

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
	bool AppendForHotInstrumentRecord(duckdb_appender appender, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentRecord(duckdb_prepared_statement statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentRecordUpdate(duckdb_prepared_statement statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentPrimaryKey(duckdb_prepared_statement statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentIndexTradingDay(duckdb_prepared_statement statement, mdb::HotInstrument* record);
	bool AppendForInstrumentRecord(duckdb_appender appender, mdb::Instrument* record);
	void SetStatementForInstrumentRecord(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(duckdb_prepared_statement statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(duckdb_prepared_statement statement, mdb::Instrument* record);
	bool AppendForAccountRecord(duckdb_appender appender, mdb::Account* record);
	void SetStatementForAccountRecord(duckdb_prepared_statement statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(duckdb_prepared_statement statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(duckdb_prepared_statement statement, mdb::Account* record);


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
	duckdb_prepared_statement m_HotInstrumentDeleteStatement;
	duckdb_prepared_statement m_HotInstrumentDeleteByTradingDayIndexStatement;
	duckdb_prepared_statement m_HotInstrumentUpdateStatement;
	duckdb_prepared_statement m_HotInstrumentSelectStatement;
	duckdb_prepared_statement m_HotInstrumentTruncateStatement;
	duckdb_prepared_statement m_InstrumentDeleteStatement;
	duckdb_prepared_statement m_InstrumentUpdateStatement;
	duckdb_prepared_statement m_InstrumentSelectStatement;
	duckdb_prepared_statement m_InstrumentTruncateStatement;
	duckdb_prepared_statement m_AccountDeleteStatement;
	duckdb_prepared_statement m_AccountUpdateStatement;
	duckdb_prepared_statement m_AccountSelectStatement;
	duckdb_prepared_statement m_AccountTruncateStatement;
};
