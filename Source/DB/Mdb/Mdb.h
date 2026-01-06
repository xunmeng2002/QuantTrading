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
		HotInstrumentTable* t_HotInstrument;
		InstrumentTable* t_Instrument;
		PrimaryAccountTable* t_PrimaryAccount;
		AccountTable* t_Account;
		CapitalTable* t_Capital;
		PositionTable* t_Position;
		PositionDetailTable* t_PositionDetail;
		OrderTable* t_Order;
		TradeTable* t_Trade;
		DepthMarketDataTable* t_DepthMarketData;
		BarMarketDataTable* t_BarMarketData;
		MdSubscribeTable* t_MdSubscribe;
		SEBrokerTable* t_SEBroker;
		SEInstrumentTable* t_SEInstrument;
		SEOrderTable* t_SEOrder;
		SETradeTable* t_SETrade;
		SEBrokerLoginSessionTable* t_SEBrokerLoginSession;
	private:
		MdbSubscriber* m_MdbSubscriber;
	};
}

