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

	PrimaryAccount* PrimaryAccount::Allocate()
	{
		return ::Allocate<PrimaryAccount>();
	}
	void PrimaryAccount::Free()
	{
		::Free<PrimaryAccount>(this);
	}
	const char* PrimaryAccount::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%d,%d,%d,%d,%d",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, BrokerPassword, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
		return t_MdbDataStringBuffer;
	}
	int PrimaryAccount::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%d','%d','%d','%d','%d'),",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, BrokerPassword, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
	}
	const char* PrimaryAccount::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "PrimaryAccount:PrimaryAccountID:[%s], PrimaryAccountName:[%s], AccountClass:[%d], BrokerPassword:[%s], OfferID:[%d], IsAllowLogin:[%d], IsSimulateAccount:[%d], LoginStatus:[%d], InitStatus:[%d]",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, BrokerPassword, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
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

	Capital* Capital::Allocate()
	{
		return ::Allocate<Capital>();
	}
	void Capital::Free()
	{
		::Free<Capital>(this);
	}
	const char* Capital::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
		return t_MdbDataStringBuffer;
	}
	int Capital::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f'),",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
	}
	const char* Capital::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Capital:TradingDay:[%s], AccountID:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
		return t_MdbDataStringBuffer;
	}

	Position* Position::Allocate()
	{
		return ::Allocate<Position>();
	}
	void Position::Free()
	{
		::Free<Position>(this);
	}
	const char* Position::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
		return t_MdbDataStringBuffer;
	}
	int Position::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%lld','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%d','%f','%f','%f','%f','%f','%f'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
	}
	const char* Position::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Position:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
		return t_MdbDataStringBuffer;
	}

	PositionDetail* PositionDetail::Allocate()
	{
		return ::Allocate<PositionDetail>();
	}
	void PositionDetail::Free()
	{
		::Free<PositionDetail>(this);
	}
	const char* PositionDetail::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f,%lld,%f",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
		return t_MdbDataStringBuffer;
	}
	int PositionDetail::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%s','%lld','%f','%f','%f','%f','%f','%f','%d','%f','%f','%f','%f','%f','%f','%lld','%f'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
	}
	const char* PositionDetail::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "PositionDetail:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], OpenDate:[%s], TradeID:[%s], Volume:[%lld], OpenPrice:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f], CloseVolume:[%lld], CloseAmount:[%f]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
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

	BarMarketData* BarMarketData::Allocate()
	{
		return ::Allocate<BarMarketData>();
	}
	void BarMarketData::Free()
	{
		::Free<BarMarketData>(this);
	}
	const char* BarMarketData::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%d,%d,%lld,%lld,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}
	int BarMarketData::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%d','%d','%lld','%lld','%f','%f','%f','%f','%f','%f','%lld','%lld','%f','%f','%f'),",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
	}
	const char* BarMarketData::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}

	MdSubscribe* MdSubscribe::Allocate()
	{
		return ::Allocate<MdSubscribe>();
	}
	void MdSubscribe::Free()
	{
		::Free<MdSubscribe>(this);
	}
	const char* MdSubscribe::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%d,%s,%s",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
		return t_MdbDataStringBuffer;
	}
	int MdSubscribe::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%d','%s','%s'),",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
	}
	const char* MdSubscribe::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "MdSubscribe:ExchangeID:[%s], InstrumentID:[%s], RealInstrumentID:[%s], ProductID:[%s], ProductClass:[%d], StartTradingDay:[%s], EndTradingDay:[%s]",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
		return t_MdbDataStringBuffer;
	}

	SEBroker* SEBroker::Allocate()
	{
		return ::Allocate<SEBroker>();
	}
	void SEBroker::Free()
	{
		::Free<SEBroker>(this);
	}
	const char* SEBroker::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%d,%s,%s",
			BrokerID, BrokerName, Password);
		return t_MdbDataStringBuffer;
	}
	int SEBroker::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%d','%s','%s'),",
			BrokerID, BrokerName, Password);
	}
	const char* SEBroker::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "SEBroker:BrokerID:[%d], BrokerName:[%s], Password:[%s]",
			BrokerID, BrokerName, Password);
		return t_MdbDataStringBuffer;
	}

	SEInstrument* SEInstrument::Allocate()
	{
		return ::Allocate<SEInstrument>();
	}
	void SEInstrument::Free()
	{
		::Free<SEInstrument>(this);
	}
	const char* SEInstrument::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%s,%d,%lld,%lld,%lld,%lld,%d,%f,%f,%f,%s",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, VolumeMultiple, PriceTick, UpperLimitPrice, LowerLimitPrice, SessionName);
		return t_MdbDataStringBuffer;
	}
	int SEInstrument::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%s','%d','%lld','%lld','%lld','%lld','%d','%f','%f','%f','%s'),",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, VolumeMultiple, PriceTick, UpperLimitPrice, LowerLimitPrice, SessionName);
	}
	const char* SEInstrument::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "SEInstrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], VolumeMultiple:[%d], PriceTick:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], SessionName:[%s]",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, VolumeMultiple, PriceTick, UpperLimitPrice, LowerLimitPrice, SessionName);
		return t_MdbDataStringBuffer;
	}

	SEOrder* SEOrder::Allocate()
	{
		return ::Allocate<SEOrder>();
	}
	void SEOrder::Free()
	{
		::Free<SEOrder>(this);
	}
	const char* SEOrder::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%f,%lld,%lld,%lld,%d,%d,%s,%s,%s,%s,%lld,%d",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID);
		return t_MdbDataStringBuffer;
	}
	int SEOrder::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%d','%s','%s','%s','%d','%d','%d','%d','%d','%f','%lld','%lld','%lld','%d','%d','%s','%s','%s','%s','%lld','%d'),",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID);
	}
	const char* SEOrder::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "SEOrder:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID);
		return t_MdbDataStringBuffer;
	}

	SETrade* SETrade::Allocate()
	{
		return ::Allocate<SETrade>();
	}
	void SETrade::Free()
	{
		::Free<SETrade>(this);
	}
	const char* SETrade::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%d,%s,%s,%s,%d,%d,%s,%d,%d,%f,%lld,%d,%f,%f,%s,%s",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}
	int SETrade::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%d','%s','%s','%s','%d','%d','%s','%d','%d','%f','%lld','%d','%f','%f','%s','%s'),",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
	}
	const char* SETrade::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "SETrade:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			TradingDay, BrokerID, AccountID, ExchangeID, InstrumentID, (int)ProductClass, OrderID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}

	SEBrokerLoginSession* SEBrokerLoginSession::Allocate()
	{
		return ::Allocate<SEBrokerLoginSession>();
	}
	void SEBrokerLoginSession::Free()
	{
		::Free<SEBrokerLoginSession>(this);
	}
	const char* SEBrokerLoginSession::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%d,%lld,%s",
			BrokerID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}
	int SEBrokerLoginSession::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%d','%lld','%s'),",
			BrokerID, SessionID, IPAddress);
	}
	const char* SEBrokerLoginSession::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "SEBrokerLoginSession:BrokerID:[%d], SessionID:[%lld], IPAddress:[%s]",
			BrokerID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}


	thread_local TradingDay t_CompareTradingDay;
	thread_local Exchange t_CompareExchange;
	thread_local Product t_CompareProduct;
	thread_local HotInstrument t_CompareHotInstrument;
	thread_local Instrument t_CompareInstrument;
	thread_local PrimaryAccount t_ComparePrimaryAccount;
	thread_local Account t_CompareAccount;
	thread_local Capital t_CompareCapital;
	thread_local Position t_ComparePosition;
	thread_local PositionDetail t_ComparePositionDetail;
	thread_local Order t_CompareOrder;
	thread_local Trade t_CompareTrade;
	thread_local DepthMarketData t_CompareDepthMarketData;
	thread_local BarMarketData t_CompareBarMarketData;
	thread_local MdSubscribe t_CompareMdSubscribe;
	thread_local SEBroker t_CompareSEBroker;
	thread_local SEInstrument t_CompareSEInstrument;
	thread_local SEOrder t_CompareSEOrder;
	thread_local SETrade t_CompareSETrade;
	thread_local SEBrokerLoginSession t_CompareSEBrokerLoginSession;

}
