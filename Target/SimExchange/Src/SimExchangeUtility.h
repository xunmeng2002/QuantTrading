#pragma once
#include "MdbStructs.h"


struct OrderLessForPrice
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderGreatForPrice
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderGreatForOrderID
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};

