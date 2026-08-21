#include "Mdb.h"
#include "TableList.h"
#include "MdbTableRegistry.h"
#include "BackTestTableList.h"
#include "Init.h"
#include "Config/Config.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <DBAdapters/AsyncDBWriter/AsyncDBWriter.h>
#include <DBAdapters/DBInterface/DB.h>
#include <DBAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DBAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DBAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DBAdapters/MariadbWrapper/MariadbWrapper.h>
#include <iostream>
#include <map>
#include <string.h>

using namespace std;
using namespace mdb;
using namespace spark::core;
using namespace dbadapters;

const char* ConfigName = "BackTestInit.json";

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
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
    Logger::GetInstance().Start();

    DB* db = CreateDB(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
    mdb::MdbTableRegistry registry(BackTestTableList);
    AsyncDBWriter* dbWriter = new AsyncDBWriter(db, &registry);
    Mdb* mdb = new Mdb(BackTestTableList);
    mdb->Subscribe(dbWriter);
    dbWriter->Subscribe(mdb);
    dbWriter->Start();

    Init(mdb, config.TradingDay, config.AccountID, config.Password);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    dbWriter->Stop();
    dbWriter->Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();

	return 0;
}
