#pragma once
#include "Types.h"

class RspInfoField
{
public:
	static constexpr UShortType FieldID = 0x0001;
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};
class NotifyConnectField
{
public:
	static constexpr UShortType FieldID = 0x0002;
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
	IntType Port;		//端口
};
class NotifyDisConnectField
{
public:
	static constexpr UShortType FieldID = 0x0003;
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
	IntType Port;		//端口
};
class ReqMdUserLoginField
{
public:
	static constexpr UShortType FieldID = 0x1001;
	UserIDType UserID;		//用户代码
	PasswordType Password;		//密码
};
class RspMdUserLoginField
{
public:
	static constexpr UShortType FieldID = 0x1002;
	UserIDType UserID;		//用户代码
	DateType LoginDate;		//登录日期
	TimeType LoginTime;		//登录时间
	SessionIDType SessionID;		//会话编号
};
class ReqMdUserLogoutField
{
public:
	static constexpr UShortType FieldID = 0x1003;
	UserIDType UserID;		//用户代码
};
class RspMdUserLogoutField
{
public:
	static constexpr UShortType FieldID = 0x1004;
	UserIDType UserID;		//用户代码
};
class ReqSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1005;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class RspSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1006;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class ReqUnSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1007;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class RspUnSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1008;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class ReqSubMarketDataFinishedField
{
public:
	static constexpr UShortType FieldID = 0x1009;
	SessionIDType SessionID;		//会话编号
};
class DepthMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x100A;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	Int64Type UpdateTs;		//更新时间戳
	PriceType LastPrice;		//最新价
	PriceType PreSettlementPrice;		//昨结算价
	PriceType PreClosePrice;		//昨收盘价
	LargeVolumeType PreOpenInterest;		//上日持仓量
	PriceType OpenPrice;		//开盘价
	PriceType HighestPrice;		//最高价
	PriceType LowestPrice;		//最低价
	PriceType ClosePrice;		//收盘价
	VolumeType CurrVolume;		//当前数量
	VolumeType Volume;		//委托数量
	MoneyType CurrTurnover;		//当前成交金额
	MoneyType Turnover;		//成交金额
	LargeVolumeType OpenInterest;		//持仓量
	PriceType SettlementPrice;		//结算价
	PriceType UpperLimitPrice;		//涨停板价
	PriceType LowerLimitPrice;		//跌停板价
	PriceType AveragePrice;		//当日均价
	PriceType AskPrice1;		//申卖价一
	PriceType AskPrice2;		//申卖价二
	PriceType AskPrice3;		//申卖价三
	PriceType AskPrice4;		//申卖价四
	PriceType AskPrice5;		//申卖价五
	PriceType AskPrice6;		//申卖价六
	PriceType AskPrice7;		//申卖价七
	PriceType AskPrice8;		//申卖价八
	PriceType AskPrice9;		//申卖价九
	PriceType AskPrice10;		//申卖价十
	VolumeType AskVolume1;		//申卖量一
	VolumeType AskVolume2;		//申卖量二
	VolumeType AskVolume3;		//申卖量三
	VolumeType AskVolume4;		//申卖量四
	VolumeType AskVolume5;		//申卖量五
	VolumeType AskVolume6;		//申卖量六
	VolumeType AskVolume7;		//申卖量七
	VolumeType AskVolume8;		//申卖量八
	VolumeType AskVolume9;		//申卖量九
	VolumeType AskVolume10;		//申卖量十
	PriceType BidPrice1;		//申买价一
	PriceType BidPrice2;		//申买价二
	PriceType BidPrice3;		//申买价三
	PriceType BidPrice4;		//申买价四
	PriceType BidPrice5;		//申买价五
	PriceType BidPrice6;		//申买价六
	PriceType BidPrice7;		//申买价七
	PriceType BidPrice8;		//申买价八
	PriceType BidPrice9;		//申买价九
	PriceType BidPrice10;		//申买价十
	VolumeType BidVolume1;		//申买量一
	VolumeType BidVolume2;		//申买量二
	VolumeType BidVolume3;		//申买量三
	VolumeType BidVolume4;		//申买量四
	VolumeType BidVolume5;		//申买量五
	VolumeType BidVolume6;		//申买量六
	VolumeType BidVolume7;		//申买量七
	VolumeType BidVolume8;		//申买量八
	VolumeType BidVolume9;		//申买量九
	VolumeType BidVolume10;		//申买量十
};
class BarMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x100B;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	BarPrecesType BarPreces;		//Bar精度
	IntType BarPeriod;		//Bar周期
	Int64Type BarTime;		//Bar时间
	Int64Type UpdateTs;		//更新时间戳
	PriceType HighestPrice;		//最高价
	PriceType LowestPrice;		//最低价
	PriceType Open;		//开盘价
	PriceType High;		//最高价
	PriceType Low;		//最低价
	PriceType Close;		//收盘价
	VolumeType CurrVolume;		//当前数量
	VolumeType Volume;		//委托数量
	MoneyType CurrTurnover;		//当前成交金额
	MoneyType Turnover;		//成交金额
	LargeVolumeType OpenInterest;		//持仓量
};
class SessionBeginField
{
public:
	static constexpr UShortType FieldID = 0x100C;
	DateType TradingDay;		//交易日
};
class SessionEndField
{
public:
	static constexpr UShortType FieldID = 0x100D;
	DateType TradingDay;		//交易日
};
class MarketDataEndField
{
public:
	static constexpr UShortType FieldID = 0x100D;
	DateType TradingDay;		//交易日
};
class ReqAccountLoginField
{
public:
	static constexpr UShortType FieldID = 0x2001;
	AccountIDType AccountID;		//账户代码
	PasswordType Password;		//密码
};
class RspAccountLoginField
{
public:
	static constexpr UShortType FieldID = 0x2002;
	AccountIDType AccountID;		//账户代码
	DateType LoginDate;		//登录日期
	TimeType LoginTime;		//登录时间
	SessionIDType SessionID;		//会话编号
};
class ReqAccountLogoutField
{
public:
	static constexpr UShortType FieldID = 0x2003;
	AccountIDType AccountID;		//账户代码
};
class RspAccountLogoutField
{
public:
	static constexpr UShortType FieldID = 0x2004;
	AccountIDType AccountID;		//账户代码
};
class AccountLogoutField
{
public:
	static constexpr UShortType FieldID = 0x2005;
	AccountIDType AccountID;		//账户代码
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};
class ReqQryAccountField
{
public:
	static constexpr UShortType FieldID = 0x2006;
	AccountIDType AccountID;		//账户代码
};
class AccountField
{
public:
	static constexpr UShortType FieldID = 0x2007;
	AccountIDType AccountID;		//账户代码
	AccountTypeType AccountType;		//账户类型
	AccountStatusType AccountStatus;		//账户状态
	GroupIDType TradeGroupID;		//交易组代码
	GroupIDType RiskGroupID;		//交易组代码
	GroupIDType CommissionGroupID;		//交易组代码
};
class ReqQryHolderAccountField
{
public:
	static constexpr UShortType FieldID = 0x2008;
	AccountIDType AccountID;		//账户代码
};
class HolderAccountField
{
public:
	static constexpr UShortType FieldID = 0x2009;
	ExchangeIDType ExchangeID;		//交易所代码
	AccountIDType HolderAccountID;		//股东账户代码
	BoolType PrimaryFlag;		//主账号标志
};
class ReqQryCapitalField
{
public:
	static constexpr UShortType FieldID = 0x200A;
	AccountIDType AccountID;		//账户代码
};
class CapitalField
{
public:
	static constexpr UShortType FieldID = 0x200B;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	AccountTypeType AccountType;		//账户类型
	MoneyType Balance;		//权益
	MoneyType PreBalance;		//上日权益
	MoneyType Available;		//可用资金
	MoneyType MarketValue;		//市值
	MoneyType CashIn;		//现金收入
	MoneyType CashOut;		//现金支出
	MoneyType Margin;		//保证金
	MoneyType Commission;		//手续费
	MoneyType FrozenCash;		//冻结资金
	MoneyType FrozenMargin;		//冻结保证金
	MoneyType FrozenCommission;		//冻结手续费
	MoneyType CloseProfitByDate;		//逐日平仓盈亏
	MoneyType CloseProfitByTrade;		//逐笔平仓盈亏
	MoneyType PositionProfitByDate;		//逐日持仓盈亏
	MoneyType PositionProfitByTrade;		//逐笔持仓盈亏
	MoneyType Deposit;		//入金
	MoneyType Withdraw;		//出金
};
class ReqQryPositionField
{
public:
	static constexpr UShortType FieldID = 0x200C;
	AccountIDType AccountID;		//账户代码
};
class PositionField
{
public:
	static constexpr UShortType FieldID = 0x200D;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	AccountTypeType AccountType;		//账户类型
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	PosiDirectionType PosiDirection;		//持仓方向
	VolumeType TotalPosition;		//持仓数量
	VolumeType PositionFrozen;		//冻结持仓
	VolumeType TodayPosition;		//今日持仓
	MoneyType MarketValue;		//市值
	MoneyType CashIn;		//现金收入
	MoneyType CashOut;		//现金支出
	MoneyType Margin;		//保证金
	MoneyType Commission;		//手续费
	VolumeMultipleType VolumeMultiple;		//合约乘数
	MoneyType CloseProfitByDate;		//逐日平仓盈亏
	MoneyType CloseProfitByTrade;		//逐笔平仓盈亏
	MoneyType PositionProfitByDate;		//逐日持仓盈亏
	MoneyType PositionProfitByTrade;		//逐笔持仓盈亏
	PriceType LastPrice;		//最新价
	PriceType PreSettlementPrice;		//昨结算价
};
class ReqQryOrderField
{
public:
	static constexpr UShortType FieldID = 0x200E;
	AccountIDType AccountID;		//账户代码
};
class OrderField
{
public:
	static constexpr UShortType FieldID = 0x200F;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeType VolumeTotal;		//剩余数量
	VolumeType VolumeTraded;		//成交数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	OrderStatusType OrderStatus;		//委托状态
	DateType OrderDate;		//委托日期
	TimeType OrderTime;		//委托时间
	DateType CancelDate;		//撤单日期
	TimeType CancelTime;		//撤单时间
	SessionIDType SessionID;		//会话编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
	RequestIDType RequestID;		//客户端请求编号
	MoneyType FrozenCash;		//冻结资金
	MoneyType FrozenMargin;		//冻结保证金
	MoneyType FrozenCommission;		//冻结手续费
};
class ReqQryTradeField
{
public:
	static constexpr UShortType FieldID = 0x2010;
	AccountIDType AccountID;		//账户代码
};
class TradeField
{
public:
	static constexpr UShortType FieldID = 0x2011;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	TradeIDType TradeID;		//成交编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	MoneyType TradeAmount;		//成交金额
	MoneyType Commission;		//手续费
	DateType TradeDate;		//成交日期
	TimeType TradeTime;		//成交时间
};
class ReqQryInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x2012;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class InstrumentField
{
public:
	static constexpr UShortType FieldID = 0x2013;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	InstrumentIDType ExchangeInstID;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	VolumeMultipleType VolumeMultiple;		//合约乘数
	ProductClassType ProductClass;		//品种类型
};
class ReqQryOptionInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x2014;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class OptionInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x2015;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	InstrumentIDType ExchangeInstID;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	VolumeMultipleType VolumeMultiple;		//合约乘数
	OptionTypeType OptionType;		//期权类型
	InstrumentIDType UnderlyingInstrumentID;		//标的合约代码
	PriceType ExecutePrice;		//行权价
	MoneyType UnitMargin;		//单位保证金
	PriceType PriceTick;		//最小变动价位
	VolumeType MaxLimitOrderVolume;		//限价最大下单量
	VolumeType MaxMarketOrderVolume;		//市价最大下单量
	DateType ExpiringDate;		//到期日
};
class ReqQryCommissionRateField
{
public:
	static constexpr UShortType FieldID = 0x2016;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	ProductClassType ProductClass;		//品种类型
};
class CommissionRateField
{
public:
	static constexpr UShortType FieldID = 0x2017;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	ProductClassType ProductClass;		//品种类型
	RateType OpenBuyByMoney;		//买开仓费率
	RateType OpenSellByMoney;		//卖开仓费率
	RateType CloseBuyByMoney;		//买平仓费率
	RateType CloseSellByMoney;		//卖平仓费率
	RateType OpenBuyByVolume;		//每手买开仓费用
	RateType OpenSellByVolume;		//每手卖开仓费用
	RateType CloseBuyByVolume;		//每手买平仓费用
	RateType CloseSellByVolume;		//每手卖平仓费用
	MoneyType MinCommission;		//最低手续费
	MoneyType MaxCommission;		//最高手续费
};
class ReqQryMoneyTransferField
{
public:
	static constexpr UShortType FieldID = 0x2018;
	AccountIDType AccountID;		//账户代码
};
class MoneyTransferField
{
public:
	static constexpr UShortType FieldID = 0x2019;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	SequenceNoType MoneyTransferID;		//出入金编号
	AccountTypeType AccountType;		//账户类型
	TransferDirectionType TransferDirection;		//转移方向
	MoneyType TransferAmount;		//转移金额
	MessageType InfoMessage;		//备注信息
	UserIDType UserID;		//用户代码
	DateType TransferDate;		//操作日期
	TimeType TransferTime;		//操作时间
};
class ReqInsertOrderField
{
public:
	static constexpr UShortType FieldID = 0x201A;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};
