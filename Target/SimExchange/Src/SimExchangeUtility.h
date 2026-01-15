#pragma once
#include "MdbStructs.h"


struct OrderLessForPrice
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderLessForPriceOpposite
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderLessForOrderID
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};

