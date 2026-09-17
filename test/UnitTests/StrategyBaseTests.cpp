#include "TestHelpers.h"
#include "StrategyBase.h"

#include "doctest/doctest.h"

#include <string>

using namespace QuantTrading::UnitTest;

namespace QuantTrading::UnitTest
{
    // 暴露 StrategyBase 受保护接口给测试断言
    class ProbeStrategy : public QuantTrading::strategy::StrategyBase
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

        void SetSubscribeOnStart(const char* exchange_id, const char* instrumentId)
        {
            subscribe_exchange_id = exchange_id;
            subscribe_instrument_id = instrumentId;
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
    CHECK(fake_api.SubscribeCount == 1);
}

// 账户注册先于 OnStart 的行情订阅（requestId 1 = 注册，2 = 订阅）：引擎账户表在首次下单前必已自建
TEST_CASE("StrategyBase registers account before subscribing market data on start")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    strategy.SetSubscribeOnStart("CFFEX", "IF2503");
    CHECK(strategy.Start());
    REQUIRE(fake_api.RegisterAccountRequests.size() == 1);
    CHECK(std::string(fake_api.RegisterAccountRequests[0].AccountId) == "accountA");
    CHECK(fake_api.RegisterAccountRequestId == 1);
    CHECK(fake_api.LastSubscribeRequestId > fake_api.RegisterAccountRequestId);
}

TEST_CASE("StrategyBase registers account exactly once across repeated start state")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    CHECK(strategy.Start());
    CHECK(fake_api.RegisterAccountRequests.size() == 1);
}

TEST_CASE("StrategyBase accumulates position and last price from events")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto md_tick = MakeMdTickField("IF2503", 4000.0);
    fake_api.RegisteredSpi->OnRtnDepthMarketData(&md_tick);
    CHECK(strategy.GetLastPrice("IF2503") == doctest::Approx(4000.0));

    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Buy, OffsetFlagType::Open, 3990.0, 1, 300, 8.5);
    fake_api.RegisteredSpi->OnRtnTrade(&open_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 1);
    CHECK(strategy.GetShortPosition("IF2503") == 0);

    auto close_trade = MakeTradeField("IF2503", 43, DirectionType::Sell, OffsetFlagType::Close, 4000.0, 1, 300, 8.5);
    fake_api.RegisteredSpi->OnRtnTrade(&close_trade);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
    CHECK(strategy.GetShortPosition("IF2503") == 0);
}

TEST_CASE("StrategyBase accumulates short position from sell open trade")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto open_trade = MakeTradeField("IF2503", 42, DirectionType::Sell, OffsetFlagType::Open, 4010.0, 2, 300, 8.5);
    fake_api.RegisteredSpi->OnRtnTrade(&open_trade);
    CHECK(strategy.GetShortPosition("IF2503") == 2);
    CHECK(strategy.GetLongPosition("IF2503") == 0);
}

TEST_CASE("StrategyBase cancels by engine OrderId when report seen")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto clientOrderId = strategy.BuyOpen("CFFEX", "IF2503", 3990.0, 1);
    auto order = MakeOrderField("IF2503", 42, clientOrderId);
    fake_api.RegisteredSpi->OnRtnOrder(&order);

    REQUIRE(strategy.CancelOrder(clientOrderId));
    REQUIRE(fake_api.CancelRequests.size() == 1);
    CHECK(fake_api.CancelRequests[0].OrderId == 42);
    CHECK(fake_api.CancelRequests[0].ClientOrderId == clientOrderId);
}

TEST_CASE("StrategyBase cancels by ClientOrderId fallback without report")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    auto clientOrderId = strategy.BuyOpen("CFFEX", "IF2503", 3990.0, 1);
    REQUIRE(strategy.CancelOrder(clientOrderId));
    REQUIRE(fake_api.CancelRequests.size() == 1);
    CHECK(fake_api.CancelRequests[0].OrderId == 0);
    CHECK(fake_api.CancelRequests[0].ClientOrderId == clientOrderId);
    CHECK(std::string(fake_api.CancelRequests[0].ExchangeId) == "CFFEX");
    CHECK(std::string(fake_api.CancelRequests[0].InstrumentId) == "IF2503");
}

TEST_CASE("StrategyBase refuses cancel for unknown client order")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());
    CHECK_FALSE(strategy.CancelOrder(999));
    CHECK(fake_api.CancelRequests.empty());
}

TEST_CASE("StrategyBase releases api once on market data end")
{
    FakeBackTestApi fake_api;
    ProbeStrategy strategy(&fake_api, "accountA");
    REQUIRE(strategy.Start());

    MarketDataEndField market_data_end;
    fake_api.RegisteredSpi->OnRtnMarketDataEnd(&market_data_end);
    fake_api.RegisteredSpi->OnRtnMarketDataEnd(&market_data_end);
    CHECK(fake_api.ReleaseCount == 1);
}
