#pragma once
#include "Mdb.h"
#include "Environment.h"

using quanttrading::quanttradingcommon::AccountInfo;
namespace quanttrading::simexchangeinit
{
    void Init(mdb::Mdb* mdb, AccountInfo* accountInfo, const std::string& tradingDay);
}

