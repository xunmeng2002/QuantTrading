#pragma once
#include "Types.h"
#include "Fields.h"
#include "MdbStructs.h"

DirectionType GetOppoDirection(const DirectionType& direction);
PosiDirectionType GetPosiDirection(const OffsetFlagType& offsetFlag, const DirectionType& direction);


void PackageToMdb(DepthMarketDataField* field, mdb::DepthMarketData* dbStruct);
void MdbToPackage(mdb::DepthMarketData* dbStruct, DepthMarketDataField* field);

void PackageToMdb(BarMarketDataField* field, mdb::BarMarketData* dbStruct);
void MdbToPackage(mdb::BarMarketData* dbStruct, BarMarketDataField* field);

