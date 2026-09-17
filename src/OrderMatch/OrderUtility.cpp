#include "OrderUtility.h"
#include "Error.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <string>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;
using namespace QuantTrading::Packages;

namespace QuantTrading::OrderMatch
{
    static OrderIdType g_MaxOrderID = 0;

    bool OrderLessForPrice::operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const
    {
        if (left->Price < right->Price)
            return true;
        else if (left->Price > right->Price)
            return false;
        return left->OrderId < right->OrderId;
    }
    bool OrderLessForPriceOpposite::operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const
    {
        if (left->Price > right->Price)
            return true;
        else if (left->Price < right->Price)
            return false;
        return left->OrderId < right->OrderId;
    }
    bool OrderLessForOrderID::operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const
    {
        return left->OrderId < right->OrderId;
    }

    OrderIdType GetNextOrderID()
    {
        return ++g_MaxOrderID;
    }
    void SeedNextOrderIDFromMaxOrderID(OrderIdType maxOrderId)
    {
        if (maxOrderId > g_MaxOrderID)
        {
            g_MaxOrderID = maxOrderId;
        }
    }
    void SeedNextOrderIDFromOrders(QuantTrading::OrderTable* orderTable)
    {
        OrderIdType maxOrderId = 0;
        auto orderPair = orderTable->PrimaryKey->SelectAll();
        for (auto& it = orderPair.first; it != orderPair.second; ++it)
        {
            if ((*it)->OrderId > maxOrderId)
            {
                maxOrderId = (*it)->OrderId;
            }
        }
        SeedNextOrderIDFromMaxOrderID(maxOrderId);
    }
    bool IsMarketPriceClass(OrderPriceTypeType orderPriceType)
    {
        switch (orderPriceType)
        {
        case OrderPriceTypeType::AnyPriceFAK:
        case OrderPriceTypeType::AnyPriceFOK:
            return true;
        default:
            return false;
        }
    }
    bool HasOrderPriceBound(OrderPriceTypeType orderPriceType)
    {
        switch (orderPriceType)
        {
        case OrderPriceTypeType::LimitPrice:
        case OrderPriceTypeType::LimitPriceFAK:
        case OrderPriceTypeType::LimitPriceFOK:
        case OrderPriceTypeType::BestOppoPrice:
            return true;
        default:
            return false;
        }
    }
    int CheckForInsertOrder(ReqInsertOrderField* reqInsertOrder, QuantTrading::Instrument* instrument)
    {
        if (strlen(reqInsertOrder->AccountId) == 0)
            return ErrorAccountNotExist;
        if (reqInsertOrder->Direction != DirectionType::Buy && reqInsertOrder->Direction != DirectionType::Sell)
            return ErrorInvalidDirection;
        if (reqInsertOrder->OffsetFlag != OffsetFlagType::Open && reqInsertOrder->OffsetFlag != OffsetFlagType::Close && reqInsertOrder->OffsetFlag != OffsetFlagType::CloseToday)
            return ErrorInvalidOffsetFlag;
        switch (reqInsertOrder->OrderPriceType)
        {
        case OrderPriceTypeType::LimitPrice:
        case OrderPriceTypeType::AnyPriceFAK:
        case OrderPriceTypeType::AnyPriceFOK:
        case OrderPriceTypeType::LimitPriceFAK:
        case OrderPriceTypeType::LimitPriceFOK:
        case OrderPriceTypeType::BestOwnPrice:
        case OrderPriceTypeType::BestOppoPrice:
            break;
        default:
            return ErrorInvalidOrderPriceType;
        }
        //if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::LimitPrice && (reqInsertOrder->Price > instrument->UpperLimitPrice || reqInsertOrder->Price < instrument->LowerLimitPrice))
        //	return ErrorInvalidOrderPrice;
        if (reqInsertOrder->Volume <= 0)
            return ErrorInvalidOrderVolume;
        if (IsMarketPriceClass(reqInsertOrder->OrderPriceType))
        {
            if (instrument->MaxMarketOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxMarketOrderVolume)
                return ErrorInvalidOrderVolume;
            if (instrument->MinMarketOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinMarketOrderVolume)
                return ErrorInvalidOrderVolume;
        }
        else
        {
            if (instrument->MaxLimitOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxLimitOrderVolume)
                return ErrorInvalidOrderVolume;
            if (instrument->MinLimitOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinLimitOrderVolume)
                return ErrorInvalidOrderVolume;
        }
        return ErrorNone;
    }
    int CheckForCancelOrder(QuantTrading::Order* order)
    {
        if (order->OrderStatus == OrderStatusType::Inserting || order->OrderStatus == OrderStatusType::Inserted || order->OrderStatus == OrderStatusType::PartTraded)
        {
            return ErrorNone;
        }
        return ErrorFinalOrderStatus;
    }
    QuantTrading::Order* CreateOrder(ReqInsertOrderPackage* reqPackage, QuantTrading::Account* account, QuantTrading::Instrument* instrument,
        const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime, const OfferIdType& offerId)
    {
        auto order = Order::Allocate();
        memset(order, 0, sizeof(Order));
        Utility::Strcpy(order->TradingDay, tradingDay);
        Utility::Strcpy(order->AccountId, reqPackage->ReqInsertOrder->AccountId);
        order->AccountType = account->AccountType;
        Utility::Strcpy(order->ExchangeId, reqPackage->ReqInsertOrder->ExchangeId);
        Utility::Strcpy(order->InstrumentId, reqPackage->ReqInsertOrder->InstrumentId);
        order->ProductClass = instrument->ProductClass;
        order->OrderId = GetNextOrderID();
        strcpy(order->OrderSysId, std::to_string(order->OrderId).c_str());
        order->Direction = reqPackage->ReqInsertOrder->Direction;
        order->OffsetFlag = reqPackage->ReqInsertOrder->OffsetFlag;
        order->OrderPriceType = reqPackage->ReqInsertOrder->OrderPriceType;
        order->Price = reqPackage->ReqInsertOrder->Price;
        order->Volume = reqPackage->ReqInsertOrder->Volume;
        order->VolumeTotal = reqPackage->ReqInsertOrder->Volume;
        order->VolumeTraded = 0;
        order->VolumeMultiple = instrument->VolumeMultiple;
        order->OrderStatus = OrderStatusType::Inserted;
        Utility::Strcpy(order->OrderDate, orderDate);
        Utility::Strcpy(order->OrderTime, orderTime);
        order->SessionId = reqPackage->SessionId;
        order->ClientOrderId = reqPackage->ReqInsertOrder->ClientOrderId;
        order->RequestId = reqPackage->Head.MsgSeqNum;
        order->OfferId = offerId;
        order->TradeGroupId = account->TradeGroupId;
        order->RiskGroupId = account->RiskGroupId;
        order->CommissionGroupId = account->CommissionGroupId;
        order->RebuildMark = false;
        order->IsForceClose = false;

        return order;
    }
    QuantTrading::Position* CreatePosition(QuantTrading::Trade* trade, const PosiDirectionType& posiDirection)
    {
        auto position = QuantTrading::Position::Allocate();
        memset(position, 0, sizeof(Position));
        strcpy(position->TradingDay, trade->TradingDay);
        strcpy(position->AccountId, trade->AccountId);
        position->AccountType = trade->AccountType;
        strcpy(position->ExchangeId, trade->ExchangeId);
        strcpy(position->InstrumentId, trade->InstrumentId);
        position->ProductClass = trade->ProductClass;
        position->PosiDirection = posiDirection;
        position->TotalPosition = trade->Volume;
        position->PositionFrozen = 0;
        position->TodayPosition = trade->Volume;
        position->Commission = trade->Commission;
        position->VolumeMultiple = trade->VolumeMultiple;
        position->PreSettlementPrice = trade->Price;
        position->SettlementPrice = trade->Price;
        return position;
    }
    QuantTrading::PositionDetail* CreatePositionDetail(QuantTrading::Trade* trade, const PosiDirectionType& posiDirection)
    {
        auto positionDetail = QuantTrading::PositionDetail::Allocate();
        memset(positionDetail, 0, sizeof(PositionDetail));
        strcpy(positionDetail->TradingDay, trade->TradingDay);
        strcpy(positionDetail->AccountId, trade->AccountId);
        positionDetail->AccountType = trade->AccountType;
        strcpy(positionDetail->ExchangeId, trade->ExchangeId);
        strcpy(positionDetail->InstrumentId, trade->InstrumentId);
        positionDetail->ProductClass = trade->ProductClass;
        positionDetail->PosiDirection = posiDirection;
        strcpy(positionDetail->OpenDate, trade->TradingDay);
        strcpy(positionDetail->TradeId, trade->TradeId);
        positionDetail->Volume = trade->Volume;
        positionDetail->OpenPrice = trade->Price;
        positionDetail->Commission = trade->Commission;
        positionDetail->VolumeMultiple = trade->VolumeMultiple;
        positionDetail->CloseVolume = 0;
        positionDetail->CloseAmount = 0.0;
        positionDetail->PreSettlementPrice = trade->Price;
        positionDetail->SettlementPrice = trade->Price;
        return positionDetail;
    }
}
