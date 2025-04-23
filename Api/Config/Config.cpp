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
		std::cout << "Parse Config Failed." << std::endl;
		std::string s;
		inFile >> s;
		std::cout << s << std::endl;
		throw std::logic_error("Parse Config Failed.");
	}
	else
	{
		std::cout << "Parse Config Success." << std::endl;
	}
	inFile.close();
	
	LogLevel = root["LogLevel"].asInt();
	ProtocolType = root["ProtocolType"].asString();
	Print();
}



void Config::Print()
{
	printf("LogLevel:%d\n", LogLevel);
	printf("ProtocolType:%s\n", ProtocolType.c_str());
}

