#pragma once
#include <QuantTrading/Fields.h>

class BarSubscriber
{
public:
	virtual void OnBarMarketData(BarMarketDataField* bar) = 0;
};

