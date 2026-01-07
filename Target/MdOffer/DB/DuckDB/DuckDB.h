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
	virtual void CreateDepthMarketData() override;
	virtual void DropDepthMarketData() override;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) override;
	virtual void TruncateDepthMarketData() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::DepthMarketData*>& records);
	
	virtual void CreateBarMarketData() override;
	virtual void DropBarMarketData() override;
	virtual void InsertBarMarketData(mdb::BarMarketData* record) override;
	virtual void BatchInsertBarMarketData(std::list<mdb::BarMarketData*>* records) override;
	virtual void DeleteBarMarketData(mdb::BarMarketData* record) override;
	virtual void UpdateBarMarketData(mdb::BarMarketData* record) override;
	virtual void SelectBarMarketData(std::list<mdb::BarMarketData*>& records) override;
	virtual void TruncateBarMarketData() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::BarMarketData*>& records);
	

private:
	bool AppendForDepthMarketDataRecord(duckdb_appender appender, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecord(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	bool AppendForBarMarketDataRecord(duckdb_appender appender, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecord(duckdb_prepared_statement statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::BarMarketData* record);


private:
	std::string m_DBName;
	duckdb_database m_DB;
	duckdb_connection m_Connection;
	char* m_SqlBuff;

	duckdb_prepared_statement m_DepthMarketDataDeleteStatement;
	duckdb_prepared_statement m_DepthMarketDataUpdateStatement;
	duckdb_prepared_statement m_DepthMarketDataSelectStatement;
	duckdb_prepared_statement m_DepthMarketDataTruncateStatement;
	duckdb_prepared_statement m_BarMarketDataDeleteStatement;
	duckdb_prepared_statement m_BarMarketDataUpdateStatement;
	duckdb_prepared_statement m_BarMarketDataSelectStatement;
	duckdb_prepared_statement m_BarMarketDataTruncateStatement;
};
