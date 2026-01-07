#pragma once

constexpr const char* CreateSqliteDBTradingDayTableSqlString = "CREATE TABLE IF NOT EXISTS t_TradingDay(PK int, CurrTradingDay char(9), PreTradingDay char(9), PRIMARY KEY(PK));";
constexpr const char* TruncateSqliteDBTradingDayTableSqlString = "Delete From t_TradingDay;";

constexpr const char* CreateSqliteDBExchangeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Exchange(ExchangeID char(8), ExchangeName char(64), PRIMARY KEY(ExchangeID));";
constexpr const char* TruncateSqliteDBExchangeTableSqlString = "Delete From t_Exchange;";

constexpr const char* CreateSqliteDBProductTableSqlString = "CREATE TABLE IF NOT EXISTS t_Product(ExchangeID char(8), ProductID char(32), ProductName char(32), ProductClass int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName char(32), PRIMARY KEY(ExchangeID, ProductID));";
constexpr const char* TruncateSqliteDBProductTableSqlString = "Delete From t_Product;";

constexpr const char* CreateSqliteDBHotInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_HotInstrument(TradingDay char(9), ExchangeID char(8), ProductID char(32), InstrumentID char(32), ProductClass int, Volume bigint, MaxVolume bigint, Turnover double, MaxTurnover double, OpenInterest double, MaxOpenInterest double, Rank int, PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);";
constexpr const char* TruncateSqliteDBHotInstrumentTableSqlString = "Delete From t_HotInstrument;";

constexpr const char* CreateSqliteDBInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_Instrument(ExchangeID char(8), InstrumentID char(32), ExchangeInstID char(32), InstrumentName char(64), ProductID char(32), ProductClass int, InstrumentClass int, Rank int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName char(32), PRIMARY KEY(ExchangeID, InstrumentID));";
constexpr const char* TruncateSqliteDBInstrumentTableSqlString = "Delete From t_Instrument;";

constexpr const char* CreateSqliteDBPrimaryAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_PrimaryAccount(PrimaryAccountID char(32), PrimaryAccountName char(64), AccountClass int, BrokerPassword char(64), OfferID int, IsAllowLogin bool, IsSimulateAccount bool, LoginStatus int, InitStatus int, PRIMARY KEY(PrimaryAccountID)); CREATE INDEX IF NOT EXISTS OfferIDIndex ON t_PrimaryAccount(OfferID);";
constexpr const char* TruncateSqliteDBPrimaryAccountTableSqlString = "Delete From t_PrimaryAccount;";

constexpr const char* CreateSqliteDBAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_Account(AccountID char(32), AccountName char(64), AccountType int, AccountStatus int, Password char(64), TradeGroupID int, RiskGroupID int, CommissionGroupID int, PRIMARY KEY(AccountID));";
constexpr const char* TruncateSqliteDBAccountTableSqlString = "Delete From t_Account;";

constexpr const char* CreateSqliteDBCapitalTableSqlString = "CREATE TABLE IF NOT EXISTS t_Capital(TradingDay char(9), AccountID char(32), AccountType int, Balance double, PreBalance double, Available double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, Deposit double, Withdraw double, PRIMARY KEY(TradingDay, AccountID)); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_Capital(TradingDay);";
constexpr const char* TruncateSqliteDBCapitalTableSqlString = "Delete From t_Capital;";

constexpr const char* CreateSqliteDBPositionTableSqlString = "CREATE TABLE IF NOT EXISTS t_Position(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, PosiDirection int, TotalPosition bigint, PositionFrozen bigint, TodayPosition bigint, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)); CREATE INDEX IF NOT EXISTS AccountIndex ON t_Position(TradingDay, AccountID); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_Position(TradingDay);";
constexpr const char* TruncateSqliteDBPositionTableSqlString = "Delete From t_Position;";

constexpr const char* CreateSqliteDBPositionDetailTableSqlString = "CREATE TABLE IF NOT EXISTS t_PositionDetail(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, PosiDirection int, OpenDate char(9), TradeID char(64), Volume bigint, OpenPrice double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, CloseVolume bigint, CloseAmount double, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)); CREATE INDEX IF NOT EXISTS TradeMatchIndex ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection); CREATE INDEX IF NOT EXISTS TradingDayIndex ON t_PositionDetail(TradingDay);";
constexpr const char* TruncateSqliteDBPositionDetailTableSqlString = "Delete From t_PositionDetail;";

constexpr const char* CreateSqliteDBOrderTableSqlString = "CREATE TABLE IF NOT EXISTS t_Order(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, OrderSysID char(64), Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate char(9), OrderTime char(9), CancelDate char(9), CancelTime char(9), SessionID bigint, ClientOrderID int, RequestID int, OfferID int, TradeGroupID int, RiskGroupID int, CommissionGroupID int, FrozenCash double, FrozenMargin double, FrozenCommission double, RebuildMark bool, IsForceClose bool, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID));";
constexpr const char* TruncateSqliteDBOrderTableSqlString = "Delete From t_Order;";

constexpr const char* CreateSqliteDBTradeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Trade(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, OrderSysID char(64), TradeID char(64), Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate char(9), TradeTime char(9), PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction));";
constexpr const char* TruncateSqliteDBTradeTableSqlString = "Delete From t_Trade;";

