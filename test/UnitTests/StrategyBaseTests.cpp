#include "TestHelpers.h"
#include "StrategyBase.h"

#include "doctest/doctest.h"

#include <string>

using namespace quanttrading::unittest;

namespace quanttrading::unittest
{
    // 暴露 StrategyBase 受保护接口给测试断言
    class ProbeStrategy : public quanttrading::strategy::StrategyBase
    {
    public:
        using StrategyBase::StrategyBase;
        using StrategyBase::SubscribeTick;
        using StrategyBase::BuyOpen;
        using StrategyBase::SellOpen;
        using StrategyBase::BuyClose;
        using StrategyBase::SellClose;
        using StrategyBase::CancelOrder;
        using StrategyBase::GetLongPosition;
        using StrategyBase::GetShortPosition;
        using StrategyBase::GetLastPrice;

        void SetSubscribeOnStart(const char* exchange_id, const char* instrument_id)
        {
            subscribe_exchange_id = exchange_id;
            subscribe_instrument_id = instrument_id;
        }

    protected:
        void OnStart() override
        {
            if (!subscribe_exchange_id.empty())
            {
                SubscribeTick(subscribe_exchange_id.c_str(), subscribe_instrument_id.c_str());
            }
        }

    private:
        std::string subscribe_exchange_id;
        std::string subscribe_instrument_id;
    };
}

TEST_CASE("StrategyBase subscribes market data on start")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    strategy.SetSubscribeOnStart("CFFEX", "IF2503");
    CHECK(strategy.Start());
    CHECK(fake_api.subscribe_count == 1);
}

TEST_CASE("StrategyBase accumulates position and last price from events")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto md_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.registered_spi->OnRtnDepthMarketData(&md_tick);
    CHECK(strategy.GetLastPrice("IF2503") == doctest::Approx(4000.0));

    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 1);
    CHECK(strategy.GetShortPosition("IF2503") == 0);

    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
    CHECK(strategy.GetShortPosition("IF2503") == 0);
}

TEST_CASE("StrategyBase accumulates short position from sell open trade")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Sell, OffsetFlagType::Open, 4010.0, 2, 300, 8.5);
    fake_api.registered_spi->OnRtnTrade(&open_trade);
    CHECK(strategy.GetShortPosition("IF2503") == 2);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
}

TEST_CASE("StrategyBase cancels by engine OrderID when report seen")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto client_order_id = strategy.BuyOpen("CFFEX", "IF2503", 3990.0, 1);
    auto order = MakeOrderField("IF2503", 42, client_order_id);
    fake_api.registered_spi->OnRtnOrder(&order);

    REQUIRE(strategy.CancelOrder(client_order_id));
    REQUIRE(fake_api.cancel_requests.size() == 1);
    CHECK(fake_api.cancel_requests[0].OrderID == 42);
    CHECK(fake_api.cancel_requests[0].ClientOrderID == client_order_id);
}

TEST_CASE("StrategyBase cancels by ClientOrderID fallback without report")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto client_order_id = strategy.BuyOpen("CFFEX", "IF2503", 3990.0, 1);
    REQUIRE(strategy.CancelOrder(client_order_id));
    REQUIRE(fake_api.cancel_requests.size() == 1);
    CHECK(fake_api.cancel_requests[0].OrderID == 0);
    CHECK(fake_api.cancel_requests[0].ClientCancelOrderID == client_order_id);
    CHECK(fake_api.cancel_requests[0].ClientOrderID == client_order_id);
    CHECK(std::string(fake_api.cancel_requests[0].ExchangeID) == "CFFEX");
    CHECK(std::string(fake_api.cancel_requests[0].InstrumentID) == "IF2503");
}

TEST_CASE("StrategyBase refuses cancel for unknown client order")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());
    CHECK_FALSE(strategy.CancelOrder(999));
    CHECK(fake_api.cancel_requests.empty());
}

TEST_CASE("StrategyBase releases api once on market data end")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    MarketDataEndField market_data_end;
    fake_api.registered_spi->OnRtnMarketDataEnd(&market_data_end);
    fake_api.registered_spi->OnRtnMarketDataEnd(&market_data_end);
    CHECK(fake_api.release_count == 1);
}
