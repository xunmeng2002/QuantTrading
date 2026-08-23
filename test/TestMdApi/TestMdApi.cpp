#include "MdApiMiddle.h"
#include "MdSpiImpl.h"
#include "Config/Config.h"
#include "ServerConfig.h"
#include <Spark/Core/Logger/Logger.h>
#include <iostream>

using namespace std;
using namespace quanttrading;
using namespace quanttrading::testmdapi;
using namespace quanttrading::quanttradingcommon;

const char* ConfigName = "TestMdApi.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(config.ServerConfigPath.c_str());

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();


	auto api = MdApiMiddle::CreateMdApiMiddle();
	auto spi = new MdSpiImpl(api);
	cout << "API Version:" << api->GetApiVersion() << endl;
	api->RegisterSpi(spi);
	api->RegisterFront(serverConfig.MdOfferAddress.c_str());
	api->Init();

	std::this_thread::sleep_for(chrono::seconds(120));
	api->Release();
	std::this_thread::sleep_for(chrono::seconds(1));

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

