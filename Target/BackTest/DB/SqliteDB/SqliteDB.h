#pragma once
#include "DB.h"
#include "sqlite3.h"
#include <string>
#include <vector>
#include <list>


class SqliteDB : public DB
{
public:
	SqliteDB(const std::string& dbName);
	~SqliteDB();
	virtual bool Connect() override;
	virtual void DisConnect() override;
	virtual void InitDB() override;
	virtual void TruncateSessionTables() override;
	virtual void TruncateTables() override;
	
	bool Exec(const char* sql);
	virtual void InsertTradingDay(mdb::TradingDay* record) override;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) override;
	virtual void DeleteTradingDay(mdb::TradingDay* record) override;
	virtual void UpdateTradingDay(mdb::TradingDay* record) override;
	virtual void SelectTradingDay(std::vector<mdb::TradingDay*>& records) override;
	virtual void TruncateTradingDay() override;
	
	virtual void InsertExchange(mdb::Exchange* record) override;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) override;
	virtual void DeleteExchange(mdb::Exchange* record) override;
	virtual void UpdateExchange(mdb::Exchange* record) override;
	virtual void SelectExchange(std::vector<mdb::Exchange*>& records) override;
	virtual void TruncateExchange() override;
	
	virtual void InsertProduct(mdb::Product* record) override;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) override;
	virtual void DeleteProduct(mdb::Product* record) override;
	virtual void UpdateProduct(mdb::Product* record) override;
	virtual void SelectProduct(std::vector<mdb::Product*>& records) override;
	virtual void TruncateProduct() override;
	
	virtual void InsertInstrument(mdb::Instrument* record) override;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) override;
	virtual void DeleteInstrument(mdb::Instrument* record) override;
	virtual void UpdateInstrument(mdb::Instrument* record) override;
	virtual void SelectInstrument(std::vector<mdb::Instrument*>& records) override;
	virtual void TruncateInstrument() override;
	
	virtual void InsertPrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void BatchInsertPrimaryAccount(std::list<mdb::PrimaryAccount*>* records) override;
	virtual void DeletePrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void DeletePrimaryAccountByOfferIDIndex(mdb::PrimaryAccount* record) override;
	virtual void UpdatePrimaryAccount(mdb::PrimaryAccount* record) override;
	virtual void SelectPrimaryAccount(std::vector<mdb::PrimaryAccount*>& records) override;
	virtual void TruncatePrimaryAccount() override;
	
	virtual void InsertAccount(mdb::Account* record) override;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) override;
	virtual void DeleteAccount(mdb::Account* record) override;
	virtual void UpdateAccount(mdb::Account* record) override;
	virtual void SelectAccount(std::vector<mdb::Account*>& records) override;
	virtual void TruncateAccount() override;
	
	virtual void InsertCapital(mdb::Capital* record) override;
	virtual void BatchInsertCapital(std::list<mdb::Capital*>* records) override;
	virtual void DeleteCapital(mdb::Capital* record) override;
	virtual void UpdateCapital(mdb::Capital* record) override;
	virtual void SelectCapital(std::vector<mdb::Capital*>& records) override;
	virtual void TruncateCapital() override;
	
	virtual void InsertPosition(mdb::Position* record) override;
	virtual void BatchInsertPosition(std::list<mdb::Position*>* records) override;
	virtual void DeletePosition(mdb::Position* record) override;
	virtual void DeletePositionByAccountIndex(mdb::Position* record) override;
	virtual void UpdatePosition(mdb::Position* record) override;
	virtual void SelectPosition(std::vector<mdb::Position*>& records) override;
	virtual void TruncatePosition() override;
	
	virtual void InsertOrder(mdb::Order* record) override;
	virtual void BatchInsertOrder(std::list<mdb::Order*>* records) override;
	virtual void DeleteOrder(mdb::Order* record) override;
	virtual void UpdateOrder(mdb::Order* record) override;
	virtual void SelectOrder(std::vector<mdb::Order*>& records) override;
	virtual void TruncateOrder() override;
	
	virtual void InsertTrade(mdb::Trade* record) override;
	virtual void BatchInsertTrade(std::list<mdb::Trade*>* records) override;
	virtual void DeleteTrade(mdb::Trade* record) override;
	virtual void UpdateTrade(mdb::Trade* record) override;
	virtual void SelectTrade(std::vector<mdb::Trade*>& records) override;
	virtual void TruncateTrade() override;
	
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) override;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) override;
	virtual void SelectDepthMarketData(std::vector<mdb::DepthMarketData*>& records) override;
	virtual void TruncateDepthMarketData() override;
	

