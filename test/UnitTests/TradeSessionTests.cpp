#include "TestHelpers.h"
#include "TradeSession.h"

#include "doctest/doctest.h"
#include <Spark/Core/Utility/TimeUtility.h>

#include <memory>
#include <vector>

using namespace quanttrading::bar;
using namespace quanttrading::unittest;

TEST_SUITE("TradeSession")
{

namespace
{
// 造一节并登记到 trade_session（所有权归该 TradeSession）；返回裸指针供用例做身份断言（"同一时段"须是同一个对象）
TradeSection* AddTradeSection(TradeSession& trade_session, int from, int to, SectionClassType section_class)
{
    auto trade_section = std::make_unique<TradeSection>();
    trade_section->From = from;
    trade_section->To = to;
    trade_section->SectionClass = section_class;
    TradeSection* trade_section_pointer = trade_section.get();
    trade_session.TradeSections.push_back(std::move(trade_section));
    return trade_section_pointer;
}
}

TEST_CASE("无交易时段时GetFirstBarTime返回0(H19回归)")
{
    TradeSession trade_session;
    CHECK(trade_session.GetFirstTradeSection() == nullptr);
    CHECK(trade_session.GetFirstBarTime(20240301) == 0);
}

TEST_CASE("仅集合竞价时段时GetFirstBarTime返回0(H19回归)")
{
    TradeSession trade_session;
    AddTradeSection(trade_session, 850, 900, SectionClassType::Auction);

    CHECK(trade_session.GetFirstTradeSection() == nullptr);
    CHECK(trade_session.GetFirstBarTime(20240301) == 0);
}

TEST_CASE("日盘首根bar时间与时段起止bar时间")
{
    TradeSession trade_session;
    auto* morning = AddTradeSection(trade_session, 900, 1015, SectionClassType::Section);
    AddTradeSection(trade_session, 1330, 1500, SectionClassType::Section);

    CHECK(trade_session.GetFirstTradeSection() == morning);
    CHECK(trade_session.GetFirstBarTime(20240301) == 202403010901LL);

    long long begin_bar_time = 0;
    long long end_bar_time = 0;
    trade_session.GetSectionBarTime(morning, 20240301, begin_bar_time, end_bar_time);
    CHECK(begin_bar_time == 202403010901LL);
    CHECK(end_bar_time == 202403011016LL);
}

TEST_CASE("夜盘与跨零点时段的bar时间换算")
{
    TradeSession trade_session;
    auto* night = AddTradeSection(trade_session, 2100, 2300, SectionClassType::Section);
    auto* overnight = AddTradeSection(trade_session, 2400, 2700, SectionClassType::Section);

    auto pre_trading_day = spark::core::TimeUtility::GetPreTradingDay(20240301);
    CHECK(trade_session.GetFirstBarTime(20240301) == pre_trading_day * 10000LL + 2101);

    long long begin_bar_time = 0;
    long long end_bar_time = 0;
    trade_session.GetSectionBarTime(night, 20240301, begin_bar_time, end_bar_time);
    CHECK(begin_bar_time == pre_trading_day * 10000LL + 2101);
    CHECK(end_bar_time == pre_trading_day * 10000LL + 2301);

    trade_session.GetSectionBarTime(overnight, 20240301, begin_bar_time, end_bar_time);
    CHECK(begin_bar_time == 202403010001LL);
    CHECK(end_bar_time == 202403010301LL);
}

TEST_CASE("时段定位与早于800时间的跨零点归属")
{
    TradeSession trade_session;
    auto* morning = AddTradeSection(trade_session, 900, 1015, SectionClassType::Section);
    auto* afternoon = AddTradeSection(trade_session, 1330, 1500, SectionClassType::Section);
    auto* overnight = AddTradeSection(trade_session, 2400, 2700, SectionClassType::Section);

    CHECK(trade_session.GetTradeSection(900) == morning);
    CHECK(trade_session.GetTradeSection(1015) == morning);
    CHECK(trade_session.GetTradeSection(899) == nullptr);
    CHECK(trade_session.GetTradeSection(1016) == nullptr);
    CHECK(trade_session.GetTradeSection(1435) == afternoon);
    CHECK(trade_session.GetTradeSection(130) == overnight);
    CHECK(trade_session.GetTradeSection(500) == nullptr);
}

TEST_CASE("下一时段跳过集合竞价节")
{
    TradeSession trade_session;
    AddTradeSection(trade_session, 850, 900, SectionClassType::Auction);
    auto* morning = AddTradeSection(trade_session, 900, 1015, SectionClassType::Section);
    AddTradeSection(trade_session, 1020, 1030, SectionClassType::Auction);
    auto* afternoon = AddTradeSection(trade_session, 1030, 1130, SectionClassType::Section);

    CHECK(trade_session.GetFirstTradeSection() == morning);
    CHECK(trade_session.GetNextTradeSection(morning) == afternoon);
    CHECK(trade_session.GetNextTradeSection(afternoon) == nullptr);
}

TEST_CASE("ParseFromJsonString解析与跨零点时段归一化")
{
    const char* session_json = R"([
        {"Name":"TestSession",
         "Exchanges":[{"ExchangeID":"TEST","Products":["cu","*"]}],
         "Sections":[{"From":850,"To":900,"SectionClass":0},
                     {"From":900,"To":1015,"SectionClass":1},
                     {"From":0,"To":230,"SectionClass":1}]}
    ])";
    TradeSessions trade_sessions;
    REQUIRE(LoadTradeSessionJson(trade_sessions, session_json));

    const auto* trade_session = trade_sessions.GetTradeSession("TEST", "cu");
    REQUIRE(trade_session != nullptr);
    CHECK(trade_session->Check("TEST", "cu"));
    CHECK(trade_session->Check("TEST", "*"));
    CHECK_FALSE(trade_session->Check("CZCE", "cu"));
    CHECK(trade_sessions.GetTradeSession("TEST", "*") == trade_session);
    CHECK(trade_sessions.GetTradeSession("CZCE", "cu") == nullptr);

    REQUIRE(trade_session->TradeSections.size() == 3);
    CHECK(trade_session->TradeSections[0]->From == 850);
    CHECK(trade_session->TradeSections[0]->SectionClass == SectionClassType::Auction);
    CHECK(trade_session->TradeSections[1]->SectionClass == SectionClassType::Section);
    CHECK(trade_session->TradeSections[2]->From == 2400);
    CHECK(trade_session->TradeSections[2]->To == 2630);
}

TEST_CASE("TradeSessions拒绝重复装载")
{
    // 装载后内容不再变化是聚合器缓存 TradeSession* 的前提，重复装载必须被拒（否则缓存裸指针悬空）
    const char* session_json = R"([
        {"Name":"TestSession",
         "Exchanges":[{"ExchangeID":"TEST","Products":["cu"]}],
         "Sections":[{"From":900,"To":1015,"SectionClass":1}]}
    ])";
    TradeSessions trade_sessions;
    REQUIRE(LoadTradeSessionJson(trade_sessions, session_json));
    CHECK_FALSE(LoadTradeSessionJson(trade_sessions, session_json));
    CHECK(trade_sessions.GetTradeSession("TEST", "cu") != nullptr);
}
}
