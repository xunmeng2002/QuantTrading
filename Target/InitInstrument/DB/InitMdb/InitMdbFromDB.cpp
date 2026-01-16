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
		LoadTradingDayTable(mdb, db);
		LoadExchangeTable(mdb, db);
		LoadProductTable(mdb, db);
		LoadHotInstrumentTable(mdb, db);
		LoadInstrumentTable(mdb, db);
		LoadAccountTable(mdb, db);
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
	void InitMdbFromDB::LoadHotInstrumentTable(Mdb* mdb, DB* db)
	{
		list<HotInstrument*> records;
		db->SelectHotInstrument(records);
		for (auto record : records)
		{
			mdb->t_HotInstrument->Insert(record);
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
	void InitMdbFromDB::LoadAccountTable(Mdb* mdb, DB* db)
	{
		list<Account*> records;
		db->SelectAccount(records);
		for (auto record : records)
		{
			mdb->t_Account->Insert(record);
		}
	}
}
