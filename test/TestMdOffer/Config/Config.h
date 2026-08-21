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
	string MdUser;
	string MdPassword;
	std::list<SubscribeInstrument*> SubscribeInstruments;
	
private:
	static Config m_Instance;
};
