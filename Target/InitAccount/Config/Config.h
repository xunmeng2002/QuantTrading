#pragma once
#include <string>
#include <list>
#include "ConfigStructs.h"

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
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	
private:
	static Config m_Instance;
};
