// 本文件由 ../Templates/Cpp/Mdb/MdbIndexComp.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"

namespace QuantTrading
{
	struct HotInstrumentEqualForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	struct HotInstrumentLessForTradingDayIndex
	{
		bool operator()(const HotInstrument* const left, const HotInstrument* const right) const;
	};
	
	struct InstrumentEqualForExchangeIdIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	struct InstrumentLessForExchangeIdIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	
	struct MdUserLoginSessionEqualForSessionIdIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForSessionIdIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
	struct MdUserLoginSessionEqualForMdUserIdIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForMdUserIdIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
	struct PrimaryAccountEqualForOfferIdIndex
	{
		bool operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const;
	};
	struct PrimaryAccountLessForOfferIdIndex
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
	
	struct OrderEqualForAccountIdIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	struct OrderLessForAccountIdIndex
	{
		bool operator()(const Order* const left, const Order* const right) const;
	};
	
	struct TradeEqualForAccountIdIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	struct TradeLessForAccountIdIndex
	{
		bool operator()(const Trade* const left, const Trade* const right) const;
	};
	
	struct AccountLoginSessionEqualForSessionIdIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForSessionIdIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
	struct AccountLoginSessionEqualForAccountIdIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	struct AccountLoginSessionLessForAccountIdIndex
	{
		bool operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const;
	};
	
	struct PrimaryAccountLoginSessionEqualForSessionIdIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	struct PrimaryAccountLoginSessionLessForSessionIdIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	
	struct PrimaryAccountLoginSessionEqualForPrimaryAccountIdIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	struct PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex
	{
		bool operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const;
	};
	
}
