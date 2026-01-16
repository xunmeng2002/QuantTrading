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
	
	virtual void CreateTradingDay() override;
	virtual void DropTradingDay() override;
	virtual void InsertTradingDay(mdb::TradingDay* record) override;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) override;
	virtual void DeleteTradingDay(mdb::TradingDay* record) override;
	virtual void UpdateTradingDay(mdb::TradingDay* record) override;
	virtual void SelectTradingDay(std::list<mdb::TradingDay*>& records) override;
	virtual void TruncateTradingDay() override;
	
	virtual void CreateExchange() override;
	virtual void DropExchange() override;
	virtual void InsertExchange(mdb::Exchange* record) override;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) override;
	virtual void DeleteExchange(mdb::Exchange* record) override;
	virtual void UpdateExchange(mdb::Exchange* record) override;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) override;
	virtual void TruncateExchange() override;
	
	virtual void CreateProduct() override;
	virtual void DropProduct() override;
	virtual void InsertProduct(mdb::Product* record) override;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) override;
	virtual void DeleteProduct(mdb::Product* record) override;
	virtual void UpdateProduct(mdb::Product* record) override;
	virtual void SelectProduct(std::list<mdb::Product*>& records) override;
	virtual void TruncateProduct() override;
	
	virtual void CreateHotInstrument() override;
	virtual void DropHotInstrument() override;
	virtual void InsertHotInstrument(mdb::HotInstrument* record) override;
	virtual void BatchInsertHotInstrument(std::list<mdb::HotInstrument*>* records) override;
	virtual void DeleteHotInstrument(mdb::HotInstrument* record) override;
	virtual void DeleteHotInstrumentByTradingDayIndex(mdb::HotInstrument* record) override;
	virtual void UpdateHotInstrument(mdb::HotInstrument* record) override;
	virtual void SelectHotInstrument(std::list<mdb::HotInstrument*>& records) override;
	virtual void TruncateHotInstrument() override;
	
	virtual void CreateInstrument() override;
	virtual void DropInstrument() override;
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void DeleteInstrumentByExchangeIDIndex(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	
	virtual void CreateAccount() override;
	virtual void DropAccount() override;
	virtual void InsertAccount(mdb::Account* record) override;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) override;
	virtual void DeleteAccount(mdb::Account* record) override;
	virtual void UpdateAccount(mdb::Account* record) override;
	virtual void SelectAccount(std::list<mdb::Account*>& records) override;
	virtual void TruncateAccount() override;
	

private:
	void SetStatementForTradingDayRecord(sql::PreparedStatement* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(sql::PreparedStatement* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(sql::PreparedStatement* statement, const IntType& PK);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::TradingDay*>& records);
	void SetStatementForExchangeRecord(sql::PreparedStatement* statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(sql::PreparedStatement* statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Exchange*>& records);
	void SetStatementForProductRecord(sql::PreparedStatement* statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(sql::PreparedStatement* statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Product*>& records);
	void SetStatementForHotInstrumentRecord(sql::PreparedStatement* statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentRecordUpdate(sql::PreparedStatement* statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank);
	void SetStatementForHotInstrumentIndexTradingDay(sql::PreparedStatement* statement, mdb::HotInstrument* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::HotInstrument*>& records);
	void SetStatementForInstrumentRecord(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void SetStatementForInstrumentIndexExchangeID(sql::PreparedStatement* statement, mdb::Instrument* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Instrument*>& records);
	void SetStatementForAccountRecord(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Account*>& records);


private:
	sql::Driver* m_Driver;
	sql::Connection* m_DBConnection;
	sql::Statement* m_Statement;

	std::string m_Host;
	std::string m_User;
	std::string m_Passwd;
	char* m_SqlBuff;

	sql::PreparedStatement* m_TradingDayCreateStatement;
	sql::PreparedStatement* m_TradingDayDropStatement;
	sql::PreparedStatement* m_TradingDayInsertStatement;
	sql::PreparedStatement* m_TradingDayDeleteStatement;
	sql::PreparedStatement* m_TradingDayUpdateStatement;
	sql::PreparedStatement* m_TradingDaySelectStatement;
	sql::PreparedStatement* m_TradingDayTruncateStatement;
	sql::PreparedStatement* m_ExchangeCreateStatement;
	sql::PreparedStatement* m_ExchangeDropStatement;
	sql::PreparedStatement* m_ExchangeInsertStatement;
	sql::PreparedStatement* m_ExchangeDeleteStatement;
	sql::PreparedStatement* m_ExchangeUpdateStatement;
	sql::PreparedStatement* m_ExchangeSelectStatement;
	sql::PreparedStatement* m_ExchangeTruncateStatement;
	sql::PreparedStatement* m_ProductCreateStatement;
	sql::PreparedStatement* m_ProductDropStatement;
	sql::PreparedStatement* m_ProductInsertStatement;
	sql::PreparedStatement* m_ProductDeleteStatement;
	sql::PreparedStatement* m_ProductUpdateStatement;
	sql::PreparedStatement* m_ProductSelectStatement;
	sql::PreparedStatement* m_ProductTruncateStatement;
	sql::PreparedStatement* m_HotInstrumentCreateStatement;
	sql::PreparedStatement* m_HotInstrumentDropStatement;
	sql::PreparedStatement* m_HotInstrumentInsertStatement;
	sql::PreparedStatement* m_HotInstrumentDeleteStatement;
	sql::PreparedStatement* m_HotInstrumentDeleteByTradingDayIndexStatement;
	sql::PreparedStatement* m_HotInstrumentUpdateStatement;
	sql::PreparedStatement* m_HotInstrumentSelectStatement;
	sql::PreparedStatement* m_HotInstrumentTruncateStatement;
	sql::PreparedStatement* m_InstrumentCreateStatement;
	sql::PreparedStatement* m_InstrumentDropStatement;
	sql::PreparedStatement* m_InstrumentInsertStatement;
	sql::PreparedStatement* m_InstrumentDeleteStatement;
	sql::PreparedStatement* m_InstrumentDeleteByExchangeIDIndexStatement;
	sql::PreparedStatement* m_InstrumentUpdateStatement;
	sql::PreparedStatement* m_InstrumentSelectStatement;
	sql::PreparedStatement* m_InstrumentTruncateStatement;
	sql::PreparedStatement* m_AccountCreateStatement;
	sql::PreparedStatement* m_AccountDropStatement;
	sql::PreparedStatement* m_AccountInsertStatement;
	sql::PreparedStatement* m_AccountDeleteStatement;
	sql::PreparedStatement* m_AccountUpdateStatement;
	sql::PreparedStatement* m_AccountSelectStatement;
	sql::PreparedStatement* m_AccountTruncateStatement;
};
