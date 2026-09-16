// 本文件由 ../Templates/Cpp/Mdb/MdbIndexComp.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbIndexComp.h"
#include <string.h>


namespace QuantTrading
{
	bool HotInstrumentEqualForTradingDayIndex::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0&& strcmp(left->ProductId, right->ProductId) == 0&& left->Rank == right->Rank && strcmp(left->TradingDay, right->TradingDay) == 0;
	}
	bool HotInstrumentLessForTradingDayIndex::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->ProductId, right->ProductId) < 0)
			return true;
		else if (strcmp(left->ProductId, right->ProductId) > 0)
			return false;
		if (left->Rank < right->Rank)
			return true;
		else if (left->Rank > right->Rank)
			return false;
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		return false;
	}
	
	bool InstrumentEqualForExchangeIdIndex::operator()(const Instrument* const left, const Instrument* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0;
	}
	bool InstrumentLessForExchangeIdIndex::operator()(const Instrument* const left, const Instrument* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		return false;
	}
	
	bool MdUserLoginSessionEqualForSessionIdIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return left->SessionId == right->SessionId ;
	}
	bool MdUserLoginSessionLessForSessionIdIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	
	bool MdUserLoginSessionEqualForMdUserIdIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return strcmp(left->MdUserId, right->MdUserId) == 0;
	}
	bool MdUserLoginSessionLessForMdUserIdIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (strcmp(left->MdUserId, right->MdUserId) < 0)
			return true;
		else if (strcmp(left->MdUserId, right->MdUserId) > 0)
			return false;
		return false;
	}
	
	bool PrimaryAccountEqualForOfferIdIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		return left->OfferId == right->OfferId ;
	}
	bool PrimaryAccountLessForOfferIdIndex::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		if (left->OfferId < right->OfferId)
			return true;
		else if (left->OfferId > right->OfferId)
			return false;
		return false;
	}
	
	bool CapitalEqualForTradingDayIndex::operator()(const Capital* const left, const Capital* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0;
	}
	bool CapitalLessForTradingDayIndex::operator()(const Capital* const left, const Capital* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		return false;
	}
	
	bool PositionEqualForAccountIndex::operator()(const Position* const left, const Position* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool PositionLessForAccountIndex::operator()(const Position* const left, const Position* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	
	bool PositionEqualForTradingDayIndex::operator()(const Position* const left, const Position* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0;
	}
	bool PositionLessForTradingDayIndex::operator()(const Position* const left, const Position* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		return false;
	}
	
	bool PositionDetailEqualForTradeMatchIndex::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountId, right->AccountId) == 0&& strcmp(left->ExchangeId, right->ExchangeId) == 0&& strcmp(left->InstrumentId, right->InstrumentId) == 0&& left->PosiDirection == right->PosiDirection ;
	}
	bool PositionDetailLessForTradeMatchIndex::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->PosiDirection < right->PosiDirection)
			return true;
		else if (left->PosiDirection > right->PosiDirection)
			return false;
		return false;
	}
	
	bool PositionDetailEqualForTradingDayIndex::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0;
	}
	bool PositionDetailLessForTradingDayIndex::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		return false;
	}
	
	bool OrderEqualForAccountIdIndex::operator()(const Order* const left, const Order* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool OrderLessForAccountIdIndex::operator()(const Order* const left, const Order* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	
	bool TradeEqualForAccountIdIndex::operator()(const Trade* const left, const Trade* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0&& strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool TradeLessForAccountIdIndex::operator()(const Trade* const left, const Trade* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	
	bool AccountLoginSessionEqualForSessionIdIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		return left->SessionId == right->SessionId ;
	}
	bool AccountLoginSessionLessForSessionIdIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	
	bool AccountLoginSessionEqualForAccountIdIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		return strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool AccountLoginSessionLessForAccountIdIndex::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	
	bool PrimaryAccountLoginSessionEqualForSessionIdIndex::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		return left->SessionId == right->SessionId ;
	}
	bool PrimaryAccountLoginSessionLessForSessionIdIndex::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	
	bool PrimaryAccountLoginSessionEqualForPrimaryAccountIdIndex::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		return strcmp(left->PrimaryAccountId, right->PrimaryAccountId) == 0;
	}
	bool PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) < 0)
			return true;
		else if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) > 0)
			return false;
		return false;
	}
	
}
