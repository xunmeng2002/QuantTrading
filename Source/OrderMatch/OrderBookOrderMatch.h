#pragma once
#include "OrderMatch.h"


class OrderBookOrderMatch : public OrderMatch
{
public:
	OrderBookOrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID = 0);
	virtual ~OrderBookOrderMatch();

	virtual void OnTick(mdb::DepthMarketData* mdTick) override;
	virtual void OnBar(mdb::BarMarketData* mdBar) override;
	virtual void InsertOrder(mdb::Order* order) override;

protected:
	void CheckMatch(mdb::Order* order);
	bool  CheckMatchForTwoOrder(mdb::Order* order, mdb::Order* queueOrder);
};




