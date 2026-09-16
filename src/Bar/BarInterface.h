#pragma once
#include <QuantTrading/Fields.h>

namespace QuantTrading::bar
{
    class BarSubscriber
    {
    public:
        virtual void OnBarMarketData(BarMarketDataField* bar) = 0;
    };
}
