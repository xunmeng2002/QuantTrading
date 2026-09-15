// 本文件由 ../Templates/Cpp/Mdb/ModuleTableList.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "TableList.h"
#include "MdbStructs.h"

using namespace mdb;
namespace quanttrading::mdoffer
{
	inline const unsigned int kmdofferTableIDs[] =
	{
		Exchange::TableID,
		Instrument::TableID,
		DepthMarketData::TableID,
		BarMarketData::TableID,
		MdSubscribe::TableID,
		MdUser::TableID,
		MdUserLoginSession::TableID,
	};
	inline const TableList mdofferTableList = { "mdoffer", kmdofferTableIDs, static_cast<int>(sizeof(kmdofferTableIDs) / sizeof(kmdofferTableIDs[0])) };
}
