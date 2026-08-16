#pragma warning(disable:4819)
#include "ThostFtdcTraderApiMiddle.h"
#include "ThostFtdcTraderSpiImpl.h"
#include "Environment.h"
#include "Mdb.h"
#include "TableList.h"
#include "MdbTableRegistry.h"
#include "SimExchangeTableList.h"
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

const char* ConfigName = "SimExchangeInit.json";

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

	map<string, Environment*> environments;
	ReadEnvironment(environments, config.EnvironmentFile.c_str());
	auto environment = GetEnvironment(environments, config.EnvironmentName, config.EnvironmentName24);
	if (environment == nullptr)
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
		return -1;
	}

	DB* db = CreateDB(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
    mdb::MdbTableRegistry registry(SimExchangeTableList);
	AsyncDBWriter* dbWriter = new AsyncDBWriter(db, &registry);
	Mdb* mdb = new Mdb(SimExchangeTableList);
	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);

	Init(mdb, environment->Accounts[0], config.TradingDay);

	CThostFtdcTraderApi* traderApi = CThostFtdcTraderApiMiddle::CreateFtdcTraderApi();
	cout << "API Version:" << traderApi->GetApiVersion() << endl;
	CThostFtdcTraderSpiImpl* traderSpi = new CThostFtdcTraderSpiImpl(traderApi, mdb);
	traderSpi->SetAccountInfo(environment->Accounts[0]);
	traderSpi->SetNewPassword("");
	traderApi->RegisterSpi(traderSpi);
	for (auto frontInfo : environment->Fronts)
	{
		traderApi->RegisterFront(frontInfo->TradeFront);
	}
	traderApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->Init();
	dbWriter->Start();

	while (!traderSpi->m_QryFinished)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));

	traderApi->Release();
	dbWriter->Stop();
    dbWriter->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


