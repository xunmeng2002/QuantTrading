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
	
	virtual void CreateInstrument() override;
	virtual void DropInstrument() override;
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void DeleteInstrumentByExchangeIDIndex(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	
	virtual void CreateDepthMarketData() override;
	virtual void DropDepthMarketData() override;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records, const DateType& tradingDay) override;
	virtual void TruncateDepthMarketData() override;
	
	virtual void CreateBarMarketData() override;
	virtual void DropBarMarketData() override;
	virtual void InsertBarMarketData(mdb::BarMarketData* record) override;
	virtual void BatchInsertBarMarketData(std::list<mdb::BarMarketData*>* records) override;
	virtual void DeleteBarMarketData(mdb::BarMarketData* record) override;
	virtual void UpdateBarMarketData(mdb::BarMarketData* record) override;
	virtual void SelectBarMarketData(std::list<mdb::BarMarketData*>& records, const DateType& tradingDay) override;
	virtual void TruncateBarMarketData() override;
	
	virtual void CreatePrimaryAccount() override;
	virtual void DropPrimaryAccount() override;
	virtual void InsertPrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void BatchInsertPrimaryAccount(std::list<mdb::PrimaryAccount*>* records) override;
	virtual void DeletePrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void DeletePrimaryAccountByOfferIDIndex(mdb::PrimaryAccount* record) override;
	virtual void UpdatePrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void SelectPrimaryAccount(std::list<mdb::PrimaryAccount*>& records) override;
	virtual void TruncatePrimaryAccount() override;
	
	virtual void CreateAccount() override;
	virtual void DropAccount() override;
	virtual void InsertAccount(mdb::Account* record) override;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) override;
	virtual void DeleteAccount(mdb::Account* record) override;
	virtual void UpdateAccount(mdb::Account* record) override;
	virtual void SelectAccount(std::list<mdb::Account*>& records) override;
	virtual void TruncateAccount() override;
	
	virtual void CreateOrder() override;
	virtual void DropOrder() override;
	virtual void InsertOrder(mdb::Order* record) override;
	virtual void BatchInsertOrder(std::list<mdb::Order*>* records) override;
	virtual void DeleteOrder(mdb::Order* record) override;
	virtual void DeleteOrderByAccountIDIndex(mdb::Order* record) override;
	virtual void UpdateOrder(mdb::Order* record) override;
	virtual void SelectOrder(std::list<mdb::Order*>& records) override;
	virtual void TruncateOrder() override;
	
	virtual void CreateTrade() override;
	virtual void DropTrade() override;
	virtual void InsertTrade(mdb::Trade* record) override;
	virtual void BatchInsertTrade(std::list<mdb::Trade*>* records) override;
	virtual void DeleteTrade(mdb::Trade* record) override;
	virtual void DeleteTradeByAccountIDIndex(mdb::Trade* record) override;
	virtual void UpdateTrade(mdb::Trade* record) override;
	virtual void SelectTrade(std::list<mdb::Trade*>& records) override;
	virtual void TruncateTrade() override;
	
	virtual void CreateAccountLoginSession() override;
	virtual void DropAccountLoginSession() override;
	virtual void InsertAccountLoginSession(mdb::AccountLoginSession* record) override;
	virtual void BatchInsertAccountLoginSession(std::list<mdb::AccountLoginSession*>* records) override;
	virtual void DeleteAccountLoginSession(mdb::AccountLoginSession* record) override;
	virtual void DeleteAccountLoginSessionByAccountIDIndex(mdb::AccountLoginSession* record) override;
	virtual void UpdateAccountLoginSession(mdb::AccountLoginSession* record) override;
	virtual void SelectAccountLoginSession(std::list<mdb::AccountLoginSession*>& records) override;
	virtual void TruncateAccountLoginSession() override;
	

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
	void SetStatementForInstrumentRecord(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(sql::PreparedStatement* statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void SetStatementForInstrumentIndexExchangeID(sql::PreparedStatement* statement, mdb::Instrument* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Instrument*>& records);
	void SetStatementForDepthMarketDataRecord(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::DepthMarketData*>& records);
	void SetStatementForBarMarketDataRecord(sql::PreparedStatement* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataRecordUpdate(sql::PreparedStatement* statement, mdb::BarMarketData* record);
	void SetStatementForBarMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::BarMarketData*>& records);
	void SetStatementForPrimaryAccountRecord(sql::PreparedStatement* statement, mdb::PrimaryAccount* record);
	void SetStatementForPrimaryAccountRecordUpdate(sql::PreparedStatement* statement, mdb::PrimaryAccount* record);
	void SetStatementForPrimaryAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& PrimaryAccountID);
	void SetStatementForPrimaryAccountIndexOfferID(sql::PreparedStatement* statement, mdb::PrimaryAccount* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::PrimaryAccount*>& records);
	void SetStatementForAccountRecord(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(sql::PreparedStatement* statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(sql::PreparedStatement* statement, const AccountIDType& AccountID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Account*>& records);
	void SetStatementForOrderRecord(sql::PreparedStatement* statement, mdb::Order* record);
	void SetStatementForOrderRecordUpdate(sql::PreparedStatement* statement, mdb::Order* record);
	void SetStatementForOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
	void SetStatementForOrderIndexAccountID(sql::PreparedStatement* statement, mdb::Order* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Order*>& records);
	void SetStatementForTradeRecord(sql::PreparedStatement* statement, mdb::Trade* record);
	void SetStatementForTradeRecordUpdate(sql::PreparedStatement* statement, mdb::Trade* record);
	void SetStatementForTradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
	void SetStatementForTradeIndexAccountID(sql::PreparedStatement* statement, mdb::Trade* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::Trade*>& records);
	void SetStatementForAccountLoginSessionRecord(sql::PreparedStatement* statement, mdb::AccountLoginSession* record);
	void SetStatementForAccountLoginSessionRecordUpdate(sql::PreparedStatement* statement, mdb::AccountLoginSession* record);
	void SetStatementForAccountLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID);
	void SetStatementForAccountLoginSessionIndexAccountID(sql::PreparedStatement* statement, mdb::AccountLoginSession* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::AccountLoginSession*>& records);


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
	sql::PreparedStatement* m_InstrumentCreateStatement;
	sql::PreparedStatement* m_InstrumentDropStatement;
	sql::PreparedStatement* m_InstrumentInsertStatement;
	sql::PreparedStatement* m_InstrumentDeleteStatement;
	sql::PreparedStatement* m_InstrumentDeleteByExchangeIDIndexStatement;
	sql::PreparedStatement* m_InstrumentUpdateStatement;
	sql::PreparedStatement* m_InstrumentSelectStatement;
	sql::PreparedStatement* m_InstrumentTruncateStatement;
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
	sql::PreparedStatement* m_PrimaryAccountCreateStatement;
	sql::PreparedStatement* m_PrimaryAccountDropStatement;
	sql::PreparedStatement* m_PrimaryAccountInsertStatement;
	sql::PreparedStatement* m_PrimaryAccountDeleteStatement;
	sql::PreparedStatement* m_PrimaryAccountDeleteByOfferIDIndexStatement;
	sql::PreparedStatement* m_PrimaryAccountUpdateStatement;
	sql::PreparedStatement* m_PrimaryAccountSelectStatement;
	sql::PreparedStatement* m_PrimaryAccountTruncateStatement;
	sql::PreparedStatement* m_AccountCreateStatement;
	sql::PreparedStatement* m_AccountDropStatement;
	sql::PreparedStatement* m_AccountInsertStatement;
	sql::PreparedStatement* m_AccountDeleteStatement;
	sql::PreparedStatement* m_AccountUpdateStatement;
	sql::PreparedStatement* m_AccountSelectStatement;
	sql::PreparedStatement* m_AccountTruncateStatement;
	sql::PreparedStatement* m_OrderCreateStatement;
	sql::PreparedStatement* m_OrderDropStatement;
	sql::PreparedStatement* m_OrderInsertStatement;
	sql::PreparedStatement* m_OrderDeleteStatement;
	sql::PreparedStatement* m_OrderDeleteByAccountIDIndexStatement;
	sql::PreparedStatement* m_OrderUpdateStatement;
	sql::PreparedStatement* m_OrderSelectStatement;
	sql::PreparedStatement* m_OrderTruncateStatement;
	sql::PreparedStatement* m_TradeCreateStatement;
	sql::PreparedStatement* m_TradeDropStatement;
	sql::PreparedStatement* m_TradeInsertStatement;
	sql::PreparedStatement* m_TradeDeleteStatement;
	sql::PreparedStatement* m_TradeDeleteByAccountIDIndexStatement;
	sql::PreparedStatement* m_TradeUpdateStatement;
	sql::PreparedStatement* m_TradeSelectStatement;
	sql::PreparedStatement* m_TradeTruncateStatement;
	sql::PreparedStatement* m_AccountLoginSessionCreateStatement;
	sql::PreparedStatement* m_AccountLoginSessionDropStatement;
	sql::PreparedStatement* m_AccountLoginSessionInsertStatement;
	sql::PreparedStatement* m_AccountLoginSessionDeleteStatement;
	sql::PreparedStatement* m_AccountLoginSessionDeleteByAccountIDIndexStatement;
	sql::PreparedStatement* m_AccountLoginSessionUpdateStatement;
	sql::PreparedStatement* m_AccountLoginSessionSelectStatement;
	sql::PreparedStatement* m_AccountLoginSessionTruncateStatement;
};
