#include "MdReader.h"
#include "Logger.h"
#include "MdbStructs.h"
#include "DuckDBCommon.h"
#include "DuckDB.h"
#include <chrono>

using namespace mdb;
using namespace std;
using namespace std::chrono;

MdReader::MdReader(const Config& config)
	:m_MdDataPath(config.MdDataPath), m_StartTradingDay(config.StartTradingDay), m_EndTradingDay(config.EndTradingDay), m_Duckdb(nullptr), m_DuckdbConnection(nullptr), m_SqlBuff{ 0 }
{
}
MdReader::~MdReader()
{
	if (m_DuckdbConnection != nullptr)
	{
		duckdb_disconnect(&m_DuckdbConnection);
	}
	if (m_Duckdb != nullptr)
	{
		duckdb_close(&m_Duckdb);
	}
}
bool MdReader::Init()
{
	if (duckdb_open(nullptr, &m_Duckdb) == DuckDBError)
	{
		WriteLog(LogLevel::Error, "duckdb_open Error.");
		return false;
	}
	if (duckdb_connect(m_Duckdb, &m_DuckdbConnection) == DuckDBError)
	{
		WriteLog(LogLevel::Error, "duckdb_connect Error.");
		return false;
	}
	return true;
}


void MdReader::ReadMdInstrument(std::list<mdb::Instrument*> instruments)
{
	auto startQueryTime = chrono::high_resolution_clock::now();
	memset(m_SqlBuff, 0, sizeof(m_SqlBuff));
	GetInstrumentSqlString();
	WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", m_SqlBuff);

	duckdb_result result;
	ExecuteQuery(&result);
	DuckDB::ParseRecord(result, instruments);
	auto endQueryTime = chrono::high_resolution_clock::now();
	auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
	WriteLog(LogLevel::Info, "ReadMdInstrument QueryTimeCost:%lld ms, RecordCount:%lld", t1.count(), instruments.size());
}
void MdReader::ReadMdTick(std::list<mdb::MdSubscribe*>& mdSubscribes, std::list<mdb::DepthMarketData*>& mdTicks)
{
	auto startQueryTime = chrono::high_resolution_clock::now();
	for (auto mdSubscribe : mdSubscribes)
	{
		ReadMdTickForOneSub(mdSubscribe, mdTicks);
	}
	auto endQueryTime = chrono::high_resolution_clock::now();
	mdTicks.sort([](mdb::DepthMarketData* left, mdb::DepthMarketData* right) {return left->UpdateTs < right->UpdateTs; });
	auto endSortTime = chrono::high_resolution_clock::now();
	auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
	auto t2 = chrono::duration_cast<milliseconds>(endSortTime - endQueryTime);
	WriteLog(LogLevel::Info, "ReadMdTick QueryTimeCost:%lld ms, SortTimeCost:%lld ms, RecordCount:%lld", t1.count(), t2.count(), mdTicks.size());

}
void MdReader::ReadMdBar(std::list<mdb::MdSubscribe*>& mdSubscribes, std::list<mdb::BarMarketData*>& mdBars)
{
	auto startQueryTime = chrono::high_resolution_clock::now();
	for (auto mdSubscribe : mdSubscribes)
	{
		ReadMdBarForOneSub(mdSubscribe, mdBars);
	}
	auto endQueryTime = chrono::high_resolution_clock::now();
	mdBars.sort([](mdb::BarMarketData* left, mdb::BarMarketData* right) {return left->UpdateTs < right->UpdateTs; });
	auto endSortTime = chrono::high_resolution_clock::now();
	auto t1 = chrono::duration_cast<milliseconds>(endQueryTime - startQueryTime);
	auto t2 = chrono::duration_cast<milliseconds>(endSortTime - endQueryTime);
	WriteLog(LogLevel::Info, "ReadMdBar QueryTimeCost:%lld ms, SortTimeCost:%lld ms, RecordCount:%lld", t1.count(), t2.count(), mdBars.size());
}

