#include "OrderMatch.h"
#include "OrderBookOrderMatch.h"
#include "LastPriceOrderMatch.h"
#include "OppositePriceOrderMatch.h"
#include "BarOrderMatch.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/DoubleUtility.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <cstring>
#include <limits>

using namespace std;
using namespace mdb;
using namespace Spark::Core;

namespace QuantTrading::ordermatch
{
    namespace
    {
        template <typename OrderLess>
        bool TryGetBookBestPrice(const std::map<std::string, std::set<QuantTrading::Order*, OrderLess>>& orderBook, const std::string& instrumentId, PriceType& bestPrice)
        {
            auto it = orderBook.find(instrumentId);
            if (it == orderBook.end() || it->second.empty())
            {
                return false;
            }
            bestPrice = (*it->second.begin())->Price;
            return true;
        }
    }

    OrderMatch* OrderMatch::CreateOrderMatch(const MatchModeType& matchMode, const DateType& tradingDay, int maxTradeID)
    {
        switch (matchMode)
        {
        case MatchModeType::OrderBook:
            return new OrderBookOrderMatch(tradingDay, maxTradeID);
        case MatchModeType::LastPrice:
            return new LastPriceOrderMatch(tradingDay, maxTradeID);
        case MatchModeType::OppositePrice:
            return new OppositePriceOrderMatch(tradingDay, maxTradeID);
        case MatchModeType::Bar:
            return new BarOrderMatch(tradingDay, maxTradeID);
        default:
            break;
        }
        WriteLog(LogLevel::Error, "CreateOrderMatch Failed. MatchModeType:%d", matchMode);
        return nullptr;
    }
    OrderMatch::OrderMatch(const DateType& tradingDay, int maxTradeID)
        :m_OrderMatchSubscriber(nullptr), m_MaxTradeID(maxTradeID), m_TradeID(""), m_CurrDate(""), m_CurrTime("")
    {
        memcpy(m_TradingDay, tradingDay, sizeof(DateType));
    }
    OrderMatch::~OrderMatch()
    {

    }
    void OrderMatch::Subscribe(OrderMatchSubscriber* orderMatchSubscriber)
    {
        m_OrderMatchSubscriber = orderMatchSubscriber;
    }

    void OrderMatch::InsertOrder(QuantTrading::Order* order)
    {
        if (order->OrderPriceType == OrderPriceTypeType::BestOwnPrice)
        {
            PriceType bestPrice;
            if (TryGetOwnBookBestPrice(order, bestPrice))
            {
                order->Price = bestPrice;
                AddOrderToLimitQueue(order);
                m_OrderMatchSubscriber->OnOrder(order);
            }
            else
            {
                CancelOrderOnInsert(order);
            }
            return;
        }
        AddOrderToQueue(order);
        m_OrderMatchSubscriber->OnOrder(order);
    }

    void OrderMatch::OnTradingDayChange(const DateType& nextTradingDay)
    {
        CancelOrders();
        memcpy(m_TradingDay, nextTradingDay, sizeof(DateType));
        m_MaxTradeID = 0;
        m_BuyOrders.clear();
        m_SellOrders.clear();
        m_MarketBuyOrders.clear();
        m_MarketSellOrders.clear();
    }
    void OrderMatch::CancelOrder(QuantTrading::Order* order)
    {
        auto newOrder = Order::Allocate();
        memcpy(newOrder, order, sizeof(Order));
        newOrder->VolumeTotal = 0;
        newOrder->OrderStatus = order->VolumeTraded > 0 ? OrderStatusType::PartTradedCanceled : OrderStatusType::Canceled;
        strcpy(newOrder->CancelDate, m_CurrDate);
        strcpy(newOrder->CancelTime, m_CurrTime);
        m_OrderMatchSubscriber->OnOrderUpdate(order, newOrder);
    }
    void OrderMatch::CancelOrderOnInsert(QuantTrading::Order* order)
    {
        // 接受确认先于撤销回报,维持 已报->已撤 的回报序列
        m_OrderMatchSubscriber->OnOrder(order);
        CancelOrder(order);
    }

