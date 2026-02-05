
CREATE TABLE IF NOT EXISTS t_TradingDay(
  `PK` int, 
  `CurrTradingDay` text, 
  `PreTradingDay` text, 
  PRIMARY KEY(PK)
);


CREATE TABLE IF NOT EXISTS t_Exchange(
  `ExchangeID` text, 
  `ExchangeName` text, 
  PRIMARY KEY(ExchangeID)
);


CREATE TABLE IF NOT EXISTS t_Product(
  `ExchangeID` text, 
  `ProductID` text, 
  `ProductName` text, 
  `ProductClass` int, 
  `VolumeMultiple` int, 
  `PriceTick` double, 
  `MaxMarketOrderVolume` bigint, 
  `MinMarketOrderVolume` bigint, 
  `MaxLimitOrderVolume` bigint, 
  `MinLimitOrderVolume` bigint, 
  `SessionName` text, 
  PRIMARY KEY(ExchangeID, ProductID)
);


CREATE TABLE IF NOT EXISTS t_HotInstrument(
  `TradingDay` text, 
  `ExchangeID` text, 
  `ProductID` text, 
  `InstrumentID` text, 
  `ProductClass` int, 
  `Volume` bigint, 
  `MaxVolume` bigint, 
  `Turnover` double, 
  `MaxTurnover` double, 
  `OpenInterest` double, 
  `MaxOpenInterest` double, 
  `Rank` int, 
  PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)
);
CREATE INDEX HotInstrumentTradingDay ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);


CREATE TABLE IF NOT EXISTS t_Instrument(
  `ExchangeID` text, 
  `InstrumentID` text, 
  `ExchangeInstID` text, 
  `InstrumentName` text, 
  `ProductID` text, 
  `ProductClass` int, 
  `InstrumentClass` int, 
  `Rank` int, 
  `VolumeMultiple` int, 
  `PriceTick` double, 
  `MaxMarketOrderVolume` bigint, 
  `MinMarketOrderVolume` bigint, 
  `MaxLimitOrderVolume` bigint, 
  `MinLimitOrderVolume` bigint, 
  `SessionName` text, 
  PRIMARY KEY(ExchangeID, InstrumentID)
);
CREATE INDEX InstrumentExchangeID ON t_Instrument(ExchangeID);


CREATE TABLE IF NOT EXISTS t_DepthMarketData(
  `TradingDay` text, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `UpdateTs` bigint, 
  `LastPrice` double, 
  `PreSettlementPrice` double, 
  `PreClosePrice` double, 
  `PreOpenInterest` double, 
  `OpenPrice` double, 
  `HighestPrice` double, 
  `LowestPrice` double, 
  `ClosePrice` double, 
  `CurrVolume` bigint, 
  `Volume` bigint, 
  `CurrTurnover` double, 
  `Turnover` double, 
  `OpenInterest` double, 
  `SettlementPrice` double, 
  `UpperLimitPrice` double, 
  `LowerLimitPrice` double, 
  `AveragePrice` double, 
  `AskPrice1` double, 
  `AskPrice2` double, 
  `AskPrice3` double, 
  `AskPrice4` double, 
  `AskPrice5` double, 
  `AskPrice6` double, 
  `AskPrice7` double, 
  `AskPrice8` double, 
  `AskPrice9` double, 
  `AskPrice10` double, 
  `AskVolume1` bigint, 
  `AskVolume2` bigint, 
  `AskVolume3` bigint, 
  `AskVolume4` bigint, 
  `AskVolume5` bigint, 
  `AskVolume6` bigint, 
  `AskVolume7` bigint, 
  `AskVolume8` bigint, 
  `AskVolume9` bigint, 
  `AskVolume10` bigint, 
  `BidPrice1` double, 
  `BidPrice2` double, 
  `BidPrice3` double, 
  `BidPrice4` double, 
  `BidPrice5` double, 
  `BidPrice6` double, 
  `BidPrice7` double, 
  `BidPrice8` double, 
  `BidPrice9` double, 
  `BidPrice10` double, 
  `BidVolume1` bigint, 
  `BidVolume2` bigint, 
  `BidVolume3` bigint, 
  `BidVolume4` bigint, 
  `BidVolume5` bigint, 
  `BidVolume6` bigint, 
  `BidVolume7` bigint, 
  `BidVolume8` bigint, 
  `BidVolume9` bigint, 
  `BidVolume10` bigint, 
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)
);