constexpr const char* CreateSqliteDBSEBrokerTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEBroker(BrokerID int, BrokerName char(16), Password char(64), PRIMARY KEY(BrokerID));";
constexpr const char* TruncateSqliteDBSEBrokerTableSqlString = "Delete From t_SEBroker;";

constexpr const char* CreateSqliteDBSEInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEInstrument(ExchangeID char(8), InstrumentID char(32), ExchangeInstID char(32), InstrumentName char(64), ProductID char(32), ProductClass int, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, VolumeMultiple int, PriceTick double, UpperLimitPrice double, LowerLimitPrice double, SessionName char(32), PRIMARY KEY(ExchangeID, InstrumentID)); CREATE INDEX IF NOT EXISTS ExchangeIDIndex ON t_SEInstrument(ExchangeID);";
constexpr const char* TruncateSqliteDBSEInstrumentTableSqlString = "Delete From t_SEInstrument;";

constexpr const char* CreateSqliteDBSEOrderTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEOrder(TradingDay char(9), BrokerID int, AccountID char(32), ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate char(9), OrderTime char(9), CancelDate char(9), CancelTime char(9), SessionID bigint, ClientOrderID int, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)); CREATE INDEX IF NOT EXISTS AccountIDIndex ON t_SEOrder(TradingDay, AccountID);";
constexpr const char* TruncateSqliteDBSEOrderTableSqlString = "Delete From t_SEOrder;";

constexpr const char* CreateSqliteDBSETradeTableSqlString = "CREATE TABLE IF NOT EXISTS t_SETrade(TradingDay char(9), BrokerID int, AccountID char(32), ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, TradeID char(64), Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate char(9), TradeTime char(9), PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)); CREATE INDEX IF NOT EXISTS AccountIDIndex ON t_SETrade(TradingDay, AccountID);";
constexpr const char* TruncateSqliteDBSETradeTableSqlString = "Delete From t_SETrade;";

constexpr const char* CreateSqliteDBSEBrokerLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_SEBrokerLoginSession(BrokerID int, SessionID bigint, IPAddress char(16), PRIMARY KEY(SessionID)); CREATE INDEX IF NOT EXISTS BrokerIDIndex ON t_SEBrokerLoginSession(BrokerID);";
constexpr const char* TruncateSqliteDBSEBrokerLoginSessionTableSqlString = "Delete From t_SEBrokerLoginSession;";

constexpr const char* CreateSqliteDBDepthMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_DepthMarketData(TradingDay char(9), ExchangeID char(8), InstrumentID char(32), UpdateTs bigint, LastPrice double, PreSettlementPrice double, PreClosePrice double, PreOpenInterest double, OpenPrice double, HighestPrice double, LowestPrice double, ClosePrice double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, SettlementPrice double, UpperLimitPrice double, LowerLimitPrice double, AveragePrice double, AskPrice1 double, AskPrice2 double, AskPrice3 double, AskPrice4 double, AskPrice5 double, AskPrice6 double, AskPrice7 double, AskPrice8 double, AskPrice9 double, AskPrice10 double, AskVolume1 bigint, AskVolume2 bigint, AskVolume3 bigint, AskVolume4 bigint, AskVolume5 bigint, AskVolume6 bigint, AskVolume7 bigint, AskVolume8 bigint, AskVolume9 bigint, AskVolume10 bigint, BidPrice1 double, BidPrice2 double, BidPrice3 double, BidPrice4 double, BidPrice5 double, BidPrice6 double, BidPrice7 double, BidPrice8 double, BidPrice9 double, BidPrice10 double, BidVolume1 bigint, BidVolume2 bigint, BidVolume3 bigint, BidVolume4 bigint, BidVolume5 bigint, BidVolume6 bigint, BidVolume7 bigint, BidVolume8 bigint, BidVolume9 bigint, BidVolume10 bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID));";
constexpr const char* TruncateSqliteDBDepthMarketDataTableSqlString = "Delete From t_DepthMarketData;";

constexpr const char* CreateSqliteDBBarMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_BarMarketData(TradingDay char(9), ExchangeID char(8), InstrumentID char(32), BarPreces int, BarPeriod int, BarTime bigint, UpdateTs bigint, PreSettlementPrice double, PreClosePrice double, Open double, High double, Low double, Close double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime));";
constexpr const char* TruncateSqliteDBBarMarketDataTableSqlString = "Delete From t_BarMarketData;";

constexpr const char* CreateSqliteDBMdSubscribeTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdSubscribe(ExchangeID char(8), InstrumentID char(32), RealInstrumentID char(32), ProductID char(32), ProductClass int, StartTradingDay char(9), EndTradingDay char(9), PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay));";
constexpr const char* TruncateSqliteDBMdSubscribeTableSqlString = "Delete From t_MdSubscribe;";

constexpr const char* CreateSqliteDBMdUserTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUser(MdUserID char(32), MdUserName char(64), Password char(64), PRIMARY KEY(MdUserID));";
constexpr const char* TruncateSqliteDBMdUserTableSqlString = "Delete From t_MdUser;";

constexpr const char* CreateSqliteDBMdUserLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(MdUserID char(32), SessionID bigint, IPAddress char(16), PRIMARY KEY(SessionID)); CREATE INDEX IF NOT EXISTS MdUserIDIndex ON t_MdUserLoginSession(MdUserID);";
constexpr const char* TruncateSqliteDBMdUserLoginSessionTableSqlString = "Delete From t_MdUserLoginSession;";

