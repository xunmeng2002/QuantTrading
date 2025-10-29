#include "SimExchangeUtility.h"



bool OrderLessForPrice::operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const
{
	if (left->Price < right->Price)
		return true;
	else if (left->Price > right->Price)
		return false;
	return left->OrderID < right->OrderID;
}
bool OrderGreatForPrice::operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const
{
	if (left->Price > right->Price)
		return true;
	else if (left->Price < right->Price)
		return false;
	return left->OrderID > right->OrderID;
}
bool OrderLessForOrderID::operator()(const mdb::SEOrder* const left, const mdb::SEOrder* const right) const
{
	return left->OrderID < right->OrderID;
}
