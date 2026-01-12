#pragma warning(disable:4819)
#include "ThostFtdcMdApiMiddle.h"
#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
#include "Config.h"
#include "ServerConfig.h"
#include "Environment.h"
#include "TimeUtility.h"
#include "Mdb.h"
#include "InitMdbFromDB.h"
#include "DBWriter.h"
#include "DuckDB.h"
#include "SqliteDB.h"
#include "MysqlDB.h"
#include "MdFront.h"
#include "MdKernel.h"
#include "TradeSession.h"
#include <iostream>
#include <fstream>
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;
using namespace mdb;

const char* ConfigName = "MdOffer.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);
	auto& serverConfig = ServerConfig::GetInstance();
	serverConfig.Load(config.ServerConfigPath.c_str());

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	map<string, Environment*> environments;
	ReadEnvironment(config.EnvironmentFile.c_str(), environments);
	auto environment = GetEnvironment(environments, config.EnvironmentName, config.EnvironmentName24);
	if (environment == nullptr)
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return -1;
	}

	std::ifstream inFile(config.SessionFile.c_str());
	TradeSessions::m_SessionJsonString = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	TradeSessions::ParseTradeSessions();

	
	DB* mdDB = nullptr;
	DB* initDB = nullptr;
	auto dbType = DBTypeType(config.DbType[0]);
	switch (dbType)
	{
	case DBTypeType::DuckDB:
		mdDB = new DuckDB(config.DbMdHost);
		initDB = new DuckDB(config.DbInitHost);
		break;
	case DBTypeType::SqliteDB:
		mdDB = new SqliteDB(config.DbMdHost);
		initDB = new SqliteDB(config.DbInitHost);
		break;
	case DBTypeType::MysqlDB:
		mdDB = new MysqlDB(config.DbMdHost, config.DbUser, config.DbPassword);
		initDB = new MysqlDB(config.DbInitHost, config.DbUser, config.DbPassword);
		break;
	default:
		WriteLog(LogLevel::Error, "Unsupported DBType:%c", config.DbType[0]);
		return -1;
	}
	DBWriter* dbWriter = new DBWriter(mdDB);
	Mdb* mdb = new Mdb();
	if (!initDB->Connect())
	{
		WriteLog(LogLevel::Error, "InitDB Connect Failed.");
		return -1;
	}
	InitMdbFromDB::LoadExchangeTable(mdb, initDB);
	InitMdbFromDB::LoadInstrumentTable(mdb, initDB);
	initDB->DisConnect();
	delete initDB;

	mdb->Subscribe(dbWriter);
	MdKernel* mdKernel = new MdKernel(mdb);
	dbWriter->Subscribe(mdKernel);
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str(), 100);

	CThostFtdcMdApi* mdApi = CThostFtdcMdApiMiddle::CreateFtdcMdApi();
	cout << "API Version:" << mdApi->GetApiVersion() << endl;
	CThostFtdcMdSpiImpl* mdSpi = new CThostFtdcMdSpiImpl(mdApi, mdKernel);
	mdSpi->SetAccountInfo(environment->Accounts[0]);
	mdApi->RegisterSpi(mdSpi);
	for (auto frontInfo : environment->Fronts)
	{
		mdApi->RegisterFront(frontInfo->MdFront);
	}

	mdKernel->SetMdFront(mdFront);
	mdKernel->SetMdSpi(mdSpi);



	mdApi->Init();
	mdFront->Init();
	dbWriter->Start();
	mdKernel->Start();
	mdFront->Start();

	mdFront->Join();
	mdKernel->Join();
	dbWriter->Join();

	mdApi->Release();
	mdFront->Stop();
	mdKernel->Stop();
	dbWriter->Stop();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


