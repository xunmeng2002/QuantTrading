#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace spark::core;

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
	string SessionFile;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	string DbInitHost;
	
private:
	static Config m_Instance;
};
