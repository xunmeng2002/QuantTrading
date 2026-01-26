#pragma once
#include "MdbStructs.h"


struct PositionDetialLessForOpenDate
{
	bool operator()(const mdb::PositionDetail* const left, const mdb::PositionDetail* const right) const;
};



