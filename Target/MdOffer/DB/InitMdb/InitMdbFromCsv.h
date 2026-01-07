#pragma once
#include "Mdb.h"

namespace mdb
{
	class InitMdbFromCsv
	{
	public:
		static void LoadTables(Mdb* mdb, const char* dir);
	private:
		static void LoadDepthMarketDataTable(Mdb* mdb, const char* dir);
		static void LoadBarMarketDataTable(Mdb* mdb, const char* dir);
	};
}
