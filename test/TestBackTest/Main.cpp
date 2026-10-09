#include "BackTestApiMiddle.h"
#include "BackTestSpiImpl.h"
#include "RunResult.h"
#include "Config/Config.h"
#include <Spark/Core/Logger/Logger.h>
#include <cstdio>
#include <exception>

using namespace QuantTrading;
using namespace QuantTrading::TestBackTest;
using namespace QuantTrading::BackTest;

const char* ConfigName = "TestBackTest.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	// 启动前先删陈旧结果：这样「文件不存在」就等价于「本轮没走完收尾」，
	// 调度器复用同一工作目录也不会把上一轮的 result.json 读成本轮结论
	std::remove(ResultFileName);

	auto api = BackTestApiMiddle::CreateBackTestApiMiddle();
	BackTestSpiParams spiParams;
	spiParams.OrderTriggerRatio = config.OrderTriggerRatio;
	spiParams.OrderVolume = config.OrderVolume;
	spiParams.AccountId = config.AccountId;
	spiParams.ExchangeId = config.ExchangeId;
	spiParams.InstrumentId = config.InstrumentId;

	// 参数非法在构造期即抛（如 OrderTriggerRatio 越界）：异常一律算「宿主启动失败」，
	// 不让它走 abort（MSVC 下 abort 与「引擎报告失败」同为码 3，只能靠结果文件消歧）
	bool hostStarted = false;
	try
	{
		BackTestSpiImpl* spi = new BackTestSpiImpl(api, spiParams);
		api->RegisterSpi(spi);
		// Init 失败时引擎线程从未启动，后面的 Join 会挂在没启动的 AsyncDbWriter/ThreadBase 上，必须先返回
		if (api->Init())
		{
			spi->ReqRegisterAccount();
			spi->ReqSubMarketData();
			api->Join();
			hostStarted = true;
		}
		delete spi;
	}
	catch (const std::exception& error)
	{
		std::fprintf(stderr, "BackTest host start failed: %s\n", error.what());
	}

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return hostStarted ? ExitCodeFromRunResultFile(ResultFileName) : ExitCodeHostInitFailed;
}
