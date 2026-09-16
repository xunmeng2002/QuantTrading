#pragma once
#include "MdbStructs.h"
#include "MdbTables.h"
#include "Packages.h"


namespace QuantTrading
{
    class OrderTable;
}

namespace QuantTrading::ordermatch
{
    struct OrderLessForPrice
    {
        bool operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const;
    };
    struct OrderLessForPriceOpposite
    {
        bool operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const;
    };
    struct OrderLessForOrderID
    {
        bool operator()(const QuantTrading::Order* const left, const QuantTrading::Order* const right) const;
    };

    int CheckForInsertOrder(ReqInsertOrderField* reqInsertOrder, QuantTrading::Instrument* instrument);
    int CheckForCancelOrder(QuantTrading::Order* order);
    QuantTrading::Order* CreateOrder(QuantTrading::Packages::ReqInsertOrderPackage* reqPackage, QuantTrading::Account* account, QuantTrading::Instrument* instrument,
        const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime, const OfferIdType& offerId = 0);
    QuantTrading::Position* CreatePosition(QuantTrading::Trade* trade, const PosiDirectionType& posiDirection);
    QuantTrading::PositionDetail* CreatePositionDetail(QuantTrading::Trade* trade, const PosiDirectionType& posiDirection);

    // 市价类委托:价格不由下单者指定,入口量限走合约市价参数(MaxMarketOrderVolume)
    bool IsMarketPriceClass(OrderPriceTypeType orderPriceType);
    // 受价委托:扫簿受委托价格约束(限价族与已解析的对方最优),无界市价族不受约束
    bool HasOrderPriceBound(OrderPriceTypeType orderPriceType);

    OrderIdType GetNextOrderID();
    void SeedNextOrderIDFromMaxOrderID(OrderIdType maxOrderId);
    void SeedNextOrderIDFromOrders(QuantTrading::OrderTable* orderTable);
}