class ReqCancelOrderField
{
public:
	static constexpr UShortType FieldID = 0x201B;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ClientOrderIDType ClientCancelOrderID;		//客户端撤单委托编号
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	SessionIDType SessionID;		//会话编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};
class ReqSEBrokerLoginField
{
public:
	static constexpr UShortType FieldID = 0x3001;
	BrokerIDType BrokerID;		//经纪公司代码
	PasswordType Password;		//密码
};
class RspSEBrokerLoginField
{
public:
	static constexpr UShortType FieldID = 0x3002;
	BrokerIDType BrokerID;		//经纪公司代码
	BrokerNameType BrokerName;		//经纪公司名称
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
};
class ReqSEInsertOrderField
{
public:
	static constexpr UShortType FieldID = 0x3003;
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};
class ReqSECancelOrderField
{
public:
	static constexpr UShortType FieldID = 0x3004;
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	OrderIDType CancelOrderID;		//本地撤单编号
	OrderIDType OrderID;		//委托编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
	SessionIDType SessionID;		//会话编号
};
class ReqQrySEOrderField
{
public:
	static constexpr UShortType FieldID = 0x3005;
	AccountIDType AccountID;		//账户代码
};
class SEOrderField
{
public:
	static constexpr UShortType FieldID = 0x3006;
	DateType TradingDay;		//交易日
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeType VolumeTotal;		//剩余数量
	VolumeType VolumeTraded;		//成交数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	OrderStatusType OrderStatus;		//委托状态
	DateType OrderDate;		//委托日期
	TimeType OrderTime;		//委托时间
	DateType CancelDate;		//撤单日期
	TimeType CancelTime;		//撤单时间
	SessionIDType SessionID;		//会话编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};
class ReqQrySETradeField
{
public:
	static constexpr UShortType FieldID = 0x3007;
	AccountIDType AccountID;		//账户代码
};
class SETradeField
{
public:
	static constexpr UShortType FieldID = 0x3008;
	DateType TradingDay;		//交易日
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	TradeIDType TradeID;		//成交编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	MoneyType TradeAmount;		//成交金额
	MoneyType Commission;		//手续费
	DateType TradeDate;		//成交日期
	TimeType TradeTime;		//成交时间
};
class ReqQrySEInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x3009;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class SEInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x300A;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	InstrumentIDType ExchangeInstID;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	ProductIDType ProductID;		//品种代码
	ProductClassType ProductClass;		//品种类型
	VolumeType MaxMarketOrderVolume;		//市价最大下单量
	VolumeType MinMarketOrderVolume;		//市价最小下单量
	VolumeType MaxLimitOrderVolume;		//限价最大下单量
	VolumeType MinLimitOrderVolume;		//限价最小下单量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	PriceType PriceTick;		//最小变动价位
	PriceType UpperLimitPrice;		//涨停板价
	PriceType LowerLimitPrice;		//跌停板价
};
