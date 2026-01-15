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
	
	virtual void OnExchangeInsert(mdb::Exchange* record) {}
	virtual void OnExchangeBatchInsert(std::list<mdb::Exchange*>* records) {}
	virtual void OnExchangeErase(mdb::Exchange* record) {}
	virtual void OnExchangeUpdate(mdb::Exchange* record) {}
	virtual void OnExchangeTruncate() {}
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) {}
	virtual void OnInstrumentBatchInsert(std::list<mdb::Instrument*>* records) {}
	virtual void OnInstrumentErase(mdb::Instrument* record) {}
	virtual void OnInstrumentEraseByExchangeIDIndex(mdb::Instrument* record) {}
	virtual void OnInstrumentUpdate(mdb::Instrument* record) {}
	virtual void OnInstrumentTruncate() {}
	
	virtual void OnDepthMarketDataInsert(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataBatchInsert(std::list<mdb::DepthMarketData*>* records) {}
	virtual void OnDepthMarketDataErase(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataUpdate(mdb::DepthMarketData* record) {}
	virtual void OnDepthMarketDataTruncate() {}
	
	virtual void OnBarMarketDataInsert(mdb::BarMarketData* record) {}
	virtual void OnBarMarketDataBatchInsert(std::list<mdb::BarMarketData*>* records) {}
	virtual void OnBarMarketDataErase(mdb::BarMarketData* record) {}
	virtual void OnBarMarketDataUpdate(mdb::BarMarketData* record) {}
	virtual void OnBarMarketDataTruncate() {}
	
	virtual void OnMdSubscribeInsert(mdb::MdSubscribe* record) {}
	virtual void OnMdSubscribeBatchInsert(std::list<mdb::MdSubscribe*>* records) {}
	virtual void OnMdSubscribeErase(mdb::MdSubscribe* record) {}
	virtual void OnMdSubscribeUpdate(mdb::MdSubscribe* record) {}
	virtual void OnMdSubscribeTruncate() {}
	
	virtual void OnMdUserInsert(mdb::MdUser* record) {}
	virtual void OnMdUserBatchInsert(std::list<mdb::MdUser*>* records) {}
	virtual void OnMdUserErase(mdb::MdUser* record) {}
	virtual void OnMdUserUpdate(mdb::MdUser* record) {}
	virtual void OnMdUserTruncate() {}
	
	virtual void OnMdUserLoginSessionInsert(mdb::MdUserLoginSession* record) {}
	virtual void OnMdUserLoginSessionBatchInsert(std::list<mdb::MdUserLoginSession*>* records) {}
	virtual void OnMdUserLoginSessionErase(mdb::MdUserLoginSession* record) {}
	virtual void OnMdUserLoginSessionEraseByMdUserIDIndex(mdb::MdUserLoginSession* record) {}
	virtual void OnMdUserLoginSessionUpdate(mdb::MdUserLoginSession* record) {}
	virtual void OnMdUserLoginSessionTruncate() {}
	

public:
	std::atomic<bool> m_Connected;
};

