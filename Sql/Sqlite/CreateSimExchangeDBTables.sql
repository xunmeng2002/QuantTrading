
CREATE TABLE IF NOT EXISTS `t_TradingDay` (
  `PK` int,  -- '主键'
  `CurrTradingDay` text,  -- '当前交易日'
  `PreTradingDay` text,  -- '昨交易日'
  PRIMARY KEY(PK)
);  -- '交易日'


CREATE TABLE IF NOT EXISTS `t_Exchange` (
  `ExchangeID` text,  -- '交易所代码'
  `ExchangeName` text,  -- '交易所名称'
  PRIMARY KEY(ExchangeID)
);  -- '交易所'


CREATE TABLE IF NOT EXISTS `t_Product` (
  `ExchangeID` text,  -- '交易所代码'
  `ProductID` text,  -- '品种代码'
  `ProductName` text,  -- '品种名称'
  `ProductClass` int,  -- '品种类型'
  `VolumeMultiple` int,  -- '合约乘数'
  `PriceTick` double,  -- '最小变动价位'
  `MaxMarketOrderVolume` bigint,  -- '市价最大下单量'
  `MinMarketOrderVolume` bigint,  -- '市价最小下单量'
  `MaxLimitOrderVolume` bigint,  -- '限价最大下单量'
  `MinLimitOrderVolume` bigint,  -- '限价最小下单量'
  `SessionName` text,  -- '交易节名称'
  PRIMARY KEY(ExchangeID, ProductID)
);  -- '品种表'


CREATE TABLE IF NOT EXISTS `t_HotInstrument` (
  `TradingDay` text,  -- '交易日'
  `ExchangeID` text,  -- '交易所代码'
  `ProductID` text,  -- '品种代码'
  `InstrumentID` text,  -- '合约代码'
  `ProductClass` int,  -- '品种类型'
  `Volume` bigint,  -- '委托数量'
  `MaxVolume` bigint,  -- '最大数量'
  `Turnover` double,  -- '成交金额'
  `MaxTurnover` double,  -- '最大成交金额'
  `OpenInterest` double,  -- '持仓量'
  `MaxOpenInterest` double,  -- '最大持仓量'
  `Rank` int,  -- '级别'
  PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)
);  -- '主力合约表'
  CREATE INDEX TradingDay ON t_HotInstrument(ExchangeID, ProductID, Rank, TradingDay);


CREATE TABLE IF NOT EXISTS `t_Instrument` (
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `ExchangeInstID` text,  -- '交易所合约代码'
  `InstrumentName` text,  -- '合约名称'
  `ProductID` text,  -- '品种代码'
  `ProductClass` int,  -- '品种类型'
  `InstrumentClass` int,  -- '合约类别'
  `Rank` int,  -- '级别'
  `VolumeMultiple` int,  -- '合约乘数'
  `PriceTick` double,  -- '最小变动价位'
  `MaxMarketOrderVolume` bigint,  -- '市价最大下单量'
  `MinMarketOrderVolume` bigint,  -- '市价最小下单量'
  `MaxLimitOrderVolume` bigint,  -- '限价最大下单量'
  `MinLimitOrderVolume` bigint,  -- '限价最小下单量'
  `SessionName` text,  -- '交易节名称'
  PRIMARY KEY(ExchangeID, InstrumentID)
);  -- '合约'


CREATE TABLE IF NOT EXISTS `t_PrimaryAccount` (
  `TradingDay` text,  -- '交易日'
  `PrimaryAccountID` text,  -- '主账户代码'
  `PrimaryAccountName` text,  -- '主账户名称'
  `AccountClass` int,  -- '账户类别'
  `BrokerPassword` text,  -- '经纪公司密码'
  `OfferID` int,  -- '报盘代码'
  `IsAllowLogin` int,  -- '是否允许登陆'
  `IsSimulateAccount` int,  -- '是否模拟账号'
  `LoginStatus` int,  -- '登录状态'
  `InitStatus` int,  -- '初始化状态'
  PRIMARY KEY(PrimaryAccountID)
);  -- '主账户'
  CREATE INDEX OfferID ON t_PrimaryAccount(OfferID);


