#pragma once
#include <QuantTrading/Fields.h>

namespace QuantTrading::Bar
{
    class BarSubscriber
    {
    public:
        virtual void OnBarMarketData(BarMarketDataField* bar) = 0;
    };
}
