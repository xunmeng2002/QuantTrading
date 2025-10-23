#include "SimExchangeApiMiddle.h"
#include "SimExchangeSpiImpl.h"
#include "Logger.h"
#include "ServerConfig.h"
#include <iostream>

using namespace std;

auto serverConfigFile = "../../ServerConfig.json";

int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();

	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(serverConfigFile);

	auto api = SimExchangeApiMiddle::CreateSimExchangeApiMiddle();
	auto spi = new SimExchangeSpiImpl(api);
	cout << api->GetApiVersion() << endl;
	api->RegisterSpi(spi);
	api->RegisterFront(serverConfig.SETradeFrontAddress.c_str());
	api->Init();

	while (!spi->m_Finished)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
	}
	spi->ReqQryOrder();
	std::this_thread::sleep_for(chrono::seconds(10));

	api->Release();
	std::this_thread::sleep_for(chrono::seconds(1));

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

