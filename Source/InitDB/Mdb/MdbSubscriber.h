#pragma once
#include "MdbStructs.h"
#include <atomic>
#include <list>


class MdbSubscriber
{
public:
	MdbSubscriber()
		:m_Connected(false)
	{
	}
	virtual void OnCreateTables() {}
	virtual void OnDropTables() {}
	virtual void OnTruncateTables() {}
	
	virtual void OnTradingDayInsert(mdb::TradingDay* record) {}
	virtual void OnTradingDayBatchInsert(std::list<mdb::TradingDay*>* records) {}
	virtual void OnTradingDayErase(mdb::TradingDay* record) {}
	virtual void OnTradingDayUpdate(mdb::TradingDay* record) {}
	virtual void OnTradingDayTruncate() {}
	
	virtual void OnExchangeInsert(mdb::Exchange* record) {}
	virtual void OnExchangeBatchInsert(std::list<mdb::Exchange*>* records) {}
	virtual void OnExchangeErase(mdb::Exchange* record) {}
	virtual void OnExchangeUpdate(mdb::Exchange* record) {}
	virtual void OnExchangeTruncate() {}
	
	virtual void OnProductInsert(mdb::Product* record) {}
	virtual void OnProductBatchInsert(std::list<mdb::Product*>* records) {}
	virtual void OnProductErase(mdb::Product* record) {}
	virtual void OnProductUpdate(mdb::Product* record) {}
	virtual void OnProductTruncate() {}
	
	virtual void OnHotInstrumentInsert(mdb::HotInstrument* record) {}
	virtual void OnHotInstrumentBatchInsert(std::list<mdb::HotInstrument*>* records) {}
	virtual void OnHotInstrumentErase(mdb::HotInstrument* record) {}
	virtual void OnHotInstrumentEraseByTradingDayIndex(mdb::HotInstrument* record) {}
	virtual void OnHotInstrumentUpdate(mdb::HotInstrument* record) {}
	virtual void OnHotInstrumentTruncate() {}
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) {}
	virtual void OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records) {}
	virtual void OnInstrumentErase(mdb::Instrument* record) {}
	virtual void OnInstrumentEraseByExchangeIDIndex(mdb::Instrument* record) {}
	virtual void OnInstrumentUpdate(mdb::Instrument* record) {}
	virtual void OnInstrumentTruncate() {}
	
	virtual void OnAccountInsert(mdb::Account* record) {}
	virtual void OnAccountBatchInsert(std::list<mdb::Account*>* records) {}
	virtual void OnAccountErase(mdb::Account* record) {}
	virtual void OnAccountUpdate(mdb::Account* record) {}
	virtual void OnAccountTruncate() {}
	

public:
	std::atomic<bool> m_Connected;
};

