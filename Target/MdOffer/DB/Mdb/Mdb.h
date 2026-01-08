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
		ExchangeTable* t_Exchange;
		InstrumentTable* t_Instrument;
		DepthMarketDataTable* t_DepthMarketData;
		BarMarketDataTable* t_BarMarketData;
		MdSubscribeTable* t_MdSubscribe;
		MdUserTable* t_MdUser;
		MdUserLoginSessionTable* t_MdUserLoginSession;
	private:
		MdbSubscriber* m_MdbSubscriber;
	};
}

