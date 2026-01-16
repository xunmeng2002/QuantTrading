#include "Logger.h"
#include "Config.h"
#include "TimeUtility.h"
#include "Mdb.h"
#include "DBCommon.h"
#include "DBWriter.h"
#include "DuckDB.h"
#include "SqliteDB.h"
#include "MysqlDB.h"
#include <iostream>
#include <map>
#include <string.h>

using namespace std;
using namespace mdb;

const char* ConfigName = "InitAccount.json";

int main(int argc, char* argv[])
{
	auto& config = Config::GetInstance();
	config.Load(ConfigName);

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
	Logger::GetInstance().Start();

	DB* db = CreateDB(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
	DBWriter* dbWriter = new DBWriter(db);
	Mdb* mdb = new Mdb();
	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);

	dbWriter->Start();




	dbWriter->Stop();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


