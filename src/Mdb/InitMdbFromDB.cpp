#include "InitMdbFromDB.h"
#include <DBAdapters/DBInterface/TypedTable.h>
#include <vector>

using namespace std;
using namespace dbadapters;

namespace mdb
{

	void InitMdbFromDB::LoadTables(Mdb* mdb, DB* db, const TableList& tableList)
	{
		for (int i = 0; i < tableList.Count; ++i)
		{
			switch (tableList.TableIDs[i])
			{
			case TradingDay::TableID:  LoadTradingDayTable(mdb, db); break;
			case Exchange::TableID:  LoadExchangeTable(mdb, db); break;
			case Product::TableID:  LoadProductTable(mdb, db); break;
			case HotInstrument::TableID:  LoadHotInstrumentTable(mdb, db); break;
			case Instrument::TableID:  LoadInstrumentTable(mdb, db); break;
			case DepthMarketData::TableID:  LoadDepthMarketDataTable(mdb, db); break;
			case BarMarketData::TableID:  LoadBarMarketDataTable(mdb, db); break;
			case MdSubscribe::TableID:  LoadMdSubscribeTable(mdb, db); break;
			case MdUser::TableID:  LoadMdUserTable(mdb, db); break;
			case MdUserLoginSession::TableID:  LoadMdUserLoginSessionTable(mdb, db); break;
			case PrimaryAccount::TableID:  LoadPrimaryAccountTable(mdb, db); break;
			case Account::TableID:  LoadAccountTable(mdb, db); break;
			case Capital::TableID:  LoadCapitalTable(mdb, db); break;
			case Position::TableID:  LoadPositionTable(mdb, db); break;
			case PositionDetail::TableID:  LoadPositionDetailTable(mdb, db); break;
			case Order::TableID:  LoadOrderTable(mdb, db); break;
			case Trade::TableID:  LoadTradeTable(mdb, db); break;
			case AccountLoginSession::TableID:  LoadAccountLoginSessionTable(mdb, db); break;
			default: break;
			}
		}
	}

	void InitMdbFromDB::LoadTradingDayTable(Mdb* mdb, DB* db)
	{
		TypedTable<TradingDay> table(db);
		vector<TradingDay*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_TradingDay->Insert(record);
		}
	}
	void InitMdbFromDB::LoadExchangeTable(Mdb* mdb, DB* db)
	{
		TypedTable<Exchange> table(db);
		vector<Exchange*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Exchange->Insert(record);
		}
	}
	void InitMdbFromDB::LoadProductTable(Mdb* mdb, DB* db)
	{
		TypedTable<Product> table(db);
		vector<Product*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Product->Insert(record);
		}
	}
	void InitMdbFromDB::LoadHotInstrumentTable(Mdb* mdb, DB* db)
	{
		TypedTable<HotInstrument> table(db);
		vector<HotInstrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_HotInstrument->Insert(record);
		}
	}
	void InitMdbFromDB::LoadInstrumentTable(Mdb* mdb, DB* db)
	{
		TypedTable<Instrument> table(db);
		vector<Instrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Instrument->Insert(record);
		}
	}
	void InitMdbFromDB::LoadDepthMarketDataTable(Mdb* mdb, DB* db)
	{
		TypedTable<DepthMarketData> table(db);
		vector<DepthMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_DepthMarketData->Insert(record);
		}
	}
	void InitMdbFromDB::LoadBarMarketDataTable(Mdb* mdb, DB* db)
	{
		TypedTable<BarMarketData> table(db);
		vector<BarMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_BarMarketData->Insert(record);
		}
	}
	void InitMdbFromDB::LoadMdSubscribeTable(Mdb* mdb, DB* db)
	{
		TypedTable<MdSubscribe> table(db);
		vector<MdSubscribe*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_MdSubscribe->Insert(record);
		}
	}
	void InitMdbFromDB::LoadMdUserTable(Mdb* mdb, DB* db)
	{
		TypedTable<MdUser> table(db);
		vector<MdUser*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_MdUser->Insert(record);
		}
	}
	void InitMdbFromDB::LoadMdUserLoginSessionTable(Mdb* mdb, DB* db)
	{
		TypedTable<MdUserLoginSession> table(db);
		vector<MdUserLoginSession*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_MdUserLoginSession->Insert(record);
		}
	}
	void InitMdbFromDB::LoadPrimaryAccountTable(Mdb* mdb, DB* db)
	{
		TypedTable<PrimaryAccount> table(db);
		vector<PrimaryAccount*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_PrimaryAccount->Insert(record);
		}
	}
	void InitMdbFromDB::LoadAccountTable(Mdb* mdb, DB* db)
	{
		TypedTable<Account> table(db);
		vector<Account*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Account->Insert(record);
		}
	}
	void InitMdbFromDB::LoadCapitalTable(Mdb* mdb, DB* db)
	{
		TypedTable<Capital> table(db);
		vector<Capital*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Capital->Insert(record);
		}
	}
	void InitMdbFromDB::LoadPositionTable(Mdb* mdb, DB* db)
	{
		TypedTable<Position> table(db);
		vector<Position*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Position->Insert(record);
		}
	}
	void InitMdbFromDB::LoadPositionDetailTable(Mdb* mdb, DB* db)
	{
		TypedTable<PositionDetail> table(db);
		vector<PositionDetail*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_PositionDetail->Insert(record);
		}
	}
	void InitMdbFromDB::LoadOrderTable(Mdb* mdb, DB* db)
	{
		TypedTable<Order> table(db);
		vector<Order*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Order->Insert(record);
		}
	}
	void InitMdbFromDB::LoadTradeTable(Mdb* mdb, DB* db)
	{
		TypedTable<Trade> table(db);
		vector<Trade*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_Trade->Insert(record);
		}
	}
	void InitMdbFromDB::LoadAccountLoginSessionTable(Mdb* mdb, DB* db)
	{
		TypedTable<AccountLoginSession> table(db);
		vector<AccountLoginSession*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->t_AccountLoginSession->Insert(record);
		}
	}
}
