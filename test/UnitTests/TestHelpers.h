#pragma once
#include "TradeSession.h"
#include "OrderMatch.h"
#include <QuantTrading/BackTestApi.h>
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

    // 用 JSON 字符串装载交易时段（绕开文件读取）；实例由持有方管理生命周期，析构即回收，无需手动清理
    inline bool LoadTradeSessionJson(quanttrading::bar::TradeSessions& tradeSessions, const char* sessionJson)
    {
        return tradeSessions.ParseFromJsonString(sessionJson);
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

    // 回测策略层测试桩：实现 BackTestApi 纯虚接口，捕获 SPI 注册与 Req 请求，供测试回放引擎事件
    class FakeBackTestApi : public quanttrading::BackTestApi
    {
    public:
        bool Init() override { return init_result; }
        void Join() override {}
        void Release() override { ++release_count; }
        void RegisterFront(const char* /*address*/) override {}
        void RegisterSpi(quanttrading::BackTestSpi* spi) override { registered_spi = spi; }
        int ReqSubMarketData(const ReqSubMarketDataField* req, int requestID) override
        {
            ++subscribe_count;
            last_subscribe_request_id = requestID;
            if (req != nullptr)
            {
                subscribe_requests.push_back(*req);
            }
            return 0;
        }
        int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* /*req*/, int /*requestID*/) override { return 0; }
        int ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestID) override
        {
            if (reqRegisterAccount != nullptr)
            {
                register_account_requests.push_back(*reqRegisterAccount);
            }
            register_account_request_id = requestID;
            return 0;
        }
        int ReqInsertOrder(const ReqInsertOrderField* req_insert_order, int /*requestID*/) override
        {
            insert_requests.push_back(*req_insert_order);
            return 0;
        }
        int ReqCancelOrder(const ReqCancelOrderField* req_cancel_order, int /*requestID*/) override
        {
            cancel_requests.push_back(*req_cancel_order);
            return 0;
        }

        bool init_result = true;
        int release_count = 0;
        int subscribe_count = 0;
        int last_subscribe_request_id = 0;
        int register_account_request_id = 0;
        quanttrading::BackTestSpi* registered_spi = nullptr;
        // 逐条留存订阅请求：策略声明的 bar 周期随请求上报，测试据此断言声明的周期已挂到订阅上
        std::vector<ReqSubMarketDataField> subscribe_requests;
        std::vector<ReqRegisterAccountField> register_account_requests;
        std::vector<ReqInsertOrderField> insert_requests;
        std::vector<ReqCancelOrderField> cancel_requests;
    };

    // 造 DepthMarketDataField（值类型，栈上使用）
    inline DepthMarketDataField MakeMdTickField(const char* instrument_id, double last_price)
    {
        DepthMarketDataField md_tick;
        std::memset(&md_tick, 0, sizeof(md_tick));
        CopyString(md_tick.InstrumentID, instrument_id);
        md_tick.LastPrice = last_price;
        return md_tick;
    }

    // 造 BarMarketDataField（值类型，栈上使用；四价统一填 close_price，时间字段按 bar 结束分钟填充）
    inline BarMarketDataField MakeMdBarField(const char* instrument_id, long long end_bar_minute, double close_price)
    {
        BarMarketDataField md_bar;
        std::memset(&md_bar, 0, sizeof(md_bar));
        CopyString(md_bar.InstrumentID, instrument_id);
        md_bar.BarPreces = BarPrecesType::Minute;
        md_bar.BarPeriod = 5;
        md_bar.BarTime = end_bar_minute * 100000;
        md_bar.UpdateTs = md_bar.BarTime;
        md_bar.Open = close_price;
        md_bar.High = close_price;
        md_bar.Low = close_price;
        md_bar.Close = close_price;
        md_bar.HighestPrice = close_price;
        md_bar.LowestPrice = close_price;
        return md_bar;
    }

    // 造 TradeField（值类型）
    inline TradeField MakeTradeField(const char* instrument_id, int order_id, DirectionType direction,
        OffsetFlagType offset_flag, double price, long long volume, int volume_multiple, double commission)
    {
        TradeField trade;
        std::memset(&trade, 0, sizeof(trade));
        CopyString(trade.InstrumentID, instrument_id);
        trade.OrderID = order_id;
        trade.Direction = direction;
        trade.OffsetFlag = offset_flag;
        trade.Price = price;
        trade.Volume = volume;
        trade.VolumeMultiple = volume_multiple;
        trade.Commission = commission;
        return trade;
    }

    // 造 OrderField（值类型，只填订单路由相关字段）
    inline OrderField MakeOrderField(const char* instrument_id, int order_id, int client_order_id)
    {
        OrderField order;
        std::memset(&order, 0, sizeof(order));
        CopyString(order.InstrumentID, instrument_id);
        order.OrderID = order_id;
        order.ClientOrderID = client_order_id;
        return order;
    }
}
