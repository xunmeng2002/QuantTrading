#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace spark::core;

namespace quanttrading::backtest
{
class Config
{
	Config();
public:
	static Config& GetInstance();
	void Load(const char* fileName);
	void Print();
	
public:
	int MatchMode;
	string MdDataPath;
	string DumpPath;
	string SessionFile;
	string StartTradingDay;
	string EndTradingDay;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	string DbInitHost;
	
private:
	static Config m_Instance;
};
}
