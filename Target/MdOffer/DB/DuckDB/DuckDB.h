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
	
	virtual void CreateMdSubscribe() override;
	virtual void DropMdSubscribe() override;
	virtual void InsertMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void BatchInsertMdSubscribe(std::list<mdb::MdSubscribe*>* records) override;
	virtual void DeleteMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void UpdateMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void SelectMdSubscribe(std::list<mdb::MdSubscribe*>& records) override;
	virtual void TruncateMdSubscribe() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::MdSubscribe*>& records);
	
	virtual void CreateMdUser() override;
	virtual void DropMdUser() override;
	virtual void InsertMdUser(mdb::MdUser* record) override;
	virtual void BatchInsertMdUser(std::list<mdb::MdUser*>* records) override;
	virtual void DeleteMdUser(mdb::MdUser* record) override;
	virtual void UpdateMdUser(mdb::MdUser* record) override;
	virtual void SelectMdUser(std::list<mdb::MdUser*>& records) override;
	virtual void TruncateMdUser() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::MdUser*>& records);
	
	virtual void CreateMdUserLoginSession() override;
	virtual void DropMdUserLoginSession() override;
	virtual void InsertMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void BatchInsertMdUserLoginSession(std::list<mdb::MdUserLoginSession*>* records) override;
	virtual void DeleteMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void DeleteMdUserLoginSessionByMdUserIDIndex(mdb::MdUserLoginSession* record) override;
	virtual void UpdateMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void SelectMdUserLoginSession(std::list<mdb::MdUserLoginSession*>& records) override;
	virtual void TruncateMdUserLoginSession() override;
	static void ParseRecord(duckdb_result& result, std::list<mdb::MdUserLoginSession*>& records);
	

private:
	bool AppendForDepthMarketDataRecord(duckdb_appender appender, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecord(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::DepthMarketData* record);
	bool AppendForBarMarketDataRecord(duckdb_appender appender, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecord(duckdb_prepared_statement statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(duckdb_prepared_statement statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(duckdb_prepared_statement statement, mdb::BarMarketData* record);
	bool AppendForMdSubscribeRecord(duckdb_appender appender, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribeRecord(duckdb_prepared_statement statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribeRecordUpdate(duckdb_prepared_statement statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribePrimaryKey(duckdb_prepared_statement statement, mdb::MdSubscribe* record);
	bool AppendForMdUserRecord(duckdb_appender appender, mdb::MdUser* record);
	void SetStatementForMdUserRecord(duckdb_prepared_statement statement, mdb::MdUser* record);
	void SetStatementForMdUserRecordUpdate(duckdb_prepared_statement statement, mdb::MdUser* record);
	void SetStatementForMdUserPrimaryKey(duckdb_prepared_statement statement, mdb::MdUser* record);
	bool AppendForMdUserLoginSessionRecord(duckdb_appender appender, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionRecord(duckdb_prepared_statement statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionRecordUpdate(duckdb_prepared_statement statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionPrimaryKey(duckdb_prepared_statement statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionIndexMdUserID(duckdb_prepared_statement statement, mdb::MdUserLoginSession* record);


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
	duckdb_prepared_statement m_MdSubscribeDeleteStatement;
	duckdb_prepared_statement m_MdSubscribeUpdateStatement;
	duckdb_prepared_statement m_MdSubscribeSelectStatement;
	duckdb_prepared_statement m_MdSubscribeTruncateStatement;
	duckdb_prepared_statement m_MdUserDeleteStatement;
	duckdb_prepared_statement m_MdUserUpdateStatement;
	duckdb_prepared_statement m_MdUserSelectStatement;
	duckdb_prepared_statement m_MdUserTruncateStatement;
	duckdb_prepared_statement m_MdUserLoginSessionDeleteStatement;
	duckdb_prepared_statement m_MdUserLoginSessionDeleteByMdUserIDIndexStatement;
	duckdb_prepared_statement m_MdUserLoginSessionUpdateStatement;
	duckdb_prepared_statement m_MdUserLoginSessionSelectStatement;
	duckdb_prepared_statement m_MdUserLoginSessionTruncateStatement;
};
