#include "MdbStructs.h"
#include "MemCacheTemplateSingleton.h"
#include <string>
#include <cstring>

namespace mdb
{
	thread_local char t_MdbDataStringBuffer[10240];

	TradingDay* TradingDay::Allocate()
	{
		return ::Allocate<TradingDay>();
	}
	void TradingDay::Free()
	{
		::Free<TradingDay>(this);
	}
	const char* TradingDay::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%d,%s,%s",
			PK, CurrTradingDay, PreTradingDay);
		return t_MdbDataStringBuffer;
	}
	int TradingDay::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%d','%s','%s'),",
			PK, CurrTradingDay, PreTradingDay);
	}
	const char* TradingDay::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "TradingDay:PK:[%d], CurrTradingDay:[%s], PreTradingDay:[%s]",
			PK, CurrTradingDay, PreTradingDay);
		return t_MdbDataStringBuffer;
	}

	Exchange* Exchange::Allocate()
	{
		return ::Allocate<Exchange>();
	}
	void Exchange::Free()
	{
		::Free<Exchange>(this);
	}
	const char* Exchange::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s",
			ExchangeID, ExchangeName);
		return t_MdbDataStringBuffer;
	}
	int Exchange::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s'),",
			ExchangeID, ExchangeName);
	}
	const char* Exchange::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Exchange:ExchangeID:[%s], ExchangeName:[%s]",
			ExchangeID, ExchangeName);
		return t_MdbDataStringBuffer;
	}

	Product* Product::Allocate()
	{
		return ::Allocate<Product>();
	}
	void Product::Free()
	{
		::Free<Product>(this);
	}
	const char* Product::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	int Product::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%d','%d','%f','%lld','%lld','%lld','%lld','%s'),",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
	}
	const char* Product::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Product:ExchangeID:[%s], ProductID:[%s], ProductName:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}

	HotInstrument* HotInstrument::Allocate()
	{
		return ::Allocate<HotInstrument>();
	}
	void HotInstrument::Free()
	{
		::Free<HotInstrument>(this);
	}
	const char* HotInstrument::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%d,%lld,%lld,%f,%f,%f,%f,%d",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return t_MdbDataStringBuffer;
	}
	int HotInstrument::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%d','%lld','%lld','%f','%f','%f','%f','%d'),",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
	}
	const char* HotInstrument::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "HotInstrument:TradingDay:[%s], ExchangeID:[%s], ProductID:[%s], InstrumentID:[%s], ProductClass:[%d], Volume:[%lld], MaxVolume:[%lld], Turnover:[%f], MaxTurnover:[%f], OpenInterest:[%f], MaxOpenInterest:[%f], Rank:[%d]",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return t_MdbDataStringBuffer;
	}

	Instrument* Instrument::Allocate()
	{
		return ::Allocate<Instrument>();
	}
	void Instrument::Free()
	{
		::Free<Instrument>(this);
	}
	const char* Instrument::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%s,%d,%d,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	int Instrument::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%s','%d','%d','%d','%d','%f','%lld','%lld','%lld','%lld','%s'),",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
	}
	const char* Instrument::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Instrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], InstrumentClass:[%d], Rank:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}

	Account* Account::Allocate()
	{
		return ::Allocate<Account>();
	}
	void Account::Free()
	{
		::Free<Account>(this);
	}
	const char* Account::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%d,%s,%d,%d,%d",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
		return t_MdbDataStringBuffer;
	}
	int Account::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%d','%s','%d','%d','%d'),",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
	}
	const char* Account::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Account:AccountID:[%s], AccountName:[%s], AccountType:[%d], AccountStatus:[%d], Password:[%s], TradeGroupID:[%d], RiskGroupID:[%d], CommissionGroupID:[%d]",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
		return t_MdbDataStringBuffer;
	}


	thread_local TradingDay t_CompareTradingDay;
	thread_local Exchange t_CompareExchange;
	thread_local Product t_CompareProduct;
	thread_local HotInstrument t_CompareHotInstrument;
	thread_local Instrument t_CompareInstrument;
	thread_local Account t_CompareAccount;

}
