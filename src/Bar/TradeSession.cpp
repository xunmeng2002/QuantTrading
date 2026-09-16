#include "TradeSession.h"
#include "BarUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Serialization/json/json.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace Spark::Core;

namespace QuantTrading::Bar
{
    const TradeSession* TradeSessions::GetTradeSessionForInstrument(const char* exchangeId, const char* instrumentId) const
    {
        // 交易所与品种共同决定交易节：先按品种精确匹配（同交易所不同节，如 IF/IC 与 cu/al），
        // 再按该交易所的 "*" 兜底（股票等代码无品种前缀）。Check 是字面量匹配，"*" 无通配语义，故两次查询不可合并
        const std::string productId = GetUnderlyingID(instrumentId);
        const TradeSession* tradeSession = GetTradeSession(exchangeId, productId.c_str());
        if (tradeSession == nullptr)
        {
            tradeSession = GetTradeSession(exchangeId, "*");
        }
        return tradeSession;
    }

    bool TradeSession::Check(const char* exchangeId, const char* productId) const
    {
        auto it = ExchangeProducts.find(exchangeId);
        if (it == ExchangeProducts.end())
            return false;
        auto& products = it->second;
        auto productIt = std::find(products.begin(), products.end(), productId);
        if (productIt == products.end())
            return false;
        return true;
    }
    long long TradeSession::GetFirstBarTime(int tradingDay) const
    {
        auto tradeSection = GetFirstTradeSection();
        if (tradeSection == nullptr)
        {
            return 0;
        }
        if (tradeSection->From > 1800)
        {
            char preTradingDay[16]{ 0 };
            TimeUtility::GetPreTradingDay(std::to_string(tradingDay).c_str(), preTradingDay);
            tradingDay = atoi(preTradingDay);
        }
        return tradingDay * 10000LL + tradeSection->From + 1;
    }
    const TradeSection* TradeSession::GetTradeSection(int time) const
    {
        if (time < 800)
        {
            time += 2400;
        }
        for (auto& section : TradeSections)
        {
            if (time >= section->From && time <= section->To)
            {
                return section.get();
            }
        }
        return nullptr;
    }
    const TradeSection* TradeSession::GetNextTradeSection(const TradeSection* preTradeSection) const
    {
        bool find = false;
        for (auto it = TradeSections.begin(); it != TradeSections.end(); ++it)
        {
            if (find)
            {
                if ((*it)->SectionClass == SectionClassType::Section)
                    return it->get();
            }
            else
            {
                find = it->get() == preTradeSection;
            }
        }
        return nullptr;
    }
    const TradeSection* TradeSession::GetFirstTradeSection() const
    {
        for (auto& section : TradeSections)
        {
            if (section->SectionClass == SectionClassType::Section)
            {
                return section.get();
            }
        }
        return nullptr;
    }
    void TradeSession::GetSectionBarTime(const TradeSection* tradeSection, int tradingDay, long long& beginBarTime, long long& endBarTime) const
    {
        int preTradingDay = 0;
        if ((tradeSection->From > 1800 && tradeSection->From < 2400) || (tradeSection->To > 1800 && tradeSection->To < 2400))
        {
            char date[16]{ 0 };
            TimeUtility::GetPreTradingDay(std::to_string(tradingDay).c_str(), date);
            preTradingDay = atoi(date);
        }
        if (tradeSection->From > 1800 && tradeSection->From < 2400)
        {
            beginBarTime = preTradingDay * 10000LL + tradeSection->From + 1;
        }
        else if (tradeSection->From >= 2400)
        {
            beginBarTime = tradingDay * 10000LL + tradeSection->From - 2400 + 1;
        }
        else
        {
            beginBarTime = tradingDay * 10000LL + tradeSection->From + 1;
        }
        if (tradeSection->To > 1800 && tradeSection->To < 2400)
        {
            endBarTime = preTradingDay * 10000LL + tradeSection->To + 1;
        }
        else if (tradeSection->To >= 2400)
        {
            endBarTime = tradingDay * 10000LL + tradeSection->To + 1 - 2400;
        }
        else
        {
            endBarTime = tradingDay * 10000LL + tradeSection->To + 1;
        }
    }
    std::string TradeSession::ToString() const
    {
        std::ostringstream sessionText;
        sessionText << "{Name:" << Name << ", Exchanges:[";
        for (auto& it : ExchangeProducts)
        {
            sessionText << "{ExchangeId:" << it.first << ", Products:[";
            for (auto& productId : it.second)
            {
                sessionText << productId << ", ";
            }
            sessionText << "]},";
        }
        sessionText << "], Sections:[";
        for (auto& tradeSection : TradeSections)
        {
            sessionText << "{From:" << tradeSection->From << ", To:" << tradeSection->To
                << ", SectionClass:" << static_cast<int>(tradeSection->SectionClass) << "}, ";
        }
        sessionText << "]}";
        return sessionText.str();
    }

