#pragma once
#include <Spark/Types.h>
#include <string>

namespace quanttrading
{
    DirectionType GetOppoDirection(const DirectionType& direction);
    PosiDirectionType GetPosiDirection(const OffsetFlagType& offsetFlag, const DirectionType& direction);

    // BarPreces 与 Parquet Preces 列同格式（<n><s|m|h|d>，如 1m/5m/1h/1d），
    // 拆解为行情主键的精度枚举与周期数：s→Second、m→Minute、h→Minute×60、d→Day。
    bool ParseBarPreces(const std::string& barPreces, BarPrecesType& barPrecesType, int& barPeriod);

    // 该精度可否作为聚合目标：Second 不可表达（BarTime 为分钟粒度）、周期数 <=0 无意义。
    // 策略层声明周期与聚合器构造共用同一判据，避免两处规则漂移。
    bool IsValidBarPrecesTarget(BarPrecesType barPrecesType, int barPeriod);
}
