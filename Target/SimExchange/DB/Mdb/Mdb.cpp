#include "Mdb.h"


namespace mdb
{
	Mdb::Mdb(): m_MdbSubscriber(nullptr)
	{
		t_TradingDay = new TradingDayTable(this);
		t_Exchange = new ExchangeTable(this);
		t_Product = new ProductTable(this);
		t_Instrument = new InstrumentTable(this);
		t_DepthMarketData = new DepthMarketDataTable(this);
		t_BarMarketData = new BarMarketDataTable(this);
		t_PrimaryAccount = new PrimaryAccountTable(this);
		t_Account = new AccountTable(this);
		t_Order = new OrderTable(this);
		t_Trade = new TradeTable(this);
		t_AccountLoginSession = new AccountLoginSessionTable(this);
	}
	void Mdb::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
		t_TradingDay->Subscribe(mdbSubscriber);
		t_Exchange->Subscribe(mdbSubscriber);
		t_Product->Subscribe(mdbSubscriber);
		t_Instrument->Subscribe(mdbSubscriber);
		t_DepthMarketData->Subscribe(mdbSubscriber);
		t_BarMarketData->Subscribe(mdbSubscriber);
		t_PrimaryAccount->Subscribe(mdbSubscriber);
		t_Account->Subscribe(mdbSubscriber);
		t_Order->Subscribe(mdbSubscriber);
		t_Trade->Subscribe(mdbSubscriber);
		t_AccountLoginSession->Subscribe(mdbSubscriber);
	}
	void Mdb::UnSubscribe()
	{
		t_TradingDay->UnSubscribe();
		t_Exchange->UnSubscribe();
		t_Product->UnSubscribe();
		t_Instrument->UnSubscribe();
		t_DepthMarketData->UnSubscribe();
		t_BarMarketData->UnSubscribe();
		t_PrimaryAccount->UnSubscribe();
		t_Account->UnSubscribe();
		t_Order->UnSubscribe();
		t_Trade->UnSubscribe();
		t_AccountLoginSession->UnSubscribe();
	}
	void Mdb::InitDB()
	{
		CreateTables();
		t_TradingDay->InitDB();
		t_Exchange->InitDB();
		t_Product->InitDB();
		t_Instrument->InitDB();
		t_DepthMarketData->InitDB();
		t_BarMarketData->InitDB();
		t_PrimaryAccount->InitDB();
		t_Account->InitDB();
		t_Order->InitDB();
		t_Trade->InitDB();
		t_AccountLoginSession->InitDB();
	}
	void Mdb::SetInitStatus(bool initStatus)
	{
		t_TradingDay->m_DBInited = initStatus;
		t_Exchange->m_DBInited = initStatus;
		t_Product->m_DBInited = initStatus;
		t_Instrument->m_DBInited = initStatus;
		t_DepthMarketData->m_DBInited = initStatus;
		t_BarMarketData->m_DBInited = initStatus;
		t_PrimaryAccount->m_DBInited = initStatus;
		t_Account->m_DBInited = initStatus;
		t_Order->m_DBInited = initStatus;
		t_Trade->m_DBInited = initStatus;
		t_AccountLoginSession->m_DBInited = initStatus;
	}
	void Mdb::Dump(const char* dir)
	{
		t_TradingDay->Dump(dir);
		t_Exchange->Dump(dir);
		t_Product->Dump(dir);
		t_Instrument->Dump(dir);
		t_DepthMarketData->Dump(dir);
		t_BarMarketData->Dump(dir);
		t_PrimaryAccount->Dump(dir);
		t_Account->Dump(dir);
		t_Order->Dump(dir);
		t_Trade->Dump(dir);
		t_AccountLoginSession->Dump(dir);
	}
	void Mdb::CreateTables()
	{
		if (m_MdbSubscriber != nullptr)
		{
			m_MdbSubscriber->OnCreateTables();	
		}
	}
	void Mdb::DropTables()
	{
		if (m_MdbSubscriber != nullptr)
		{
			m_MdbSubscriber->OnDropTables();
		}
	}
	void Mdb::TruncateTables()
	{
		if (m_MdbSubscriber != nullptr)
		{
			m_MdbSubscriber->OnTruncateTables();
		}
		t_TradingDay->TruncateTables();
		t_Exchange->TruncateTables();
		t_Product->TruncateTables();
		t_Instrument->TruncateTables();
		t_DepthMarketData->TruncateTables();
		t_BarMarketData->TruncateTables();
		t_PrimaryAccount->TruncateTables();
		t_Account->TruncateTables();
		t_Order->TruncateTables();
		t_Trade->TruncateTables();
		t_AccountLoginSession->TruncateTables();
	}
	
	void Mdb::OnDBConnected()
	{
		InitDB();
	}
	void Mdb::OnDBDisConnected()
	{
		t_TradingDay->m_DBInited = false;
		t_Exchange->m_DBInited = false;
		t_Product->m_DBInited = false;
		t_Instrument->m_DBInited = false;
		t_DepthMarketData->m_DBInited = false;
		t_BarMarketData->m_DBInited = false;
		t_PrimaryAccount->m_DBInited = false;
		t_Account->m_DBInited = false;
		t_Order->m_DBInited = false;
		t_Trade->m_DBInited = false;
		t_AccountLoginSession->m_DBInited = false;
	}
}
