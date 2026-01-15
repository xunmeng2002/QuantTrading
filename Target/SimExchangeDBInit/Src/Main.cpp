#include "Mdb.h"
#include "TimeUtility.h"
#include <string.h>

using namespace std;
using namespace mdb;

void InitTradingDay(Mdb* mdb);
void InitExchange(Mdb* mdb);
void InitProduct(Mdb* mdb);
void InitInstrument(Mdb* mdb);

int main()
{
	Mdb* mdb = new Mdb();
	InitTradingDay(mdb);
	InitExchange(mdb);
	InitProduct(mdb);
	InitInstrument(mdb);

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
void InitProduct(Mdb* mdb)
{
	Product* product = new Product();
	strcpy(product->ExchangeID, "CFFEX");
	strcpy(product->ProductID, "IF");
	strcpy(product->ProductName, "IF");
	product->ProductClass = ProductClassType::Future;
	product->VolumeMultiple = 300;
	product->PriceTick = 1;
	product->MaxMarketOrderVolume = 10;
	product->MinMarketOrderVolume = 0;
	product->MaxLimitOrderVolume = 10;
	product->MinLimitOrderVolume = 0;
	strcpy(product->SessionName, "");
	mdb->t_Product->Insert(product);
}
void InitInstrument(Mdb* mdb)
{
	Instrument* instrument = new Instrument();
	strcpy(instrument->ExchangeID, "CFFEX");
	strcpy(instrument->InstrumentID, "IF2512");
	strcpy(instrument->ExchangeInstID, "IF2512");
	strcpy(instrument->InstrumentName, "IF2512");
	strcpy(instrument->ProductID, "IF");
	instrument->ProductClass = ProductClassType::Future;
	instrument->InstrumentClass = InstrumentClassType::Normal;
	instrument->Rank = 0;
	instrument->VolumeMultiple = 300;
	instrument->PriceTick = 1;
	instrument->MaxMarketOrderVolume = 10;
	instrument->MinMarketOrderVolume = 0;
	instrument->MaxLimitOrderVolume = 10;
	instrument->MinLimitOrderVolume = 0;
	strcpy(instrument->SessionName, "");
	mdb->t_Instrument->Insert(instrument);
}

