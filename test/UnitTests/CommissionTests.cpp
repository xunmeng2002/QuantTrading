#include "BackTestTableList.h"
#include "Mdb.h"
#include "doctest/doctest.h"
#include "CommissionTestHelpers.h"

#include <algorithm>
#include <cstring>
#include <string>

using namespace QuantTrading::UnitTest;


TEST_SUITE("Commission")
{
using QuantTrading::Settlement::CommissionCalculator;

constexpr const char* TestTradingDay = "20240310";
constexpr const char* TestAccountId = "test";
constexpr const char* TestExchangeId = "SSE";
constexpr const char* TestInstrumentId = "600000";
constexpr GroupIdType TestCommissionGroupId = 1;

TEST_CASE("开仓按金额费率计佣金且不动印花税过户费")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* rate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Buy);
    REQUIRE(rate != nullptr);
    rate->OpenByMoney = 0.00025;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* trade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(trade);

    // 10.0 × 1000 × 1 = 10000 的成交金额，按 0.00025 收 2.5
    CHECK(trade->Commission == doctest::Approx(2.5));
    CHECK(trade->StampTax == doctest::Approx(0.0));
    CHECK(trade->TransferFee == doctest::Approx(0.0));
}

TEST_CASE("金额侧与手数侧费率相加而非相乘")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* rate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Buy);
    REQUIRE(rate != nullptr);
    rate->OpenByVolume = 1.5;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* trade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(trade);

    // 金额侧为 0，手数侧 1.5 × 1000 手 = 1500；若两列相乘则会得到 0
    CHECK(trade->Commission == doctest::Approx(1500.0));
}

TEST_CASE("MinCommission按每笔成交封底")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* rate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Buy);
    REQUIRE(rate != nullptr);
    rate->MinCommission = 5.0;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* firstTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    auto* secondTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T2",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(firstTrade);
    calculator.Apply(secondTrade);

    // 费率算出来是 0，两笔各自被封底，故共收 10 而非 5
    CHECK(firstTrade->Commission == doctest::Approx(5.0));
    CHECK(secondTrade->Commission == doctest::Approx(5.0));
}

TEST_CASE("MaxCommission非正值视为不封顶")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* rate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Buy);
    REQUIRE(rate != nullptr);
    rate->OpenByMoney = 0.01;
    rate->MaxCommission = -1.0;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* trade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(trade);

    CHECK(trade->Commission == doctest::Approx(100.0));
}

TEST_CASE("封底只作用佣金不封印花税过户费")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* rate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Sell);
    REQUIRE(rate != nullptr);
    rate->CloseByMoney = 0.00025;
    rate->CloseByVolume = 0.01;
    rate->CloseStampTaxByMoney = 0.0005;
    rate->CloseTransferFeeByMoney = 0.00001;
    rate->MinCommission = 20.0;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* trade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Sell, OffsetFlagType::Close, 10.0, 1000);
    calculator.Apply(trade);

    // 佣金 2.5 + 10 = 12.5 被封底到 20；印花税 5、过户费 0.1 按费率实收，不受封底影响
    CHECK(trade->Commission == doctest::Approx(20.0));
    CHECK(trade->StampTax == doctest::Approx(5.0));
    CHECK(trade->TransferFee == doctest::Approx(0.1));
}

TEST_CASE("平仓费用按成交量分摊且分项之和逐位等于成交")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    QuantTrading::Settlement::PositionMaintenance positionMaintenance(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    for (int index = 0; index < 3; ++index)
    {
        auto* openTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId,
            ("T" + std::to_string(index + 1)).c_str(), DirectionType::Buy, OffsetFlagType::Open, 10.0, 1);
        positionMaintenance.UpdateOnTrade(openTrade);
    }
    auto* closeTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "C1",
        DirectionType::Sell, OffsetFlagType::Close, 11.0, 3);
    closeTrade->Commission = 17.6;
    closeTrade->StampTax = 5.0;
    closeTrade->TransferFee = 0.1;
    positionMaintenance.UpdateOnTrade(closeTrade);

    auto positionDetails = CollectCommissionPositionDetails(&commissionMdb, TestTradingDay, TestAccountId, TestExchangeId,
        TestInstrumentId, PosiDirectionType::Long);
    REQUIRE(positionDetails.size() == 3);
    std::sort(positionDetails.begin(), positionDetails.end(), [](const QuantTrading::PositionDetail* left, const QuantTrading::PositionDetail* right)
        { return std::strcmp(left->TradeId, right->TradeId) < 0; });

    // 前两条按 1/3 分摊，末条取余额；若把整笔费用全压给首条，这两条断言立刻失败
    CHECK(positionDetails[0]->Commission == doctest::Approx(closeTrade->Commission / 3.0));
    CHECK(positionDetails[1]->Commission == doctest::Approx(closeTrade->Commission / 3.0));
    CHECK(positionDetails[0]->StampTax == doctest::Approx(closeTrade->StampTax / 3.0));

    // 三项各自之和必须与成交逐位相等，不留浮点残差
    CHECK(positionDetails[0]->Commission + positionDetails[1]->Commission + positionDetails[2]->Commission == closeTrade->Commission);
    CHECK(positionDetails[0]->StampTax + positionDetails[1]->StampTax + positionDetails[2]->StampTax == closeTrade->StampTax);
    CHECK(positionDetails[0]->TransferFee + positionDetails[1]->TransferFee + positionDetails[2]->TransferFee == closeTrade->TransferFee);
}

