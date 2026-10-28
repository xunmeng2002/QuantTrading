// 本文件由 ../Templates/Cpp/Mdb/LockBased/InitMdbFromDb.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
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
			case TradingDay::TableId:  LoadTradingDays(mdb, db); break;
			case Exchange::TableId:  LoadExchanges(mdb, db); break;
			case Product::TableId:  LoadProducts(mdb, db); break;
			case HotInstrument::TableId:  LoadHotInstruments(mdb, db); break;
			case Instrument::TableId:  LoadInstruments(mdb, db); break;
			case DepthMarketData::TableId:  LoadDepthMarketDatas(mdb, db); break;
			case BarMarketData::TableId:  LoadBarMarketDatas(mdb, db); break;
			case MdSubscribe::TableId:  LoadMdSubscribes(mdb, db); break;
			case MdUser::TableId:  LoadMdUsers(mdb, db); break;
			case PrimaryAccount::TableId:  LoadPrimaryAccounts(mdb, db); break;
			case Account::TableId:  LoadAccounts(mdb, db); break;
			case Capital::TableId:  LoadCapitals(mdb, db); break;
			case Position::TableId:  LoadPositions(mdb, db); break;
			case PositionDetail::TableId:  LoadPositionDetails(mdb, db); break;
			case Order::TableId:  LoadOrders(mdb, db); break;
			case Trade::TableId:  LoadTrades(mdb, db); break;
			case CommissionGroup::TableId:  LoadCommissionGroups(mdb, db); break;
			case BaseCommission::TableId:  LoadBaseCommissions(mdb, db); break;
			default: break;
			}
		}
	}

	void InitMdbFromDb::LoadTradingDays(Mdb* mdb, Db* db)
	{
		TypedTable<TradingDay> table(db);
		std::vector<TradingDay*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->TradingDays->Insert(record);
		}
	}
	void InitMdbFromDb::LoadExchanges(Mdb* mdb, Db* db)
	{
		TypedTable<Exchange> table(db);
		std::vector<Exchange*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Exchanges->Insert(record);
		}
	}
	void InitMdbFromDb::LoadProducts(Mdb* mdb, Db* db)
	{
		TypedTable<Product> table(db);
		std::vector<Product*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Products->Insert(record);
		}
	}
	void InitMdbFromDb::LoadHotInstruments(Mdb* mdb, Db* db)
	{
		TypedTable<HotInstrument> table(db);
		std::vector<HotInstrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->HotInstruments->Insert(record);
		}
	}
	void InitMdbFromDb::LoadInstruments(Mdb* mdb, Db* db)
	{
		TypedTable<Instrument> table(db);
		std::vector<Instrument*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Instruments->Insert(record);
		}
	}
	void InitMdbFromDb::LoadDepthMarketDatas(Mdb* mdb, Db* db)
	{
		TypedTable<DepthMarketData> table(db);
		std::vector<DepthMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->DepthMarketDatas->Insert(record);
		}
	}
	void InitMdbFromDb::LoadBarMarketDatas(Mdb* mdb, Db* db)
	{
		TypedTable<BarMarketData> table(db);
		std::vector<BarMarketData*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->BarMarketDatas->Insert(record);
		}
	}
	void InitMdbFromDb::LoadMdSubscribes(Mdb* mdb, Db* db)
	{
		TypedTable<MdSubscribe> table(db);
		std::vector<MdSubscribe*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->MdSubscribes->Insert(record);
		}
	}
	void InitMdbFromDb::LoadMdUsers(Mdb* mdb, Db* db)
	{
		TypedTable<MdUser> table(db);
		std::vector<MdUser*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->MdUsers->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPrimaryAccounts(Mdb* mdb, Db* db)
	{
		TypedTable<PrimaryAccount> table(db);
		std::vector<PrimaryAccount*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->PrimaryAccounts->Insert(record);
		}
	}
	void InitMdbFromDb::LoadAccounts(Mdb* mdb, Db* db)
	{
		TypedTable<Account> table(db);
		std::vector<Account*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Accounts->Insert(record);
		}
	}
	void InitMdbFromDb::LoadCapitals(Mdb* mdb, Db* db)
	{
		TypedTable<Capital> table(db);
		std::vector<Capital*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Capitals->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPositions(Mdb* mdb, Db* db)
	{
		TypedTable<Position> table(db);
		std::vector<Position*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Positions->Insert(record);
		}
	}
	void InitMdbFromDb::LoadPositionDetails(Mdb* mdb, Db* db)
	{
		TypedTable<PositionDetail> table(db);
		std::vector<PositionDetail*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->PositionDetails->Insert(record);
		}
	}
	void InitMdbFromDb::LoadOrders(Mdb* mdb, Db* db)
	{
		TypedTable<Order> table(db);
		std::vector<Order*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Orders->Insert(record);
		}
	}
	void InitMdbFromDb::LoadTrades(Mdb* mdb, Db* db)
	{
		TypedTable<Trade> table(db);
		std::vector<Trade*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->Trades->Insert(record);
		}
	}
	void InitMdbFromDb::LoadCommissionGroups(Mdb* mdb, Db* db)
	{
		TypedTable<CommissionGroup> table(db);
		std::vector<CommissionGroup*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->CommissionGroups->Insert(record);
		}
	}
	void InitMdbFromDb::LoadBaseCommissions(Mdb* mdb, Db* db)
	{
		TypedTable<BaseCommission> table(db);
		std::vector<BaseCommission*> records;
		table.SelectAll(records);
		for (auto record : records)
		{
			mdb->BaseCommissions->Insert(record);
		}
	}
}
