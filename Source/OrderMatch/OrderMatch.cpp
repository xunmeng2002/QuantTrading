#include "OrderMatch.h"
#include "OrderBookOrderMatch.h"
#include "LastPriceOrderMatch.h"
#include "OppositePriceOrderMatch.h"
#include "BarOrderMatch.h"
#include "Logger.h"
#include "TimeUtility.h"

using namespace std;
using namespace mdb;

OrderMatch* OrderMatch::CreateOrderMatch(const MatchModeType& matchMode, mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID)
{
	switch (matchMode)
	{
	case MatchModeType::OrderBook:
		return new OrderBookOrderMatch(mdb, tradingDay, maxTradeID);
	case MatchModeType::LastPrice:
		return new LastPriceOrderMatch(mdb, tradingDay, maxTradeID);
	case MatchModeType::OppositePrice:
		return new OppositePriceOrderMatch(mdb, tradingDay, maxTradeID);
	case MatchModeType::Bar:
		return new BarOrderMatch(mdb, tradingDay, maxTradeID);
	default:
		break;
	}
	WriteLog(LogLevel::Error, "CreateOrderMatch Failed. MatchModeType:%c", matchMode);
	return nullptr;
}
OrderMatch::OrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID)
	:m_Mdb(mdb), m_OrderMatchSubscriber(nullptr), m_MaxTradeID(maxTradeID), m_TradeID(""), m_CurrDate(""), m_CurrTime("")
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

void OrderMatch::CancelOrder(mdb::Order* order)
{
	auto newOrder = Order::Allocate();
	memcpy(newOrder, order, sizeof(Order));
	newOrder->VolumeTotal = 0;
	newOrder->OrderStatus = order->VolumeTraded > 0 ? OrderStatusType::PartTradedCanceled : OrderStatusType::Canceled;
	strcpy(newOrder->CancelDate, m_CurrDate);
	strcpy(newOrder->CancelTime, m_CurrTime);
	m_Mdb->t_Order->Update(order, newOrder);
	m_OrderMatchSubscriber->OnOrder(order);
}

void OrderMatch::Match(mdb::Order* order, PriceType price, VolumeType volume, const TradeIDType& tradeID)
{
	if (volume <= 0)
		return;
	auto newOrder = Order::Allocate();
	memcpy(newOrder, order, sizeof(Order));
	newOrder->VolumeTraded += volume;
	newOrder->VolumeTotal -= volume;
	newOrder->OrderStatus = order->VolumeTotal > 0 ? OrderStatusType::PartTraded : OrderStatusType::AllTraded;
	m_Mdb->t_Order->Update(order, newOrder);
	m_OrderMatchSubscriber->OnOrder(order);

	auto trade = Trade::Allocate();
	memset(trade, 0, sizeof(Trade));
	strcpy(trade->TradingDay, order->TradingDay);
	strcpy(trade->AccountID, order->AccountID);
	trade->AccountType = order->AccountType;
	strcpy(trade->ExchangeID, order->ExchangeID);
	strcpy(trade->InstrumentID, order->InstrumentID);
	trade->ProductClass = order->ProductClass;
	trade->OrderID = order->OrderID;
	strcpy(trade->OrderSysID, order->OrderSysID);
	strcpy(trade->TradeID, tradeID);
	trade->Direction = order->Direction;
	trade->OffsetFlag = order->OffsetFlag;
	trade->Price = price;
	trade->Volume = volume;
	trade->VolumeMultiple = order->VolumeMultiple;
	trade->TradeAmount = price * volume * order->VolumeMultiple;;
	trade->Commission = 0;
	strcpy(trade->TradeDate, m_CurrDate);
	strcpy(trade->TradeTime, m_CurrTime);
	m_Mdb->t_Trade->Insert(trade);

	m_OrderMatchSubscriber->OnTrade(trade);
}
void OrderMatch::AddOrderToQueue(mdb::Order* order)
{
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_BuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_SellOrders[order->InstrumentID].insert(order);
		}
	}
	else
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_MarketBuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_MarketSellOrders[order->InstrumentID].insert(order);
		}
	}
}
void OrderMatch::GetNextTradeID(TradeIDType& tradeID)
{
	sprintf(tradeID, "%s%08d", m_TradingDay, ++m_MaxTradeID);
}
void OrderMatch::UpdateDateTime()
{
	GetLocalDateTime(m_CurrDate, m_CurrTime);
}
void OrderMatch::UpdateDateTime(const Int64Type& updateTs)
{
	GetDateTimeFromTimeStamp(updateTs, m_CurrDate, m_CurrTime);
}

