#pragma once
#include "DB.h"
#include "sqlite3.h"
#include <string>
#include <list>


class SqliteDB : public DB
{
public:
	SqliteDB(const std::string& dbName);
	~SqliteDB();
	virtual bool Connect() override;
	virtual void DisConnect() override;
	virtual void InitDB() override;
	virtual void CreateTables() override;
	virtual void DropTables() override;
	virtual void TruncateTables() override;
	virtual void TruncateSessionTables() override;
	
	bool Exec(const char* sql);
	virtual void CreateDepthMarketData() override;
	virtual void DropDepthMarketData() override;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) override;
	virtual void TruncateDepthMarketData() override;
	
	virtual void CreateBarMarketData() override;
	virtual void DropBarMarketData() override;
	virtual void InsertBarMarketData(mdb::BarMarketData* record) override;
	virtual void BatchInsertBarMarketData(std::list<mdb::BarMarketData*>* records) override;
	virtual void DeleteBarMarketData(mdb::BarMarketData* record) override;
	virtual void UpdateBarMarketData(mdb::BarMarketData* record) override;
	virtual void SelectBarMarketData(std::list<mdb::BarMarketData*>& records) override;
	virtual void TruncateBarMarketData() override;
	

private:
	void SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::DepthMarketData*>& records);
	void SetStatementForBarMarketDataRecord(sqlite3_stmt* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::BarMarketData*>& records);


private:
	std::string m_DBName;
	sqlite3* m_DB;
	char* m_SqlBuff;

	sqlite3_stmt* m_DepthMarketDataInsertStatement;
	sqlite3_stmt* m_DepthMarketDataDeleteStatement;
	sqlite3_stmt* m_DepthMarketDataUpdateStatement;
	sqlite3_stmt* m_DepthMarketDataSelectStatement;
	sqlite3_stmt* m_DepthMarketDataTruncateStatement;
	sqlite3_stmt* m_BarMarketDataInsertStatement;
	sqlite3_stmt* m_BarMarketDataDeleteStatement;
	sqlite3_stmt* m_BarMarketDataUpdateStatement;
	sqlite3_stmt* m_BarMarketDataSelectStatement;
	sqlite3_stmt* m_BarMarketDataTruncateStatement;
};
