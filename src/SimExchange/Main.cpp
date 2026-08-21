#include <Spark/Core/Logger/Logger.h>
#include "Config/Config.h"
#include "ServerConfig.h"
#include "Mdb.h"
#include "InitMdbFromDB.h"
#include "MdbTableRegistry.h"
#include "SimExchangeTableList.h"
#include <DBAdapters/AsyncDBWriter/AsyncDBWriter.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
#include "MdFront.h"
#include "TradeFront.h"
#include "SimExchange.h"
#include "InnerMdApi.h"
#include "InnerMdSpiImpl.h"
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;
using namespace mdb;
using namespace spark::core;
using namespace dbadapters;

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
	Mdb* mdb = new Mdb(SimExchangeTableList);
	mdb::MdbTableRegistry schemaRegistry(SimExchangeTableList);
	AsyncDBWriter* dbWriter = new AsyncDBWriter(db, &schemaRegistry);
	if (!initDB->Connect())
	{
		WriteLog(LogLevel::Error, "InitDB Connect Failed.");
		return Exit();
	}
	InitMdbFromDB::LoadTables(mdb, initDB, SimExchangeTableList);
	initDB->DisConnect();
	delete initDB;

	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);


	InnerMdApi* innerMdApi = new InnerMdApi();
	InnerMdSpiImpl* innerMdSpi = new InnerMdSpiImpl(innerMdApi, config.MdUser, config.MdPassword);
	innerMdApi->RegisterSpi(innerMdSpi);
	innerMdApi->RegisterFront(serverConfig.MdOfferAddress.c_str());
	TradeFront* tradeFront = new TradeFront(serverConfig.TradeFrontAddress.c_str());
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str());
	auto simExchange = new SimExchange(mdb, tradeFront, mdFront, innerMdSpi, (MatchModeType)config.MatchMode);
	tradeFront->Subscribe(simExchange);
	//mdFront->Subscribe(*);
	innerMdSpi->SetSimExchange(simExchange);


	simExchange->Init();
	tradeFront->Init();
	//mdFront->Init();
	innerMdApi->Init();
	dbWriter->Start();
	simExchange->Start();
	tradeFront->Start();
	//mdFront->Start();

	dbWriter->Join();
	simExchange->Join();
	tradeFront->Join();
	mdFront->Join();
	innerMdApi->Join(); 

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}
