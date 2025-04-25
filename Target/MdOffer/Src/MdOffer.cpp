#pragma warning(disable:4819)
#include "ThostFtdcMdApiMiddle.h"
#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
#include "Config.h"
#include "ServerConfig.h"
#include "Environment.h"
#include "MdFront.h"
#include "MdKernel.h"
#include "TradeSession.h"
#include <iostream>
#include <fstream>
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;

const char* ConfigName = "MdOffer.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(config.ServerConfigPath.c_str());

	map<string, Environment*> environments;
	ReadEnvironment(config.EnvironmentFile.c_str(), environments);

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	std::ifstream inFile(config.SessionFile.c_str());
	TradeSessions::m_SessionJsonString = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	TradeSessions::ParseTradeSessions();

	MdKernel* mdKernel = new MdKernel(config.MdUser.c_str(), config.MdPassword.c_str());
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str(), 100);

	auto environment = environments[config.SelectedEnvironmentName];
	if (environment == nullptr)
	{
		WriteLog(LogLevel::Error, "environment is nullptr, SelectedEnvironmentName:%s", config.SelectedEnvironmentName.c_str());
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return -1;
	}
	CThostFtdcMdApi* mdApi = CThostFtdcMdApiMiddle::CreateFtdcMdApi();
	cout << "API Version:" << mdApi->GetApiVersion() << endl;
	CThostFtdcMdSpiImpl* mdSpi = new CThostFtdcMdSpiImpl(mdApi, mdKernel);
	mdSpi->SetAccountInfo(environment->Accounts[0]);
	mdApi->RegisterSpi(mdSpi);
	for (auto frontInfo : environment->Fronts)
	{
		mdApi->RegisterFront(frontInfo->MdFront);
	}

	mdKernel->SetMdFront(mdFront);
	mdKernel->SetMdSpi(mdSpi);



	mdApi->Init();
	mdFront->Init();
	mdKernel->Start();
	mdFront->Start();
	mdKernel->Join();
	mdFront->Join();

	mdApi->Release();
	mdKernel->Stop();
	mdFront->Stop();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


