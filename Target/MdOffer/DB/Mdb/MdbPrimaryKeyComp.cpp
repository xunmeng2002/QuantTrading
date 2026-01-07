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
}
