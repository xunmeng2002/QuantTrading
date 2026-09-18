// 本文件由 ../Templates/Cpp/Mdb/MdbTableRegistry.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbTableRegistry.h"
#include "MdbStructs.h"


namespace QuantTrading
{
	MdbTableRegistry::MdbTableRegistry(const TableList& tableList)
	{
		for (int i = 0; i < tableList.Count; ++i)
		{
			unsigned int tableId = tableList.TableIds[i];
			tableIds_.push_back(tableId);
			schemas_.push_back(GetSchemaById(tableId));
		}
	}
	const TableSchema* MdbTableRegistry::GetSchema(unsigned int tableId) const
	{
		for (size_t i = 0; i < tableIds_.size(); ++i)
		{
			if (tableIds_[i] == tableId)
			{
				return schemas_[i];
			}
		}
		return nullptr;
	}
	const TableSchema* const* MdbTableRegistry::GetAllSchemas() const
	{
		return schemas_.data();
	}
	int MdbTableRegistry::GetTableCount() const
	{
		return static_cast<int>(tableIds_.size());
	}
	const TableSchema* MdbTableRegistry::GetSchemaById(unsigned int tableId)
	{
		switch (tableId)
		{
		case TradingDay::TableId: return &TradingDay::GetSchema();
		case Exchange::TableId: return &Exchange::GetSchema();
		case Product::TableId: return &Product::GetSchema();
		case HotInstrument::TableId: return &HotInstrument::GetSchema();
		case Instrument::TableId: return &Instrument::GetSchema();
		case DepthMarketData::TableId: return &DepthMarketData::GetSchema();
		case BarMarketData::TableId: return &BarMarketData::GetSchema();
		case MdSubscribe::TableId: return &MdSubscribe::GetSchema();
		case MdUser::TableId: return &MdUser::GetSchema();
		case MdUserLoginSession::TableId: return &MdUserLoginSession::GetSchema();
		case PrimaryAccount::TableId: return &PrimaryAccount::GetSchema();
		case Account::TableId: return &Account::GetSchema();
		case Capital::TableId: return &Capital::GetSchema();
		case Position::TableId: return &Position::GetSchema();
		case PositionDetail::TableId: return &PositionDetail::GetSchema();
		case Order::TableId: return &Order::GetSchema();
		case Trade::TableId: return &Trade::GetSchema();
		case AccountLoginSession::TableId: return &AccountLoginSession::GetSchema();
		case PrimaryAccountLoginSession::TableId: return &PrimaryAccountLoginSession::GetSchema();
		case CommissionGroup::TableId: return &CommissionGroup::GetSchema();
		case BaseCommission::TableId: return &BaseCommission::GetSchema();
		default: return nullptr;
		}
	}
}
