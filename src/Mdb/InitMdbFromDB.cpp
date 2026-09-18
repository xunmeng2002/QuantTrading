// 本文件由 ../Templates/Cpp/Mdb/InitMdbFromDB.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "InitMdbFromDb.h"
#include <DbAdapters/DbInterface/TypedTable.h>
#include <vector>

using namespace DbAdapters;

namespace QuantTrading
{

	void InitMdbFromDb::LoadTables(Mdb* mdb, Db* db, const TableList& tableList)
	{
		for (int i = 0; i < tableList.Count; ++i)
		{
			switch (tableList.TableIds[i])
			{
			case TradingDay::TableId:  LoadTradingDayTable(mdb, db); break;
			case Exchange::TableId:  LoadExchangeTable(mdb, db); break;
			case Product::TableId:  LoadProductTable(mdb, db); break;
			case HotInstrument::TableId:  LoadHotInstrumentTable(mdb, db); break;
			case Instrument::TableId:  LoadInstrumentTable(mdb, db); break;
			case DepthMarketData::TableId:  LoadDepthMarketDataTable(mdb, db); break;
			case BarMarketData::TableId:  LoadBarMarketDataTable(mdb, db); break;
			case MdSubscribe::TableId:  LoadMdSubscribeTable(mdb, db); break;
			case MdUser::TableId:  LoadMdUserTable(mdb, db); break;
			case PrimaryAccount::TableId:  LoadPrimaryAccountTable(mdb, db); break;
			case Account::TableId:  LoadAccountTable(mdb, db); break;
			case Capital::TableId:  LoadCapitalTable(mdb, db); break;
			case Position::TableId:  LoadPositionTable(mdb, db); break;
			case PositionDetail::TableId:  LoadPositionDetailTable(mdb, db); break;
			case Order::TableId:  LoadOrderTable(mdb, db); break;
			case Trade::TableId:  LoadTradeTable(mdb, db); break;
			case CommissionGroup::TableId:  LoadCommissionGroupTable(mdb, db); break;
			case BaseCommission::TableId:  LoadBaseCommissionTable(mdb, db); break;
			default: break;
			}
		}
	}

	void InitMdbFromDb::LoadTradingDayTable(Mdb* mdb, Db* db)
	{
		TypedTable<TradingDay> table(db);
		std::vector<TradingDay*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->TradingDay->Insert(record);
		}
	}
	void InitMdbFromDb::LoadExchangeTable(Mdb* mdb, Db* db)
	{
		TypedTable<Exchange> table(db);
		std::vector<Exchange*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Exchange->Insert(record);
		}
	}
	void InitMdbFromDb::LoadProductTable(Mdb* mdb, Db* db)
	{
		TypedTable<Product> table(db);
		std::vector<Product*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Product->Insert(record);
		}
	}
	void InitMdbFromDb::LoadHotInstrumentTable(Mdb* mdb, Db* db)
	{
		TypedTable<HotInstrument> table(db);
		std::vector<HotInstrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->HotInstrument->Insert(record);
		}
	}
	void InitMdbFromDb::LoadInstrumentTable(Mdb* mdb, Db* db)
	{
		TypedTable<Instrument> table(db);
		std::vector<Instrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Instrument->Insert(record);
		}
	}
	void InitMdbFromDb::LoadDepthMarketDataTable(Mdb* mdb, Db* db)
	{
		TypedTable<DepthMarketData> table(db);
		std::vector<DepthMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->DepthMarketData->Insert(record);
		}
	}
	void InitMdbFromDb::LoadBarMarketDataTable(Mdb* mdb, Db* db)
	{
		TypedTable<BarMarketData> table(db);
		std::vector<BarMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->BarMarketData->Insert(record);
		}
	}
	void InitMdbFromDb::LoadMdSubscribeTable(Mdb* mdb, Db* db)
	{
		TypedTable<MdSubscribe> table(db);
		std::vector<MdSubscribe*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->MdSubscribe->Insert(record);
		}
	}
	void InitMdbFromDb::LoadMdUserTable(Mdb* mdb, Db* db)
	{
		TypedTable<MdUser> table(db);
		std::vector<MdUser*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->MdUser->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPrimaryAccountTable(Mdb* mdb, Db* db)
	{
		TypedTable<PrimaryAccount> table(db);
		std::vector<PrimaryAccount*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->PrimaryAccount->Insert(record);
		}
	}
	void InitMdbFromDb::LoadAccountTable(Mdb* mdb, Db* db)
	{
		TypedTable<Account> table(db);
		std::vector<Account*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Account->Insert(record);
		}
	}
	void InitMdbFromDb::LoadCapitalTable(Mdb* mdb, Db* db)
	{
		TypedTable<Capital> table(db);
		std::vector<Capital*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Capital->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPositionTable(Mdb* mdb, Db* db)
	{
		TypedTable<Position> table(db);
		std::vector<Position*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Position->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPositionDetailTable(Mdb* mdb, Db* db)
	{
		TypedTable<PositionDetail> table(db);
		std::vector<PositionDetail*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->PositionDetail->Insert(record);
		}
	}
	void InitMdbFromDb::LoadOrderTable(Mdb* mdb, Db* db)
	{
		TypedTable<Order> table(db);
		std::vector<Order*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Order->Insert(record);
		}
	}
	void InitMdbFromDb::LoadTradeTable(Mdb* mdb, Db* db)
	{
		TypedTable<Trade> table(db);
		std::vector<Trade*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Trade->Insert(record);
		}
	}
	void InitMdbFromDb::LoadCommissionGroupTable(Mdb* mdb, Db* db)
	{
		TypedTable<CommissionGroup> table(db);
		std::vector<CommissionGroup*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->CommissionGroup->Insert(record);
		}
	}
	void InitMdbFromDb::LoadBaseCommissionTable(Mdb* mdb, Db* db)
	{
		TypedTable<BaseCommission> table(db);
		std::vector<BaseCommission*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->BaseCommission->Insert(record);
		}
	}
}
