#pragma once
#include "Mdb.h"
#include "DB.h"

namespace mdb
{
	class InitMdbFromDB
	{
	public:
		static void LoadTablesWithTradingDay(Mdb* mdb, DB* db, const DateType& tradingDay);
		static void LoadTablesWithoutTradingDay(Mdb* mdb, DB* db);

		static void LoadDepthMarketDataTable(Mdb* mdb, DB* db);
		static void LoadBarMarketDataTable(Mdb* mdb, DB* db);
		static void LoadMdSubscribeTable(Mdb* mdb, DB* db);
		static void LoadMdUserTable(Mdb* mdb, DB* db);
		static void LoadMdUserLoginSessionTable(Mdb* mdb, DB* db);
	};
}
