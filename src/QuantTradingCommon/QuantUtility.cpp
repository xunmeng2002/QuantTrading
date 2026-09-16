#include "QuantUtility.h"


namespace QuantTrading
{
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
    bool ParseBarPreces(const std::string& barPreces, BarPrecesType& barPrecesType, int& barPeriod)
    {
        if (barPreces.size() < 2 || barPreces.size() > 6)
        {
            return false;
        }
        const char unit = barPreces.back();
        int count = 0;
        for (std::size_t index = 0; index + 1 < barPreces.size(); ++index)
        {
            if (barPreces[index] < '0' || barPreces[index] > '9')
            {
                return false;
            }
            count = count * 10 + (barPreces[index] - '0');
        }
        if (count <= 0)
        {
            return false;
        }
        switch (unit)
        {
            case 's':
                barPrecesType = BarPrecesType::Second;
                break;
            case 'm':
            case 'h':
                barPrecesType = BarPrecesType::Minute;
                barPeriod = unit == 'h' ? count * 60 : count;
                return true;
            case 'd':
                barPrecesType = BarPrecesType::Day;
                break;
            default:
                return false;
        }
        barPeriod = count;
        return true;
    }
    bool IsValidBarPrecesTarget(BarPrecesType barPrecesType, int barPeriod)
    {
        return barPrecesType != BarPrecesType::Second && barPeriod > 0;
    }
}
