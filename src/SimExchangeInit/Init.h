#pragma once
#include "Mdb.h"
#include "Environment.h"
#include <string>

using quanttrading::AccountInfo;
namespace quanttrading::simexchangeinit
{
    void Init(mdb::Mdb* mdb, AccountInfo* accountInfo, const std::string& tradingDay);
}

