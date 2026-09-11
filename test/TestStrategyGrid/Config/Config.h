#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace spark::core;

namespace quanttrading::teststrategygrid
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
	string SessionFile;
	string AccountID;
	string ExchangeID;
	string InstrumentID;
	string BarPreces;
	double GridStep;
	int GridCount;
	int VolumePerGrid;
	
private:
	static Config m_Instance;
};
}
