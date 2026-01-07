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
		static void LoadSEBrokerTable(Mdb* mdb, DB* db);
		static void LoadSEInstrumentTable(Mdb* mdb, DB* db);
		static void LoadSEOrderTable(Mdb* mdb, DB* db);
		static void LoadSETradeTable(Mdb* mdb, DB* db);
		static void LoadSEBrokerLoginSessionTable(Mdb* mdb, DB* db);
		static void LoadDepthMarketDataTable(Mdb* mdb, DB* db);
	};
}
