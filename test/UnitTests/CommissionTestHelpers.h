#pragma once
#include "TestHelpers.h"
#include "TableList.h"
#include "MdbStructs.h"
#include "CommissionCalculator.h"
#include "PositionMaintenance.h"
#include <cstring>
#include <vector>

namespace QuantTrading::UnitTest
{
    // 计费单测专用的最小表清单：只列计费链路上真被触碰的表。
    // 刻意不复用 SimExchangeTableList —— 实盘清单不含 CommissionGroup/BaseCommission，
    // 复用会让 mdb->BaseCommission 恒为 nullptr，CommissionCalculator::Apply 一步都跑不进去。
    inline const unsigned int CommissionTableIds[] =
    {
        TradingDay::TableId,
        Account::TableId,
        Capital::TableId,
        Position::TableId,
        PositionDetail::TableId,
        Order::TableId,
        Trade::TableId,
        CommissionGroup::TableId,
        BaseCommission::TableId,
    };
    inline const TableList CommissionTableList =
        { "Commission", CommissionTableIds, static_cast<int>(sizeof(CommissionTableIds) / sizeof(CommissionTableIds[0])) };

    // 装入账户行（表接管所有权，主键冲突时返回 nullptr）。手续费组号只此一处来源，
    // CommissionCalculator 靠 trade->AccountId 反查它。
    inline QuantTrading::Account* InsertCommissionAccount(QuantTrading::Mdb* commissionMdb, const char* accountId, GroupIdType commissionGroupId)
    {
        auto* account = QuantTrading::Account::Allocate();
        std::memset(account, 0, sizeof(QuantTrading::Account));
        CopyString(account->AccountId, accountId);
        account->CommissionGroupId = commissionGroupId;
        if (!commissionMdb->Account->Insert(account))
        {
            return nullptr;
        }
        return account;
    }

    // 装入费率行（表接管所有权，主键冲突时返回 nullptr）。除主键四列外全为 0，
    // 费率列由调用方按字段名补 —— 0 在计费里就是"该侧免费"，不会被当成"未配置"。
    inline QuantTrading::BaseCommission* InsertBaseCommission(QuantTrading::Mdb* commissionMdb, GroupIdType commissionGroupId,
        const char* exchangeId, const char* instrumentId, DirectionType direction)
    {
        auto* rate = QuantTrading::BaseCommission::Allocate();
        std::memset(rate, 0, sizeof(QuantTrading::BaseCommission));
        rate->CommissionGroupId = commissionGroupId;
        CopyString(rate->ExchangeId, exchangeId);
        CopyString(rate->InstrumentId, instrumentId);
        rate->Direction = direction;
        if (!commissionMdb->BaseCommission->Insert(rate))
        {
            return nullptr;
        }
        return rate;
    }

    // 造成交记录（经守卫登记回池，不入表）。成交金额按 价 × 量 × 乘数 算好，
    // 与 OrderMatch 出成交时的口径一致 —— 计费只看 TradeAmount，不自己乘。
    inline QuantTrading::Trade* MakeCommissionTrade(PoolRecordGuard<QuantTrading::Trade>& tradePool, const char* tradingDay,
        const char* accountId, const char* exchangeId, const char* instrumentId, const char* tradeId,
        DirectionType direction, OffsetFlagType offsetFlag, double price, long long volume, long long volumeMultiple = 1)
    {
        auto* trade = tradePool.Create();
        std::memset(trade, 0, sizeof(QuantTrading::Trade));
        CopyString(trade->TradingDay, tradingDay);
        CopyString(trade->AccountId, accountId);
        CopyString(trade->ExchangeId, exchangeId);
        CopyString(trade->InstrumentId, instrumentId);
        CopyString(trade->TradeId, tradeId);
        trade->ProductClass = ProductClassType::Stock;
        trade->Direction = direction;
        trade->OffsetFlag = offsetFlag;
        trade->Price = price;
        trade->Volume = volume;
        trade->VolumeMultiple = volumeMultiple;
        trade->TradeAmount = price * static_cast<double>(volume) * static_cast<double>(volumeMultiple);
        return trade;
    }

    // 按撮合索引收集某合约某方向的全部持仓明细（平仓配对顺序即由该索引决定）
    inline std::vector<QuantTrading::PositionDetail*> CollectCommissionPositionDetails(QuantTrading::Mdb* commissionMdb, const char* tradingDay,
        const char* accountId, const char* exchangeId, const char* instrumentId, PosiDirectionType posiDirection)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIdType accountIdBuffer;
        CopyString(accountIdBuffer, accountId);
        ExchangeIdType exchangeIdBuffer;
        CopyString(exchangeIdBuffer, exchangeId);
        InstrumentIdType instrumentIdBuffer;
        CopyString(instrumentIdBuffer, instrumentId);
        std::vector<QuantTrading::PositionDetail*> positionDetails;
        auto itPair = commissionMdb->PositionDetail->TradeMatchIndex->EqualRange(tradingDayBuffer, accountIdBuffer, exchangeIdBuffer,
            instrumentIdBuffer, posiDirection);
        for (auto it = itPair.first; it != itPair.second; ++it)
        {
            positionDetails.push_back(*it);
        }
        return positionDetails;
    }
}
