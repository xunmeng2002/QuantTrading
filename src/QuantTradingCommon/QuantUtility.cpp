#include "QuantUtility.h"


DirectionType GetOppoDirection(const DirectionType& direction)
{
	if (direction == DirectionType::Buy)
		return DirectionType::Sell;
	return DirectionType::Buy;
}
PosiDirectionType GetPosiDirection(const OffsetFlagType& offsetFlag, const DirectionType& direction)
{
	if (offsetFlag == OffsetFlagType::Open)
	{
		if (direction == DirectionType::Buy)
			return PosiDirectionType::Long;
		return PosiDirectionType::Short;
	}
	else
	{
		if (direction == DirectionType::Buy)
			return PosiDirectionType::Short;
		return PosiDirectionType::Long;
	}
}
