#include "Logger.h"
#include "Config.h"
#include "ServerConfig.h"
#include "MdFront.h"
#include "TradeFront.h"
#include "SimExchange.h"
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;

const char* ConfigName = "SimExchange.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(config.ServerConfigPath.c_str());

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	TradeFront* tradeFront = new TradeFront(serverConfig.SETradeFrontAddress.c_str());
	MdFront* mdFront = new MdFront(serverConfig.SEMdOfferAddress.c_str());
	auto simExchange = new SimExchange(config, tradeFront, mdFront);
	tradeFront->Subscribe(simExchange);
	mdFront->Subscribe(simExchange);

	simExchange->Init();
	tradeFront->Init();
	mdFront->Init();
	simExchange->Start();
	tradeFront->Start();
	mdFront->Start();

	simExchange->Join();
	tradeFront->Join();
	mdFront->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


