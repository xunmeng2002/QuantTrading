#include "BackTestApiMiddle.h"
#include "GridStrategy.h"
#include "Config/Config.h"
#include <Spark/Core/Logger/Logger.h>

using namespace quanttrading;
using namespace quanttrading::teststrategygrid;

const char* ConfigName = "TestStrategyGrid.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	auto api = BackTestApiMiddle::CreateBackTestApiMiddle();
	GridParams gridParams;
	gridParams.GridStep = config.GridStep;
	gridParams.GridCount = config.GridCount;
	gridParams.VolumePerGrid = config.VolumePerGrid;
	gridParams.ExchangeID = config.ExchangeID;
	gridParams.InstrumentID = config.InstrumentID;
	gridParams.BarPreces = config.BarPreces;
	GridStrategy gridStrategy(api, config.AccountID.c_str(), gridParams);
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
