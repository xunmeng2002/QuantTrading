#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


namespace quanttrading::backtest
{
// BarPreces 与 Parquet Preces 列同格式（<n><s|m|h|d>，如 1m/5m/15m/1h/1d），
// 拆解为撮合引擎的精度枚举与周期数：s→Second、m→Minute、h→Minute×60、d→Day。
static bool ParseBarPreces(const string& barPreces, BarPrecesType& barPrecesType, int& barPeriod)
{
	if (barPreces.size() < 2)
	{
		return false;
	}
	const char unit = barPreces.back();
	const int count = atoi(barPreces.substr(0, barPreces.size() - 1).c_str());
	if (count <= 0)
	{
		return false;
	}
	switch (unit)
	{
		case 's':
			barPrecesType = BarPrecesType::Second;
			break;
		case 'm':
		case 'h':
			barPrecesType = BarPrecesType::Minute;
			barPeriod = unit == 'h' ? count * 60 : count;
			return true;
		case 'd':
			barPrecesType = BarPrecesType::Day;
			break;
		default:
			return false;
	}
	barPeriod = count;
	return true;
}

Config Config::m_Instance;
Config::Config()
{

}
Config& Config::GetInstance()
{
	return m_Instance;
}
void Config::Load(const char* fileName)
{
	Json::Reader reader;
	Json::Value root;
	std::ifstream inFile(fileName, std::ios::binary);
	if (!reader.parse(inFile, root))
	{
		std::string errorMsg = std::string("Parse Config Failed. FileName:") + fileName;
		std::cout << errorMsg << std::endl;
		throw std::logic_error(errorMsg);
	}
	else
	{
		std::cout << "Parse Config Success." << std::endl;
	}
	inFile.close();
	
	MatchMode = root["MatchMode"].asInt();
	BarPreces = root["BarPreces"].asString();
	if (BarPreces.empty())
	{
		BarPreces = "1m";
		std::cout << "BarPreces not set, fallback to 1m." << std::endl;
	}
	if (!ParseBarPreces(BarPreces, BarPrecesValue, BarPeriod))
	{
		const std::string errorMsg = std::string("Invalid BarPreces, expect <n><s|m|h|d> e.g. 1m/5m/1h/1d. BarPreces:") + BarPreces;
		std::cout << errorMsg << std::endl;
		throw std::logic_error(errorMsg);
	}
	MdDataPath = root["MdDataPath"].asString();
	DumpPath = root["DumpPath"].asString();
	SessionFile = root["SessionFile"].asString();
	StartTradingDay = root["StartTradingDay"].asString();
	EndTradingDay = root["EndTradingDay"].asString();
	DbType = root["DbType"].asString();
	DbUser = root["DbUser"].asString();
	DbPassword = root["DbPassword"].asString();
	DbHost = root["DbHost"].asString();
	DbInitHost = root["DbInitHost"].asString();
	Print();
}



void Config::Print()
{
	printf("MatchMode:%d\n", MatchMode);
	printf("BarPreces:%s (PrecesValue:%d, Period:%d)\n", BarPreces.c_str(), static_cast<int>(BarPrecesValue), BarPeriod);
	printf("MdDataPath:%s\n", MdDataPath.c_str());
	printf("DumpPath:%s\n", DumpPath.c_str());
	printf("SessionFile:%s\n", SessionFile.c_str());
	printf("StartTradingDay:%s\n", StartTradingDay.c_str());
	printf("EndTradingDay:%s\n", EndTradingDay.c_str());
	printf("DbType:%s\n", DbType.c_str());
	printf("DbUser:%s\n", DbUser.c_str());
	printf("DbHost:%s\n", DbHost.c_str());
	printf("DbInitHost:%s\n", DbInitHost.c_str());
}

}
