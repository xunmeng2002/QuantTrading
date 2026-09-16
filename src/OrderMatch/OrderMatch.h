#pragma once
#include "OrderUtility.h"
#include "MdbStructs.h"
#include <string>
#include <map>
#include <set>

namespace QuantTrading::ordermatch
{
    class OrderMatchSubscriber
    {
    public:
        virtual void OnOrder(QuantTrading::Order* order) = 0;
        virtual void OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder) = 0;
        virtual void OnTrade(QuantTrading::Trade* trade) = 0;
    };

    class OrderMatch
    {
    public:
        static OrderMatch* CreateOrderMatch(const MatchModeType& matchMode, const DateType& tradingDay, int maxTradeID = 0);
        OrderMatch(const DateType& tradingDay, int maxTradeID = 0);
        virtual ~OrderMatch();
        void Subscribe(OrderMatchSubscriber* orderMatchSubscriber);

        virtual void OnTradingDayChange(const DateType& nextTradingDay);
        virtual void OnTick(QuantTrading::DepthMarketData* mdTick) = 0;
        virtual void OnBar(QuantTrading::BarMarketData* mdBar) = 0;
        virtual void InsertOrder(QuantTrading::Order* order);
        virtual void CancelOrder(QuantTrading::Order* order);

    protected:
        void Match(QuantTrading::Order* order, PriceType price, VolumeType volume, const TradeIdType& tradeID);
        void AddOrderToQueue(QuantTrading::Order* order);
        void AddOrderToLimitQueue(QuantTrading::Order* order);
        void AddOrderToMarketQueue(QuantTrading::Order* order);
        void CancelOrderOnInsert(QuantTrading::Order* order);
        void CancelOrders();
        void GetNextTradeID(TradeIdType& tradeID);
        void UpdateDateTime();
        void UpdateDateTime(const Int64Type& updateTs);
        bool TryGetOwnBookBestPrice(QuantTrading::Order* order, PriceType& bestPrice);
        bool TryGetOpponentBookBestPrice(QuantTrading::Order* order, PriceType& bestPrice);
        VolumeType CountOpponentFillableVolume(QuantTrading::Order* order);
        void MatchMarketOrderAtPrice(QuantTrading::Order* order, PriceType marketPrice, PriceType opponentPrice);

        // 限价FAK/FOK 仅享有插入后首次行情机会,未成交即撤(市价族在市价队列由事件路径处理,不在此列)
        template <typename OrderLess>
        void CancelUnfilledImmediateOrders(std::set<QuantTrading::Order*, OrderLess>& orderQueue)
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
        TradeIdType m_TradeID;
        DateType m_CurrDate;
        TimeType m_CurrTime;
        std::map<std::string, std::set<QuantTrading::Order*, OrderLessForPriceOpposite>> m_BuyOrders;
        std::map<std::string, std::set<QuantTrading::Order*, OrderLessForPrice>> m_SellOrders;
        std::map<std::string, std::set<QuantTrading::Order*, OrderLessForOrderID>> m_MarketBuyOrders;
        std::map<std::string, std::set<QuantTrading::Order*, OrderLessForOrderID>> m_MarketSellOrders;
    };
}
