
CREATE TABLE IF NOT EXISTS `t_TradingDay` (
  `PK` int COMMENT '主键',
  `CurrTradingDay` char(9) COMMENT '当前交易日',
  `PreTradingDay` char(9) COMMENT '昨交易日',

  PRIMARY KEY(PK)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='交易日';

CREATE TABLE IF NOT EXISTS `t_Exchange` (
  `ExchangeID` char(8) COMMENT '交易所代码',
  `ExchangeName` char(64) COMMENT '交易所名称',

  PRIMARY KEY(ExchangeID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='交易所';

CREATE TABLE IF NOT EXISTS `t_Product` (
  `ExchangeID` char(8) COMMENT '交易所代码',
  `ProductID` char(32) COMMENT '品种代码',
  `ProductName` char(32) COMMENT '品种名称',
  `ProductClass` int COMMENT '品种类型',
  `VolumeMultiple` int COMMENT '合约乘数',
  `PriceTick` decimal(24,8) COMMENT '最小变动价位',
  `MaxMarketOrderVolume` bigint COMMENT '市价最大下单量',
  `MinMarketOrderVolume` bigint COMMENT '市价最小下单量',
  `MaxLimitOrderVolume` bigint COMMENT '限价最大下单量',
  `MinLimitOrderVolume` bigint COMMENT '限价最小下单量',
  `SessionName` char(32) COMMENT '交易节名称',

  PRIMARY KEY(ExchangeID, ProductID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='品种表';

CREATE TABLE IF NOT EXISTS `t_HotInstrument` (
  `TradingDay` char(9) COMMENT '交易日',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `ProductID` char(32) COMMENT '品种代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `Volume` bigint COMMENT '委托数量',
  `MaxVolume` bigint COMMENT '最大数量',
  `Turnover` decimal(24,8) COMMENT '成交金额',
  `MaxTurnover` decimal(24,8) COMMENT '最大成交金额',
  `OpenInterest` decimal(24,8) COMMENT '持仓量',
  `MaxOpenInterest` decimal(24,8) COMMENT '最大持仓量',
  `Rank` int COMMENT '级别',

  INDEX TradingDay(ExchangeID, ProductID, Rank, TradingDay),
  PRIMARY KEY(TradingDay, ExchangeID, ProductID, Rank)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='主力合约表';

CREATE TABLE IF NOT EXISTS `t_Instrument` (
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ExchangeInstID` char(32) COMMENT '交易所合约代码',
  `InstrumentName` char(64) COMMENT '合约名称',
  `ProductID` char(32) COMMENT '品种代码',
  `ProductClass` int COMMENT '品种类型',
  `InstrumentClass` int COMMENT '合约类别',
  `Rank` int COMMENT '级别',
  `VolumeMultiple` int COMMENT '合约乘数',
  `PriceTick` decimal(24,8) COMMENT '最小变动价位',
  `MaxMarketOrderVolume` bigint COMMENT '市价最大下单量',
  `MinMarketOrderVolume` bigint COMMENT '市价最小下单量',
  `MaxLimitOrderVolume` bigint COMMENT '限价最大下单量',
  `MinLimitOrderVolume` bigint COMMENT '限价最小下单量',
  `SessionName` char(32) COMMENT '交易节名称',

  PRIMARY KEY(ExchangeID, InstrumentID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='合约';

CREATE TABLE IF NOT EXISTS `t_PrimaryAccount` (
  `PrimaryAccountID` char(32) COMMENT '主账户代码',
  `PrimaryAccountName` char(64) COMMENT '主账户名称',
  `AccountClass` int COMMENT '账户类别',
  `BrokerPassword` char(64) COMMENT '经纪公司密码',
  `OfferID` int COMMENT '报盘代码',
  `IsAllowLogin` bool COMMENT '是否允许登陆',
  `IsSimulateAccount` bool COMMENT '是否模拟账号',
  `LoginStatus` int COMMENT '登录状态',
  `InitStatus` int COMMENT '初始化状态',

  INDEX OfferID(OfferID),
  PRIMARY KEY(PrimaryAccountID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='主账户';

CREATE TABLE IF NOT EXISTS `t_Account` (
  `AccountID` char(32) COMMENT '账户代码',
  `AccountName` char(64) COMMENT '账户名称',
  `AccountType` int COMMENT '账户类型',
  `AccountStatus` int COMMENT '账户状态',
  `Password` char(64) COMMENT '密码',
  `TradeGroupID` int COMMENT '交易组代码',
  `RiskGroupID` int COMMENT '交易组代码',
  `CommissionGroupID` int COMMENT '交易组代码',

  PRIMARY KEY(AccountID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='账户';

CREATE TABLE IF NOT EXISTS `t_Capital` (
  `TradingDay` char(9) COMMENT '交易日',
  `AccountID` char(32) COMMENT '账户代码',
  `AccountType` int COMMENT '账户类型',
  `Balance` decimal(24,8) COMMENT '权益',
  `PreBalance` decimal(24,8) COMMENT '上日权益',
  `Available` decimal(24,8) COMMENT '可用资金',
  `MarketValue` decimal(24,8) COMMENT '市值',
  `CashIn` decimal(24,8) COMMENT '现金收入',
  `CashOut` decimal(24,8) COMMENT '现金支出',
  `Margin` decimal(24,8) COMMENT '保证金',
  `Commission` decimal(24,8) COMMENT '手续费',
  `FrozenCash` decimal(24,8) COMMENT '冻结资金',
  `FrozenMargin` decimal(24,8) COMMENT '冻结保证金',
  `FrozenCommission` decimal(24,8) COMMENT '冻结手续费',
  `CloseProfitByDate` decimal(24,8) COMMENT '逐日平仓盈亏',
  `CloseProfitByTrade` decimal(24,8) COMMENT '逐笔平仓盈亏',
  `PositionProfitByDate` decimal(24,8) COMMENT '逐日持仓盈亏',
  `PositionProfitByTrade` decimal(24,8) COMMENT '逐笔持仓盈亏',
  `Deposit` decimal(24,8) COMMENT '入金',
  `Withdraw` decimal(24,8) COMMENT '出金',

  INDEX TradingDay(TradingDay),
  PRIMARY KEY(TradingDay, AccountID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='资金';

CREATE TABLE IF NOT EXISTS `t_Position` (
  `TradingDay` char(9) COMMENT '交易日',
  `AccountID` char(32) COMMENT '账户代码',
  `AccountType` int COMMENT '账户类型',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `PosiDirection` int COMMENT '持仓方向',
  `TotalPosition` bigint COMMENT '持仓数量',
  `PositionFrozen` bigint COMMENT '冻结持仓',
  `TodayPosition` bigint COMMENT '今日持仓',
  `MarketValue` decimal(24,8) COMMENT '市值',
  `CashIn` decimal(24,8) COMMENT '现金收入',
  `CashOut` decimal(24,8) COMMENT '现金支出',
  `Margin` decimal(24,8) COMMENT '保证金',
  `Commission` decimal(24,8) COMMENT '手续费',
  `FrozenCash` decimal(24,8) COMMENT '冻结资金',
  `FrozenMargin` decimal(24,8) COMMENT '冻结保证金',
  `FrozenCommission` decimal(24,8) COMMENT '冻结手续费',
  `VolumeMultiple` int COMMENT '合约乘数',
  `CloseProfitByDate` decimal(24,8) COMMENT '逐日平仓盈亏',
  `CloseProfitByTrade` decimal(24,8) COMMENT '逐笔平仓盈亏',
  `PositionProfitByDate` decimal(24,8) COMMENT '逐日持仓盈亏',
  `PositionProfitByTrade` decimal(24,8) COMMENT '逐笔持仓盈亏',
  `SettlementPrice` decimal(24,8) COMMENT '结算价',
  `PreSettlementPrice` decimal(24,8) COMMENT '昨结算价',

  INDEX Account(TradingDay, AccountID),
  INDEX TradingDay(TradingDay),
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='持仓';

CREATE TABLE IF NOT EXISTS `t_PositionDetail` (
  `TradingDay` char(9) COMMENT '交易日',
  `AccountID` char(32) COMMENT '账户代码',
  `AccountType` int COMMENT '账户类型',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `PosiDirection` int COMMENT '持仓方向',
  `OpenDate` char(9) COMMENT '开仓日期',
  `TradeID` char(64) COMMENT '成交编号',
  `Volume` bigint COMMENT '委托数量',
  `OpenPrice` decimal(24,8) COMMENT '开盘价',
  `MarketValue` decimal(24,8) COMMENT '市值',
  `CashIn` decimal(24,8) COMMENT '现金收入',
  `CashOut` decimal(24,8) COMMENT '现金支出',
  `Margin` decimal(24,8) COMMENT '保证金',
  `Commission` decimal(24,8) COMMENT '手续费',
  `VolumeMultiple` int COMMENT '合约乘数',
  `CloseProfitByDate` decimal(24,8) COMMENT '逐日平仓盈亏',
  `CloseProfitByTrade` decimal(24,8) COMMENT '逐笔平仓盈亏',
  `PositionProfitByDate` decimal(24,8) COMMENT '逐日持仓盈亏',
  `PositionProfitByTrade` decimal(24,8) COMMENT '逐笔持仓盈亏',
  `SettlementPrice` decimal(24,8) COMMENT '结算价',
  `PreSettlementPrice` decimal(24,8) COMMENT '昨结算价',
  `CloseVolume` bigint COMMENT '平仓数量',
  `CloseAmount` decimal(24,8) COMMENT '平仓金额',

  INDEX TradeMatch(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection),
  INDEX TradingDay(TradingDay),
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection, OpenDate, TradeID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='持仓明细';

CREATE TABLE IF NOT EXISTS `t_Order` (
  `TradingDay` char(9) COMMENT '交易日',
  `AccountID` char(32) COMMENT '账户代码',
  `AccountType` int COMMENT '账户类型',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `OrderID` int COMMENT '委托编号',
  `OrderSysID` char(64) COMMENT '系统委托编号',
  `Direction` int COMMENT '买卖方向',
  `OffsetFlag` int COMMENT '开平标志',
  `OrderPriceType` int COMMENT '委托价格类型',
  `Price` decimal(24,8) COMMENT '委托价格',
  `Volume` bigint COMMENT '委托数量',
  `VolumeTotal` bigint COMMENT '剩余数量',
  `VolumeTraded` bigint COMMENT '成交数量',
  `VolumeMultiple` int COMMENT '合约乘数',
  `OrderStatus` int COMMENT '委托状态',
  `OrderDate` char(9) COMMENT '委托日期',
  `OrderTime` char(9) COMMENT '委托时间',
  `CancelDate` char(9) COMMENT '撤单日期',
  `CancelTime` char(9) COMMENT '撤单时间',
  `SessionID` bigint COMMENT '会话编号',
  `ClientOrderID` int COMMENT '客户端委托编号',
  `RequestID` int COMMENT '客户端请求编号',
  `OfferID` int COMMENT '报盘代码',
  `TradeGroupID` int COMMENT '交易组代码',
  `RiskGroupID` int COMMENT '交易组代码',
  `CommissionGroupID` int COMMENT '交易组代码',
  `FrozenCash` decimal(24,8) COMMENT '冻结资金',
  `FrozenMargin` decimal(24,8) COMMENT '冻结保证金',
  `FrozenCommission` decimal(24,8) COMMENT '冻结手续费',
  `RebuildMark` bool COMMENT '重建标志',
  `IsForceClose` bool COMMENT '是否强平单',

  UNIQUE ClientOrderID(TradingDay, AccountID, ExchangeID, InstrumentID, SessionID, ClientOrderID),
  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='委托';

CREATE TABLE IF NOT EXISTS `t_Trade` (
  `TradingDay` char(9) COMMENT '交易日',
  `AccountID` char(32) COMMENT '账户代码',
  `AccountType` int COMMENT '账户类型',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `OrderID` int COMMENT '委托编号',
  `OrderSysID` char(64) COMMENT '系统委托编号',
  `TradeID` char(64) COMMENT '成交编号',
  `Direction` int COMMENT '买卖方向',
  `OffsetFlag` int COMMENT '开平标志',
  `Price` decimal(24,8) COMMENT '委托价格',
  `Volume` bigint COMMENT '委托数量',
  `VolumeMultiple` int COMMENT '合约乘数',
  `TradeAmount` decimal(24,8) COMMENT '成交金额',
  `Commission` decimal(24,8) COMMENT '手续费',
  `TradeDate` char(9) COMMENT '成交日期',
  `TradeTime` char(9) COMMENT '成交时间',

  PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='成交';

CREATE TABLE IF NOT EXISTS `t_DepthMarketData` (
  `TradingDay` char(9) COMMENT '交易日',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `UpdateTs` bigint COMMENT '更新时间戳',
  `LastPrice` decimal(24,8) COMMENT '最新价',
  `PreSettlementPrice` decimal(24,8) COMMENT '昨结算价',
  `PreClosePrice` decimal(24,8) COMMENT '昨收盘价',
  `PreOpenInterest` decimal(24,8) COMMENT '上日持仓量',
  `OpenPrice` decimal(24,8) COMMENT '开盘价',
  `HighestPrice` decimal(24,8) COMMENT '最高价',
  `LowestPrice` decimal(24,8) COMMENT '最低价',
  `ClosePrice` decimal(24,8) COMMENT '收盘价',
  `CurrVolume` bigint COMMENT '当前数量',
  `Volume` bigint COMMENT '委托数量',
  `CurrTurnover` decimal(24,8) COMMENT '当前成交金额',
  `Turnover` decimal(24,8) COMMENT '成交金额',
  `OpenInterest` decimal(24,8) COMMENT '持仓量',
  `SettlementPrice` decimal(24,8) COMMENT '结算价',
  `UpperLimitPrice` decimal(24,8) COMMENT '涨停板价',
  `LowerLimitPrice` decimal(24,8) COMMENT '跌停板价',
  `AveragePrice` decimal(24,8) COMMENT '当日均价',
  `AskPrice1` decimal(24,8) COMMENT '申卖价一',
  `AskPrice2` decimal(24,8) COMMENT '申卖价二',
  `AskPrice3` decimal(24,8) COMMENT '申卖价三',
  `AskPrice4` decimal(24,8) COMMENT '申卖价四',
  `AskPrice5` decimal(24,8) COMMENT '申卖价五',
  `AskPrice6` decimal(24,8) COMMENT '申卖价六',
  `AskPrice7` decimal(24,8) COMMENT '申卖价七',
  `AskPrice8` decimal(24,8) COMMENT '申卖价八',
  `AskPrice9` decimal(24,8) COMMENT '申卖价九',
  `AskPrice10` decimal(24,8) COMMENT '申卖价十',
  `AskVolume1` bigint COMMENT '申卖量一',
  `AskVolume2` bigint COMMENT '申卖量二',
  `AskVolume3` bigint COMMENT '申卖量三',
  `AskVolume4` bigint COMMENT '申卖量四',
  `AskVolume5` bigint COMMENT '申卖量五',
  `AskVolume6` bigint COMMENT '申卖量六',
  `AskVolume7` bigint COMMENT '申卖量七',
  `AskVolume8` bigint COMMENT '申卖量八',
  `AskVolume9` bigint COMMENT '申卖量九',
  `AskVolume10` bigint COMMENT '申卖量十',
  `BidPrice1` decimal(24,8) COMMENT '申买价一',
  `BidPrice2` decimal(24,8) COMMENT '申买价二',
  `BidPrice3` decimal(24,8) COMMENT '申买价三',
  `BidPrice4` decimal(24,8) COMMENT '申买价四',
  `BidPrice5` decimal(24,8) COMMENT '申买价五',
  `BidPrice6` decimal(24,8) COMMENT '申买价六',
  `BidPrice7` decimal(24,8) COMMENT '申买价七',
  `BidPrice8` decimal(24,8) COMMENT '申买价八',
  `BidPrice9` decimal(24,8) COMMENT '申买价九',
  `BidPrice10` decimal(24,8) COMMENT '申买价十',
  `BidVolume1` bigint COMMENT '申买量一',
  `BidVolume2` bigint COMMENT '申买量二',
  `BidVolume3` bigint COMMENT '申买量三',
  `BidVolume4` bigint COMMENT '申买量四',
  `BidVolume5` bigint COMMENT '申买量五',
  `BidVolume6` bigint COMMENT '申买量六',
  `BidVolume7` bigint COMMENT '申买量七',
  `BidVolume8` bigint COMMENT '申买量八',
  `BidVolume9` bigint COMMENT '申买量九',
  `BidVolume10` bigint COMMENT '申买量十',

  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='深度行情';

CREATE TABLE IF NOT EXISTS `t_BarMarketData` (
  `TradingDay` char(9) COMMENT '交易日',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `BarPreces` int COMMENT 'Bar精度',
  `BarPeriod` int COMMENT 'Bar周期',
  `BarTime` bigint COMMENT 'Bar时间',
  `UpdateTs` bigint COMMENT '更新时间戳',
  `PreSettlementPrice` decimal(24,8) COMMENT '昨结算价',
  `PreClosePrice` decimal(24,8) COMMENT '昨收盘价',
  `Open` decimal(24,8) COMMENT '开盘价',
  `High` decimal(24,8) COMMENT '最高价',
  `Low` decimal(24,8) COMMENT '最低价',
  `Close` decimal(24,8) COMMENT '收盘价',
  `CurrVolume` bigint COMMENT '当前数量',
  `Volume` bigint COMMENT '委托数量',
  `CurrTurnover` decimal(24,8) COMMENT '当前成交金额',
  `Turnover` decimal(24,8) COMMENT '成交金额',
  `OpenInterest` decimal(24,8) COMMENT '持仓量',

  PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, BarPreces, BarPeriod, BarTime)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='Bar行情';

CREATE TABLE IF NOT EXISTS `t_MdSubscribe` (
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `RealInstrumentID` char(32) COMMENT '真实合约代码',
  `ProductID` char(32) COMMENT '品种代码',
  `ProductClass` int COMMENT '品种类型',
  `StartTradingDay` char(9) COMMENT '开始交易日',
  `EndTradingDay` char(9) COMMENT '结束交易日',

  PRIMARY KEY(ExchangeID, InstrumentID, StartTradingDay)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='行情订阅';

CREATE TABLE IF NOT EXISTS `t_SEBroker` (
  `BrokerID` int COMMENT '经纪公司代码',
  `BrokerName` char(16) COMMENT '经纪公司名称',
  `Password` char(64) COMMENT '密码',

  PRIMARY KEY(BrokerID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='模拟交易经纪商';

CREATE TABLE IF NOT EXISTS `t_SEInstrument` (
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ExchangeInstID` char(32) COMMENT '交易所合约代码',
  `InstrumentName` char(64) COMMENT '合约名称',
  `ProductID` char(32) COMMENT '品种代码',
  `ProductClass` int COMMENT '品种类型',
  `MaxMarketOrderVolume` bigint COMMENT '市价最大下单量',
  `MinMarketOrderVolume` bigint COMMENT '市价最小下单量',
  `MaxLimitOrderVolume` bigint COMMENT '限价最大下单量',
  `MinLimitOrderVolume` bigint COMMENT '限价最小下单量',
  `VolumeMultiple` int COMMENT '合约乘数',
  `PriceTick` decimal(24,8) COMMENT '最小变动价位',
  `UpperLimitPrice` decimal(24,8) COMMENT '涨停板价',
  `LowerLimitPrice` decimal(24,8) COMMENT '跌停板价',
  `SessionName` char(32) COMMENT '交易节名称',

  PRIMARY KEY(ExchangeID, InstrumentID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='模拟交易合约';

CREATE TABLE IF NOT EXISTS `t_SEOrder` (
  `TradingDay` char(9) COMMENT '交易日',
  `BrokerID` int COMMENT '经纪公司代码',
  `AccountID` char(32) COMMENT '账户代码',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `OrderID` int COMMENT '委托编号',
  `Direction` int COMMENT '买卖方向',
  `OffsetFlag` int COMMENT '开平标志',
  `OrderPriceType` int COMMENT '委托价格类型',
  `Price` decimal(24,8) COMMENT '委托价格',
  `Volume` bigint COMMENT '委托数量',
  `VolumeTotal` bigint COMMENT '剩余数量',
  `VolumeTraded` bigint COMMENT '成交数量',
  `VolumeMultiple` int COMMENT '合约乘数',
  `OrderStatus` int COMMENT '委托状态',
  `OrderDate` char(9) COMMENT '委托日期',
  `OrderTime` char(9) COMMENT '委托时间',
  `CancelDate` char(9) COMMENT '撤单日期',
  `CancelTime` char(9) COMMENT '撤单时间',
  `SessionID` bigint COMMENT '会话编号',
  `ClientOrderID` int COMMENT '客户端委托编号',

  PRIMARY KEY(TradingDay, AccountID, ExchangeID, InstrumentID, OrderID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='模拟交易委托';

CREATE TABLE IF NOT EXISTS `t_SETrade` (
  `TradingDay` char(9) COMMENT '交易日',
  `BrokerID` int COMMENT '经纪公司代码',
  `AccountID` char(32) COMMENT '账户代码',
  `ExchangeID` char(8) COMMENT '交易所代码',
  `InstrumentID` char(32) COMMENT '合约代码',
  `ProductClass` int COMMENT '品种类型',
  `OrderID` int COMMENT '委托编号',
  `TradeID` char(64) COMMENT '成交编号',
  `Direction` int COMMENT '买卖方向',
  `OffsetFlag` int COMMENT '开平标志',
  `Price` decimal(24,8) COMMENT '委托价格',
  `Volume` bigint COMMENT '委托数量',
  `VolumeMultiple` int COMMENT '合约乘数',
  `TradeAmount` decimal(24,8) COMMENT '成交金额',
  `Commission` decimal(24,8) COMMENT '手续费',
  `TradeDate` char(9) COMMENT '成交日期',
  `TradeTime` char(9) COMMENT '成交时间',

  PRIMARY KEY(TradingDay, ExchangeID, TradeID, Direction)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='模拟交易成交';

CREATE TABLE IF NOT EXISTS `t_SEBrokerLoginSession` (
  `BrokerID` int COMMENT '经纪公司代码',
  `SessionID` bigint COMMENT '会话编号',
  `IPAddress` char(16) COMMENT 'IP地址',

  INDEX BrokerID(BrokerID),
  PRIMARY KEY(SessionID)
) ENGINE=MyISAM DEFAULT COLLATE='utf8mb4_bin' COMMENT='模拟交易经纪商登录会话';


