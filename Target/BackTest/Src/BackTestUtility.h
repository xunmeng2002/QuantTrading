#pragma once
#include "MdbStructs.h"


struct PositionDetialLessForOpenDate
{
	bool operator()(const mdb::PositionDetail* const left, const mdb::PositionDetail* const right) const;
};
struct OrderLessForPrice
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderGreatForPrice
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};
struct OrderLessForOrderID
{
	bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
};

PriceType GetMatchPrice(OrderPriceTypeType orderPriceType, PriceType orderPrice, PriceType oppoPrice, PriceType lastPrice);

