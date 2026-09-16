#pragma once
#include "TestHelpers.h"
#include "SimExchangeTableList.h"
#include "Settlement.h"
#include "SettlementPriceSource.h"
#include "PositionMaintenance.h"
#include <map>
#include <string>

namespace QuantTrading::UnitTest
{
    // 固定结算价来源：按合约映射预设结算价，未配置的合约回退持仓明细 PreSettlementPrice
    class FixedSettlementPriceSource : public QuantTrading::Settlement::SettlementPriceSource
    {
    public:
        PriceType GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail) override
        {
            auto it = prices.find(positionDetail->InstrumentId);
            return it != prices.end() ? it->second : positionDetail->PreSettlementPrice;
        }

        std::map<std::string, PriceType> prices;
    };

    // 造成交记录（经守卫登记回池，不入表），默认 IF2503、乘数 300
    inline QuantTrading::Trade* MakeSettlementTrade(PoolRecordGuard<QuantTrading::Trade>& tradePool, const char* tradingDay, const char* tradeID,
        DirectionType direction, OffsetFlagType offsetFlag, double price, long long volume,
        ProductClassType productClass = ProductClassType::Future, long long volumeMultiple = 300)
    {
        auto* trade = tradePool.Create();
        CopyString(trade->TradingDay, tradingDay);
        CopyString(trade->AccountId, "test");
        CopyString(trade->ExchangeId, "CFFEX");
        CopyString(trade->InstrumentId, "IF2503");
        trade->ProductClass = productClass;
        CopyString(trade->TradeId, tradeID);
        trade->Direction = direction;
        trade->OffsetFlag = offsetFlag;
        trade->Price = price;
        trade->Volume = volume;
        trade->VolumeMultiple = volumeMultiple;
        return trade;
    }

    // 装入持仓行（表接管所有权，主键冲突时返回 nullptr），默认 IF2503、乘数 300
    inline QuantTrading::Position* InsertSettlementPosition(QuantTrading::Mdb* settlementMdb, const char* tradingDay,
        PosiDirectionType posiDirection, long long totalPosition, double settlementPrice = 0.0)
    {
        auto* position = QuantTrading::Position::Allocate();
        std::memset(position, 0, sizeof(QuantTrading::Position));
        CopyString(position->TradingDay, tradingDay);
        CopyString(position->AccountId, "test");
        CopyString(position->ExchangeId, "CFFEX");
        CopyString(position->InstrumentId, "IF2503");
        position->ProductClass = ProductClassType::Future;
        position->PosiDirection = posiDirection;
        position->TotalPosition = totalPosition;
        position->VolumeMultiple = 300;
        position->SettlementPrice = settlementPrice;
        if (!settlementMdb->Position->Insert(position))
        {
            return nullptr;
        }
        return position;
    }

    // 装入持仓明细行（表接管所有权，主键冲突时返回 nullptr），默认 IF2503、乘数 300
    inline QuantTrading::PositionDetail* InsertSettlementPositionDetail(QuantTrading::Mdb* settlementMdb, const char* tradingDay, const char* openDate,
        const char* tradeID, PosiDirectionType posiDirection, double openPrice, double preSettlementPrice, long long volume,
        long long closeVolume = 0, const char* instrumentId = "IF2503")
    {
        auto* detail = QuantTrading::PositionDetail::Allocate();
        std::memset(detail, 0, sizeof(QuantTrading::PositionDetail));
        CopyString(detail->TradingDay, tradingDay);
        CopyString(detail->AccountId, "test");
        CopyString(detail->ExchangeId, "CFFEX");
        CopyString(detail->InstrumentId, instrumentId);
        detail->ProductClass = ProductClassType::Future;
        detail->PosiDirection = posiDirection;
        CopyString(detail->OpenDate, openDate);
        CopyString(detail->TradeId, tradeID);
        detail->Volume = volume;
        detail->CloseVolume = closeVolume;
        detail->OpenPrice = openPrice;
        detail->PreSettlementPrice = preSettlementPrice;
        detail->VolumeMultiple = 300;
        if (!settlementMdb->PositionDetail->Insert(detail))
        {
            return nullptr;
        }
        return detail;
    }

    // 装入资金行（表接管所有权），账户 test
    inline QuantTrading::Capital* InsertSettlementCapital(QuantTrading::Mdb* settlementMdb, const char* tradingDay, double preBalance, double balance)
    {
        auto* capital = QuantTrading::Capital::Allocate();
        std::memset(capital, 0, sizeof(QuantTrading::Capital));
        CopyString(capital->TradingDay, tradingDay);
        CopyString(capital->AccountId, "test");
        capital->PreBalance = preBalance;
        capital->Balance = balance;
        if (!settlementMdb->Capital->Insert(capital))
        {
            return nullptr;
        }
        return capital;
    }

    // 主键查持仓（mdb 键接口以定长数组引用收参，字符串字面量须转缓冲）
    inline QuantTrading::Position* SelectSettlementPosition(QuantTrading::Mdb* settlementMdb, const char* tradingDay, const char* instrumentId,
        PosiDirectionType posiDirection)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIdType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIdType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIdType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, instrumentId);
        return settlementMdb->Position->PrimaryKey->Select(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer, instrumentIDBuffer, posiDirection);
    }

    // 主键查持仓明细（键含开仓日期与成交编号）
    inline QuantTrading::PositionDetail* SelectSettlementPositionDetail(QuantTrading::Mdb* settlementMdb, const char* tradingDay, const char* instrumentId,
        PosiDirectionType posiDirection, const char* openDate, const char* tradeID)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIdType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIdType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIdType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, instrumentId);
        DateType openDateBuffer;
        CopyString(openDateBuffer, openDate);
        TradeIdType tradeIDBuffer;
        CopyString(tradeIDBuffer, tradeID);
        return settlementMdb->PositionDetail->PrimaryKey->Select(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer, instrumentIDBuffer,
            posiDirection, openDateBuffer, tradeIDBuffer);
    }

    // 按撮合索引统计当日明细数
    inline long long CountSettlementPositionDetailByMatch(QuantTrading::Mdb* settlementMdb, const char* tradingDay, PosiDirectionType posiDirection)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        AccountIdType accountIDBuffer;
        CopyString(accountIDBuffer, "test");
        ExchangeIdType exchangeIDBuffer;
        CopyString(exchangeIDBuffer, "CFFEX");
        InstrumentIdType instrumentIDBuffer;
        CopyString(instrumentIDBuffer, "IF2503");
        auto itPair = settlementMdb->PositionDetail->TradeMatchIndex->EqualRange(tradingDayBuffer, accountIDBuffer, exchangeIDBuffer,
            instrumentIDBuffer, posiDirection);
        return static_cast<long long>(std::distance(itPair.first, itPair.second));
    }

    // 按交易日索引统计/取首行（表模板参数由实参推导）
    template <typename Table>
    inline long long CountByTradingDay(Table* table, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        auto itPair = table->TradingDayIndex->EqualRange(tradingDayBuffer);
        return static_cast<long long>(std::distance(itPair.first, itPair.second));
    }

    template <typename Table>
    inline auto* FirstByTradingDay(Table* table, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        auto itPair = table->TradingDayIndex->EqualRange(tradingDayBuffer);
        return itPair.first != itPair.second ? *itPair.first : nullptr;
    }

    // 结算入口包装（Settle/RollToNextDay 以 DateType 引用收参）
    inline void SettleDay(QuantTrading::Settlement::Settlement& settlement, const char* tradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        settlement.Settle(tradingDayBuffer);
    }

    inline void RollDay(QuantTrading::Settlement::Settlement& settlement, const char* tradingDay, const char* nextTradingDay)
    {
        DateType tradingDayBuffer;
        CopyString(tradingDayBuffer, tradingDay);
        DateType nextTradingDayBuffer;
        CopyString(nextTradingDayBuffer, nextTradingDay);
        settlement.RollToNextDay(tradingDayBuffer, nextTradingDayBuffer);
    }
}
