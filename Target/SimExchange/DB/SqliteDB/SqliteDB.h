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
	void SetStatementForTradingDayRecord(sqlite3_stmt* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(sqlite3_stmt* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(sqlite3_stmt* statement, const IntType& PK);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::TradingDay*>& records);
	void SetStatementForExchangeRecord(sqlite3_stmt* statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(sqlite3_stmt* statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::Exchange*>& records);
	void SetStatementForProductRecord(sqlite3_stmt* statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(sqlite3_stmt* statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::Product*>& records);
	void SetStatementForSEBrokerRecord(sqlite3_stmt* statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerRecordUpdate(sqlite3_stmt* statement, mdb::SEBroker* record);
	void SetStatementForSEBrokerPrimaryKey(sqlite3_stmt* statement, const BrokerIDType& BrokerID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::SEBroker*>& records);
	void SetStatementForSEInstrumentRecord(sqlite3_stmt* statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentRecordUpdate(sqlite3_stmt* statement, mdb::SEInstrument* record);
	void SetStatementForSEInstrumentPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void SetStatementForSEInstrumentIndexExchangeID(sqlite3_stmt* statement, mdb::SEInstrument* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::SEInstrument*>& records);
	void SetStatementForSEOrderRecord(sqlite3_stmt* statement, mdb::SEOrder* record);
	void SetStatementForSEOrderRecordUpdate(sqlite3_stmt* statement, mdb::SEOrder* record);
	void SetStatementForSEOrderPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
	void SetStatementForSEOrderIndexAccountID(sqlite3_stmt* statement, mdb::SEOrder* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::SEOrder*>& records);
	void SetStatementForSETradeRecord(sqlite3_stmt* statement, mdb::SETrade* record);
	void SetStatementForSETradeRecordUpdate(sqlite3_stmt* statement, mdb::SETrade* record);
	void SetStatementForSETradePrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
	void SetStatementForSETradeIndexAccountID(sqlite3_stmt* statement, mdb::SETrade* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::SETrade*>& records);
	void SetStatementForSEBrokerLoginSessionRecord(sqlite3_stmt* statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionRecordUpdate(sqlite3_stmt* statement, mdb::SEBrokerLoginSession* record);
	void SetStatementForSEBrokerLoginSessionPrimaryKey(sqlite3_stmt* statement, const SessionIDType& SessionID);
	void SetStatementForSEBrokerLoginSessionIndexBrokerID(sqlite3_stmt* statement, mdb::SEBrokerLoginSession* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::SEBrokerLoginSession*>& records);
	void SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::DepthMarketData*>& records);


private:
	std::string m_DBName;
	sqlite3* m_DB;
	char* m_SqlBuff;

	sqlite3_stmt* m_TradingDayInsertStatement;
	sqlite3_stmt* m_TradingDayDeleteStatement;
	sqlite3_stmt* m_TradingDayUpdateStatement;
	sqlite3_stmt* m_TradingDaySelectStatement;
	sqlite3_stmt* m_TradingDayTruncateStatement;
	sqlite3_stmt* m_ExchangeInsertStatement;
	sqlite3_stmt* m_ExchangeDeleteStatement;
	sqlite3_stmt* m_ExchangeUpdateStatement;
	sqlite3_stmt* m_ExchangeSelectStatement;
	sqlite3_stmt* m_ExchangeTruncateStatement;
	sqlite3_stmt* m_ProductInsertStatement;
	sqlite3_stmt* m_ProductDeleteStatement;
	sqlite3_stmt* m_ProductUpdateStatement;
	sqlite3_stmt* m_ProductSelectStatement;
	sqlite3_stmt* m_ProductTruncateStatement;
	sqlite3_stmt* m_SEBrokerInsertStatement;
	sqlite3_stmt* m_SEBrokerDeleteStatement;
	sqlite3_stmt* m_SEBrokerUpdateStatement;
	sqlite3_stmt* m_SEBrokerSelectStatement;
	sqlite3_stmt* m_SEBrokerTruncateStatement;
	sqlite3_stmt* m_SEInstrumentInsertStatement;
	sqlite3_stmt* m_SEInstrumentDeleteStatement;
	sqlite3_stmt* m_SEInstrumentDeleteByExchangeIDIndexStatement;
	sqlite3_stmt* m_SEInstrumentUpdateStatement;
	sqlite3_stmt* m_SEInstrumentSelectStatement;
	sqlite3_stmt* m_SEInstrumentTruncateStatement;
	sqlite3_stmt* m_SEOrderInsertStatement;
	sqlite3_stmt* m_SEOrderDeleteStatement;
	sqlite3_stmt* m_SEOrderDeleteByAccountIDIndexStatement;
	sqlite3_stmt* m_SEOrderUpdateStatement;
	sqlite3_stmt* m_SEOrderSelectStatement;
	sqlite3_stmt* m_SEOrderTruncateStatement;
	sqlite3_stmt* m_SETradeInsertStatement;
	sqlite3_stmt* m_SETradeDeleteStatement;
	sqlite3_stmt* m_SETradeDeleteByAccountIDIndexStatement;
	sqlite3_stmt* m_SETradeUpdateStatement;
	sqlite3_stmt* m_SETradeSelectStatement;
	sqlite3_stmt* m_SETradeTruncateStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionInsertStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionDeleteStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionDeleteByBrokerIDIndexStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionUpdateStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionSelectStatement;
	sqlite3_stmt* m_SEBrokerLoginSessionTruncateStatement;
	sqlite3_stmt* m_DepthMarketDataInsertStatement;
	sqlite3_stmt* m_DepthMarketDataDeleteStatement;
	sqlite3_stmt* m_DepthMarketDataUpdateStatement;
	sqlite3_stmt* m_DepthMarketDataSelectStatement;
	sqlite3_stmt* m_DepthMarketDataTruncateStatement;
};
