#pragma once
#include "MdbStructs.h"
#include "Mdb.h"
#include "Packages.h"


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
mdb::Order* InitOrder(ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::PrimaryAccount* primaryAccount, mdb::Instrument* instrument,
	const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime);

PriceType GetMatchPrice(OrderPriceTypeType orderPriceType, PriceType orderPrice, PriceType oppoPrice, PriceType lastPrice);



