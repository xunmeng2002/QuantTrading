// 本文件由 ../Templates/Cpp/Protocol/Packages/Fields.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <Spark/Types.h>

class RspInfoField
{
public:
	static constexpr UInt16Type FieldId = 0x0001;
	ErrorIdType ErrorId;		//错误代码
	MessageType ErrorMsg;		//错误信息
};
class NotifyConnectField
{
public:
	static constexpr UInt16Type FieldId = 0x0002;
	SessionIdType SessionId;		//会话编号
	IpAddressType IpAddress;		//Ip地址
	Int32Type Port;		//端口
};
class NotifyDisConnectField
{
public:
	static constexpr UInt16Type FieldId = 0x0003;
	SessionIdType SessionId;		//会话编号
	IpAddressType IpAddress;		//Ip地址
	Int32Type Port;		//端口
};
class NotifyDbConnectField
{
public:
	static constexpr UInt16Type FieldId = 0x0004;
	DbNameType DbName;		//数据库名称
};
class NotifyDbDisConnectField
{
public:
	static constexpr UInt16Type FieldId = 0x0005;
	DbNameType DbName;		//数据库名称
};
class ReqMdUserLoginField
{
public:
	static constexpr UInt16Type FieldId = 0x1001;
	UserIdType UserId;		//用户代码
	PasswordType Password;		//密码
};
class RspMdUserLoginField
{
public:
	static constexpr UInt16Type FieldId = 0x1002;
	UserIdType UserId;		//用户代码
	DateType LoginDate;		//登录日期
	TimeType LoginTime;		//登录时间
	SessionIdType SessionId;		//会话编号
};
class ReqMdUserLogoutField
{
public:
	static constexpr UInt16Type FieldId = 0x1003;
	UserIdType UserId;		//用户代码
};
class RspMdUserLogoutField
{
public:
	static constexpr UInt16Type FieldId = 0x1004;
	UserIdType UserId;		//用户代码
};
class ReqSubMarketDataField
{
public:
	static constexpr UInt16Type FieldId = 0x1005;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	BarPrecesType BarPreces;		//Bar精度
	Int32Type BarPeriod;		//Bar周期
};
class RspSubMarketDataField
{
public:
	static constexpr UInt16Type FieldId = 0x1006;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
};
class ReqUnSubMarketDataField
{
public:
	static constexpr UInt16Type FieldId = 0x1007;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
};
class RspUnSubMarketDataField
{
public:
	static constexpr UInt16Type FieldId = 0x1008;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
};
class ReqSubMarketDataFinishedField
{
public:
	static constexpr UInt16Type FieldId = 0x1009;
	SessionIdType SessionId;		//会话编号
};
class DepthMarketDataField
{
public:
	static constexpr UInt16Type FieldId = 0x100A;
	DateType TradingDay;		//交易日
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
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
	static constexpr UInt16Type FieldId = 0x100B;
	DateType TradingDay;		//交易日
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	BarPrecesType BarPreces;		//Bar精度
	Int32Type BarPeriod;		//Bar周期
	Int64Type BarTime;		//Bar时间
	Int64Type UpdateTs;		//更新时间戳
	PriceType PreSettlementPrice;		//昨结算价
	PriceType PreClosePrice;		//昨收盘价
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
	static constexpr UInt16Type FieldId = 0x100C;
	DateType TradingDay;		//交易日
};
class SessionEndField
{
public:
	static constexpr UInt16Type FieldId = 0x100D;
	DateType TradingDay;		//交易日
};
class MarketDataEndField
{
public:
	static constexpr UInt16Type FieldId = 0x100E;
	DateType TradingDay;		//交易日
};
class ReqRegisterAccountField
{
public:
	static constexpr UInt16Type FieldId = 0x2001;
	AccountIdType AccountId;		//账户代码
};
class RspRegisterAccountField
{
public:
	static constexpr UInt16Type FieldId = 0x2002;
	AccountIdType AccountId;		//账户代码
};
class ReqAccountLoginField
{
public:
	static constexpr UInt16Type FieldId = 0x2003;
	AccountIdType AccountId;		//账户代码
	PasswordType Password;		//密码
};
class RspAccountLoginField
{
public:
	static constexpr UInt16Type FieldId = 0x2004;
	AccountIdType AccountId;		//账户代码
	DateType LoginDate;		//登录日期
	TimeType LoginTime;		//登录时间
	SessionIdType SessionId;		//会话编号
};
class ReqAccountLogoutField
{
public:
	static constexpr UInt16Type FieldId = 0x2005;
	AccountIdType AccountId;		//账户代码
};
class RspAccountLogoutField
{
public:
	static constexpr UInt16Type FieldId = 0x2006;
	AccountIdType AccountId;		//账户代码
};
class AccountLogoutField
{
public:
	static constexpr UInt16Type FieldId = 0x2007;
	AccountIdType AccountId;		//账户代码
	ErrorIdType ErrorId;		//错误代码
	MessageType ErrorMsg;		//错误信息
};
class ReqQryAccountField
{
public:
	static constexpr UInt16Type FieldId = 0x2008;
	AccountIdType AccountId;		//账户代码
};
class AccountField
{
public:
	static constexpr UInt16Type FieldId = 0x2009;
	AccountIdType AccountId;		//账户代码
	AccountTypeType AccountType;		//账户类型
	AccountStatusType AccountStatus;		//账户状态
	GroupIdType TradeGroupId;		//交易组代码
	GroupIdType RiskGroupId;		//交易组代码
	GroupIdType CommissionGroupId;		//交易组代码
};
class ReqQryHolderAccountField
{
public:
	static constexpr UInt16Type FieldId = 0x200A;
	AccountIdType AccountId;		//账户代码
};
class HolderAccountField
{
public:
	static constexpr UInt16Type FieldId = 0x200B;
	ExchangeIdType ExchangeId;		//交易所代码
	AccountIdType HolderAccountId;		//股东账户代码
	BoolType PrimaryFlag;		//主账号标志
};
class ReqQryCapitalField
{
public:
	static constexpr UInt16Type FieldId = 0x200C;
	AccountIdType AccountId;		//账户代码
};
class CapitalField
{
public:
	static constexpr UInt16Type FieldId = 0x200D;
	DateType TradingDay;		//交易日
	AccountIdType AccountId;		//账户代码
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
	static constexpr UInt16Type FieldId = 0x200E;
	AccountIdType AccountId;		//账户代码
};
class PositionField
{
public:
	static constexpr UInt16Type FieldId = 0x200F;
	DateType TradingDay;		//交易日
	AccountIdType AccountId;		//账户代码
	AccountTypeType AccountType;		//账户类型
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
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
	static constexpr UInt16Type FieldId = 0x2010;
	AccountIdType AccountId;		//账户代码
};
class OrderField
{
public:
	static constexpr UInt16Type FieldId = 0x2011;
	DateType TradingDay;		//交易日
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIdType OrderId;		//委托编号
	OrderSysIdType OrderSysId;		//系统委托编号
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
	SessionIdType SessionId;		//会话编号
	ClientOrderIdType ClientOrderId;		//客户端委托编号
	RequestIdType RequestId;		//客户端请求编号
	MoneyType FrozenCash;		//冻结资金
	MoneyType FrozenMargin;		//冻结保证金
	MoneyType FrozenCommission;		//冻结手续费
};
class ReqQryTradeField
{
public:
	static constexpr UInt16Type FieldId = 0x2012;
	AccountIdType AccountId;		//账户代码
};
class TradeField
{
public:
	static constexpr UInt16Type FieldId = 0x2013;
	DateType TradingDay;		//交易日
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIdType OrderId;		//委托编号
	OrderSysIdType OrderSysId;		//系统委托编号
	TradeIdType TradeId;		//成交编号
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
	static constexpr UInt16Type FieldId = 0x2014;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
};
class InstrumentField
{
public:
	static constexpr UInt16Type FieldId = 0x2015;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	InstrumentIdType ExchangeInstId;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	ProductIdType ProductId;		//品种代码
	ProductClassType ProductClass;		//品种类型
	VolumeMultipleType VolumeMultiple;		//合约乘数
	PriceType PriceTick;		//最小变动价位
	VolumeType MaxMarketOrderVolume;		//市价最大下单量
	VolumeType MinMarketOrderVolume;		//市价最小下单量
	VolumeType MaxLimitOrderVolume;		//限价最大下单量
	VolumeType MinLimitOrderVolume;		//限价最小下单量
	SessionNameType SessionName;		//交易节名称
};
class ReqQryOptionInstrumentField
{
public:
	static constexpr UInt16Type FieldId = 0x2016;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
};
class OptionInstrumentField
{
public:
	static constexpr UInt16Type FieldId = 0x2017;
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	InstrumentIdType ExchangeInstId;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	VolumeMultipleType VolumeMultiple;		//合约乘数
	OptionTypeType OptionType;		//期权类型
	InstrumentIdType UnderlyingInstrumentId;		//标的合约代码
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
	static constexpr UInt16Type FieldId = 0x2018;
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
	ProductClassType ProductClass;		//品种类型
};
class CommissionRateField
{
public:
	static constexpr UInt16Type FieldId = 0x2019;
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
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
	static constexpr UInt16Type FieldId = 0x201A;
	AccountIdType AccountId;		//账户代码
};
class MoneyTransferField
{
public:
	static constexpr UInt16Type FieldId = 0x201B;
	DateType TradingDay;		//交易日
	AccountIdType AccountId;		//账户代码
	SequenceNoType MoneyTransferId;		//出入金编号
	AccountTypeType AccountType;		//账户类型
	TransferDirectionType TransferDirection;		//转移方向
	MoneyType TransferAmount;		//转移金额
	MessageType InfoMessage;		//备注信息
	UserIdType UserId;		//用户代码
	DateType TransferDate;		//操作日期
	TimeType TransferTime;		//操作时间
};
class ReqInsertOrderField
{
public:
	static constexpr UInt16Type FieldId = 0x201C;
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	ClientOrderIdType ClientOrderId;		//客户端委托编号
};
class ReqCancelOrderField
{
public:
	static constexpr UInt16Type FieldId = 0x201D;
	AccountIdType AccountId;		//账户代码
	ExchangeIdType ExchangeId;		//交易所代码
	InstrumentIdType InstrumentId;		//合约代码
	ClientOrderIdType ClientCancelOrderId;		//客户端撤单委托编号
	OrderIdType OrderId;		//委托编号
	OrderSysIdType OrderSysId;		//系统委托编号
	SessionIdType SessionId;		//会话编号
	ClientOrderIdType ClientOrderId;		//客户端委托编号
};
