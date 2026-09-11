#include "TradeSession.h"
#include "BarUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Serialization/json/json.h>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;
using namespace spark::core;

namespace quanttrading::bar
{
    TradeSession* TradeSessions::GetTradeSessionForInstrument(const char* exchangeID, const char* instrumentID)
    {
        // 交易所与品种共同决定交易节：先按品种精确匹配（同交易所不同节，如 IF/IC 与 cu/al），
        // 再按该交易所的 "*" 兜底（股票等代码无品种前缀）。Check 是字面量匹配，"*" 无通配语义，故两次查询不可合并
        const std::string productID = GetUnderlyingID(instrumentID);
        TradeSession* tradeSession = GetTradeSession(exchangeID, productID.c_str());
        if (tradeSession == nullptr)
        {
            tradeSession = GetTradeSession(exchangeID, "*");
        }
        return tradeSession;
    }

    bool TradeSession::Check(const char* exchangeID, const char* productID)
    {
        auto it = ExchangeProducts.find(exchangeID);
        if (it == ExchangeProducts.end())
            return false;
        auto& products = it->second;
        auto productIt = std::find(products.begin(), products.end(), productID);
        if (productIt == products.end())
            return false;
        return true;
    }
    long long TradeSession::GetFirstBarTime(int tradingDay)
    {
        auto tradeSection = GetFirstTradeSection();
        if (tradeSection == nullptr)
        {
            return 0;
        }
        if (tradeSection->From > 1800)
        {
            char preTradingDay[16]{ 0 };
            TimeUtility::GetPreTradingDay(to_string(tradingDay).c_str(), preTradingDay);
            tradingDay = atoi(preTradingDay);
        }
        return tradingDay * 10000LL + tradeSection->From + 1;
    }
    TradeSection* TradeSession::GetTradeSection(int time)
    {
        if (time < 800)
        {
            time += 2400;
        }
        for (auto section : TradeSections)
        {
            if (time >= section->From && time <= section->To)
            {
                return section;
            }
        }
        return nullptr;
    }
    TradeSection* TradeSession::GetNextTradeSection(TradeSection* preTradeSection)
    {
        bool find = false;
        for (auto it = TradeSections.begin(); it != TradeSections.end(); ++it)
        {
            if (find)
            {
                if ((*it)->SectionClass == SectionClassType::Section)
                    return *it;
            }
            else
            {
                find = *it == preTradeSection;
            }
        }
        return nullptr;
    }
    TradeSection* TradeSession::GetFirstTradeSection()
    {
        for (auto section : TradeSections)
        {
            if (section->SectionClass == SectionClassType::Section)
            {
                return section;
            }
        }
        return nullptr;
    }
    void TradeSession::GetSectionBarTime(TradeSection* tradeSection, int tradingDay, long long& beginBarTime, long long& endBarTime)
    {
        int preTradingDay = 0;
        if ((tradeSection->From > 1800 && tradeSection->From < 2400) || (tradeSection->To > 1800 && tradeSection->To < 2400))
        {
            char date[16]{ 0 };
            TimeUtility::GetPreTradingDay(to_string(tradingDay).c_str(), date);
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
    const char* TradeSession::ToString() const
    {
        static char buff[1024];
        int index = 0;
        memset(buff, 0, 1024);
        index += sprintf(buff + index, "{Name:%s, Exchanges:[", Name.c_str());
        for (auto& it : ExchangeProducts)
        {
            index += sprintf(buff + index, "{ExchangeID:%s, Products:[", it.first.c_str());
            for (auto& productID : it.second)
            {
                index += sprintf(buff + index, "%s, ", productID.c_str());
            }
            index += sprintf(buff + index, "]},");
        }
        index += sprintf(buff + index, "], Sections:[");
        for (auto tradeSection : TradeSections)
        {
            index += sprintf(buff + index, "{From:%d, To:%d, SectionClass:%d}, ", tradeSection->From, tradeSection->To, (int)(tradeSection->SectionClass));
        }
        index += sprintf(buff + index, "]}");
        return buff;
    }

    bool TradeSessions::m_Inited = false;
    std::string TradeSessions::m_SessionJsonString;
    std::vector<TradeSession*> TradeSessions::m_TradeSessions;
    bool TradeSessions::LoadFromFile(const std::string& sessionFile)
    {
        if (m_Inited)
        {
            return true;
        }
        std::ifstream sessionFileStream(sessionFile.c_str());
        if (!sessionFileStream.is_open())
        {
            WriteLog(LogLevel::Error, "TradeSessions: Open session file failed. SessionFile:%s", sessionFile.c_str());
            return false;
        }
        m_SessionJsonString = std::string((std::istreambuf_iterator<char>(sessionFileStream)), std::istreambuf_iterator<char>());
        if (!ParseTradeSessions())
        {
            WriteLog(LogLevel::Error, "TradeSessions: Parse session file failed. SessionFile:%s", sessionFile.c_str());
            return false;
        }
        WriteLog(LogLevel::Info, "TradeSessions: Trade sessions loaded. SessionCount:%d, SessionFile:%s",
            static_cast<int>(m_TradeSessions.size()), sessionFile.c_str());
        return true;
    }
    bool TradeSessions::ParseTradeSessions()
    {
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(m_SessionJsonString, root))
        {
            printf("ParseTradeSessions Failed. JsonStr:%s\n", m_SessionJsonString.c_str());
            return false;
        }
        for (auto i = 0u; i < root.size(); ++i)
        {
            auto& tradeSessionValue = root[i];
            TradeSession* tradeSession = new TradeSession();
            tradeSession->Name = tradeSessionValue["Name"].asString();
            for (auto j = 0u; j < tradeSessionValue["Exchanges"].size(); ++j)
            {
                auto& exchangesValue = tradeSessionValue["Exchanges"][j];
                auto exchangeID = exchangesValue["ExchangeID"].asString();
                tradeSession->ExchangeProducts.insert(make_pair(exchangeID, list<string>()));
                for (auto k = 0u; k < exchangesValue["Products"].size(); ++k)
                {
                    auto& productValue = exchangesValue["Products"][k];
                    tradeSession->ExchangeProducts[exchangeID].push_back(productValue.asString());
                }
            }
            for (auto j = 0u; j < tradeSessionValue["Sections"].size(); ++j)
            {
                auto& tradeSectionValue = tradeSessionValue["Sections"][j];
                TradeSection* tradeSection = new TradeSection();
                tradeSection->From = tradeSectionValue["From"].asInt();
                tradeSection->To = tradeSectionValue["To"].asInt();
                tradeSection->SectionClass = (SectionClassType)tradeSectionValue["SectionClass"].asInt();

                if (tradeSection->From < 800)
                {
                    tradeSection->From += 2400;
                }
                if (tradeSection->To < 800)
                {
                    tradeSection->To += 2400;
                }
                tradeSession->TradeSections.push_back(tradeSection);
            }

            m_TradeSessions.push_back(tradeSession);
        }

        for (auto tradeSession : m_TradeSessions)
        {
            printf("TradeSession:%s\n", tradeSession->ToString());
        }
        m_Inited = true;
        return true;
    }
    TradeSession* TradeSessions::GetTradeSession(const char* exchangeID, const char* productID)
    {
        for (auto tradeSession : m_TradeSessions)
        {
            if (tradeSession->Check(exchangeID, productID))
            {
                return tradeSession;
            }
        }
        return nullptr;
    }
}
