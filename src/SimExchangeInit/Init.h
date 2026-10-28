#pragma once
#include "LockBased/Mdb.h"
#include "Environment.h"
#include <string>

using QuantTrading::AccountInfo;
namespace QuantTrading::SimExchangeInit
{
    void Init(QuantTrading::Mdb* mdb, AccountInfo* accountInfo, const std::string& tradingDay);
}

