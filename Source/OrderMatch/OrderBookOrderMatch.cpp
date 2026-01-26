#include "OrderBookOrderMatch.h"
#include "DoubleUtility.h"

using namespace std;

OrderBookOrderMatch::OrderBookOrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID)
	:OrderMatch(mdb, tradingDay, maxTradeID)
{

}
OrderBookOrderMatch::~OrderBookOrderMatch()
{

}

void OrderBookOrderMatch::OnTick(mdb::DepthMarketData* mdTick)
{

}
void OrderBookOrderMatch::OnBar(mdb::BarMarketData* mdBar)
{

}
void OrderBookOrderMatch::InsertOrder(mdb::Order* order)
{
	UpdateDateTime();
	CheckMatch(order);
	if (order->VolumeTotal > 0)
	{
		AddOrderToQueue(order);
	}
	if (order->VolumeTraded == 0)
	{
		m_OrderMatchSubscriber->OnOrder(order);
	}
}
void OrderBookOrderMatch::CheckMatch(mdb::Order* order)
{
	if (order->Direction == DirectionType::Buy)
	{
		auto& queueOrders = m_SellOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			if (!CheckMatchForTwoOrder(order, queueOrder))
			{
				break;
			}
		}
	}
	else
	{
		auto& queueOrders = m_BuyOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			if (!CheckMatchForTwoOrder(order, queueOrder))
			{
				break;
			}
		}
	}
}
bool OrderBookOrderMatch::CheckMatchForTwoOrder(mdb::Order* order, mdb::Order* queueOrder)
{
	if (order->VolumeTotal <= 0)
		return false;
	if (queueOrder->VolumeTotal <= 0)
		return true;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy && DoubleLess(order->Price, queueOrder->Price))
			return false;
		if (order->Direction == DirectionType::Sell && DoubleGreat(order->Price, queueOrder->Price))
			return false;
	}

	VolumeType matchVolume = 0;
	PriceType matchPrice = 0.0;
	matchVolume = min(order->VolumeTotal, queueOrder->VolumeTotal);
	matchPrice = queueOrder->Price;

	GetNextTradeID(m_TradeID);
	Match(queueOrder, matchPrice, matchVolume, m_TradeID);
	Match(order, matchPrice, matchVolume, m_TradeID);
	return true;
}

