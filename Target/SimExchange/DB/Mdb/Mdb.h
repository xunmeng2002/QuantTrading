#pragma once
#include "MdbTables.h"
#include "MdbSubscriber.h"
#include "DBSubscriber.h"


namespace mdb
{
	class Mdb : public DBSubscriber
	{
	public:
		Mdb();
		void Subscribe(MdbSubscriber* mdbSubscriber);
		void UnSubscribe();
		void InitDB();
		void SetInitStatus(bool initStatus);
		void Dump(const char* dir);
		void CreateTables();
		void DropTables();
		void TruncateTables();
		
		virtual void OnDBConnected() override;
		virtual void OnDBDisConnected() override;

	public:
		TradingDayTable* t_TradingDay;
		ExchangeTable* t_Exchange;
		ProductTable* t_Product;
		DepthMarketDataTable* t_DepthMarketData;
		SEBrokerTable* t_SEBroker;
		SEInstrumentTable* t_SEInstrument;
		SEOrderTable* t_SEOrder;
		SETradeTable* t_SETrade;
		SEBrokerLoginSessionTable* t_SEBrokerLoginSession;
	private:
		MdbSubscriber* m_MdbSubscriber;
	};
}

