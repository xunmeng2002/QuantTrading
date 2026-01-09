#pragma once

constexpr const char* CreateDuckDBTradingDayTableSqlString = "CREATE TABLE IF NOT EXISTS t_TradingDay(PK int, CurrTradingDay varchar, PreTradingDay varchar, PRIMARY KEY(PK));";
constexpr const char* TruncateDuckDBTradingDayTableSqlString = "Delete From t_TradingDay;";

constexpr const char* CreateDuckDBExchangeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Exchange(ExchangeID varchar, ExchangeName varchar, PRIMARY KEY(ExchangeID));";
constexpr const char* TruncateDuckDBExchangeTableSqlString = "Delete From t_Exchange;";

constexpr const char* CreateDuckDBProductTableSqlString = "CREATE TABLE IF NOT EXISTS t_Product(ExchangeID varchar, ProductID varchar, ProductName varchar, ProductClass int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName varchar, PRIMARY KEY(ExchangeID, ProductID));";
constexpr const char* TruncateDuckDBProductTableSqlString = "Delete From t_Product;";

constexpr const char* CreateDuckDBHotInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_HotInstrument(TradingDay varchar, ExchangeID varchar, ProductID varchar, InstrumentID varchar, ProductClass int, Volume bigint, MaxVolume bigint, Turnover double, MaxTurnover double, OpenInterest double, MaxOpenInterest double, Rank int, PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);";
constexpr const char* TruncateDuckDBHotInstrumentTableSqlString = "Delete From t_HotInstrument;";

constexpr const char* CreateDuckDBInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_Instrument(ExchangeID varchar, InstrumentID varchar, ExchangeInstID varchar, InstrumentName varchar, ProductID varchar, ProductClass int, InstrumentClass int, Rank int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName varchar, PRIMARY KEY(ExchangeID, InstrumentID));";
constexpr const char* TruncateDuckDBInstrumentTableSqlString = "Delete From t_Instrument;";

constexpr const char* CreateDuckDBDepthMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_DepthMarketData(TradingDay varchar, ExchangeID varchar, InstrumentID varchar, UpdateTs bigint, LastPrice double, PreSettlementPrice double, PreClosePrice double, PreOpenInterest double, OpenPrice double, HighestPrice double, LowestPrice double, ClosePrice double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, SettlementPrice double, UpperLimitPrice double, LowerLimitPrice double, AveragePrice double, AskPrice1 double, AskPrice2 double, AskPrice3 double, AskPrice4 double, AskPrice5 double, AskPrice6 double, AskPrice7 double, AskPrice8 double, AskPrice9 double, AskPrice10 double, AskVolume1 bigint, AskVolume2 bigint, AskVolume3 bigint, AskVolume4 bigint, AskVolume5 bigint, AskVolume6 bigint, AskVolume7 bigint, AskVolume8 bigint, AskVolume9 bigint, AskVolume10 bigint, BidPrice1 double, BidPrice2 double, BidPrice3 double, BidPrice4 double, BidPrice5 double, BidPrice6 double, BidPrice7 double, BidPrice8 double, BidPrice9 double, BidPrice10 double, BidVolume1 bigint, BidVolume2 bigint, BidVolume3 bigint, BidVolume4 bigint, BidVolume5 bigint, BidVolume6 bigint, BidVolume7 bigint, BidVolume8 bigint, BidVolume9 bigint, BidVolume10 bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID));";
constexpr const char* TruncateDuckDBDepthMarketDataTableSqlString = "Delete From t_DepthMarketData;";

constexpr const char* CreateDuckDBBarMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_BarMarketData(TradingDay varchar, ExchangeID varchar, InstrumentID varchar, BarPreces int, BarPeriod int, BarTime bigint, UpdateTs bigint, PreSettlementPrice double, PreClosePrice double, Open double, High double, Low double, Close double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime));";
constexpr const char* TruncateDuckDBBarMarketDataTableSqlString = "Delete From t_BarMarketData;";

constexpr const char* CreateDuckDBMdSubscribeTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdSubscribe(ExchangeID varchar, InstrumentID varchar, RealInstrumentID varchar, ProductID varchar, ProductClass int, StartTradingDay varchar, EndTradingDay varchar, PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay));";
constexpr const char* TruncateDuckDBMdSubscribeTableSqlString = "Delete From t_MdSubscribe;";

constexpr const char* CreateDuckDBMdUserTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUser(MdUserID varchar, MdUserName varchar, Password varchar, PRIMARY KEY(MdUserID));";
constexpr const char* TruncateDuckDBMdUserTableSqlString = "Delete From t_MdUser;";

constexpr const char* CreateDuckDBMdUserLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(MdUserID varchar, SessionID bigint, IPAddress varchar, PRIMARY KEY(SessionID)); CREATE INDEX IF NOT EXISTS MdUserIDIndex ON t_MdUserLoginSession(MdUserID);";
constexpr const char* TruncateDuckDBMdUserLoginSessionTableSqlString = "Delete From t_MdUserLoginSession;";

constexpr const char* CreateDuckDBPrimaryAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_PrimaryAccount(PrimaryAccountID varchar, PrimaryAccountName varchar, AccountClass int, BrokerPassword varchar, OfferID int, IsAllowLogin bool, IsSimulateAccount bool, LoginStatus int, InitStatus int, PRIMARY KEY(PrimaryAccountID)); CREATE INDEX IF NOT EXISTS OfferIDIndex ON t_PrimaryAccount(OfferID);";
constexpr const char* TruncateDuckDBPrimaryAccountTableSqlString = "Delete From t_PrimaryAccount;";

