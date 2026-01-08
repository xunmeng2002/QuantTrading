#pragma once
#include "Mdb.h"

namespace mdb
{
	class InitMdbFromCsv
	{
	public:
		static void LoadTables(Mdb* mdb, const char* dir);
	private:
		static void LoadExchangeTable(Mdb* mdb, const char* dir);
		static void LoadInstrumentTable(Mdb* mdb, const char* dir);
		static void LoadDepthMarketDataTable(Mdb* mdb, const char* dir);
		static void LoadBarMarketDataTable(Mdb* mdb, const char* dir);
		static void LoadMdSubscribeTable(Mdb* mdb, const char* dir);
		static void LoadMdUserTable(Mdb* mdb, const char* dir);
		static void LoadMdUserLoginSessionTable(Mdb* mdb, const char* dir);
	};
}
