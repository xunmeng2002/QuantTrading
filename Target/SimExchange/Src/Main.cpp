#include "Logger.h"
#include "Config.h"
#include "ServerConfig.h"
#include "Mdb.h"
#include "InitMdbFromDB.h"
#include "DBCommon.h"
#include "DBWriter.h"
#include "DuckDB.h"
#include "SqliteDB.h"
#include "MysqlDB.h"
#include "MdFront.h"
#include "TradeFront.h"
#include "SimExchange.h"
#include <string.h>
#ifdef LINUX
#include <signal.h>
#endif // LINUX

using namespace std;
using namespace mdb;

const char* ConfigName = "SimExchange.json";

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
	InitMdbFromDB::LoadTablesWithoutTradingDay(mdb, initDB);
	initDB->DisConnect();
	delete initDB;

	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);

	TradeFront* tradeFront = new TradeFront(serverConfig.TradeFrontAddress.c_str());
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str());
	auto simExchange = new SimExchange(mdb, tradeFront, mdFront);
	tradeFront->Subscribe(simExchange);
	//mdFront->Subscribe(*);

	simExchange->Init();
	tradeFront->Init();
	//mdFront->Init();
	dbWriter->Start();
	simExchange->Start();
	tradeFront->Start();
	//mdFront->Start();

	dbWriter->Join();
	simExchange->Join();
	tradeFront->Join();
	mdFront->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


