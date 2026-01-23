#include "BackTestApiMiddle.h"
#include "BackTestSpiImpl.h"
#include "Logger.h"
#include <iostream>

using namespace std;

const char* ConfigName = "TestBackTest.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();


	auto api = BackTestApiMiddle::CreateBackTestApiMiddle();
	BackTestApi::SetExternLogger(Logger::GetWriteLogFunc());
	BackTestSpiImpl* spi = new BackTestSpiImpl(api, config);
	api->RegisterSpi(spi);
	api->Init();
	spi->ReqSubMarketData();

	api->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

