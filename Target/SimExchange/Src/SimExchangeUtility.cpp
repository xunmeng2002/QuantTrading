#include "SimExchangeUtility.h"



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
