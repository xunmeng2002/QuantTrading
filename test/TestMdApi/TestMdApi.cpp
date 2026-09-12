#include "MdApiMiddle.h"
#include "MdSpiImpl.h"
#include "Config/Config.h"
#include "ServerConfig.h"
#include <Spark/Core/Logger/Logger.h>
#include <iostream>

using namespace std;
using namespace quanttrading;
using namespace quanttrading::testmdapi;
using namespace quanttrading;

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

	int waitSeconds = 0;
	while (spi->m_RtnMdCount == 0 && waitSeconds < 120)
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		++waitSeconds;
	}
	if (spi->m_RtnMdCount == 0)
	{
		cout << "Timeout waiting for market data." << endl;
	}
	if (spi->m_RspMdUserLoginCount > 0)
	{
		spi->ReqUserLogout();
		int waitLogoutSeconds = 0;
		while ((spi->m_RspMdUserLogoutCount == 0 || spi->m_RspMdUserLoginCount < 2) && waitLogoutSeconds < 30)
		{
			std::this_thread::sleep_for(chrono::seconds(1));
			++waitLogoutSeconds;
		}
		cout << "Logout Rsp:" << spi->m_RspMdUserLogoutCount << ", Re-login Rsp:" << spi->m_RspMdUserLoginCount << " (expect 1 and 2)" << endl;
	}
	api->Release();
	std::this_thread::sleep_for(chrono::seconds(1));

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

