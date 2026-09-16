#include "MdReader.h"

#include "QuantUtility.h"

#include <Spark/Core/Logger/Logger.h>
#include <chrono>
#include <cstdarg>
#include <cstring>
#include <stdexcept>
#include <string>

using namespace QuantTrading;
using namespace std;
using namespace std::chrono;
using namespace Spark::Core;
using namespace DbAdapters;

namespace
{
    std::string FormatSql(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
        va_list argsCopy;
        va_copy(argsCopy, args);
        int length = vsnprintf(nullptr, 0, format, argsCopy);
        va_end(argsCopy);
        std::string result;
        if (length > 0)
        {
            result.resize(static_cast<std::size_t>(length) + 1);
            vsnprintf(result.data(), result.size(), format, args);
            result.resize(static_cast<std::size_t>(length));
        }
        va_end(args);
        return result;
    }

    void ThrowIfQueryFailed(const std::string& error)
    {
        if (!error.empty())
        {
            std::string errorMessage = "duckdb_query Error. ErrorMsg:" + error;
            WriteLog(LogLevel::Error, "%s", errorMessage.c_str());
            throw std::logic_error(errorMessage);
        }
    }

    // 三种查询共用的记录工厂：对象池分配 + 清零 + 压入调用方 std::list<T*>。
    // 复用 mdb 结构的 GetSchema()，仅需补齐分配/追加回调。
    template <typename T>
    RecordFactory MakeVectorizedRecordFactory()
    {
        return {
            []() -> void* {
                T* record = T::Allocate();
                memset(record, 0, sizeof(T));
                return record;
            },
            [](void* records, void* record) {
                static_cast<std::list<T*>*>(records)->push_back(static_cast<T*>(record));
            },
        };
    }
}

