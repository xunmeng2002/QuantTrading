#pragma once
#include "TradeSession.h"
#include "OrderMatch.h"
#include <QuantTrading/BackTestApi.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace QuantTrading::UnitTest
{
    template <std::size_t DestSize>
    void CopyString(char (&dest)[DestSize], const char* source)
    {
        std::snprintf(dest, DestSize, "%s", source);
    }
    inline long long MakeUpdateTs(int tradingDay, int hhmmss, int milliSecond)
    {
        return static_cast<long long>(tradingDay) * 1000000000LL + static_cast<long long>(hhmmss) * 1000 + milliSecond;
    }
    inline bool LoadTradeSessionJson(QuantTrading::Bar::TradeSessions& tradeSessions, const char* sessionJson)
    {
        return tradeSessions.ParseFromJsonString(sessionJson);
    }
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

    class RecordingOrderMatchSubscriber : public QuantTrading::OrderMatch::OrderMatchSubscriber
    {
    public:
        struct OrderUpdateRecord
        {
            int OrderId;
            long long VolumeTotal;
            long long VolumeTraded;
            OrderStatusType OrderStatus;
        };

        struct TradeRecord
        {
            int OrderId;
            DirectionType Direction;
            double Price;
            long long Volume;
        };

        void OnOrder(QuantTrading::Order* order) override
        {
            RestingOrderIds.push_back(order->OrderId);
        }
        void OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* new_order) override
        {
            std::memcpy(order, new_order, sizeof(QuantTrading::Order));
            OrderUpdates.push_back({new_order->OrderId, new_order->VolumeTotal, new_order->VolumeTraded, new_order->OrderStatus});
            new_order->Deallocate();
        }
        void OnTrade(QuantTrading::Trade* trade) override
        {
            Trades.push_back({trade->OrderId, trade->Direction, trade->Price, trade->Volume});
            trade->Deallocate();
        }

        std::vector<int> RestingOrderIds;
        std::vector<OrderUpdateRecord> OrderUpdates;
        std::vector<TradeRecord> Trades;
    };

    // 测试订单由对象池分配，析构时统一回池
    class OrderPoolGuard
    {
    public:
        QuantTrading::Order* MakeOrder(int OrderId, DirectionType direction, double price, long long volume, OrderPriceTypeType orderPriceType = OrderPriceTypeType::LimitPrice)
        {
            auto* order = orderPool_.Create();
            CopyString(order->TradingDay, "20240301");
            CopyString(order->AccountId, "test");
            CopyString(order->ExchangeId, "SHFE");
            CopyString(order->InstrumentId, "cu2503");
            order->OrderId = OrderId;
            order->Direction = direction;
            order->OffsetFlag = OffsetFlagType::Open;
            order->OrderPriceType = orderPriceType;
            order->Price = price;
            order->Volume = volume;
            order->VolumeTotal = volume;
            order->OrderStatus = OrderStatusType::Inserted;
            order->VolumeMultiple = 1;
            return order;
        }

    private:
        PoolRecordGuard<QuantTrading::Order> orderPool_;
    };

    inline QuantTrading::DepthMarketData* MakeMdTick(PoolRecordGuard<QuantTrading::DepthMarketData>& tick_pool, long long updateTs,
        double lastPrice, long long volume, double bidPrice, long long bidVolume, double askPrice, long long askVolume)
    {
        auto* tick = tick_pool.Create();
        CopyString(tick->TradingDay, "20240301");
        CopyString(tick->ExchangeId, "SHFE");
        CopyString(tick->InstrumentId, "cu2503");
        tick->UpdateTs = updateTs;
        tick->LastPrice = lastPrice;
        tick->Volume = volume;
        tick->BidPrice1 = bidPrice;
        tick->BidVolume1 = bidVolume;
        tick->AskPrice1 = askPrice;
        tick->AskVolume1 = askVolume;
        return tick;
    }
    inline QuantTrading::BarMarketData* MakeBarRecord(PoolRecordGuard<QuantTrading::BarMarketData>& barPool, long long updateTs,
        double openPrice, double highPrice, double lowPrice, double closePrice)
    {
        auto* bar = barPool.Create();
        CopyString(bar->TradingDay, "20240301");
        CopyString(bar->ExchangeId, "SHFE");
        CopyString(bar->InstrumentId, "cu2503");
        bar->UpdateTs = updateTs;
        bar->Open = openPrice;
        bar->High = highPrice;
        bar->Low = lowPrice;
        bar->Close = closePrice;
        return bar;
    }

    class FakeBackTestApi : public QuantTrading::BackTestApi
    {
    public:
        bool Init() override { return InitResult; }
        void Join() override {}
        void Release() override { ++ReleaseCount; }
        void RegisterFront(const char* /*address*/) override {}
        void RegisterSpi(QuantTrading::BackTestSpi* spi) override { RegisteredSpi = spi; }
        int ReqSubMarketData(const ReqSubMarketDataField* req, int requestId) override
        {
            ++SubscribeCount;
            LastSubscribeRequestId = requestId;
            if (req != nullptr)
            {
                SubscribeRequests.push_back(*req);
            }
            return 0;
        }
        int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* /*req*/, int /*requestId*/) override { return 0; }
        int ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestId) override
        {
            if (reqRegisterAccount != nullptr)
            {
                RegisterAccountRequests.push_back(*reqRegisterAccount);
            }
            RegisterAccountRequestId = requestId;
            return 0;
        }
        int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int /*requestId*/) override
        {
            InsertRequests.push_back(*reqInsertOrder);
            return 0;
        }
        int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int /*requestId*/) override
        {
            CancelRequests.push_back(*reqCancelOrder);
            return 0;
        }

        bool InitResult = true;
        int ReleaseCount = 0;
        int SubscribeCount = 0;
        int LastSubscribeRequestId = 0;
        int RegisterAccountRequestId = 0;
        QuantTrading::BackTestSpi* RegisteredSpi = nullptr;
        std::vector<ReqSubMarketDataField> SubscribeRequests;
        std::vector<ReqRegisterAccountField> RegisterAccountRequests;
        std::vector<ReqInsertOrderField> InsertRequests;
        std::vector<ReqCancelOrderField> CancelRequests;
    };

    inline DepthMarketDataField MakeMdTickField(const char* instrumentId, double lastPrice)
    {
        DepthMarketDataField md_tick;
        std::memset(&md_tick, 0, sizeof(md_tick));
        CopyString(md_tick.InstrumentId, instrumentId);
        md_tick.LastPrice = lastPrice;
        return md_tick;
    }
    inline BarMarketDataField MakeMdBarField(const char* instrumentId, long long endBarMinute, double closePrice)
    {
        BarMarketDataField md_bar;
        std::memset(&md_bar, 0, sizeof(md_bar));
        CopyString(md_bar.InstrumentId, instrumentId);
        md_bar.BarPreces = BarPrecesType::Minute;
        md_bar.BarPeriod = 5;
        md_bar.BarTime = endBarMinute * 100000;
        md_bar.UpdateTs = md_bar.BarTime;
        md_bar.Open = closePrice;
        md_bar.High = closePrice;
        md_bar.Low = closePrice;
        md_bar.Close = closePrice;
        md_bar.HighestPrice = closePrice;
        md_bar.LowestPrice = closePrice;
        return md_bar;
    }
    inline TradeField MakeTradeField(const char* instrumentId, int OrderId, DirectionType direction, OffsetFlagType offset_flag, double price,
        long long volume, int volumeMultiple, double commission)
    {
        TradeField trade;
        std::memset(&trade, 0, sizeof(trade));
        CopyString(trade.InstrumentId, instrumentId);
        trade.OrderId = OrderId;
        trade.Direction = direction;
        trade.OffsetFlag = offset_flag;
        trade.Price = price;
        trade.Volume = volume;
        trade.VolumeMultiple = volumeMultiple;
        trade.Commission = commission;
        return trade;
    }
    inline OrderField MakeOrderField(const char* instrumentId, int OrderId, int clientOrderId)
    {
        OrderField order;
        std::memset(&order, 0, sizeof(order));
        CopyString(order.InstrumentId, instrumentId);
        order.OrderId = OrderId;
        order.ClientOrderId = clientOrderId;
        return order;
    }
}