CREATE TABLE IF NOT EXISTS t_BarMarketData(
  `TradingDay` text, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `BarPreces` int, 
  `BarPeriod` int, 
  `BarTime` bigint, 
  `UpdateTs` bigint, 
  `PreSettlementPrice` double, 
  `PreClosePrice` double, 
  `HighestPrice` double, 
  `LowestPrice` double, 
  `Open` double, 
  `High` double, 
  `Low` double, 
  `Close` double, 
  `CurrVolume` bigint, 
  `Volume` bigint, 
  `CurrTurnover` double, 
  `Turnover` double, 
  `OpenInterest` double, 
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)
);


CREATE TABLE IF NOT EXISTS t_MdSubscribe(
  `ExchangeID` text, 
  `InstrumentID` text, 
  `RealInstrumentID` text, 
  `ProductID` text, 
  `ProductClass` int, 
  `StartTradingDay` text, 
  `EndTradingDay` text, 
  PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)
);


CREATE TABLE IF NOT EXISTS t_MdUser(
  `MdUserID` text, 
  `MdUserName` text, 
  `Password` text, 
  PRIMARY KEY(MdUserID)
);


CREATE TABLE IF NOT EXISTS t_MdUserLoginSession(
  `MdUserID` text, 
  `SessionID` bigint, 
  `IPAddress` text, 
  PRIMARY KEY(SessionID)
);
CREATE INDEX MdUserLoginSessionMdUserID ON t_MdUserLoginSession(MdUserID);


CREATE TABLE IF NOT EXISTS t_PrimaryAccount(
  `PrimaryAccountID` text, 
  `PrimaryAccountName` text, 
  `AccountClass` int, 
  `Password` text, 
  `OfferID` int, 
  `IsAllowLogin` int, 
  `IsSimulateAccount` int, 
  `LoginStatus` int, 
  `InitStatus` int, 
  PRIMARY KEY(PrimaryAccountID)
);
CREATE INDEX PrimaryAccountOfferID ON t_PrimaryAccount(OfferID);


CREATE TABLE IF NOT EXISTS t_Account(
  `AccountID` text, 
  `AccountName` text, 
  `AccountType` int, 
  `AccountStatus` int, 
  `Password` text, 
  `TradeGroupID` int, 
  `RiskGroupID` int, 
  `CommissionGroupID` int, 
  PRIMARY KEY(AccountID)
);


CREATE TABLE IF NOT EXISTS t_Capital(
  `TradingDay` text, 
  `AccountID` text, 
  `AccountType` int, 
  `Balance` double, 
  `PreBalance` double, 
  `Available` double, 
  `MarketValue` double, 
  `CashIn` double, 
  `CashOut` double, 
  `Margin` double, 
  `Commission` double, 
  `FrozenCash` double, 
  `FrozenMargin` double, 
  `FrozenCommission` double, 
  `CloseProfitByDate` double, 
  `CloseProfitByTrade` double, 
  `PositionProfitByDate` double, 
  `PositionProfitByTrade` double, 
  `Deposit` double, 
  `Withdraw` double, 
  PRIMARY KEY(TradingDay, AccountID)
);
CREATE INDEX CapitalTradingDay ON t_Capital(TradingDay);


