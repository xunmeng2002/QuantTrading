#pragma once
#include "TestHelpers.h"
#include "SimExchangeTableList.h"
#include "Settlement.h"
#include "SettlementPriceSource.h"
#include "PositionMaintenance.h"
#include <map>
#include <string>

namespace quanttrading::unittest
{
    // 固定结算价来源：按合约映射预设结算价，未配置的合约回退持仓明细 PreSettlementPrice
    class FixedSettlementPriceSource : public quanttrading::settlement::SettlementPriceSource
    {
    public:
        PriceType GetSettlementPrice(const mdb::PositionDetail* positionDetail) override
        {
            auto it = prices.find(positionDetail->InstrumentID);
            return it != prices.end() ? it->second : positionDetail->PreSettlementPrice;
        }

        std::map<std::string, PriceType> prices;
    };

    // 造成交记录（经守卫登记回池，不入表），默认 IF2503、乘数 300
    inline mdb::Trade* MakeSettlementTrade(PoolRecordGuard<mdb::Trade>& tradePool, const char* tradingDay, const char* tradeID,
        DirectionType direction, OffsetFlagType offsetFlag, double price, long long volume,
        ProductClassType productClass = ProductClassType::Future, long long volumeMultiple = 300)
    {
        auto* trade = tradePool.Create();
        CopyString(trade->TradingDay, tradingDay);
        CopyString(trade->AccountID, "test");
        CopyString(trade->ExchangeID, "CFFEX");
        CopyString(trade->InstrumentID, "IF2503");
        trade->ProductClass = productClass;
        CopyString(trade->TradeID, tradeID);
        trade->Direction = direction;
        trade->OffsetFlag = offsetFlag;
        trade->Price = price;
        trade->Volume = volume;
        trade->VolumeMultiple = volumeMultiple;
        return trade;
    }

    // 装入持仓行（表接管所有权，主键冲突时返回 nullptr），默认 IF2503、乘数 300
    inline mdb::Position* InsertSettlementPosition(mdb::Mdb* settlementMdb, const char* tradingDay,
        PosiDirectionType posiDirection, long long totalPosition, double settlementPrice = 0.0)
    {
        auto* position = mdb::Position::Allocate();
        std::memset(position, 0, sizeof(mdb::Position));
        CopyString(position->TradingDay, tradingDay);
        CopyString(position->AccountID, "test");
        CopyString(position->ExchangeID, "CFFEX");
        CopyString(position->InstrumentID, "IF2503");
        position->ProductClass = ProductClassType::Future;
        position->PosiDirection = posiDirection;
        position->TotalPosition = totalPosition;
        position->VolumeMultiple = 300;
        position->SettlementPrice = settlementPrice;
        if (!settlementMdb->t_Position->Insert(position))
        {
            return nullptr;
        }
        return position;
    }

    // 装入持仓明细行（表接管所有权，主键冲突时返回 nullptr），默认 IF2503、乘数 300
    inline mdb::PositionDetail* InsertSettlementPositionDetail(mdb::Mdb* settlementMdb, const char* tradingDay, const char* openDate,
        const char* tradeID, PosiDirectionType posiDirection, double openPrice, double preSettlementPrice, long long volume,
        long long closeVolume = 0, const char* instrumentID = "IF2503")
    {
        auto* detail = mdb::PositionDetail::Allocate();
        std::memset(detail, 0, sizeof(mdb::PositionDetail));
        CopyString(detail->TradingDay, tradingDay);
        CopyString(detail->AccountID, "test");
        CopyString(detail->ExchangeID, "CFFEX");
        CopyString(detail->InstrumentID, instrumentID);
        detail->ProductClass = ProductClassType::Future;
        detail->PosiDirection = posiDirection;
        CopyString(detail->OpenDate, openDate);
        CopyString(detail->TradeID, tradeID);
        detail->Volume = volume;
        detail->CloseVolume = closeVolume;
        detail->OpenPrice = openPrice;
        detail->PreSettlementPrice = preSettlementPrice;
        detail->VolumeMultiple = 300;
        if (!settlementMdb->t_PositionDetail->Insert(detail))
        {
            return nullptr;
        }
        return detail;
    }

    // 装入资金行（表接管所有权），账户 test
    inline mdb::Capital* InsertSettlementCapital(mdb::Mdb* settlementMdb, const char* tradingDay, double preBalance, double balance)
    {
        auto* capital = mdb::Capital::Allocate();
        std::memset(capital, 0, sizeof(mdb::Capital));
        CopyString(capital->TradingDay, tradingDay);
        CopyString(capital->AccountID, "test");
        capital->PreBalance = preBalance;
        capital->Balance = balance;
        if (!settlementMdb->t_Capital->Insert(capital))
        {
            return nullptr;
        }
        return capital;
    }

    // 主键查持仓（mdb 键接口以定长数组引用收参，字符串字面量须转缓冲）
    inline mdb::Position* SelectSettlementPosition(mdb::Mdb* settlementMdb, const char* tradingDay, const char* instrumentID,
        PosiDirectionType posiDirection)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIDType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIDType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIDType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, instrumentID);
        return settlementMdb->t_Position->m_PrimaryKey->Select(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer, instrumentIDBuffer, posiDirection);
    }

    // 主键查持仓明细（键含开仓日期与成交编号）
    inline mdb::PositionDetail* SelectSettlementPositionDetail(mdb::Mdb* settlementMdb, const char* tradingDay, const char* instrumentID,
        PosiDirectionType posiDirection, const char* openDate, const char* tradeID)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIDType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIDType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIDType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, instrumentID);
        DateType openDateBuffer;
        CopyString(openDateBuffer, openDate);
        TradeIDType tradeIDBuffer;
        CopyString(tradeIDBuffer, tradeID);
        return settlementMdb->t_PositionDetail->m_PrimaryKey->Select(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer, instrumentIDBuffer,
            posiDirection, openDateBuffer, tradeIDBuffer);
    }

    // 按撮合索引统计当日明细数
    inline long long CountSettlementPositionDetailByMatch(mdb::Mdb* settlementMdb, const char* tradingDay, PosiDirectionType posiDirection)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIDType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIDType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIDType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, "IF2503");
        auto itPair = settlementMdb->t_PositionDetail->m_TradeMatchIndex->EqualRange(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer,
            instrumentIDBuffer, posiDirection);
        return static_cast<long long>(std::distance(itPair.first, itPair.second));
    }

    // 按交易日索引统计/取首行（表模板参数由实参推导）
    template <typename Table>
    inline long long CountByTradingDay(Table* table, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        auto itPair = table->m_TradingDayIndex->EqualRange(tradingDayBuffer);
        return static_cast<long long>(std::distance(itPair.first, itPair.second));
    }

    template <typename Table>
    inline auto* FirstByTradingDay(Table* table, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        auto itPair = table->m_TradingDayIndex->EqualRange(tradingDayBuffer);
        return itPair.first != itPair.second ? *itPair.first : nullptr;
    }

    // 结算入口包装（Settle/RollToNextDay 以 DateType 引用收参）
    inline void SettleDay(quanttrading::settlement::Settlement& settlement, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        settlement.Settle(tradingDayBuffer);
    }

    inline void RollDay(quanttrading::settlement::Settlement& settlement, const char* tradingDay, const char* nextTradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        DateType nextTradingDayBuffer;
        CopyString(nextTradingDayBuffer, nextTradingDay);
        settlement.RollToNextDay(tradingDayBuffer, nextTradingDayBuffer);
    }
}
