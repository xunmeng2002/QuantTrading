#pragma once
#include <Spark/Types.h>

namespace quanttrading
{
    DirectionType GetOppoDirection(const DirectionType& direction);
    PosiDirectionType GetPosiDirection(const OffsetFlagType& offsetFlag, const DirectionType& direction);
}
