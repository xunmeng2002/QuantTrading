#pragma warning(disable:4819)
#include "ThostFtdcMdApiMiddle.h"
#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
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

const char* sessionConfigFile = "Sessions.json";

int main(int argc, char* argv[])
{
	map<string, Environment*> environments;
	ReadEnvironment(environments);

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();

	std::ifstream inFile(sessionConfigFile);
	TradeSessions::m_SessionJsonString = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	TradeSessions::ParseTradeSessions();

	MdKernel* mdKernel = new MdKernel("MdUser", "MdPassword");
	MdFront* mdFront = new MdFront("tcp://127.0.0.1:10000", 100);

	string environmentName = "SimNow";
	auto environment = environments[environmentName];
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


