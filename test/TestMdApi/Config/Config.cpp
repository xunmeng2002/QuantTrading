// 本文件由 ../Templates/Cpp/Config/Config.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdexcept>


namespace QuantTrading::TestMdApi
{
Config Config::instance_;
Config::Config()
{

}
Config& Config::GetInstance()
{
	return instance_;
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
	ServerConfigPath = root["ServerConfigPath"].asString();
	MdUser = root["MdUser"].asString();
	MdPassword = root["MdPassword"].asString();
	for (auto& subValue : root["SubscribeInstruments"])
	{
		SubscribeInstrument* subRecord = new SubscribeInstrument();
		subRecord->ExchangeId = subValue["ExchangeId"].asString();
		subRecord->InstrumentId = subValue["InstrumentId"].asString();
		SubscribeInstruments.push_back(subRecord);
	}
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("ServerConfigPath:%s\n", ServerConfigPath.c_str());
	printf("MdUser:%s\n", MdUser.c_str());
	printf("SubscribeInstruments:[\n");
	for (auto record : SubscribeInstruments)
	{
		printf("{\n");
		printf("\tExchangeId:%s, InstrumentId:%s, \n",
			record->ExchangeId.c_str(), record->InstrumentId.c_str());
		printf("},\n");
	}
	printf("]\n");
}

}
