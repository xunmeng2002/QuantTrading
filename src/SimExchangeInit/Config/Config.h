#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;

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
	string EnvironmentFile;
	string EnvironmentName;
	string EnvironmentName24;
	string TradingDay;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	
private:
	static Config m_Instance;
};
