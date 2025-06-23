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
	bool SEBrokerEqualForSEBrokerPrimaryKey::operator()(const SEBroker* const left, const SEBroker* const right) const
	{
		return left->BrokerID == right->BrokerID;
	}
	bool SEBrokerLessForSEBrokerPrimaryKey::operator()(const SEBroker* const left, const SEBroker* const right) const
	{
		if (left->BrokerID < right->BrokerID)
			return true;
		else if (left->BrokerID > right->BrokerID)
			return false;
		return false;
	}
	size_t SEBrokerHashForSEBrokerPrimaryKey::operator()(const SEBroker* const record) const
	{
		return std::hash<int>()(record->BrokerID);
	}
	bool SEInstrumentEqualForSEInstrumentPrimaryKey::operator()(const SEInstrument* const left, const SEInstrument* const right) const
	{
		return strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0;
	}
	bool SEInstrumentLessForSEInstrumentPrimaryKey::operator()(const SEInstrument* const left, const SEInstrument* const right) const
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
	size_t SEInstrumentHashForSEInstrumentPrimaryKey::operator()(const SEInstrument* const record) const
	{
		return std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID);
	}
	bool SEOrderEqualForSEOrderPrimaryKey::operator()(const SEOrder* const left, const SEOrder* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountID, right->AccountID) == 0 && strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->InstrumentID, right->InstrumentID) == 0 && left->OrderID == right->OrderID;
	}
	bool SEOrderLessForSEOrderPrimaryKey::operator()(const SEOrder* const left, const SEOrder* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountID, right->AccountID) < 0)
			return true;
		else if (strcmp(left->AccountID, right->AccountID) > 0)
			return false;
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->InstrumentID, right->InstrumentID) < 0)
			return true;
		else if (strcmp(left->InstrumentID, right->InstrumentID) > 0)
			return false;
		if (left->OrderID < right->OrderID)
			return true;
		else if (left->OrderID > right->OrderID)
			return false;
		return false;
	}
	size_t SEOrderHashForSEOrderPrimaryKey::operator()(const SEOrder* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountID) + std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->InstrumentID) + std::hash<int>()(record->OrderID);
	}
	bool SETradeEqualForSETradePrimaryKey::operator()(const SETrade* const left, const SETrade* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeID, right->ExchangeID) == 0 && strcmp(left->TradeID, right->TradeID) == 0 && left->Direction == right->Direction;
	}
	bool SETradeLessForSETradePrimaryKey::operator()(const SETrade* const left, const SETrade* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeID, right->ExchangeID) < 0)
			return true;
		else if (strcmp(left->ExchangeID, right->ExchangeID) > 0)
			return false;
		if (strcmp(left->TradeID, right->TradeID) < 0)
			return true;
		else if (strcmp(left->TradeID, right->TradeID) > 0)
			return false;
		if (left->Direction < right->Direction)
			return true;
		else if (left->Direction > right->Direction)
			return false;
		return false;
	}
	size_t SETradeHashForSETradePrimaryKey::operator()(const SETrade* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeID) + std::hash<string>()(record->TradeID) + std::hash<char>()((char)record->Direction);
	}
	bool SEBrokerLoginSessionEqualForSEBrokerLoginSessionPrimaryKey::operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const
	{
		return left->SessionID == right->SessionID;
	}
	bool SEBrokerLoginSessionLessForSEBrokerLoginSessionPrimaryKey::operator()(const SEBrokerLoginSession* const left, const SEBrokerLoginSession* const right) const
	{
		if (left->SessionID < right->SessionID)
			return true;
		else if (left->SessionID > right->SessionID)
			return false;
		return false;
	}
	size_t SEBrokerLoginSessionHashForSEBrokerLoginSessionPrimaryKey::operator()(const SEBrokerLoginSession* const record) const
	{
		return std::hash<long long>()(record->SessionID);
	}
}
