#include "Logger.h"
#include "Config.h"
#include "ServerConfig.h"
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

	auto simExchange = new SimExchange(config);

	simExchange->Start();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


