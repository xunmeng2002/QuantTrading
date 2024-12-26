#include <iostream>
#include "Mdb.h"
#include "DB.h"
#include "DBWriter.h"
#include "InitMdbFromDB.h"
#include "TimeUtility.h"
#include "Logger.h"

using namespace std;
using namespace mdb;

const char* dbHost = "tcp://172.21.59.169:3306/SimExchange";
const char* dbUser = "ams";
const char* dbPasswd = "ams";

static const char* InitTradingDay(Mdb* mdb)
{
	auto currDate = GetLocalDate();
	TradingDay* tradingday = new TradingDay();
	memset(tradingday, 0, sizeof(TradingDay));
	tradingday->PK = 1;
	GetPreTradingDay(currDate.c_str(), tradingday->PreTradingDay);
	GetNextTradingDay(tradingday->PreTradingDay, tradingday->CurrTradingDay);
	mdb->t_TradingDay->Insert(tradingday);
	return tradingday->CurrTradingDay;
}
static void InitExchange(Mdb* mdb)
{
	Exchange* exchange1 = new Exchange();
	Exchange* exchange2 = new Exchange();
	Exchange* exchange3 = new Exchange();
	Exchange* exchange4 = new Exchange();
	Exchange* exchange5 = new Exchange();
	Exchange* exchange6 = new Exchange();
	strcpy(exchange1->ExchangeID, "SHFE");
	strcpy(exchange1->ExchangeName, (const char*)(u8"上海期货交易所"));
	strcpy(exchange2->ExchangeID, "INE");
	strcpy(exchange2->ExchangeName, (const char*)(u8"上海能源中心"));
	strcpy(exchange3->ExchangeID, "CFFEX");
	strcpy(exchange3->ExchangeName, (const char*)(u8"中国金融期货交易所"));
	strcpy(exchange4->ExchangeID, "CZCE");
	strcpy(exchange4->ExchangeName, (const char*)(u8"郑州商品期货交易所"));
	strcpy(exchange5->ExchangeID, "DCE");
	strcpy(exchange5->ExchangeName, (const char*)(u8"大连商品期货交易所"));
	strcpy(exchange6->ExchangeID, "GFE");
	strcpy(exchange6->ExchangeName, (const char*)(u8"广州期货交易所"));

	mdb->t_Exchange->Insert(exchange1);
	mdb->t_Exchange->Insert(exchange2);
	mdb->t_Exchange->Insert(exchange3);
	mdb->t_Exchange->Insert(exchange4);
	mdb->t_Exchange->Insert(exchange5);
	mdb->t_Exchange->Insert(exchange6);
}
static void InitAccount(Mdb* mdb, const DateType tradingDay)
{
	Account* account = new Account();
	memset(account, 0, sizeof(Account));
	strcpy(account->TradingDay, tradingDay);
	strcpy(account->AccountID, "Xunmeng01");
	strcpy(account->AccountName, "Xunmeng01");
	strcpy(account->Password, "123456");
	account->PreBalance = 1000000;
	account->Balance = 1000000;
	account->CloseProfitByDate = 0;
	account->PositionProfitByDate = 0;
	account->PositionProfitByTrade = 0;
	account->PremiumIn = 0;
	account->PremiumOut = 0;
	account->MarketValue = 0;
	mdb->t_Account->Insert(account);
}


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();

	Mdb* mdb = new Mdb();
	DBWriter* dbWriter = new DBWriter(dbHost, dbUser, dbPasswd);
	mdb->Subscribe(dbWriter);
	mdb->SetInitStatus(true);
	
	dbWriter->Start();
	mdb->TruncateTables();

	auto tradingDay = InitTradingDay(mdb);
	InitExchange(mdb);
	InitAccount(mdb, tradingDay);

	this_thread::sleep_for(chrono::seconds(1));
	dbWriter->Stop();
	dbWriter->Join();
	
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}
