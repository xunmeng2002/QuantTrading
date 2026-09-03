#pragma once
#include <QuantTrading/Fields.h>
#include "MdbStructs.h"

void FieldToMdb(const DepthMarketDataField* field, mdb::DepthMarketData* dbStruct);
void MdbToField(const mdb::DepthMarketData* dbStruct, DepthMarketDataField* field);

void FieldToMdb(const BarMarketDataField* field, mdb::BarMarketData* dbStruct);
void MdbToField(const mdb::BarMarketData* dbStruct, BarMarketDataField* field);

void MdbToField(const mdb::Order* dbStruct, OrderField* field);
void MdbToField(const mdb::Trade* dbStruct, TradeField* field);
