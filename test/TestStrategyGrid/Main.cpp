#include "BackTestApiMiddle.h"
#include "GridStrategy.h"
#include "RunResult.h"
#include "Config/Config.h"
#include <Spark/Core/Logger/Logger.h>
#include <cstdio>
#include <exception>

using namespace QuantTrading;
using namespace QuantTrading::TestStrategyGrid;
using namespace QuantTrading::BackTest;

const char* ConfigName = "TestStrategyGrid.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	// 启动前先删陈旧结果，让「文件不存在」等价于「本轮没走完收尾」
	std::remove(ResultFileName);

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
	// 参数非法在构造期即抛（如 GridStep 比例越界）：与 Python 孪生同码 —— 异常一律算「宿主
	// 启动失败」，不让它走 abort（MSVC 下 abort 与「引擎报告失败」同为码 3，只能靠结果文件消歧）
	bool hostStarted = false;
	try
	{
		GridStrategy gridStrategy(api, config.AccountId.c_str(), gridParams);
		hostStarted = gridStrategy.Start();
		if (hostStarted)
		{
			gridStrategy.WaitForEnd();
		}
	}
	catch (const std::exception& error)
	{
		std::fprintf(stderr, "Strategy start failed: %s\n", error.what());
	}

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return hostStarted ? ExitCodeFromRunResultFile(ResultFileName) : ExitCodeHostInitFailed;
}
