#pragma once
#include "TableOperate.h"

class TableOperateImpl : public TableOperate
{
public:
	virtual void Free() override;
	virtual void FreeRecord() override;
	virtual void FreeRecords() override;
	virtual const char* GetDebugString() const override;
};
