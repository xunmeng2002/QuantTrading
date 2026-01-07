#pragma once
#include "DB.h"
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_error.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <string>
#include <list>


class MysqlDB : public DB
{
public:
	MysqlDB(const std::string& host, const std::string& user, const std::string& passwd);
	~MysqlDB();
	virtual bool Connect() override;
	virtual void DisConnect() override;
	virtual void InitDB() override;
	virtual void CreateTables() override;
	virtual void DropTables() override;
	virtual void TruncateTables() override;
	virtual void TruncateSessionTables() override;
	
	template<typename T>
	void CustomSelectSql(const char* sql, std::list<T*>& records)
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
	void SetStatementForDepthMarketDataRecord(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::DepthMarketData*>& records);
	void SetStatementForBarMarketDataRecord(sql::PreparedStatement* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(sql::PreparedStatement* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::BarMarketData*>& records);
	void SetStatementForMdSubscribeRecord(sql::PreparedStatement* statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribeRecordUpdate(sql::PreparedStatement* statement, mdb::MdSubscribe* record);
	void SetStatementForMdSubscribePrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::MdSubscribe*>& records);
	void SetStatementForMdUserRecord(sql::PreparedStatement* statement, mdb::MdUser* record);
	void SetStatementForMdUserRecordUpdate(sql::PreparedStatement* statement, mdb::MdUser* record);
	void SetStatementForMdUserPrimaryKey(sql::PreparedStatement* statement, const UserIDType& MdUserID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::MdUser*>& records);
	void SetStatementForMdUserLoginSessionRecord(sql::PreparedStatement* statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionRecordUpdate(sql::PreparedStatement* statement, mdb::MdUserLoginSession* record);
	void SetStatementForMdUserLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID);
	void SetStatementForMdUserLoginSessionIndexMdUserID(sql::PreparedStatement* statement, mdb::MdUserLoginSession* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::MdUserLoginSession*>& records);


private:
	sql::Driver* m_Driver;
	sql::Connection* m_DBConnection;
	sql::Statement* m_Statement;

	std::string m_Host;
	std::string m_User;
	std::string m_Passwd;
	char* m_SqlBuff;

	sql::PreparedStatement* m_DepthMarketDataCreateStatement;
	sql::PreparedStatement* m_DepthMarketDataDropStatement;
	sql::PreparedStatement* m_DepthMarketDataInsertStatement;
	sql::PreparedStatement* m_DepthMarketDataDeleteStatement;
	sql::PreparedStatement* m_DepthMarketDataUpdateStatement;
	sql::PreparedStatement* m_DepthMarketDataSelectStatement;
	sql::PreparedStatement* m_DepthMarketDataTruncateStatement;
	sql::PreparedStatement* m_BarMarketDataCreateStatement;
	sql::PreparedStatement* m_BarMarketDataDropStatement;
	sql::PreparedStatement* m_BarMarketDataInsertStatement;
	sql::PreparedStatement* m_BarMarketDataDeleteStatement;
	sql::PreparedStatement* m_BarMarketDataUpdateStatement;
	sql::PreparedStatement* m_BarMarketDataSelectStatement;
	sql::PreparedStatement* m_BarMarketDataTruncateStatement;
	sql::PreparedStatement* m_MdSubscribeCreateStatement;
	sql::PreparedStatement* m_MdSubscribeDropStatement;
	sql::PreparedStatement* m_MdSubscribeInsertStatement;
	sql::PreparedStatement* m_MdSubscribeDeleteStatement;
	sql::PreparedStatement* m_MdSubscribeUpdateStatement;
	sql::PreparedStatement* m_MdSubscribeSelectStatement;
	sql::PreparedStatement* m_MdSubscribeTruncateStatement;
	sql::PreparedStatement* m_MdUserCreateStatement;
	sql::PreparedStatement* m_MdUserDropStatement;
	sql::PreparedStatement* m_MdUserInsertStatement;
	sql::PreparedStatement* m_MdUserDeleteStatement;
	sql::PreparedStatement* m_MdUserUpdateStatement;
	sql::PreparedStatement* m_MdUserSelectStatement;
	sql::PreparedStatement* m_MdUserTruncateStatement;
	sql::PreparedStatement* m_MdUserLoginSessionCreateStatement;
	sql::PreparedStatement* m_MdUserLoginSessionDropStatement;
	sql::PreparedStatement* m_MdUserLoginSessionInsertStatement;
	sql::PreparedStatement* m_MdUserLoginSessionDeleteStatement;
	sql::PreparedStatement* m_MdUserLoginSessionDeleteByMdUserIDIndexStatement;
	sql::PreparedStatement* m_MdUserLoginSessionUpdateStatement;
	sql::PreparedStatement* m_MdUserLoginSessionSelectStatement;
	sql::PreparedStatement* m_MdUserLoginSessionTruncateStatement;
};
