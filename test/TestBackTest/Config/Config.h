// 本文件由 ../Templates/Cpp/Config/Config.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace Spark::Core;

namespace QuantTrading::TestBackTest
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
	string AccountId;
	string ExchangeId;
	string InstrumentId;
	
private:
	static Config instance;
};
}
