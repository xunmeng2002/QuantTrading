
#include "Config/Config.h"
#include "DatabaseAdapterFactory.h"
#include "ServerConfig.h"
#include "Mdb.h"
#include "InitMdbFromDb.h"
#include "MdbTableRegistry.h"
#include "SimExchangeTableList.h"
#include "MdSpiImpl.h"
#include "MdFront.h"
#include "ShutdownSignal.h"
#include "TradeFront.h"
#include "SimExchange.h"
#include <QuantTrading/MdApi.h>
#include <Spark/Core/Logger/Logger.h>
#include <DbAdapters/AsyncDbWriter/AsyncDbWriter.h>
#include <DbAdapters/DbInterface/Db.h>
#include <chrono>
#include <string.h>
#include <thread>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;
using namespace DbAdapters;
using namespace QuantTrading;
using namespace QuantTrading::SimExchange;

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
	ShutdownSignal::InstallHandlers();

	Db* initDb = QuantTrading::CreateDatabaseAdapter(config.DbType, config.DbInitHost, config.DbUser, config.DbPassword);
	Db* db = QuantTrading::CreateDatabaseAdapter(config.DbType, config.DbHost, config.DbUser, config.DbPassword);
	if (initDb == nullptr || db == nullptr)
	{
		return Exit();
	}
	Mdb* mdb = new Mdb(SimExchangeTableList);
	QuantTrading::MdbTableRegistry schemaRegistry(SimExchangeTableList);
	AsyncDbWriter* dbWriter = new AsyncDbWriter(db, &schemaRegistry);
	if (!initDb->Connect())
	{
		WriteLog(LogLevel::Error, "InitDb Connect Failed.");
		return Exit();
	}
	InitMdbFromDb::LoadTables(mdb, initDb, SimExchangeTableList);
	initDb->DisConnect();
	delete initDb;

	mdb->Subscribe(dbWriter);
	dbWriter->Subscribe(mdb);


	MdApi* mdApi = MdApi::CreateMdApi();
	MdSpiImpl* mdSpi = new MdSpiImpl(mdApi, config.MdUser, config.MdPassword);
	mdApi->RegisterSpi(mdSpi);
	mdApi->RegisterFront(serverConfig.MdOfferAddress.c_str());
	TradeFront* tradeFront = new TradeFront(serverConfig.TradeFrontAddress.c_str());
	MdFront* mdFront = new MdFront(serverConfig.MdOfferAddress.c_str());
	auto simExchange = new QuantTrading::SimExchange::SimExchange(mdb, tradeFront, mdFront, mdSpi, (MatchModeType)config.MatchMode);
	tradeFront->Subscribe(simExchange);
	//mdFront->Subscribe(*);
	mdSpi->SetSimExchange(simExchange);


	simExchange->Init();
	tradeFront->Init();
	//mdFront->Init();
	mdApi->Init();
	dbWriter->Start();
	simExchange->Start();
	tradeFront->Start();
	//mdFront->Start();

	// 等待退出请求（Ctrl+C / SIGTERM），按依赖序有序关停，替代原先阻塞的 Join 链。
	while (!ShutdownSignal::IsRequested())
	{
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	WriteLog(LogLevel::Info, "Shutdown requested, stopping in dependency order.");

	mdApi->Release();                          // ① 停行情客户端（数据源）
	simExchange->Stop();
	simExchange->Join();                       // ② 撮合线程清空队列
	tradeFront->Stop();
	tradeFront->Join();                        // ③ 交易服务端
	mdFront->Stop();
	mdFront->Join();                           // ④ 行情服务端（未启动，Stop/Join 为无操作）
	dbWriter->Stop();
	dbWriter->Join();                          // ⑤ 刷完剩余落库操作

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}
