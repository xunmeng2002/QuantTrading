#include "BackTestApiMiddle.h"
#include "GridStrategy.h"
#include "Config/Config.h"
#include <Spark/Core/Logger/Logger.h>

using namespace QuantTrading;
using namespace QuantTrading::teststrategygrid;

const char* ConfigName = "TestStrategyGrid.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	// 交易节由 BackTest.dll 内的回测引擎自己装载（BackTest.json 的 SessionFile），
	// 策略宿主只声明期望的 bar 周期，聚合与桶对齐全部发生在引擎侧，本进程不再持有交易节
	auto api = BackTestApiMiddle::CreateBackTestApiMiddle();
	GridParams gridParams;
	gridParams.GridStep = config.GridStep;
	gridParams.GridCount = config.GridCount;
	gridParams.VolumePerGrid = config.VolumePerGrid;
	gridParams.ExchangeId = config.ExchangeId;
	gridParams.InstrumentId = config.InstrumentId;
	gridParams.BarPreces = config.BarPreces;
	GridStrategy gridStrategy(api, config.AccountId.c_str(), gridParams);
	if (!gridStrategy.Start())
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return 1;
	}
	gridStrategy.WaitForEnd();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}
