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
	void SetStatementForHotInstrumentRecord(sqlite3_stmt* statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentRecordUpdate(sqlite3_stmt* statement, mdb::HotInstrument* record);
	void SetStatementForHotInstrumentPrimaryKey(sqlite3_stmt* statement, const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank);
	void SetStatementForHotInstrumentIndexTradingDay(sqlite3_stmt* statement, mdb::HotInstrument* record);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::HotInstrument*>& records);
	void SetStatementForInstrumentRecord(sqlite3_stmt* statement, mdb::Instrument* record);
	void SetStatementForInstrumentRecordUpdate(sqlite3_stmt* statement, mdb::Instrument* record);
	void SetStatementForInstrumentPrimaryKey(sqlite3_stmt* statement, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::Instrument*>& records);
	void SetStatementForAccountRecord(sqlite3_stmt* statement, mdb::Account* record);
	void SetStatementForAccountRecordUpdate(sqlite3_stmt* statement, mdb::Account* record);
	void SetStatementForAccountPrimaryKey(sqlite3_stmt* statement, const AccountIDType& AccountID);
	void ParseRecord(sqlite3_stmt* statement, std::list<mdb::Account*>& records);


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
	sqlite3_stmt* m_HotInstrumentInsertStatement;
	sqlite3_stmt* m_HotInstrumentDeleteStatement;
	sqlite3_stmt* m_HotInstrumentDeleteByTradingDayIndexStatement;
	sqlite3_stmt* m_HotInstrumentUpdateStatement;
	sqlite3_stmt* m_HotInstrumentSelectStatement;
	sqlite3_stmt* m_HotInstrumentTruncateStatement;
	sqlite3_stmt* m_InstrumentInsertStatement;
	sqlite3_stmt* m_InstrumentDeleteStatement;
	sqlite3_stmt* m_InstrumentUpdateStatement;
	sqlite3_stmt* m_InstrumentSelectStatement;
	sqlite3_stmt* m_InstrumentTruncateStatement;
	sqlite3_stmt* m_AccountInsertStatement;
	sqlite3_stmt* m_AccountDeleteStatement;
	sqlite3_stmt* m_AccountUpdateStatement;
	sqlite3_stmt* m_AccountSelectStatement;
	sqlite3_stmt* m_AccountTruncateStatement;
};
