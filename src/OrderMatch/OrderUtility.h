#pragma once
#include "MdbStructs.h"
#include "Packages.h"


namespace mdb
{
    class OrderTable;
}

namespace quanttrading::ordermatch
{
    struct OrderLessForPrice
    {
        bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
    };
    struct OrderLessForPriceOpposite
    {
        bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
    };
    struct OrderLessForOrderID
    {
        bool operator()(const mdb::Order* const left, const mdb::Order* const right) const;
    };

    int CheckForInsertOrder(ReqInsertOrderField* reqInsertOrder, mdb::Instrument* instrument);
    int CheckForCancelOrder(mdb::Order* order);
    mdb::Order* CreateOrder(quanttrading::packages::ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::Instrument* instrument,
        const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime, const OfferIDType& offerID = 0);
    mdb::Position* CreatePosition(mdb::Trade* trade, const PosiDirectionType& posiDirection);
    mdb::PositionDetail* CreatePositionDetail(mdb::Trade* trade, const PosiDirectionType& posiDirection);

    // 市价类委托:价格不由下单者指定,入口量限走合约市价参数(MaxMarketOrderVolume)
    bool IsMarketPriceClass(OrderPriceTypeType orderPriceType);
    // 受价委托:扫簿受委托价格约束(限价族与已解析的对方最优),无界市价族不受约束
    bool HasOrderPriceBound(OrderPriceTypeType orderPriceType);

    OrderIDType GetNextOrderID();
    void SeedNextOrderIDFromMaxOrderID(OrderIDType maxOrderID);
    void SeedNextOrderIDFromOrders(mdb::OrderTable* orderTable);
}