    bool TradeSessions::RejectIfAlreadyLoaded(const char* sessionSource) const
    {
        if (!m_IsLoaded)
        {
            return false;
        }
        // 已装载后内容不再变化是他方缓存裸指针（BarAggregator/MinuteBar 按合约缓存 TradeSession*）的前提，重复装载会令其失效
        WriteLog(LogLevel::Error, "TradeSessions: Already loaded, refuse reload. SessionSource:%s", sessionSource);
        return true;
    }

    bool TradeSessions::LoadFromFile(const std::string& sessionFile)
    {
        if (RejectIfAlreadyLoaded(sessionFile.c_str()))
        {
            return false;
        }
        std::ifstream sessionFileStream(sessionFile.c_str());
        if (!sessionFileStream.is_open())
        {
            WriteLog(LogLevel::Error, "TradeSessions: Open session file failed. SessionFile:%s", sessionFile.c_str());
            return false;
        }
        const std::string sessionJsonString((std::istreambuf_iterator<char>(sessionFileStream)), std::istreambuf_iterator<char>());
        if (!ParseFromJsonString(sessionJsonString))
        {
            WriteLog(LogLevel::Error, "TradeSessions: Parse session file failed. SessionFile:%s", sessionFile.c_str());
            return false;
        }
        WriteLog(LogLevel::Info, "TradeSessions: Trade sessions loaded. SessionCount:%d, SessionFile:%s",
            static_cast<int>(m_TradeSessions.size()), sessionFile.c_str());
        return true;
    }
    bool TradeSessions::ParseFromJsonString(const std::string& sessionJsonString)
    {
        if (RejectIfAlreadyLoaded("JsonString"))
        {
            return false;
        }
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(sessionJsonString, root))
        {
            WriteLog(LogLevel::Error, "TradeSessions: Parse json string failed. JsonStr:%s", sessionJsonString.c_str());
            return false;
        }
        for (auto i = 0u; i < root.size(); ++i)
        {
            auto& tradeSessionValue = root[i];
            auto tradeSession = std::make_unique<TradeSession>();
            tradeSession->Name = tradeSessionValue["Name"].asString();
            for (auto j = 0u; j < tradeSessionValue["Exchanges"].size(); ++j)
            {
                auto& exchangesValue = tradeSessionValue["Exchanges"][j];
                auto exchangeId = exchangesValue["ExchangeId"].asString();
                tradeSession->ExchangeProducts.insert(std::make_pair(exchangeId, std::list<std::string>()));
                for (auto k = 0u; k < exchangesValue["Products"].size(); ++k)
                {
                    auto& productValue = exchangesValue["Products"][k];
                    tradeSession->ExchangeProducts[exchangeId].push_back(productValue.asString());
                }
            }
            for (auto j = 0u; j < tradeSessionValue["Sections"].size(); ++j)
            {
                auto& tradeSectionValue = tradeSessionValue["Sections"][j];
                auto tradeSection = std::make_unique<TradeSection>();
                tradeSection->From = tradeSectionValue["From"].asInt();
                tradeSection->To = tradeSectionValue["To"].asInt();
                tradeSection->SectionClass = static_cast<SectionClassType>(tradeSectionValue["SectionClass"].asInt());

                if (tradeSection->From < 800)
                {
                    tradeSection->From += 2400;
                }
                if (tradeSection->To < 800)
                {
                    tradeSection->To += 2400;
                }
                tradeSession->TradeSections.push_back(std::move(tradeSection));
            }

            m_TradeSessions.push_back(std::move(tradeSession));
        }

        for (auto& tradeSession : m_TradeSessions)
        {
            WriteLog(LogLevel::Info, "TradeSessions: TradeSession:%s", tradeSession->ToString().c_str());
        }
        m_IsLoaded = true;
        return true;
    }
    const TradeSession* TradeSessions::GetTradeSession(const char* exchangeId, const char* productId) const
    {
        for (auto& tradeSession : m_TradeSessions)
        {
            if (tradeSession->Check(exchangeId, productId))
            {
                return tradeSession.get();
            }
        }
        return nullptr;
    }
}
