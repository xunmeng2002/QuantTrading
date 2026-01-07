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
	void InitMdbFromDB::LoadMdSubscribeTable(Mdb* mdb, DB* db)
	{
		list<MdSubscribe*> records;
		db->SelectMdSubscribe(records);
		for (auto record : records)
		{
			mdb->t_MdSubscribe->Insert(record);
		}
	}
	void InitMdbFromDB::LoadMdUserTable(Mdb* mdb, DB* db)
	{
		list<MdUser*> records;
		db->SelectMdUser(records);
		for (auto record : records)
		{
			mdb->t_MdUser->Insert(record);
		}
	}
	void InitMdbFromDB::LoadMdUserLoginSessionTable(Mdb* mdb, DB* db)
	{
		list<MdUserLoginSession*> records;
		db->SelectMdUserLoginSession(records);
		for (auto record : records)
		{
			mdb->t_MdUserLoginSession->Insert(record);
		}
	}
}
