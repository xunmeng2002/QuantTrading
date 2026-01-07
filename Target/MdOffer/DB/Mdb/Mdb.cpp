#include "Mdb.h"


namespace mdb
{
	Mdb::Mdb()
	{
		t_DepthMarketData = new DepthMarketDataTable(this);
		t_BarMarketData = new BarMarketDataTable(this);
	}
	void Mdb::Subscribe(MdbSubscriber* mdbSubscriber)
	{
		m_MdbSubscriber = mdbSubscriber;
		t_DepthMarketData->Subscribe(mdbSubscriber);
		t_BarMarketData->Subscribe(mdbSubscriber);
	}
	void Mdb::UnSubscribe()
	{
		t_DepthMarketData->UnSubscribe();
		t_BarMarketData->UnSubscribe();
	}
	void Mdb::InitDB()
	{
		t_DepthMarketData->InitDB();
		t_BarMarketData->InitDB();
	}
	void Mdb::SetInitStatus(bool initStatus)
	{
		t_DepthMarketData->m_DBInited = initStatus;
		t_BarMarketData->m_DBInited = initStatus;
	}
	void Mdb::Dump(const char* dir)
	{
		t_DepthMarketData->Dump(dir);
		t_BarMarketData->Dump(dir);
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
		t_DepthMarketData->TruncateTables();
		t_BarMarketData->TruncateTables();
	}
	
	void Mdb::OnDBConnected()
	{
		InitDB();
	}
	void Mdb::OnDBDisConnected()
	{
		t_DepthMarketData->m_DBInited = false;
		t_BarMarketData->m_DBInited = false;
	}
}
