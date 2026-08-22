#pragma once
#include "Mdb.h"
#include "Environment.h"

namespace quanttrading::backtestinit
{
    void Init(mdb::Mdb* mdb, const std::string& tradingDay, const std::string& accountID, const std::string& password);
}

