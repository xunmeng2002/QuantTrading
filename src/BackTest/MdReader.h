#pragma once
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <Spark/Types.h>
#include "MdbStructs.h"
#include "Config/Config.h"
#include <list>
#include <memory>
#include <string>

namespace QuantTrading::BackTest
{
class MdReader
{
public:
	MdReader(const Config& config);
	~MdReader();
	bool Init();

	// 数据集精度（BackTest.json 的 BarPreces）：订阅声明的目标周期须能由它聚合而来，引擎在装载期据此预校验
	BarPrecesType GetBarPrecesType() const { return barPrecesType_; }
	int GetBarPeriod() const { return barPeriod_; }

	void ReadMdInstrument(std::list<QuantTrading::Instrument*>& instruments);
	void ReadMdTick(std::list<QuantTrading::MdSubscribe*>& mdSubscribes, std::list<QuantTrading::DepthMarketData*>& mdTicks);
	void ReadMdBar(std::list<QuantTrading::MdSubscribe*>& mdSubscribes, std::list<QuantTrading::BarMarketData*>& mdBars);

private:
	void ReadMdTickForOneSub(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::DepthMarketData*>& mdTicks);
	void ReadMdBarForOneSub(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::BarMarketData*>& mdBars);

	void UpdateMdTicks(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::DepthMarketData*>& mdTicks);
	void UpdateMdBars(QuantTrading::MdSubscribe* mdSubscribe, std::list<QuantTrading::BarMarketData*>& mdBars);

	std::string GetInstrumentSqlString() const;
	std::string GetTickSqlString(QuantTrading::MdSubscribe* mdSubscribe) const;
	std::string GetBarSqlString(QuantTrading::MdSubscribe* mdSubscribe) const;

private:
	std::string mdDataPath_;
	std::string barPreces_;
	BarPrecesType barPrecesType_ = BarPrecesType::Minute;
	int barPeriod_ = 1;
	DateType startTradingDay_;
	DateType endTradingDay_;
	std::unique_ptr<DbAdapters::DuckdbWrapper> duckdbWrapper_;
};
}
