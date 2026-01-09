#include "Mdb.h"


namespace mdb
{
	Mdb::Mdb(): m_MdbSubscriber(nullptr)
	{
		t_Exchange = new ExchangeTable(this);
		t_Instrument = new InstrumentTable(this);
		t_DepthMarketData = new DepthMarketDataTable(this);
		t_BarMarketData = new BarMarketDataTable(this);
		t_MdSubscribe = new MdSubscribeTable(this);
		t_MdUser = new MdUserTable(this);
		t_MdUserLoginSession = new MdUserLoginSessionTable(this);
	}
	void Mdb::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
		t_Exchange->Subscribe(mdbSubscriber);
		t_Instrument->Subscribe(mdbSubscriber);
		t_DepthMarketData->Subscribe(mdbSubscriber);
		t_BarMarketData->Subscribe(mdbSubscriber);
		t_MdSubscribe->Subscribe(mdbSubscriber);
		t_MdUser->Subscribe(mdbSubscriber);
		t_MdUserLoginSession->Subscribe(mdbSubscriber);
	}
	void Mdb::UnSubscribe()
	{
		t_Exchange->UnSubscribe();
		t_Instrument->UnSubscribe();
		t_DepthMarketData->UnSubscribe();
		t_BarMarketData->UnSubscribe();
		t_MdSubscribe->UnSubscribe();
		t_MdUser->UnSubscribe();
		t_MdUserLoginSession->UnSubscribe();
	}
	void Mdb::InitDB()
	{
		CreateTables();
		t_Exchange->InitDB();
		t_Instrument->InitDB();
		t_DepthMarketData->InitDB();
		t_BarMarketData->InitDB();
		t_MdSubscribe->InitDB();
		t_MdUser->InitDB();
		t_MdUserLoginSession->InitDB();
	}
	void Mdb::SetInitStatus(bool initStatus)
	{
		t_Exchange->m_DBInited = initStatus;
		t_Instrument->m_DBInited = initStatus;
		t_DepthMarketData->m_DBInited = initStatus;
		t_BarMarketData->m_DBInited = initStatus;
		t_MdSubscribe->m_DBInited = initStatus;
		t_MdUser->m_DBInited = initStatus;
		t_MdUserLoginSession->m_DBInited = initStatus;
	}
	void Mdb::Dump(const char* dir)
	{
		t_Exchange->Dump(dir);
		t_Instrument->Dump(dir);
		t_DepthMarketData->Dump(dir);
		t_BarMarketData->Dump(dir);
		t_MdSubscribe->Dump(dir);
		t_MdUser->Dump(dir);
		t_MdUserLoginSession->Dump(dir);
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
		t_Exchange->TruncateTables();
		t_Instrument->TruncateTables();
		t_DepthMarketData->TruncateTables();
		t_BarMarketData->TruncateTables();
		t_MdSubscribe->TruncateTables();
		t_MdUser->TruncateTables();
		t_MdUserLoginSession->TruncateTables();
	}
	
	void Mdb::OnDBConnected()
	{
		InitDB();
	}
	void Mdb::OnDBDisConnected()
	{
		t_Exchange->m_DBInited = false;
		t_Instrument->m_DBInited = false;
		t_DepthMarketData->m_DBInited = false;
		t_BarMarketData->m_DBInited = false;
		t_MdSubscribe->m_DBInited = false;
		t_MdUser->m_DBInited = false;
		t_MdUserLoginSession->m_DBInited = false;
	}
}
