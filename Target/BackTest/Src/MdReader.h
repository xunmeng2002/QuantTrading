#pragma once
#include "duckdb.hpp"
#include "Types.h"
#include "MdbStructs.h"
#include "Config.h"
#include <list>

class MdReader
{
public:
	MdReader(const Config& config);
	~MdReader();
	bool Init();

	void ReadMdInstrument(std::list<mdb::Instrument*>& instruments);
	void ReadMdTick(std::list<mdb::MdSubscribe*>& mdSubscribes, std::list<mdb::DepthMarketData*>& mdTicks);
	void ReadMdBar(std::list<mdb::MdSubscribe*>& mdSubscribes, std::list<mdb::BarMarketData*>& mdBars);

private:
	void ReadMdTickForOneSub(mdb::MdSubscribe* mdSubscribe, std::list<mdb::DepthMarketData*>& mdTicks);
	void ReadMdBarForOneSub(mdb::MdSubscribe* mdSubscribe, std::list<mdb::BarMarketData*>& mdBars);

	void ExecuteQuery(duckdb_result* result);
	void ParseInstrumentRecord(duckdb_result& result, std::list<mdb::Instrument*>& records);
	void ParseMdTickRecord(duckdb_result& result, std::list<mdb::DepthMarketData*>& records);
	void ParseMdBarRecord(duckdb_result& result, std::list<mdb::BarMarketData*>& records);

	void UpdateMdTicks(mdb::MdSubscribe* mdSubscribe, std::list<mdb::DepthMarketData*>& mdTicks);
	void UpdateMdBars(mdb::MdSubscribe* mdSubscribe, std::list<mdb::BarMarketData*>& mdBars);

	void GetInstrumentSqlString();
	void GetTickSqlString(mdb::MdSubscribe* mdSubscribe);
	void GetBarSqlString(mdb::MdSubscribe* mdSubscribe);

private:
	std::string m_MdDataPath;
	DateType m_StartTradingDay;
	DateType m_EndTradingDay;
	duckdb_database m_Duckdb;
	duckdb_connection m_DuckdbConnection;

	char m_SqlBuff[1024];
};
