#pragma once
#include "MdbStructs.h"


struct OrderLessForPrice
{
	bool operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const;
};
struct OrderGreatForPrice
{
	bool operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const;
};
struct OrderLessForOrderID
{
	bool operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const;
};

