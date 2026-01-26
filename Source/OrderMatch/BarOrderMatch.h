#pragma once
#include "OrderMatch.h"


class BarOrderMatch : public OrderMatch
{
public:
	BarOrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID = 0);
	virtual ~BarOrderMatch();

	virtual void OnTick(mdb::DepthMarketData* mdTick) override;
	virtual void OnBar(mdb::BarMarketData* mdBar) override;
	virtual void InsertOrder(mdb::Order* order) override;

protected:
	void CheckMatch(mdb::BarMarketData* mdBar);
	bool CheckMatchForOrder(mdb::BarMarketData* mdBar, mdb::Order* order);
};




