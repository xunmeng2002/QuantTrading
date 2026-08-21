#pragma once
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <Spark/Types.h>
#include "MdbStructs.h"
#include "Config/Config.h"
#include <list>
#include <memory>
#include <string>

namespace quanttrading::backtest
{
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

	void UpdateMdTicks(mdb::MdSubscribe* mdSubscribe, std::list<mdb::DepthMarketData*>& mdTicks);
	void UpdateMdBars(mdb::MdSubscribe* mdSubscribe, std::list<mdb::BarMarketData*>& mdBars);

	std::string GetInstrumentSqlString() const;
	std::string GetTickSqlString(mdb::MdSubscribe* mdSubscribe) const;
	std::string GetBarSqlString(mdb::MdSubscribe* mdSubscribe) const;

private:
	std::string m_MdDataPath;
	DateType m_StartTradingDay;
	DateType m_EndTradingDay;
	std::unique_ptr<dbadapters::DuckdbWrapper> m_DuckdbWrapper;
};
}
