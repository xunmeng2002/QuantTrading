// 本文件由 ../Templates/Cpp/Config/Config.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace Spark::Core;

namespace QuantTrading::MdOffer
{
class Config
{
	Config();
public:
	static Config& GetInstance();
	void Load(const char* fileName);
	void Print();
	
public:
	int LogLevel;
	string ServerConfigPath;
	string EnvironmentFile;
	string EnvironmentName;
	string EnvironmentName24;
	string SessionFile;
	string DbType;
	string DbUser;
	string DbPassword;
	string DbHost;
	string MdUserId;
	string MdPassword;
	std::list<SubscribeInstrument*> SubscribeInstruments;
	
private:
	static Config instance_;
};
}
