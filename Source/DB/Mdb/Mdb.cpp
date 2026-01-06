#include "Mdb.h"


namespace mdb
{
	Mdb::Mdb()
	{
		t_TradingDay = new TradingDayTable(this);
		t_Exchange = new ExchangeTable(this);
		t_Product = new ProductTable(this);
		t_HotInstrument = new HotInstrumentTable(this);
		t_Instrument = new InstrumentTable(this);
		t_PrimaryAccount = new PrimaryAccountTable(this);
		t_Account = new AccountTable(this);
		t_Capital = new CapitalTable(this);
		t_Position = new PositionTable(this);
		t_PositionDetail = new PositionDetailTable(this);
		t_Order = new OrderTable(this);
		t_Trade = new TradeTable(this);
		t_DepthMarketData = new DepthMarketDataTable(this);
		t_BarMarketData = new BarMarketDataTable(this);
		t_MdSubscribe = new MdSubscribeTable(this);
		t_SEBroker = new SEBrokerTable(this);
		t_SEInstrument = new SEInstrumentTable(this);
		t_SEOrder = new SEOrderTable(this);
		t_SETrade = new SETradeTable(this);
		t_SEBrokerLoginSession = new SEBrokerLoginSessionTable(this);
	}
	void Mdb::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
		t_TradingDay->Subscribe(mdbSubscriber);
		t_Exchange->Subscribe(mdbSubscriber);
		t_Product->Subscribe(mdbSubscriber);
		t_HotInstrument->Subscribe(mdbSubscriber);
		t_Instrument->Subscribe(mdbSubscriber);
		t_PrimaryAccount->Subscribe(mdbSubscriber);
		t_Account->Subscribe(mdbSubscriber);
		t_Capital->Subscribe(mdbSubscriber);
		t_Position->Subscribe(mdbSubscriber);
		t_PositionDetail->Subscribe(mdbSubscriber);
		t_Order->Subscribe(mdbSubscriber);
		t_Trade->Subscribe(mdbSubscriber);
		t_DepthMarketData->Subscribe(mdbSubscriber);
		t_BarMarketData->Subscribe(mdbSubscriber);
		t_MdSubscribe->Subscribe(mdbSubscriber);
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
		t_HotInstrument->UnSubscribe();
		t_Instrument->UnSubscribe();
		t_PrimaryAccount->UnSubscribe();
		t_Account->UnSubscribe();
		t_Capital->UnSubscribe();
		t_Position->UnSubscribe();
		t_PositionDetail->UnSubscribe();
		t_Order->UnSubscribe();
		t_Trade->UnSubscribe();
		t_DepthMarketData->UnSubscribe();
		t_BarMarketData->UnSubscribe();
		t_MdSubscribe->UnSubscribe();
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
		t_HotInstrument->InitDB();
		t_Instrument->InitDB();
		t_PrimaryAccount->InitDB();
		t_Account->InitDB();
		t_Capital->InitDB();
		t_Position->InitDB();
		t_PositionDetail->InitDB();
		t_Order->InitDB();
		t_Trade->InitDB();
		t_DepthMarketData->InitDB();
		t_BarMarketData->InitDB();
		t_MdSubscribe->InitDB();
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
		t_HotInstrument->m_DBInited = initStatus;
		t_Instrument->m_DBInited = initStatus;
		t_PrimaryAccount->m_DBInited = initStatus;
		t_Account->m_DBInited = initStatus;
		t_Capital->m_DBInited = initStatus;
		t_Position->m_DBInited = initStatus;
		t_PositionDetail->m_DBInited = initStatus;
		t_Order->m_DBInited = initStatus;
		t_Trade->m_DBInited = initStatus;
		t_DepthMarketData->m_DBInited = initStatus;
		t_BarMarketData->m_DBInited = initStatus;
		t_MdSubscribe->m_DBInited = initStatus;
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
		t_HotInstrument->Dump(dir);
		t_Instrument->Dump(dir);
		t_PrimaryAccount->Dump(dir);
		t_Account->Dump(dir);
		t_Capital->Dump(dir);
		t_Position->Dump(dir);
		t_PositionDetail->Dump(dir);
		t_Order->Dump(dir);
		t_Trade->Dump(dir);
		t_DepthMarketData->Dump(dir);
		t_BarMarketData->Dump(dir);
		t_MdSubscribe->Dump(dir);
		t_SEBroker->Dump(dir);
		t_SEInstrument->Dump(dir);
		t_SEOrder->Dump(dir);
		t_SETrade->Dump(dir);
		t_SEBrokerLoginSession->Dump(dir);
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
		t_HotInstrument->TruncateTables();
		t_Instrument->TruncateTables();
		t_PrimaryAccount->TruncateTables();
		t_Account->TruncateTables();
		t_Capital->TruncateTables();
		t_Position->TruncateTables();
		t_PositionDetail->TruncateTables();
		t_Order->TruncateTables();
		t_Trade->TruncateTables();
		t_DepthMarketData->TruncateTables();
		t_BarMarketData->TruncateTables();
		t_MdSubscribe->TruncateTables();
		t_SEBroker->TruncateTables();
		t_SEInstrument->TruncateTables();
		t_SEOrder->TruncateTables();
		t_SETrade->TruncateTables();
		t_SEBrokerLoginSession->TruncateTables();
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
		t_HotInstrument->m_DBInited = false;
		t_Instrument->m_DBInited = false;
		t_PrimaryAccount->m_DBInited = false;
		t_Account->m_DBInited = false;
		t_Capital->m_DBInited = false;
		t_Position->m_DBInited = false;
		t_PositionDetail->m_DBInited = false;
		t_Order->m_DBInited = false;
		t_Trade->m_DBInited = false;
		t_DepthMarketData->m_DBInited = false;
		t_BarMarketData->m_DBInited = false;
		t_MdSubscribe->m_DBInited = false;
		t_SEBroker->m_DBInited = false;
		t_SEInstrument->m_DBInited = false;
		t_SEOrder->m_DBInited = false;
		t_SETrade->m_DBInited = false;
		t_SEBrokerLoginSession->m_DBInited = false;
	}
}
