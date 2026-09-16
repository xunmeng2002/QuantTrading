// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace QuantTrading;
namespace QuantTrading::MdOffer
{
	inline const unsigned int MdOfferTableIds[] =
	{
		Exchange::TableId,
		Instrument::TableId,
		DepthMarketData::TableId,
		BarMarketData::TableId,
		MdSubscribe::TableId,
		MdUser::TableId,
		MdUserLoginSession::TableId,
	};
	inline const TableList MdOfferTableList = { "MdOffer", MdOfferTableIds, static_cast<int>(sizeof(MdOfferTableIds) / sizeof(MdOfferTableIds[0])) };
}
