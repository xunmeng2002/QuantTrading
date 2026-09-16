#include "Mdb.h"
#include "doctest/doctest.h"
#include "SettlementTestHelpers.h"

using namespace QuantTrading::unittest;
using QuantTrading::settlement::PositionMaintenance;

TEST_SUITE("PositionMaintenance")
{

TEST_CASE("开仓成交建持仓与开仓明细")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    auto* trade = MakeSettlementTrade(tradePool, "20240301", "1", DirectionType::Buy, OffsetFlagType::Open, 3000.0, 2);
    maintenance.UpdateOnTrade(trade);

    auto* position = SelectSettlementPosition(&settlementMdb, "20240301", "IF2503", PosiDirectionType::Long);
    REQUIRE(position != nullptr);
    CHECK(position->TotalPosition == 2);
    CHECK(position->TodayPosition == 2);
    CHECK(position->PreSettlementPrice == 3000.0);
    CHECK(position->SettlementPrice == 3000.0);

    CHECK(CountSettlementPositionDetailByMatch(&settlementMdb, "20240301", PosiDirectionType::Long) == 1);
    auto* detail = SelectSettlementPositionDetail(&settlementMdb, "20240301", "IF2503", PosiDirectionType::Long, "20240301", "1");
    REQUIRE(detail != nullptr);
    CHECK(std::string(detail->OpenDate) == "20240301");
    CHECK(std::string(detail->TradeId) == "1");
    CHECK(detail->Volume == 2);
    CHECK(detail->OpenPrice == 3000.0);
    CHECK(detail->CloseVolume == 0);
}

TEST_CASE("同向加仓累计持仓且明细逐笔新建")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240301", "1", DirectionType::Buy, OffsetFlagType::Open, 3000.0, 2));
    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240301", "2", DirectionType::Buy, OffsetFlagType::Open, 3010.0, 1));

    auto* position = SelectSettlementPosition(&settlementMdb, "20240301", "IF2503", PosiDirectionType::Long);
    REQUIRE(position != nullptr);
    CHECK(position->TotalPosition == 3);
    // 加仓路径只累计 TotalPosition，TodayPosition 保持首次开仓写入值（与移植前回测行为一致）
    CHECK(position->TodayPosition == 2);
    CHECK(CountSettlementPositionDetailByMatch(&settlementMdb, "20240301", PosiDirectionType::Long) == 2);
}

TEST_CASE("平仓先开先平且跨日明细盈亏按昨结算价")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    REQUIRE(InsertSettlementPosition(&settlementMdb, "20240303", PosiDirectionType::Long, 2, 3050.0));
    REQUIRE(InsertSettlementPositionDetail(&settlementMdb, "20240303", "20240301", "T1", PosiDirectionType::Long, 3000.0, 3050.0, 1));
    REQUIRE(InsertSettlementPositionDetail(&settlementMdb, "20240303", "20240303", "T2", PosiDirectionType::Long, 3000.0, 3050.0, 1));

    auto* trade = MakeSettlementTrade(tradePool, "20240303", "3", DirectionType::Sell, OffsetFlagType::Close, 3100.0, 1);
    maintenance.UpdateOnTrade(trade);

    auto* position = SelectSettlementPosition(&settlementMdb, "20240303", "IF2503", PosiDirectionType::Long);
    REQUIRE(position != nullptr);
    CHECK(position->TotalPosition == 1);

    auto* closed = SelectSettlementPositionDetail(&settlementMdb, "20240303", "IF2503", PosiDirectionType::Long, "20240301", "T1");
    REQUIRE(closed != nullptr);
    CHECK(closed->CloseVolume == 1);
    CHECK(closed->CloseProfitByTrade == doctest::Approx(30000.0));
    CHECK(closed->CloseProfitByDate == doctest::Approx(15000.0));

    auto* untouched = SelectSettlementPositionDetail(&settlementMdb, "20240303", "IF2503", PosiDirectionType::Long, "20240303", "T2");
    REQUIRE(untouched != nullptr);
    CHECK(untouched->CloseVolume == 0);
}