private:
	void SetStatementForTradingDayRecord(sqlite3_stmt* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayRecordUpdate(sqlite3_stmt* statement, mdb::TradingDay* record);
	void SetStatementForTradingDayPrimaryKey(sqlite3_stmt* statement, const UserIDType& PK);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::TradingDay*>& records);
	void SetStatementForExchangeRecord(sqlite3_stmt* statement, mdb::Exchange* record);
	void SetStatementForExchangeRecordUpdate(sqlite3_stmt* statement, mdb::Exchange* record);
	void SetStatementForExchangePrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Exchange*>& records);
	void SetStatementForProductRecord(sqlite3_stmt* statement, mdb::Product* record);
	void SetStatementForProductRecordUpdate(sqlite3_stmt* statement, mdb::Product* record);
	void SetStatementForProductPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Product*>& records);
	void SetStatementForInstrumentRecord(sqlite3_stmt* statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(sqlite3_stmt* statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Instrument*>& records);
	void SetStatementForPrimaryAccountRecord(sqlite3_stmt* statement, mdb::PrimaryAccount* record);
	void SetStatementForPrimaryAccountRecordUpdate(sqlite3_stmt* statement, mdb::PrimaryAccount* record);
	void SetStatementForPrimaryAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& PrimaryAccountID);
	void SetStatementForPrimaryAccountIndexOfferID(sqlite3_stmt* statement, mdb::PrimaryAccount* record);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::PrimaryAccount*>& records);
	void SetStatementForAccountRecord(sqlite3_stmt* statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(sqlite3_stmt* statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Account*>& records);
	void SetStatementForCapitalRecord(sqlite3_stmt* statement, mdb::Capital* record);
	void SetStatementForCapitalRecordUpdate(sqlite3_stmt* statement, mdb::Capital* record);
	void SetStatementForCapitalPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Capital*>& records);
	void SetStatementForPositionRecord(sqlite3_stmt* statement, mdb::Position* record);
	void SetStatementForPositionRecordUpdate(sqlite3_stmt* statement, mdb::Position* record);
	void SetStatementForPositionPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
	void SetStatementForPositionIndexAccount(sqlite3_stmt* statement, mdb::Position* record);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Position*>& records);
	void SetStatementForOrderRecord(sqlite3_stmt* statement, mdb::Order* record);
	void SetStatementForOrderRecordUpdate(sqlite3_stmt* statement, mdb::Order* record);
	void SetStatementForOrderPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Order*>& records);
	void SetStatementForTradeRecord(sqlite3_stmt* statement, mdb::Trade* record);
	void SetStatementForTradeRecordUpdate(sqlite3_stmt* statement, mdb::Trade* record);
	void SetStatementForTradePrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::Trade*>& records);
	void SetStatementForDepthMarketDataRecord(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataRecordUpdate(sqlite3_stmt* statement, mdb::DepthMarketData* record);
	void SetStatementForDepthMarketDataPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::vector<mdb::DepthMarketData*>& records);


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
	sqlite3_stmt* m_InstrumentInsertStatement;
	sqlite3_stmt* m_InstrumentDeleteStatement;
	sqlite3_stmt* m_InstrumentUpdateStatement;
	sqlite3_stmt* m_InstrumentSelectStatement;
	sqlite3_stmt* m_InstrumentTruncateStatement;
	sqlite3_stmt* m_PrimaryAccountInsertStatement;
	sqlite3_stmt* m_PrimaryAccountDeleteStatement;
	sqlite3_stmt* m_PrimaryAccountDeleteByOfferIDIndexStatement;
	sqlite3_stmt* m_PrimaryAccountUpdateStatement;
	sqlite3_stmt* m_PrimaryAccountSelectStatement;
	sqlite3_stmt* m_PrimaryAccountTruncateStatement;
	sqlite3_stmt* m_AccountInsertStatement;
	sqlite3_stmt* m_AccountDeleteStatement;
	sqlite3_stmt* m_AccountUpdateStatement;
	sqlite3_stmt* m_AccountSelectStatement;
	sqlite3_stmt* m_AccountTruncateStatement;
	sqlite3_stmt* m_CapitalInsertStatement;
	sqlite3_stmt* m_CapitalDeleteStatement;
	sqlite3_stmt* m_CapitalUpdateStatement;
	sqlite3_stmt* m_CapitalSelectStatement;
	sqlite3_stmt* m_CapitalTruncateStatement;
	sqlite3_stmt* m_PositionInsertStatement;
	sqlite3_stmt* m_PositionDeleteStatement;
	sqlite3_stmt* m_PositionDeleteByAccountIndexStatement;
	sqlite3_stmt* m_PositionUpdateStatement;
	sqlite3_stmt* m_PositionSelectStatement;
	sqlite3_stmt* m_PositionTruncateStatement;
	sqlite3_stmt* m_OrderInsertStatement;
	sqlite3_stmt* m_OrderDeleteStatement;
	sqlite3_stmt* m_OrderUpdateStatement;
	sqlite3_stmt* m_OrderSelectStatement;
	sqlite3_stmt* m_OrderTruncateStatement;
	sqlite3_stmt* m_TradeInsertStatement;
	sqlite3_stmt* m_TradeDeleteStatement;
	sqlite3_stmt* m_TradeUpdateStatement;
	sqlite3_stmt* m_TradeSelectStatement;
	sqlite3_stmt* m_TradeTruncateStatement;
	sqlite3_stmt* m_DepthMarketDataInsertStatement;
	sqlite3_stmt* m_DepthMarketDataDeleteStatement;
	sqlite3_stmt* m_DepthMarketDataUpdateStatement;
	sqlite3_stmt* m_DepthMarketDataSelectStatement;
	sqlite3_stmt* m_DepthMarketDataTruncateStatement;
};
