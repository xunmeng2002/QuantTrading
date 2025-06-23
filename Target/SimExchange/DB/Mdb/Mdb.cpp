#include "Mdb.h"


namespace mdb
{
	Mdb::Mdb()
	{
		t_TradingDay = new TradingDayTable(this);
		t_Exchange = new ExchangeTable(this);
		t_Product = new ProductTable(this);
		t_DepthMarketData = new DepthMarketDataTable(this);
		t_SEBroker = new SEBrokerTable(this);
		t_SEInstrument = new SEInstrumentTable(this);
		t_SEOrder = new SEOrderTable(this);
		t_SETrade = new SETradeTable(this);
		t_SEBrokerLoginSession = new SEBrokerLoginSessionTable(this);
	}
	void Mdb::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		t_TradingDay->Subscribe(mdbSubscriber);
		t_Exchange->Subscribe(mdbSubscriber);
		t_Product->Subscribe(mdbSubscriber);
		t_DepthMarketData->Subscribe(mdbSubscriber);
		t_SEBroker->Subscribe(mdbSubscriber);
		t_SEInstrument->Subscribe(mdbSubscriber);
		t_SEOrder->Subscribe(mdbSubscriber);
		t_SETrade->Subscribe(mdbSubscriber);
		t_SEBrokerLoginSession->Subscribe(mdbSubscriber);
	}
	void Mdb::UnSubscribe()
	{
		t_TradingDay->UnSubscribe();
		t_Exchange->UnSubscribe();
		t_Product->UnSubscribe();
		t_DepthMarketData->UnSubscribe();
		t_SEBroker->UnSubscribe();
		t_SEInstrument->UnSubscribe();
		t_SEOrder->UnSubscribe();
		t_SETrade->UnSubscribe();
		t_SEBrokerLoginSession->UnSubscribe();
	}
	void Mdb::InitDB()
	{
		t_TradingDay->InitDB();
		t_Exchange->InitDB();
		t_Product->InitDB();
		t_DepthMarketData->InitDB();
		t_SEBroker->InitDB();
		t_SEInstrument->InitDB();
		t_SEOrder->InitDB();
		t_SETrade->InitDB();
		t_SEBrokerLoginSession->InitDB();
	}
	void Mdb::SetInitStatus(bool initStatus)
	{
		t_TradingDay->m_DBInited = initStatus;
		t_Exchange->m_DBInited = initStatus;
		t_Product->m_DBInited = initStatus;
		t_DepthMarketData->m_DBInited = initStatus;
		t_SEBroker->m_DBInited = initStatus;
		t_SEInstrument->m_DBInited = initStatus;
		t_SEOrder->m_DBInited = initStatus;
		t_SETrade->m_DBInited = initStatus;
		t_SEBrokerLoginSession->m_DBInited = initStatus;
	}
	void Mdb::Dump(const char* dir)
	{
		t_TradingDay->Dump(dir);
		t_Exchange->Dump(dir);
		t_Product->Dump(dir);
		t_DepthMarketData->Dump(dir);
		t_SEBroker->Dump(dir);
		t_SEInstrument->Dump(dir);
		t_SEOrder->Dump(dir);
		t_SETrade->Dump(dir);
		t_SEBrokerLoginSession->Dump(dir);
	}
	void Mdb::TruncateTables()
	{
		t_TradingDay->TruncateTable();
		t_Exchange->TruncateTable();
		t_Product->TruncateTable();
		t_DepthMarketData->TruncateTable();
		t_SEBroker->TruncateTable();
		t_SEInstrument->TruncateTable();
		t_SEOrder->TruncateTable();
		t_SETrade->TruncateTable();
		t_SEBrokerLoginSession->TruncateTable();
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
		t_DepthMarketData->m_DBInited = false;
		t_SEBroker->m_DBInited = false;
		t_SEInstrument->m_DBInited = false;
		t_SEOrder->m_DBInited = false;
		t_SETrade->m_DBInited = false;
		t_SEBrokerLoginSession->m_DBInited = false;
	}
}
