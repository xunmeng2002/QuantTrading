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

	void InitMdbFromDB::LoadDepthMarketDataTable(Mdb* mdb, DB* db)
	{
		list<DepthMarketData*> records;
		db->SelectDepthMarketData(records);
		for (auto record : records)
		{
			mdb->t_DepthMarketData->Insert(record);
		}
	}
	void InitMdbFromDB::LoadBarMarketDataTable(Mdb* mdb, DB* db)
	{
		list<BarMarketData*> records;
		db->SelectBarMarketData(records);
		for (auto record : records)
		{
			mdb->t_BarMarketData->Insert(record);
		}
	}
}
