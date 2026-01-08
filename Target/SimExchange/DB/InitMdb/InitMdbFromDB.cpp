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

	void InitMdbFromDB::LoadTradingDayTable(Mdb* mdb, DB* db)
	{
		list<TradingDay*> records;
		db->SelectTradingDay(records);
		for (auto record : records)
		{
			mdb->t_TradingDay->Insert(record);
		}
	}
	void InitMdbFromDB::LoadExchangeTable(Mdb* mdb, DB* db)
	{
		list<Exchange*> records;
		db->SelectExchange(records);
		for (auto record : records)
		{
			mdb->t_Exchange->Insert(record);
		}
	}
	void InitMdbFromDB::LoadProductTable(Mdb* mdb, DB* db)
	{
		list<Product*> records;
		db->SelectProduct(records);
		for (auto record : records)
		{
			mdb->t_Product->Insert(record);
		}
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
	void InitMdbFromDB::LoadSEBrokerTable(Mdb* mdb, DB* db)
	{
		list<SEBroker*> records;
		db->SelectSEBroker(records);
		for (auto record : records)
		{
			mdb->t_SEBroker->Insert(record);
		}
	}
	void InitMdbFromDB::LoadSEInstrumentTable(Mdb* mdb, DB* db)
	{
		list<SEInstrument*> records;
		db->SelectSEInstrument(records);
		for (auto record : records)
		{
			mdb->t_SEInstrument->Insert(record);
		}
	}
	void InitMdbFromDB::LoadSEOrderTable(Mdb* mdb, DB* db)
	{
		list<SEOrder*> records;
		db->SelectSEOrder(records);
		for (auto record : records)
		{
			mdb->t_SEOrder->Insert(record);
		}
	}
	void InitMdbFromDB::LoadSETradeTable(Mdb* mdb, DB* db)
	{
		list<SETrade*> records;
		db->SelectSETrade(records);
		for (auto record : records)
		{
			mdb->t_SETrade->Insert(record);
		}
	}
	void InitMdbFromDB::LoadSEBrokerLoginSessionTable(Mdb* mdb, DB* db)
	{
		list<SEBrokerLoginSession*> records;
		db->SelectSEBrokerLoginSession(records);
		for (auto record : records)
		{
			mdb->t_SEBrokerLoginSession->Insert(record);
		}
	}
}
