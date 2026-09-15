#include "Mdb.h"
#include "MdbTickSettlementPriceSource.h"
#include "doctest/doctest.h"
#include "SettlementTestHelpers.h"
#include <limits>

using namespace quanttrading::unittest;
using quanttrading::settlement::MdbTickSettlementPriceSource;
using quanttrading::settlement::Settlement;

TEST_SUITE("Settlement")
{

TEST_CASE("Settle明细逐日逐笔盈亏与期权市值")
{
    mdb::Mdb settlementMdb(quanttrading::simexchange::simexchangeTableList);
    FixedSettlementPriceSource priceSource;
    priceSource.prices = {{"IF2503", 3100.0}, {"IO2503", 110.0}};
    Settlement settlement(&settlementMdb, &priceSource);

    auto* todayFuture = InsertSettlementPositionDetail(&settlementMdb, "20240310", "20240310", "T1", PosiDirectionType::Long, 3000.0, 3050.0, 1);
    REQUIRE(todayFuture != nullptr);
    auto* carriedFuture = InsertSettlementPositionDetail(&settlementMdb, "20240310", "20240301", "T2", PosiDirectionType::Long, 3000.0, 3050.0, 1);
    REQUIRE(carriedFuture != nullptr);
    auto* option = InsertSettlementPositionDetail(&settlementMdb, "20240310", "20240310", "T3", PosiDirectionType::Long, 100.0, 90.0, 1,
        0, "IO2503");
    REQUIRE(option != nullptr);
    option->ProductClass = ProductClassType::FutureOption;

    SettleDay(settlement, "20240310");

    CHECK(todayFuture->SettlementPrice == doctest::Approx(3100.0));
    CHECK(todayFuture->PositionProfitByDate == doctest::Approx(30000.0));
    CHECK(todayFuture->PositionProfitByTrade == doctest::Approx(30000.0));
    CHECK(todayFuture->MarketValue == doctest::Approx(0.0));

    CHECK(carriedFuture->SettlementPrice == doctest::Approx(3100.0));
    CHECK(carriedFuture->PositionProfitByDate == doctest::Approx(15000.0));
    CHECK(carriedFuture->PositionProfitByTrade == doctest::Approx(30000.0));

    CHECK(option->SettlementPrice == doctest::Approx(110.0));
    CHECK(option->PositionProfitByDate == doctest::Approx(3000.0));
    CHECK(option->MarketValue == doctest::Approx(33000.0));
}

TEST_CASE("Settle聚合持仓与资金并核算权益可用")
{
    mdb::Mdb settlementMdb(quanttrading::simexchange::simexchangeTableList);
    FixedSettlementPriceSource priceSource;
    priceSource.prices = {{"IF2503", 3100.0}};
    Settlement settlement(&settlementMdb, &priceSource);

    auto* position = InsertSettlementPosition(&settlementMdb, "20240310", PosiDirectionType::Long, 3);
    REQUIRE(position != nullptr);
    auto* detail1 = InsertSettlementPositionDetail(&settlementMdb, "20240310", "20240310", "T1", PosiDirectionType::Long, 3000.0, 3050.0, 1);
    REQUIRE(detail1 != nullptr);
    detail1->CloseProfitByDate = 30000.0;
    detail1->CloseProfitByTrade = 30000.0;
    detail1->Commission = 50.0;
    auto* detail2 = InsertSettlementPositionDetail(&settlementMdb, "20240310", "20240301", "T2", PosiDirectionType::Long, 3000.0, 3050.0, 1);
    REQUIRE(detail2 != nullptr);
    detail2->CloseProfitByDate = 15000.0;
    detail2->CloseProfitByTrade = 30000.0;
    detail2->Commission = 30.0;
    auto* capital = InsertSettlementCapital(&settlementMdb, "20240310", 1000000.0, 0.0);
    REQUIRE(capital != nullptr);
    capital->FrozenCash = 500.0;
    capital->FrozenMargin = 200.0;
    capital->FrozenCommission = 30.0;

    SettleDay(settlement, "20240310");

    CHECK(position->CloseProfitByDate == doctest::Approx(45000.0));
    CHECK(position->CloseProfitByTrade == doctest::Approx(60000.0));
    CHECK(position->PositionProfitByDate == doctest::Approx(45000.0));
    CHECK(position->PositionProfitByTrade == doctest::Approx(60000.0));
    CHECK(position->Commission == doctest::Approx(80.0));
    CHECK(position->SettlementPrice == doctest::Approx(3100.0));

    CHECK(capital->PositionProfitByDate == doctest::Approx(45000.0));
    CHECK(capital->CloseProfitByDate == doctest::Approx(45000.0));
    CHECK(capital->Commission == doctest::Approx(80.0));
    CHECK(capital->Balance == doctest::Approx(1089920.0));
    CHECK(capital->Available == doctest::Approx(1089190.0));
}

TEST_CASE("RollToNextDay结转未平记录并过滤已平与零持仓")
{
    mdb::Mdb settlementMdb(quanttrading::simexchange::simexchangeTableList);
    FixedSettlementPriceSource priceSource;
    Settlement settlement(&settlementMdb, &priceSource);

    auto* capital = InsertSettlementCapital(&settlementMdb, "20240301", 1000000.0, 1100000.0);
    REQUIRE(capital != nullptr);
    auto* openPosition = InsertSettlementPosition(&settlementMdb, "20240301", PosiDirectionType::Long, 2, 3100.0);
    REQUIRE(openPosition != nullptr);
    openPosition->TodayPosition = 2;
    auto* closedPosition = InsertSettlementPosition(&settlementMdb, "20240301", PosiDirectionType::Short, 0, 3100.0);
    REQUIRE(closedPosition != nullptr);
    auto* carriedDetail = InsertSettlementPositionDetail(&settlementMdb, "20240301", "20240301", "T1", PosiDirectionType::Long, 3000.0, 3050.0, 2, 1);
    REQUIRE(carriedDetail != nullptr);
    carriedDetail->SettlementPrice = 3100.0;
    auto* closedDetail = InsertSettlementPositionDetail(&settlementMdb, "20240301", "20240301", "T2", PosiDirectionType::Long, 3000.0, 3050.0, 1, 1);
    REQUIRE(closedDetail != nullptr);

    RollDay(settlement, "20240301", "20240302");

    CHECK(CountByTradingDay(settlementMdb.position, "20240302") == 1);
    auto* nextPosition = FirstByTradingDay(settlementMdb.position, "20240302");
    REQUIRE(nextPosition != nullptr);
    CHECK(nextPosition->TotalPosition == 2);
    CHECK(nextPosition->TodayPosition == 0);
    CHECK(nextPosition->PreSettlementPrice == doctest::Approx(3100.0));

    CHECK(CountByTradingDay(settlementMdb.positionDetail, "20240302") == 1);
    auto* nextDetail = FirstByTradingDay(settlementMdb.positionDetail, "20240302");
    REQUIRE(nextDetail != nullptr);
    CHECK(std::string(nextDetail->OpenDate) == "20240301");
    CHECK(nextDetail->Volume == 2);
    CHECK(nextDetail->CloseVolume == 1);
    CHECK(nextDetail->PreSettlementPrice == doctest::Approx(3100.0));

    CHECK(CountByTradingDay(settlementMdb.capital, "20240302") == 1);
    auto* nextCapital = FirstByTradingDay(settlementMdb.capital, "20240302");
    REQUIRE(nextCapital != nullptr);
    CHECK(nextCapital->PreBalance == doctest::Approx(1100000.0));
    CHECK(nextCapital->MarketValue == doctest::Approx(0.0));
}

TEST_CASE("MdbTickSettlementPriceSource异常值逐级回退")
{
    mdb::Mdb settlementMdb(quanttrading::simexchange::simexchangeTableList);
    MdbTickSettlementPriceSource priceSource(&settlementMdb);
    auto infinity = std::numeric_limits<double>::infinity();

    auto makeTick = [&](const char* instrumentID, double lastPrice, double preSettlementPrice)
    {
        auto* tick = mdb::DepthMarketData::Allocate();
        std::memset(tick, 0, sizeof(mdb::DepthMarketData));
        CopyString(tick->TradingDay, "20240308");
        CopyString(tick->ExchangeID, "CFFEX");
        CopyString(tick->InstrumentID, instrumentID);
        tick->LastPrice = lastPrice;
        tick->PreSettlementPrice = preSettlementPrice;
        REQUIRE(settlementMdb.depthMarketData->Insert(tick));
    };

    auto* validDetail = InsertSettlementPositionDetail(&settlementMdb, "20240308", "20240308", "T1", PosiDirectionType::Long, 3000.0, 3000.0, 1);
    REQUIRE(validDetail != nullptr);
    auto* infDetail = InsertSettlementPositionDetail(&settlementMdb, "20240308", "20240308", "T2", PosiDirectionType::Long, 3000.0, 3000.0, 1, 0, "IF2504");
    REQUIRE(infDetail != nullptr);
    auto* missingDetail = InsertSettlementPositionDetail(&settlementMdb, "20240308", "20240308", "T3", PosiDirectionType::Long, 3000.0, 3000.0, 1, 0, "IF2505");
    REQUIRE(missingDetail != nullptr);
    auto* allInfDetail = InsertSettlementPositionDetail(&settlementMdb, "20240308", "20240308", "T4", PosiDirectionType::Long, 3000.0, 3000.0, 1, 0, "IF2506");
    REQUIRE(allInfDetail != nullptr);

    makeTick("IF2503", 3110.0, 3090.0);
    makeTick("IF2504", infinity, 3090.0);
    makeTick("IF2506", infinity, infinity);

    CHECK(priceSource.GetSettlementPrice(validDetail) == doctest::Approx(3110.0));
    CHECK(priceSource.GetSettlementPrice(infDetail) == doctest::Approx(3090.0));
    CHECK(priceSource.GetSettlementPrice(missingDetail) == doctest::Approx(3000.0));
    CHECK(priceSource.GetSettlementPrice(allInfDetail) == doctest::Approx(3000.0));
}

}
