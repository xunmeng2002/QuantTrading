#include "Mdb.h"
#include "TimeUtility.h"
#include <string.h>

using namespace std;
using namespace mdb;

void InitTradingDay(Mdb* mdb);
void InitExchange(Mdb* mdb);
void InitAccount(Mdb* mdb);
void InitCapital(Mdb* mdb);

int main()
{
	Mdb* mdb = new Mdb();
	InitTradingDay(mdb);
	InitExchange(mdb);
	InitAccount(mdb);
	InitCapital(mdb);

	mdb->Dump("./Csv");

	return 0;
}
void InitTradingDay(Mdb* mdb)
{
	TradingDay* tradingDay = new TradingDay;
	tradingDay->PK = 1;
	strcpy(tradingDay->CurrTradingDay, GetLocalDate().c_str());
	GetPreTradingDay(tradingDay->CurrTradingDay, tradingDay->PreTradingDay);
	mdb->t_TradingDay->Insert(tradingDay);
}
void InitExchange(Mdb* mdb)
{
	Exchange* exchange1 = new Exchange();
	Exchange* exchange2 = new Exchange();
	Exchange* exchange3 = new Exchange();
	Exchange* exchange4 = new Exchange();
	Exchange* exchange5 = new Exchange();

	strcpy(exchange1->ExchangeID, "CFFEX");
	strcpy(exchange1->ExchangeName, (const char*)(u8"中国金融期货交易所"));
	strcpy(exchange2->ExchangeID, "SHFE");
	strcpy(exchange2->ExchangeName, (const char*)(u8"上海期货交易所"));
	strcpy(exchange3->ExchangeID, "DCE");
	strcpy(exchange3->ExchangeName, (const char*)(u8"大连商品交易所"));
	strcpy(exchange4->ExchangeID, "CZCE");
	strcpy(exchange4->ExchangeName, (const char*)(u8"郑州商品交易所"));
	strcpy(exchange5->ExchangeID, "INE");
	strcpy(exchange5->ExchangeName, (const char*)(u8"上海国际能源交易中心"));

	mdb->t_Exchange->Insert(exchange1);
	mdb->t_Exchange->Insert(exchange2);
	mdb->t_Exchange->Insert(exchange3);
	mdb->t_Exchange->Insert(exchange4);
	mdb->t_Exchange->Insert(exchange5);
}
void InitAccount(Mdb* mdb)
{
	Account* account = new Account();
	strcpy(account->AccountID, "18511899894");
	strcpy(account->AccountName, "18511899894");
	account->AccountType = AccountTypeType::Primary;
	account->AccountStatus = AccountStatusType::Normal;
	strcpy(account->Password, "123456");
	account->TradeGroupID = 1;
	account->RiskGroupID = 1;
	account->CommissionGroupID = 1;
	mdb->t_Account->Insert(account);
}
void InitCapital(Mdb* mdb)
{
	Capital* capital = new Capital();
	memset(capital, 0, sizeof(Capital));
	strcpy(capital->TradingDay, GetLocalDate().c_str());
	strcpy(capital->AccountID, "18511899894");
	capital->AccountType = AccountTypeType::Primary;
	capital->Balance = 0;
	capital->PreBalance = 0;
	capital->Available = 0;
	capital->MarketValue = 0;
	capital->CashIn = 0;
	capital->CashOut = 0;
	capital->Margin = 0;
	capital->Commission = 0;
	capital->FrozenCash = 0;
	capital->FrozenMargin = 0;
	capital->FrozenCommission = 0;
	capital->CloseProfitByDate = 0;
	capital->CloseProfitByTrade = 0;
	capital->PositionProfitByDate = 0;
	capital->PositionProfitByTrade = 0;
	capital->Deposit = 0;
	capital->Withdraw = 0;
	mdb->t_Capital->Insert(capital);
}

