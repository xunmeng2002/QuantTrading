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
	DbType = root["DbType"].asString();
	DbUser = root["DbUser"].asString();
	DbPassword = root["DbPassword"].asString();
	DbHost = root["DbHost"].asString();
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("DbType:%s\n", DbType.c_str());
	printf("DbUser:%s\n", DbUser.c_str());
	printf("DbPassword:%s\n", DbPassword.c_str());
	printf("DbHost:%s\n", DbHost.c_str());
}

