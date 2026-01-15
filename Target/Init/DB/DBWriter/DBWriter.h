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
#include <mutex>
#include <condition_variable>


class DBWriter : public ThreadBase, public MdbSubscriber
{
public:
	DBWriter(DB* db);
	~DBWriter();
	void Subscribe(DBSubscriber* dbSubscriber);
	DB* GetDB();
	bool Connect();
	void DisConnect();
	
	virtual void OnCreateTables() override;
	virtual void OnDropTables() override;
	virtual void OnTruncateTables() override;
	
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
	
	virtual void OnHotInstrumentInsert(mdb::HotInstrument* record) override;
	virtual void OnHotInstrumentBatchInsert(std::list<mdb::HotInstrument*>* records) override;
	virtual void OnHotInstrumentErase(mdb::HotInstrument* record) override;
	virtual void OnHotInstrumentEraseByTradingDayIndex(mdb::HotInstrument* record) override;
	virtual void OnHotInstrumentUpdate(mdb::HotInstrument* record) override;
	virtual void OnHotInstrumentTruncate() override;
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) override;
	virtual void OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records) override;
	virtual void OnInstrumentErase(mdb::Instrument* record) override;
	virtual void OnInstrumentEraseByExchangeIDIndex(mdb::Instrument* record) override;
	virtual void OnInstrumentUpdate(mdb::Instrument* record) override;
	virtual void OnInstrumentTruncate() override;
	
	virtual void OnAccountInsert(mdb::Account* record) override;
	virtual void OnAccountBatchInsert(std::list<mdb::Account*>* records) override;
	virtual void OnAccountErase(mdb::Account* record) override;
	virtual void OnAccountUpdate(mdb::Account* record) override;
	virtual void OnAccountTruncate() override;
	

protected:
	virtual void Run() override;
	void CheckConnect();
	void CheckDBOperate();
	void HandleDBOperate();
	DBOperate* GetDBOperate();

private:
	void AddDBOperate(DBOperate* dbOperate);
	
	void CreateTables(DBOperate* dbOperate);
	void DropTables(DBOperate* dbOperate);
	void TruncateTables(DBOperate* dbOperate);
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
	std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;
};

