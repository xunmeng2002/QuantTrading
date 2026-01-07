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
		static void LoadPrimaryAccountTable(Mdb* mdb, const char* dir);
		static void LoadAccountTable(Mdb* mdb, const char* dir);
		static void LoadCapitalTable(Mdb* mdb, const char* dir);
		static void LoadPositionTable(Mdb* mdb, const char* dir);
		static void LoadPositionDetailTable(Mdb* mdb, const char* dir);
		static void LoadOrderTable(Mdb* mdb, const char* dir);
		static void LoadTradeTable(Mdb* mdb, const char* dir);
		static void LoadSEBrokerTable(Mdb* mdb, const char* dir);
		static void LoadSEInstrumentTable(Mdb* mdb, const char* dir);
		static void LoadSEOrderTable(Mdb* mdb, const char* dir);
		static void LoadSETradeTable(Mdb* mdb, const char* dir);
		static void LoadSEBrokerLoginSessionTable(Mdb* mdb, const char* dir);
		static void LoadDepthMarketDataTable(Mdb* mdb, const char* dir);
		static void LoadBarMarketDataTable(Mdb* mdb, const char* dir);
		static void LoadMdSubscribeTable(Mdb* mdb, const char* dir);
		static void LoadMdUserTable(Mdb* mdb, const char* dir);
		static void LoadMdUserLoginSessionTable(Mdb* mdb, const char* dir);
	};
}
