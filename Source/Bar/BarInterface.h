#pragma once
#include "Packages.h"

class BarSubscriber
{
public:
	virtual void OnBarMarketData(BarMarketDataField* bar) = 0;
};

