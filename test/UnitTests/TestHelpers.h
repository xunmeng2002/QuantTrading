#pragma once
#include "TradeSession.h"
#include <cstdio>
#include <string>
#include <vector>

namespace quanttrading::unittest
{
    // 将字符串拷入固定长度字符数组（截断安全）
    template <std::size_t DestSize>
    void CopyString(char (&dest)[DestSize], const char* source)
    {
        std::snprintf(dest, DestSize, "%s", source);
    }

    // 由日期与时分秒（如 143000）、毫秒构造行情 UpdateTs（YYYYMMDDHHMMSSmmm）
    inline long long MakeUpdateTs(int tradingDay, int hhmmss, int milliSecond)
    {
        return static_cast<long long>(tradingDay) * 1000000000LL + static_cast<long long>(hhmmss) * 1000 + milliSecond;
    }

    // 用 JSON 字符串装载交易时段（ParseTradeSessions 的入参为静态成员，绕开文件读取）
    inline bool LoadTradeSessionJson(const char* sessionJson)
    {
        quanttrading::bar::TradeSessions::m_SessionJsonString = sessionJson;
        return quanttrading::bar::TradeSessions::ParseTradeSessions();
    }

    // 清理 ParseTradeSessions 在静态区遗留的对象（库侧只 new 不 delete，测试须自行配平）
    inline void ResetTradeSessions()
    {
        for (auto* tradeSession : quanttrading::bar::TradeSessions::m_TradeSessions)
        {
            for (auto* tradeSection : tradeSession->TradeSections)
            {
                delete tradeSection;
            }
            delete tradeSession;
        }
        quanttrading::bar::TradeSessions::m_TradeSessions.clear();
        quanttrading::bar::TradeSessions::m_Inited = false;
        quanttrading::bar::TradeSessions::m_SessionJsonString.clear();
    }
}
