#include "MdbPrimaryKeyComp.h"
#include <string.h>
#include <string>
#include <functional>

using std::string;


namespace mdb
{
	bool TradingDayEqualForTradingDayPrimaryKey::operator()(const TradingDay* const left, const TradingDay* const right) const
	{
		return left->PK == right->PK;
	}
	bool TradingDayLessForTradingDayPrimaryKey::operator()(const TradingDay* const left, const TradingDay* const right) const
	{
		if (left->PK < right->PK)
			return true;
		else if (left->PK > right->PK)
			return false;
		return false;
	}
	size_t TradingDayHashForTradingDayPrimaryKey::operator()(const TradingDay* const record) const
	{
		return std::hash<int>()(record->PK);
	}
	bool ExchangeEqualForExchangePrimaryKey::operator()(const Exchange* const left, const Exchange* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0;
	}
	bool ExchangeLessForExchangePrimaryKey::operator()(const Exchange* const left, const Exchange* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		return false;
	}
	size_t ExchangeHashForExchangePrimaryKey::operator()(const Exchange* const record) const
	{
		return std::hash<string>()(record->ExchangeID);
	}
	bool ProductEqualForProductPrimaryKey::operator()(const Product* const left, const Product* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->ProductID, right->ProductID) == 0;
	}
	bool ProductLessForProductPrimaryKey::operator()(const Product* const left, const Product* const right) const
	{
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->ProductID, right->ProductID) < 0)
			return true;
		else if (strcmp(left->ProductID, right->ProductID) > 0)
			return false;
		return false;
	}
	size_t ProductHashForProductPrimaryKey::operator()(const Product* const record) const
	{
		return std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->ProductID);
	}
	bool HotInstrumentEqualForHotInstrumentPrimaryKey::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->ProductID, right->ProductID) == 0 && left->Rank == right->Rank;
	}
	bool HotInstrumentLessForHotInstrumentPrimaryKey::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->ProductID, right->ProductID) < 0)
			return true;
		else if (strcmp(left->ProductID, right->ProductID) > 0)
			return false;
		if (left->Rank < right->Rank)
			return true;
		else if (left->Rank > right->Rank)
			return false;
		return false;
	}
	size_t HotInstrumentHashForHotInstrumentPrimaryKey::operator()(const HotInstrument* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->ProductID) + std::hash<int>()(record->Rank);
	}
	bool InstrumentEqualForInstrumentPrimaryKey::operator()(const Instrument* const left, const Instrument* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0;
	}
	bool InstrumentLessForInstrumentPrimaryKey::operator()(const Instrument* const left, const Instrument* const right) const
	{
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
	size_t InstrumentHashForInstrumentPrimaryKey::operator()(const Instrument* const record) const
	{
		return std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID);
	}
	bool AccountEqualForAccountPrimaryKey::operator()(const Account* const left, const Account* const right) const
	{
		return strcmp(left->AccountID, right->AccountID) == 0;
	}
	bool AccountLessForAccountPrimaryKey::operator()(const Account* const left, const Account* const right) const
	{
		if (strcmp(left->AccountID, right->AccountID) < 0)
			return true;
		else if (strcmp(left->AccountID, right->AccountID) > 0)
			return false;
		return false;
	}
	size_t AccountHashForAccountPrimaryKey::operator()(const Account* const record) const
	{
		return std::hash<string>()(record->AccountID);
	}
}
