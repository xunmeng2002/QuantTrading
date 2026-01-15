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
	ProductIDType ProductID;		//品种代码
	ProductClassType ProductClass;		//品种类型
	VolumeMultipleType VolumeMultiple;		//合约乘数
	PriceType PriceTick;		//最小变动价位
	VolumeType MaxMarketOrderVolume;		//市价最大下单量
	VolumeType MinMarketOrderVolume;		//市价最小下单量
	VolumeType MaxLimitOrderVolume;		//限价最大下单量
	VolumeType MinLimitOrderVolume;		//限价最小下单量
	SessionNameType SessionName;		//交易节名称
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

