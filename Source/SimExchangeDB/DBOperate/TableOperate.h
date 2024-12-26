#pragma once
#include "Types.h"

class TableOperate
{
public:
	static TableOperate* Allocate();
	void Free();
	void FreeRecord();
	void FreeRecords();
	const char* GetDebugString() const;

	DBOperateType Operate;
	unsigned int TableID;
	unsigned int IndexID;
	void* Record;
};
