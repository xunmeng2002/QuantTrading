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
	
	virtual void CreateMdSubscribe() override;
	virtual void DropMdSubscribe() override;
	virtual void InsertMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void BatchInsertMdSubscribe(std::list<mdb::MdSubscribe*>* records) override;
	virtual void DeleteMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void UpdateMdSubscribe(mdb::MdSubscribe* record) override;
	virtual void SelectMdSubscribe(std::list<mdb::MdSubscribe*>& records) override;
	virtual void TruncateMdSubscribe() override;
	
	virtual void CreateMdUser() override;
	virtual void DropMdUser() override;
	virtual void InsertMdUser(mdb::MdUser* record) override;
	virtual void BatchInsertMdUser(std::list<mdb::MdUser*>* records) override;
	virtual void DeleteMdUser(mdb::MdUser* record) override;
	virtual void UpdateMdUser(mdb::MdUser* record) override;
	virtual void SelectMdUser(std::list<mdb::MdUser*>& records) override;
	virtual void TruncateMdUser() override;
	
	virtual void CreateMdUserLoginSession() override;
	virtual void DropMdUserLoginSession() override;
	virtual void InsertMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void BatchInsertMdUserLoginSession(std::list<mdb::MdUserLoginSession*>* records) override;
	virtual void DeleteMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void DeleteMdUserLoginSessionByMdUserIDIndex(mdb::MdUserLoginSession* record) override;
	virtual void UpdateMdUserLoginSession(mdb::MdUserLoginSession* record) override;
	virtual void SelectMdUserLoginSession(std::list<mdb::MdUserLoginSession*>& records) override;
	virtual void TruncateMdUserLoginSession() override;
	

private:
	void SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::DepthMarketData*>& records);
	void SetStatementForBarMarketDataRecord(sqlite3_stmt* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::BarMarketData*>& records);
	void SetStatementForMdSubscribeRecord(sqlite3_stmt* statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribeRecordUpdate(sqlite3_stmt* statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribePrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::MdSubscribe*>& records);
	void SetStatementForMdUserRecord(sqlite3_stmt* statement, mdb::MdUser* record);
	void SetStatementForMdUserRecordUpdate(sqlite3_stmt* statement, mdb::MdUser* record);
	void SetStatementForMdUserPrimaryKey(sqlite3_stmt* statement, const UserIDType& MdUserID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::MdUser*>& records);
	void SetStatementForMdUserLoginSessionRecord(sqlite3_stmt* statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionRecordUpdate(sqlite3_stmt* statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionPrimaryKey(sqlite3_stmt* statement, const SessionIDType& SessionID);
	void SetStatementForMdUserLoginSessionIndexMdUserID(sqlite3_stmt* statement, mdb::MdUserLoginSession* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::MdUserLoginSession*>& records);


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
	sqlite3_stmt* m_MdSubscribeInsertStatement;
	sqlite3_stmt* m_MdSubscribeDeleteStatement;
	sqlite3_stmt* m_MdSubscribeUpdateStatement;
	sqlite3_stmt* m_MdSubscribeSelectStatement;
	sqlite3_stmt* m_MdSubscribeTruncateStatement;
	sqlite3_stmt* m_MdUserInsertStatement;
	sqlite3_stmt* m_MdUserDeleteStatement;
	sqlite3_stmt* m_MdUserUpdateStatement;
	sqlite3_stmt* m_MdUserSelectStatement;
	sqlite3_stmt* m_MdUserTruncateStatement;
	sqlite3_stmt* m_MdUserLoginSessionInsertStatement;
	sqlite3_stmt* m_MdUserLoginSessionDeleteStatement;
	sqlite3_stmt* m_MdUserLoginSessionDeleteByMdUserIDIndexStatement;
	sqlite3_stmt* m_MdUserLoginSessionUpdateStatement;
	sqlite3_stmt* m_MdUserLoginSessionSelectStatement;
	sqlite3_stmt* m_MdUserLoginSessionTruncateStatement;
};
