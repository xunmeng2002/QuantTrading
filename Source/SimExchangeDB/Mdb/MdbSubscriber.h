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
	virtual void TruncateTables() {}
	virtual void OnTradingDayInsert(mdb::TradingDay* record) {}
	virtual void OnTradingDayErase(mdb::TradingDay* record) {}
	virtual void OnTradingDayUpdate(mdb::TradingDay* record) {}
	virtual void OnTradingDayReplace(mdb::TradingDay* record) {}
	virtual void OnTradingDayTruncate() {}
	
	virtual void OnExchangeInsert(mdb::Exchange* record) {}
	virtual void OnExchangeErase(mdb::Exchange* record) {}
	virtual void OnExchangeUpdate(mdb::Exchange* record) {}
	virtual void OnExchangeReplace(mdb::Exchange* record) {}
	virtual void OnExchangeTruncate() {}
	
	virtual void OnProductInsert(mdb::Product* record) {}
	virtual void OnProductErase(mdb::Product* record) {}
	virtual void OnProductUpdate(mdb::Product* record) {}
	virtual void OnProductReplace(mdb::Product* record) {}
	virtual void OnProductTruncate() {}
	
	virtual void OnInstrumentInsert(mdb::Instrument* record) {}
	virtual void OnInstrumentErase(mdb::Instrument* record) {}
	virtual void OnInstrumentUpdate(mdb::Instrument* record) {}
	virtual void OnInstrumentReplace(mdb::Instrument* record) {}
	virtual void OnInstrumentTruncate() {}
	
	virtual void OnAccountInsert(mdb::Account* record) {}
	virtual void OnAccountErase(mdb::Account* record) {}
	virtual void OnAccountUpdate(mdb::Account* record) {}
	virtual void OnAccountReplace(mdb::Account* record) {}
	virtual void OnAccountTruncate() {}
	
	virtual void OnPositionInsert(mdb::Position* record) {}
	virtual void OnPositionErase(mdb::Position* record) {}
	virtual void OnPositionUpdate(mdb::Position* record) {}
	virtual void OnPositionReplace(mdb::Position* record) {}
	virtual void OnPositionTruncate() {}
	
	virtual void OnOrderInsert(mdb::Order* record) {}
	virtual void OnOrderErase(mdb::Order* record) {}
	virtual void OnOrderUpdate(mdb::Order* record) {}
	virtual void OnOrderReplace(mdb::Order* record) {}
	virtual void OnOrderTruncate() {}
	
	virtual void OnTradeInsert(mdb::Trade* record) {}
	virtual void OnTradeErase(mdb::Trade* record) {}
	virtual void OnTradeUpdate(mdb::Trade* record) {}
	virtual void OnTradeReplace(mdb::Trade* record) {}
	virtual void OnTradeTruncate() {}
	
	virtual void OnMdTickInsert(mdb::MdTick* record) {}
	virtual void OnMdTickErase(mdb::MdTick* record) {}
	virtual void OnMdTickUpdate(mdb::MdTick* record) {}
	virtual void OnMdTickReplace(mdb::MdTick* record) {}
	virtual void OnMdTickTruncate() {}
	

public:
	std::atomic<bool> m_Connected;
};

