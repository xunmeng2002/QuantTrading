#pragma warning(disable: 4311)
#include "Config.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


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
	
	LogLevel = root["LogLevel"].asInt();
	MdDataPath = root["MdDataPath"].asString();
	CsvPath = root["CsvPath"].asString();
	DumpPath = root["DumpPath"].asString();
	SessionFile = root["SessionFile"].asString();
	MarketDataType = root["MarketDataType"].asString();
	StartTradingDay = root["StartTradingDay"].asString();
	EndTradingDay = root["EndTradingDay"].asString();
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("MdDataPath:%s\n", MdDataPath.c_str());
	printf("CsvPath:%s\n", CsvPath.c_str());
	printf("DumpPath:%s\n", DumpPath.c_str());
	printf("SessionFile:%s\n", SessionFile.c_str());
	printf("MarketDataType:%s\n", MarketDataType.c_str());
	printf("StartTradingDay:%s\n", StartTradingDay.c_str());
	printf("EndTradingDay:%s\n", EndTradingDay.c_str());
}

