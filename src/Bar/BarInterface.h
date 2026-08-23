#pragma once
#include <QuantTrading/Fields.h>

namespace quanttrading::bar
{
    class BarSubscriber
    {
    public:
        virtual void OnBarMarketData(BarMarketDataField* bar) = 0;
    };
}