CREATE TABLE IF NOT EXISTS `t_Account` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountName` text,  -- '账户名称'
  `AccountType` int,  -- '账户类型'
  `AccountStatus` int,  -- '账户状态'
  `Password` text,  -- '密码'
  `TradeGroupID` int,  -- '交易组代码'
  `RiskGroupID` int,  -- '交易组代码'
  `CommissionGroupID` int,  -- '交易组代码'
  PRIMARY KEY(AccountID)
);  -- '账户'


CREATE TABLE IF NOT EXISTS `t_Capital` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountType` int,  -- '账户类型'
  `Balance` double,  -- '权益'
  `PreBalance` double,  -- '上日权益'
  `Available` double,  -- '可用资金'
  `MarketValue` double,  -- '市值'
  `CashIn` double,  -- '现金收入'
  `CashOut` double,  -- '现金支出'
  `Margin` double,  -- '保证金'
  `Commission` double,  -- '手续费'
  `FrozenCash` double,  -- '冻结资金'
  `FrozenMargin` double,  -- '冻结保证金'
  `FrozenCommission` double,  -- '冻结手续费'
  `CloseProfitByDate` double,  -- '逐日平仓盈亏'
  `CloseProfitByTrade` double,  -- '逐笔平仓盈亏'
  `PositionProfitByDate` double,  -- '逐日持仓盈亏'
  `PositionProfitByTrade` double,  -- '逐笔持仓盈亏'
  `Deposit` double,  -- '入金'
  `Withdraw` double,  -- '出金'
  PRIMARY KEY(AccountID)
);  -- '资金'
  CREATE INDEX TradingDay ON t_Capital(TradingDay);


