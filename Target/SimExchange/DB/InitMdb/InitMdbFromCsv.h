#pragma once
#include "Mdb.h"

namespace mdb
{
	class InitMdbFromCsv
	{
	public:
		static void LoadTables(Mdb* mdb, const char* dir);
	private:
		static void LoadTradingDayTable(Mdb* mdb, const char* dir);
		static void LoadExchangeTable(Mdb* mdb, const char* dir);
		static void LoadProductTable(Mdb* mdb, const char* dir);
		static void LoadSEBrokerTable(Mdb* mdb, const char* dir);
		static void LoadSEInstrumentTable(Mdb* mdb, const char* dir);
		static void LoadSEOrderTable(Mdb* mdb, const char* dir);
		static void LoadSETradeTable(Mdb* mdb, const char* dir);
		static void LoadSEBrokerLoginSessionTable(Mdb* mdb, const char* dir);
		static void LoadDepthMarketDataTable(Mdb* mdb, const char* dir);
	};
}
