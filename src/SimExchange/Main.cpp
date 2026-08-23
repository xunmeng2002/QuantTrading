
#include "Config/Config.h"
#include "ServerConfig.h"
#include "Mdb.h"
#include "InitMdbFromDB.h"
#include "MdbTableRegistry.h"
#include "SimExchangeTableList.h"
#include "MdSpiImpl.h"
#include "MdFront.h"
#include "TradeFront.h"
#include "SimExchange.h"
#include <QuantTrading/MdApi.h>
#include <Spark/Core/Logger/Logger.h>
#include <DBAdapters/AsyncDBWriter/AsyncDBWriter.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;
using namespace mdb;
using namespace spark::core;
using namespace dbadapters;
using namespace quanttrading;
using namespace quanttrading::simexchange;

const char* ConfigName = "SimExchange.json";

int Exit(int code = -1)
{
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	exit(code);
	return code;
}

static DB* CreateDB(const std::string dbType, const std::string dbHost, const std::string dbUser, const std::string dbPassword)
{
    if (dbType == "0")
    {
        return new DuckdbWrapper(dbHost);
    }
    if (dbType == "2")
    {
        return new MysqlWrapper(dbHost);
    }
    if (dbType == "3")
    {
        return new MariadbWrapper(dbHost, dbUser, dbPassword);
    }
    return new SqliteWrapper(dbHost);
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

	DB* initDB = CreateDB(config.DbType, config.DbInitHost, config.DbUser, config.DbPassword);
	DB* db = CreateDB(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
	if (initDB == nullptr || db == nullptr)
	{
		return Exit();
	}
	Mdb* mdb = new Mdb(simexchangeTableList);
	mdb::MdbTableRegistry schemaRegistry(simexchangeTableList);
	AsyncDBWriter* dbWriter = new AsyncDBWriter(db, &schemaRegistry);
	if (!initDB->Connect())
	{
		WriteLog(LogLevel::Error, "InitDB Connect Failed.");
		return Exit();
	}
	InitMdbFromDB::LoadTables(mdb, initDB, simexchangeTableList);
	initDB->DisConnect();
	delete initDB;

	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);


	MdApi* mdApi = MdApi::CreateMdApi();
	MdSpiImpl* MdSpi = new MdSpiImpl(mdApi, config.MdUser, config.MdPassword);
	mdApi->RegisterSpi(MdSpi);
	mdApi->RegisterFront(serverConfig.MdOfferAddress.c_str());
	TradeFront* tradeFront = new TradeFront(serverConfig.TradeFrontAddress.c_str());
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str());
	auto simExchange = new SimExchange(mdb, tradeFront, mdFront, MdSpi, (MatchModeType)config.MatchMode);
	tradeFront->Subscribe(simExchange);
	//mdFront->Subscribe(*);
	MdSpi->SetSimExchange(simExchange);


	simExchange->Init();
	tradeFront->Init();
	//mdFront->Init();
	mdApi->Init();
	dbWriter->Start();
	simExchange->Start();
	tradeFront->Start();
	//mdFront->Start();

	dbWriter->Join();
	simExchange->Join();
	tradeFront->Join();
	mdFront->Join();
	mdApi->Join(); 

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}
