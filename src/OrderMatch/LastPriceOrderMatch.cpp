#include "LastPriceOrderMatch.h"
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace mdb;
using namespace spark::core;

LastPriceOrderMatch::LastPriceOrderMatch(const DateType& tradingDay, int maxTradeID)
	:OrderMatch(tradingDay, maxTradeID)
{

}
LastPriceOrderMatch::~LastPriceOrderMatch()
{

}

void LastPriceOrderMatch::OnTick(mdb::DepthMarketData* mdTick)
{
	UpdateDateTime(mdTick->UpdateTs);
	if (mdTick->Volume > 0 && mdTick->LastPrice != std::numeric_limits<double>::infinity())
	{
		CheckMatch(mdTick);
	}
}
void LastPriceOrderMatch::OnBar(mdb::BarMarketData* mdBar)
{

}
void LastPriceOrderMatch::InsertOrder(mdb::Order* order)
{
	AddOrderToQueue(order);
}

void LastPriceOrderMatch::CheckMatch(mdb::DepthMarketData* mdTick)
{
	auto& marketBuyQueueOrders = m_MarketBuyOrders[mdTick->InstrumentID];
	for (auto& marketBuyQueueOrder : marketBuyQueueOrders)
	{
		GetNextTradeID(m_TradeID);
		Match(marketBuyQueueOrder, mdTick->LastPrice, marketBuyQueueOrder->VolumeTotal, m_TradeID);
	}
	m_MarketBuyOrders.erase(mdTick->InstrumentID);
	auto& marketSellQueueOrders = m_MarketSellOrders[mdTick->InstrumentID];
	for (auto& marketSellQueueOrder : marketSellQueueOrders)
	{
		GetNextTradeID(m_TradeID);
		Match(marketSellQueueOrder, mdTick->LastPrice, marketSellQueueOrder->VolumeTotal, m_TradeID);
	}
	m_MarketSellOrders.erase(mdTick->InstrumentID);

	auto& buyQueueOrders = m_BuyOrders[mdTick->InstrumentID];
	for (auto& buyQueueOrder : buyQueueOrders)
	{
		if (!CheckMatchForOrder(mdTick, buyQueueOrder))
		{
			break;
		}
	}
	std::erase_if(buyQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });

	auto& sellQueueOrders = m_SellOrders[mdTick->InstrumentID];
	for (auto& sellQueueOrder : sellQueueOrders)
	{
		if (!CheckMatchForOrder(mdTick, sellQueueOrder))
		{
			break;
		}
	}
	std::erase_if(sellQueueOrders, [](mdb::Order* order) {return order->VolumeTotal == 0; });
}
bool LastPriceOrderMatch::CheckMatchForOrder(mdb::DepthMarketData* mdTick, mdb::Order* order)
{
	if (order->Direction == DirectionType::Buy && DoubleUtility::DoubleLess(order->Price, mdTick->LastPrice))
		return false;
	else if (order->Direction == DirectionType::Sell && DoubleUtility::DoubleGreat(order->Price, mdTick->LastPrice))
		return false;

	GetNextTradeID(m_TradeID);
	Match(order, mdTick->LastPrice, order->VolumeTotal, m_TradeID);
	return true;
}
