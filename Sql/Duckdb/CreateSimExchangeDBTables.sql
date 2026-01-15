
CREATE TABLE IF NOT EXISTS t_TradingDay(
  PK int, 
  CurrTradingDay varchar, 
  PreTradingDay varchar, 
  PRIMARY KEY(PK)
);  -- '交易日'


CREATE TABLE IF NOT EXISTS t_Exchange(
  ExchangeID varchar, 
  ExchangeName varchar, 
  PRIMARY KEY(ExchangeID)
);  -- '交易所'


CREATE TABLE IF NOT EXISTS t_Product(
  ExchangeID varchar, 
  ProductID varchar, 
  ProductName varchar, 
  ProductClass int, 
  VolumeMultiple int, 
  PriceTick double, 
  MaxMarketOrderVolume bigint, 
  MinMarketOrderVolume bigint, 
  MaxLimitOrderVolume bigint, 
  MinLimitOrderVolume bigint, 
  SessionName varchar, 
  PRIMARY KEY(ExchangeID, ProductID)
);  -- '品种表'


CREATE TABLE IF NOT EXISTS t_HotInstrument(
  TradingDay varchar, 
  ExchangeID varchar, 
  ProductID varchar, 
  InstrumentID varchar, 
  ProductClass int, 
  Volume bigint, 
  MaxVolume bigint, 
  Turnover double, 
  MaxTurnover double, 
  OpenInterest double, 
  MaxOpenInterest double, 
  Rank int, 
  PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)
);  -- '主力合约表'
  CREATE INDEX HotInstrumentTradingDay ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);


CREATE TABLE IF NOT EXISTS t_Instrument(
  ExchangeID varchar, 
  InstrumentID varchar, 
  ExchangeInstID varchar, 
  InstrumentName varchar, 
  ProductID varchar, 
  ProductClass int, 
  InstrumentClass int, 
  Rank int, 
  VolumeMultiple int, 
  PriceTick double, 
  MaxMarketOrderVolume bigint, 
  MinMarketOrderVolume bigint, 
  MaxLimitOrderVolume bigint, 
  MinLimitOrderVolume bigint, 
  SessionName varchar, 
  PRIMARY KEY(ExchangeID, InstrumentID)
);  -- '合约'


CREATE TABLE IF NOT EXISTS t_DepthMarketData(
  TradingDay varchar, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  UpdateTs bigint, 
  LastPrice double, 
  PreSettlementPrice double, 
  PreClosePrice double, 
  PreOpenInterest double, 
  OpenPrice double, 
  HighestPrice double, 
  LowestPrice double, 
  ClosePrice double, 
  CurrVolume bigint, 
  Volume bigint, 
  CurrTurnover double, 
  Turnover double, 
  OpenInterest double, 
  SettlementPrice double, 
  UpperLimitPrice double, 
  LowerLimitPrice double, 
  AveragePrice double, 
  AskPrice1 double, 
  AskPrice2 double, 
  AskPrice3 double, 
  AskPrice4 double, 
  AskPrice5 double, 
  AskPrice6 double, 
  AskPrice7 double, 
  AskPrice8 double, 
  AskPrice9 double, 
  AskPrice10 double, 
  AskVolume1 bigint, 
  AskVolume2 bigint, 
  AskVolume3 bigint, 
  AskVolume4 bigint, 
  AskVolume5 bigint, 
  AskVolume6 bigint, 
  AskVolume7 bigint, 
  AskVolume8 bigint, 
  AskVolume9 bigint, 
  AskVolume10 bigint, 
  BidPrice1 double, 
  BidPrice2 double, 
  BidPrice3 double, 
  BidPrice4 double, 
  BidPrice5 double, 
  BidPrice6 double, 
  BidPrice7 double, 
  BidPrice8 double, 
  BidPrice9 double, 
  BidPrice10 double, 
  BidVolume1 bigint, 
  BidVolume2 bigint, 
  BidVolume3 bigint, 
  BidVolume4 bigint, 
  BidVolume5 bigint, 
  BidVolume6 bigint, 
  BidVolume7 bigint, 
  BidVolume8 bigint, 
  BidVolume9 bigint, 
  BidVolume10 bigint, 
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)
);  -- '深度行情'


CREATE TABLE IF NOT EXISTS t_BarMarketData(
  TradingDay varchar, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  BarPreces int, 
  BarPeriod int, 
  BarTime bigint, 
  UpdateTs bigint, 
  PreSettlementPrice double, 
  PreClosePrice double, 
  Open double, 
  High double, 
  Low double, 
  Close double, 
  CurrVolume bigint, 
  Volume bigint, 
  CurrTurnover double, 
  Turnover double, 
  OpenInterest double, 
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)
);  -- 'Bar行情'


CREATE TABLE IF NOT EXISTS t_MdSubscribe(
  ExchangeID varchar, 
  InstrumentID varchar, 
  RealInstrumentID varchar, 
  ProductID varchar, 
  ProductClass int, 
  StartTradingDay varchar, 
  EndTradingDay varchar, 
  PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)
);  -- '行情订阅'


CREATE TABLE IF NOT EXISTS t_MdUser(
  MdUserID varchar, 
  MdUserName varchar, 
  Password varchar, 
  PRIMARY KEY(MdUserID)
);  -- '账户'


CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(
  MdUserID varchar, 
  SessionID bigint, 
  IPAddress varchar, 
  PRIMARY KEY(SessionID)
);  -- '行情用户登录会话'
  CREATE INDEX MdUserLoginSessionMdUserID ON t_MdUserLoginSession(MdUserID);


