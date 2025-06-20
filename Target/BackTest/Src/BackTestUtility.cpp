#include "BackTestUtility.h"
#include <limits>
#include <string.h>



bool PositionDetialLessForOpenDate::operator()(const mdb::PositionDetail* const left, const mdb::PositionDetail* const right) const
{
	if (strcmp(left->OpenDate, right->OpenDate) < 0)
		return true;
	else if (strcmp(left->OpenDate, right->OpenDate) > 0)
		return false;
	return strcmp(left->TradeID, right->TradeID) < 0;
}
bool OrderLessForPrice::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	if (left->Price < right->Price)
		return true;
	else if (left->Price > right->Price)
		return false;
	return left->OrderID < right->OrderID;
}
bool OrderGreatForPrice::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	if (left->Price > right->Price)
		return true;
	else if (left->Price < right->Price)
		return false;
	return left->OrderID > right->OrderID;
}
bool OrderGreatForOrderID::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	return left->OrderID < right->OrderID;
}

PriceType GetMatchPrice(OrderPriceTypeType orderPriceType, PriceType orderPrice, PriceType oppoPrice, PriceType lastPrice)
{
	if (orderPriceType != OrderPriceTypeType::LimitPrice || lastPrice == std::numeric_limits<double>::infinity())
	{
		return oppoPrice;
	}
	if (oppoPrice <= orderPrice && orderPrice <= lastPrice)
		return orderPrice;
	if (oppoPrice >= orderPrice && orderPrice >= lastPrice)
		return orderPrice;

	if (orderPrice <= oppoPrice && oppoPrice <= lastPrice)
		return oppoPrice;
	if (orderPrice >= oppoPrice && oppoPrice >= lastPrice)
		return oppoPrice;
	return lastPrice;
}
