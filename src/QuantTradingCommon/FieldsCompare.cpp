#include "FieldsCompare.h"
#include <string.h>

bool std::less<ReqSubMarketDataField>::operator()(const ReqSubMarketDataField* left, const ReqSubMarketDataField* right) const
{
    int exchangeCmp = strcmp(left->ExchangeID, right->ExchangeID);
    if (exchangeCmp < 0)
    {
        return true;
    }
    if (exchangeCmp > 0)
    {
        return false;
    }
    return strcmp(left->InstrumentID, right->InstrumentID) < 0;
}
bool std::less<ReqSubMarketDataField>::operator()(const ReqSubMarketDataField left, const ReqSubMarketDataField right) const
{
    int exchangeCmp = strcmp(left.ExchangeID, right.ExchangeID);
    if (exchangeCmp < 0)
    {
        return true;
    }
    if (exchangeCmp > 0)
    {
        return false;
    }
    return strcmp(left.InstrumentID, right.InstrumentID) < 0;
}
