#include "DBOperateImpl.h"
#include "MemCacheTemplateSingleton.h"
#include "MdbStructs.h"
#include <cstring>

using namespace mdb;

DBOperate* DBOperate::Allocate()
{
	return ::Allocate<DBOperateImpl>();
}
void DBOperateImpl::Free()
{
	Operate = (DBOperateType)0;
	TableID = 0;
	IndexID = 0;
	Record = nullptr;
	MemCacheTemplateSingleton<DBOperate>::GetInstance().Free(this);
}
void DBOperateImpl::FreeRecord()
{
	if (Operate == DBOperateType::Insert || Operate == DBOperateType::BatchInsert || Operate == DBOperateType::Truncate)
	{
		return;
	}
	switch(TableID)
	{
	case DepthMarketData::TableID:
	{
		((DepthMarketData*)Record)->Free();
		break;
	}
	case BarMarketData::TableID:
	{
		((BarMarketData*)Record)->Free();
		break;
	}
	default:
		break;
	}
	Record = nullptr;
}
const char* DBOperateImpl::GetDebugString() const
{
	switch (TableID)
	{
	case DepthMarketData::TableID:
	{
		return ((DepthMarketData*)Record)->GetDebugString();
	}
	case BarMarketData::TableID:
	{
		return ((BarMarketData*)Record)->GetDebugString();
	}
	default:
		break;
	}
	return "";
}
