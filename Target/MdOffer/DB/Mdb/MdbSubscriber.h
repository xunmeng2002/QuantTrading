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
	virtual void OnCreateTables() {}
	virtual void OnDropTables() {}
	virtual void OnTruncateTables() {}
	
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
	

public:
	std::atomic<bool> m_Connected;
};

