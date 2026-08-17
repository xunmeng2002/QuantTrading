#pragma once
#include "MdbStructs.h"

namespace quanttrading::backtest
{
struct PositionDetialLessForOpenDate
{
	bool operator()(const mdb::PositionDetail* const left, const mdb::PositionDetail* const right) const;
};
}



