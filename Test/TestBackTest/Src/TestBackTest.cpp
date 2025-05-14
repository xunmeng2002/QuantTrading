#include "BackTestApiMiddle.h"
#include "BackTestSpiImpl.h"
#include "Logger.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();


	auto api = BackTestApiMiddle::CreateBackTestApiMiddle();
	BackTestSpiImpl* spi = new BackTestSpiImpl(api);
	api->RegisterSpi(spi);
	api->Init();
	spi->ReqSubMarketData();

	api->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

