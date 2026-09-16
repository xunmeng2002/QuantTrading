// 本文件由 ../Templates/Cpp/Config/Config.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdexcept>


namespace QuantTrading::TestStrategyGrid
{
Config Config::instance;
Config::Config()
{

}
Config& Config::GetInstance()
{
	return instance;
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
	AccountId = root["AccountId"].asString();
	ExchangeId = root["ExchangeId"].asString();
	InstrumentId = root["InstrumentId"].asString();
	BarPreces = root["BarPreces"].asString();
	GridStep = root["GridStep"].asDouble();
	GridCount = root["GridCount"].asInt();
	VolumePerGrid = root["VolumePerGrid"].asInt();
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("AccountId:%s\n", AccountId.c_str());
	printf("ExchangeId:%s\n", ExchangeId.c_str());
	printf("InstrumentId:%s\n", InstrumentId.c_str());
	printf("BarPreces:%s\n", BarPreces.c_str());
	printf("GridStep:%f\n", GridStep);
	printf("GridCount:%d\n", GridCount);
	printf("VolumePerGrid:%d\n", VolumePerGrid);
}

}
