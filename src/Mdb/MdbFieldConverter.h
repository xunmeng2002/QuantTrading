#pragma once
#include <QuantTrading/Fields.h>
#include "Model/MdbStructs.h"

void FieldToMdb(const QuantTrading::DepthMarketDataField* field, QuantTrading::DepthMarketData* dbStruct);
void MdbToField(const QuantTrading::DepthMarketData* dbStruct, QuantTrading::DepthMarketDataField* field);

void FieldToMdb(const QuantTrading::BarMarketDataField* field, QuantTrading::BarMarketData* dbStruct);
void MdbToField(const QuantTrading::BarMarketData* dbStruct, QuantTrading::BarMarketDataField* field);

void MdbToField(const QuantTrading::Order* dbStruct, QuantTrading::OrderField* field);
void MdbToField(const QuantTrading::Trade* dbStruct, QuantTrading::TradeField* field);