TEST_CASE("持仓不足时余额落最后一条已配对明细")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    QuantTrading::Settlement::PositionMaintenance positionMaintenance(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    for (int index = 0; index < 3; ++index)
    {
        auto* openTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId,
            ("T" + std::to_string(index + 1)).c_str(), DirectionType::Buy, OffsetFlagType::Open, 10.0, 1);
        positionMaintenance.UpdateOnTrade(openTrade);
    }
    auto* closeTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "C1",
        DirectionType::Sell, OffsetFlagType::Close, 11.0, 5);
    closeTrade->Commission = 17.6;
    closeTrade->StampTax = 5.0;
    closeTrade->TransferFee = 0.1;
    positionMaintenance.UpdateOnTrade(closeTrade);

    auto positionDetails = CollectCommissionPositionDetails(&commissionMdb, TestTradingDay, TestAccountId, TestExchangeId,
        TestInstrumentId, PosiDirectionType::Long);
    REQUIRE(positionDetails.size() == 3);
    std::sort(positionDetails.begin(), positionDetails.end(), [](const QuantTrading::PositionDetail* left, const QuantTrading::PositionDetail* right)
        { return std::strcmp(left->TradeId, right->TradeId) < 0; });

    // 三条明细只吃下 3 手，成交 5 手的费用按 1/5 分摊后余 2/5 由末条兜底：
    // 缺了这条兜底，分项之和只有 3/5，下面三条等式全部失败
    CHECK(positionDetails[0]->Commission == doctest::Approx(closeTrade->Commission / 5.0));
    CHECK(positionDetails[1]->Commission == doctest::Approx(closeTrade->Commission / 5.0));
    CHECK(positionDetails[2]->Commission > closeTrade->Commission / 5.0);
    CHECK(positionDetails[0]->Commission + positionDetails[1]->Commission + positionDetails[2]->Commission == closeTrade->Commission);
}

TEST_CASE("费率行缺失按零计费并按去重键计数")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* firstTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    auto* secondTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T2",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(firstTrade);
    calculator.Apply(secondTrade);

    CHECK(firstTrade->Commission == doctest::Approx(0.0));
    CHECK(firstTrade->StampTax == doctest::Approx(0.0));
    CHECK(firstTrade->TransferFee == doctest::Approx(0.0));
    // 两笔成交计 2，去重键只计 1，缺口清单里也只出现一条
    CHECK(calculator.GetMissingRateCount() == 2);
    CHECK(calculator.GetZeroRateKeyCount() == 1);
    REQUIRE(calculator.GetMissingRateKeys().size() == 1);
    CHECK(calculator.GetMissingRateKeys()[0] == "1|SSE|600000|0");
}

TEST_CASE("买卖方向参与取费率行")
{
    QuantTrading::Mdb commissionMdb(CommissionTableList);
    REQUIRE(InsertCommissionAccount(&commissionMdb, TestAccountId, TestCommissionGroupId) != nullptr);
    auto* buyRate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Buy);
    REQUIRE(buyRate != nullptr);
    buyRate->OpenByMoney = 0.00025;
    auto* sellRate = InsertBaseCommission(&commissionMdb, TestCommissionGroupId, TestExchangeId, TestInstrumentId, DirectionType::Sell);
    REQUIRE(sellRate != nullptr);
    sellRate->OpenByMoney = 0.001;

    CommissionCalculator calculator(&commissionMdb);
    PoolRecordGuard<QuantTrading::Trade> tradePool;
    auto* buyTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T1",
        DirectionType::Buy, OffsetFlagType::Open, 10.0, 1000);
    auto* sellTrade = MakeCommissionTrade(tradePool, TestTradingDay, TestAccountId, TestExchangeId, TestInstrumentId, "T2",
        DirectionType::Sell, OffsetFlagType::Open, 10.0, 1000);
    calculator.Apply(buyTrade);
    calculator.Apply(sellTrade);

    CHECK(buyTrade->Commission == doctest::Approx(2.5));
    CHECK(sellTrade->Commission == doctest::Approx(10.0));
    CHECK(calculator.GetMissingRateCount() == 0);
}

TEST_CASE("回测表清单已注册费率两张表")
{
    // 费率表不在回测清单里，mdb.BaseCommission 就是 nullptr，计费整条链路静默不生效。
    // 这条断言是"改了 BackTestTableNames.xml 却忘了重跑 pumpall.py"的唯一自动防线
    bool hasCommissionGroup = false;
    bool hasBaseCommission = false;
    for (int index = 0; index < QuantTrading::BackTest::BackTestTableList.Count; ++index)
    {
        const auto tableId = QuantTrading::BackTest::BackTestTableList.TableIds[index];
        hasCommissionGroup = hasCommissionGroup || tableId == QuantTrading::CommissionGroup::TableId;
        hasBaseCommission = hasBaseCommission || tableId == QuantTrading::BaseCommission::TableId;
    }
    CHECK(hasCommissionGroup);
    CHECK(hasBaseCommission);
}

}
