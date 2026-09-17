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
#include <DbAdapters/AsyncDbWriter/AsyncDbWriter.h>
#include <DbAdapters/DbInterface/Db.h>
#include <DbAdapters/DuckdbWrapper/DuckdbWrapper.h>
#include <DbAdapters/SqliteWrapper/SqliteWrapper.h>
#include <DbAdapters/MysqlWrapper/MysqlWrapper.h>
#include <DbAdapters/MariadbWrapper/MariadbWrapper.h>
#include <chrono>
#include <iostream>
#include <map>
#include <string.h>
#include <thread>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;
using namespace DbAdapters;
using namespace QuantTrading::SimExchange;
using namespace QuantTrading::SimExchangeInit;
using namespace QuantTrading;

const char* ConfigName = "SimExchangeInit.json";

static Db* CreateDb(const std::string dbType, const std::string dbHost, const std::string dbUser, const std::string dbPassword)
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

	Db* db = CreateDb(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
    QuantTrading::MdbTableRegistry registry(SimExchangeTableList);
	AsyncDbWriter* dbWriter = new AsyncDbWriter(db, &registry);
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

	// 查询完成标志由前置回报驱动；前置不可达或认证失败时它永不置位，此处用上限兜底，
	// 免得进程永久挂起——超时后仍走正常收尾，只是种子库可能不完整，故记 ERROR
	constexpr int QueryWaitTimeoutSeconds = 600;
	int waitedSeconds = 0;
	while (!traderSpi->qryFinished_ && waitedSeconds < QueryWaitTimeoutSeconds)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		++waitedSeconds;
	}
	if (!traderSpi->qryFinished_)
	{
		WriteLog(LogLevel::Error, "Query not finished in %d seconds, seed database may be incomplete. Check front reachability and account.", QueryWaitTimeoutSeconds);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));

	traderApi->Release();
	dbWriter->Stop();
    dbWriter->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


