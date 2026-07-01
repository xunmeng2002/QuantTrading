#include "SimExchangeApiMiddle.h"
#include "SimExchangeSpiImpl.h"
#include "Logger.h"
#include "ServerConfig.h"
#include "Config.h"
#include "Environment.h"
#include <iostream>

using namespace std;

const char* ConfigName = "TestSimExchangeApi.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(config.ServerConfigPath.c_str());

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();

	map<string, Environment*> environments;
	ReadEnvironment(environments, config.EnvironmentFile.c_str());
	auto environment = GetEnvironment(environments, config.EnvironmentName, config.EnvironmentName24);
	if (environment == nullptr)
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return -1;
	}

	auto api = SimExchangeApiMiddle::CreateSimExchangeApiMiddle();
	auto spi = new SimExchangeSpiImpl(api);
	spi->SetAccountInfo(environment->Accounts[0]);
	cout << api->GetApiVersion() << endl;
	api->RegisterSpi(spi);
	api->RegisterFront(serverConfig.TradeFrontAddress.c_str());
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

