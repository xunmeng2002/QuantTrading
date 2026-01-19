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
#include "DBCommon.h"
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

int Exit(int code = -1)
{
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	exit(code);
	return code;
}

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
	ReadEnvironment(environments, config.EnvironmentFile.c_str());
	auto environment = GetEnvironment(environments, config.EnvironmentName, config.EnvironmentName24);
	if (environment == nullptr)
	{
		return Exit();
	}

	std::ifstream inFile(config.SessionFile.c_str());
	TradeSessions::m_SessionJsonString = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	TradeSessions::ParseTradeSessions();

	
	DB* initDB = CreateDB(config.DbType, config.DbInitHost, config.DbUser, config.DbPassword);
	DB* db = CreateDB(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
	if (initDB == nullptr || db == nullptr)
	{
		return Exit();
	}
	DBWriter* dbWriter = new DBWriter(db);
	Mdb* mdb = new Mdb();
	if (!initDB->Connect())
	{
		WriteLog(LogLevel::Error, "InitDB Connect Failed.");
		return Exit();
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


