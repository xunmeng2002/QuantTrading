#include "Init.h"
#include "TimeUtility.h"

using namespace std;
using namespace mdb;


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
	Exchange* exchange6 = new Exchange();

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
	strcpy(exchange6->ExchangeID, "GFEX");
	strcpy(exchange6->ExchangeName, (const char*)(u8"广州期货交易所"));

	mdb->t_Exchange->Insert(exchange1);
	mdb->t_Exchange->Insert(exchange2);
	mdb->t_Exchange->Insert(exchange3);
	mdb->t_Exchange->Insert(exchange4);
	mdb->t_Exchange->Insert(exchange5);
	mdb->t_Exchange->Insert(exchange6);
}
void InitHotInstrument(Mdb* mdb)
{

}
void InitProduct(Mdb* mdb)
{

}
void InitInstrument(Mdb* mdb)
{

}
void InitPrimaryAccount(Mdb* mdb, AccountInfo* accountInfo)
{
	PrimaryAccount* record1 = new PrimaryAccount();
	memset(record1, 0, sizeof(PrimaryAccount));
	strcpy(record1->PrimaryAccountID, accountInfo->InvestorID);
	strcpy(record1->PrimaryAccountName, accountInfo->Phone);
	record1->AccountClass = AccountClassType::Option;
	strcpy(record1->Password, accountInfo->Password);
	record1->OfferID = 1;
	record1->IsAllowLogin = true;
	record1->IsSimulateAccount = true;
	record1->LoginStatus = LoginStatusType::NotLog;
	record1->InitStatus = InitStatusType::Initialized;
	mdb->t_PrimaryAccount->Insert(record1);
}
Account* InitAccount(Mdb* mdb, AccountInfo* accountInfo)
{
	Account* account = new Account();
	strcpy(account->AccountID, accountInfo->InvestorID);
	strcpy(account->AccountName, accountInfo->Phone);
	account->AccountType = AccountTypeType::Primary;
	account->AccountStatus = AccountStatusType::Normal;
	strcpy(account->Password, accountInfo->Password);
	account->TradeGroupID = 1;
	account->RiskGroupID = 1;
	account->CommissionGroupID = 1;
	mdb->t_Account->Insert(account);
	return account;
}
void InitCapital(Mdb* mdb, Account* account)
{
	Capital* capital = new Capital();
	memset(capital, 0, sizeof(Capital));
	strcpy(capital->TradingDay, GetLocalDate().c_str());
	strcpy(capital->AccountID, account->AccountID);
	capital->AccountType = account->AccountType;
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
void InitPosition(Mdb* mdb, Account* account)
{
}
void InitPositionDetail(Mdb* mdb, Account* account)
{
}
void InitOrder(Mdb* mdb, Account* account)
{
}
void InitTrade(Mdb* mdb, Account* account)
{
}

//目前Exchange，Product，Instrument由Simnow提供，这里不做Init
void Init(mdb::Mdb* mdb, AccountInfo* accountInfo)
{
	InitTradingDay(mdb);
	InitHotInstrument(mdb);
	InitPrimaryAccount(mdb, accountInfo);
	auto account = InitAccount(mdb, accountInfo);
	InitCapital(mdb, account);
	InitPosition(mdb, account);
	InitPositionDetail(mdb, account);
	InitOrder(mdb, account);
	InitTrade(mdb, account);
}