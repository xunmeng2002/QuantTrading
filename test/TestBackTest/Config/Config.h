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
	string AccountID;
	string ExchangeID;
	string InstrumentID;
	
private:
	static Config m_Instance;
};
