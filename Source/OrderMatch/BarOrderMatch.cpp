#include "BarOrderMatch.h"
#include "DoubleUtility.h"
#include <string>

using namespace std;
using namespace mdb;


BarOrderMatch::BarOrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID)
	:OrderMatch(mdb, tradingDay, maxTradeID)
{

}
BarOrderMatch::~BarOrderMatch()
{

}

void BarOrderMatch::OnTick(mdb::DepthMarketData* mdTick)
{

}
void BarOrderMatch::OnBar(mdb::BarMarketData* mdBar)
{
	UpdateDateTime(mdBar->UpdateTs);
	CheckMatch(mdBar);
}
void BarOrderMatch::InsertOrder(mdb::Order* order)
{
	AddOrderToQueue(order);
}
void BarOrderMatch::CheckMatch(mdb::BarMarketData* mdBar)
{
	auto& marketBuyQueueOrders = m_MarketBuyOrders[mdBar->InstrumentID];
	for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
	{
		CheckMatchForOrder(mdBar, marketBuyQueueOrder);
	}
	m_MarketBuyOrders.erase(mdBar->InstrumentID);
	auto& marketSellQueueOrders = m_MarketSellOrders[mdBar->InstrumentID];
	for (auto& marketSellQueueOrder : marketSellQueueOrders)
	{
		CheckMatchForOrder(mdBar, marketSellQueueOrder);
	}
	m_MarketSellOrders.erase(mdBar->InstrumentID);

	auto& buyQueueOrders = m_BuyOrders[mdBar->InstrumentID];
	for (auto& buyQueueOrder : buyQueueOrders)
	{
		if (!CheckMatchForOrder(mdBar, buyQueueOrder))
		{
			break;
		}
	}
	std::erase_if(buyQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });

	auto& sellQueueOrders = m_SellOrders[mdBar->InstrumentID];
	for (auto& sellQueueOrder : sellQueueOrders)
	{
		if (!CheckMatchForOrder(mdBar, sellQueueOrder))
		{
			break;
		}
	}
	std::erase_if(sellQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });
}
bool BarOrderMatch::CheckMatchForOrder(mdb::BarMarketData* mdBar, mdb::Order* order)
{
	PriceType matchPrice;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy)
		{
			if (DoubleLess(order->Price, mdBar->Low))
				return false;
			matchPrice = DoubleGreat(order->Price, mdBar->High) ? mdBar->High : order->Price;
		}
		else
		{
			if (DoubleGreat(order->Price, mdBar->High))
				return false;
			matchPrice = DoubleLess(order->Price, mdBar->Low) ? mdBar->Low : order->Price;
		}
	}
	else
	{
		matchPrice = (mdBar->High + mdBar->Low) / 2;
	}
	GetNextTradeID(m_TradeID);
	Match(order, matchPrice, order->VolumeTotal, m_TradeID);
	return true;
}


