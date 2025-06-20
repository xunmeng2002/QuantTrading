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
	virtual void TruncateSessionTables() = 0;
	virtual void TruncateTables() = 0;
	
	virtual void InsertTradingDay(mdb::TradingDay* record) = 0;
	virtual void BatchInsertTradingDay(std::list<mdb::TradingDay*>* records) = 0;
	virtual void DeleteTradingDay(mdb::TradingDay* record) = 0;
	virtual void UpdateTradingDay(mdb::TradingDay* record) = 0;
	virtual void SelectTradingDay(std::list<mdb::TradingDay*>& records) = 0;
	virtual void TruncateTradingDay() = 0;

	virtual void InsertExchange(mdb::Exchange* record) = 0;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) = 0;
	virtual void DeleteExchange(mdb::Exchange* record) = 0;
	virtual void UpdateExchange(mdb::Exchange* record) = 0;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) = 0;
	virtual void TruncateExchange() = 0;

	virtual void InsertProduct(mdb::Product* record) = 0;
	virtual void BatchInsertProduct(std::list<mdb::Product*>* records) = 0;
	virtual void DeleteProduct(mdb::Product* record) = 0;
	virtual void UpdateProduct(mdb::Product* record) = 0;
	virtual void SelectProduct(std::list<mdb::Product*>& records) = 0;
	virtual void TruncateProduct() = 0;

	virtual void InsertInstrument(mdb::Instrument* record) = 0;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) = 0;
	virtual void DeleteInstrument(mdb::Instrument* record) = 0;
	virtual void UpdateInstrument(mdb::Instrument* record) = 0;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) = 0;
	virtual void TruncateInstrument() = 0;

	virtual void InsertOrder(mdb::Order* record) = 0;
	virtual void BatchInsertOrder(std::list<mdb::Order*>* records) = 0;
	virtual void DeleteOrder(mdb::Order* record) = 0;
	virtual void UpdateOrder(mdb::Order* record) = 0;
	virtual void SelectOrder(std::list<mdb::Order*>& records) = 0;
	virtual void TruncateOrder() = 0;

	virtual void InsertTrade(mdb::Trade* record) = 0;
	virtual void BatchInsertTrade(std::list<mdb::Trade*>* records) = 0;
	virtual void DeleteTrade(mdb::Trade* record) = 0;
	virtual void UpdateTrade(mdb::Trade* record) = 0;
	virtual void SelectTrade(std::list<mdb::Trade*>& records) = 0;
	virtual void TruncateTrade() = 0;

	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) = 0;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) = 0;
	virtual void TruncateDepthMarketData() = 0;

};
