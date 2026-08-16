#include "OrderUtility.h"
#include "Error.h"
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/TimeUtility.h>
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
int CheckForCancelOrder(mdb::Order* order)
{
	if (order->OrderStatus == OrderStatusType::Inserting || order->OrderStatus == OrderStatusType::Inserted || order->OrderStatus == OrderStatusType::PartTraded)
	{
		return ErrorNone;
	}
	return ErrorFinalOrderStatus;
}
mdb::Order* CreateOrder(ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::Instrument* instrument,
	const DateType& tradingDay, const DateType& orderDate, const TimeType& orderTime, const OfferIDType& offerID)
{
	auto order = Order::Allocate();
	memset(order, 0, sizeof(Order));
	Utility::Strcpy(order->TradingDay, tradingDay);
	Utility::Strcpy(order->AccountID, reqPackage->ReqInsertOrder->AccountID);
	order->AccountType = account->AccountType;
	Utility::Strcpy(order->ExchangeID, reqPackage->ReqInsertOrder->ExchangeID);
	Utility::Strcpy(order->InstrumentID, reqPackage->ReqInsertOrder->InstrumentID);
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
    Utility::Strcpy(order->OrderDate, orderDate);
    Utility::Strcpy(order->OrderTime, orderTime);
	order->SessionID = reqPackage->SessionID;
	order->ClientOrderID = reqPackage->ReqInsertOrder->ClientOrderID;
	order->RequestID = reqPackage->Head.MsgSeqNum;
	order->OfferID = offerID;
	order->TradeGroupID = account->TradeGroupID;
	order->RiskGroupID = account->RiskGroupID;
	order->CommissionGroupID = account->CommissionGroupID;
	order->RebuildMark = false;
	order->IsForceClose = false;

	return order;
}
mdb::Position* CreatePosition(mdb::Trade* trade, const PosiDirectionType& posiDirection)
{
	auto position = mdb::Position::Allocate();
	memset(position, 0, sizeof(Position));
	strcpy(position->TradingDay, trade->TradingDay);
	strcpy(position->AccountID, trade->AccountID);
	position->AccountType = trade->AccountType;
	strcpy(position->ExchangeID, trade->ExchangeID);
	strcpy(position->InstrumentID, trade->InstrumentID);
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
mdb::PositionDetail* CreatePositionDetail(mdb::Trade* trade, const PosiDirectionType& posiDirection)
{
	auto positionDetail = mdb::PositionDetail::Allocate();
	memset(positionDetail, 0, sizeof(PositionDetail));
	strcpy(positionDetail->TradingDay, trade->TradingDay);
	strcpy(positionDetail->AccountID, trade->AccountID);
	positionDetail->AccountType = trade->AccountType;
	strcpy(positionDetail->ExchangeID, trade->ExchangeID);
	strcpy(positionDetail->InstrumentID, trade->InstrumentID);
	positionDetail->ProductClass = trade->ProductClass;
	positionDetail->PosiDirection = posiDirection;
	strcpy(positionDetail->OpenDate, trade->TradingDay);
	strcpy(positionDetail->TradeID, trade->TradeID);
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

