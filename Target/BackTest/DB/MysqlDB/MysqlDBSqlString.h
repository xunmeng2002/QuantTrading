#pragma once

constexpr const char* CreateMysqlDBTradingDayTableSqlString = "CREATE TABLE IF NOT EXISTS t_TradingDay(PK int, CurrTradingDay char(9), PreTradingDay char(9), PRIMARY KEY(PK)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBTradingDayTableSqlString = "Truncate Table t_TradingDay;";

constexpr const char* CreateMysqlDBExchangeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Exchange(ExchangeID char(8), ExchangeName char(64), PRIMARY KEY(ExchangeID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBExchangeTableSqlString = "Truncate Table t_Exchange;";

constexpr const char* CreateMysqlDBProductTableSqlString = "CREATE TABLE IF NOT EXISTS t_Product(ExchangeID char(8), ProductID char(32), ProductName char(32), ProductClass int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName char(32), PRIMARY KEY(ExchangeID, ProductID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBProductTableSqlString = "Truncate Table t_Product;";

constexpr const char* CreateMysqlDBHotInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_HotInstrument(TradingDay char(9), ExchangeID char(8), ProductID char(32), InstrumentID char(32), ProductClass int, Volume bigint, MaxVolume bigint, Turnover double, MaxTurnover double, OpenInterest double, MaxOpenInterest double, Rank int, INDEX TradingDay(ExchangeID, ProductID, Rank, TradingDay), PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBHotInstrumentTableSqlString = "Truncate Table t_HotInstrument;";

constexpr const char* CreateMysqlDBInstrumentTableSqlString = "CREATE TABLE IF NOT EXISTS t_Instrument(ExchangeID char(8), InstrumentID char(32), ExchangeInstID char(32), InstrumentName char(64), ProductID char(32), ProductClass int, InstrumentClass int, Rank int, VolumeMultiple int, PriceTick double, MaxMarketOrderVolume bigint, MinMarketOrderVolume bigint, MaxLimitOrderVolume bigint, MinLimitOrderVolume bigint, SessionName char(32), PRIMARY KEY(ExchangeID, InstrumentID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBInstrumentTableSqlString = "Truncate Table t_Instrument;";

constexpr const char* CreateMysqlDBDepthMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_DepthMarketData(TradingDay char(9), ExchangeID char(8), InstrumentID char(32), UpdateTs bigint, LastPrice double, PreSettlementPrice double, PreClosePrice double, PreOpenInterest double, OpenPrice double, HighestPrice double, LowestPrice double, ClosePrice double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, SettlementPrice double, UpperLimitPrice double, LowerLimitPrice double, AveragePrice double, AskPrice1 double, AskPrice2 double, AskPrice3 double, AskPrice4 double, AskPrice5 double, AskPrice6 double, AskPrice7 double, AskPrice8 double, AskPrice9 double, AskPrice10 double, AskVolume1 bigint, AskVolume2 bigint, AskVolume3 bigint, AskVolume4 bigint, AskVolume5 bigint, AskVolume6 bigint, AskVolume7 bigint, AskVolume8 bigint, AskVolume9 bigint, AskVolume10 bigint, BidPrice1 double, BidPrice2 double, BidPrice3 double, BidPrice4 double, BidPrice5 double, BidPrice6 double, BidPrice7 double, BidPrice8 double, BidPrice9 double, BidPrice10 double, BidVolume1 bigint, BidVolume2 bigint, BidVolume3 bigint, BidVolume4 bigint, BidVolume5 bigint, BidVolume6 bigint, BidVolume7 bigint, BidVolume8 bigint, BidVolume9 bigint, BidVolume10 bigint, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBDepthMarketDataTableSqlString = "Truncate Table t_DepthMarketData;";

constexpr const char* CreateMysqlDBBarMarketDataTableSqlString = "CREATE TABLE IF NOT EXISTS t_BarMarketData(TradingDay char(9), ExchangeID char(8), InstrumentID char(32), BarPreces int, BarPeriod int, BarTime bigint, UpdateTs bigint, PreSettlementPrice double, PreClosePrice double, Open double, High double, Low double, Close double, CurrVolume bigint, Volume bigint, CurrTurnover double, Turnover double, OpenInterest double, PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBBarMarketDataTableSqlString = "Truncate Table t_BarMarketData;";

constexpr const char* CreateMysqlDBMdSubscribeTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdSubscribe(ExchangeID char(8), InstrumentID char(32), RealInstrumentID char(32), ProductID char(32), ProductClass int, StartTradingDay char(9), EndTradingDay char(9), PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBMdSubscribeTableSqlString = "Truncate Table t_MdSubscribe;";

constexpr const char* CreateMysqlDBMdUserTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUser(MdUserID char(32), MdUserName char(64), Password char(64), PRIMARY KEY(MdUserID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBMdUserTableSqlString = "Truncate Table t_MdUser;";

constexpr const char* CreateMysqlDBMdUserLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(MdUserID char(32), SessionID bigint, IPAddress char(16), INDEX MdUserID(MdUserID), PRIMARY KEY(SessionID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBMdUserLoginSessionTableSqlString = "Truncate Table t_MdUserLoginSession;";

constexpr const char* CreateMysqlDBPrimaryAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_PrimaryAccount(PrimaryAccountID char(32), PrimaryAccountName char(64), AccountClass int, BrokerPassword char(64), OfferID int, IsAllowLogin bool, IsSimulateAccount bool, LoginStatus int, InitStatus int, INDEX OfferID(OfferID), PRIMARY KEY(PrimaryAccountID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBPrimaryAccountTableSqlString = "Truncate Table t_PrimaryAccount;";

constexpr const char* CreateMysqlDBAccountTableSqlString = "CREATE TABLE IF NOT EXISTS t_Account(AccountID char(32), AccountName char(64), AccountType int, AccountStatus int, Password char(64), TradeGroupID int, RiskGroupID int, CommissionGroupID int, PRIMARY KEY(AccountID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBAccountTableSqlString = "Truncate Table t_Account;";

constexpr const char* CreateMysqlDBCapitalTableSqlString = "CREATE TABLE IF NOT EXISTS t_Capital(TradingDay char(9), AccountID char(32), AccountType int, Balance double, PreBalance double, Available double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, Deposit double, Withdraw double, INDEX TradingDay(TradingDay), PRIMARY KEY(TradingDay, AccountID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBCapitalTableSqlString = "Truncate Table t_Capital;";

constexpr const char* CreateMysqlDBPositionTableSqlString = "CREATE TABLE IF NOT EXISTS t_Position(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, PosiDirection int, TotalPosition bigint, PositionFrozen bigint, TodayPosition bigint, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, FrozenCash double, FrozenMargin double, FrozenCommission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, INDEX Account(TradingDay, AccountID), INDEX TradingDay(TradingDay), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBPositionTableSqlString = "Truncate Table t_Position;";

constexpr const char* CreateMysqlDBPositionDetailTableSqlString = "CREATE TABLE IF NOT EXISTS t_PositionDetail(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, PosiDirection int, OpenDate char(9), TradeID char(64), Volume bigint, OpenPrice double, MarketValue double, CashIn double, CashOut double, Margin double, Commission double, VolumeMultiple int, CloseProfitByDate double, CloseProfitByTrade double, PositionProfitByDate double, PositionProfitByTrade double, SettlementPrice double, PreSettlementPrice double, CloseVolume bigint, CloseAmount double, INDEX TradeMatch(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection), INDEX TradingDay(TradingDay), PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBPositionDetailTableSqlString = "Truncate Table t_PositionDetail;";

constexpr const char* CreateMysqlDBOrderTableSqlString = "CREATE TABLE IF NOT EXISTS t_Order(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, OrderSysID char(64), Direction int, OffsetFlag int, OrderPriceType int, Price double, Volume bigint, VolumeTotal bigint, VolumeTraded bigint, VolumeMultiple int, OrderStatus int, OrderDate char(9), OrderTime char(9), CancelDate char(9), CancelTime char(9), SessionID bigint, ClientOrderID int, RequestID int, OfferID int, TradeGroupID int, RiskGroupID int, CommissionGroupID int, FrozenCash double, FrozenMargin double, FrozenCommission double, RebuildMark bool, IsForceClose bool, PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBOrderTableSqlString = "Truncate Table t_Order;";

constexpr const char* CreateMysqlDBTradeTableSqlString = "CREATE TABLE IF NOT EXISTS t_Trade(TradingDay char(9), AccountID char(32), AccountType int, ExchangeID char(8), InstrumentID char(32), ProductClass int, OrderID int, OrderSysID char(64), TradeID char(64), Direction int, OffsetFlag int, Price double, Volume bigint, VolumeMultiple int, TradeAmount double, Commission double, TradeDate char(9), TradeTime char(9), PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBTradeTableSqlString = "Truncate Table t_Trade;";

constexpr const char* CreateMysqlDBAccountLoginSessionTableSqlString = "CREATE TABLE IF NOT EXISTS t_AccountLoginSession(AccountID char(32), SessionID bigint, IPAddress char(16), INDEX AccountID(AccountID), PRIMARY KEY(SessionID)) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin';";
constexpr const char* TruncateMysqlDBAccountLoginSessionTableSqlString = "Truncate Table t_AccountLoginSession;";

