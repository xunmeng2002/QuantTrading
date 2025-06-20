#include "InitMdbFromDB.h"
#include <list>

using namespace std;

namespace mdb
{
	void InitMdbFromDB::LoadTablesWithTradingDay(Mdb* mdb, DB* db, const DateType& tradingDay)
	{
	}
	void InitMdbFromDB::LoadTablesWithoutTradingDay(Mdb* mdb, DB* db)
	{
	}

	void InitMdbFromDB::LoadTradingDayTable(Mdb* mdb, DB* db)
	{
		list<TradingDay*> records;
		db->SelectTradingDay(records);
		for (auto record : records)
		{
			mdb->t_TradingDay->Insert(record);
		}
	}
	void InitMdbFromDB::LoadExchangeTable(Mdb* mdb, DB* db)
	{
		list<Exchange*> records;
		db->SelectExchange(records);
		for (auto record : records)
		{
			mdb->t_Exchange->Insert(record);
		}
	}
	void InitMdbFromDB::LoadProductTable(Mdb* mdb, DB* db)
	{
		list<Product*> records;
		db->SelectProduct(records);
		for (auto record : records)
		{
			mdb->t_Product->Insert(record);
		}
	}
	void InitMdbFromDB::LoadInstrumentTable(Mdb* mdb, DB* db)
	{
		list<Instrument*> records;
		db->SelectInstrument(records);
		for (auto record : records)
		{
			mdb->t_Instrument->Insert(record);
		}
	}
	void InitMdbFromDB::LoadOrderTable(Mdb* mdb, DB* db)
	{
		list<Order*> records;
		db->SelectOrder(records);
		for (auto record : records)
		{
			mdb->t_Order->Insert(record);
		}
	}
	void InitMdbFromDB::LoadTradeTable(Mdb* mdb, DB* db)
	{
		list<Trade*> records;
		db->SelectTrade(records);
		for (auto record : records)
		{
			mdb->t_Trade->Insert(record);
		}
	}
	void InitMdbFromDB::LoadDepthMarketDataTable(Mdb* mdb, DB* db)
	{
		list<DepthMarketData*> records;
		db->SelectDepthMarketData(records);
		for (auto record : records)
		{
			mdb->t_DepthMarketData->Insert(record);
		}
	}
}
