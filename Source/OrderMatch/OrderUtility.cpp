#include "OrderUtility.h"
#include "TimeUtility.h"
#include "Error.h"
#include <string>

using namespace std;
using namespace mdb;

bool OrderLessForPrice::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	if (left->Price < right->Price)
		return true;
	else if (left->Price > right->Price)
		return false;
	return left->OrderID < right->OrderID;
}
bool OrderLessForPriceOpposite::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	if (left->Price > right->Price)
		return true;
	else if (left->Price < right->Price)
		return false;
	return left->OrderID > right->OrderID;
}
bool OrderLessForOrderID::operator()(const mdb::Order* const left, const mdb::Order* const right) const
{
	return left->OrderID < right->OrderID;
}

OrderIDType GetNextOrderID()
{
	static OrderIDType m_MaxOrderID = 0;
	return ++m_MaxOrderID;
}
int CheckForInsertOrder(ReqInsertOrderField* reqInsertOrder, mdb::Instrument* instrument)
{
	if (strlen(reqInsertOrder->AccountID) == 0)
		return ErrorAccountNotExist;
	if (reqInsertOrder->Direction != DirectionType::Buy && reqInsertOrder->Direction != DirectionType::Sell)
		return ErrorInvalidDirection;
	if (reqInsertOrder->OffsetFlag != OffsetFlagType::Open && reqInsertOrder->OffsetFlag != OffsetFlagType::Close && reqInsertOrder->OffsetFlag != OffsetFlagType::CloseToday)
		return ErrorInvalidOffsetFlag;
	if (reqInsertOrder->OrderPriceType != OrderPriceTypeType::LimitPrice && reqInsertOrder->OrderPriceType != OrderPriceTypeType::AnyPrice)
		return ErrorInvalidOrderPriceType;
	//if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::LimitPrice && (reqInsertOrder->Price > instrument->UpperLimitPrice || reqInsertOrder->Price < instrument->LowerLimitPrice))
	//	return ErrorInvalidOrderPrice;
	if (reqInsertOrder->Volume <= 0)
		return ErrorInvalidOrderVolume;
	if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (instrument->MaxLimitOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxLimitOrderVolume)
			return ErrorInvalidOrderVolume;
		if (instrument->MinLimitOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinLimitOrderVolume)
			return ErrorInvalidOrderVolume;
	}
	if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::AnyPrice)
	{
		if (instrument->MaxMarketOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxMarketOrderVolume)
			return ErrorInvalidOrderVolume;
		if (instrument->MinMarketOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinMarketOrderVolume)
			return ErrorInvalidOrderVolume;
	}
	return ErrorNone;
}
mdb::Order* InitOrder(ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::PrimaryAccount* primaryAccount, mdb::Instrument* instrument,
	const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime)
{
	auto order = Order::Allocate();
	memset(order, 0, sizeof(Order));
	memcpy(order->TradingDay, tradingDay, sizeof(DateType));
	memcpy(order->AccountID, reqPackage->ReqInsertOrder->AccountID, sizeof(AccountIDType));
	order->AccountType = account->AccountType;
	memcpy(order->ExchangeID, reqPackage->ReqInsertOrder->ExchangeID, sizeof(ExchangeIDType));
	memcpy(order->InstrumentID, reqPackage->ReqInsertOrder->InstrumentID, sizeof(InstrumentIDType));
	order->ProductClass = instrument->ProductClass;
	order->OrderID = GetNextOrderID();
	strcpy(order->OrderSysID, std::to_string(order->OrderID).c_str());
	order->Direction = reqPackage->ReqInsertOrder->Direction;
	order->OffsetFlag = reqPackage->ReqInsertOrder->OffsetFlag;
	order->OrderPriceType = reqPackage->ReqInsertOrder->OrderPriceType;
	order->Price = reqPackage->ReqInsertOrder->Price;
	order->Volume = reqPackage->ReqInsertOrder->Volume;
	order->VolumeTotal = reqPackage->ReqInsertOrder->Volume;
	order->VolumeTraded = 0;
	order->VolumeMultiple = instrument->VolumeMultiple;
	order->OrderStatus = OrderStatusType::Inserted;
	memcpy(order->OrderDate, orderDate, sizeof(DateType));
	memcpy(order->OrderTime, orderTime, sizeof(DateType));
	order->SessionID = reqPackage->SessionID;
	order->ClientOrderID = reqPackage->ReqInsertOrder->ClientOrderID;
	order->RequestID = reqPackage->Head.MsgSeqNum;
	order->OfferID = primaryAccount->OfferID;
	order->TradeGroupID = account->TradeGroupID;
	order->RiskGroupID = account->RiskGroupID;
	order->CommissionGroupID = account->CommissionGroupID;
	order->RebuildMark = false;
	order->IsForceClose = false;

	return order;
}

PriceType GetMatchPrice(OrderPriceTypeType orderPriceType, PriceType orderPrice, PriceType oppoPrice, PriceType lastPrice)
{
	if (orderPriceType != OrderPriceTypeType::LimitPrice || lastPrice == std::numeric_limits<double>::infinity())
	{
		return oppoPrice;
	}
	if (oppoPrice <= orderPrice && orderPrice <= lastPrice)
		return orderPrice;
	if (oppoPrice >= orderPrice && orderPrice >= lastPrice)
		return orderPrice;

	if (orderPrice <= oppoPrice && oppoPrice <= lastPrice)
		return oppoPrice;
	if (orderPrice >= oppoPrice && oppoPrice >= lastPrice)
		return oppoPrice;
	return lastPrice;
}

