#include "FieldsCompare.h"
#include <string.h>

bool std::less<QuantTrading::ReqSubMarketDataField>::operator()(const QuantTrading::ReqSubMarketDataField* left, const QuantTrading::ReqSubMarketDataField* right) const
{
    int exchangeCmp = strcmp(left->ExchangeId, right->ExchangeId);
    if (exchangeCmp < 0)
    {
        return true;
    }
    if (exchangeCmp > 0)
    {
        return false;
    }
    return strcmp(left->InstrumentId, right->InstrumentId) < 0;
}
bool std::less<QuantTrading::ReqSubMarketDataField>::operator()(const QuantTrading::ReqSubMarketDataField left, const QuantTrading::ReqSubMarketDataField right) const
{
    int exchangeCmp = strcmp(left.ExchangeId, right.ExchangeId);
    if (exchangeCmp < 0)
    {
        return true;
    }
    if (exchangeCmp > 0)
    {
        return false;
    }
    return strcmp(left.InstrumentId, right.InstrumentId) < 0;
}
