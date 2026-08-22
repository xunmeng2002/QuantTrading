#pragma once
#include "Mdb.h"
#include "Environment.h"

namespace quanttrading::simexchangeinit
{
    void Init(mdb::Mdb* mdb, AccountInfo* accountInfo, const std::string& tradingDay);
}

