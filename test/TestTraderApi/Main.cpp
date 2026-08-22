#include "TraderApiMiddle.h"
#include "TraderSpiImpl.h"
#include "Config/Config.h"
#include "ServerConfig.h"
#include "Environment.h"
#include <Spark/Core/Logger/Logger.h>
#include <iostream>

using namespace std;
using namespace quanttrading::testtraderapi;

const char* ConfigName = "TestTraderApi.json";

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

	auto api = TraderApiMiddle::CreateTraderApiMiddle();
	auto spi = new TraderSpiImpl(api);
	spi->SetAccountInfo(environment->Accounts[0]);
	cout << api->GetApiVersion() << endl;
	api->RegisterSpi(spi);
	api->RegisterFront(serverConfig.TradeFrontAddress.c_str());
	api->Init();

	int waitSeconds = 0;
	while (!spi->m_Finished && waitSeconds < 120)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		++waitSeconds;
	}
	spi->ReqQryOrder();
	std::this_thread::sleep_for(chrono::seconds(10));

	api->Release();
	std::this_thread::sleep_for(chrono::seconds(1));

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

