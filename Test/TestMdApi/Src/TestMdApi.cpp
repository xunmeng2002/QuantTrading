#include "MdApiMiddle.h"
#include "MdSpiImpl.h"
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

	auto api = MdApiMiddle::CreateMdApiMiddle();
	auto spi = new MdSpiImpl(api);
	cout << api->GetApiVersion() << endl;
	api->RegisterSpi(spi);
	api->RegisterFront(serverConfig.MdOfferAddress.c_str());
	api->Init();

	std::this_thread::sleep_for(chrono::seconds(90));
	api->Release();
	std::this_thread::sleep_for(chrono::seconds(1));

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

