#pragma warning(disable:4819)
#include "ThostFtdcMdApiMiddle.h"
#include "ThostFtdcMdSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include "Config/Config.h"
#include "ServerConfig.h"
#include "Environment.h"
#include <Spark/Core/Utility/TimeUtility.h>
#include "Mdb.h"
#include "InitMdbFromDB.h"
#include "MdbTableRegistry.h"
#include "MdOfferTableList.h"
#include <DBAdapters/DBInterface/DB.h>
#include <DBAdapters/DBInterface/TypedTable.h>
#include <DBAdapters/DBInterface/SchemaRegistry.h>
#include <DBAdapters/AsyncDBWriter/AsyncDBWriter.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
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
using namespace spark::core;
using namespace dbadapters;

const char* ConfigName = "MdOffer.json";

const char* initSqliteDBName = "./MdOfferInit.db";
const char* sqliteDBName = "./MdOffer.db";
const char* duckdbDBName = "./MdOffer.duckdb";
const char* mysqlHost = "mysqlx://sams:sams@localhost:33060/MdOffer";
const char* mariadbHost = "tcp://localhost:3306/MdOffer";
const char* mariadbUser = "sams";
const char* mariadbPassword = "sams";

static DB* CreateDataDb(const Config& config)
{
    if (config.DbType == "0")
    {
        return new DuckdbWrapper(config.DbHost);
    }
    if (config.DbType == "2")
    {
        return new MysqlWrapper(config.DbHost);
    }
    if (config.DbType == "3")
    {
        return new MariadbWrapper(config.DbHost, config.DbUser, config.DbPassword);
    }
    return new SqliteWrapper(config.DbHost);
}


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

    DB* db = CreateDataDb(config);
    SqliteWrapper* initDB = new SqliteWrapper(config.DbInitHost.empty() ? initSqliteDBName : config.DbInitHost);
	
    Mdb* mdb = new Mdb(MdOfferTableList);
    mdb::MdbTableRegistry schemaRegistry(MdOfferTableList);
    AsyncDBWriter* dbWriter = new AsyncDBWriter(db, &schemaRegistry);
    mdb->Subscribe(dbWriter);
    dbWriter->Subscribe(mdb);

	
	InitMdbFromDB::LoadMdUserTable(mdb, initDB);
	InitMdbFromDB::LoadExchangeTable(mdb, initDB);
	InitMdbFromDB::LoadInstrumentTable(mdb, initDB);
	initDB->DisConnect();
	delete initDB;

    mdb->t_MdUser->Insert(new MdUser("MdUser", "", "123456"));

	MdKernel* mdKernel = new MdKernel(mdb);
	dbWriter->Subscribe(mdKernel);
	MdFront* mdFront = new MdFront(IOModelType::Select, serverConfig.MdOfferAddress.c_str(), 100);

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

