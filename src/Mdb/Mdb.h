// 本文件由 ../Templates/Cpp/Mdb/Mdb.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbTables.h"
#include "MdbTableBase.h"
#include "TableList.h"
#include <DbAdapters/DbInterface/MdbSubscriber.h>
#include <DbAdapters/DbInterface/DbSubscriber.h>
#include <vector>


namespace QuantTrading
{
	class Mdb : public DbAdapters::DbSubscriber
	{
	public:
		explicit Mdb(const TableList& tableList);
		void Subscribe(MdbSubscriber* subscriber);
		void UnSubscribe();
		void InitDb();
		void SetInitStatus(bool initStatus);
		void Dump(const char* dir);
		void CreateTables();
		void DropTables();
		void TruncateTables();

		virtual void OnDbConnected() override;
		virtual void OnDbDisConnected() override;

		TradingDayTable* TradingDays = nullptr;
		ExchangeTable* Exchanges = nullptr;
		ProductTable* Products = nullptr;
		HotInstrumentTable* HotInstruments = nullptr;
		InstrumentTable* Instruments = nullptr;
		DepthMarketDataTable* DepthMarketDatas = nullptr;
		BarMarketDataTable* BarMarketDatas = nullptr;
		MdSubscribeTable* MdSubscribes = nullptr;
		MdUserTable* MdUsers = nullptr;
		MdUserLoginSessionTable* MdUserLoginSessions = nullptr;
		PrimaryAccountTable* PrimaryAccounts = nullptr;
		AccountTable* Accounts = nullptr;
		CapitalTable* Capitals = nullptr;
		PositionTable* Positions = nullptr;
		PositionDetailTable* PositionDetails = nullptr;
		OrderTable* Orders = nullptr;
		TradeTable* Trades = nullptr;
		AccountLoginSessionTable* AccountLoginSessions = nullptr;
		PrimaryAccountLoginSessionTable* PrimaryAccountLoginSessions = nullptr;
		CommissionGroupTable* CommissionGroups = nullptr;
		BaseCommissionTable* BaseCommissions = nullptr;

	private:
		MdbSubscriber* mdbSubscriber_;
		std::vector<MdbTableBase*> tables_;
	};
}
