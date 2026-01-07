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

