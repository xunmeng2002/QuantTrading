#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace spark::core;

namespace quanttrading::backtestinit
{
class Config
{
	Config();
public:
	static Config& GetInstance();
	void Load(const char* fileName);
	void Print();
	
public:
	int LogLevel;
	string ServerConfigPath;
	string TradingDay;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	string AccountID;
	string Password;
	
private:
	static Config m_Instance;
};
}
