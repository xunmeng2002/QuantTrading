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

		static void LoadTradingDayTable(Mdb* mdb, DB* db);
		static void LoadExchangeTable(Mdb* mdb, DB* db);
		static void LoadProductTable(Mdb* mdb, DB* db);
		static void LoadInstrumentTable(Mdb* mdb, DB* db);
		static void LoadOrderTable(Mdb* mdb, DB* db);
		static void LoadTradeTable(Mdb* mdb, DB* db);
		static void LoadDepthMarketDataTable(Mdb* mdb, DB* db);
	};
}
