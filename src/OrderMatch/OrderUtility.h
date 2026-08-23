#pragma once
#include "MdbStructs.h"
#include "Packages.h"


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

    PriceType GetMatchPrice(OrderPriceTypeType orderPriceType, PriceType orderPrice, PriceType oppoPrice, PriceType lastPrice);
}


