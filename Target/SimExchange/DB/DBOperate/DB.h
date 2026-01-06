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

	virtual void CreateDepthMarketData() = 0;
	virtual void DropDepthMarketData() = 0;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) = 0;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) = 0;
	virtual void TruncateDepthMarketData() = 0;

	virtual void CreateSEBroker() = 0;
	virtual void DropSEBroker() = 0;
	virtual void InsertSEBroker(mdb::SEBroker* record) = 0;
	virtual void BatchInsertSEBroker(std::list<mdb::SEBroker*>* records) = 0;
	virtual void DeleteSEBroker(mdb::SEBroker* record) = 0;
	virtual void UpdateSEBroker(mdb::SEBroker* record) = 0;
	virtual void SelectSEBroker(std::list<mdb::SEBroker*>& records) = 0;
	virtual void TruncateSEBroker() = 0;

	virtual void CreateSEInstrument() = 0;
	virtual void DropSEInstrument() = 0;
	virtual void InsertSEInstrument(mdb::SEInstrument* record) = 0;
	virtual void BatchInsertSEInstrument(std::list<mdb::SEInstrument*>* records) = 0;
	virtual void DeleteSEInstrument(mdb::SEInstrument* record) = 0;
	virtual void DeleteSEInstrumentByExchangeIDIndex(mdb::SEInstrument* record) = 0;
	virtual void UpdateSEInstrument(mdb::SEInstrument* record) = 0;
	virtual void SelectSEInstrument(std::list<mdb::SEInstrument*>& records) = 0;
	virtual void TruncateSEInstrument() = 0;

	virtual void CreateSEOrder() = 0;
	virtual void DropSEOrder() = 0;
	virtual void InsertSEOrder(mdb::SEOrder* record) = 0;
	virtual void BatchInsertSEOrder(std::list<mdb::SEOrder*>* records) = 0;
	virtual void DeleteSEOrder(mdb::SEOrder* record) = 0;
	virtual void DeleteSEOrderByAccountIDIndex(mdb::SEOrder* record) = 0;
	virtual void UpdateSEOrder(mdb::SEOrder* record) = 0;
	virtual void SelectSEOrder(std::list<mdb::SEOrder*>& records) = 0;
	virtual void TruncateSEOrder() = 0;

	virtual void CreateSETrade() = 0;
	virtual void DropSETrade() = 0;
	virtual void InsertSETrade(mdb::SETrade* record) = 0;
	virtual void BatchInsertSETrade(std::list<mdb::SETrade*>* records) = 0;
	virtual void DeleteSETrade(mdb::SETrade* record) = 0;
	virtual void DeleteSETradeByAccountIDIndex(mdb::SETrade* record) = 0;
	virtual void UpdateSETrade(mdb::SETrade* record) = 0;
	virtual void SelectSETrade(std::list<mdb::SETrade*>& records) = 0;
	virtual void TruncateSETrade() = 0;

	virtual void CreateSEBrokerLoginSession() = 0;
	virtual void DropSEBrokerLoginSession() = 0;
	virtual void InsertSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) = 0;
	virtual void BatchInsertSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>* records) = 0;
	virtual void DeleteSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) = 0;
	virtual void DeleteSEBrokerLoginSessionByBrokerIDIndex(mdb::SEBrokerLoginSession* record) = 0;
	virtual void UpdateSEBrokerLoginSession(mdb::SEBrokerLoginSession* record) = 0;
	virtual void SelectSEBrokerLoginSession(std::list<mdb::SEBrokerLoginSession*>& records) = 0;
	virtual void TruncateSEBrokerLoginSession() = 0;

};
