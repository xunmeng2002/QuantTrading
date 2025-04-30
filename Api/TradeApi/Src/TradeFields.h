#pragma once
#include "Types.h"


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

class RspInfoField
{
public:
	static constexpr UShortType FieldID = 0x0001;
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
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
	MoneyType Asset;		//总资产
	MoneyType PreAsset;		//上日总资产
	MoneyType CashAsset;		//现金资产
	MoneyType PreCashAsset;		//上日现金资产
	MoneyType Available;		//可用资金
	MoneyType CashIn;		//现金收入
	MoneyType CashOut;		//现金支出
	MoneyType Margin;		//保证金
	MoneyType Commission;		//手续费
	MoneyType StampTax;		//印花税
	MoneyType TransferFee;		//过户费
	MoneyType FrozenCash;		//冻结资金
	MoneyType FrozenMargin;		//冻结保证金
	MoneyType FrozenCommission;		//冻结手续费
	MoneyType FrozenStampTax;		//冻结印花税
	MoneyType FrozenTransferFee;		//冻结过户费
	MoneyType MarketValue;		//市值
	MoneyType TotalProfit;		//总盈亏
	MoneyType TodayProfit;		//当日盈亏
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
	SecurityTypeType SecurityType;		//证券类别
	PosiDirectionType PosiDirection;		//持仓方向
	VolumeType TotalPosition;		//持仓数量
	VolumeType PositionFrozen;		//冻结持仓
	VolumeType TodayPosition;		//今日持仓
	PriceType TotalCostPrice;		//总成本价
	PriceType TodayCostPrice;		//当日成本价
	MoneyType CashIn;		//现金收入
	MoneyType CashOut;		//现金支出
	MoneyType Margin;		//保证金
	MoneyType Commission;		//手续费
	MoneyType StampTax;		//印花税
	MoneyType TransferFee;		//过户费
	MoneyType MarketValue;		//市值
	VolumeMultipleType VolumeMultiple;		//合约乘数
	MoneyType TotalCost;		//总成本
	MoneyType TodayCost;		//当日成本
	MoneyType TotalProfit;		//总盈亏
	MoneyType TodayProfit;		//当日盈亏
	PriceType LastPrice;		//最新价
	PriceType PrePrice;		//昨收盘价或昨结算价
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
	SecurityTypeType SecurityType;		//证券类别
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
	MessageType StatusMsg;		//状态信息
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
	MoneyType FrozenStampTax;		//冻结印花税
	MoneyType FrozenTransferFee;		//冻结过户费
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
	SecurityTypeType SecurityType;		//证券类别
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
	MoneyType StampTax;		//印花税
	MoneyType TransferFee;		//过户费
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
	SecurityTypeType SecurityType;		//证券类别
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
	VolumeType MaxLimitOrderVolume;		//限价最大下单数量
	VolumeType MaxMarketOrderVolume;		//市价最大下单数量
	DateType ExpiringDate;		//到期日
};

class ReqQryCommissionRateField
{
public:
	static constexpr UShortType FieldID = 0x2016;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	SecurityTypeType SecurityType;		//证券类别
};

class CommissionRateField
{
public:
	static constexpr UShortType FieldID = 0x2017;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	SecurityTypeType SecurityType;		//证券类别
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
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};

class CancelOrderField
{
public:
	static constexpr UShortType FieldID = 0x201C;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ClientOrderIDType ClientCancelOrderID;		//客户端撤单委托编号
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};

class AccountLogoutField
{
public:
	static constexpr UShortType FieldID = 0x2005;
	AccountIDType AccountID;		//账户代码
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};

