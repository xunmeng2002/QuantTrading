#include "MdbPrimaryKeyComp.h"
#include <string.h>
#include <string>
#include <functional>

using std::string;


namespace mdb
{
	bool DepthMarketDataEqualForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const left, const DepthMarketData* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0;
	}
	bool DepthMarketDataLessForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const left, const DepthMarketData* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->InstrumentID, right->InstrumentID) < 0)
			return true;
		else if (strcmp(left->InstrumentID, right->InstrumentID) > 0)
			return false;
		return false;
	}
	size_t DepthMarketDataHashForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID);
	}
	bool BarMarketDataEqualForBarMarketDataPrimaryKey::operator()(const BarMarketData* const left, const BarMarketData* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0 && left->BarPreces == right->BarPreces && left->BarPeriod == right->BarPeriod && left->BarTime == right->BarTime;
	}
	bool BarMarketDataLessForBarMarketDataPrimaryKey::operator()(const BarMarketData* const left, const BarMarketData* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->InstrumentID, right->InstrumentID) < 0)
			return true;
		else if (strcmp(left->InstrumentID, right->InstrumentID) > 0)
			return false;
		if (left->BarPreces < right->BarPreces)
			return true;
		else if (left->BarPreces > right->BarPreces)
			return false;
		if (left->BarPeriod < right->BarPeriod)
			return true;
		else if (left->BarPeriod > right->BarPeriod)
			return false;
		if (left->BarTime < right->BarTime)
			return true;
		else if (left->BarTime > right->BarTime)
			return false;
		return false;
	}
	size_t BarMarketDataHashForBarMarketDataPrimaryKey::operator()(const BarMarketData* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID) + std::hash<char>()((char)record->BarPreces) + std::hash<int>()(record->BarPeriod) + std::hash<long long>()(record->BarTime);
	}
	bool MdSubscribeEqualForMdSubscribePrimaryKey::operator()(const MdSubscribe* const left, const MdSubscribe* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0 && strcmp(left->StartTradingDay, right->StartTradingDay) == 0;
	}
	bool MdSubscribeLessForMdSubscribePrimaryKey::operator()(const MdSubscribe* const left, const MdSubscribe* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->InstrumentID, right->InstrumentID) < 0)
			return true;
		else if (strcmp(left->InstrumentID, right->InstrumentID) > 0)
			return false;
		if (strcmp(left->StartTradingDay, right->StartTradingDay) < 0)
			return true;
		else if (strcmp(left->StartTradingDay, right->StartTradingDay) > 0)
			return false;
		return false;
	}
	size_t MdSubscribeHashForMdSubscribePrimaryKey::operator()(const MdSubscribe* const record) const
	{
		return std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID) + std::hash<string>()(record->StartTradingDay);
	}
	bool MdUserEqualForMdUserPrimaryKey::operator()(const MdUser* const left, const MdUser* const right) const
	{
		return strcmp(left->MdUserID, right->MdUserID) == 0;
	}
	bool MdUserLessForMdUserPrimaryKey::operator()(const MdUser* const left, const MdUser* const right) const
	{
		if (strcmp(left->MdUserID, right->MdUserID) < 0)
			return true;
		else if (strcmp(left->MdUserID, right->MdUserID) > 0)
			return false;
		return false;
	}
	size_t MdUserHashForMdUserPrimaryKey::operator()(const MdUser* const record) const
	{
		return std::hash<string>()(record->MdUserID);
	}
	bool MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return left->SessionID == right->SessionID;
	}
	bool MdUserLoginSessionLessForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (left->SessionID < right->SessionID)
			return true;
		else if (left->SessionID > right->SessionID)
			return false;
		return false;
	}
	size_t MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const record) const
	{
		return std::hash<long long>()(record->SessionID);
	}
}
