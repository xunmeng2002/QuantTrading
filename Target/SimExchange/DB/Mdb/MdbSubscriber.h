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
	
	virtual void OnSEBrokerInsert(mdb::SEBroker* record) {}
	virtual void OnSEBrokerBatchInsert(std::list<mdb::SEBroker*>* records) {}
	virtual void OnSEBrokerErase(mdb::SEBroker* record) {}
	virtual void OnSEBrokerUpdate(mdb::SEBroker* record) {}
	virtual void OnSEBrokerTruncate() {}
	
	virtual void OnSEInstrumentInsert(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentBatchInsert(std::list<mdb::SEInstrument*>* records) {}
	virtual void OnSEInstrumentErase(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentEraseByExchangeIDIndex(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentUpdate(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentTruncate() {}
	
	virtual void OnSEOrderInsert(mdb::SEOrder* record) {}
	virtual void OnSEOrderBatchInsert(std::list<mdb::SEOrder*>* records) {}
	virtual void OnSEOrderErase(mdb::SEOrder* record) {}
	virtual void OnSEOrderEraseByAccountIDIndex(mdb::SEOrder* record) {}
	virtual void OnSEOrderUpdate(mdb::SEOrder* record) {}
	virtual void OnSEOrderTruncate() {}
	
	virtual void OnSETradeInsert(mdb::SETrade* record) {}
	virtual void OnSETradeBatchInsert(std::list<mdb::SETrade*>* records) {}
	virtual void OnSETradeErase(mdb::SETrade* record) {}
	virtual void OnSETradeEraseByAccountIDIndex(mdb::SETrade* record) {}
	virtual void OnSETradeUpdate(mdb::SETrade* record) {}
	virtual void OnSETradeTruncate() {}
	
	virtual void OnSEBrokerLoginSessionInsert(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionBatchInsert(std::list<mdb::SEBrokerLoginSession*>* records) {}
	virtual void OnSEBrokerLoginSessionErase(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionEraseByBrokerIDIndex(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionUpdate(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionTruncate() {}
	
	virtual void OnDepthMarketDataInsert(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records) {}
	virtual void OnDepthMarketDataErase(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataUpdate(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataTruncate() {}
	

public:
	std::atomic<bool> m_Connected;
};

