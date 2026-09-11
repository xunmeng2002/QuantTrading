#include "BackTestApiMiddle.h"
#include "GridStrategy.h"
#include "Config/Config.h"
#include "TradeSession.h"
#include <Spark/Core/Logger/Logger.h>

using namespace quanttrading;
using namespace quanttrading::bar;
using namespace quanttrading::teststrategygrid;

const char* ConfigName = "TestStrategyGrid.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	// 策略宿主侧装载交易节：BarStatic 为静态库，BackTest.dll 与本进程各持一份 TradeSessions 静态区，
	// 聚合器运行在本进程（StrategyStatic），故必须在策略宿主侧装载，装载失败即拒绝启动（否则会静默回落墙钟对齐）
	if (!TradeSessions::LoadFromFile(config.SessionFile))
	{
		WriteLog(LogLevel::Error, "Load trade sessions failed. SessionFile:%s", config.SessionFile.c_str());
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return 1;
	}

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