void MdReader::ReadMdTickForOneSub(mdb::MdSubscribe* mdSubscribe, std::list<mdb::DepthMarketData*>& mdTicks)
{
	memset(m_SqlBuff, 0, sizeof(m_SqlBuff));
	GetTickSqlString(mdSubscribe);
	WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", m_SqlBuff);

	duckdb_result result;
	ExecuteQuery(&result);
	std::list<mdb::DepthMarketData*> tempMdTicks;
	DuckDB::ParseRecord(result, tempMdTicks);
	UpdateMdTicks(mdSubscribe, tempMdTicks);
	mdTicks.splice(mdTicks.end(), tempMdTicks);
}
void MdReader::ReadMdBarForOneSub(mdb::MdSubscribe* mdSubscribe, std::list<mdb::BarMarketData*>& mdBars)
{
	memset(m_SqlBuff, 0, sizeof(m_SqlBuff));
	GetBarSqlString(mdSubscribe);
	WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", m_SqlBuff);

	duckdb_result result;
	ExecuteQuery(&result);
	std::list<mdb::BarMarketData*> tempMdBars;
	DuckDB::ParseRecord(result, tempMdBars);
	UpdateMdBars(mdSubscribe, tempMdBars);
	mdBars.splice(mdBars.end(), tempMdBars);
}

void MdReader::ExecuteQuery(duckdb_result* result)
{
	if (duckdb_query(m_DuckdbConnection, m_SqlBuff, result) == DuckDBError)
	{
		char errorMsg[256]{ 0 };
		sprintf(errorMsg, "duckdb_query Error. ErrorMsg:%s", duckdb_result_error(result));
		WriteLog(LogLevel::Error, errorMsg);
		throw std::logic_error(errorMsg);
	}
}

void MdReader::UpdateMdTicks(mdb::MdSubscribe* mdSubscribe, std::list<mdb::DepthMarketData*>& mdTicks)
{
	for (auto mdTick : mdTicks)
	{
		memcpy(mdTick->InstrumentID, mdSubscribe->InstrumentID, sizeof(InstrumentIDType));
	}
}
void MdReader::UpdateMdBars(mdb::MdSubscribe* mdSubscribe, std::list<mdb::BarMarketData*>& mdBars)
{
	for (auto mdBar : mdBars)
	{
		memcpy(mdBar->InstrumentID, mdSubscribe->InstrumentID, sizeof(InstrumentIDType));
		mdBar->UpdateTs = mdBar->UpdateTs * 100000LL;
		mdBar->BarTime = mdBar->UpdateTs;
	}
}

void MdReader::GetInstrumentSqlString()
{
	static auto sqlTemplate = "Select ExchangeID, InstrumentID, InstrumentID, '', ProductID, 48, 48, 0, 1, 1, 0, 0, 0, 0 "
		"from read_parquet('%s/bar/Identity=*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%d' and TradingDay <= '%d' and Preces = '1d' "
		"Group by ExchangeID, InstrumentID;";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(), m_StartTradingDay, m_EndTradingDay);
}
void MdReader::GetTickSqlString(mdb::MdSubscribe* mdSubscribe)
{
	static auto sqlTemplate = "Select TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, "
		"OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, "
		"SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, "
		"AskPrices[1], AskPrices[2], AskPrices[3], AskPrices[4], AskPrices[5], AskPrices[6], AskPrices[7], AskPrices[8], AskPrices[9], AskPrices[10], "
		"AskVolumes[1], AskVolumes[2], AskVolumes[3], AskVolumes[4], AskVolumes[5], AskVolumes[6], AskVolumes[7], AskVolumes[8], AskVolumes[9], AskVolumes[10], "
		"BidPrices[1], BidPrices[2], BidPrices[3], BidPrices[4], BidPrices[5], BidPrices[6], BidPrices[7], BidPrices[8], BidPrices[9], BidPrices[10], "
		"BidVolumes[1], BidVolumes[2], BidVolumes[3], BidVolumes[4], BidVolumes[5], BidVolumes[6], BidVolumes[7], BidVolumes[8], BidVolumes[9], BidVolumes[10] "
		"from read_parquet('%s/Tick/Identity=%s.*/Year=*/Month=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%d' and TradingDay <= '%d' and InstrumentID = '%s';";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(), 
		mdSubscribe->ExchangeID, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentID);
}
void MdReader::GetBarSqlString(mdb::MdSubscribe* mdSubscribe)
{
	static auto sqlTemplate = "Select TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime, UpdateTs, "
		"PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest "
		"from read_parquet('%s/Bar/Identity=%s.*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%d' and TradingDay <= '%d' and InstrumentID = '%s';";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(),
		mdSubscribe->ExchangeID, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentID);
}
