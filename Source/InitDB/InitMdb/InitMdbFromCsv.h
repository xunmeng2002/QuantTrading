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
		static void LoadHotInstrumentTable(Mdb* mdb, const char* dir);
		static void LoadInstrumentTable(Mdb* mdb, const char* dir);
		static void LoadAccountTable(Mdb* mdb, const char* dir);
	};
}
