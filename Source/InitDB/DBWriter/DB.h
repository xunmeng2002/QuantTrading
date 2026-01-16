#pragma once
#include "MdbStructs.h"
#include <string>
#include <list>


class DB
{
public:
	virtual bool Connect() = 0;
	virtual void DisConnect() = 0;
	virtual void InitDB() = 0;
	virtual void CreateTables() = 0;
	virtual void DropTables() = 0;
	virtual void TruncateTables() = 0;
	virtual void TruncateSessionTables() = 0;
	
	virtual void CreateTradingDay() = 0;
	virtual void DropTradingDay() = 0;
	virtual void InsertTradingDay(mdb::TradingDay* record) = 0;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) = 0;
	virtual void DeleteTradingDay(mdb::TradingDay* record) = 0;
	virtual void UpdateTradingDay(mdb::TradingDay* record) = 0;
	virtual void SelectTradingDay(std::list<mdb::TradingDay*>& records) = 0;
	virtual void TruncateTradingDay() = 0;

	virtual void CreateExchange() = 0;
	virtual void DropExchange() = 0;
	virtual void InsertExchange(mdb::Exchange* record) = 0;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) = 0;
	virtual void DeleteExchange(mdb::Exchange* record) = 0;
	virtual void UpdateExchange(mdb::Exchange* record) = 0;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) = 0;
	virtual void TruncateExchange() = 0;

	virtual void CreateProduct() = 0;
	virtual void DropProduct() = 0;
	virtual void InsertProduct(mdb::Product* record) = 0;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) = 0;
	virtual void DeleteProduct(mdb::Product* record) = 0;
	virtual void UpdateProduct(mdb::Product* record) = 0;
	virtual void SelectProduct(std::list<mdb::Product*>& records) = 0;
	virtual void TruncateProduct() = 0;

	virtual void CreateHotInstrument() = 0;
	virtual void DropHotInstrument() = 0;
	virtual void InsertHotInstrument(mdb::HotInstrument* record) = 0;
	virtual void BatchInsertHotInstrument(std::list<mdb::HotInstrument*>* records) = 0;
	virtual void DeleteHotInstrument(mdb::HotInstrument* record) = 0;
	virtual void DeleteHotInstrumentByTradingDayIndex(mdb::HotInstrument* record) = 0;
	virtual void UpdateHotInstrument(mdb::HotInstrument* record) = 0;
	virtual void SelectHotInstrument(std::list<mdb::HotInstrument*>& records) = 0;
	virtual void TruncateHotInstrument() = 0;

	virtual void CreateInstrument() = 0;
	virtual void DropInstrument() = 0;
	virtual void InsertInstrument(mdb::Instrument* record) = 0;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) = 0;
	virtual void DeleteInstrument(mdb::Instrument* record) = 0;
	virtual void DeleteInstrumentByExchangeIDIndex(mdb::Instrument* record) = 0;
	virtual void UpdateInstrument(mdb::Instrument* record) = 0;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) = 0;
	virtual void TruncateInstrument() = 0;

	virtual void CreateAccount() = 0;
	virtual void DropAccount() = 0;
	virtual void InsertAccount(mdb::Account* record) = 0;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) = 0;
	virtual void DeleteAccount(mdb::Account* record) = 0;
	virtual void UpdateAccount(mdb::Account* record) = 0;
	virtual void SelectAccount(std::list<mdb::Account*>& records) = 0;
	virtual void TruncateAccount() = 0;

};
