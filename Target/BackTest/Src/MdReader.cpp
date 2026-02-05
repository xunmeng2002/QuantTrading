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
	ParseMdTickRecord(result, tempMdTicks);
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
	ParseMdBarRecord(result, tempMdBars);
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
void MdReader::ParseMdTickRecord(duckdb_result& result, std::list<mdb::DepthMarketData*>& records)
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
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);
		duckdb_vector column7 = duckdb_data_chunk_get_vector(dataChunk, 7);
		duckdb_vector column8 = duckdb_data_chunk_get_vector(dataChunk, 8);
		duckdb_vector column9 = duckdb_data_chunk_get_vector(dataChunk, 9);
		duckdb_vector column10 = duckdb_data_chunk_get_vector(dataChunk, 10);
		duckdb_vector column11 = duckdb_data_chunk_get_vector(dataChunk, 11);
		duckdb_vector column12 = duckdb_data_chunk_get_vector(dataChunk, 12);
		duckdb_vector column13 = duckdb_data_chunk_get_vector(dataChunk, 13);
		duckdb_vector column14 = duckdb_data_chunk_get_vector(dataChunk, 14);
		duckdb_vector column15 = duckdb_data_chunk_get_vector(dataChunk, 15);
		duckdb_vector column16 = duckdb_data_chunk_get_vector(dataChunk, 16);
		duckdb_vector column17 = duckdb_data_chunk_get_vector(dataChunk, 17);
		duckdb_vector column18 = duckdb_data_chunk_get_vector(dataChunk, 18);
		duckdb_vector column19 = duckdb_data_chunk_get_vector(dataChunk, 19);
		duckdb_vector column20 = duckdb_data_chunk_get_vector(dataChunk, 20);
		duckdb_vector column21 = duckdb_data_chunk_get_vector(dataChunk, 21);
		duckdb_vector column22 = duckdb_data_chunk_get_vector(dataChunk, 22);
		duckdb_vector column23 = duckdb_data_chunk_get_vector(dataChunk, 23);
		duckdb_vector column24 = duckdb_data_chunk_get_vector(dataChunk, 24);
		duckdb_vector column25 = duckdb_data_chunk_get_vector(dataChunk, 25);
		duckdb_vector column26 = duckdb_data_chunk_get_vector(dataChunk, 26);
		duckdb_vector column27 = duckdb_data_chunk_get_vector(dataChunk, 27);
		duckdb_vector column28 = duckdb_data_chunk_get_vector(dataChunk, 28);
		duckdb_vector column29 = duckdb_data_chunk_get_vector(dataChunk, 29);
		duckdb_vector column30 = duckdb_data_chunk_get_vector(dataChunk, 30);
		duckdb_vector column31 = duckdb_data_chunk_get_vector(dataChunk, 31);
		duckdb_vector column32 = duckdb_data_chunk_get_vector(dataChunk, 32);
		duckdb_vector column33 = duckdb_data_chunk_get_vector(dataChunk, 33);
		duckdb_vector column34 = duckdb_data_chunk_get_vector(dataChunk, 34);
		duckdb_vector column35 = duckdb_data_chunk_get_vector(dataChunk, 35);
		duckdb_vector column36 = duckdb_data_chunk_get_vector(dataChunk, 36);
		duckdb_vector column37 = duckdb_data_chunk_get_vector(dataChunk, 37);
		duckdb_vector column38 = duckdb_data_chunk_get_vector(dataChunk, 38);
		duckdb_vector column39 = duckdb_data_chunk_get_vector(dataChunk, 39);
		duckdb_vector column40 = duckdb_data_chunk_get_vector(dataChunk, 40);
		duckdb_vector column41 = duckdb_data_chunk_get_vector(dataChunk, 41);
		duckdb_vector column42 = duckdb_data_chunk_get_vector(dataChunk, 42);
		duckdb_vector column43 = duckdb_data_chunk_get_vector(dataChunk, 43);
		duckdb_vector column44 = duckdb_data_chunk_get_vector(dataChunk, 44);
		duckdb_vector column45 = duckdb_data_chunk_get_vector(dataChunk, 45);
		duckdb_vector column46 = duckdb_data_chunk_get_vector(dataChunk, 46);
		duckdb_vector column47 = duckdb_data_chunk_get_vector(dataChunk, 47);
		duckdb_vector column48 = duckdb_data_chunk_get_vector(dataChunk, 48);
		duckdb_vector column49 = duckdb_data_chunk_get_vector(dataChunk, 49);
		duckdb_vector column50 = duckdb_data_chunk_get_vector(dataChunk, 50);
		duckdb_vector column51 = duckdb_data_chunk_get_vector(dataChunk, 51);
		duckdb_vector column52 = duckdb_data_chunk_get_vector(dataChunk, 52);
		duckdb_vector column53 = duckdb_data_chunk_get_vector(dataChunk, 53);
		duckdb_vector column54 = duckdb_data_chunk_get_vector(dataChunk, 54);

		int64_t* dataColumn0 = (int64_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		int64_t* dataColumn3 = (int64_t*)duckdb_vector_get_data(column3);
		duckdb_hugeint* dataColumn4 = (duckdb_hugeint*)duckdb_vector_get_data(column4);
		duckdb_hugeint* dataColumn5 = (duckdb_hugeint*)duckdb_vector_get_data(column5);
		duckdb_hugeint* dataColumn6 = (duckdb_hugeint*)duckdb_vector_get_data(column6);
		duckdb_hugeint* dataColumn7 = (duckdb_hugeint*)duckdb_vector_get_data(column7);
		duckdb_hugeint* dataColumn8 = (duckdb_hugeint*)duckdb_vector_get_data(column8);
		duckdb_hugeint* dataColumn9 = (duckdb_hugeint*)duckdb_vector_get_data(column9);
		duckdb_hugeint* dataColumn10 = (duckdb_hugeint*)duckdb_vector_get_data(column10);
		double* dataColumn11 = (double*)duckdb_vector_get_data(column11);
		double* dataColumn12 = (double*)duckdb_vector_get_data(column12);
		double* dataColumn13 = (double*)duckdb_vector_get_data(column13);
		double* dataColumn14 = (double*)duckdb_vector_get_data(column14);
		duckdb_hugeint* dataColumn15 = (duckdb_hugeint*)duckdb_vector_get_data(column15);
		duckdb_hugeint* dataColumn16 = (duckdb_hugeint*)duckdb_vector_get_data(column16);
		duckdb_hugeint* dataColumn17 = (duckdb_hugeint*)duckdb_vector_get_data(column17);
		duckdb_hugeint* dataColumn18 = (duckdb_hugeint*)duckdb_vector_get_data(column18);
		duckdb_hugeint* dataColumn19 = (duckdb_hugeint*)duckdb_vector_get_data(column19);
		duckdb_hugeint* dataColumn20 = (duckdb_hugeint*)duckdb_vector_get_data(column20);
		duckdb_hugeint* dataColumn21 = (duckdb_hugeint*)duckdb_vector_get_data(column21);
		duckdb_hugeint* dataColumn22 = (duckdb_hugeint*)duckdb_vector_get_data(column22);
		duckdb_hugeint* dataColumn23 = (duckdb_hugeint*)duckdb_vector_get_data(column23);
		duckdb_hugeint* dataColumn24 = (duckdb_hugeint*)duckdb_vector_get_data(column34);
		double* dataColumn25 = (double*)duckdb_vector_get_data(column25);
		double* dataColumn26 = (double*)duckdb_vector_get_data(column26);
		double* dataColumn27 = (double*)duckdb_vector_get_data(column27);
		double* dataColumn28 = (double*)duckdb_vector_get_data(column28);
		double* dataColumn29 = (double*)duckdb_vector_get_data(column29);
		double* dataColumn30 = (double*)duckdb_vector_get_data(column30);
		double* dataColumn31 = (double*)duckdb_vector_get_data(column31);
		double* dataColumn32 = (double*)duckdb_vector_get_data(column32);
		double* dataColumn33 = (double*)duckdb_vector_get_data(column33);
		double* dataColumn34 = (double*)duckdb_vector_get_data(column34);
		duckdb_hugeint* dataColumn35 = (duckdb_hugeint*)duckdb_vector_get_data(column35);
		duckdb_hugeint* dataColumn36 = (duckdb_hugeint*)duckdb_vector_get_data(column36);
		duckdb_hugeint* dataColumn37 = (duckdb_hugeint*)duckdb_vector_get_data(column37);
		duckdb_hugeint* dataColumn38 = (duckdb_hugeint*)duckdb_vector_get_data(column38);
		duckdb_hugeint* dataColumn39 = (duckdb_hugeint*)duckdb_vector_get_data(column39);
		duckdb_hugeint* dataColumn40 = (duckdb_hugeint*)duckdb_vector_get_data(column40);
		duckdb_hugeint* dataColumn41 = (duckdb_hugeint*)duckdb_vector_get_data(column41);
		duckdb_hugeint* dataColumn42 = (duckdb_hugeint*)duckdb_vector_get_data(column42);
		duckdb_hugeint* dataColumn43 = (duckdb_hugeint*)duckdb_vector_get_data(column43);
		duckdb_hugeint* dataColumn44 = (duckdb_hugeint*)duckdb_vector_get_data(column44);
		double* dataColumn45 = (double*)duckdb_vector_get_data(column45);
		double* dataColumn46 = (double*)duckdb_vector_get_data(column46);
		double* dataColumn47 = (double*)duckdb_vector_get_data(column47);
		double* dataColumn48 = (double*)duckdb_vector_get_data(column48);
		double* dataColumn49 = (double*)duckdb_vector_get_data(column49);
		double* dataColumn50 = (double*)duckdb_vector_get_data(column50);
		double* dataColumn51 = (double*)duckdb_vector_get_data(column51);
		double* dataColumn52 = (double*)duckdb_vector_get_data(column52);
		double* dataColumn53 = (double*)duckdb_vector_get_data(column53);
		double* dataColumn54 = (double*)duckdb_vector_get_data(column54);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);
		uint64_t* validityColumn9 = duckdb_vector_get_validity(column9);
		uint64_t* validityColumn10 = duckdb_vector_get_validity(column10);
		uint64_t* validityColumn11 = duckdb_vector_get_validity(column11);
		uint64_t* validityColumn12 = duckdb_vector_get_validity(column12);
		uint64_t* validityColumn13 = duckdb_vector_get_validity(column13);
		uint64_t* validityColumn14 = duckdb_vector_get_validity(column14);
		uint64_t* validityColumn15 = duckdb_vector_get_validity(column15);
		uint64_t* validityColumn16 = duckdb_vector_get_validity(column16);
		uint64_t* validityColumn17 = duckdb_vector_get_validity(column17);
		uint64_t* validityColumn18 = duckdb_vector_get_validity(column18);
		uint64_t* validityColumn19 = duckdb_vector_get_validity(column19);
		uint64_t* validityColumn20 = duckdb_vector_get_validity(column20);
		uint64_t* validityColumn21 = duckdb_vector_get_validity(column21);
		uint64_t* validityColumn22 = duckdb_vector_get_validity(column22);
		uint64_t* validityColumn23 = duckdb_vector_get_validity(column23);
		uint64_t* validityColumn24 = duckdb_vector_get_validity(column24);
		uint64_t* validityColumn25 = duckdb_vector_get_validity(column25);
		uint64_t* validityColumn26 = duckdb_vector_get_validity(column26);
		uint64_t* validityColumn27 = duckdb_vector_get_validity(column27);
		uint64_t* validityColumn28 = duckdb_vector_get_validity(column28);
		uint64_t* validityColumn29 = duckdb_vector_get_validity(column29);
		uint64_t* validityColumn30 = duckdb_vector_get_validity(column30);
		uint64_t* validityColumn31 = duckdb_vector_get_validity(column31);
		uint64_t* validityColumn32 = duckdb_vector_get_validity(column32);
		uint64_t* validityColumn33 = duckdb_vector_get_validity(column33);
		uint64_t* validityColumn34 = duckdb_vector_get_validity(column34);
		uint64_t* validityColumn35 = duckdb_vector_get_validity(column35);
		uint64_t* validityColumn36 = duckdb_vector_get_validity(column36);
		uint64_t* validityColumn37 = duckdb_vector_get_validity(column37);
		uint64_t* validityColumn38 = duckdb_vector_get_validity(column38);
		uint64_t* validityColumn39 = duckdb_vector_get_validity(column39);
		uint64_t* validityColumn40 = duckdb_vector_get_validity(column40);
		uint64_t* validityColumn41 = duckdb_vector_get_validity(column41);
		uint64_t* validityColumn42 = duckdb_vector_get_validity(column42);
		uint64_t* validityColumn43 = duckdb_vector_get_validity(column43);
		uint64_t* validityColumn44 = duckdb_vector_get_validity(column44);
		uint64_t* validityColumn45 = duckdb_vector_get_validity(column45);
		uint64_t* validityColumn46 = duckdb_vector_get_validity(column46);
		uint64_t* validityColumn47 = duckdb_vector_get_validity(column47);
		uint64_t* validityColumn48 = duckdb_vector_get_validity(column48);
		uint64_t* validityColumn49 = duckdb_vector_get_validity(column49);
		uint64_t* validityColumn50 = duckdb_vector_get_validity(column50);
		uint64_t* validityColumn51 = duckdb_vector_get_validity(column51);
		uint64_t* validityColumn52 = duckdb_vector_get_validity(column52);
		uint64_t* validityColumn53 = duckdb_vector_get_validity(column53);
		uint64_t* validityColumn54 = duckdb_vector_get_validity(column54);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			DepthMarketData* record = DepthMarketData::Allocate();
			memset(record, 0, sizeof(DepthMarketData));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				strcpy(record->TradingDay, to_string(dataColumn0[row]).c_str());
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->UpdateTs = dataColumn3[row];
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->LastPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn4[row] }); else record->LastPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->PreSettlementPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn5[row] }); else record->PreSettlementPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->PreClosePrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn6[row] }); else record->PreClosePrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->HighestPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn7[row] }); else record->HighestPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->LowestPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn8[row] }); else record->LowestPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->CurrTurnover = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn9[row] }); else record->CurrTurnover = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->Turnover = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn10[row] }); else record->Turnover = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->CurrVolume = (VolumeType)dataColumn11[row];
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->Volume = (VolumeType)dataColumn12[row];
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->OpenInterest = dataColumn13[row];
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->PreOpenInterest = dataColumn14[row];
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->AskPrice1 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn15[row] }); else record->AskPrice1 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->AskPrice2 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn16[row] }); else record->AskPrice2 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->AskPrice3 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn17[row] }); else record->AskPrice3 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->AskPrice4 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn18[row] }); else record->AskPrice4 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->AskPrice5 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn19[row] }); else record->AskPrice5 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn20, row)) record->AskPrice6 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn20[row] }); else record->AskPrice6 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn21, row)) record->AskPrice7 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn21[row] }); else record->AskPrice7 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn22, row)) record->AskPrice8 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn22[row] }); else record->AskPrice8 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn23, row)) record->AskPrice9 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn23[row] }); else record->AskPrice9 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn24, row)) record->AskPrice10 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn24[row] }); else record->AskPrice10 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn25, row)) record->AskVolume1 = (VolumeType)dataColumn25[row];
			if (duckdb_validity_row_is_valid(validityColumn26, row)) record->AskVolume2 = (VolumeType)dataColumn26[row];
			if (duckdb_validity_row_is_valid(validityColumn27, row)) record->AskVolume3 = (VolumeType)dataColumn27[row];
			if (duckdb_validity_row_is_valid(validityColumn28, row)) record->AskVolume4 = (VolumeType)dataColumn28[row];
			if (duckdb_validity_row_is_valid(validityColumn29, row)) record->AskVolume5 = (VolumeType)dataColumn29[row];
			if (duckdb_validity_row_is_valid(validityColumn30, row)) record->AskVolume6 = (VolumeType)dataColumn30[row];
			if (duckdb_validity_row_is_valid(validityColumn31, row)) record->AskVolume7 = (VolumeType)dataColumn31[row];
			if (duckdb_validity_row_is_valid(validityColumn32, row)) record->AskVolume8 = (VolumeType)dataColumn32[row];
			if (duckdb_validity_row_is_valid(validityColumn33, row)) record->AskVolume9 = (VolumeType)dataColumn33[row];
			if (duckdb_validity_row_is_valid(validityColumn34, row)) record->AskVolume10 = (VolumeType)dataColumn34[row];
			if (duckdb_validity_row_is_valid(validityColumn35, row)) record->BidPrice1 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn35[row] }); else record->BidPrice1 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn36, row)) record->BidPrice2 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn36[row] }); else record->BidPrice2 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn37, row)) record->BidPrice3 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn37[row] }); else record->BidPrice3 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn38, row)) record->BidPrice4 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn38[row] }); else record->BidPrice4 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn39, row)) record->BidPrice5 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn39[row] }); else record->BidPrice5 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn40, row)) record->BidPrice6 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn40[row] }); else record->BidPrice6 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn41, row)) record->BidPrice7 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn41[row] }); else record->BidPrice7 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn42, row)) record->BidPrice8 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn42[row] }); else record->BidPrice8 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn43, row)) record->BidPrice9 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn43[row] }); else record->BidPrice9 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn44, row)) record->BidPrice10 = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn44[row] }); else record->BidPrice10 = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn45, row)) record->BidVolume1 = (VolumeType)dataColumn45[row];
			if (duckdb_validity_row_is_valid(validityColumn46, row)) record->BidVolume2 = (VolumeType)dataColumn46[row];
			if (duckdb_validity_row_is_valid(validityColumn47, row)) record->BidVolume3 = (VolumeType)dataColumn47[row];
			if (duckdb_validity_row_is_valid(validityColumn48, row)) record->BidVolume4 = (VolumeType)dataColumn48[row];
			if (duckdb_validity_row_is_valid(validityColumn49, row)) record->BidVolume5 = (VolumeType)dataColumn49[row];
			if (duckdb_validity_row_is_valid(validityColumn50, row)) record->BidVolume6 = (VolumeType)dataColumn50[row];
			if (duckdb_validity_row_is_valid(validityColumn51, row)) record->BidVolume7 = (VolumeType)dataColumn51[row];
			if (duckdb_validity_row_is_valid(validityColumn52, row)) record->BidVolume8 = (VolumeType)dataColumn52[row];
			if (duckdb_validity_row_is_valid(validityColumn53, row)) record->BidVolume9 = (VolumeType)dataColumn53[row];
			if (duckdb_validity_row_is_valid(validityColumn54, row)) record->BidVolume10 = (VolumeType)dataColumn54[row];
			records.push_back(record);
		}
	}
}
void MdReader::ParseMdBarRecord(duckdb_result& result, std::list<mdb::BarMarketData*>& records)
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
		duckdb_vector column3 = duckdb_data_chunk_get_vector(dataChunk, 3);
		duckdb_vector column4 = duckdb_data_chunk_get_vector(dataChunk, 4);
		duckdb_vector column5 = duckdb_data_chunk_get_vector(dataChunk, 5);
		duckdb_vector column6 = duckdb_data_chunk_get_vector(dataChunk, 6);
		duckdb_vector column7 = duckdb_data_chunk_get_vector(dataChunk, 7);
		duckdb_vector column8 = duckdb_data_chunk_get_vector(dataChunk, 8);
		duckdb_vector column9 = duckdb_data_chunk_get_vector(dataChunk, 9);
		duckdb_vector column10 = duckdb_data_chunk_get_vector(dataChunk, 10);
		duckdb_vector column11 = duckdb_data_chunk_get_vector(dataChunk, 11);
		duckdb_vector column12 = duckdb_data_chunk_get_vector(dataChunk, 12);
		duckdb_vector column13 = duckdb_data_chunk_get_vector(dataChunk, 13);
		duckdb_vector column14 = duckdb_data_chunk_get_vector(dataChunk, 14);
		duckdb_vector column15 = duckdb_data_chunk_get_vector(dataChunk, 15);
		duckdb_vector column16 = duckdb_data_chunk_get_vector(dataChunk, 16);
		duckdb_vector column17 = duckdb_data_chunk_get_vector(dataChunk, 17);
		duckdb_vector column18 = duckdb_data_chunk_get_vector(dataChunk, 18);
		duckdb_vector column19 = duckdb_data_chunk_get_vector(dataChunk, 19);

		int64_t* dataColumn0 = (int64_t*)duckdb_vector_get_data(column0);
		duckdb_string_t* dataColumn1 = (duckdb_string_t*)duckdb_vector_get_data(column1);
		duckdb_string_t* dataColumn2 = (duckdb_string_t*)duckdb_vector_get_data(column2);
		int* dataColumn3 = (int*)duckdb_vector_get_data(column3);
		int* dataColumn4 = (int*)duckdb_vector_get_data(column4);
		int64_t* dataColumn5 = (int64_t*)duckdb_vector_get_data(column5);
		int64_t* dataColumn6 = (int64_t*)duckdb_vector_get_data(column6);
		duckdb_hugeint* dataColumn7 = (duckdb_hugeint*)duckdb_vector_get_data(column7);
		duckdb_hugeint* dataColumn8 = (duckdb_hugeint*)duckdb_vector_get_data(column8);
		duckdb_hugeint* dataColumn9 = (duckdb_hugeint*)duckdb_vector_get_data(column9);
		duckdb_hugeint* dataColumn10 = (duckdb_hugeint*)duckdb_vector_get_data(column10);
		duckdb_hugeint* dataColumn11 = (duckdb_hugeint*)duckdb_vector_get_data(column11);
		duckdb_hugeint* dataColumn12 = (duckdb_hugeint*)duckdb_vector_get_data(column12);
		duckdb_hugeint* dataColumn13 = (duckdb_hugeint*)duckdb_vector_get_data(column13);
		duckdb_hugeint* dataColumn14 = (duckdb_hugeint*)duckdb_vector_get_data(column14);
		double* dataColumn15 = (double*)duckdb_vector_get_data(column15);
		double* dataColumn16 = (double*)duckdb_vector_get_data(column16);
		duckdb_hugeint* dataColumn17 = (duckdb_hugeint*)duckdb_vector_get_data(column17);
		duckdb_hugeint* dataColumn18 = (duckdb_hugeint*)duckdb_vector_get_data(column18);
		double* dataColumn19 = (double*)duckdb_vector_get_data(column19);

		uint64_t* validityColumn0 = duckdb_vector_get_validity(column0);
		uint64_t* validityColumn1 = duckdb_vector_get_validity(column1);
		uint64_t* validityColumn2 = duckdb_vector_get_validity(column2);
		uint64_t* validityColumn3 = duckdb_vector_get_validity(column3);
		uint64_t* validityColumn4 = duckdb_vector_get_validity(column4);
		uint64_t* validityColumn5 = duckdb_vector_get_validity(column5);
		uint64_t* validityColumn6 = duckdb_vector_get_validity(column6);
		uint64_t* validityColumn7 = duckdb_vector_get_validity(column7);
		uint64_t* validityColumn8 = duckdb_vector_get_validity(column8);
		uint64_t* validityColumn9 = duckdb_vector_get_validity(column9);
		uint64_t* validityColumn10 = duckdb_vector_get_validity(column10);
		uint64_t* validityColumn11 = duckdb_vector_get_validity(column11);
		uint64_t* validityColumn12 = duckdb_vector_get_validity(column12);
		uint64_t* validityColumn13 = duckdb_vector_get_validity(column13);
		uint64_t* validityColumn14 = duckdb_vector_get_validity(column14);
		uint64_t* validityColumn15 = duckdb_vector_get_validity(column15);
		uint64_t* validityColumn16 = duckdb_vector_get_validity(column16);
		uint64_t* validityColumn17 = duckdb_vector_get_validity(column17);
		uint64_t* validityColumn18 = duckdb_vector_get_validity(column18);
		uint64_t* validityColumn19 = duckdb_vector_get_validity(column19);

		idx_t rowCount = duckdb_data_chunk_get_size(dataChunk);
		for (idx_t row = 0LL; row < rowCount; ++row)
		{
			BarMarketData* record = BarMarketData::Allocate();
			memset(record, 0, sizeof(BarMarketData));
			if (duckdb_validity_row_is_valid(validityColumn0, row))
			{
				strcpy(record->TradingDay, to_string(dataColumn0[row]).c_str());
			}
			if (duckdb_validity_row_is_valid(validityColumn1, row))
			{
				CpyDuckdbString(record->ExchangeID, dataColumn1[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn2, row))
			{
				CpyDuckdbString(record->InstrumentID, dataColumn2[row]);
			}
			if (duckdb_validity_row_is_valid(validityColumn3, row)) record->BarPreces = BarPrecesType(dataColumn3[row]);
			if (duckdb_validity_row_is_valid(validityColumn4, row)) record->BarPeriod = dataColumn4[row];
			if (duckdb_validity_row_is_valid(validityColumn5, row)) record->BarTime = dataColumn5[row];
			if (duckdb_validity_row_is_valid(validityColumn6, row)) record->UpdateTs = dataColumn6[row];
			if (duckdb_validity_row_is_valid(validityColumn7, row)) record->PreSettlementPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn7[row] }); else record->PreSettlementPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn8, row)) record->PreClosePrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn7[row] }); else record->PreClosePrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn9, row)) record->HighestPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn9[row] }); else record->HighestPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn10, row)) record->LowestPrice = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn10[row] }); else record->LowestPrice = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn11, row)) record->Open = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn11[row] }); else record->Open = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn12, row)) record->High = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn12[row] }); else record->High = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn13, row)) record->Low = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn13[row] }); else record->Low = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn14, row)) record->Close = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn14[row] }); else record->Close = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn15, row)) record->CurrVolume = (VolumeType)dataColumn15[row];
			if (duckdb_validity_row_is_valid(validityColumn16, row)) record->Volume = (VolumeType)dataColumn16[row];
			if (duckdb_validity_row_is_valid(validityColumn17, row)) record->CurrTurnover = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn17[row] }); else record->CurrTurnover = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn18, row)) record->Turnover = duckdb_decimal_to_double(duckdb_decimal{ 24, 8, dataColumn18[row] }); else record->Turnover = std::numeric_limits<double>::infinity();
			if (duckdb_validity_row_is_valid(validityColumn19, row)) record->OpenInterest = dataColumn19[row];
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
		"from read_parquet('%s/Bar/Identity=CFFEX.*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%s' and TradingDay <= '%s' and Preces = '1d' "
		"Group by ExchangeID, InstrumentID, ProductID;";
	sprintf(m_SqlBuff, sqlTemplate, m_MdDataPath.c_str(), m_StartTradingDay, m_EndTradingDay);
}
void MdReader::GetTickSqlString(mdb::MdSubscribe* mdSubscribe)
{
	static auto sqlTemplate = "Select TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, "
		"LastTurnover, Turnover, LastTraded, Volume, PreOpenInterest, OpenInterest, "
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
		"PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, LastTraded, Volume, LastTurnover, Turnover, OpenInterest "
		"from read_parquet('%s/Bar/Identity=%s.*/Year=*/*.parquet', union_by_name=true) "
		"where TradingDay >= '%s' and TradingDay <= '%s' and InstrumentID = '%s';";
	sprintf(m_SqlBuff, sqlTemplate, BarPrecesType::Minute,
		m_MdDataPath.c_str(), mdSubscribe->ExchangeID, mdSubscribe->StartTradingDay, mdSubscribe->EndTradingDay, mdSubscribe->RealInstrumentID);
}
