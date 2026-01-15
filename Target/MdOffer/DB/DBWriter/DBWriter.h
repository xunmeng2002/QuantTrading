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
	
	virtual void OnExchangeInsert(mdb::Exchange* record) override;
	virtual void OnExchangeBatchInsert(std::list<mdb::Exchange*>* records) override;
	virtual void OnExchangeErase(mdb::Exchange* record) override;
	virtual void OnExchangeUpdate(mdb::Exchange* record) override;
	virtual void OnExchangeTruncate() override;
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) override;
	virtual void OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records) override;
	virtual void OnInstrumentErase(mdb::Instrument* record) override;
	virtual void OnInstrumentEraseByExchangeIDIndex(mdb::Instrument* record) override;
	virtual void OnInstrumentUpdate(mdb::Instrument* record) override;
	virtual void OnInstrumentTruncate() override;
	
	virtual void OnDepthMarketDataInsert(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records) override;
	virtual void OnDepthMarketDataErase(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataUpdate(mdb::DepthMarketData* record) override;
	virtual void OnDepthMarketDataTruncate() override;
	
	virtual void OnBarMarketDataInsert(mdb::BarMarketData* record) override;
	virtual void OnBarMarketDataBatchInsert(std::list<mdb::BarMarketData*>* records) override;
	virtual void OnBarMarketDataErase(mdb::BarMarketData* record) override;
	virtual void OnBarMarketDataUpdate(mdb::BarMarketData* record) override;
	virtual void OnBarMarketDataTruncate() override;
	
	virtual void OnMdSubscribeInsert(mdb::MdSubscribe* record) override;
	virtual void OnMdSubscribeBatchInsert(std::list<mdb::MdSubscribe*>* records) override;
	virtual void OnMdSubscribeErase(mdb::MdSubscribe* record) override;
	virtual void OnMdSubscribeUpdate(mdb::MdSubscribe* record) override;
	virtual void OnMdSubscribeTruncate() override;
	
	virtual void OnMdUserInsert(mdb::MdUser* record) override;
	virtual void OnMdUserBatchInsert(std::list<mdb::MdUser*>* records) override;
	virtual void OnMdUserErase(mdb::MdUser* record) override;
	virtual void OnMdUserUpdate(mdb::MdUser* record) override;
	virtual void OnMdUserTruncate() override;
	
	virtual void OnMdUserLoginSessionInsert(mdb::MdUserLoginSession* record) override;
	virtual void OnMdUserLoginSessionBatchInsert(std::list<mdb::MdUserLoginSession*>* records) override;
	virtual void OnMdUserLoginSessionErase(mdb::MdUserLoginSession* record) override;
	virtual void OnMdUserLoginSessionEraseByMdUserIDIndex(mdb::MdUserLoginSession* record) override;
	virtual void OnMdUserLoginSessionUpdate(mdb::MdUserLoginSession* record) override;
	virtual void OnMdUserLoginSessionTruncate() override;
	

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

