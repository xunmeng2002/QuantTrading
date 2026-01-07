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
	
	virtual void CreateSEBroker() override;
	virtual void DropSEBroker() override;
	virtual void InsertSEBroker(mdb::SEBroker* record) override;
	virtual void BatchInsertSEBroker(std::list<mdb::SEBroker*>* records) override;
	virtual void DeleteSEBroker(mdb::SEBroker* record) override;
	virtual void UpdateSEBroker(mdb::SEBroker* record) override;
	virtual void SelectSEBroker(std::list<mdb::SEBroker*>& records) override;
	virtual void TruncateSEBroker() override;
	
	virtual void CreateSEInstrument() override;
	virtual void DropSEInstrument() override;
	virtual void InsertSEInstrument(mdb::SEInstrument* record) override;
	virtual void BatchInsertSEInstrument(std::list<mdb::SEInstrument*>* records) override;
	virtual void DeleteSEInstrument(mdb::SEInstrument* record) override;
	virtual void DeleteSEInstrumentByExchangeIDIndex(mdb::SEInstrument* record) override;
	virtual void UpdateSEInstrument(mdb::SEInstrument* record) override;
	virtual void SelectSEInstrument(std::list<mdb::SEInstrument*>& records) override;
	virtual void TruncateSEInstrument() override;
	
	virtual void CreateSEOrder() override;
	virtual void DropSEOrder() override;
	virtual void InsertSEOrder(mdb::SEOrder* record) override;
	virtual void BatchInsertSEOrder(std::list<mdb::SEOrder*>* records) override;
	virtual void DeleteSEOrder(mdb::SEOrder* record) override;
	virtual void DeleteSEOrderByAccountIDIndex(mdb::SEOrder* record) override;
	virtual void UpdateSEOrder(mdb::SEOrder* record) override;
	virtual void SelectSEOrder(std::list<mdb::SEOrder*>& records) override;
	virtual void TruncateSEOrder() override;
	
	virtual void CreateSETrade() override;
	virtual void DropSETrade() override;
	virtual void InsertSETrade(mdb::SETrade* record) override;
	virtual void BatchInsertSETrade(std::list<mdb::SETrade*>* records) override;
	virtual void DeleteSETrade(mdb::SETrade* record) override;
	virtual void DeleteSETradeByAccountIDIndex(mdb::SETrade* record) override;
	virtual void UpdateSETrade(mdb::SETrade* record) override;
	virtual void SelectSETrade(std::list<mdb::SETrade*>& records) override;
	virtual void TruncateSETrade() override;
	
	virtual void CreateSEBrokerLoginSession() override;
	virtual void DropSEBrokerLoginSession() override;
	virtual void InsertSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void BatchInsertSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>* records) override;
	virtual void DeleteSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void DeleteSEBrokerLoginSessionByBrokerIDIndex(mdb::SEBrokerLoginSession* record) override;
	virtual void UpdateSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) override;
	virtual void SelectSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>& records) override;
	virtual void TruncateSEBrokerLoginSession() override;
	
	virtual void CreateDepthMarketData() override;
	virtual void DropDepthMarketData() override;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) override;
	virtual void TruncateDepthMarketData() override;
	

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
	void SetStatementForSEBrokerRecord(sql::PreparedStatement* statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerRecordUpdate(sql::PreparedStatement* statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerPrimaryKey(sql::PreparedStatement* statement, const BrokerIDType& BrokerID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::SEBroker*>& records);
	void SetStatementForSEInstrumentRecord(sql::PreparedStatement* statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentRecordUpdate(sql::PreparedStatement* statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentPrimaryKey(sql::PreparedStatement* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void SetStatementForSEInstrumentIndexExchangeID(sql::PreparedStatement* statement, mdb::SEInstrument* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::SEInstrument*>& records);
	void SetStatementForSEOrderRecord(sql::PreparedStatement* statement, mdb::SEOrder* record);
	void SetStatementForSEOrderRecordUpdate(sql::PreparedStatement* statement, mdb::SEOrder* record);
	void SetStatementForSEOrderPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
	void SetStatementForSEOrderIndexAccountID(sql::PreparedStatement* statement, mdb::SEOrder* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::SEOrder*>& records);
	void SetStatementForSETradeRecord(sql::PreparedStatement* statement, mdb::SETrade* record);
	void SetStatementForSETradeRecordUpdate(sql::PreparedStatement* statement, mdb::SETrade* record);
	void SetStatementForSETradePrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
	void SetStatementForSETradeIndexAccountID(sql::PreparedStatement* statement, mdb::SETrade* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::SETrade*>& records);
	void SetStatementForSEBrokerLoginSessionRecord(sql::PreparedStatement* statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionRecordUpdate(sql::PreparedStatement* statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionPrimaryKey(sql::PreparedStatement* statement, const SessionIDType& SessionID);
	void SetStatementForSEBrokerLoginSessionIndexBrokerID(sql::PreparedStatement* statement, mdb::SEBrokerLoginSession* record);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::SEBrokerLoginSession*>& records);
	void SetStatementForDepthMarketDataRecord(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sql::PreparedStatement* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sql::PreparedStatement* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sql::ResultSet* result, std::list<mdb::DepthMarketData*>& records);


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
	sql::PreparedStatement* m_SEBrokerCreateStatement;
	sql::PreparedStatement* m_SEBrokerDropStatement;
	sql::PreparedStatement* m_SEBrokerInsertStatement;
	sql::PreparedStatement* m_SEBrokerDeleteStatement;
	sql::PreparedStatement* m_SEBrokerUpdateStatement;
	sql::PreparedStatement* m_SEBrokerSelectStatement;
	sql::PreparedStatement* m_SEBrokerTruncateStatement;
	sql::PreparedStatement* m_SEInstrumentCreateStatement;
	sql::PreparedStatement* m_SEInstrumentDropStatement;
	sql::PreparedStatement* m_SEInstrumentInsertStatement;
	sql::PreparedStatement* m_SEInstrumentDeleteStatement;
	sql::PreparedStatement* m_SEInstrumentDeleteByExchangeIDIndexStatement;
	sql::PreparedStatement* m_SEInstrumentUpdateStatement;
	sql::PreparedStatement* m_SEInstrumentSelectStatement;
	sql::PreparedStatement* m_SEInstrumentTruncateStatement;
	sql::PreparedStatement* m_SEOrderCreateStatement;
	sql::PreparedStatement* m_SEOrderDropStatement;
	sql::PreparedStatement* m_SEOrderInsertStatement;
	sql::PreparedStatement* m_SEOrderDeleteStatement;
	sql::PreparedStatement* m_SEOrderDeleteByAccountIDIndexStatement;
	sql::PreparedStatement* m_SEOrderUpdateStatement;
	sql::PreparedStatement* m_SEOrderSelectStatement;
	sql::PreparedStatement* m_SEOrderTruncateStatement;
	sql::PreparedStatement* m_SETradeCreateStatement;
	sql::PreparedStatement* m_SETradeDropStatement;
	sql::PreparedStatement* m_SETradeInsertStatement;
	sql::PreparedStatement* m_SETradeDeleteStatement;
	sql::PreparedStatement* m_SETradeDeleteByAccountIDIndexStatement;
	sql::PreparedStatement* m_SETradeUpdateStatement;
	sql::PreparedStatement* m_SETradeSelectStatement;
	sql::PreparedStatement* m_SETradeTruncateStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionCreateStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionDropStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionInsertStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionDeleteStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionUpdateStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionSelectStatement;
	sql::PreparedStatement* m_SEBrokerLoginSessionTruncateStatement;
	sql::PreparedStatement* m_DepthMarketDataCreateStatement;
	sql::PreparedStatement* m_DepthMarketDataDropStatement;
	sql::PreparedStatement* m_DepthMarketDataInsertStatement;
	sql::PreparedStatement* m_DepthMarketDataDeleteStatement;
	sql::PreparedStatement* m_DepthMarketDataUpdateStatement;
	sql::PreparedStatement* m_DepthMarketDataSelectStatement;
	sql::PreparedStatement* m_DepthMarketDataTruncateStatement;
};