CREATE TABLE IF NOT EXISTS t_PrimaryAccount(
  PrimaryAccountID varchar, 
  PrimaryAccountName varchar, 
  AccountClass int, 
  Password varchar, 
  OfferID int, 
  IsAllowLogin int, 
  IsSimulateAccount int, 
  LoginStatus int, 
  InitStatus int, 
  PRIMARY KEY(PrimaryAccountID)
);  -- '主账户'
  CREATE INDEX PrimaryAccountOfferID ON t_PrimaryAccount(OfferID);


CREATE TABLE IF NOT EXISTS t_Account(
  AccountID varchar, 
  AccountName varchar, 
  AccountType int, 
  AccountStatus int, 
  Password varchar, 
  TradeGroupID int, 
  RiskGroupID int, 
  CommissionGroupID int, 
  PRIMARY KEY(AccountID)
);  -- '账户'


CREATE TABLE IF NOT EXISTS t_Capital(
  TradingDay varchar, 
  AccountID varchar, 
  AccountType int, 
  Balance double, 
  PreBalance double, 
  Available double, 
  MarketValue double, 
  CashIn double, 
  CashOut double, 
  Margin double, 
  Commission double, 
  FrozenCash double, 
  FrozenMargin double, 
  FrozenCommission double, 
  CloseProfitByDate double, 
  CloseProfitByTrade double, 
  PositionProfitByDate double, 
  PositionProfitByTrade double, 
  Deposit double, 
  Withdraw double, 
  PRIMARY KEY(TradingDay, AccountID)
);  -- '资金'
  CREATE INDEX CapitalTradingDay ON t_Capital(TradingDay);


CREATE TABLE IF NOT EXISTS t_Position(
  TradingDay varchar, 
  AccountID varchar, 
  AccountType int, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  ProductClass int, 
  PosiDirection int, 
  TotalPosition bigint, 
  PositionFrozen bigint, 
  TodayPosition bigint, 
  MarketValue double, 
  CashIn double, 
  CashOut double, 
  Margin double, 
  Commission double, 
  FrozenCash double, 
  FrozenMargin double, 
  FrozenCommission double, 
  VolumeMultiple int, 
  CloseProfitByDate double, 
  CloseProfitByTrade double, 
  PositionProfitByDate double, 
  PositionProfitByTrade double, 
  SettlementPrice double, 
  PreSettlementPrice double, 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)
);  -- '持仓'
  CREATE INDEX PositionAccount ON t_Position(TradingDay, AccountID);
  CREATE INDEX PositionTradingDay ON t_Position(TradingDay);


CREATE TABLE IF NOT EXISTS t_PositionDetail(
  TradingDay varchar, 
  AccountID varchar, 
  AccountType int, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  ProductClass int, 
  PosiDirection int, 
  OpenDate varchar, 
  TradeID varchar, 
  Volume bigint, 
  OpenPrice double, 
  MarketValue double, 
  CashIn double, 
  CashOut double, 
  Margin double, 
  Commission double, 
  VolumeMultiple int, 
  CloseProfitByDate double, 
  CloseProfitByTrade double, 
  PositionProfitByDate double, 
  PositionProfitByTrade double, 
  SettlementPrice double, 
  PreSettlementPrice double, 
  CloseVolume bigint, 
  CloseAmount double, 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)
);  -- '持仓明细'
  CREATE INDEX PositionDetailTradeMatch ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
  CREATE INDEX PositionDetailTradingDay ON t_PositionDetail(TradingDay);


CREATE TABLE IF NOT EXISTS t_Order(
  TradingDay varchar, 
  AccountID varchar, 
  AccountType int, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  ProductClass int, 
  OrderID int, 
  OrderSysID varchar, 
  Direction int, 
  OffsetFlag int, 
  OrderPriceType int, 
  Price double, 
  Volume bigint, 
  VolumeTotal bigint, 
  VolumeTraded bigint, 
  VolumeMultiple int, 
  OrderStatus int, 
  OrderDate varchar, 
  OrderTime varchar, 
  CancelDate varchar, 
  CancelTime varchar, 
  SessionID bigint, 
  ClientOrderID int, 
  RequestID int, 
  OfferID int, 
  TradeGroupID int, 
  RiskGroupID int, 
  CommissionGroupID int, 
  FrozenCash double, 
  FrozenMargin double, 
  FrozenCommission double, 
  RebuildMark int, 
  IsForceClose int, 
  UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)
);  -- '委托'


CREATE TABLE IF NOT EXISTS t_Trade(
  TradingDay varchar, 
  AccountID varchar, 
  AccountType int, 
  ExchangeID varchar, 
  InstrumentID varchar, 
  ProductClass int, 
  OrderID int, 
  OrderSysID varchar, 
  TradeID varchar, 
  Direction int, 
  OffsetFlag int, 
  Price double, 
  Volume bigint, 
  VolumeMultiple int, 
  TradeAmount double, 
  Commission double, 
  TradeDate varchar, 
  TradeTime varchar, 
  PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)
);  -- '成交'


CREATE TABLE IF NOT EXISTS t_AccountLoginSession(
  AccountID varchar, 
  SessionID bigint, 
  IPAddress varchar, 
  PRIMARY KEY(SessionID)
);  -- '账户登录会话'
  CREATE INDEX AccountLoginSessionAccountID ON t_AccountLoginSession(AccountID);


