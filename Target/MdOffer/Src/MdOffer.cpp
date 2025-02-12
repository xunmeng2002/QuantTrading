#pragma warning(disable:4819)
#include "ThostFtdcMdApiMiddle.h"
#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
#include "CtpAccountInfo.h"
#include <iostream>
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX



using namespace std;

#ifdef LINUX
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");
	printf("back to main\n");
}
#endif // LINUX


int main(int argc, char* argv[])
{
	map<string, CtpAccountInfo*> ctpAccountInfos;
	ReadCtpAccountInfo(ctpAccountInfos);

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel::Info, LogLevel::Info);
	Logger::GetInstance().Start();

	string userID = "229140";
	CThostFtdcMdApi* mdApi = CThostFtdcMdApiMiddle::CreateFtdcMdApi();
	cout << "API Version:" << mdApi->GetApiVersion() << endl;
	CThostFtdcMdSpiImpl* mdSpi = new CThostFtdcMdSpiImpl(mdApi);
	mdSpi->SetCtpAccountInfo(ctpAccountInfos[userID]);
	mdApi->RegisterSpi(mdSpi);
	for (auto& mdFrontAddr : ctpAccountInfos[userID]->MdFrontAddrs)
	{
		mdApi->RegisterFront((char*)mdFrontAddr.c_str());
	}
	mdApi->Init();

#ifdef LINUX
	struct sigaction act;
	act.sa_handler = sigusr1_handler;
	act.sa_flags = SA_NODEFER;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		perror("fail to set handler for SIGUSR1");
		exit(1);
	}
#endif // LINUX
	std::this_thread::sleep_for(std::chrono::seconds(30));

	mdApi->Release();
	//mdApi->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


