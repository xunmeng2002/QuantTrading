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
	:m_MdDataPath(config.MdDataPath), m_Duckdb(nullptr), m_DuckdbConnection(nullptr), m_SqlBuff{ 0 }
{
	strcpy(m_StartTradingDay, config.StartTradingDay.c_str());
	strcpy(m_EndTradingDay, config.EndTradingDay.c_str());
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


void MdReader::ReadMdInstrument(std::list<mdb::Instrument*>& instruments)
{
	auto startQueryTime = chrono::high_resolution_clock::now();
	memset(m_SqlBuff, 0, sizeof(m_SqlBuff));
	GetInstrumentSqlString();
	WriteLog(LogLevel::Info, "duckdb_query: Sql:%s", m_SqlBuff);

	duckdb_result result;
	ExecuteQuery(&result);
	ParseInstrumentRecord(result, instruments);
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
		char errorMsg[1024]{ 0 };
		sprintf(errorMsg, "duckdb_query Error. ErrorMsg:%s", duckdb_result_error(result));
		WriteLog(LogLevel::Error, errorMsg);
		throw std::logic_error(errorMsg);
	}
}
void MdReader::ParseInstrumentRecord(duckdb_result& result, std::list<mdb::Instrument*>& records)
{
	while (true)
	{
		duckdb_data_chunk dataChunk = duckdb_fetch_chunk(result);
		if (dataChunk == nullptr)
		{
			break;
		}
		duckdb_vector column0 = duckdb_data_chunk_get_vector(dataChunk, 0);
		duckdb_vector column1 = duckdb_data_chunk_get_vector(dataChunk, 1);
		duckdb_vector column2 = duckdb_data_chunk_get_vector(dataChunk, 2);

		duckdb_string_t* dataColumn0 = (duckdb_string_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			Instrument* record = Instrument::Allocate();
			memset(record, 0, sizeof(Instrument));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn0[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->ProductID, dataColumn2[row]);
			}
			records.push_back(record);
		}
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
	static auto sqlTemplate = "Select ExchangeID, InstrumentID, ProductID "
		"from read_parquet('%s/bar/Identity=CFFEX.*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%s' and TradingDay <= '%s' and Preces = '1d' "
		"Group by ExchangeID, InstrumentID, ProductID;";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(), m_StartTradingDay, m_EndTradingDay);
}
void MdReader::GetTickSqlString(mdb::MdSubscribe* mdSubscribe)
{
	static auto sqlTemplate = "Select TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, "
		"OpenPrice, HighestPrice, LowestPrice, 0.0, LastTraded, Volume, LastTurnover, Turnover, OpenInterest, "
		"SettlementPrice, 0.0, 0.0, 0.0, "
		"AskPrices[1], AskPrices[2], AskPrices[3], AskPrices[4], AskPrices[5], AskPrices[6], AskPrices[7], AskPrices[8], AskPrices[9], AskPrices[10], "
		"AskVolumes[1], AskVolumes[2], AskVolumes[3], AskVolumes[4], AskVolumes[5], AskVolumes[6], AskVolumes[7], AskVolumes[8], AskVolumes[9], AskVolumes[10], "
		"BidPrices[1], BidPrices[2], BidPrices[3], BidPrices[4], BidPrices[5], BidPrices[6], BidPrices[7], BidPrices[8], BidPrices[9], BidPrices[10], "
		"BidVolumes[1], BidVolumes[2], BidVolumes[3], BidVolumes[4], BidVolumes[5], BidVolumes[6], BidVolumes[7], BidVolumes[8], BidVolumes[9], BidVolumes[10] "
		"from read_parquet('%s/Tick/Identity=%s.*/Year=*/Month=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%s' and TradingDay <= '%s' and InstrumentID = '%s';";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(), 
		mdSubscribe->ExchangeID, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentID);
}
void MdReader::GetBarSqlString(mdb::MdSubscribe* mdSubscribe)
{
	static auto sqlTemplate = "Select TradingDay, ExchangeID, InstrumentID, %d, 1, UpdateTs, UpdateTs, "
		"PreSettlementPrice, PreClosePrice, Open, High, Low, Close, LastTraded, Volume, LastTurnover, Turnover, OpenInterest "
		"from read_parquet('%s/Bar/Identity=%s.*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%s' and TradingDay <= '%s' and InstrumentID = '%s';";
	sprintf(m_SqlBuff, sqlTemplate, BarPrecesType::Minute,
		m_MdDataPath.c_str(), mdSubscribe->ExchangeID, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentID);
}
