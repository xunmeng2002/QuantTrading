#pragma once
#include "OrderMatch.h"


class LastPriceOrderMatch : public OrderMatch
{
public:
	LastPriceOrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID = 0);
	virtual ~LastPriceOrderMatch();

	virtual void OnTick(mdb::DepthMarketData* mdTick) override;
	virtual void OnBar(mdb::BarMarketData* mdBar) override;
	virtual void InsertOrder(mdb::Order* order) override;
protected:
	void CheckMatch(mdb::DepthMarketData* mdTick);
	bool CheckMatchForOrder(mdb::DepthMarketData* mdTick, mdb::Order* order);
};


