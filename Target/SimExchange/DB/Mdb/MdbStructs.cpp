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

	Order* Order::Allocate()
	{
		return ::Allocate<Order>();
	}
	void Order::Free()
	{
		::Free<Order>(this);
	}
	const char* Order::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%d,%d,%d,%f,%lld,%lld,%lld,%d,%d,%s,%s,%s,%s,%lld,%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return t_MdbDataStringBuffer;
	}
	int Order::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%d','%d','%d','%f','%lld','%lld','%lld','%d','%d','%s','%s','%s','%s','%lld','%d','%d','%d','%d','%d','%d','%f','%f','%f','%d','%d'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
	}
	const char* Order::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Order:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], OfferID:[%d], TradeGroupID:[%d], RiskGroupID:[%d], CommissionGroupID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], RebuildMark:[%d], IsForceClose:[%d]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return t_MdbDataStringBuffer;
	}

	Trade* Trade::Allocate()
	{
		return ::Allocate<Trade>();
	}
	void Trade::Free()
	{
		::Free<Trade>(this);
	}
	const char* Trade::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%s,%d,%d,%f,%lld,%d,%f,%f,%s,%s",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}
	int Trade::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%s','%d','%d','%f','%lld','%d','%f','%f','%s','%s'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
	}
	const char* Trade::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Trade:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}

	DepthMarketData* DepthMarketData::Allocate()
	{
		return ::Allocate<DepthMarketData>();
	}
	void DepthMarketData::Free()
	{
		::Free<DepthMarketData>(this);
	}
	const char* DepthMarketData::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return t_MdbDataStringBuffer;
	}
	int DepthMarketData::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld'),",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
	}
	const char* DepthMarketData::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "DepthMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return t_MdbDataStringBuffer;
	}


	thread_local TradingDay t_CompareTradingDay;
	thread_local Exchange t_CompareExchange;
	thread_local Product t_CompareProduct;
	thread_local Instrument t_CompareInstrument;
	thread_local Order t_CompareOrder;
	thread_local Trade t_CompareTrade;
	thread_local DepthMarketData t_CompareDepthMarketData;

}