CREATE TABLE IF NOT EXISTS `t_Position` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountType` int,  -- '账户类型'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `ProductClass` int,  -- '品种类型'
  `PosiDirection` int,  -- '持仓方向'
  `TotalPosition` bigint,  -- '持仓数量'
  `PositionFrozen` bigint,  -- '冻结持仓'
  `TodayPosition` bigint,  -- '今日持仓'
  `MarketValue` double,  -- '市值'
  `CashIn` double,  -- '现金收入'
  `CashOut` double,  -- '现金支出'
  `Margin` double,  -- '保证金'
  `Commission` double,  -- '手续费'
  `FrozenCash` double,  -- '冻结资金'
  `FrozenMargin` double,  -- '冻结保证金'
  `FrozenCommission` double,  -- '冻结手续费'
  `VolumeMultiple` int,  -- '合约乘数'
  `CloseProfitByDate` double,  -- '逐日平仓盈亏'
  `CloseProfitByTrade` double,  -- '逐笔平仓盈亏'
  `PositionProfitByDate` double,  -- '逐日持仓盈亏'
  `PositionProfitByTrade` double,  -- '逐笔持仓盈亏'
  `SettlementPrice` double,  -- '结算价'
  `PreSettlementPrice` double,  -- '昨结算价'
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)
);  -- '持仓'
  CREATE INDEX Account ON t_Position(TradingDay, AccountID);
  CREATE INDEX TradingDay ON t_Position(TradingDay);


CREATE TABLE IF NOT EXISTS `t_PositionDetail` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountType` int,  -- '账户类型'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `ProductClass` int,  -- '品种类型'
  `PosiDirection` int,  -- '持仓方向'
  `OpenDate` text,  -- '开仓日期'
  `TradeID` text,  -- '成交编号'
  `Volume` bigint,  -- '委托数量'
  `OpenPrice` double,  -- '开盘价'
  `MarketValue` double,  -- '市值'
  `CashIn` double,  -- '现金收入'
  `CashOut` double,  -- '现金支出'
  `Margin` double,  -- '保证金'
  `Commission` double,  -- '手续费'
  `VolumeMultiple` int,  -- '合约乘数'
  `CloseProfitByDate` double,  -- '逐日平仓盈亏'
  `CloseProfitByTrade` double,  -- '逐笔平仓盈亏'
  `PositionProfitByDate` double,  -- '逐日持仓盈亏'
  `PositionProfitByTrade` double,  -- '逐笔持仓盈亏'
  `SettlementPrice` double,  -- '结算价'
  `PreSettlementPrice` double,  -- '昨结算价'
  `CloseVolume` bigint,  -- '平仓数量'
  `CloseAmount` double,  -- '平仓金额'
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)
);  -- '持仓明细'
  CREATE INDEX TradeMatch ON t_PositionDetail(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
  CREATE INDEX TradingDay ON t_PositionDetail(TradingDay);


CREATE TABLE IF NOT EXISTS `t_Order` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountType` int,  -- '账户类型'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `ProductClass` int,  -- '品种类型'
  `OrderID` int,  -- '委托编号'
  `OrderSysID` text,  -- '系统委托编号'
  `Direction` int,  -- '买卖方向'
  `OffsetFlag` int,  -- '开平标志'
  `OrderPriceType` int,  -- '委托价格类型'
  `Price` double,  -- '委托价格'
  `Volume` bigint,  -- '委托数量'
  `VolumeTotal` bigint,  -- '剩余数量'
  `VolumeTraded` bigint,  -- '成交数量'
  `VolumeMultiple` int,  -- '合约乘数'
  `OrderStatus` int,  -- '委托状态'
  `OrderDate` text,  -- '委托日期'
  `OrderTime` text,  -- '委托时间'
  `CancelDate` text,  -- '撤单日期'
  `CancelTime` text,  -- '撤单时间'
  `SessionID` bigint,  -- '会话编号'
  `ClientOrderID` int,  -- '客户端委托编号'
  `RequestID` int,  -- '客户端请求编号'
  `OfferID` int,  -- '报盘代码'
  `TradeGroupID` int,  -- '交易组代码'
  `RiskGroupID` int,  -- '交易组代码'
  `CommissionGroupID` int,  -- '交易组代码'
  `FrozenCash` double,  -- '冻结资金'
  `FrozenMargin` double,  -- '冻结保证金'
  `FrozenCommission` double,  -- '冻结手续费'
  `RebuildMark` int,  -- '重建标志'
  `IsForceClose` int,  -- '是否强平单'
  UNIQUE (TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID),
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)
);  -- '委托'


CREATE TABLE IF NOT EXISTS `t_Trade` (
  `TradingDay` text,  -- '交易日'
  `AccountID` text,  -- '账户代码'
  `AccountType` int,  -- '账户类型'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `ProductClass` int,  -- '品种类型'
  `OrderID` int,  -- '委托编号'
  `OrderSysID` text,  -- '系统委托编号'
  `TradeID` text,  -- '成交编号'
  `Direction` int,  -- '买卖方向'
  `OffsetFlag` int,  -- '开平标志'
  `Price` double,  -- '委托价格'
  `Volume` bigint,  -- '委托数量'
  `VolumeMultiple` int,  -- '合约乘数'
  `TradeAmount` double,  -- '成交金额'
  `Commission` double,  -- '手续费'
  `TradeDate` text,  -- '成交日期'
  `TradeTime` text,  -- '成交时间'
  PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)
);  -- '成交'


CREATE TABLE IF NOT EXISTS `t_DepthMarketData` (
  `TradingDay` text,  -- '交易日'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `UpdateTs` bigint,  -- '更新时间戳'
  `LastPrice` double,  -- '最新价'
  `PreSettlementPrice` double,  -- '昨结算价'
  `PreClosePrice` double,  -- '昨收盘价'
  `PreOpenInterest` double,  -- '上日持仓量'
  `OpenPrice` double,  -- '开盘价'
  `HighestPrice` double,  -- '最高价'
  `LowestPrice` double,  -- '最低价'
  `ClosePrice` double,  -- '收盘价'
  `CurrVolume` bigint,  -- '当前数量'
  `Volume` bigint,  -- '委托数量'
  `CurrTurnover` double,  -- '当前成交金额'
  `Turnover` double,  -- '成交金额'
  `OpenInterest` double,  -- '持仓量'
  `SettlementPrice` double,  -- '结算价'
  `UpperLimitPrice` double,  -- '涨停板价'
  `LowerLimitPrice` double,  -- '跌停板价'
  `AveragePrice` double,  -- '当日均价'
  `AskPrice1` double,  -- '申卖价一'
  `AskPrice2` double,  -- '申卖价二'
  `AskPrice3` double,  -- '申卖价三'
  `AskPrice4` double,  -- '申卖价四'
  `AskPrice5` double,  -- '申卖价五'
  `AskPrice6` double,  -- '申卖价六'
  `AskPrice7` double,  -- '申卖价七'
  `AskPrice8` double,  -- '申卖价八'
  `AskPrice9` double,  -- '申卖价九'
  `AskPrice10` double,  -- '申卖价十'
  `AskVolume1` bigint,  -- '申卖量一'
  `AskVolume2` bigint,  -- '申卖量二'
  `AskVolume3` bigint,  -- '申卖量三'
  `AskVolume4` bigint,  -- '申卖量四'
  `AskVolume5` bigint,  -- '申卖量五'
  `AskVolume6` bigint,  -- '申卖量六'
  `AskVolume7` bigint,  -- '申卖量七'
  `AskVolume8` bigint,  -- '申卖量八'
  `AskVolume9` bigint,  -- '申卖量九'
  `AskVolume10` bigint,  -- '申卖量十'
  `BidPrice1` double,  -- '申买价一'
  `BidPrice2` double,  -- '申买价二'
  `BidPrice3` double,  -- '申买价三'
  `BidPrice4` double,  -- '申买价四'
  `BidPrice5` double,  -- '申买价五'
  `BidPrice6` double,  -- '申买价六'
  `BidPrice7` double,  -- '申买价七'
  `BidPrice8` double,  -- '申买价八'
  `BidPrice9` double,  -- '申买价九'
  `BidPrice10` double,  -- '申买价十'
  `BidVolume1` bigint,  -- '申买量一'
  `BidVolume2` bigint,  -- '申买量二'
  `BidVolume3` bigint,  -- '申买量三'
  `BidVolume4` bigint,  -- '申买量四'
  `BidVolume5` bigint,  -- '申买量五'
  `BidVolume6` bigint,  -- '申买量六'
  `BidVolume7` bigint,  -- '申买量七'
  `BidVolume8` bigint,  -- '申买量八'
  `BidVolume9` bigint,  -- '申买量九'
  `BidVolume10` bigint,  -- '申买量十'
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)
);  -- '深度行情'


CREATE TABLE IF NOT EXISTS `t_BarMarketData` (
  `TradingDay` text,  -- '交易日'
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `BarPreces` int,  -- 'Bar精度'
  `BarPeriod` int,  -- 'Bar周期'
  `BarTime` bigint,  -- 'Bar时间'
  `UpdateTs` bigint,  -- '更新时间戳'
  `PreSettlementPrice` double,  -- '昨结算价'
  `PreClosePrice` double,  -- '昨收盘价'
  `Open` double,  -- '开盘价'
  `High` double,  -- '最高价'
  `Low` double,  -- '最低价'
  `Close` double,  -- '收盘价'
  `CurrVolume` bigint,  -- '当前数量'
  `Volume` bigint,  -- '委托数量'
  `CurrTurnover` double,  -- '当前成交金额'
  `Turnover` double,  -- '成交金额'
  `OpenInterest` double,  -- '持仓量'
  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)
);  -- 'Bar行情'


CREATE TABLE IF NOT EXISTS `t_MdSubscribe` (
  `ExchangeID` text,  -- '交易所代码'
  `InstrumentID` text,  -- '合约代码'
  `RealInstrumentID` text,  -- '真实合约代码'
  `ProductID` text,  -- '品种代码'
  `ProductClass` int,  -- '品种类型'
  `StartTradingDay` text,  -- '开始交易日'
  `EndTradingDay` text,  -- '结束交易日'
  PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)
);  -- '行情订阅'



