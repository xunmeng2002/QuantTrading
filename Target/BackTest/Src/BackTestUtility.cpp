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

