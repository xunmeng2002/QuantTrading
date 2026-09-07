#pragma once
#include "OrderUtility.h"
#include "MdbStructs.h"
#include <string>
#include <map>
#include <set>

namespace quanttrading::ordermatch
{
    class OrderMatchSubscriber
    {
    public:
        virtual void OnOrder(mdb::Order* order) = 0;
        virtual void OnOrderUpdate(mdb::Order* order, mdb::Order* newOrder) = 0;
        virtual void OnTrade(mdb::Trade* trade) = 0;
    };

    class OrderMatch
    {
    public:
        static OrderMatch* CreateOrderMatch(const MatchModeType& matchMode, const DateType& tradingDay, int maxTradeID = 0);
        OrderMatch(const DateType& tradingDay, int maxTradeID = 0);
        virtual ~OrderMatch();
        void Subscribe(OrderMatchSubscriber* orderMatchSubscriber);

        virtual void OnTradingDayChange(const DateType& nextTradingDay);
        virtual void OnTick(mdb::DepthMarketData* mdTick) = 0;
        virtual void OnBar(mdb::BarMarketData* mdBar) = 0;
        virtual void InsertOrder(mdb::Order* order);
        virtual void CancelOrder(mdb::Order* order);

    protected:
        void Match(mdb::Order* order, PriceType price, VolumeType volume, const TradeIDType& tradeID);
        void AddOrderToQueue(mdb::Order* order);
        void AddOrderToLimitQueue(mdb::Order* order);
        void AddOrderToMarketQueue(mdb::Order* order);
        void CancelOrderOnInsert(mdb::Order* order);
        void CancelOrders();
        void GetNextTradeID(TradeIDType& tradeID);
        void UpdateDateTime();
        void UpdateDateTime(const Int64Type& updateTs);
        bool TryGetOwnBookBestPrice(mdb::Order* order, PriceType& bestPrice);
        bool TryGetOpponentBookBestPrice(mdb::Order* order, PriceType& bestPrice);
        VolumeType CountOpponentFillableVolume(mdb::Order* order);
        void MatchMarketOrderAtPrice(mdb::Order* order, PriceType marketPrice, PriceType opponentPrice);

        // 限价FAK/FOK 仅享有插入后首次行情机会,未成交即撤(市价族在市价队列由事件路径处理,不在此列)
        template <typename OrderLess>
        void CancelUnfilledImmediateOrders(std::set<mdb::Order*, OrderLess>& orderQueue)
        {
            for (auto order : orderQueue)
            {
                if (order->VolumeTotal > 0
                    && (order->OrderPriceType == OrderPriceTypeType::LimitPriceFAK || order->OrderPriceType == OrderPriceTypeType::LimitPriceFOK))
                {
                    CancelOrder(order);
                }
            }
        }

    protected:
        OrderMatchSubscriber* m_OrderMatchSubscriber;

        DateType m_TradingDay;
        int m_MaxTradeID;
        TradeIDType m_TradeID;
        DateType m_CurrDate;
        TimeType m_CurrTime;
        std::map<std::string, std::set<mdb::Order*, OrderLessForPriceOpposite>> m_BuyOrders;
        std::map<std::string, std::set<mdb::Order*, OrderLessForPrice>> m_SellOrders;
        std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketBuyOrders;
        std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketSellOrders;
    };
}
