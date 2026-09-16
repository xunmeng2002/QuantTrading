#pragma once
#include <QuantTrading/Fields.h>
#include "MdbStructs.h"

void FieldToMdb(const DepthMarketDataField* field, QuantTrading::DepthMarketData* dbStruct);
void MdbToField(const QuantTrading::DepthMarketData* dbStruct, DepthMarketDataField* field);

void FieldToMdb(const BarMarketDataField* field, QuantTrading::BarMarketData* dbStruct);
void MdbToField(const QuantTrading::BarMarketData* dbStruct, BarMarketDataField* field);

void MdbToField(const QuantTrading::Order* dbStruct, OrderField* field);
void MdbToField(const QuantTrading::Trade* dbStruct, TradeField* field);
