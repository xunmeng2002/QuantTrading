#pragma once
#include "ThreadBase.h"
#include "TableOperate.h"
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
	DBWriter(const std::string& host, const std::string& user, const std::string& passwd);
	~DBWriter();
	void Subscribe(DBSubscriber* dbSubscriber);
	DB* GetDB();
	bool Connect();
	void DisConnect();
	
	virtual void TruncateTables() override;
	virtual void OnTradingDayInsert(mdb::TradingDay* record) override;
	virtual void OnTradingDayErase(mdb::TradingDay* record) override;
	virtual void OnTradingDayUpdate(mdb::TradingDay* record) override;
	virtual void OnTradingDayReplace(mdb::TradingDay* record) override;
	virtual void OnTradingDayTruncate() override;
	
	virtual void OnExchangeInsert(mdb::Exchange* record) override;
	virtual void OnExchangeErase(mdb::Exchange* record) override;
	virtual void OnExchangeUpdate(mdb::Exchange* record) override;
	virtual void OnExchangeReplace(mdb::Exchange* record) override;
	virtual void OnExchangeTruncate() override;
	
	virtual void OnProductInsert(mdb::Product* record) override;
	virtual void OnProductErase(mdb::Product* record) override;
	virtual void OnProductUpdate(mdb::Product* record) override;
	virtual void OnProductReplace(mdb::Product* record) override;
	virtual void OnProductTruncate() override;
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) override;
	virtual void OnInstrumentErase(mdb::Instrument* record) override;
	virtual void OnInstrumentUpdate(mdb::Instrument* record) override;
	virtual void OnInstrumentReplace(mdb::Instrument* record) override;
	virtual void OnInstrumentTruncate() override;
	
	virtual void OnAccountInsert(mdb::Account* record) override;
	virtual void OnAccountErase(mdb::Account* record) override;
	virtual void OnAccountUpdate(mdb::Account* record) override;
	virtual void OnAccountReplace(mdb::Account* record) override;
	virtual void OnAccountTruncate() override;
	
	virtual void OnPositionInsert(mdb::Position* record) override;
	virtual void OnPositionErase(mdb::Position* record) override;
	virtual void OnPositionUpdate(mdb::Position* record) override;
	virtual void OnPositionReplace(mdb::Position* record) override;
	virtual void OnPositionTruncate() override;
	
	virtual void OnOrderInsert(mdb::Order* record) override;
	virtual void OnOrderErase(mdb::Order* record) override;
	virtual void OnOrderUpdate(mdb::Order* record) override;
	virtual void OnOrderReplace(mdb::Order* record) override;
	virtual void OnOrderTruncate() override;
	
	virtual void OnTradeInsert(mdb::Trade* record) override;
	virtual void OnTradeErase(mdb::Trade* record) override;
	virtual void OnTradeUpdate(mdb::Trade* record) override;
	virtual void OnTradeReplace(mdb::Trade* record) override;
	virtual void OnTradeTruncate() override;
	
	virtual void OnMdTickInsert(mdb::MdTick* record) override;
	virtual void OnMdTickErase(mdb::MdTick* record) override;
	virtual void OnMdTickUpdate(mdb::MdTick* record) override;
	virtual void OnMdTickReplace(mdb::MdTick* record) override;
	virtual void OnMdTickTruncate() override;
	

protected:
	virtual void Run() override;
	void CheckConnect();
	void CheckTableOperate();
	void HandleTableOperate();
	TableOperate* GetTableOperate();

private:
	void InsertRecord(TableOperate* tableOperate);
	void DeleteRecord(TableOperate* tableOperate);
	void DeleteRecordByIndex(TableOperate* tableOperate);
	void UpdateRecord(TableOperate* tableOperate);
	void ReplaceRecord(TableOperate* tableOperate);
	void BatchUpdateRecords(TableOperate* tableOperate);
	void TruncateTable(TableOperate* tableOperate);

private:
	std::string m_Host;
	std::string m_User;
	std::string m_Passwd;
	DB* m_DB;
	DBSubscriber* m_DBSubscriber;
	std::list<TableOperate*> m_TableOperates;
};

