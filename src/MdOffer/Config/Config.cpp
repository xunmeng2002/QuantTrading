#pragma warning(disable: 4311)
#include "Config.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


namespace quanttrading::mdoffer
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
	EnvironmentFile = root["EnvironmentFile"].asString();
	EnvironmentName = root["EnvironmentName"].asString();
	EnvironmentName24 = root["EnvironmentName24"].asString();
	SessionFile = root["SessionFile"].asString();
	DbType = root["DbType"].asString();
	DbUser = root["DbUser"].asString();
	DbPassword = root["DbPassword"].asString();
	DbHost = root["DbHost"].asString();
	MdUserID = root["MdUserID"].asString();
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
	printf("EnvironmentFile:%s\n", EnvironmentFile.c_str());
	printf("EnvironmentName:%s\n", EnvironmentName.c_str());
	printf("EnvironmentName24:%s\n", EnvironmentName24.c_str());
	printf("SessionFile:%s\n", SessionFile.c_str());
	printf("DbType:%s\n", DbType.c_str());
	printf("DbUser:%s\n", DbUser.c_str());
	printf("DbHost:%s\n", DbHost.c_str());
	printf("MdUserID:%s\n", MdUserID.c_str());
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
