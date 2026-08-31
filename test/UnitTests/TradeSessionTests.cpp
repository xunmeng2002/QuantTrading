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
// 拥有 TradeSection 生命周期；TradeSession 按库设计只持裸指针
class SectionOwner
{
public:
    TradeSection* Add(int from, int to, SectionClassType section_class)
    {
        auto trade_section = std::make_unique<TradeSection>();
        trade_section->From = from;
        trade_section->To = to;
        trade_section->SectionClass = section_class;
        sections_.push_back(std::move(trade_section));
        return sections_.back().get();
    }

private:
    std::vector<std::unique_ptr<TradeSection>> sections_;
};
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
    SectionOwner section_owner;
    trade_session.TradeSections.push_back(section_owner.Add(850, 900, SectionClassType::Auction));

    CHECK(trade_session.GetFirstTradeSection() == nullptr);
    CHECK(trade_session.GetFirstBarTime(20240301) == 0);
}

TEST_CASE("日盘首根bar时间与时段起止bar时间")
{
    TradeSession trade_session;
    SectionOwner section_owner;
    auto* morning = section_owner.Add(900, 1015, SectionClassType::Section);
    trade_session.TradeSections.push_back(morning);
    trade_session.TradeSections.push_back(section_owner.Add(1330, 1500, SectionClassType::Section));

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
    SectionOwner section_owner;
    auto* night = section_owner.Add(2100, 2300, SectionClassType::Section);
    auto* overnight = section_owner.Add(2400, 2700, SectionClassType::Section);
    trade_session.TradeSections.push_back(night);
    trade_session.TradeSections.push_back(overnight);

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
    SectionOwner section_owner;
    auto* morning = section_owner.Add(900, 1015, SectionClassType::Section);
    auto* afternoon = section_owner.Add(1330, 1500, SectionClassType::Section);
    auto* overnight = section_owner.Add(2400, 2700, SectionClassType::Section);
    trade_session.TradeSections.push_back(morning);
    trade_session.TradeSections.push_back(afternoon);
    trade_session.TradeSections.push_back(overnight);

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
    SectionOwner section_owner;
    trade_session.TradeSections.push_back(section_owner.Add(850, 900, SectionClassType::Auction));
    auto* morning = section_owner.Add(900, 1015, SectionClassType::Section);
    trade_session.TradeSections.push_back(morning);
    trade_session.TradeSections.push_back(section_owner.Add(1020, 1030, SectionClassType::Auction));
    auto* afternoon = section_owner.Add(1030, 1130, SectionClassType::Section);
    trade_session.TradeSections.push_back(afternoon);

    CHECK(trade_session.GetFirstTradeSection() == morning);
    CHECK(trade_session.GetNextTradeSection(morning) == afternoon);
    CHECK(trade_session.GetNextTradeSection(afternoon) == nullptr);
}

TEST_CASE("ParseTradeSessions解析与跨零点时段归一化")
{
    ResetTradeSessions();
    const char* session_json = R"([
        {"Name":"TestSession",
         "Exchanges":[{"ExchangeID":"TEST","Products":["cu","*"]}],
         "Sections":[{"From":850,"To":900,"SectionClass":0},
                     {"From":900,"To":1015,"SectionClass":1},
                     {"From":0,"To":230,"SectionClass":1}]}
    ])";
    REQUIRE(LoadTradeSessionJson(session_json));
    REQUIRE(TradeSessions::m_TradeSessions.size() == 1);

    auto* trade_session = TradeSessions::m_TradeSessions.front();
    CHECK(trade_session->Check("TEST", "cu"));
    CHECK(trade_session->Check("TEST", "*"));
    CHECK_FALSE(trade_session->Check("CZCE", "cu"));
    CHECK(TradeSessions::GetTradeSession("TEST", "cu") == trade_session);

    REQUIRE(trade_session->TradeSections.size() == 3);
    CHECK(trade_session->TradeSections[0]->From == 850);
    CHECK(trade_session->TradeSections[0]->SectionClass == SectionClassType::Auction);
    CHECK(trade_session->TradeSections[1]->SectionClass == SectionClassType::Section);
    CHECK(trade_session->TradeSections[2]->From == 2400);
    CHECK(trade_session->TradeSections[2]->To == 2630);

    ResetTradeSessions();
}
}