CREATE TABLE IF NOT EXISTS t_Position(
  `TradingDay` text, 
  `AccountID` text, 
  `AccountType` int, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `ProductClass` int, 
  `PosiDirection` int, 
  `TotalPosition` bigint, 
  `PositionFrozen` bigint, 
  `TodayPosition` bigint, 
  `MarketValue` double, 
  `CashIn` double, 
  `CashOut` double, 
  `Margin` double, 
  `Commission` double, 
  `FrozenCash` double, 
  `FrozenMargin` double, 
  `FrozenCommission` double, 
  `VolumeMultiple` int, 
  `CloseProfitByDate` double, 
  `CloseProfitByTrade` double, 
  `PositionProfitByDate` double, 
  `PositionProfitByTrade` double, 
  `SettlementPrice` double, 
  `PreSettlementPrice` double, 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)
);
CREATE INDEX PositionAccount ON t_Position(TradingDay, AccountID);
CREATE INDEX PositionTradingDay ON t_Position(TradingDay);


CREATE TABLE IF NOT EXISTS t_PositionDetail(
  `TradingDay` text, 
  `AccountID` text, 
  `AccountType` int, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `ProductClass` int, 
  `PosiDirection` int, 
  `OpenDate` text, 
  `TradeID` text, 
  `Volume` bigint, 
  `OpenPrice` double, 
  `MarketValue` double, 
  `CashIn` double, 
  `CashOut` double, 
  `Margin` double, 
  `Commission` double, 
  `VolumeMultiple` int, 
  `CloseProfitByDate` double, 
  `CloseProfitByTrade` double, 
  `PositionProfitByDate` double, 
  `PositionProfitByTrade` double, 
  `SettlementPrice` double, 
  `PreSettlementPrice` double, 
  `CloseVolume` bigint, 
  `CloseAmount` double, 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)
);
CREATE INDEX PositionDetailTradeMatch ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
CREATE INDEX PositionDetailTradingDay ON t_PositionDetail(TradingDay);


CREATE TABLE IF NOT EXISTS t_Order(
  `TradingDay` text, 
  `AccountID` text, 
  `AccountType` int, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `ProductClass` int, 
  `OrderID` int, 
  `OrderSysID` text, 
  `Direction` int, 
  `OffsetFlag` int, 
  `OrderPriceType` int, 
  `Price` double, 
  `Volume` bigint, 
  `VolumeTotal` bigint, 
  `VolumeTraded` bigint, 
  `VolumeMultiple` int, 
  `OrderStatus` int, 
  `OrderDate` text, 
  `OrderTime` text, 
  `CancelDate` text, 
  `CancelTime` text, 
  `SessionID` bigint, 
  `ClientOrderID` int, 
  `RequestID` int, 
  `OfferID` int, 
  `TradeGroupID` int, 
  `RiskGroupID` int, 
  `CommissionGroupID` int, 
  `FrozenCash` double, 
  `FrozenMargin` double, 
  `FrozenCommission` double, 
  `RebuildMark` int, 
  `IsForceClose` int, 
  UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID), 
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)
);
CREATE INDEX OrderAccountID ON t_Order(TradingDay, AccountID);


CREATE TABLE IF NOT EXISTS t_Trade(
  `TradingDay` text, 
  `AccountID` text, 
  `AccountType` int, 
  `ExchangeID` text, 
  `InstrumentID` text, 
  `ProductClass` int, 
  `OrderID` int, 
  `OrderSysID` text, 
  `TradeID` text, 
  `Direction` int, 
  `OffsetFlag` int, 
  `Price` double, 
  `Volume` bigint, 
  `VolumeMultiple` int, 
  `TradeAmount` double, 
  `Commission` double, 
  `TradeDate` text, 
  `TradeTime` text, 
  PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)
);
CREATE INDEX TradeAccountID ON t_Trade(TradingDay, AccountID);


CREATE TABLE IF NOT EXISTS t_AccountLoginSession(
  `AccountID` text, 
  `SessionID` bigint, 
  `IPAddress` text, 
  PRIMARY KEY(SessionID)
);
CREATE INDEX AccountLoginSessionAccountID ON t_AccountLoginSession(AccountID);


