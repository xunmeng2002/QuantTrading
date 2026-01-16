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
	case HotInstrument::TableID:
	{
		((HotInstrument*)Record)->Free();
		break;
	}
	case Instrument::TableID:
	{
		((Instrument*)Record)->Free();
		break;
	}
	case Account::TableID:
	{
		((Account*)Record)->Free();
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
	case HotInstrument::TableID:
	{
		return ((HotInstrument*)Record)->GetDebugString();
	}
	case Instrument::TableID:
	{
		return ((Instrument*)Record)->GetDebugString();
	}
	case Account::TableID:
	{
		return ((Account*)Record)->GetDebugString();
	}
	default:
		break;
	}
	return "";
}
