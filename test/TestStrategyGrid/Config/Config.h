// 本文件由 ../Templates/Cpp/Config/Config.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <string>
#include <list>

using std::string;
using namespace spark::core;

namespace quanttrading::teststrategygrid
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
	string AccountID;
	string ExchangeID;
	string InstrumentID;
	string BarPreces;
	double GridStep;
	int GridCount;
	int VolumePerGrid;
	
private:
	static Config instance;
};
}
