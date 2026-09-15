// 本文件由 ../Templates/Cpp/Mdb/MdbIndexComp.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct HotInstrumentEqualForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	struct HotInstrumentLessForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	
	struct InstrumentEqualForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	struct InstrumentLessForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	
	struct MdUserLoginSessionEqualForSessionIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForSessionIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
	struct MdUserLoginSessionEqualForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
	struct PrimaryAccountEqualForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	struct PrimaryAccountLessForOfferIDIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	
	struct CapitalEqualForTradingDayIndex
	{
		bool operator()(const Capital* const left, const Capital* const right) const;
	};
	struct CapitalLessForTradingDayIndex
	{
		bool operator()(const Capital* const left, const Capital* const right) const;
	};
	
	struct PositionEqualForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	struct PositionLessForAccountIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	
	struct PositionEqualForTradingDayIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	struct PositionLessForTradingDayIndex
	{
		bool operator()(const Position* const left, const Position* const right) const;
	};
	
	struct PositionDetailEqualForTradeMatchIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	struct PositionDetailLessForTradeMatchIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	
	struct PositionDetailEqualForTradingDayIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	struct PositionDetailLessForTradingDayIndex
	{
		bool operator()(const PositionDetail* const left, const PositionDetail* const right) const;
	};
	
	struct OrderEqualForAccountIDIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	struct OrderLessForAccountIDIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	
	struct TradeEqualForAccountIDIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	struct TradeLessForAccountIDIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	
	struct AccountLoginSessionEqualForSessionIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForSessionIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
	struct AccountLoginSessionEqualForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForAccountIDIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
	struct PrimaryAccountLoginSessionEqualForSessionIDIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	struct PrimaryAccountLoginSessionLessForSessionIDIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	
	struct PrimaryAccountLoginSessionEqualForPrimaryAccountIDIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	struct PrimaryAccountLoginSessionLessForPrimaryAccountIDIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	
}