constexpr const char* CreateDuckDBAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_Account(AccountID varchar, AccountName varchar, AccountType int, AccountStatus int, Password varchar, TradeGroupID int, RiskGroupID int, CommissionGroupID int, PRIMARY KEY(AccountID));";
constexpr const char* TruncateDuckDBAccountTableSqlString = "Delete From t_Account;";

constexpr const char* CreateDuckDBCapitalTableSqlString = "CREATE TABLE IF NOT EXISTS t_Capital(TradingDay varchar, AccountID varchar, AccountType int, Balance double, PreBalance double, Available double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, Deposit double, Withdraw double, PRIMARY KEY(TradingDay, AccountID)); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_Capital(TradingDay);";
constexpr const char* TruncateDuckDBCapitalTableSqlString = "Delete From t_Capital;";

constexpr const char* CreateDuckDBPositionTableSqlString = "CREATE TABLE IF NOT EXISTS t_Position(TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, PosiDirection int, TotalPosition bigint, PositionFrozen bigint, TodayPosition bigint, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)); CREATE INDEX IF NOT EXISTS AccountIndex ON t_Position(TradingDay, AccountID); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_Position(TradingDay);";
constexpr const char* TruncateDuckDBPositionTableSqlString = "Delete From t_Position;";

constexpr const char* CreateDuckDBPositionDetailTableSqlString = "CREATE TABLE IF NOT EXISTS t_PositionDetail(TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, PosiDirection int, OpenDate varchar, TradeID varchar, Volume bigint, OpenPrice double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, CloseVolume bigint, CloseAmount double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)); CREATE INDEX IF NOT EXISTS TradeMatchIndex ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_PositionDetail(TradingDay);";
constexpr const char* TruncateDuckDBPositionDetailTableSqlString = "Delete From t_PositionDetail;";

constexpr const char* CreateDuckDBOrderTableSqlString = "CREATE TABLE IF NOT EXISTS t_Order(TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, OrderSysID varchar, Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate varchar, OrderTime varchar, CancelDate varchar, CancelTime varchar, SessionID bigint, ClientOrderID int, RequestID int, OfferID int, TradeGroupID int, RiskGroupID int, CommissionGroupID int, FrozenCash double, FrozenMargin double, FrozenCommission double, RebuildMark bool, IsForceClose bool, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID));";
constexpr const char* TruncateDuckDBOrderTableSqlString = "Delete From t_Order;";

constexpr const char* CreateDuckDBTradeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Trade(TradingDay varchar, AccountID varchar, AccountType int, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, OrderSysID varchar, TradeID varchar, Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate varchar, TradeTime varchar, PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction));";
constexpr const char* TruncateDuckDBTradeTableSqlString = "Delete From t_Trade;";

constexpr const char* CreateDuckDBSEBrokerTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEBroker(BrokerID int, BrokerName varchar, Password varchar, PRIMARY KEY(BrokerID));";
constexpr const char* TruncateDuckDBSEBrokerTableSqlString = "Delete From t_SEBroker;";

constexpr const char* CreateDuckDBSEInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEInstrument(ExchangeID varchar, InstrumentID varchar, ExchangeInstID varchar, InstrumentName varchar, ProductID varchar, ProductClass int, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, VolumeMultiple int, PriceTick double, UpperLimitPrice double, LowerLimitPrice double, SessionName varchar, PRIMARY KEY(ExchangeID, InstrumentID)); CREATE INDEX IF NOT EXISTS ExchangeIDIndex ON t_SEInstrument(ExchangeID);";
constexpr const char* TruncateDuckDBSEInstrumentTableSqlString = "Delete From t_SEInstrument;";

constexpr const char* CreateDuckDBSEOrderTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEOrder(TradingDay varchar, BrokerID int, AccountID varchar, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate varchar, OrderTime varchar, CancelDate varchar, CancelTime varchar, SessionID bigint, ClientOrderID int, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)); CREATE INDEX IF NOT EXISTS AccountIDIndex ON t_SEOrder(TradingDay, AccountID);";
constexpr const char* TruncateDuckDBSEOrderTableSqlString = "Delete From t_SEOrder;";

constexpr const char* CreateDuckDBSETradeTableSqlString = "CREATE TABLE IF NOT EXISTS t_SETrade(TradingDay varchar, BrokerID int, AccountID varchar, ExchangeID varchar, InstrumentID varchar, ProductClass int, OrderID int, TradeID varchar, Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate varchar, TradeTime varchar, PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)); CREATE INDEX IF NOT EXISTS AccountIDIndex ON t_SETrade(TradingDay, AccountID);";
constexpr const char* TruncateDuckDBSETradeTableSqlString = "Delete From t_SETrade;";

constexpr const char* CreateDuckDBSEBrokerLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEBrokerLoginSession(BrokerID int, SessionID bigint, IPAddress varchar, PRIMARY KEY(SessionID)); CREATE INDEX IF NOT EXISTS BrokerIDIndex ON t_SEBrokerLoginSession(BrokerID);";
constexpr const char* TruncateDuckDBSEBrokerLoginSessionTableSqlString = "Delete From t_SEBrokerLoginSession;";