    void OrderMatch::Match(QuantTrading::Order* order, PriceType price, VolumeType volume, const TradeIdType& tradeID)
    {
        if (volume <= 0)
            return;
        auto newOrder = Order::Allocate();
        memcpy(newOrder, order, sizeof(Order));
        newOrder->VolumeTraded += volume;
        newOrder->VolumeTotal -= volume;
        newOrder->OrderStatus = newOrder->VolumeTotal > 0 ? OrderStatusType::PartTraded : OrderStatusType::AllTraded;
        m_OrderMatchSubscriber->OnOrderUpdate(order, newOrder);

        auto trade = Trade::Allocate();
        memset(trade, 0, sizeof(Trade));
        strcpy(trade->TradingDay, order->TradingDay);
        strcpy(trade->AccountId, order->AccountId);
        trade->AccountType = order->AccountType;
        strcpy(trade->ExchangeId, order->ExchangeId);
        strcpy(trade->InstrumentId, order->InstrumentId);
        trade->ProductClass = order->ProductClass;
        trade->OrderId = order->OrderId;
        strcpy(trade->OrderSysId, order->OrderSysId);
        strcpy(trade->TradeId, tradeID);
        trade->Direction = order->Direction;
        trade->OffsetFlag = order->OffsetFlag;
        trade->Price = price;
        trade->Volume = volume;
        trade->VolumeMultiple = order->VolumeMultiple;
        trade->TradeAmount = price * volume * order->VolumeMultiple;;
        trade->Commission = 0;
        strcpy(trade->TradeDate, m_CurrDate);
        strcpy(trade->TradeTime, m_CurrTime);

        m_OrderMatchSubscriber->OnTrade(trade);
    }
    void OrderMatch::AddOrderToQueue(QuantTrading::Order* order)
    {
        switch (order->OrderPriceType)
        {
        case OrderPriceTypeType::AnyPriceFAK:
        case OrderPriceTypeType::AnyPriceFOK:
        case OrderPriceTypeType::BestOppoPrice:
            // 市价族与未解析的对方最优:由行情事件消费市价队列
            AddOrderToMarketQueue(order);
            break;
        default:
            // 限价族与已解析的本方最优:挂限价队列排队
            AddOrderToLimitQueue(order);
            break;
        }
    }
    void OrderMatch::AddOrderToLimitQueue(QuantTrading::Order* order)
    {
        if (order->Direction == DirectionType::Buy)
        {
            m_BuyOrders[order->InstrumentId].insert(order);
        }
        else
        {
            m_SellOrders[order->InstrumentId].insert(order);
        }
    }
    void OrderMatch::AddOrderToMarketQueue(QuantTrading::Order* order)
    {
        if (order->Direction == DirectionType::Buy)
        {
            m_MarketBuyOrders[order->InstrumentId].insert(order);
        }
        else
        {
            m_MarketSellOrders[order->InstrumentId].insert(order);
        }
    }
    bool OrderMatch::TryGetOwnBookBestPrice(QuantTrading::Order* order, PriceType& bestPrice)
    {
        // 本方簿:买方取买簿最高价,卖方取卖簿最低价
        if (order->Direction == DirectionType::Buy)
        {
            return TryGetBookBestPrice(m_BuyOrders, order->InstrumentId, bestPrice);
        }
        return TryGetBookBestPrice(m_SellOrders, order->InstrumentId, bestPrice);
    }
    bool OrderMatch::TryGetOpponentBookBestPrice(QuantTrading::Order* order, PriceType& bestPrice)
    {
        // 对手簿:买方取卖簿最低价,卖方取买簿最高价
        if (order->Direction == DirectionType::Buy)
        {
            return TryGetBookBestPrice(m_SellOrders, order->InstrumentId, bestPrice);
        }
        return TryGetBookBestPrice(m_BuyOrders, order->InstrumentId, bestPrice);
    }
    VolumeType OrderMatch::CountOpponentFillableVolume(QuantTrading::Order* order)
    {
        // 预扫对手簿累计可成量(FOK 用):受价单只累计价格不劣于委托价的档位,无界市价族累计全簿
        const bool hasPriceBound = HasOrderPriceBound(order->OrderPriceType);
        VolumeType fillableVolume = 0;
        if (order->Direction == DirectionType::Buy)
        {
            auto it = m_SellOrders.find(order->InstrumentId);
            if (it == m_SellOrders.end())
            {
                return 0;
            }
            for (auto queueOrder : it->second)
            {
                if (queueOrder->VolumeTotal <= 0)
                {
                    continue;
                }
                if (hasPriceBound && DoubleUtility::DoubleLess(order->Price, queueOrder->Price))
                {
                    break;
                }
                fillableVolume += queueOrder->VolumeTotal;
            }
        }
        else
        {
            auto it = m_BuyOrders.find(order->InstrumentId);
            if (it == m_BuyOrders.end())
            {
                return 0;
            }
            for (auto queueOrder : it->second)
            {
                if (queueOrder->VolumeTotal <= 0)
                {
                    continue;
                }
                if (hasPriceBound && DoubleUtility::DoubleGreat(order->Price, queueOrder->Price))
                {
                    break;
                }
                fillableVolume += queueOrder->VolumeTotal;
            }
        }
        return fillableVolume;
    }
    void OrderMatch::CancelOrders()
    {
        for (auto& it : m_MarketBuyOrders)
        {
            for (auto order : it.second)
            {
                if (order->VolumeTotal > 0)
                {
                    CancelOrder(order);
                }
            }
        }
        for (auto& it : m_MarketSellOrders)
        {
            for (auto order : it.second)
            {
                if (order->VolumeTotal > 0)
                {
                    CancelOrder(order);
                }
            }
        }
        for (auto& it : m_BuyOrders)
        {
            for (auto order : it.second)
            {
                if (order->VolumeTotal > 0)
                {
                    CancelOrder(order);
                }
            }
        }
        for (auto& it : m_SellOrders)
        {
            for (auto order : it.second)
            {
                if (order->VolumeTotal > 0)
                {
                    CancelOrder(order);
                }
            }
        }
    }
    void OrderMatch::GetNextTradeID(TradeIdType& tradeID)
    {
        sprintf(tradeID, "%s%08d", m_TradingDay, ++m_MaxTradeID);
    }
    void OrderMatch::MatchMarketOrderAtPrice(QuantTrading::Order* order, PriceType marketPrice, PriceType opponentPrice)
    {
        // 对方最优按对手价成交,无有效对手价(inf)时撤销;其余市价族按模式市价成交
        PriceType matchPrice = marketPrice;
        if (order->OrderPriceType == OrderPriceTypeType::BestOppoPrice)
        {
            if (opponentPrice == std::numeric_limits<double>::infinity())
            {
                CancelOrder(order);
                return;
            }
            matchPrice = opponentPrice;
        }
        GetNextTradeID(m_TradeID);
        Match(order, matchPrice, order->VolumeTotal, m_TradeID);
    }
    void OrderMatch::UpdateDateTime()
    {
        TimeUtility::GetLocalDateTime(m_CurrDate, m_CurrTime);
    }
    void OrderMatch::UpdateDateTime(const Int64Type& updateTs)
    {
        TimeUtility::GetDateTimeFromTimeStamp(updateTs, m_CurrDate, m_CurrTime);
    }
}