namespace QuantTrading::BackTest
{
MdReader::MdReader(const Config& config)
    : mdDataPath_(config.MdDataPath)
    , barPreces_(config.BarPreces)
{
    strcpy(startTradingDay_, config.StartTradingDay.c_str());
    strcpy(endTradingDay_, config.EndTradingDay.c_str());
    if (!QuantTrading::ParseBarPreces(barPreces_, barPrecesType_, barPeriod_))
    {
        const std::string errorMsg = "Invalid BarPreces, expect <n><s|m|h|d> e.g. 1m/5m/1h/1d. BarPreces:" + barPreces_;
        WriteLog(LogLevel::Error, "%s", errorMsg.c_str());
        throw std::logic_error(errorMsg);
    }
}
MdReader::~MdReader()
{
}

bool MdReader::Init()
{
    duckdbWrapper_ = std::make_unique<DuckdbWrapper>(":memory:");
    if (!duckdbWrapper_->Connect())
    {
        WriteLog(LogLevel::Error, "duckdb_open Error.");
        return false;
    }
    return true;
}

void MdReader::ReadMdInstrument(std::list<QuantTrading::Instrument*>& instruments)
{
    auto startQueryTime = chrono::high_resolution_clock::now();
    std::string sql = GetInstrumentSqlString();
    WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", sql.c_str());

    ThrowIfQueryFailed(duckdbWrapper_->SelectWithSqlVectorized(
        sql.c_str(), &Instrument::GetSchema(), &instruments, MakeVectorizedRecordFactory<Instrument>()));

    auto endQueryTime = chrono::high_resolution_clock::now();
    auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
    WriteLog(LogLevel::Info, "ReadMdInstrument QueryTimeCost:%lld ms, RecordCount:%lld", t1.count(), instruments.size());
}

void MdReader::ReadMdTick(std::list<QuantTrading::MdSubscribe*>& mdSubscribes, std::list<QuantTrading::DepthMarketData*>& mdTicks)
{
    auto startQueryTime = chrono::high_resolution_clock::now();
    for (auto mdSubscribe : mdSubscribes)
    {
        ReadMdTickForOneSub(mdSubscribe, mdTicks);
    }
    auto endQueryTime = chrono::high_resolution_clock::now();
    mdTicks.sort([](QuantTrading::DepthMarketData* left, QuantTrading::DepthMarketData* right) {return left->UpdateTs < right->UpdateTs; });
    auto endSortTime = chrono::high_resolution_clock::now();
    auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
    auto t2 = chrono::duration_cast<milliseconds>(endSortTime - endQueryTime);
    WriteLog(LogLevel::Info, "ReadMdTick QueryTimeCost:%lld ms, SortTimeCost:%lld ms, RecordCount:%lld", t1.count(), t2.count(), mdTicks.size());
}

void MdReader::ReadMdBar(std::list<QuantTrading::MdSubscribe*>& mdSubscribes, std::list<QuantTrading::BarMarketData*>& mdBars)
{
    auto startQueryTime = chrono::high_resolution_clock::now();
    for (auto mdSubscribe : mdSubscribes)
    {
        ReadMdBarForOneSub(mdSubscribe, mdBars);
    }
    auto endQueryTime = chrono::high_resolution_clock::now();
    mdBars.sort([](QuantTrading::BarMarketData* left, QuantTrading::BarMarketData* right) {return left->UpdateTs < right->UpdateTs; });
    auto endSortTime = chrono::high_resolution_clock::now();
    auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
    auto t2 = chrono::duration_cast<milliseconds>(endSortTime - endQueryTime);
    WriteLog(LogLevel::Info, "ReadMdBar QueryTimeCost:%lld ms, SortTimeCost:%lld ms, RecordCount:%lld", t1.count(), t2.count(), mdBars.size());
}

void MdReader::ReadMdTickForOneSub(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::DepthMarketData*>& mdTicks)
{
    std::string sql = GetTickSqlString(mdSubscribe);
    WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", sql.c_str());

    std::list<QuantTrading::DepthMarketData*> tempMdTicks;
    ThrowIfQueryFailed(duckdbWrapper_->SelectWithSqlVectorized(
        sql.c_str(), &DepthMarketData::GetSchema(), &tempMdTicks, MakeVectorizedRecordFactory<DepthMarketData>()));
    UpdateMdTicks(mdSubscribe, tempMdTicks);
    mdTicks.splice(mdTicks.end(), tempMdTicks);
}

void MdReader::ReadMdBarForOneSub(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::BarMarketData*>& mdBars)
{
    std::string sql = GetBarSqlString(mdSubscribe);
    WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", sql.c_str());

    std::list<QuantTrading::BarMarketData*> tempMdBars;
    ThrowIfQueryFailed(duckdbWrapper_->SelectWithSqlVectorized(
        sql.c_str(), &BarMarketData::GetSchema(), &tempMdBars, MakeVectorizedRecordFactory<BarMarketData>()));
    UpdateMdBars(mdSubscribe, tempMdBars);
    mdBars.splice(mdBars.end(), tempMdBars);
}

void MdReader::UpdateMdTicks(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::DepthMarketData*>& mdTicks)
{
    for (auto mdTick : mdTicks)
    {
        memcpy(mdTick->InstrumentId, mdSubscribe->InstrumentId, sizeof(InstrumentIdType));
    }
}
void MdReader::UpdateMdBars(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::BarMarketData*>& mdBars)
{
    for (auto mdBar : mdBars)
    {
        memcpy(mdBar->InstrumentId, mdSubscribe->InstrumentId, sizeof(InstrumentIdType));
        mdBar->UpdateTs = mdBar->UpdateTs * 100000LL;
        mdBar->BarTime = mdBar->UpdateTs;
    }
}

// SQL 列序与 mdb 各结构的 GetSchema() 字段序完全一致；列名以实际 parquet 数据为准
// （数据侧尚未按 mdb schema 整理，缺失列/旧列名在 SQL 侧适配）。
std::string MdReader::GetInstrumentSqlString() const
{
    // Bar parquet 不含合约元数据列；仅 ExchangeId/InstrumentId/ProductId 来自数据，
    // 其余 12 列以 NULL 占位（向量化读 NULL→Int=0/Char=空串/Double=+inf），
    // 由 SimExchange::InitMdInstrument 依据 product 重填。
    // 扫描全部数据目录（Identity=*）且不按精度过滤：任意一行即可标识合约，
    // 兼容既有 1m/1h/1d 混存的 CFFEX 文件，也支持其他交易所目录（如 SSE.Stock 的 5m 文件）。
    static const char* sqlTemplate =
        "Select ExchangeId, InstrumentId, NULL, NULL, ProductId, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL "
        "from read_parquet('%s/Bar/Identity=*/Year=*/*.parquet', union_by_name=true) "
        "where TradingDay >= '%s' and TradingDay <= '%s' "
        "Group by ExchangeId, InstrumentId, ProductId;";
    return FormatSql(sqlTemplate, mdDataPath_.c_str(), startTradingDay_, endTradingDay_);
}

std::string MdReader::GetTickSqlString(QuantTrading::MdSubscribe* mdSubscribe) const
{
    // Tick parquet 盘口为数组列（AskPrices[] 等），按下标逐档展开；
    // 数据源缺 OpenPrice/ClosePrice/UpperLimitPrice/LowerLimitPrice/AveragePrice 5 列，
    // 以 NULL 占位（向量化读 NULL→Double=+inf，盘口空档位即无成交价）。
    static const char* sqlTemplate =
        "Select TradingDay, ExchangeId, InstrumentId, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, NULL, "
        "HighestPrice, LowestPrice, NULL, LastTraded, Volume, LastTurnover, Turnover, OpenInterest, SettlementPrice, NULL, NULL, NULL, "
        "AskPrices[1], AskPrices[2], AskPrices[3], AskPrices[4], AskPrices[5], AskPrices[6], AskPrices[7], AskPrices[8], AskPrices[9], AskPrices[10], "
        "AskVolumes[1], AskVolumes[2], AskVolumes[3], AskVolumes[4], AskVolumes[5], AskVolumes[6], AskVolumes[7], AskVolumes[8], AskVolumes[9], AskVolumes[10], "
        "BidPrices[1], BidPrices[2], BidPrices[3], BidPrices[4], BidPrices[5], BidPrices[6], BidPrices[7], BidPrices[8], BidPrices[9], BidPrices[10], "
        "BidVolumes[1], BidVolumes[2], BidVolumes[3], BidVolumes[4], BidVolumes[5], BidVolumes[6], BidVolumes[7], BidVolumes[8], BidVolumes[9], BidVolumes[10] "
        "from read_parquet('%s/Tick/Identity=%s.*/Year=*/Month=*/*.parquet', union_by_name=true) "
        "where TradingDay >= '%s' and TradingDay <= '%s' and InstrumentId = '%s';";
    return FormatSql(sqlTemplate, mdDataPath_.c_str(),
        mdSubscribe->ExchangeId, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentId);
}

std::string MdReader::GetBarSqlString(QuantTrading::MdSubscribe* mdSubscribe) const
{
    // 按配置的 BarPreces 过滤：同一数据根可并存多精度文件（旧 D:\Md 树单文件内 1m/1h/1d 混存），
    // 不过滤会把非本周期 bar 混入回放；精度枚举与周期数同样取自配置而非写死 Minute/1。
    static const char* sqlTemplate =
        "Select TradingDay, ExchangeId, InstrumentId, %d, %d, UpdateTs, UpdateTs, "
        "PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, LastTraded, Volume, LastTurnover, Turnover, OpenInterest "
        "from read_parquet('%s/Bar/Identity=%s.*/Year=*/*.parquet', union_by_name=true) "
        "where TradingDay >= '%s' and TradingDay <= '%s' and Preces = '%s' and InstrumentId = '%s';";
    return FormatSql(sqlTemplate, static_cast<int>(barPrecesType_), barPeriod_,
        mdDataPath_.c_str(), mdSubscribe->ExchangeId, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, barPreces_.c_str(), mdSubscribe->RealInstrumentId);
}
}
