#pragma once
#include "TradeSession.h"
#include "OrderMatch.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace quanttrading::unittest
{
    // 将字符串拷入固定长度字符数组（截断安全）
    template <std::size_t DestSize>
    void CopyString(char (&dest)[DestSize], const char* source)
    {
        std::snprintf(dest, DestSize, "%s", source);
    }

    // 由日期与时分秒（如 143000）、毫秒构造行情 UpdateTs（YYYYMMDDHHMMSSmmm）
    inline long long MakeUpdateTs(int tradingDay, int hhmmss, int milliSecond)
    {
        return static_cast<long long>(tradingDay) * 1000000000LL + static_cast<long long>(hhmmss) * 1000 + milliSecond;
    }

    // 用 JSON 字符串装载交易时段（ParseTradeSessions 的入参为静态成员，绕开文件读取）
    inline bool LoadTradeSessionJson(const char* sessionJson)
    {
        quanttrading::bar::TradeSessions::m_SessionJsonString = sessionJson;
        return quanttrading::bar::TradeSessions::ParseTradeSessions();
    }

    // 清理 ParseTradeSessions 在静态区遗留的对象（库侧只 new 不 delete，测试须自行配平）
    inline void ResetTradeSessions()
    {
        for (auto* tradeSession : quanttrading::bar::TradeSessions::m_TradeSessions)
        {
            for (auto* tradeSection : tradeSession->TradeSections)
            {
                delete tradeSection;
            }
            delete tradeSession;
        }
        quanttrading::bar::TradeSessions::m_TradeSessions.clear();
        quanttrading::bar::TradeSessions::m_Inited = false;
        quanttrading::bar::TradeSessions::m_SessionJsonString.clear();
    }

    // 池分配记录（tick/bar/order 等）统一登记、析构回池，与"池对象所有权归订阅方/测试侧"契约配平
    template <typename Record>
    class PoolRecordGuard
    {
    public:
        Record* Create()
        {
            auto* record = Record::Allocate();
            records_.push_back(record);
            return record;
        }

        ~PoolRecordGuard()
        {
            for (auto* record : records_)
            {
                record->Deallocate();
            }
        }

    private:
        std::vector<Record*> records_;
    };

    // 撮合订阅者：记录回调并按引擎契约把 newOrder 状态写回原 order（与 t_Order->Update 的 memcpy 语义一致）
    class RecordingOrderMatchSubscriber : public quanttrading::ordermatch::OrderMatchSubscriber
    {
    public:
        struct OrderUpdateRecord
        {
            int order_id;
            long long volume_total;
            long long volume_traded;
            OrderStatusType order_status;
        };

        struct TradeRecord
        {
            int order_id;
            DirectionType direction;
            double price;
            long long volume;
        };

        void OnOrder(mdb::Order* order) override
        {
            resting_order_ids.push_back(order->OrderID);
        }

        void OnOrderUpdate(mdb::Order* order, mdb::Order* new_order) override
        {
            std::memcpy(order, new_order, sizeof(mdb::Order));
            order_updates.push_back({new_order->OrderID, new_order->VolumeTotal, new_order->VolumeTraded, new_order->OrderStatus});
            new_order->Deallocate();
        }

        void OnTrade(mdb::Trade* trade) override
        {
            trades.push_back({trade->OrderID, trade->Direction, trade->Price, trade->Volume});
            trade->Deallocate();
        }

        std::vector<int> resting_order_ids;
        std::vector<OrderUpdateRecord> order_updates;
        std::vector<TradeRecord> trades;
    };

    // 测试订单由对象池分配，析构时统一回池
    class OrderPoolGuard
    {
    public:
        mdb::Order* MakeOrder(int order_id, DirectionType direction, double price, long long volume,
            OrderPriceTypeType order_price_type = OrderPriceTypeType::LimitPrice)
        {
            auto* order = order_pool_.Create();
            CopyString(order->TradingDay, "20240301");
            CopyString(order->AccountID, "test");
            CopyString(order->ExchangeID, "SHFE");
            CopyString(order->InstrumentID, "cu2503");
            order->OrderID = order_id;
            order->Direction = direction;
            order->OffsetFlag = OffsetFlagType::Open;
            order->OrderPriceType = order_price_type;
            order->Price = price;
            order->Volume = volume;
            order->VolumeTotal = volume;
            order->OrderStatus = OrderStatusType::Inserted;
            order->VolumeMultiple = 1;
            return order;
        }

    private:
        PoolRecordGuard<mdb::Order> order_pool_;
    };

    // 造 mdb tick 记录（经守卫登记回池），last_price/bid/ask 按引擎需要填充
    inline mdb::DepthMarketData* MakeMdTick(PoolRecordGuard<mdb::DepthMarketData>& tick_pool, long long update_ts,
        double last_price, long long volume, double bid_price, long long bid_volume, double ask_price, long long ask_volume)
    {
        auto* tick = tick_pool.Create();
        CopyString(tick->TradingDay, "20240301");
        CopyString(tick->ExchangeID, "SHFE");
        CopyString(tick->InstrumentID, "cu2503");
        tick->UpdateTs = update_ts;
        tick->LastPrice = last_price;
        tick->Volume = volume;
        tick->BidPrice1 = bid_price;
        tick->BidVolume1 = bid_volume;
        tick->AskPrice1 = ask_price;
        tick->AskVolume1 = ask_volume;
        return tick;
    }

    // 造 mdb bar 记录（经守卫登记回池）
    inline mdb::BarMarketData* MakeBarRecord(PoolRecordGuard<mdb::BarMarketData>& bar_pool, long long update_ts,
        double open_price, double high_price, double low_price, double close_price)
    {
        auto* bar = bar_pool.Create();
        CopyString(bar->TradingDay, "20240301");
        CopyString(bar->ExchangeID, "SHFE");
        CopyString(bar->InstrumentID, "cu2503");
        bar->UpdateTs = update_ts;
        bar->Open = open_price;
        bar->High = high_price;
        bar->Low = low_price;
        bar->Close = close_price;
        return bar;
    }
}
