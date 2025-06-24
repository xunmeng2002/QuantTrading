#pragma once
#include "ThreadBase.h"
#include "DBOperate.h"
#include "MdbSubscriber.h"
#include "MdbStructs.h"
#include "DB.h"
#include "DBSubscriber.h"
#include "Timer.h"
#include <list>
#include <atomic>


class DBWriter : public ThreadBase, public MdbSubscriber
{
public:
	DBWriter(DB* db);
	~DBWriter();
	void Subscribe(DBSubscriber* dbSubscriber);
	DB* GetDB();
	bool Connect();
	void DisConnect();
	
	virtual void TruncateTables() override;
	virtual void OnTradingDayInsert(mdb::TradingDay* record) override;
	virtual void OnTradingDayBatchInsert(std::list<mdb::TradingDay*>* records) override;
	virtual void OnTradingDayErase(mdb::TradingDay* record) override;
	virtual void OnTradingDayUpdate(mdb::TradingDay* record) override;
	virtual void OnTradingDayTruncate() override;
	
	virtual void OnExchangeInsert(mdb::Exchange* record) override;
	virtual void OnExchangeBatchInsert(std::list<mdb::Exchange*>* records) override;
	virtual void OnExchangeErase(mdb::Exchange* record) override;
	virtual void OnExchangeUpdate(mdb::Exchange* record) override;
	virtual void OnExchangeTruncate() override;
	
	virtual void OnProductInsert(mdb::Product* record) override;
	virtual void OnProductBatchInsert(std::list<mdb::Product*>* records) override;
	virtual void OnProductErase(mdb::Product* record) override;
	virtual void OnProductUpdate(mdb::Product* record) override;
	virtual void OnProductTruncate() override;
	
	virtual void OnDepthMarketDataInsert(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records) override;
	virtual void OnDepthMarketDataErase(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataUpdate(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataTruncate() override;
	
	virtual void OnSEBrokerInsert(mdb::SEBroker* record) override;
	virtual void OnSEBrokerBatchInsert(std::list<mdb::SEBroker*>* records) override;
	virtual void OnSEBrokerErase(mdb::SEBroker* record) override;
	virtual void OnSEBrokerUpdate(mdb::SEBroker* record) override;
	virtual void OnSEBrokerTruncate() override;
	
	virtual void OnSEInstrumentInsert(mdb::SEInstrument* record) override;
	virtual void OnSEInstrumentBatchInsert(std::list<mdb::SEInstrument*>* records) override;
	virtual void OnSEInstrumentErase(mdb::SEInstrument* record) override;
	virtual void OnSEInstrumentEraseByExchangeIDIndex(mdb::SEInstrument* record) override;
	virtual void OnSEInstrumentUpdate(mdb::SEInstrument* record) override;
	virtual void OnSEInstrumentTruncate() override;
	
	virtual void OnSEOrderInsert(mdb::SEOrder* record) override;
	virtual void OnSEOrderBatchInsert(std::list<mdb::SEOrder*>* records) override;
	virtual void OnSEOrderErase(mdb::SEOrder* record) override;
	virtual void OnSEOrderEraseByAccountIDIndex(mdb::SEOrder* record) override;
	virtual void OnSEOrderUpdate(mdb::SEOrder* record) override;
	virtual void OnSEOrderTruncate() override;
	
	virtual void OnSETradeInsert(mdb::SETrade* record) override;
	virtual void OnSETradeBatchInsert(std::list<mdb::SETrade*>* records) override;
	virtual void OnSETradeErase(mdb::SETrade* record) override;
	virtual void OnSETradeEraseByAccountIDIndex(mdb::SETrade* record) override;
	virtual void OnSETradeUpdate(mdb::SETrade* record) override;
	virtual void OnSETradeTruncate() override;
	
	virtual void OnSEBrokerLoginSessionInsert(mdb::SEBrokerLoginSession* record) override;
	virtual void OnSEBrokerLoginSessionBatchInsert(std::list<mdb::SEBrokerLoginSession*>* records) override;
	virtual void OnSEBrokerLoginSessionErase(mdb::SEBrokerLoginSession* record) override;
	virtual void OnSEBrokerLoginSessionEraseByBrokerIDIndex(mdb::SEBrokerLoginSession* record) override;
	virtual void OnSEBrokerLoginSessionUpdate(mdb::SEBrokerLoginSession* record) override;
	virtual void OnSEBrokerLoginSessionTruncate() override;
	

protected:
	virtual void Run() override;
	void CheckConnect();
	void CheckDBOperate();
	void HandleDBOperate();
	DBOperate* GetDBOperate();

private:
	void InsertRecord(DBOperate* dbOperate);
	void DeleteRecord(DBOperate* dbOperate);
	void DeleteRecordByIndex(DBOperate* dbOperate);
	void UpdateRecord(DBOperate* dbOperate);
	void BatchInsertRecords(DBOperate* dbOperate);
	void TruncateTable(DBOperate* dbOperate);

private:
	DB* m_DB;
	DBSubscriber* m_DBSubscriber;
	std::list<DBOperate*> m_DBOperates;
};

