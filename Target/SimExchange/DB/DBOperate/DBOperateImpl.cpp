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
	case TradingDay::TableID:
	{
		((TradingDay*)Record)->Free();
		break;
	}
	case Exchange::TableID:
	{
		((Exchange*)Record)->Free();
		break;
	}
	case Product::TableID:
	{
		((Product*)Record)->Free();
		break;
	}
	case SEBroker::TableID:
	{
		((SEBroker*)Record)->Free();
		break;
	}
	case SEInstrument::TableID:
	{
		((SEInstrument*)Record)->Free();
		break;
	}
	case SEOrder::TableID:
	{
		((SEOrder*)Record)->Free();
		break;
	}
	case SETrade::TableID:
	{
		((SETrade*)Record)->Free();
		break;
	}
	case SEBrokerLoginSession::TableID:
	{
		((SEBrokerLoginSession*)Record)->Free();
		break;
	}
	case DepthMarketData::TableID:
	{
		((DepthMarketData*)Record)->Free();
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
	case TradingDay::TableID:
	{
		return ((TradingDay*)Record)->GetDebugString();
	}
	case Exchange::TableID:
	{
		return ((Exchange*)Record)->GetDebugString();
	}
	case Product::TableID:
	{
		return ((Product*)Record)->GetDebugString();
	}
	case SEBroker::TableID:
	{
		return ((SEBroker*)Record)->GetDebugString();
	}
	case SEInstrument::TableID:
	{
		return ((SEInstrument*)Record)->GetDebugString();
	}
	case SEOrder::TableID:
	{
		return ((SEOrder*)Record)->GetDebugString();
	}
	case SETrade::TableID:
	{
		return ((SETrade*)Record)->GetDebugString();
	}
	case SEBrokerLoginSession::TableID:
	{
		return ((SEBrokerLoginSession*)Record)->GetDebugString();
	}
	case DepthMarketData::TableID:
	{
		return ((DepthMarketData*)Record)->GetDebugString();
	}
	default:
		break;
	}
	return "";
}
