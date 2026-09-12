#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


namespace quanttrading::teststrategygrid
{
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
	AccountID = root["AccountID"].asString();
	ExchangeID = root["ExchangeID"].asString();
	InstrumentID = root["InstrumentID"].asString();
	BarPreces = root["BarPreces"].asString();
	GridStep = root["GridStep"].asDouble();
	GridCount = root["GridCount"].asInt();
	VolumePerGrid = root["VolumePerGrid"].asInt();
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("AccountID:%s\n", AccountID.c_str());
	printf("ExchangeID:%s\n", ExchangeID.c_str());
	printf("InstrumentID:%s\n", InstrumentID.c_str());
	printf("BarPreces:%s\n", BarPreces.c_str());
	printf("GridStep:%f\n", GridStep);
	printf("GridCount:%d\n", GridCount);
	printf("VolumePerGrid:%d\n", VolumePerGrid);
}

}
