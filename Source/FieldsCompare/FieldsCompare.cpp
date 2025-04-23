#include "FieldsCompare.h"


bool std::less<ReqSubMarketDataField>::operator()(const ReqSubMarketDataField* left, const ReqSubMarketDataField* right) const
{
	if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
	{
		return true;
	}
	else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
	{
		return false;
	}
	return strcmp(left->InstrumentID, right->InstrumentID) < 0;
}