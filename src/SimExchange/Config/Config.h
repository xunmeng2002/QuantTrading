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
	int MatchMode;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	string DbInitHost;
	string MdUser;
	string MdPassword;
	
private:
	static Config m_Instance;
};
