#include "BackTestApiMiddle.h"
#include "BackTestSpiImpl.h"
#include "RunResult.h"
#include <Spark/Core/Logger/Logger.h>
#include <cstdio>
#include <iostream>

using namespace std;
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
	BackTestSpiImpl* spi = new BackTestSpiImpl(api, config);
	api->RegisterSpi(spi);
	// Init 失败时引擎线程从未启动，后面的 Join 会挂在没启动的 AsyncDbWriter/ThreadBase 上，必须先返回
	if (!api->Init())
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return ExitCodeHostInitFailed;
	}
	spi->ReqRegisterAccount();
	spi->ReqSubMarketData();

	api->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return ExitCodeFromRunResultFile(ResultFileName);
}
