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
	virtual void OnInstrumentUpdate(mdb::Instrument* record) {}
	virtual void OnInstrumentTruncate() {}
	
	virtual void OnPrimaryAccountInsert(mdb::PrimaryAccount* record) {}
	virtual void OnPrimaryAccountBatchInsert(std::list<mdb::PrimaryAccount*>* records) {}
	virtual void OnPrimaryAccountErase(mdb::PrimaryAccount* record) {}
	virtual void OnPrimaryAccountEraseByOfferIDIndex(mdb::PrimaryAccount* record) {}
	virtual void OnPrimaryAccountUpdate(mdb::PrimaryAccount* record) {}
	virtual void OnPrimaryAccountTruncate() {}
	
	virtual void OnAccountInsert(mdb::Account* record) {}
	virtual void OnAccountBatchInsert(std::list<mdb::Account*>* records) {}
	virtual void OnAccountErase(mdb::Account* record) {}
	virtual void OnAccountUpdate(mdb::Account* record) {}
	virtual void OnAccountTruncate() {}
	
	virtual void OnCapitalInsert(mdb::Capital* record) {}
	virtual void OnCapitalBatchInsert(std::list<mdb::Capital*>* records) {}
	virtual void OnCapitalErase(mdb::Capital* record) {}
	virtual void OnCapitalEraseByTradingDayIndex(mdb::Capital* record) {}
	virtual void OnCapitalUpdate(mdb::Capital* record) {}
	virtual void OnCapitalTruncate() {}
	
	virtual void OnPositionInsert(mdb::Position* record) {}
	virtual void OnPositionBatchInsert(std::list<mdb::Position*>* records) {}
	virtual void OnPositionErase(mdb::Position* record) {}
	virtual void OnPositionEraseByAccountIndex(mdb::Position* record) {}
	virtual void OnPositionEraseByTradingDayIndex(mdb::Position* record) {}
	virtual void OnPositionUpdate(mdb::Position* record) {}
	virtual void OnPositionTruncate() {}
	
	virtual void OnPositionDetailInsert(mdb::PositionDetail* record) {}
	virtual void OnPositionDetailBatchInsert(std::list<mdb::PositionDetail*>* records) {}
	virtual void OnPositionDetailErase(mdb::PositionDetail* record) {}
	virtual void OnPositionDetailEraseByTradeMatchIndex(mdb::PositionDetail* record) {}
	virtual void OnPositionDetailEraseByTradingDayIndex(mdb::PositionDetail* record) {}
	virtual void OnPositionDetailUpdate(mdb::PositionDetail* record) {}
	virtual void OnPositionDetailTruncate() {}
	
	virtual void OnOrderInsert(mdb::Order* record) {}
	virtual void OnOrderBatchInsert(std::list<mdb::Order*>* records) {}
	virtual void OnOrderErase(mdb::Order* record) {}
	virtual void OnOrderUpdate(mdb::Order* record) {}
	virtual void OnOrderTruncate() {}
	
	virtual void OnTradeInsert(mdb::Trade* record) {}
	virtual void OnTradeBatchInsert(std::list<mdb::Trade*>* records) {}
	virtual void OnTradeErase(mdb::Trade* record) {}
	virtual void OnTradeUpdate(mdb::Trade* record) {}
	virtual void OnTradeTruncate() {}
	
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
	
	virtual void OnSEBrokerInsert(mdb::SEBroker* record) {}
	virtual void OnSEBrokerBatchInsert(std::list<mdb::SEBroker*>* records) {}
	virtual void OnSEBrokerErase(mdb::SEBroker* record) {}
	virtual void OnSEBrokerUpdate(mdb::SEBroker* record) {}
	virtual void OnSEBrokerTruncate() {}
	
	virtual void OnSEInstrumentInsert(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentBatchInsert(std::list<mdb::SEInstrument*>* records) {}
	virtual void OnSEInstrumentErase(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentUpdate(mdb::SEInstrument* record) {}
	virtual void OnSEInstrumentTruncate() {}
	
	virtual void OnSEOrderInsert(mdb::SEOrder* record) {}
	virtual void OnSEOrderBatchInsert(std::list<mdb::SEOrder*>* records) {}
	virtual void OnSEOrderErase(mdb::SEOrder* record) {}
	virtual void OnSEOrderUpdate(mdb::SEOrder* record) {}
	virtual void OnSEOrderTruncate() {}
	
	virtual void OnSETradeInsert(mdb::SETrade* record) {}
	virtual void OnSETradeBatchInsert(std::list<mdb::SETrade*>* records) {}
	virtual void OnSETradeErase(mdb::SETrade* record) {}
	virtual void OnSETradeUpdate(mdb::SETrade* record) {}
	virtual void OnSETradeTruncate() {}
	
	virtual void OnSEBrokerLoginSessionInsert(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionBatchInsert(std::list<mdb::SEBrokerLoginSession*>* records) {}
	virtual void OnSEBrokerLoginSessionErase(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionEraseByBrokerIDIndex(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionUpdate(mdb::SEBrokerLoginSession* record) {}
	virtual void OnSEBrokerLoginSessionTruncate() {}
	

public:
	std::atomic<bool> m_Connected;
};

