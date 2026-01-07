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
	virtual void UpdateInstrument(mdb::Instrument* record) = 0;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) = 0;
	virtual void TruncateInstrument() = 0;

	virtual void CreatePrimaryAccount() = 0;
	virtual void DropPrimaryAccount() = 0;
	virtual void InsertPrimaryAccount(mdb::PrimaryAccount* record) = 0;
	virtual void BatchInsertPrimaryAccount(std::list<mdb::PrimaryAccount*>* records) = 0;
	virtual void DeletePrimaryAccount(mdb::PrimaryAccount* record) = 0;
	virtual void DeletePrimaryAccountByOfferIDIndex(mdb::PrimaryAccount* record) = 0;
	virtual void UpdatePrimaryAccount(mdb::PrimaryAccount* record) = 0;
	virtual void SelectPrimaryAccount(std::list<mdb::PrimaryAccount*>& records) = 0;
	virtual void TruncatePrimaryAccount() = 0;

	virtual void CreateAccount() = 0;
	virtual void DropAccount() = 0;
	virtual void InsertAccount(mdb::Account* record) = 0;
	virtual void BatchInsertAccount(std::list<mdb::Account*>* records) = 0;
	virtual void DeleteAccount(mdb::Account* record) = 0;
	virtual void UpdateAccount(mdb::Account* record) = 0;
	virtual void SelectAccount(std::list<mdb::Account*>& records) = 0;
	virtual void TruncateAccount() = 0;

	virtual void CreateCapital() = 0;
	virtual void DropCapital() = 0;
	virtual void InsertCapital(mdb::Capital* record) = 0;
	virtual void BatchInsertCapital(std::list<mdb::Capital*>* records) = 0;
	virtual void DeleteCapital(mdb::Capital* record) = 0;
	virtual void DeleteCapitalByTradingDayIndex(mdb::Capital* record) = 0;
	virtual void UpdateCapital(mdb::Capital* record) = 0;
	virtual void SelectCapital(std::list<mdb::Capital*>& records) = 0;
	virtual void TruncateCapital() = 0;

	virtual void CreatePosition() = 0;
	virtual void DropPosition() = 0;
	virtual void InsertPosition(mdb::Position* record) = 0;
	virtual void BatchInsertPosition(std::list<mdb::Position*>* records) = 0;
	virtual void DeletePosition(mdb::Position* record) = 0;
	virtual void DeletePositionByAccountIndex(mdb::Position* record) = 0;
	virtual void DeletePositionByTradingDayIndex(mdb::Position* record) = 0;
	virtual void UpdatePosition(mdb::Position* record) = 0;
	virtual void SelectPosition(std::list<mdb::Position*>& records) = 0;
	virtual void TruncatePosition() = 0;

	virtual void CreatePositionDetail() = 0;
	virtual void DropPositionDetail() = 0;
	virtual void InsertPositionDetail(mdb::PositionDetail* record) = 0;
	virtual void BatchInsertPositionDetail(std::list<mdb::PositionDetail*>* records) = 0;
	virtual void DeletePositionDetail(mdb::PositionDetail* record) = 0;
	virtual void DeletePositionDetailByTradeMatchIndex(mdb::PositionDetail* record) = 0;
	virtual void DeletePositionDetailByTradingDayIndex(mdb::PositionDetail* record) = 0;
	virtual void UpdatePositionDetail(mdb::PositionDetail* record) = 0;
	virtual void SelectPositionDetail(std::list<mdb::PositionDetail*>& records) = 0;
	virtual void TruncatePositionDetail() = 0;

	virtual void CreateOrder() = 0;
	virtual void DropOrder() = 0;
	virtual void InsertOrder(mdb::Order* record) = 0;
	virtual void BatchInsertOrder(std::list<mdb::Order*>* records) = 0;
	virtual void DeleteOrder(mdb::Order* record) = 0;
	virtual void UpdateOrder(mdb::Order* record) = 0;
	virtual void SelectOrder(std::list<mdb::Order*>& records) = 0;
	virtual void TruncateOrder() = 0;

	virtual void CreateTrade() = 0;
	virtual void DropTrade() = 0;
	virtual void InsertTrade(mdb::Trade* record) = 0;
	virtual void BatchInsertTrade(std::list<mdb::Trade*>* records) = 0;
	virtual void DeleteTrade(mdb::Trade* record) = 0;
	virtual void UpdateTrade(mdb::Trade* record) = 0;
	virtual void SelectTrade(std::list<mdb::Trade*>& records) = 0;
	virtual void TruncateTrade() = 0;

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

	virtual void CreateDepthMarketData() = 0;
	virtual void DropDepthMarketData() = 0;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) = 0;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) = 0;
	virtual void TruncateDepthMarketData() = 0;

	virtual void CreateBarMarketData() = 0;
	virtual void DropBarMarketData() = 0;
	virtual void InsertBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void BatchInsertBarMarketData(std::list<mdb::BarMarketData*>* records) = 0;
	virtual void DeleteBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void UpdateBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void SelectBarMarketData(std::list<mdb::BarMarketData*>& records) = 0;
	virtual void TruncateBarMarketData() = 0;

	virtual void CreateMdSubscribe() = 0;
	virtual void DropMdSubscribe() = 0;
	virtual void InsertMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void BatchInsertMdSubscribe(std::list<mdb::MdSubscribe*>* records) = 0;
	virtual void DeleteMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void UpdateMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void SelectMdSubscribe(std::list<mdb::MdSubscribe*>& records) = 0;
	virtual void TruncateMdSubscribe() = 0;

	virtual void CreateMdUser() = 0;
	virtual void DropMdUser() = 0;
	virtual void InsertMdUser(mdb::MdUser* record) = 0;
	virtual void BatchInsertMdUser(std::list<mdb::MdUser*>* records) = 0;
	virtual void DeleteMdUser(mdb::MdUser* record) = 0;
	virtual void UpdateMdUser(mdb::MdUser* record) = 0;
	virtual void SelectMdUser(std::list<mdb::MdUser*>& records) = 0;
	virtual void TruncateMdUser() = 0;

	virtual void CreateMdUserLoginSession() = 0;
	virtual void DropMdUserLoginSession() = 0;
	virtual void InsertMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void BatchInsertMdUserLoginSession(std::list<mdb::MdUserLoginSession*>* records) = 0;
	virtual void DeleteMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void DeleteMdUserLoginSessionByMdUserIDIndex(mdb::MdUserLoginSession* record) = 0;
	virtual void UpdateMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void SelectMdUserLoginSession(std::list<mdb::MdUserLoginSession*>& records) = 0;
	virtual void TruncateMdUserLoginSession() = 0;

};