TEST_CASE("当日开仓平仓盈亏按开仓价")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240305", "1", DirectionType::Buy, OffsetFlagType::Open, 3000.0, 1));
    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240305", "2", DirectionType::Sell, OffsetFlagType::Close, 3100.0, 1));

    auto* detail = SelectSettlementPositionDetail(&settlementMdb, "20240305", "IF2503", PosiDirectionType::Long, "20240305", "1");
    REQUIRE(detail != nullptr);
    CHECK(detail->CloseVolume == 1);
    CHECK(detail->CloseProfitByTrade == doctest::Approx(30000.0));
    CHECK(detail->CloseProfitByDate == doctest::Approx(30000.0));
}

TEST_CASE("同日同开仓日期按TradeId先开先平")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    REQUIRE(InsertSettlementPosition(&settlementMdb, "20240306", PosiDirectionType::Long, 2, 3000.0));
    REQUIRE(InsertSettlementPositionDetail(&settlementMdb, "20240306", "20240306", "T1", PosiDirectionType::Long, 3000.0, 3000.0, 1));
    REQUIRE(InsertSettlementPositionDetail(&settlementMdb, "20240306", "20240306", "T2", PosiDirectionType::Long, 3000.0, 3000.0, 1));

    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240306", "3", DirectionType::Sell, OffsetFlagType::Close, 3100.0, 1));

    auto* first = SelectSettlementPositionDetail(&settlementMdb, "20240306", "IF2503", PosiDirectionType::Long, "20240306", "T1");
    REQUIRE(first != nullptr);
    CHECK(first->CloseVolume == 1);
    auto* second = SelectSettlementPositionDetail(&settlementMdb, "20240306", "IF2503", PosiDirectionType::Long, "20240306", "T2");
    REQUIRE(second != nullptr);
    CHECK(second->CloseVolume == 0);
}

TEST_CASE("超量平仓持仓扣为负且只配对现存明细")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    REQUIRE(InsertSettlementPosition(&settlementMdb, "20240307", PosiDirectionType::Long, 1, 3000.0));
    REQUIRE(InsertSettlementPositionDetail(&settlementMdb, "20240307", "20240307", "T1", PosiDirectionType::Long, 3000.0, 3000.0, 1));

    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240307", "2", DirectionType::Sell, OffsetFlagType::Close, 3100.0, 3));

    auto* position = SelectSettlementPosition(&settlementMdb, "20240307", "IF2503", PosiDirectionType::Long);
    REQUIRE(position != nullptr);
    CHECK(position->TotalPosition == -2);
    auto* detail = SelectSettlementPositionDetail(&settlementMdb, "20240307", "IF2503", PosiDirectionType::Long, "20240307", "T1");
    REQUIRE(detail != nullptr);
    CHECK(detail->CloseVolume == 1);
}

TEST_CASE("期权平仓按方向记现金收支")
{
    QuantTrading::Mdb settlementMdb(QuantTrading::simexchange::simexchangeTableList);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    PositionMaintenance maintenance(&settlementMdb);

    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240308", "1", DirectionType::Sell, OffsetFlagType::Open, 100.0, 1, ProductClassType::FutureOption));
    maintenance.UpdateOnTrade(MakeSettlementTrade(tradePool, "20240308", "2", DirectionType::Buy, OffsetFlagType::Close, 120.0, 1, ProductClassType::FutureOption));

    auto* detail = SelectSettlementPositionDetail(&settlementMdb, "20240308", "IF2503", PosiDirectionType::Short, "20240308", "1");
    REQUIRE(detail != nullptr);
    CHECK(detail->CloseVolume == 1);
    CHECK(detail->CashOut == doctest::Approx(36000.0));
    CHECK(detail->CashIn == doctest::Approx(0.0));
}

}
