#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


namespace quanttrading::testmdoffer
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
	ServerConfigPath = root["ServerConfigPath"].asString();
	MdUser = root["MdUser"].asString();
	MdPassword = root["MdPassword"].asString();
	for (auto& subValue : root["SubscribeInstruments"])
	{
		SubscribeInstrument* subRecord = new SubscribeInstrument();
		subRecord->ExchangeID = subValue["ExchangeID"].asString();
		subRecord->InstrumentID = subValue["InstrumentID"].asString();
		SubscribeInstruments.push_back(subRecord);
	}
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("ServerConfigPath:%s\n", ServerConfigPath.c_str());
	printf("MdUser:%s\n", MdUser.c_str());
	printf("MdPassword:%s\n", MdPassword.c_str());
	printf("SubscribeInstruments:[\n");
	for (auto record : SubscribeInstruments)
	{
		printf("{\n");
		printf("\tExchangeID:%s, InstrumentID:%s, \n",
			record->ExchangeID.c_str(), record->InstrumentID.c_str());
		printf("},\n");
	}
	printf("]\n");
}

}
